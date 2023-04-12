#ifndef    PGE_APP_VIEWPORT_HXX
# define   PGE_APP_VIEWPORT_HXX

# include "Viewport.hh"

namespace pge {

  template <typename Coordinate>
  inline
  olc::vf2d
  Viewport<Coordinate>::relativeCoords(const Vector& pos) const noexcept {
    return relativeCoords(pos.x, pos.y);
  }

  template <typename Coordinate>
  inline
  olc::vf2d
  Viewport<Coordinate>::absoluteCoords(const Vector& pos) const noexcept {
    return absoluteCoords(pos.x, pos.y);
  }

  template <typename Coordinate>
  inline
  bool
  Viewport<Coordinate>::visible(const Coordinate x,
                                const Coordinate y,
                                const Coordinate radius) const noexcept
  {
    return visible(x, y, radius, radius);
  }

  template <typename Coordinate>
  inline
  bool
  Viewport<Coordinate>::visible(const Vector& p, const Vector& sz) const noexcept {
    return visible(p.x, p.y, sz.x, sz.y);
  }

  template <typename Coordinate>
  inline
  bool
  Viewport<Coordinate>::visible(const Coordinate& x,
                                const Coordinate& y,
                                const Coordinate& sx,
                                const Coordinate& sy) const noexcept
  {
    const auto origin = topLeft();
    const auto size = dims();

    if (x + sx < origin.x || x - sx > origin.x + size.x) {
      return false;
    }

    if (y + sy < origin.y || y - sy > origin.y + size.y) {
      return false;
    }

    return true;
  }

}

#endif    /* PGE_APP_VIEWPORT_HXX */
