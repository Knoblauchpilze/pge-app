
#include "CenteredViewport.hh"
#include "Common.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge {
const olc::vi2d CENTER{-12, 5};
const olc::vi2d DIMS{4, 15};

auto generateCenteredViewportI() -> ViewportIPtr
{
  return std::make_shared<CenteredViewportI>(CENTER, DIMS);
}

auto generateCenteredTestCaseRelative(const std::string &name,
                                      const olc::vi2d &coords,
                                      const olc::vf2d &expected) -> TestCaseRelative
{
  return TestCaseRelative{name, generateCenteredViewportI, coords, expected};
}

auto generateCenteredTestCaseAbsolute(const std::string &name,
                                      const olc::vf2d &coords,
                                      const olc::vi2d &expected) -> TestCaseAbsolute
{
  return TestCaseAbsolute{name, generateCenteredViewportI, coords, expected};
}

TEST(Unit_CenteredViewport, Constructor)
{
  const auto viewport = generateCenteredViewportI();

  const auto topLeft = olc::vi2d(CENTER.x - DIMS.x / 2, CENTER.y + DIMS.y / 2);
  EXPECT_EQ(viewport->topLeft(), topLeft);
  EXPECT_EQ(viewport->center(), CENTER);
  EXPECT_EQ(viewport->dims(), DIMS);
}

INSTANTIATE_TEST_CASE_P(
  Unit_CenteredViewport,
  RelativeCoordinates,
  Values(generateCenteredTestCaseRelative("top_left", {-12, 5}, {0.0f, 0.0f}),
         generateCenteredTestCaseRelative("top_right", {-8, 5}, {1.0f, 0.0f}),
         generateCenteredTestCaseRelative("bottom_right", {-8, 20}, {1.0f, 1.0f}),
         generateCenteredTestCaseRelative("bottom_left", {-12, 20}, {0.0f, 1.0f}),
         generateCenteredTestCaseRelative("inside", {-10, 14}, {0.5f, 0.6f}),
         generateCenteredTestCaseRelative("x_too_small", {-14, 14}, {-0.5f, 0.6f}),
         generateCenteredTestCaseRelative("x_too_large", {-6, 14}, {1.5f, 0.6f}),
         generateCenteredTestCaseRelative("y_too_small", {-10, -4}, {0.5f, -0.6f}),
         generateCenteredTestCaseRelative("y_too_large", {-10, 26}, {0.5f, 1.4f})),
  generateTestNameRelative);

INSTANTIATE_TEST_CASE_P(
  Unit_CenteredViewport,
  AbsoluteCoordinates,
  Values(generateCenteredTestCaseAbsolute("top_left", {0.0f, 0.0f}, {-12, 5}),
         generateCenteredTestCaseAbsolute("top_right", {1.0f, 0.0f}, {-8, 5}),
         generateCenteredTestCaseAbsolute("bottom_right", {1.0f, 1.0f}, {-8, 20}),
         generateCenteredTestCaseAbsolute("bottom_left", {0.0f, 1.0f}, {-12, 20}),
         generateCenteredTestCaseAbsolute("inside", {0.5f, 0.6f}, {-10, 14}),
         generateCenteredTestCaseAbsolute("x_too_small", {-0.5f, 0.6f}, {-14, 14}),
         generateCenteredTestCaseAbsolute("x_too_large", {1.5f, 0.6f}, {-6, 14}),
         generateCenteredTestCaseAbsolute("y_too_small", {0.5f, -0.6f}, {-10, -4}),
         generateCenteredTestCaseAbsolute("y_too_large", {0.5f, 1.4f}, {-10, 26})),
  generateTestNameAbsolute);

TEST(Unit_CenteredViewport, Scale)
{
  const auto viewport = generateCenteredViewportI();

  const auto factor = 2;
  viewport->scale(factor, factor);

  const auto topLeft = olc::vi2d(CENTER.x - factor * DIMS.x / 2, CENTER.y + factor * DIMS.y / 2);
  EXPECT_EQ(viewport->topLeft(), topLeft);
  EXPECT_EQ(viewport->center(), CENTER);
  EXPECT_EQ(viewport->dims(), DIMS * factor);
}

} // namespace pge
