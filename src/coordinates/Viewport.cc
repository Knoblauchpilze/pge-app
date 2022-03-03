
# include "Viewport.hh"

namespace pge {

  Viewport::Viewport(const olc::vf2d& tl,
                     const olc::vf2d& dims) noexcept:
    m_tl(tl),
    m_dims(dims)
  {}

  olc::vf2d&
  Viewport::topLeft() noexcept {
    return m_tl;
  }

  const olc::vf2d&
  Viewport::topLeft() const noexcept {
    return m_tl;
  }

  olc::vf2d&
  Viewport::dims() noexcept {
    return m_dims;
  }

  const olc::vf2d&
  Viewport::dims() const noexcept {
    return m_dims;
  }

  bool
  Viewport::visible(const utils::Point2i& p, float radius) const noexcept {
    // Compute bounds for the viewport.
    olc::vf2d min = m_tl;
    olc::vf2d max = m_tl + m_dims;

    // If the element is fully out of the x span
    // or out of the y span, then it is not visible.
    if (p.x() + radius < min.x || p.x() - radius > max.x) {
      return false;
    }

    if (p.y() + radius < min.y || p.y() - radius > max.y) {
      return false;
    }

    return true;
  }

}
