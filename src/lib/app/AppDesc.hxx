#ifndef PGE_APP_APP_DESC_HXX
#define PGE_APP_APP_DESC_HXX

#include "AppDesc.hh"

namespace pge {

inline AppDesc newDesc(const olc::vi2d &dims,
                       CoordinateFramePtr cf,
                       const std::string &name) noexcept
{
  AppDesc ad;

  ad.dims     = dims;
  ad.pixRatio = olc::vi2d(1, 1);

  ad.name = name;

  ad.frame = cf;

  ad.fixedFrame = false;

  return ad;
}

} // namespace pge

#endif /* PGE_APP_APP_DESC_HXX */
