
# include "TopLeftViewport.hh"
# include <gtest/gtest.h>

using namespace ::testing;

namespace pge {
namespace {
const olc::vi2d TOP_LEFT{-12, 5};
const olc::vi2d DIMS{4, 15};

auto generateTopLeftViewportI() -> TopLeftViewportI {
  return TopLeftViewportI(TOP_LEFT, DIMS);
}
}

TEST(Unit_Coordinates_TopLeftViewport, Test_Constructor)
{
  const auto tlv = generateTopLeftViewportI();

  EXPECT_EQ(tlv.topLeft(), TOP_LEFT);
  const auto center = TOP_LEFT + DIMS / 2;
  EXPECT_EQ(tlv.center(), center);
  EXPECT_EQ(tlv.dims(), DIMS);
}

struct TestCase {
  std::string name;
  olc::vi2d coords;
  olc::vf2d expected;
};
using CoordsTestCase = TestWithParam<TestCase>;

TEST_P(CoordsTestCase, Test)
{
  const auto tlv = generateTopLeftViewportI();
  const auto param = GetParam();
  auto p = tlv.relativeCoords(param.coords.x, param.coords.y);
  EXPECT_FLOAT_EQ(param.expected.x, p.x);
  EXPECT_FLOAT_EQ(param.expected.y, p.y);
}

INSTANTIATE_TEST_CASE_P(
  Unit_Coordinates_TopLeftViewport_RelativeCoordinates_Bounds,
  CoordsTestCase,
  Values(
    TestCase{"top_left", {-12, 5}, {0.0f, 0.0f}},
    TestCase{"top_right", {-8, 5}, {1.0f, 0.0f}},
    TestCase{"bottom_right", {-8, 20}, {1.0f, 1.0f}},
    TestCase{"bottom_left", {-12, 20}, {0.0f, 1.0f}},
    TestCase{"inside", {-10, 14}, {0.5f, 0.6f}}
  ),
  [](const TestParamInfo<TestCase>& info) {
    return info.param.name;
  });

INSTANTIATE_TEST_CASE_P(
  Unit_Coordinates_TopLeftViewport_RelativeCoordinates_Inside,
  CoordsTestCase,
  Values(
    TestCase{"inside", {-10, 14}, {0.5f, 0.6f}}
  ),
  [](const TestParamInfo<TestCase>& info) {
    return info.param.name;
  });

INSTANTIATE_TEST_CASE_P(
  Unit_Coordinates_TopLeftViewport_RelativeCoordinates_Outside,
  CoordsTestCase,
  Values(
    TestCase{"x_too_small", {-14, 14}, {-0.5f, 0.6f}},
    TestCase{"x_too_large", {-6, 14}, {1.5f, 0.6f}},
    TestCase{"y_too_small", {-10, -4}, {0.5f, -0.6f}},
    TestCase{"y_too_large", {-10, 26}, {0.5f, 1.4f}}
  ),
  [](const TestParamInfo<TestCase>& info) {
    return info.param.name;
  });

}
