#include <gtest/gtest.h>
#include "YggCpp/LSys.hpp"

TEST(LSysTest, BasicRule) {
    Ygg::LSysData props = {
        "F+F",
        {"F=F+F"},
        2
    };
    Ygg::LSys lsys;
    std::string result = lsys.generateExpression(props);
    EXPECT_STREQ(result.c_str(), "F+F+F+F+F+F+F+F");
}

TEST(LSysTest, MultipleRules) {
    Ygg::LSysData props = {
            "F+G",
            {
                "F=F+F",
                "G=F-F"
             },
            2
    };
    Ygg::LSys lsys;
    std::string result = lsys.generateExpression(props);
    EXPECT_STREQ(result.c_str(), "F+F+F+F+F+F-F+F");
}