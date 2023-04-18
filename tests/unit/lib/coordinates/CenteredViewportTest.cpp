
#include "CenteredViewport.hh"
#include "Common.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge {
const olc::vi2d CENTER{-12, 5};
const olc::vi2d DIMS{4, 10};

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

auto generateCenteredTestCaseVisibility(const std::string &name,
                                        const olc::vf2d &coords,
                                        const bool expectedVisibility) -> TestCaseVisibility
{
  return TestCaseVisibility{name, generateCenteredViewportI, coords, expectedVisibility};
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
  Values(generateCenteredTestCaseRelative("top_left", {-14, 10}, {-1.0f, 1.0f}),
         generateCenteredTestCaseRelative("top_right", {-10, 10}, {1.0f, 1.0f}),
         generateCenteredTestCaseRelative("bottom_right", {-10, 0}, {1.0f, -1.0f}),
         generateCenteredTestCaseRelative("bottom_left", {-14, 0}, {-1.0f, -1.0f}),
         generateCenteredTestCaseRelative("inside", {-11, 7}, {0.5f, 0.4f}),
         generateCenteredTestCaseRelative("x_too_small", {-16, 7}, {-2.0f, 0.4f}),
         generateCenteredTestCaseRelative("x_too_large", {-7, 7}, {2.5f, 0.4f}),
         generateCenteredTestCaseRelative("y_too_small", {-13, -7}, {-0.5f, -2.4f}),
         generateCenteredTestCaseRelative("y_too_large", {-13, 36}, {-0.5f, 6.2f})),
  generateTestNameRelative);

INSTANTIATE_TEST_CASE_P(
  Unit_CenteredViewport,
  AbsoluteCoordinates,
  Values(generateCenteredTestCaseAbsolute("top_left", {-1.0f, 1.0f}, {-14, 10}),
         generateCenteredTestCaseAbsolute("top_right", {1.0f, 1.0f}, {-10, 10}),
         generateCenteredTestCaseAbsolute("bottom_right", {1.0f, -1.0f}, {-10, 0}),
         generateCenteredTestCaseAbsolute("bottom_left", {-1.0f, -1.0f}, {-14, 0}),
         generateCenteredTestCaseAbsolute("inside", {0.5f, 0.4f}, {-11, 7}),
         generateCenteredTestCaseAbsolute("x_too_small", {-2.0f, 0.4f}, {-16, 7}),
         generateCenteredTestCaseAbsolute("x_too_large", {2.5f, 0.4f}, {-7, 7}),
         generateCenteredTestCaseAbsolute("y_too_small", {-0.5f, -2.4f}, {-13, -7}),
         generateCenteredTestCaseAbsolute("y_too_large", {-0.5f, 6.2f}, {-13, 36})),
  generateTestNameAbsolute);

TEST(Unit_CenteredViewport, MoveTo)
{
  const auto viewport = generateCenteredViewportI();

  const auto origin = olc::vi2d(2, 3);
  viewport->moveTo(origin);

  const auto topLeft = olc::vi2d(origin.x - DIMS.x / 2, origin.y + DIMS.y / 2);
  EXPECT_EQ(viewport->topLeft(), topLeft);
  EXPECT_EQ(viewport->center(), origin);
  EXPECT_EQ(viewport->dims(), DIMS);
}

TEST(Unit_CenteredViewport, Translate)
{
  const auto viewport = generateCenteredViewportI();

  const auto delta = olc::vi2d(2, 3);
  viewport->translate(delta);

  const auto topLeft = olc::vi2d(CENTER.x + delta.x - DIMS.x / 2, CENTER.y + delta.y + DIMS.y / 2);
  EXPECT_EQ(viewport->topLeft(), topLeft);
  const auto center = CENTER + delta;
  EXPECT_EQ(viewport->center(), center);
  EXPECT_EQ(viewport->dims(), DIMS);
}

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

INSTANTIATE_TEST_CASE_P(Unit_CenteredViewport,
                        Visibility,
                        Values(generateCenteredTestCaseVisibility("top_left", {-14, 10}, true),
                               generateCenteredTestCaseVisibility("top_right", {-10, 10}, true),
                               generateCenteredTestCaseVisibility("bottom_right", {-10, 0}, true),
                               generateCenteredTestCaseVisibility("bottom_left", {-14, 0}, true),
                               generateCenteredTestCaseVisibility("inside", {-11, 7}, true),
                               generateCenteredTestCaseVisibility("x_too_small", {-16, 7}, false),
                               generateCenteredTestCaseVisibility("x_too_large", {-7, 7}, false),
                               generateCenteredTestCaseVisibility("y_too_small", {-13, -7}, false),
                               generateCenteredTestCaseVisibility("y_too_large", {-13, 36}, false)),
                        generateTestNameVisibility);
// const olc::vi2d CENTER{-12, 5};
// const olc::vi2d DIMS{4, 10};
} // namespace pge
