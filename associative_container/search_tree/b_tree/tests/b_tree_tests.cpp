//
// Created by Des Caldnd on 4/12/2024.
//
#include "gtest/gtest.h"
#include <b_tree.h>
#include <string>
#include <allocator_sorted_list.h>
#include <memory>
#include <map>
#include <unordered_map>
#include <client_logger_builder.h>
#include <client_logger.h>
#include <functional>

struct greater_comparator
{
	bool operator()(int lhs, int rhs) const
	{
		return lhs > rhs;
	}
};

logger *create_logger(
	std::vector<std::pair<std::string, logger::severity>> const &output_file_streams_setup,
	bool use_console_stream = true,
	logger::severity console_stream_severity = logger::severity::debug)
{
	logger_builder *builder = new client_logger_builder();

	builder->set_format("[%t %d][%s] %m");

	for (auto &output_file_stream_setup: output_file_streams_setup)
	{
		builder->add_file_stream(output_file_stream_setup.first, output_file_stream_setup.second);
		builder->add_console_stream(output_file_stream_setup.second);
	}

	logger *built_logger = builder->build();

	delete builder;

	return built_logger;
}

TEST(BTreePositiveTests, test1)
{
	B_tree<int, double, std::less<int>, 2> d;

	for (int i = 0; i < 20; ++i)
	{
		d.insert(std::make_pair(i, double(i)));
	}

	for(int i = 0; i < 13; ++i)
	{
		d.erase(i);
	}

	for (size_t i = 13; i < 20; ++i)
	{
		std::cout << d.at(i) << std::endl;
	}
}

TEST(BTreePositiveTests, test2)
{
	B_tree<int, int, std::less<int>, 2> tree;
	std::unordered_map<int, int> map;

	size_t iterations = 100'000;

	srand(time(nullptr));

	for(size_t i = 0; i < iterations; ++i)
	{
		switch(rand() % 3)
		{
			case 0:
			case 1:
			{
				int tmp = rand();
				try
				{

					if (map.find(tmp) == map.end())
					{
						map.insert(std::make_pair(tmp, 1));
						tree.emplace(tmp, 1);
					}
				} catch (std::logic_error& er)
				{
					std::cout << er.what() << std::endl;
				}
				break;
			}
//			case 2:
//			{
//				if (!map.empty())
//				{
//					auto it = map.begin();
//
//					tree.erase(it->first);
//					map.erase(it);
//				} else
//				{
//					std::cout << "Empty" << std::endl;
//				}
//				break;
//			}
		}
	}

//	while(!map.empty())
//	{
//		auto it = map.begin();
//
//		tree.erase(it->first);
//		map.erase(it);
//	}
}

TEST(BTreePositiveTests, test3)
{
	logger *logger_instance = create_logger(std::vector<std::pair<std::string, logger::severity>>
												{
													{
														"allocator_boundary_tags_tests_logs_false_positive_test_1.txt",
														logger::severity::information
													},
													{
														"allocator_boundary_tags_tests_logs_false_positive_test_1.txt",
														logger::severity::debug
													},
													{
														"allocator_boundary_tags_tests_logs_false_positive_test_1.txt",
														logger::severity::trace
													},
													{
														"allocator_boundary_tags_tests_logs_false_positive_test_1.txt",
														logger::severity::critical
													},
													{
														"allocator_boundary_tags_tests_logs_false_positive_test_1.txt",
														logger::severity::warning
													},
													{
														"allocator_boundary_tags_tests_logs_false_positive_test_1.txt",
														logger::severity::error
													}
												});

	B_tree<int, int> tree(std::less<int>(), nullptr, logger_instance);
	std::unordered_map<int, int> map;

	size_t iterations = 100'000;
	size_t res = 0;

	srand(time(nullptr));

	for(size_t i = 0; i < iterations; ++i)
	{
		switch(rand() % 3)
		{
			case 0:
			case 1:
			{
				int tmp = rand();
				try
				{

					if (map.find(tmp) == map.end())
					{
						map.insert(std::make_pair(tmp, 1));
						tree.insert(std::make_pair(tmp, 1));
						++res;
						tree.at(tmp);
					}
				} catch (std::logic_error& er)
				{
					std::cout << er.what() << std::endl;
				}
				break;
			}
			case 2:
			{
				if (!map.empty())
				{
					auto it = map.begin();

					//std::advance(it, rand() % map.size());

					tree.at(it->first);
					tree.erase(it->first);
					map.erase(it);
					--res;
				} else
				{
					std::cout << "Empty" << std::endl;
				}
			}
				break;
		}

		EXPECT_EQ(tree.size(), map.size());
	}

	EXPECT_EQ(tree.size(), map.size());

	while(!map.empty())
	{
		auto it = map.begin();
		//std::advance(it, rand() % map.size());

		tree.erase(it->first);
		map.erase(it);

		EXPECT_EQ(tree.size(), map.size());
	}

	EXPECT_EQ(tree.size(), 0);
	delete logger_instance;
}

TEST(BTreePositiveTests, test4)
{
	B_tree<int, int, std::less<int>, 20> tree;
	std::unordered_map<int, int> map;

	size_t iterations = 100'000;

	srand(time(nullptr));

	for(size_t i = 0; i < iterations; ++i)
	{
		switch(rand() % 3)
		{
			case 0:
			case 1:
			{
				int tmp = rand();
				try
				{

					if (map.find(tmp) == map.end())
					{
						map.insert(std::make_pair(tmp, 1));
						tree.emplace(tmp, 1);
					}
				} catch (std::logic_error& er)
				{
					std::cout << er.what() << std::endl;
				}
				break;
			}
			case 2:
			{
				if (!map.empty())
				{
					auto it = map.begin();

					//std::advance(it, rand() % map.size());

					tree.erase(it->first);
					map.erase(it);
				} else
				{
					std::cout << "Empty" << std::endl;
				}
			}
				break;
		}
	}

	EXPECT_EQ(tree.size(), map.size());

	while(!map.empty())
	{
		auto it = map.begin();
		//std::advance(it, rand() % map.size());

		tree.erase(it->first);
		map.erase(it);
	}
	EXPECT_EQ(tree.size(), 0);
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();

}