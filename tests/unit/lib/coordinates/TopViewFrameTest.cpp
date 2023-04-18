
#include <gtest/gtest.h>

#include "TopViewFrame.hh"

using namespace ::testing;

namespace pge {
const olc::vf2d CELLS_CENTER = {1.0f, 2.0f};
const olc::vf2d CELLS_DIMS   = {4.0f, 6.0f};

const olc::vf2d PIXELS_TOP_LEFT = {10, 32};
const olc::vf2d PIXELS_DIMS     = {100, 57};

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

} // namespace pge
