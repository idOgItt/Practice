#include <not_implemented.h>
#include <cstddef>
#include "../include/allocator_boundary_tags.h"

allocator_boundary_tags::~allocator_boundary_tags()
{
    get_mutex().~mutex();
    deallocate_with_guard(_trusted_memory);
}

allocator_boundary_tags::allocator_boundary_tags(
    allocator_boundary_tags &&other) noexcept
{
    _trusted_memory = std::exchange(other._trusted_memory, nullptr);
}

allocator_boundary_tags &allocator_boundary_tags::operator=(
    allocator_boundary_tags &&other) noexcept
{
    std::swap(_trusted_memory, other._trusted_memory);
    return *this;
}

allocator_boundary_tags::allocator_boundary_tags(
    size_t space_size,
    allocator *parent_allocator,
    logger *logger,
    allocator_with_fit_mode::fit_mode allocate_fit_mode)
{
    size_t real_size = space_size + allocator_metadata_size;

    _trusted_memory = (parent_allocator == nullptr) ? ::operator new(real_size) : parent_allocator->allocate(real_size, 1);

    auto logger_ptr = reinterpret_cast<class logger**>(_trusted_memory);

    *logger_ptr = logger;

    auto parent_allocator_ptr = reinterpret_cast<allocator**>(logger_ptr + 1);

    *parent_allocator_ptr = parent_allocator;

    auto fit_mode_ptr = reinterpret_cast<allocator_with_fit_mode::fit_mode*>(parent_allocator_ptr + 1);

    *fit_mode_ptr = allocate_fit_mode;

    auto size_ptr = reinterpret_cast<size_t*>(fit_mode_ptr + 1);

    *size_ptr = space_size;

    auto mutex_ptr = reinterpret_cast<std::mutex*>(size_ptr + 1);

    construct(mutex_ptr);

    auto first_block_ptr = reinterpret_cast<void**>(mutex_ptr + 1);

    *first_block_ptr = nullptr;
}

[[nodiscard]] void *allocator_boundary_tags::allocate(
    size_t value_size,
    size_t values_count)
{
    std::lock_guard lock(get_mutex());

    size_t real_size = value_size * values_count + occupied_block_metadata_size;

    debug_with_guard("Allocator boundary tags started allocating " + std::to_string(real_size) + " bytes");

    void* prev_occupied;

    switch (get_fit_mod())
    {
        case allocator_with_fit_mode::fit_mode::first_fit:
            prev_occupied = get_first(real_size);
            break;
        case allocator_with_fit_mode::fit_mode::the_best_fit:
            prev_occupied = get_best(real_size);
            break;
        case allocator_with_fit_mode::fit_mode::the_worst_fit:
            prev_occupied = get_worst(real_size);
            break;
    }

    if (prev_occupied == nullptr)
    {
        error_with_guard("Allocator boundary tags throwing bad_alloc while trying to allocate " + std::to_string(real_size) + " bytes");
        throw std::bad_alloc();
    }

    size_t free_block_size = get_next_free_size(prev_occupied);

    if (free_block_size < real_size + occupied_block_metadata_size)
    {
        warning_with_guard("Allocator with boundary tags changed allocating block size to " + std::to_string(free_block_size));
        real_size = free_block_size;
    }

    void* free_block_start;

    if (prev_occupied == _trusted_memory)
    {
        free_block_start = reinterpret_cast<std::byte*>(_trusted_memory) + allocator_metadata_size;
    } else
    {
        free_block_start = reinterpret_cast<std::byte*>(prev_occupied) + get_occupied_size(prev_occupied) + occupied_block_metadata_size;
    }

    auto size_ptr = reinterpret_cast<size_t*>(free_block_start);

    *size_ptr = real_size;

    auto back_ptr = reinterpret_cast<void**>(size_ptr + 1);

    *back_ptr = prev_occupied;

    auto forward_ptr = reinterpret_cast<void**>(back_ptr + 1);

    *forward_ptr = prev_occupied == _trusted_memory ? *get_first_block_ptr() : get_next_from_occupied(prev_occupied);

    auto parent_ptr = reinterpret_cast<void**>(forward_ptr + 1);

    *parent_ptr = _trusted_memory;

    void* next_block;

    if (prev_occupied == _trusted_memory)
    {
        next_block = *get_first_block_ptr();
    } else
    {
        next_block = get_next_from_occupied(prev_occupied);
    }

    if (next_block != nullptr)
    {
        auto byte_ptr = reinterpret_cast<std::byte*>(next_block);
        byte_ptr += sizeof(size_t);
        *reinterpret_cast<void**>(byte_ptr) = free_block_start;
    }

    if (prev_occupied == _trusted_memory)
    {
        *get_first_block_ptr() = free_block_start;
    } else
    {
        auto byte_ptr = reinterpret_cast<std::byte*>(prev_occupied);
        byte_ptr += sizeof(size_t) + sizeof(void*);
        *reinterpret_cast<void**>(byte_ptr) = free_block_start;
    }

    information_with_guard(std::to_string(get_free_size()));
    debug_with_guard(print_blocks());

    return reinterpret_cast<std::byte*>(free_block_start) + occupied_block_metadata_size;
}

