#ifndef PGE_APP_COORDINATE_FRAME_HH
#define PGE_APP_COORDINATE_FRAME_HH

#include "CenteredViewport.hh"
#include "TopLeftViewport.hh"
#include <core_utils/CoreObject.hh>
#include <memory>

namespace pge {

class CoordinateFrame : public utils::CoreObject
{
  public:
  /// @brief - Creates a new coordinate frame with the input pixel
  /// viewport and tiles viewport.
  /// @param cells - the visible area expressed in cells covered by
  /// this viewport.
  /// @param pixels - the pixels area representing the cells area.
  CoordinateFrame(const CenteredViewport &cells, const TopLeftViewport &pixels);

  /// @brief - Returns the current tile size for this viewport. It
  /// is computed from the ratio between the cells viewport and the
  /// pixels viewport.
  /// @return - the size of a cell in pixels.
  olc::vf2d tileSize() const noexcept;

  /// @brief - Returns the current viewport in cells.
  /// @return - the viewport of this coordinate frame in cells.
  virtual CenteredViewport cellsViewport() const noexcept = 0;

  /// @brief - Convert the input tile coordinates to the corresponding
  /// pixel position.
  /// @param x - x coordinate in tiles.
  /// @param y - y coordinate in tiles.
  /// @return - the pixel position for the input tile position.
  virtual olc::vf2d tilesToPixels(float x, float y) const noexcept = 0;

  /// @brief - Convert the input pixel coordinates to the corresponding
  /// tile coordinates.
  /// @param x - x coordinate in pixels.
  /// @param y - y coordinate in pixels.
  /// @return - the tile position for the input pixel position.
  virtual olc::vf2d pixelsToTiles(float x, float y) const noexcept = 0;

  /// @brief - Similar to the above method but convert the tiles position
  /// to an integer representation.
  /// @param pixels - pixels position to convert.
  /// @param intraTile - output argument storing the fractional tile part.
  /// @return - the integer tiles position.
  olc::vi2d pixelsToTiles(const olc::vi2d &pixels, olc::vf2d *intraTile = nullptr) const noexcept;

  /// @brief - Zoom on the specified position expressed in pixels
  /// coordinate frame. This will fix this position and make the
  /// rest of the viewport proportionally smaller while keeping
  /// the position at its current position in the pixels viewport.
  /// @param pos - the pixels position to fix.
  void zoomIn(const olc::vf2d &pos);

  /// @brief - Reverse operation to zoom out while still fixing
  /// the input position in pixels space.
  /// @param pos - the pixels position to fix.
  void zoomOut(const olc::vf2d &pos);

  /// @brief - Begin a translation of the coordinate frame started
  /// at the input position.
  /// @param origin - the origin represents where the translation
  /// started. This position will be kept constant during the
  /// translation process.
  void beginTranslation(const olc::vf2d &origin);

  /// @brief - Translate the coordinate frame. The input parameter
  /// represents the new position of the origin passed when calling
  /// the `beginTranslation` method.
  /// @param trackedOrigin - the new position of the origin.
  void translate(const olc::vf2d &trackedOrigin);

  private:
  /// @brief - Perform the zoom operation to fix the position in input (in
  /// pixels space) and changing the dimensions of the specified factor.
  /// @param factor - factor by which the dimensions of the viewports of
  /// this coordinate frame will be modified. If this value is smaller tha
  /// `1` then the zoom is a dezoom.
  /// @param pos - the position to fixe during the zoom process. Before and
  /// after the zoom operation this position will stay fixed.
  void zoom(float factor, const olc::vf2d &pos);

  olc::vf2d pixelsDistToCellsDist(const olc::vf2d &pixelsDist);

  /// @brief - Converts the distance in pixels to a distance in cells usinng the
  /// ratio between the size of a unit in pixels and cells space.
  /// @param dx - the delta along the x axis in pixels.
  /// @param dy - the delta along the y axis in pixels.
  /// @return - the distance expressed in cells.
  olc::vf2d pixelsDistToCellsDist(float dx, float dy);

  olc::vf2d cellsDistToPixelsDist(const olc::vf2d &cellsDist);

  /// @brief - Converts the distance in cells to a distance in pixels usinng the
  /// ratio between the size of a unit in cells and pixels space.
  /// @param dx - the delta along the x axis in cells.
  /// @param dy - the delta along the y axis in cells.
  /// @return - the distance expressed in pixels.
  olc::vf2d cellsDistToPixelsDist(float dx, float dy);

  protected:
  /// @brief - Define the viewport for this coordinate frame. It represent the
  /// area that is visible for now given the position of the camera. The viewport
  /// is expressed in cells and defined through its top left corner and dimensions.
  CenteredViewport m_cellsViewport;

  /// @brief - Define a similar element but for the pixels on screen. It is used
  /// to represent the pixels that can be displayed on the device. Computing the
  /// ratio between both viewport gives the size of a tile in pixels and we can
  /// deduce a scaling factor from the initial size of a tile.
  TopLeftViewport m_pixelsViewport;

  /// @brief - The origin of the translation (i.e. the pixels position when it
  /// started). Allows to compute the accumulated transform to apply to the world
  /// origin.
  olc::vf2d m_translationOrigin;

  /// @brief - Cached position of the top left corner of the pixels viewport
  /// when starting the translation. Once the translation is performed we are
  /// able to update the viewport accordingly.
  olc::vf2d m_cachedPOrigin;
};

using CoordinateFramePtr = std::shared_ptr<CoordinateFrame>;
} // namespace pge

#endif /* PGE_APP_COORDINATE_FRAME_HH */
