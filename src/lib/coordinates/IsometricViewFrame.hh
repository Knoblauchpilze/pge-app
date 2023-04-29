#ifndef PGE_APP_ISOMETRIC_VIEW_FRAME_HH
#define PGE_APP_ISOMETRIC_VIEW_FRAME_HH

#include "TransformedViewFrame.hh"
#include <eigen3/Eigen/Eigen>

namespace pge {

class IsometricViewFrame : public TransformedViewFrame
{
  public:
  IsometricViewFrame(const CenteredViewport &tiles, const TopLeftViewport &pixels);
};

} // namespace pge

#include "IsometricViewFrame.hxx"

#endif /* PGE_APP_ISOMETRIC_VIEW_FRAME_HH */
