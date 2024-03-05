
#include "IsometricViewFrame.hh"
#include <numbers>

namespace pge {

// Eigen uses clockwise rotations, so to rotate in the usual trigonometric
// way we have to invert the angle.
// https://eigen.tuxfamily.org/dox/classEigen_1_1Rotation2D.html
IsometricViewFrame::IsometricViewFrame(const CenteredViewport &tiles, const TopLeftViewport &pixels)
  : TransformedViewFrame(tiles,
                         Eigen::Rotation2Df(-std::numbers::pi / 4.0f).toRotationMatrix(),
                         pixels)
{}

} // namespace pge
