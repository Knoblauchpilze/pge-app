
#include "TransformedViewFrame.hh"

/// Links:
/// http://archive.gamedev.net/archive/reference/programming/features/mm4ihm/index.html
/// https://gamedev.stackexchange.com/questions/142784/how-do-you-transform-a-coordinate-system-from-cartesian-to-isometric
/// https://gamedev.stackexchange.com/questions/31113/how-can-i-improve-my-isometric-tile-picking-algorithm/31124#31124
/// https://stackoverflow.com/questions/21842814/mouse-position-to-isometric-tile-including-height

/// Promising:
/// https://pikuma.com/blog/isometric-projection-in-games

namespace pge {

TransformedViewFrame::TransformedViewFrame(const CenteredViewport &tiles,
                                           const Eigen::Matrix2f &transform,
                                           const TopLeftViewport &pixels)
  : CoordinateFrame(tiles, pixels)
{
  // Eigen uses clockwise rotations, so to rotate in the usual trigonometric
  // way we have to invert the angle.
  // https://eigen.tuxfamily.org/dox/classEigen_1_1Rotation2D.html
  Eigen::Rotation2Df theta(-3.14159f / 4.0f);

  m_tilesToPixelsTransform = theta.toRotationMatrix();
  m_pixelsToTilesTransform = m_tilesToPixelsTransform.inverse();
}

olc::vf2d TransformedViewFrame::tilesToPixels(float x, float y) const noexcept
{
  auto rel = m_tilesViewport.relativeCoords(x, y);
  // See TopViewFrame::pixelsToTiles.
  rel.x = (rel.x + 1.0f) / 2.0f;
  rel.y = (1.0f - rel.y) / 2.0f;

  Eigen::Vector2f transformed = m_tilesToPixelsTransform * Eigen::Vector2f{rel.x, rel.y};
  auto out                    = m_pixelsViewport.absoluteCoords(transformed(0), transformed(1));

  log("p: " + std::to_string(x) + "x" + std::to_string(y));
  log("rel: " + rel.str());
  std::stringstream str;
  str << m_tilesToPixelsTransform;
  log("mat: \n" + str.str());
  str.clear();
  log("transformed: " + std::to_string(transformed(0)) + "x" + std::to_string(transformed(1)));
  log("out: " + out.str());

  return out;
}

olc::vf2d TransformedViewFrame::pixelsToTiles(float x, float y) const noexcept
{
  olc::vf2d rel = m_pixelsViewport.relativeCoords(x, y);
  auto relSave  = rel;
  // See TopViewFrame::tilesToPixels.
  rel.x = 2.0f * rel.x - 1.0f;
  rel.y = 1.0f - 2.0f * rel.y;

  Eigen::Vector2f transformed = m_pixelsToTilesTransform * Eigen::Vector2f{rel.x, rel.y};
  auto out                    = m_tilesViewport.absoluteCoords(transformed(0), transformed(1));

  log("p: " + std::to_string(x) + "x" + std::to_string(y));
  log("relSave: " + relSave.str());
  log("rel: " + rel.str());
  std::stringstream str;
  str << m_tilesToPixelsTransform;
  log("mat: \n" + str.str());
  str.clear();
  log("transformed: " + std::to_string(transformed(0)) + "x" + std::to_string(transformed(1)));
  log("out: " + out.str());

  return out;
}

} // namespace pge
