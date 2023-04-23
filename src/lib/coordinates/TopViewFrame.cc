
#include "TopViewFrame.hh"

namespace pge {

TopViewFrame::TopViewFrame(const CenteredViewport &cells, const TopLeftViewport &pixels)
  : CoordinateFrame(cells, pixels)
{}

CenteredViewport TopViewFrame::cellsViewport() const noexcept
{
  return m_cellsViewport;
}

olc::vf2d TopViewFrame::tilesToPixels(float x, float y) const noexcept
{
  auto rel = m_cellsViewport.relativeCoords(x, y);
  // cells viewport is centered, pixels viewport is top left based.
  // rel.x = (rel.x + 1.0f) / 2.0f;
  // cells viewport is with y up, pixels viewport is with y down.
  rel.y = (1.0f - rel.y) / 2.0f;
  return m_pixelsViewport.absoluteCoords(rel.x, rel.y);
}

olc::vf2d TopViewFrame::pixelsToTiles(float x, float y) const noexcept
{
  olc::vf2d rel = m_pixelsViewport.relativeCoords(x, y);
  return m_cellsViewport.absoluteCoords(rel.x, rel.y);
}

} // namespace pge
