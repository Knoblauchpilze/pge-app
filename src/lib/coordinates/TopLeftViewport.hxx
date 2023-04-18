#ifndef PGE_APP_TOP_LEFT_VIEWPORT_HXX
#define PGE_APP_TOP_LEFT_VIEWPORT_HXX

#include "TopLeftViewport.hh"

namespace pge {

template<typename Coordinate>
inline TopLeftViewport<Coordinate>::TopLeftViewport(const Vector &tl, const Vector &dims) noexcept
  : m_topLeft(tl)
  , m_dims(dims)
{}

template<typename Coordinate>
inline typename TopLeftViewport<Coordinate>::Vector TopLeftViewport<Coordinate>::center()
  const noexcept
{
  return Vector(m_topLeft.x + m_dims.x / Coordinate(2), m_topLeft.y + m_dims.y / Coordinate(2));
}

template<typename Coordinate>
inline typename TopLeftViewport<Coordinate>::Vector TopLeftViewport<Coordinate>::topLeft()
  const noexcept
{
  return m_topLeft;
}

template<typename Coordinate>
inline typename TopLeftViewport<Coordinate>::Vector TopLeftViewport<Coordinate>::dims() const noexcept
{
  return m_dims;
}

template<typename Coordinate>
inline olc::vf2d TopLeftViewport<Coordinate>::relativeCoords(const Coordinate &x,
                                                             const Coordinate &y) const noexcept
{
  olc::vf2d out(x, y);

  out.x -= m_topLeft.x;
  out.y -= m_topLeft.y;

  out.x /= m_dims.x;
  out.y /= m_dims.y;

  return out;
}

template<typename Coordinate>
inline olc::vf2d TopLeftViewport<Coordinate>::absoluteCoords(const float x,
                                                             const float y) const noexcept
{
  olc::vf2d out(x, y);

  out.x *= m_dims.x;
  out.y *= m_dims.y;

  out.x += m_topLeft.x;
  out.y += m_topLeft.y;

  return out;
}

template<typename Coordinate>
inline void TopLeftViewport<Coordinate>::moveTo(const Vector &topLeft) noexcept
{
  m_topLeft = topLeft;
}

template<typename Coordinate>
inline void TopLeftViewport<Coordinate>::translate(const Vector &delta) noexcept
{
  m_topLeft += delta;
}

template<typename Coordinate>
inline void TopLeftViewport<Coordinate>::scale(const Coordinate sx, const Coordinate sy) noexcept
{
  m_dims.x *= sx;
  m_dims.y *= sy;
}

template<typename Coordinate>
inline bool TopLeftViewport<Coordinate>::visible(const Coordinate &x,
                                                 const Coordinate &y,
                                                 const Coordinate &sx,
                                                 const Coordinate &sy) const noexcept
{
  if (x + sx < m_topLeft.x || x - sx > m_topLeft.x + m_dims.x)
  {
    return false;
  }

  if (y + sy < m_topLeft.y || y - sy > m_topLeft.y + m_dims.y)
  {
    return false;
  }

  return true;
}

} // namespace pge

#endif /* PGE_APP_TOP_LEFT_VIEWPORT_HXX */
