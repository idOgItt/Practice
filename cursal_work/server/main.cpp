//
// Created by Des Caldnd on 6/2/2024.
//
#define BOOST_THREAD_PROVIDES_FUTURE
#define BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION

#include <boost/thread/future.hpp>

int main()
{
    auto c = boost::async(boost::launch::async, [](){ return 0; });

}