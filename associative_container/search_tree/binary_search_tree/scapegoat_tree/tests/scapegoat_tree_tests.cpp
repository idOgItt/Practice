#include "gtest/gtest.h"
#include <scapegoat_tree.h>
#include <associative_container.h>
#include <logger_builder.h>
#include <client_logger_builder.h>
#include <iostream>


logger *create_logger(
        std::vector<std::pair<std::string, logger::severity>> const &output_file_streams_setup,
        bool use_console_stream = true,
        logger::severity console_stream_severity = logger::severity::debug)
{
    std::unique_ptr<logger_builder> builder(new client_logger_builder());

    builder->set_format("[%d %t][%s] %m");

    if (use_console_stream)
    {
        builder->add_console_stream(console_stream_severity);
    }

    for (auto &output_file_stream_setup: output_file_streams_setup)
    {
        builder->add_file_stream(output_file_stream_setup.first, output_file_stream_setup.second);
    }

    logger *built_logger = builder->build();


    return built_logger;
}

bool compare_results(
        std::vector<typename binary_search_tree<int, std::string>::value_type> &expected,
        std::vector<typename binary_search_tree<int, std::string>::value_type> &actual)
{

    if (expected.size() != actual.size())
    {
        return false;
    }

    for (auto&& val : std::views::zip(expected, actual))
    {
        if (val.first.first != val.second.first)
        {
            return false;
        }

        if (val.first.second != val.second.second)
        {
            return false;
        }
    }

    return true;
}

template<typename tkey, typename tvalue>
struct test_data
{
    tkey key;
    tvalue value;
    size_t depth, height;

    test_data(size_t dep, tkey k, tvalue v, size_t h) : depth(dep), key(k), value(v), height(h) {}
};

template<
    typename tkey,
    typename tvalue>
bool infix_iterator_test(
    scapegoat_tree<tkey, tvalue> const &tree,
    std::vector<typename scapegoat_tree<tkey, tvalue>::iterator_data> &expected_result)
{
    
    std::string line;
    auto end_infix = tree.cend_infix();
    auto it = tree.cbegin_infix();
    
    for (auto const &item: expected_result)
    {
        if (it.depth() != item.depth || it->first != item.key || it->second != item.value)
        {
            return false;
        }
        ++it;
    }
    return true;
}

template<
    typename tkey,
    typename tvalue>
bool prefix_iterator_test(
    scapegoat_tree<tkey, tvalue> const &tree,
    std::vector<typename scapegoat_tree<tkey, tvalue>::iterator_data> &expected_result)
{
    std::string line;
    auto end_prefix = tree.cend_prefix();
    auto it = tree.cbegin_prefix();
    
    for (auto const &item: expected_result)
    {
        if (it.depth() != item.depth || it->first != item.key || it->second != item.value)
        {
            return false;
        }
        ++it;
    }
    return true;
}

template<
    typename tkey,
    typename tvalue>
bool postfix_iterator_test(
    scapegoat_tree<tkey, tvalue> const &tree,
    std::vector<typename scapegoat_tree<tkey, tvalue>::iterator_data> &expected_result)
{
    
    std::string line;
    auto end_postfix = tree.cend_postfix();
    auto it = tree.cbegin_postfix();
    
    for (auto const &item: expected_result)
    {
        if (it.depth() != item.depth || it->first != item.key || it->second != item.value)
        {
            return false;
        }
        ++it;
    }
    return true;
}

TEST(scapegoatTreePositiveTests, test1)
{
    std::unique_ptr<logger> logger(create_logger(std::vector<std::pair<std::string, logger::severity>>
        {
            {
                "scapegoat_tree_tests_logs.txt",
                logger::severity::trace
            },
        }));
    
    logger->trace("scapegoatTreePositiveTests.test1 started");
    
    auto sg = std::make_unique<scapegoat_tree<int, std::string>>(std::less<int>(), nullptr, logger.get(), 0.7);
    
    sg->insert(5, "a");
    sg->insert(2, "b");
    sg->insert(15, "c");
    sg->insert(3, "d");
    sg->insert(14, "e");
    sg->insert(1, "l");
    
    std::vector<typename scapegoat_tree<int, std::string>::iterator_data> expected_result =
        {
            scapegoat_tree<int, std::string>::iterator_data(2, 1, "l"),
            scapegoat_tree<int, std::string>::iterator_data(1, 2, "b"),
            scapegoat_tree<int, std::string>::iterator_data(2, 3, "d"),
            scapegoat_tree<int, std::string>::iterator_data(0, 5, "a"),
            scapegoat_tree<int, std::string>::iterator_data(2, 14, "e"),
            scapegoat_tree<int, std::string>::iterator_data(1, 15, "c")
        };
    
    EXPECT_TRUE(infix_iterator_test(*reinterpret_cast<scapegoat_tree<int, std::string> *>(sg), expected_result));
    
    logger->trace("scapegoatTreePositiveTests.test1 finished");
}

