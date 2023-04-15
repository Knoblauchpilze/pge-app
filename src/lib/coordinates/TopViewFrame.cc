
#include "TopViewFrame.hh"

namespace pge {

TopViewFrame::TopViewFrame(const CenteredViewportF &cells, const TopLeftViewportF &pixels)
  : CoordinateFrame(cells, pixels)
{}

CenteredViewportF TopViewFrame::cellsViewport() const noexcept
{
  return m_cellsViewport;
}

olc::vf2d TopViewFrame::tilesToPixels(float x, float y) const noexcept
{
  olc::vf2d rel = m_cellsViewport.relativeCoords(x, y);
  return m_pixelsViewport.absoluteCoords(rel.x, rel.y);
}

olc::vf2d TopViewFrame::pixelsToTiles(float x, float y) const noexcept
{
  olc::vf2d rel = m_pixelsViewport.relativeCoords(x, y);
  return m_cellsViewport.absoluteCoords(rel.x, rel.y);
}

} // namespace pge
