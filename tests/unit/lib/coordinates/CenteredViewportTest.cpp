
# include "CenteredViewport.hh"
# include "Common.hh"
# include <gtest/gtest.h>

using namespace ::testing;

namespace pge {
const olc::vi2d CENTER{-12, 5};
const olc::vi2d DIMS{4, 15};

auto generateCenteredViewportI() -> CenteredViewportI {
  return CenteredViewportI(CENTER, DIMS);
}

TEST(Unit_Coordinates_CenteredViewport, Test_Constructor)
{
  const auto tlv = generateCenteredViewportI();

  const auto topLeft = olc::vi2d(
    CENTER.x - DIMS.x / 2,
    CENTER.y + DIMS.y / 2
  );
  EXPECT_EQ(tlv.topLeft(), topLeft);
  EXPECT_EQ(tlv.center(), CENTER);
  EXPECT_EQ(tlv.dims(), DIMS);
}

using CenteredCoordsTestCase = TestWithParam<TestCase>;

TEST_P(CenteredCoordsTestCase, Test)
{
  const auto tlv = generateCenteredViewportI();
  const auto param = GetParam();
  auto p = tlv.relativeCoords(param.coords.x, param.coords.y);
  EXPECT_FLOAT_EQ(param.expected.x, p.x);
  EXPECT_FLOAT_EQ(param.expected.y, p.y);
}

INSTANTIATE_TEST_CASE_P(
  Unit_Coordinates_CenteredViewport_RelativeCoordinates_Bounds,
  CenteredCoordsTestCase,
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
  Unit_Coordinates_CenteredViewport_RelativeCoordinates_Inside,
  CenteredCoordsTestCase,
  Values(
    TestCase{"inside", {-10, 14}, {0.5f, 0.6f}}
  ),
  [](const TestParamInfo<TestCase>& info) {
    return info.param.name;
  });

INSTANTIATE_TEST_CASE_P(
  Unit_Coordinates_CenteredViewport_RelativeCoordinates_Outside,
  CenteredCoordsTestCase,
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