TEST(scapegoatTreePositiveTests, test2)
{
    std::unique_ptr<logger> logger(create_logger(std::vector<std::pair<std::string, logger::severity>>
                                                         {
                                                                 {
                                                                         "scapegoat_tree_tests_logs.txt",
                                                                         logger::severity::trace
                                                                 },
                                                         }));
    
    logger->trace("scapegoatTreePositiveTests.test2 started");

    auto sg = std::make_unique<scapegoat_tree<int, int>>(std::less<int>(), nullptr, logger.get(), 0.5);
    
    sg->insert(1, 5);
    sg->insert(2, 12);
    sg->insert(15, 1);
    sg->insert(3, 67);
    sg->insert(4, 45);
    
    std::vector<typename scapegoat_tree<int, int>::iterator_data> expected_result =
        {
            scapegoat_tree<int, int>::iterator_data(0, 3, 67),
            scapegoat_tree<int, int>::iterator_data(1, 2, 12),
            scapegoat_tree<int, int>::iterator_data(2, 1, 5),
            scapegoat_tree<int, int>::iterator_data(1, 15, 1),
            scapegoat_tree<int, int>::iterator_data(2, 4, 45)
        };
    
    EXPECT_TRUE(prefix_iterator_test(*reinterpret_cast<scapegoat_tree<int, int> *>(sg), expected_result));
    
    logger->trace("scapegoatTreePositiveTests.test2 finished");
}

TEST(scapegoatTreePositiveTests, test3)
{
    std::unique_ptr<logger> logger(create_logger(std::vector<std::pair<std::string, logger::severity>>
                                                         {
                                                                 {
                                                                         "scapegoat_tree_tests_logs.txt",
                                                                         logger::severity::trace
                                                                 },
                                                         }));
    
    logger->trace("scapegoatTreePositiveTests.test3 started");

    auto sg = std::make_unique<scapegoat_tree<std::string, int>>(std::less<std::string>(), nullptr, logger.get(), 0.9);
    
    sg->insert("a", 1);
    sg->insert("b", 2);
    sg->insert("c", 15);
    sg->insert("d", 3);
    sg->insert("e", 4);
    
    std::vector<typename scapegoat_tree<std::string, int>::iterator_data> expected_result =
        {
            scapegoat_tree<std::string, int>::iterator_data(4, "e", 4),
            scapegoat_tree<std::string, int>::iterator_data(3, "d", 3),
            scapegoat_tree<std::string, int>::iterator_data(2, "c", 15),
            scapegoat_tree<std::string, int>::iterator_data(1, "b", 2),
            scapegoat_tree<std::string, int>::iterator_data(0, "a", 1)
        };
    
    EXPECT_TRUE(postfix_iterator_test(*reinterpret_cast<scapegoat_tree<std::string, int> *>(sg), expected_result));
    
    logger->trace("scapegoatTreePositiveTests.test3 finished");
}

TEST(scapegoatTreePositiveTests, test4)
{
    std::unique_ptr<logger> logger(create_logger(std::vector<std::pair<std::string, logger::severity>>
                                                         {
                                                                 {
                                                                         "scapegoat_tree_tests_logs.txt",
                                                                         logger::severity::trace
                                                                 },
                                                         }));
    
    logger->trace("scapegoatTreePositiveTests.test4 started");

    auto sg = std::make_unique<scapegoat_tree<int, std::string>>(std::less<int>(), nullptr, logger.get(), 0.65);
    
    sg1->insert(6, "a");
    sg1->insert(8, "c");
    sg1->insert(15, "x");
    sg1->insert(4, "j");
    sg1->insert(1, "i");
    sg1->insert(5, "b");
    
    std::vector<typename scapegoat_tree<int, std::string>::iterator_data> expected_result =
        {
            scapegoat_tree<int, std::string>::iterator_data(2, 1, "i"),
            scapegoat_tree<int, std::string>::iterator_data(1, 4, "j"),
            scapegoat_tree<int, std::string>::iterator_data(2, 5, "b"),
            scapegoat_tree<int, std::string>::iterator_data(0, 6, "a"),
            scapegoat_tree<int, std::string>::iterator_data(2, 8, "c"),
            scapegoat_tree<int, std::string>::iterator_data(1, 15, "x"),
        };
    
    scapegoat_tree<int, std::string> sg2(std::move(*reinterpret_cast<scapegoat_tree<int, std::string> *>(sg1)));
    
    EXPECT_TRUE(infix_iterator_test(sg2, expected_result));
    
    logger->trace("scapegoatTreePositiveTests.test4 finished");
}

