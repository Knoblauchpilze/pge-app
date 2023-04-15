#ifndef PGE_APP_VIEWPORT_HH
#define PGE_APP_VIEWPORT_HH

#include <maths_utils/Vector2.hh>
#include <memory>

#include "olcEngine.hh"

namespace pge {

template<typename Coordinate>
class Viewport
{
  private:
  using Vector = olc::v2d_generic<Coordinate>;

  public:
  /// @brief - Returns the center of this viewport.
  /// @return - the center of the viewport.
  virtual Vector center() const noexcept = 0;

  /// @brief - Returns the top left corner of this viewport.
  /// @return - the top left corner of the viewport.
  virtual Vector topLeft() const noexcept = 0;

  /// @brief - Returns the dimensions of the viewport.
  /// @return - the dimensions of the viewport.
  virtual Vector dims() const noexcept = 0;

  olc::vf2d relativeCoords(const Vector &pos) const noexcept;

  /// @brief - Returns the relative coordinates of the input position
  /// compared to this viewport. In this mode, the output coordinates
  /// range from `[0; 1]` when one axis is within the viewport.
  /// @param pos - the position to convert.
  /// @return - the relative coords for this position.
  virtual olc::vf2d relativeCoords(const Coordinate &x, const Coordinate &y) const noexcept = 0;

  olc::vf2d absoluteCoords(const olc::vf2d &pos) const noexcept;

  /// @brief - Returns the absolute coordinates of the input position
  /// compared to this viewport. In this mode, the input coordinates
  /// range from `[0; 1]` when one axis is within the viewport.
  /// @param pos - the position to convert.
  /// @return - the absolute coords for this position.
  virtual olc::vf2d absoluteCoords(const float x, const float y) const noexcept = 0;

  /// @brief - Moves this viewport to the new position. Depending
  /// on the semantic of the viewport it might have a different
  /// operation.
  /// @param center - the new position of the viewport.
  virtual void moveTo(const Vector &position) noexcept = 0;

  /// @brief - Translates this viewport by the specified amount.
  /// @param delta - the delta to apply to the position of this
  /// viewport.
  virtual void translate(const Vector &delta) noexcept = 0;

  /// @brief - Scales the dimensions of the viewport by the corresponding
  /// factor.
  /// @param sx - the factor to be applied on the `x` axis.
  /// @param sy - the factor to be applied on the `y` axis.
  virtual void scale(const Coordinate sx, const Coordinate sy) noexcept = 0;

  /// @brief - Whether an element having the specified coordinates and
  /// radius is visible in the viewport.
  /// Note: the radius is centered around the coordinates. The element
  /// extends from `[x - radius; x + radius]` and same for `y`.
  /// @param x - x coordinate of the point.
  /// @param y - y coordinate of the point.
  /// @param radius - the radius in both axis.
  /// @return - `true` if such an element is at least partially visible
  /// in the viewport.
  bool visible(const Coordinate x,
               const Coordinate y,
               const Coordinate radius = Coordinate(1)) const noexcept;

  /// @brief - Whether an element having the specified coordinates and
  /// radius is visible in the viewport.
  /// Note: the size is centered around the coordinates. The element
  /// extends from `[x - sz.x; x + sz.x]` and same for `y`.
  /// @param p - the position of the element.
  /// @param sz - the size of the element.
  /// @return - `true` if such an element is at least partially visible
  /// in the viewport.
  bool visible(const Vector &p,
               const Vector &sz = Vector(Coordinate(1), Coordinate(1))) const noexcept;

  private:
  /// @brief - Whether an element having the specified coordinates and
  /// size is visible in the viewport.
  /// Note: the size is centered around the coordinates. The element
  /// extends from `[x - sz.x; x + sz.x]` and same for `y`.
  /// @param x - the x cooridinate of the element.
  /// @param y - the y cooridinate of the element.
  /// @param sx - the radius of the element for the `x` axis.
  /// @param sy - the radius of the element for the `y` axis.
  /// @return - `true` if such an element is at least partially visible
  /// in the viewport.
  bool visible(const Coordinate &x,
               const Coordinate &y,
               const Coordinate &sx,
               const Coordinate &sy) const noexcept;
};

using ViewportI = Viewport<int>;
using ViewportF = Viewport<float>;

using ViewportIPtr = std::shared_ptr<ViewportI>;
using ViewportFPtr = std::shared_ptr<ViewportF>;
} // namespace pge

#include "Viewport.hxx"

#endif /* PGE_APP_VIEWPORT_HH */
