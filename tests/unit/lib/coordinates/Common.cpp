
#include "Common.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge {

TEST_P(RelativeCoordinates, Test)
{
  const auto param = GetParam();

  const auto viewport = param.generator();
  ASSERT_NE(nullptr, viewport);

  auto p = viewport->relativeCoords(param.coords.x, param.coords.y);

  EXPECT_FLOAT_EQ(param.expected.x, p.x);
  EXPECT_FLOAT_EQ(param.expected.y, p.y);
}

TEST_P(AbsoluteCoordinates, Test)
{
  const auto param = GetParam();

  const auto viewport = param.generator();
  ASSERT_NE(nullptr, viewport);

  auto p = viewport->absoluteCoords(param.coords.x, param.coords.y);

  EXPECT_FLOAT_EQ(param.expected.x, p.x);
  EXPECT_FLOAT_EQ(param.expected.y, p.y);
}

auto generateTestNameRelative(const TestParamInfo<TestCaseRelative> &info) -> std::string
{
  return info.param.name;
}

auto generateTestNameAbsolute(const TestParamInfo<TestCaseAbsolute> &info) -> std::string
{
  return info.param.name;
}

} // namespace pge