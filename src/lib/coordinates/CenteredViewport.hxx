#ifndef    PGE_APP_CENTERED_VIEWPORT_HXX
# define   PGE_APP_CENTERED_VIEWPORT_HXX

# include "CenteredViewport.hh"

namespace pge {

  template <typename Coordinate>
  inline
  CenteredViewport<Coordinate>::CenteredViewport(const Vector& center,
                                                 const Vector& dims) noexcept:
    Viewport<Coordinate>(),
    m_center(center),
    m_dims(dims)
  {}

  template <typename Coordinate>
  inline
  typename CenteredViewport<Coordinate>::Vector
  CenteredViewport<Coordinate>::center() const noexcept {
    return m_center;
  }

  template <typename Coordinate>
  inline
  typename CenteredViewport<Coordinate>::Vector
  CenteredViewport<Coordinate>::topLeft() const noexcept {
    return Vector(
      m_center.x - m_dims.x / Coordinate(2),
      m_center.y + m_dims.y / Coordinate(2)
    );
  }

  template <typename Coordinate>
  inline
  typename CenteredViewport<Coordinate>::Vector
  CenteredViewport<Coordinate>::dims() const noexcept {
    return m_dims;
  }

  template <typename Coordinate>
  inline
  olc::vf2d
  CenteredViewport<Coordinate>::relativeCoords(const Coordinate& x, const Coordinate& y) const noexcept {
    olc::vf2d out(x, y);

    out.x -= m_center.x;
    out.y -= m_center.y;

    out.x /= m_dims.x;
    out.y /= m_dims.y;

    return out;
  }

  template <typename Coordinate>
  inline
  olc::vf2d
  CenteredViewport<Coordinate>::absoluteCoords(const Coordinate& x, const Coordinate& y) const noexcept {
    olc::vf2d out(x, y);

    out.x *= m_dims.x;
    out.y *= m_dims.y;

    out.x += m_center.x;
    out.y += m_center.y;

    return out;
  }

  template <typename Coordinate>
  inline
  void
  CenteredViewport<Coordinate>::moveTo(const Vector& center) noexcept {
    m_center = center;
  }

  template <typename Coordinate>
  inline
  void
  CenteredViewport<Coordinate>::translate(const Vector& delta) noexcept {
    m_center += delta;
  }

  template <typename Coordinate>
  inline
  void
  CenteredViewport<Coordinate>::scale(const Coordinate factor) noexcept {
    scale(factor, factor);
  }

  template <typename Coordinate>
  inline
  void
  CenteredViewport<Coordinate>::scale(const Coordinate sx, const Coordinate sy) noexcept {
    m_dims.x *= sx;
    m_dims.y *= sy;
  }

}

#endif    /* PGE_APP_CENTERED_VIEWPORT_HXX */
