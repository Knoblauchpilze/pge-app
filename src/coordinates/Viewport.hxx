#ifndef    VIEWPORT_HXX
# define   VIEWPORT_HXX

# include "Viewport.hh"

namespace pge {

  inline
  Viewport
  newViewport(const olc::vf2d& origin,
              const olc::vf2d& size) noexcept
  {
    return Viewport{origin, size};
  }

}

#endif    /* VIEWPORT_HXX */
