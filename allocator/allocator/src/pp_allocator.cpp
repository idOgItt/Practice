//
// Created by Des Caldnd on 6/29/2024.
//

#include "pp_allocator.h"


void smart_mem_resource::do_deallocate(void* p, size_t, size_t)
{
    do_deallocate_sm(p);
}

void* test_mem_resource::do_allocate(size_t n, size_t al)
{
return ::operator new(n, std::align_val_t(al));
}

void test_mem_resource::do_deallocate_sm(void* p)
{
::operator delete(p);
}

bool test_mem_resource::do_is_equal(const std::pmr::memory_resource& other) const noexcept
{
auto p = dynamic_cast<const test_mem_resource*>(&other);

return p != nullptr;
}
