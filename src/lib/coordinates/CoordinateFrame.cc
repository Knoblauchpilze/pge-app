
#include "CoordinateFrame.hh"

namespace pge {

CoordinateFrame::CoordinateFrame(const CenteredViewport &cells, const TopLeftViewport &pixels)
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
  zoom(2.0f, pos);
}

void CoordinateFrame::zoomOut(const olc::vf2d &pos)
{
  zoom(0.5f, pos);
}

void CoordinateFrame::beginTranslation(const olc::vf2d &origin)
{
  m_translationOrigin = origin;
  m_cachedPOrigin     = m_cellsViewport.center();
}

void CoordinateFrame::translate(const olc::vf2d &pos)
{
  // We need to deduce the translation added by the input
  // `pos` assuming that this will be the final position
  // of the viewport.
  olc::vf2d translation = pos - m_translationOrigin;

  auto dCells = pixelsDistToCellsDist(translation);

  m_cellsViewport.moveTo(m_cachedPOrigin + dCells);
}

void CoordinateFrame::zoom(float factor, const olc::vf2d &pos)
{
  // We want to fix `pos` on screen. To zoom of the factor,
  // we want the distance to:
  //  - the top left of the pixels viewport to be divided by
  //    the factor.
  //  - the center of the cells viewport to be divided by
  //    the factor.
  olc::vf2d dPixels = pos - m_pixelsViewport.topLeft();

  olc::vf2d pCells = pixelsToTiles(pos.x, pos.y);
  olc::vf2d dCells = pCells - m_cellsViewport.center();

  log("p: " + pos.str() + ", " + pCells.str());
  log("pix: " + m_pixelsViewport.topLeft().str() + " d: " + dPixels.str());
  log("cells: " + m_cellsViewport.center().str() + " d: " + dCells.str());

  dPixels /= factor;
  dCells /= factor;

  // m_pixelsViewport.translate(dPixels);
  m_cellsViewport.translate(dCells);

  log("pix: " + m_pixelsViewport.topLeft().str() + " d: " + dPixels.str());
  log("cells: " + m_cellsViewport.center().str() + " d: " + dCells.str());

  // Only the dimensions of the cells viewport need to be
  // updated.
  m_cellsViewport.scale(1.0f / factor, 1.0f / factor);
}

olc::vf2d CoordinateFrame::pixelsDistToCellsDist(const olc::vf2d &pixelsDist)
{
  return pixelsDistToCellsDist(pixelsDist.x, pixelsDist.y);
}

olc::vf2d CoordinateFrame::pixelsDistToCellsDist(float dx, float dy)
{
  auto ratio = m_pixelsViewport.dims() / m_cellsViewport.dims();
  return olc::vf2d{dx / ratio.x, dy / ratio.y};
}

olc::vf2d CoordinateFrame::cellsDistToPixelsDist(const olc::vf2d &cellsDist)
{
  return cellsDistToPixelsDist(cellsDist.x, cellsDist.y);
}

olc::vf2d CoordinateFrame::cellsDistToPixelsDist(float dx, float dy)
{
  auto ratio = m_cellsViewport.dims() / m_pixelsViewport.dims();
  return olc::vf2d{dx / ratio.x, dy / ratio.y};
}

} // namespace pge
