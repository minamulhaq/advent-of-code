#include "gtest/gtest.h"
#include <string>
#include <sstream>
#include <optional>
#include <utility>
#include "gift_shop.hpp"

class GiftShopTest : public ::testing::Test
{
protected:
    GiftShop gs; // constructed before each test

    void SetUp() override
    {
        // Optional: initialize state if needed
    }

    void TearDown() override
    {
        // Optional: cleanup
    }
};

TEST_F(GiftShopTest, RepeatedTwiceIsInvalid)
{
    EXPECT_TRUE(gs.is_invalid("11"));
    EXPECT_TRUE(gs.is_invalid("111"));
    EXPECT_TRUE(gs.is_invalid("55"));
    EXPECT_TRUE(gs.is_invalid("6464"));
    EXPECT_TRUE(gs.is_invalid("123123"));
    EXPECT_TRUE(gs.is_invalid("123123123"));
}
