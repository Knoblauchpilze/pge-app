
#include <gtest/gtest.h>

#include "CommonCoordinateFrame.hh"
#include "IsometricViewFrame.hh"

using namespace ::testing;

namespace pge::tests {

auto generateIsometricViewFrame() -> CoordinateFramePtr
{
  CenteredViewport tiles = {constants::Tiles::CENTER, constants::Tiles::DIMS};
  TopLeftViewport pixels = {constants::Pixels::TOP_LEFT, constants::Pixels::DIMS};
  return std::make_shared<IsometricViewFrame>(tiles, pixels);
}

TEST(Unit_IsometricViewFrame, Constructor)
{
  auto frame = generateIsometricViewFrame();

  auto tiles = frame->tilesViewport();
  EXPECT_EQ(tiles.center(), constants::Tiles::CENTER);
  EXPECT_EQ(tiles.dims(), constants::Tiles::DIMS);

  auto tile = frame->tileSize();
  EXPECT_EQ(tile, constants::Pixels::DIMS / constants::Tiles::DIMS);
}

auto generateIsometricTestCaseTilesToPixels(const std::string &name,
                                            const olc::vf2d &tiles,
                                            const olc::vf2d &expected) -> TestCaseTilesToPixels
{
  return TestCaseTilesToPixels{name, generateIsometricViewFrame(), tiles, expected};
}

INSTANTIATE_TEST_CASE_P(
  Unit_IsometricViewFrame,
  TilesToPixels,
  Values(
    generateIsometricTestCaseTilesToPixels("top_left", constants::Tiles::TOP_LEFT, {10.0f, 32.0f}),
    generateIsometricTestCaseTilesToPixels("top_right", constants::Tiles::TOP_RIGHT, {138.0f, 32.0f}),
    generateIsometricTestCaseTilesToPixels("bottom_right",
                                           constants::Tiles::BOTTOM_RIGHT,
                                           {138.0f, 90.0f}),
    generateIsometricTestCaseTilesToPixels("bottom_left",
                                           constants::Tiles::BOTTOM_LEFT,
                                           {10.0f, 90.0f}),
    generateIsometricTestCaseTilesToPixels("inside", {2.5f, -1.0f}, {122.0f, 78.4f}),
    generateIsometricTestCaseTilesToPixels("x_too_small", {-2.95f, 3.25f}, {-52.4f, 53.75f}),
    generateIsometricTestCaseTilesToPixels("x_too_large", {12.5f, 3.25f}, {442.0f, 53.75f}),
    generateIsometricTestCaseTilesToPixels("y_too_small", {-0.75f, -17.2f}, {18.0f, 172.36f}),
    generateIsometricTestCaseTilesToPixels("y_too_large", {-0.75f, 14.1f}, {18.0f, -9.18f})),
  generateTestNameTilesToPixels);

auto generateIsometricTestCasePixelsToTiles(const std::string &name,
                                            const olc::vf2d &pixels,
                                            const olc::vf2d &expected) -> TestCasePixelsToTiles
{
  return TestCasePixelsToTiles{name, generateIsometricViewFrame(), pixels, expected, 1e-5f};
}

INSTANTIATE_TEST_CASE_P(
  Unit_IsometricViewFrame,
  PixelsToTiles,
  Values(
    generateIsometricTestCasePixelsToTiles("top_left",
                                           constants::Pixels::TOP_LEFT,
                                           {constants::Tiles::CENTER.x
                                              - std::sqrt(2.0f) * constants::Tiles::DIMS.x / 2.0f,
                                            constants::Tiles::CENTER.y}),
    generateIsometricTestCasePixelsToTiles("top_right",
                                           constants::Pixels::TOP_RIGHT,
                                           {constants::Tiles::CENTER.x,
                                            constants::Tiles::CENTER.y
                                              + std::sqrt(2.0f) * constants::Tiles::DIMS.y / 2.0f}),
    generateIsometricTestCasePixelsToTiles("bottom_right",
                                           constants::Pixels::BOTTOM_RIGHT,
                                           {constants::Tiles::CENTER.x
                                              + std::sqrt(2.0f) * constants::Tiles::DIMS.x / 2.0f,
                                            constants::Tiles::CENTER.y}),
    generateIsometricTestCasePixelsToTiles("bottom_left",
                                           constants::Pixels::BOTTOM_LEFT,
                                           {constants::Tiles::CENTER.x,
                                            constants::Tiles::CENTER.y
                                              - std::sqrt(2.0f) * constants::Tiles::DIMS.y / 2.0f}),
    generateIsometricTestCasePixelsToTiles("inside", {122.0f, 78.4f}, {2.5f, -1.0f}),
    generateIsometricTestCasePixelsToTiles("x_too_small", {-52.4f, 53.75f}, {-2.95f, 3.25f}),
    generateIsometricTestCasePixelsToTiles("x_too_large", {442.0f, 53.75f}, {12.5f, 3.25f}),
    generateIsometricTestCasePixelsToTiles("y_too_small", {18.0f, 172.36f}, {-0.75f, -17.2f}),
    generateIsometricTestCasePixelsToTiles("y_too_large", {18.0f, -9.18f}, {-0.75f, 14.1f})),
  generateTestNamePixelsToTiles);

TEST(Unit_IsometricViewFrame, Translate)
{
  auto frame = generateIsometricViewFrame();

  olc::vf2d origin{20.0f, 51.0f};
  frame->beginTranslation(origin);

  olc::vf2d translationTiles{2.6f, -1.7f};
  olc::vf2d scale = constants::Pixels::DIMS / constants::Tiles::DIMS;

  auto final = origin + translationTiles * scale;
  frame->translate(final);

  auto tiles = frame->tilesViewport();
  // We moved the position of `[20; 51]` on screen from
  // this position to `origin + translationTiles * scale`.
  // The center will move in the opposite direction to
  // accomodate for `origin` being at its new position
  // on screen. As the y coordinate moves in opposite
  // direction, we have to adjust the translation.
  olc::vf2d centerTranslation{translationTiles.x, -translationTiles.y};
  auto finalTiles = constants::Tiles::CENTER - centerTranslation;
  EXPECT_EQ(tiles.center(), finalTiles);
}

TEST(Unit_IsometricViewFrame, Translate_PreserveTileSize)
{
  auto frame = generateIsometricViewFrame();

  auto tile = frame->tileSize();
  EXPECT_EQ(tile, constants::Pixels::DIMS / constants::Tiles::DIMS);

  olc::vf2d origin{20.0f, 51.0f};
  frame->beginTranslation(origin);

  olc::vf2d final{37.2f, 43.2f};
  frame->translate(final);

  tile = frame->tileSize();
  EXPECT_EQ(tile, constants::Pixels::DIMS / constants::Tiles::DIMS);
}

TEST(Unit_IsometricViewFrame, ZoomIn)
{
  auto frame = generateIsometricViewFrame();

  olc::vf2d zoomCenter{35.0f, 56.0f};
  auto tilesPos = frame->pixelsToTiles(zoomCenter.x, zoomCenter.y);

  frame->zoomIn(zoomCenter);

  auto newTilesPos = frame->pixelsToTiles(zoomCenter.x, zoomCenter.y);
  EXPECT_EQ(newTilesPos, tilesPos);
}

TEST(Unit_IsometricViewFrame, ZoomIn_DoubleTileDimensions)
{
  auto frame = generateIsometricViewFrame();

  olc::vf2d zoomCenter{35.0f, 56.0f};
  frame->zoomIn(zoomCenter);

  auto tile = frame->tileSize();
  EXPECT_EQ(tile, (constants::Pixels::DIMS / constants::Tiles::DIMS) * 2.0f);
}

TEST(Unit_IsometricViewFrame, ZoomIn_HalveTilesViewport)
{
  auto frame = generateIsometricViewFrame();

  olc::vf2d zoomCenter{35.0f, 56.0f};
  frame->zoomIn(zoomCenter);

  auto dims = frame->tilesViewport().dims();
  EXPECT_EQ(dims, constants::Tiles::DIMS / 2.0f);
}

TEST(Unit_IsometricViewFrame, ZoomOut)
{
  auto frame = generateIsometricViewFrame();

  olc::vf2d zoomCenter{118.0f, 72.0f};
  auto tilesPos = frame->pixelsToTiles(zoomCenter.x, zoomCenter.y);

  frame->zoomOut(zoomCenter);

  auto newTilesPos = frame->pixelsToTiles(zoomCenter.x, zoomCenter.y);
  EXPECT_EQ(newTilesPos, tilesPos);
}

TEST(Unit_IsometricViewFrame, ZoomOut_HalveTileDimensions)
{
  auto frame = generateIsometricViewFrame();

  olc::vf2d zoomCenter{35.0f, 56.0f};
  frame->zoomOut(zoomCenter);

  auto tile = frame->tileSize();
  EXPECT_EQ(tile, (constants::Pixels::DIMS / constants::Tiles::DIMS) / 2.0f);
}

TEST(Unit_IsometricViewFrame, ZoomOut_DoubleTilesViewport)
{
  auto frame = generateIsometricViewFrame();

  olc::vf2d zoomCenter{35.0f, 56.0f};
  frame->zoomOut(zoomCenter);

  auto dims = frame->tilesViewport().dims();
  EXPECT_EQ(dims, constants::Tiles::DIMS * 2.0f);
}

} // namespace pge::tests
