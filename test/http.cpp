#include <limits.h>
#include <gtest/gtest.h>
#include "HttpRequest.hpp"

#include <map>

using namespace std;

TEST(HttpRequest, HttpRequestTest) {
    map<string, string> parsed = HttpRequest::parseParams("A=1&B=2");
    ASSERT_EQ(0, 0);
}
