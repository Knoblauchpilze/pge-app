
#include <gtest/gtest.h>

#include "Common.hh"
#include "TopViewFrame.hh"

using namespace ::testing;

namespace pge {
const olc::vf2d CELLS_CENTER = {1.0f, 2.0f};
const olc::vf2d CELLS_DIMS   = {4.0f, 6.0f};

const olc::vf2d PIXELS_TOP_LEFT = {10.0f, 32.0f};
const olc::vf2d PIXELS_DIMS     = {100.0f, 57.0f};

auto generateTopViewFrame() -> CoordinateFramePtr
{
  CenteredViewport cells = {CELLS_CENTER, CELLS_DIMS};
  TopLeftViewport pixels = {PIXELS_TOP_LEFT, PIXELS_DIMS};
  return std::make_shared<TopViewFrame>(cells, pixels);
}

TEST(Unit_TopViewFrame, Constructor)
{
  auto frame = generateTopViewFrame();

  auto cells = frame->cellsViewport();
  EXPECT_EQ(cells.center(), CELLS_CENTER);
  EXPECT_EQ(cells.dims(), CELLS_DIMS);

  auto tile = frame->tileSize();
  EXPECT_EQ(tile, olc::vf2d(25.0f, 9.5f));
}

auto generateTestCaseTilesToPixels(const std::string &name,
                                   const olc::vf2d &tiles,
                                   const olc::vf2d &expected) -> TestCaseTilesToPixels
{
  return TestCaseTilesToPixels{name, generateTopViewFrame(), tiles, expected};
}

INSTANTIATE_TEST_CASE_P(
  Unit_TopViewFrame,
  TilesToPixels,
  Values(generateTestCaseTilesToPixels("top_left", {-1.0f, 5.0f}, {10.0f, 32.0f}),
         generateTestCaseTilesToPixels("top_right", {3.0f, 5.0f}, {110.0f, 32.0f}),
         generateTestCaseTilesToPixels("bottom_right", {3.0f, -1.0f}, {110.0f, 89.0f}),
         generateTestCaseTilesToPixels("bottom_left", {-1.0f, -1.0f}, {10.0f, 89.0f}),
         generateTestCaseTilesToPixels("inside", {2.7f, -0.8f}, {102.5f, 87.1f}),
         generateTestCaseTilesToPixels("x_too_small", {-2.9f, 3.2f}, {-37.5f, 49.1f}),
         generateTestCaseTilesToPixels("x_too_large", {12.5f, 3.2f}, {347.5f, 49.1f}),
         generateTestCaseTilesToPixels("y_too_small", {-0.8f, -17.2f}, {15.0f, 242.9f}),
         generateTestCaseTilesToPixels("y_too_large", {-0.8f, 13.2f}, {15.0f, -67.9f})),
  generateTestNameTilesToPixels);

auto generateTestCasePixelsToTiles(const std::string &name,
                                   const olc::vf2d &pixels,
                                   const olc::vf2d &expected) -> TestCasePixelsToTiles
{
  return TestCasePixelsToTiles{name, generateTopViewFrame(), pixels, expected};
}

INSTANTIATE_TEST_CASE_P(
  Unit_TopViewFrame,
  PixelsToTiles,
  Values(generateTestCasePixelsToTiles("top_left", {10.0f, 32.0f}, {-1.0f, 5.0f}),
         generateTestCasePixelsToTiles("top_right", {110.0f, 32.0f}, {3.0f, 5.0f}),
         generateTestCasePixelsToTiles("bottom_right", {110.0f, 89.0f}, {3.0f, -1.0f}),
         generateTestCasePixelsToTiles("bottom_left", {10.0f, 89.0f}, {-1.0f, -1.0f}),
         generateTestCasePixelsToTiles("inside", {102.5f, 87.1f}, {2.7f, -0.8f}),
         generateTestCasePixelsToTiles("x_too_small", {-37.5f, 49.1f}, {-2.9f, 3.2f}),
         generateTestCasePixelsToTiles("x_too_large", {347.5f, 49.1f}, {12.5f, 3.2f}),
         generateTestCasePixelsToTiles("y_too_small", {15.0f, 242.9}, {-0.8f, -17.2f}),
         generateTestCasePixelsToTiles("y_too_large", {15.0f, -67.9f}, {-0.8f, 13.2f})),
  generateTestNamePixelsToTiles);

TEST(Unit_TopViewFrame, Translate_DoesNotChangeTileSize)
{
  auto frame = generateTopViewFrame();

  auto tile = frame->tileSize();
  EXPECT_EQ(tile, olc::vf2d(25.0f, 9.5f));

  olc::vf2d origin{20.0f, 51.0f};
  frame->beginTranslation(origin);

  olc::vf2d final{37.2f, 43.2f};
  frame->translate(final);

  tile = frame->tileSize();
  EXPECT_EQ(tile, olc::vf2d(25.0f, 9.5f));
}

} // namespace pge
