#include <not_implemented.h>

#include "../include/allocator_global_heap.h"

allocator_global_heap::allocator_global_heap(
    logger *logger) : _logger(logger){
    debug_with_guard("Global heap allocator constructed");
}

[[nodiscard]] void *allocator_global_heap::allocate(
    size_t value_size,
    size_t values_count)
{
    size_t result_size = value_size * values_count + size_t_size;
    debug_with_guard("Global heap allocator started allocating " + std::to_string(result_size) + " bytes");

    void* res;

    try
    {
        res = ::operator new(result_size);
    } catch (std::bad_alloc& e)
    {
        error_with_guard("Bad alloc thrown in global_heap_allocator while trying allocate " + std::to_string(result_size) + " bytes");

        throw;
    }

    *reinterpret_cast<size_t*>(res) = values_count * value_size;

    debug_with_guard("Global heap allocator finished allocating " + std::to_string(result_size) + " bytes");
    return reinterpret_cast<size_t*>(res) + 1;
}

void allocator_global_heap::deallocate(
    void *at)
{
    debug_with_guard("Global heap allocator started deallocating " + std::to_string((unsigned long long)at));
    std::string dump = get_dump(reinterpret_cast<char*>(at), *(reinterpret_cast<size_t*>(at) - 1));

    debug_with_guard(dump);

    ::delete (reinterpret_cast<size_t*>(at) - 1);
    debug_with_guard("Global heap allocator finished deallocating " + std::to_string((unsigned long long)at));
}

inline logger *allocator_global_heap::get_logger() const
{
    return _logger;
}

inline std::string allocator_global_heap::get_typename() const noexcept
{
    return "allocator_global_heap";
}

std::string allocator_global_heap::get_dump(char *data, size_t size)
{
    trace_with_guard("Global heap allocator started get_dump");

    std::string res;

    if (size > 0)
    {
        res.reserve(size * 3);

        res += dump_byte(data[0]);

        for (size_t i = 1; i < size; ++i)
        {
            res += " " + dump_byte(data[i]);
        }
    }

    trace_with_guard("Global heap allocator finished get_dump");
    return res;
}

std::string allocator_global_heap::dump_byte(char byte)
{
    std::string res;

    constexpr const char left_mask = 0u | (1u << 7) | (1u << 6) | (1u << 5) | (1u << 4);
    constexpr const char right_mask = 0u | (1u << 3) | (1u << 2) | (1u << 1) | (1u);

    res.push_back(int_to_char(byte & left_mask));
    res.push_back(int_to_char(byte & right_mask));

    return res;
}

char allocator_global_heap::int_to_char(int val)
{
    if (val < 10)
        return '0' + val;
    else
        return 'A' + val;
}
