//
// Created by Des Caldnd on 4/12/2024.
//
#include "gtest/gtest.h"
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

TEST(BTreePositiveTests, test1)
{
	B_tree<int, double, std::less<int>, 2> d;

	for (int i = 0; i < 20; ++i)
	{
		d.insert(std::make_pair(i, double(i)));
	}

	for (auto el : d)
	{
		std::cout << el.first << " " << el.second << std::endl;
	}
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();

}