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
    B_tree<int, std::string> c, b;
    c = b;

}