void allocator_boundary_tags::deallocate(
    void *at)
{
    std::lock_guard lock(get_mutex());

    void* block_start = reinterpret_cast<std::byte*>(at) - occupied_block_metadata_size;

    void* parent_ptr = reinterpret_cast<std::byte*>(block_start) + sizeof(size_t) + sizeof(void*) * 2;

    if (parent_ptr != _trusted_memory)
    {
        error_with_guard("Incorrect deallocation object");
        throw std::logic_error("Incorrect deallocation object");
    }

    size_t block_size = *reinterpret_cast<size_t*>(block_start);

    debug_with_guard(get_dump((char*)at, block_size));

    void* prev_block = reinterpret_cast<std::byte*>(block_start) + sizeof(size_t);
    void* next_block = reinterpret_cast<std::byte*>(block_start) + sizeof(size_t) + sizeof(void*);

    if (prev_block == _trusted_memory)
    {
        *get_first_block_ptr() = next_block;
    } else
    {
        auto byte_ptr = reinterpret_cast<std::byte*>(prev_block) + sizeof(size_t) + sizeof(void*);
        *reinterpret_cast<void**>(byte_ptr) = next_block;
    }

    if (next_block != nullptr)
    {
        auto byte_ptr = reinterpret_cast<std::byte*>(prev_block) + sizeof(size_t);
        *reinterpret_cast<void**>(byte_ptr) = prev_block;
    }

    information_with_guard(std::to_string(get_free_size()));
    debug_with_guard(print_blocks());
}

inline void allocator_boundary_tags::set_fit_mode(
    allocator_with_fit_mode::fit_mode mode)
{
    std::lock_guard lock(get_mutex());
    get_fit_mod() = mode;
}

inline allocator *allocator_boundary_tags::get_allocator() const
{
    auto byte_ptr = reinterpret_cast<std::byte*>(_trusted_memory);

    return reinterpret_cast<allocator*>(byte_ptr + sizeof(logger*));
}

std::vector<allocator_test_utils::block_info> allocator_boundary_tags::get_blocks_info() const noexcept
{
    std::lock_guard lock(get_mutex());
    throw not_implemented("std::vector<allocator_test_utils::block_info> allocator_boundary_tags::get_blocks_info() const noexcept", "your code should be here...");
}

inline logger *allocator_boundary_tags::get_logger() const
{
    return reinterpret_cast<logger*>(_trusted_memory);
}

inline std::string allocator_boundary_tags::get_typename() const noexcept
{
    return "allocator_boundary_tags";
}

allocator_with_fit_mode::fit_mode& allocator_boundary_tags::get_fit_mod() const noexcept
{
    auto byte_ptr = reinterpret_cast<std::byte*>(_trusted_memory);

    return *reinterpret_cast<fit_mode*>(byte_ptr + sizeof(logger*) + sizeof(allocator*));
}

size_t allocator_boundary_tags::get_overall_size() const noexcept
{
    auto byte_ptr = reinterpret_cast<std::byte*>(_trusted_memory);

    return *reinterpret_cast<size_t*>(byte_ptr + sizeof(logger*) + sizeof(allocator*) + sizeof(fit_mode));
}

std::mutex &allocator_boundary_tags::get_mutex() const noexcept
{
    auto byte_ptr = reinterpret_cast<std::byte*>(_trusted_memory);

    return *reinterpret_cast<std::mutex*>(byte_ptr + sizeof(logger*) + sizeof(allocator*) + sizeof(fit_mode) + sizeof(size_t));
}

void *allocator_boundary_tags::get_first(size_t size) const noexcept
{
    return nullptr;
}

void *allocator_boundary_tags::get_best(size_t size) const noexcept
{
    return nullptr;
}

void *allocator_boundary_tags::get_worst(size_t size) const noexcept
{
    return nullptr;
}

size_t allocator_boundary_tags::get_occupied_size(void *block_start) const noexcept
{
    return *reinterpret_cast<size_t*>(block_start);
}

void *allocator_boundary_tags::get_previous_from_occupied(void *block_start) const noexcept
{
    auto byte_ptr = reinterpret_cast<std::byte*>(_trusted_memory);

    return reinterpret_cast<void*>(byte_ptr + sizeof(size_t));
}

void *allocator_boundary_tags::get_next_from_occupied(void *block_start) const noexcept
{
    auto byte_ptr = reinterpret_cast<std::byte*>(_trusted_memory);

    return reinterpret_cast<void*>(byte_ptr + sizeof(size_t) + sizeof(void*));
}

void *allocator_boundary_tags::get_parent_from_occupied(void *block_start) const noexcept
{
    auto byte_ptr = reinterpret_cast<std::byte*>(_trusted_memory);

    return reinterpret_cast<void*>(byte_ptr + sizeof(size_t) + sizeof(void*) + sizeof(void*));
}

size_t allocator_boundary_tags::get_next_free_size(void *occupied_block_start) const noexcept
{
    return 0;
}

void **allocator_boundary_tags::get_first_block_ptr() const noexcept
{
    auto byte_ptr = reinterpret_cast<std::byte*>(_trusted_memory);

    return reinterpret_cast<void**>(byte_ptr + sizeof(logger*) + sizeof(allocator*) + sizeof(fit_mode) + sizeof(size_t) + sizeof(std::mutex));
}

size_t allocator_boundary_tags::get_free_size() const noexcept
{
    return 0;
}
