
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
  // Cells viewport is centered, pixels viewport is top left based.
  // The minimum coordinate for the centered is `-1` and so we need
  // to offset this. Also as it ranges from `[-1; 1]`, we need to
  // half the value as the pixels only ranges from `[0; 1]`.
  rel.x = (rel.x + 1.0f) / 2.0f;
  // Cells viewport is with y up, pixels viewport is with y down so
  // the 1 of the cells is the 0 of the pixels and so we need to map
  // negatively `y`. Similarly as for `x`, cells are ranging from
  // `[-1; 1]` while pixels go from `[0; 1]` so we need to half the
  // value.
  rel.y = (1.0f - rel.y) / 2.0f;
  return m_pixelsViewport.absoluteCoords(rel.x, rel.y);
}

olc::vf2d TopViewFrame::pixelsToTiles(float x, float y) const noexcept
{
  olc::vf2d rel = m_pixelsViewport.relativeCoords(x, y);
  // Reverse operation of the `tilesToPixels`.
  rel.x = 2.0f * rel.x - 1.0f;
  rel.y = 1.0f - 2.0f * rel.y;
  return m_cellsViewport.absoluteCoords(rel.x, rel.y);
}

} // namespace pge
