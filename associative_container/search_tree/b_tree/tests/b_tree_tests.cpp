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
	std::pair<int, double> a, b;
	a = b;

	std::vector<std::pair<int, std::string>> v;
    B_tree c(v.begin(), v.end());

	auto it = c.begin();

	auto d = it->first;

}