TEST(scapegoatTreePositiveTests, test5)
{
    std::unique_ptr<logger> logger(create_logger(std::vector<std::pair<std::string, logger::severity>>
                                                         {
                                                                 {
                                                                         "scapegoat_tree_tests_logs.txt",
                                                                         logger::severity::trace
                                                                 },
                                                         }));
    
    logger->trace("scapegoatTreePositiveTests.test5 started");

    auto sg = std::make_unique<scapegoat_tree<int, std::string>>(std::less<int>(), nullptr, logger.get(), 0.65);
    
    sg1->insert(6, "a");
    sg1->insert(8, "c");
    sg1->insert(15, "x");
    sg1->insert(4, "j");
    sg1->insert(1, "i");
    sg1->insert(5, "b");
    
    std::vector<typename scapegoat_tree<int, std::string>::iterator_data> expected_result =
        {
            scapegoat_tree<int, std::string>::iterator_data(2, 1, "i"),
            scapegoat_tree<int, std::string>::iterator_data(1, 4, "j"),
            scapegoat_tree<int, std::string>::iterator_data(2, 5, "b"),
            scapegoat_tree<int, std::string>::iterator_data(0, 6, "a"),
            scapegoat_tree<int, std::string>::iterator_data(2, 8, "c"),
            scapegoat_tree<int, std::string>::iterator_data(1, 15, "x"),
        };
    
    scapegoat_tree<int, std::string> sg2 = std::move(
        *reinterpret_cast<scapegoat_tree<int, std::string> *>(sg1));
    
    EXPECT_TRUE(infix_iterator_test(sg2, expected_result));
    
    logger->trace("scapegoatTreePositiveTests.test5 finished");
}

TEST(scapegoatTreePositiveTests, test6)
{
    std::unique_ptr<logger> logger(create_logger(std::vector<std::pair<std::string, logger::severity>>
                                                         {
                                                                 {
                                                                         "scapegoat_tree_tests_logs.txt",
                                                                         logger::severity::trace
                                                                 },
                                                         }));
    
    logger->trace("scapegoatTreePositiveTests.test6 started");

    auto sg = std::make_unique<scapegoat_tree<int, std::string>>(std::less<int>(), nullptr, logger.get(), 0.5);
    
    sg1->insert(6, "a");
    sg1->insert(8, "c");
    sg1->insert(15, "x");
    sg1->insert(4, "j");
    sg1->insert(1, "i");
    sg1->insert(5, "b");
    
    sg1->dispose(5);
    
    std::vector<typename scapegoat_tree<int, std::string>::iterator_data> expected_result =
        {
            scapegoat_tree<int, std::string>::iterator_data(2, 1, "i"),
            scapegoat_tree<int, std::string>::iterator_data(1, 4, "j"),
            scapegoat_tree<int, std::string>::iterator_data(0, 6, "a"),
            scapegoat_tree<int, std::string>::iterator_data(2, 8, "c"),
            scapegoat_tree<int, std::string>::iterator_data(1, 15, "x"),
        };
    
    EXPECT_TRUE(infix_iterator_test(*reinterpret_cast<scapegoat_tree<int, std::string> *>(sg1), expected_result));
    
    logger->trace("scapegoatTreePositiveTests.test6 finished");
}

TEST(scapegoatTreePositiveTests, test7)
{
    std::unique_ptr<logger> logger(create_logger(std::vector<std::pair<std::string, logger::severity>>
                                                         {
                                                                 {
                                                                         "scapegoat_tree_tests_logs.txt",
                                                                         logger::severity::trace
                                                                 },
                                                         }));
    
    logger->trace("scapegoatTreePositiveTests.test7 started");

    auto sg = std::make_unique<scapegoat_tree<int, std::string>>(std::less<int>(), nullptr, logger.get(), 0.7);
    
    sg1->insert(6, "a");
    sg1->insert(8, "c");
    sg1->insert(15, "x");
    sg1->insert(4, "j");
    sg1->insert(3, "i");
    sg1->insert(2, "l");
    sg1->insert(5, "b");
    
    sg1->dispose(3);
    
    std::vector<typename scapegoat_tree<int, std::string>::iterator_data> expected_result =
        {
            scapegoat_tree<int, std::string>::iterator_data(2, 2, "l"),
            scapegoat_tree<int, std::string>::iterator_data(1, 4, "j"),
            scapegoat_tree<int, std::string>::iterator_data(2, 5, "b"),
            scapegoat_tree<int, std::string>::iterator_data(0, 6, "a"),
            scapegoat_tree<int, std::string>::iterator_data(1, 8, "c"),
            scapegoat_tree<int, std::string>::iterator_data(2, 15, "x"),
        };
    
    EXPECT_TRUE(infix_iterator_test(*reinterpret_cast<scapegoat_tree<int, std::string> *>(sg1), expected_result));
    
    logger->trace("scapegoatTreePositiveTests.test7 finished");
}

