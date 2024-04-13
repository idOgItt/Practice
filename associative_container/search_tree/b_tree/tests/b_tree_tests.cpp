//
// Created by Des Caldnd on 4/12/2024.
//
#include <b_tree.h>
#include <string>
#include <allocator_sorted_list.h>
#include <memory>
#include <map>
#include <functional>

struct greater_comparator
{
	bool operator()(int lhs, int rhs) const
	{
		return lhs > rhs;
	}
};

int main()
{
	std::unique_ptr<allocator> _allocate(new allocator_sorted_list(10000));

	std::map<int, std::string, greater_comparator> map;

    B_tree<int, std::string, greater_comparator, 15> c;


}