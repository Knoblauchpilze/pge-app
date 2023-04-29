
#include "IsometricViewFrame.hh"

/// Links:
/// http://archive.gamedev.net/archive/reference/programming/features/mm4ihm/index.html
/// https://gamedev.stackexchange.com/questions/142784/how-do-you-transform-a-coordinate-system-from-cartesian-to-isometric
/// https://gamedev.stackexchange.com/questions/31113/how-can-i-improve-my-isometric-tile-picking-algorithm/31124#31124
/// https://stackoverflow.com/questions/21842814/mouse-position-to-isometric-tile-including-height

/// Promising:
/// https://pikuma.com/blog/isometric-projection-in-games

namespace pge {

IsometricViewFrame::IsometricViewFrame(const CenteredViewport &cells, const TopLeftViewport &pixels)
  : CoordinateFrame(cells, pixels)
{}

CenteredViewport IsometricViewFrame::cellsViewport() const noexcept
{
  return m_cellsViewport;
}

olc::vf2d IsometricViewFrame::tilesToPixels(float x, float y) const noexcept
{
  return olc::vf2d{x, y};
}

olc::vf2d IsometricViewFrame::pixelsToTiles(float x, float y) const noexcept
{
  return olc::vf2d{x, y};
}

} // namespace pge
