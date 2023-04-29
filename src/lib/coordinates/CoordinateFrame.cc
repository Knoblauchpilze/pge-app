
#include "CoordinateFrame.hh"

namespace pge {

CoordinateFrame::CoordinateFrame(const CenteredViewport &tiles, const TopLeftViewport &pixels)
  : utils::CoreObject("frame")
  , m_tilesViewport(tiles)
  , m_pixelsViewport(pixels)
  , m_translationOrigin()
  , m_cachedPOrigin()
{
  setService("coordinate");
}

olc::vf2d CoordinateFrame::tileSize() const noexcept
{
  const auto tilesDims  = m_tilesViewport.dims();
  const auto pixelsDims = m_pixelsViewport.dims();

  return pixelsDims / tilesDims;
}

CenteredViewport CoordinateFrame::tilesViewport() const noexcept
{
  return m_tilesViewport;
}

olc::vf2d CoordinateFrame::tilesToPixels(float x, float y) const noexcept
{
  auto rel = m_tilesViewport.relativeCoords(x, y);
  // Tiles viewport is centered, pixels viewport is top left based.
  // The minimum coordinate for the centered is `-1` and so we need
  // to offset this. Also as it ranges from `[-1; 1]`, we need to
  // half the value as the pixels only ranges from `[0; 1]`.
  rel.x = (rel.x + 1.0f) / 2.0f;
  // Tiles viewport is with y up, pixels viewport is with y down so
  // the 1 of the tiles is the 0 of the pixels and so we need to map
  // negatively `y`. Similarly as for `x`, tiles are ranging from
  // `[-1; 1]` while pixels go from `[0; 1]` so we need to half the
  // value.
  rel.y = (1.0f - rel.y) / 2.0f;

  auto transformed = normalizedTilesToPixels(rel);

  return m_pixelsViewport.absoluteCoords(transformed.x, transformed.y);
}

olc::vf2d CoordinateFrame::pixelsToTiles(float x, float y) const noexcept
{
  auto rel = m_pixelsViewport.relativeCoords(x, y);
  // Reverse operation of the `tilesToPixels`.
  rel.x = 2.0f * rel.x - 1.0f;
  rel.y = 1.0f - 2.0f * rel.y;

  auto transformed = normalizedPixelsToTiles(rel);

  return m_tilesViewport.absoluteCoords(transformed.x, transformed.y);
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
  m_cachedPOrigin     = m_tilesViewport.center();
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
  // The argument here is that pixels and tiles viewport y axis are
  // moving in opposite direction.
  translation.y *= -1.0f;

  auto dTiles = pixelsDistToTilesDist(translation);

  m_tilesViewport.moveTo(m_cachedPOrigin + dTiles);
}

void CoordinateFrame::zoom(float factor, const olc::vf2d &pos)
{
  olc::vf2d dPixels = pos - m_pixelsViewport.topLeft();

  olc::vf2d pTiles = pixelsToTiles(pos.x, pos.y);
  olc::vf2d dTiles = pTiles - m_tilesViewport.center();

  dPixels /= factor;
  dTiles /= factor;

  m_tilesViewport.moveTo(pTiles - dTiles);

  // Only the dimensions of the tiles viewport need to be updated.
  m_tilesViewport.scale(1.0f / factor, 1.0f / factor);
}

olc::vf2d CoordinateFrame::pixelsDistToTilesDist(const olc::vf2d &pixelsDist)
{
  return pixelsDistToTilesDist(pixelsDist.x, pixelsDist.y);
}

olc::vf2d CoordinateFrame::pixelsDistToTilesDist(float dx, float dy)
{
  auto ratio = m_pixelsViewport.dims() / m_tilesViewport.dims();
  return olc::vf2d{dx / ratio.x, dy / ratio.y};
}

olc::vf2d CoordinateFrame::tilesDistToPixelsDist(const olc::vf2d &tilesDist)
{
  return tilesDistToPixelsDist(tilesDist.x, tilesDist.y);
}

olc::vf2d CoordinateFrame::tilesDistToPixelsDist(float dx, float dy)
{
  auto ratio = m_tilesViewport.dims() / m_pixelsViewport.dims();
  return olc::vf2d{dx / ratio.x, dy / ratio.y};
}

} // namespace pge