TEST(scapegoatTreePositiveTests, test8)
{
    std::unique_ptr<logger> logger(create_logger(std::vector<std::pair<std::string, logger::severity>>
                                                         {
                                                                 {
                                                                         "scapegoat_tree_tests_logs.txt",
                                                                         logger::severity::trace
                                                                 },
                                                         }));
    
    logger->trace("scapegoatTreePositiveTests.test8 started");

    auto sg = std::make_unique<scapegoat_tree<int, std::string>>(std::less<int>(), nullptr, logger.get(), 0.7);
    
    sg1->insert(6, "a");
    sg1->insert(8, "c");
    sg1->insert(15, "x");
    sg1->insert(11, "j");
    sg1->insert(19, "i");
    sg1->insert(12, "l");
    sg1->insert(17, "b");
    sg1->insert(18, "e");
    
    sg1->dispose(12);
    sg1->dispose(15);
    
    std::vector<typename scapegoat_tree<int, std::string>::iterator_data> expected_result =
        {
            scapegoat_tree<int, std::string>::iterator_data(2, 6, "a"),
            scapegoat_tree<int, std::string>::iterator_data(1, 8, "c"),
            scapegoat_tree<int, std::string>::iterator_data(0, 11, "j"),
            scapegoat_tree<int, std::string>::iterator_data(2, 17, "b"),
            scapegoat_tree<int, std::string>::iterator_data(1, 18, "e"),
            scapegoat_tree<int, std::string>::iterator_data(2, 19, "i"),
        };
    
    EXPECT_TRUE(infix_iterator_test(*reinterpret_cast<scapegoat_tree<int, std::string> *>(sg1), expected_result));
    
    logger->trace("scapegoatTreePositiveTests.test8 finished");
}

TEST(scapegoatTreePositiveTests, test9)
{
    std::unique_ptr<logger> logger(create_logger(std::vector<std::pair<std::string, logger::severity>>
                                                         {
                                                                 {
                                                                         "scapegoat_tree_tests_logs.txt",
                                                                         logger::severity::trace
                                                                 },
                                                         }));
    
    logger->trace("scapegoatTreePositiveTests.test9 started");

    auto sg = std::make_unique<scapegoat_tree<int, std::string>>(std::less<int>(), nullptr, logger.get(), 0.7);
    
    sg1->insert(6, "l");
    sg1->insert(8, "c");
    sg1->insert(15, "l");
    sg1->insert(11, "o");
    sg1->insert(9, "h");
    sg1->insert(2, "e");
    sg1->insert(4, "b");
    sg1->insert(18, "e");
    
    std::vector<std::string> vector;
    
    vector.push_back(sg1->obtain(9));
    vector.push_back(sg1->obtain(2));
    vector.push_back(sg1->obtain(15));
    vector.push_back(sg1->obtain(6));
    vector.push_back(sg1->obtain(11));
    
    std::string actual_result;
    
    for (auto const &item: vector)
    {
        actual_result.append(item + " ");
    }
    
    EXPECT_EQ(actual_result, "h e l l o ");
    
    logger->trace("scapegoatTreePositiveTests.test9 finished");
}

TEST(scapegoatTreePositiveTests, test10)
{
    std::unique_ptr<logger> logger(create_logger(std::vector<std::pair<std::string, logger::severity>>
                                                         {
                                                                 {
                                                                         "scapegoat_tree_tests_logs.txt",
                                                                         logger::severity::trace
                                                                 },
                                                         }));
    
    logger->trace("scapegoatTreePositiveTests.test10 started");

    auto sg = std::make_unique<scapegoat_tree<int, std::string>>(std::less<int>(), nullptr, logger.get(), 0.7);
    
    sg->insert(6, "l");
    sg->insert(8, "c");
    sg->insert(15, "l");
    sg->insert(11, "o");
    sg->insert(9, "h");
    sg->insert(2, "e");
    sg->insert(4, "b");
    sg->insert(18, "e");
    
    std::vector<associative_container<int, std::string>::key_value_pair> actual_result = sg->obtain_between(2, 10, true, false);
    
    std::vector<associative_container<int, std::string>::key_value_pair> expected_result =
        {
            { 2, "e" },
            { 4, "b" },
            { 6, "l" },
            { 8, "c" },
            { 9, "h" }
        };
    
    EXPECT_TRUE(compare_results(expected_result, actual_result));
    
    logger->trace("scapegoatTreePositiveTests.test10 finished");
}

int main(
    int argc,
    char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();
}