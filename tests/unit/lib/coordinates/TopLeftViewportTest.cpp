
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

TEST(Unit_TopLeftViewport, Constructor)
{
  const auto viewport = generateTopLeftViewportI();

  EXPECT_EQ(viewport->topLeft(), TOP_LEFT);
  const auto center = TOP_LEFT + DIMS / 2;
  EXPECT_EQ(viewport->center(), center);
  EXPECT_EQ(viewport->dims(), DIMS);
}

INSTANTIATE_TEST_CASE_P(
  Unit_TopLeftViewport,
  RelativeCoordinates,
  Values(generateTopLeftTestCaseRelative("top_left", {-12, 5}, {0.0f, 0.0f}),
         generateTopLeftTestCaseRelative("top_right", {-8, 5}, {1.0f, 0.0f}),
         generateTopLeftTestCaseRelative("bottom_right", {-8, 20}, {1.0f, 1.0f}),
         generateTopLeftTestCaseRelative("bottom_left", {-12, 20}, {0.0f, 1.0f}),
         generateTopLeftTestCaseRelative("inside", {-10, 14}, {0.5f, 0.6f}),
         generateTopLeftTestCaseRelative("x_too_small", {-14, 14}, {-0.5f, 0.6f}),
         generateTopLeftTestCaseRelative("x_too_large", {-6, 14}, {1.5f, 0.6f}),
         generateTopLeftTestCaseRelative("y_too_small", {-10, -4}, {0.5f, -0.6f}),
         generateTopLeftTestCaseRelative("y_too_large", {-10, 26}, {0.5f, 1.4f})),
  generateTestNameRelative);

INSTANTIATE_TEST_CASE_P(
  Unit_TopLeftViewport,
  AbsoluteCoordinates,
  Values(generateTopLeftTestCaseAbsolute("top_left", {0.0f, 0.0f}, {-12, 5}),
         generateTopLeftTestCaseAbsolute("top_right", {1.0f, 0.0f}, {-8, 5}),
         generateTopLeftTestCaseAbsolute("bottom_right", {1.0f, 1.0f}, {-8, 20}),
         generateTopLeftTestCaseAbsolute("bottom_left", {0.0f, 1.0f}, {-12, 20}),
         generateTopLeftTestCaseAbsolute("inside", {0.5f, 0.6f}, {-10, 14}),
         generateTopLeftTestCaseAbsolute("x_too_small", {-0.5f, 0.6f}, {-14, 14}),
         generateTopLeftTestCaseAbsolute("x_too_large", {1.5f, 0.6f}, {-6, 14}),
         generateTopLeftTestCaseAbsolute("y_too_small", {0.5f, -0.6f}, {-10, -4}),
         generateTopLeftTestCaseAbsolute("y_too_large", {0.5f, 1.4f}, {-10, 26})),
  generateTestNameAbsolute);

TEST(Unit_TopLeftViewport, MoveTo)
{
  const auto viewport = generateTopLeftViewportI();

  const auto origin = olc::vi2d(2, 3);
  viewport->moveTo(origin);

  EXPECT_EQ(viewport->topLeft(), origin);
  const auto center = origin + DIMS / 2;
  EXPECT_EQ(viewport->center(), center);
  EXPECT_EQ(viewport->dims(), DIMS);
}

TEST(Unit_TopLeftViewport, Translate)
{
  const auto viewport = generateTopLeftViewportI();

  const auto delta = olc::vi2d(2, 3);
  viewport->translate(delta);

  const auto topLeft = TOP_LEFT + delta;
  EXPECT_EQ(viewport->topLeft(), topLeft);
  const auto center = topLeft + DIMS / 2;
  EXPECT_EQ(viewport->center(), center);
  EXPECT_EQ(viewport->dims(), DIMS);
}

TEST(Unit_TopLeftViewport, Scale)
{
  const auto viewport = generateTopLeftViewportI();

  const auto factor = 2;
  viewport->scale(factor, factor);

  EXPECT_EQ(viewport->topLeft(), TOP_LEFT);
  const auto center = TOP_LEFT + factor * DIMS / 2;
  EXPECT_EQ(viewport->center(), center);
  EXPECT_EQ(viewport->dims(), DIMS * factor);
}

} // namespace pge
