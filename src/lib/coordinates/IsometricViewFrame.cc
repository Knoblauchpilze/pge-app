
#include "IsometricViewFrame.hh"

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
