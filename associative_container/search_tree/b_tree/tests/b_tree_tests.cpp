//
// Created by Des Caldnd on 4/12/2024.
//
#include <b_tree.h>
#include <string>
#include <allocator_sorted_list.h>
#include <memory>

int main()
{
	std::unique_ptr<allocator> _allocate(new allocator_sorted_list(10000));

    B_tree<int, std::string> c({}, _allocate.get());


}