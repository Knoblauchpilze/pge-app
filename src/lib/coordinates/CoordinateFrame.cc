
#include "CoordinateFrame.hh"

namespace pge {

CoordinateFrame::CoordinateFrame(const CenteredViewportF &cells, const TopLeftViewportF &pixels)
  : utils::CoreObject("frame")
  ,

  m_cellsViewport(cells)
  , m_pixelsViewport(pixels)
  ,

  m_translationOrigin()
  , m_cachedPOrigin()
{
  setService("coordinate");
}

olc::vf2d CoordinateFrame::tileSize() const noexcept
{
  const auto cellsDims  = m_cellsViewport.dims();
  const auto pixelsDims = m_pixelsViewport.dims();

  return pixelsDims / cellsDims;
}

olc::vi2d CoordinateFrame::pixelsToTiles(const olc::vi2d &pixels,
                                         olc::vf2d *intraTile) const noexcept
{
  auto tiles = pixelsToTiles(pixels.x, pixels.y);

  olc::vi2d out(static_cast<int>(std::floor(tiles.x)), static_cast<int>(std::floor(tiles.y)));

  if (intraTile != nullptr)
  {
    intraTile->x = tiles.x - out.x;
    intraTile->y = tiles.y - out.y;
  }

  return out;
}

void CoordinateFrame::zoomIn(const olc::vf2d &pos)
{
  zoom(0.5f, pos);
}

void CoordinateFrame::zoomOut(const olc::vf2d &pos)
{
  zoom(2.0f, pos);
}

void CoordinateFrame::beginTranslation(const olc::vi2d &origin)
{
  m_translationOrigin = origin;
  m_cachedPOrigin     = m_pixelsViewport.topLeft();
}

void CoordinateFrame::translate(const olc::vi2d &pos)
{
  // We need to deduce the translation added by the input
  // `pos` assuming that this will be the final position
  // of the viewport.
  olc::vf2d translation = pos - m_translationOrigin;
  m_pixelsViewport.moveTo(m_cachedPOrigin + translation);
}

void CoordinateFrame::zoom(float factor, const olc::vf2d &pos)
{
  // We want to fix `pos` on screen. To zoom of the factor,
  // we want the distance to:
  //  - the top left of the pixels viewport to be divided by
  //    the factor.
  //  - the center of the cells viewport to be divided by
  //    the factor.
  olc::vf2d dPixels = m_pixelsViewport.topLeft() - pos;

  olc::vf2d pCells = pixelsToTiles(pos);
  olc::vf2d dCells = m_cellsViewport.center() - pCells;

  log("p: " + pos.str() + ", " + pCells.str());
  log("pix: " + m_pixelsViewport.topLeft().str() + " d: " + dPixels.str());
  log("cells: " + m_cellsViewport.center().str() + " d: " + dCells.str());

  dPixels /= factor;
  dCells /= factor;

  m_pixelsViewport.moveTo(dPixels);
  m_cellsViewport.moveTo(dCells);

  log("pix: " + m_pixelsViewport.topLeft().str() + " d: " + dPixels.str());
  log("cells: " + m_cellsViewport.center().str() + " d: " + dCells.str());

  // Only the dimensions of the cells viewport need to be
  // updated.
  m_cellsViewport.scale(factor, factor);
}

} // namespace pge
