
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
  // `m_translationOrigin` moved to `pos`. Let's put some numbers:
  // m_translationPOrigin = (0, 1)
  // m_cachedPOrigin      = (0, 0)
  // pos                  = (1, 1)
  // It means pos, which **corresponds to m_translationOrigin** is
  // now more on the left side of the screen.
  // The question is then: what translation needs to be applied to
  // the center so that it is consistent with the new position (on
  // screen) of m_translationOrigin?
  // The answer to that is to apply the same translation that would
  // transform pos into m_translationOrigin again. **Not the other
  // way around**. This translation is computed then as so:
  // translation = m_translationOrigin - pos
  // By applying this, we would bring back the current position of
  // m_translationOrigin (which is pos) to its initial value.
  olc::vf2d translation = m_translationOrigin - pos;
  // The argument here is that pixels and cells viewport y axis are
  // moving in opposite direction.
  translation.y *= -1.0f;

  auto dCells = pixelsDistToCellsDist(translation);

  m_cellsViewport.moveTo(m_cachedPOrigin + dCells);
}

void CoordinateFrame::zoom(float factor, const olc::vf2d &pos)
{
  olc::vf2d dPixels = pos - m_pixelsViewport.topLeft();

  olc::vf2d pCells = pixelsToTiles(pos.x, pos.y);
  olc::vf2d dCells = pCells - m_cellsViewport.center();

  dPixels /= factor;
  dCells /= factor;

  m_cellsViewport.moveTo(pCells - dCells);

  // Only the dimensions of the cells viewport need to be updated.
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
