
#pragma once

#include "IsometricViewFrame.hh"

namespace pge {

IsometricViewFrame::IsometricViewFrame(const CenteredViewport &tiles, const TopLeftViewport &pixels)
  :

  // Eigen uses clockwise rotations, so to rotate in the usual trigonometric
  // way we have to invert the angle.
  // https://eigen.tuxfamily.org/dox/classEigen_1_1Rotation2D.html
  TransformedViewFrame(tiles, Eigen::Rotation2Df(-3.14159f / 4.0f).toRotationMatrix(), pixels)
{}

} // namespace pge
