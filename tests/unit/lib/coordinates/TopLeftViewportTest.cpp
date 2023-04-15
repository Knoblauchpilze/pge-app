
#include <gtest/gtest.h>

#include "Common.hh"
#include "TopLeftViewport.hh"

using namespace ::testing;

namespace pge {
const olc::vi2d TOP_LEFT{-12, 5};
const olc::vi2d DIMS{4, 15};

auto generateTopLeftViewportI() -> ViewportIPtr
{
  return std::make_shared<TopLeftViewportI>(TOP_LEFT, DIMS);
}

auto generateTopLeftTestCaseRelative(const std::string &name,
                                     const olc::vi2d &coords,
                                     const olc::vf2d &expected) -> TestCaseRelative
{
  return TestCaseRelative{name, generateTopLeftViewportI, coords, expected};
}

auto generateTopLeftTestCaseAbsolute(const std::string &name,
                                     const olc::vf2d &coords,
                                     const olc::vi2d &expected) -> TestCaseAbsolute
{
  return TestCaseAbsolute{name, generateTopLeftViewportI, coords, expected};
}

TEST(TopLeftViewport_Constructor, Test)
{
  const auto tlv = generateTopLeftViewportI();

  EXPECT_EQ(tlv->topLeft(), TOP_LEFT);
  const auto center = TOP_LEFT + DIMS / 2;
  EXPECT_EQ(tlv->center(), center);
  EXPECT_EQ(tlv->dims(), DIMS);
}

INSTANTIATE_TEST_CASE_P(
  TopLeftViewport_Bounds,
  RelativeCoordinates,
  Values(generateTopLeftTestCaseRelative("top_left", {-12, 5}, {0.0f, 0.0f}),
         generateTopLeftTestCaseRelative("top_right", {-8, 5}, {1.0f, 0.0f}),
         generateTopLeftTestCaseRelative("bottom_right", {-8, 20}, {1.0f, 1.0f}),
         generateTopLeftTestCaseRelative("bottom_left", {-12, 20}, {0.0f, 1.0f})),
  generateTestNameRelative);

INSTANTIATE_TEST_CASE_P(TopLeftViewport_Inside,
                        RelativeCoordinates,
                        Values(generateTopLeftTestCaseRelative("inside", {-10, 14}, {0.5f, 0.6f})),
                        generateTestNameRelative);

INSTANTIATE_TEST_CASE_P(
  TopLeftViewport_Outside,
  RelativeCoordinates,
  Values(generateTopLeftTestCaseRelative("x_too_small", {-14, 14}, {-0.5f, 0.6f}),
         generateTopLeftTestCaseRelative("x_too_large", {-6, 14}, {1.5f, 0.6f}),
         generateTopLeftTestCaseRelative("y_too_small", {-10, -4}, {0.5f, -0.6f}),
         generateTopLeftTestCaseRelative("y_too_large", {-10, 26}, {0.5f, 1.4f})),
  generateTestNameRelative);

INSTANTIATE_TEST_CASE_P(
  TopLeftViewport_Bounds,
  AbsoluteCoordinates,
  Values(generateTopLeftTestCaseAbsolute("top_left", {0.0f, 0.0f}, {-12, 5}),
         generateTopLeftTestCaseAbsolute("top_right", {1.0f, 0.0f}, {-8, 5}),
         generateTopLeftTestCaseAbsolute("bottom_right", {1.0f, 1.0f}, {-8, 20}),
         generateTopLeftTestCaseAbsolute("bottom_left", {0.0f, 1.0f}, {-12, 20})),
  generateTestNameAbsolute);

INSTANTIATE_TEST_CASE_P(TopLeftViewport_Inside,
                        AbsoluteCoordinates,
                        Values(generateTopLeftTestCaseAbsolute("inside", {0.5f, 0.6f}, {-10, 14})),
                        generateTestNameAbsolute);

INSTANTIATE_TEST_CASE_P(
  TopLeftViewport_Outside,
  AbsoluteCoordinates,
  Values(generateTopLeftTestCaseAbsolute("x_too_small", {-0.5f, 0.6f}, {-14, 14}),
         generateTopLeftTestCaseAbsolute("x_too_large", {1.5f, 0.6f}, {-6, 14}),
         generateTopLeftTestCaseAbsolute("y_too_small", {0.5f, -0.6f}, {-10, -4}),
         generateTopLeftTestCaseAbsolute("y_too_large", {0.5f, 1.4f}, {-10, 26})),
  generateTestNameAbsolute);

TEST(TopLeftViewport_MoveTo, Test)
{
  // virtual void
  // moveTo(const Vector& position) noexcept = 0;
}

} // namespace pge
