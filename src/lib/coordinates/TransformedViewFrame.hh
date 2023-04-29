#ifndef PGE_APP_TRANSFORMED_VIEW_FRAME_HH
#define PGE_APP_TRANSFORMED_VIEW_FRAME_HH

#include "CoordinateFrame.hh"
#include <eigen3/Eigen/Eigen>

namespace pge {

class TransformedViewFrame : public CoordinateFrame
{
  public:
  TransformedViewFrame(const CenteredViewport &tiles,
                       const Eigen::Matrix2f &transform,
                       const TopLeftViewport &pixels);

  olc::vf2d tilesToPixels(float x, float y) const noexcept override;

  olc::vf2d pixelsToTiles(float x, float y) const noexcept override;

  private:
  /// @brief - The transformation matrix to convert from tiles space to pixels
  /// space. This doesn't take into consideration scaling and is meant to work
  /// in normalized coordinate space.
  Eigen::Matrix2f m_tilesToPixelsTransform;

  /// @brief - The inverse matrix from the previous one.
  Eigen::Matrix2f m_pixelsToTilesTransform;
};

} // namespace pge

#endif /* PGE_APP_TRANSFORMED_VIEW_FRAME_HH */
