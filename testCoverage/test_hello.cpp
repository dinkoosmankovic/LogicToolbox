
#include <gtest/gtest.h>

#include "test/hello.h"

TEST(Hello, get_message)
{
    std::string m = get_message();
    ASSERT_EQ("Hello, World!", m);
}

TEST(Hello, get_message1)
{
    std::string m = get_message1();
    ASSERT_EQ("Hello, World!", m);
}
