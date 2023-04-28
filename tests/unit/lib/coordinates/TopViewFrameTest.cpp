
#include <gtest/gtest.h>

#include "Common.hh"
#include "TopViewFrame.hh"

using namespace ::testing;

namespace pge {
const olc::vf2d CELLS_CENTER = {1.0f, 2.0f};
const olc::vf2d CELLS_DIMS   = {4.0f, 10.0f};

const olc::vf2d PIXELS_TOP_LEFT = {10.0f, 32.0f};
const olc::vf2d PIXELS_DIMS     = {128.0f, 58.0f};

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
  EXPECT_EQ(tile, PIXELS_DIMS / CELLS_DIMS);
}

auto generateTestCaseTilesToPixels(const std::string &name,
                                   const olc::vf2d &tiles,
                                   const olc::vf2d &expected) -> TestCaseTilesToPixels
{
  return TestCaseTilesToPixels{name, generateTopViewFrame(), tiles, expected};
}

// Useful IEEE calculators:
// http://weitz.de/ieee/
// https://www.h-schmidt.net/FloatConverter/IEEE754.html
INSTANTIATE_TEST_CASE_P(
  Unit_TopViewFrame,
  TilesToPixels,
  Values(generateTestCaseTilesToPixels("top_left", {-1.0f, 7.0f}, {10.0f, 32.0f}),
         generateTestCaseTilesToPixels("top_right", {3.0f, 7.0f}, {138.0f, 32.0f}),
         generateTestCaseTilesToPixels("bottom_right", {3.0f, -3.0f}, {138.0f, 90.0f}),
         generateTestCaseTilesToPixels("bottom_left", {-1.0f, -3.0f}, {10.0f, 90.0f}),
         generateTestCaseTilesToPixels("inside", {2.5f, -1.0f}, {122.0f, 78.4f}),
         generateTestCaseTilesToPixels("x_too_small", {-2.95f, 3.25f}, {-52.4f, 53.75f}),
         generateTestCaseTilesToPixels("x_too_large", {12.5f, 3.25f}, {442.0f, 53.75f}),
         generateTestCaseTilesToPixels("y_too_small", {-0.75f, -17.2f}, {18.0f, 172.36f}),
         generateTestCaseTilesToPixels("y_too_large", {-0.75f, 14.1f}, {18.0f, -9.18f})),
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
  Values(generateTestCasePixelsToTiles("top_left", {10.0f, 32.0f}, {-1.0f, 7.0f}),
         generateTestCasePixelsToTiles("top_right", {138.0f, 32.0f}, {3.0f, 7.0f}),
         generateTestCasePixelsToTiles("bottom_right", {138.0f, 90.0f}, {3.0f, -3.0f}),
         generateTestCasePixelsToTiles("bottom_left", {10.0f, 90.0f}, {-1.0f, -3.0f}),
         generateTestCasePixelsToTiles("inside", {122.0f, 78.4f}, {2.5f, -1.0f}),
         generateTestCasePixelsToTiles("x_too_small", {-52.4f, 53.75f}, {-2.95f, 3.25f}),
         generateTestCasePixelsToTiles("x_too_large", {442.0f, 53.75f}, {12.5f, 3.25f}),
         generateTestCasePixelsToTiles("y_too_small", {18.0f, 172.36f}, {-0.75f, -17.2f}),
         generateTestCasePixelsToTiles("y_too_large", {18.0f, -9.18f}, {-0.75f, 14.1f})),
  generateTestNamePixelsToTiles);

TEST(Unit_TopViewFrame, Translate)
{
  auto frame = generateTopViewFrame();

  olc::vf2d origin{20.0f, 51.0f};
  frame->beginTranslation(origin);

  olc::vf2d translationCells{2.6f, -1.7f};
  olc::vf2d scale = PIXELS_DIMS / CELLS_DIMS;

  auto final = origin + translationCells * scale;
  frame->translate(final);

  auto cells = frame->cellsViewport();
  // We moved the position of `[20; 51]` on screen from
  // this position to `origin + translationCells * scale`.
  // The center will move in the opposite direction to
  // accomodate for `origin` being at its new position
  // on screen. As the y coordinate moves in opposite
  // direction, we have to adjust the translation.
  olc::vf2d centerTranslation{translationCells.x, -translationCells.y};
  auto finalCells = CELLS_CENTER - centerTranslation;
  EXPECT_EQ(cells.center(), finalCells);
}

TEST(Unit_TopViewFrame, Translate_PreserveTileSize)
{
  auto frame = generateTopViewFrame();

  auto tile = frame->tileSize();
  EXPECT_EQ(tile, PIXELS_DIMS / CELLS_DIMS);

  olc::vf2d origin{20.0f, 51.0f};
  frame->beginTranslation(origin);

  olc::vf2d final{37.2f, 43.2f};
  frame->translate(final);

  tile = frame->tileSize();
  EXPECT_EQ(tile, PIXELS_DIMS / CELLS_DIMS);
}

TEST(Unit_TopViewFrame, ZoomIn)
{
  auto frame = generateTopViewFrame();

  olc::vf2d zoomCenter{35.0f, 56.0f};
  auto cellsPos = frame->pixelsToTiles(zoomCenter.x, zoomCenter.y);

  frame->zoomIn(zoomCenter);

  auto newCellsPos = frame->pixelsToTiles(zoomCenter.x, zoomCenter.y);
  EXPECT_EQ(newCellsPos, cellsPos);
}

TEST(Unit_TopViewFrame, ZoomIn_DoubleTileDimensions)
{
  auto frame = generateTopViewFrame();

  olc::vf2d zoomCenter{35.0f, 56.0f};
  frame->zoomIn(zoomCenter);

  auto tile = frame->tileSize();
  EXPECT_EQ(tile, (PIXELS_DIMS / CELLS_DIMS) * 2.0f);
}

TEST(Unit_TopViewFrame, ZoomIn_HalveCellsViewport)
{
  auto frame = generateTopViewFrame();

  olc::vf2d zoomCenter{35.0f, 56.0f};
  frame->zoomIn(zoomCenter);

  auto dims = frame->cellsViewport().dims();
  EXPECT_EQ(dims, CELLS_DIMS / 2.0f);
}

TEST(Unit_TopViewFrame, ZoomOut)
{
  auto frame = generateTopViewFrame();

  olc::vf2d zoomCenter{118.0f, 72.0f};
  auto cellsPos = frame->pixelsToTiles(zoomCenter.x, zoomCenter.y);

  frame->zoomOut(zoomCenter);

  auto newCellsPos = frame->pixelsToTiles(zoomCenter.x, zoomCenter.y);
  EXPECT_EQ(newCellsPos, cellsPos);
}

TEST(Unit_TopViewFrame, ZoomOut_HalveTileDimensions)
{
  auto frame = generateTopViewFrame();

  olc::vf2d zoomCenter{35.0f, 56.0f};
  frame->zoomOut(zoomCenter);

  auto tile = frame->tileSize();
  EXPECT_EQ(tile, (PIXELS_DIMS / CELLS_DIMS) / 2.0f);
}

TEST(Unit_TopViewFrame, ZoomOut_DoubleCellsViewport)
{
  auto frame = generateTopViewFrame();

  olc::vf2d zoomCenter{35.0f, 56.0f};
  frame->zoomOut(zoomCenter);

  auto dims = frame->cellsViewport().dims();
  EXPECT_EQ(dims, CELLS_DIMS * 2.0f);
}

} // namespace pge
