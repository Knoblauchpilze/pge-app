#ifndef PGE_APP_TOP_VIEW_FRAME_HH
#define PGE_APP_TOP_VIEW_FRAME_HH

#include "CoordinateFrame.hh"

namespace pge {

class TopViewFrame : public CoordinateFrame
{
  public:
  TopViewFrame(const CenteredViewport &cells, const TopLeftViewport &pixels);

  CenteredViewport cellsViewport() const noexcept override;

  olc::vf2d tilesToPixels(float x, float y) const noexcept override;

  olc::vf2d pixelsToTiles(float x, float y) const noexcept override;
};

} // namespace pge

#endif /* PGE_APP_TOP_VIEW_FRAME_HH */
