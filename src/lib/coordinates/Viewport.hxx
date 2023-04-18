#ifndef PGE_APP_VIEWPORT_HXX
#define PGE_APP_VIEWPORT_HXX

#include "Viewport.hh"

namespace pge {

template<typename Coordinate>
inline olc::vf2d Viewport<Coordinate>::relativeCoords(const Vector &pos) const noexcept
{
  return relativeCoords(pos.x, pos.y);
}

template<typename Coordinate>
inline olc::vf2d Viewport<Coordinate>::absoluteCoords(const olc::vf2d &pos) const noexcept
{
  return absoluteCoords(pos.x, pos.y);
}

template<typename Coordinate>
inline void Viewport<Coordinate>::scale(const Coordinate factor) noexcept
{
  scale(factor, factor);
}

template<typename Coordinate>
inline bool Viewport<Coordinate>::visible(const Coordinate x,
                                          const Coordinate y,
                                          const Coordinate radius) const noexcept
{
  return visible(x, y, radius, radius);
}

template<typename Coordinate>
inline bool Viewport<Coordinate>::visible(const Vector &p, const Vector &sz) const noexcept
{
  return visible(p.x, p.y, sz.x, sz.y);
}

} // namespace pge

#endif /* PGE_APP_VIEWPORT_HXX */
