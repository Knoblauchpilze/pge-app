
#pragma once

#include "CoordinateFrame.hh"
#include <eigen3/Eigen/Eigen>

namespace pge {

class TransformedViewFrame : public CoordinateFrame
{
  public:
  TransformedViewFrame(const CenteredViewport &tiles,
                       const Eigen::Matrix2f &transform,
                       const TopLeftViewport &pixels);

  protected:
  auto normalizedTilesToPixels(const Vec2f &tiles) const noexcept -> Vec2f override;
  auto normalizedPixelsToTiles(const Vec2f &pixels) const noexcept -> Vec2f override;

  private:
  /// @brief - The transformation matrix to convert from tiles space to pixels
  /// space. This doesn't take into consideration scaling and is meant to work
  /// in normalized coordinate space.
  Eigen::Matrix2f m_tilesToPixelsTransform;

  /// @brief - The inverse matrix from the previous one.
  Eigen::Matrix2f m_pixelsToTilesTransform;
};

} // namespace pge
