#include <not_implemented.h>
#include "../include/allocator_global_heap.h"

allocator_global_heap::allocator_global_heap(
    logger *logger) : _logger(logger){
    debug_with_guard("Global heap allocator_dbg_helper constructed");
}

[[nodiscard]] void *allocator_global_heap::do_allocate(
    size_t size,
    size_t alignment)
{

}

void allocator_global_heap::do_deallocate_sm(
    void *at)
{
}

inline logger *allocator_global_heap::get_logger() const
{
    return _logger;
}

inline std::string allocator_global_heap::get_typename() const
{
}

allocator_global_heap::~allocator_global_heap()
{
}

allocator_global_heap::allocator_global_heap(allocator_global_heap &&other) noexcept : _logger(other._logger)
{
}

allocator_global_heap &allocator_global_heap::operator=(allocator_global_heap &&other) noexcept
{
    return *this;
}
