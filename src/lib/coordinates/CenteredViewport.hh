#ifndef    PGE_APP_CENTERED_VIEWPORT_HH
# define   PGE_APP_CENTERED_VIEWPORT_HH

# include <maths_utils/Vector2.hh>
# include "Viewport.hh"
# include "olcEngine.hh"

namespace pge {

  /// @brief - Defines a viewport from its center and size.
  template <typename Coordinate>
  class CenteredViewport: public Viewport<Coordinate> {
    private:
      using Vector = olc::v2d_generic<Coordinate>;

    public:

      /// @brief - Create a viewport with the specified size and center.
      /// The dimensions are spread equally on both sides of the center
      /// so the effective extent is from `center.x - dims.x / 2` to
      /// `center.x + dims.x / 2` and same along the `y` axis.
      /// @param center - the center of the viewport.
      /// @param dims - the dimensions of the viewport.
      CenteredViewport(const Vector& center,
                       const Vector& dims) noexcept;

      Vector
      center() const noexcept override;

      Vector
      topLeft() const noexcept override;

      Vector
      dims() const noexcept override;

      olc::vf2d
      relativeCoords(const Coordinate& x, const Coordinate& y) const noexcept override;

      olc::vf2d
      absoluteCoords(const Coordinate& x, const Coordinate& y) const noexcept override;

      void
      moveTo(const Vector& center) noexcept;

      /// @brief - Translates this viewport by the specified amount.
      /// @param delta - the delta to apply to the position of this
      /// viewport.
      void
      translate(const Vector& delta) noexcept;

      /// @brief  - Keeps the center constant but scales the dimensions
      /// by the specified factor.
      /// @param factor - the scale to apply on both axes.
      void
      scale(const Coordinate factor) noexcept;

      /// @brief  - Keeps the center constant but scales the dimensions
      /// by the specified factor.
      /// @param sx - the scale on the `x` axis.
      /// @param sy - the scale on the `y` axis.
      void
      scale(const Coordinate sx, const Coordinate sy) noexcept;

    private:

    private:

      /// @brief - The center of this viewport.
      Vector m_center;

      /// @brief - The dimensions of the viewport along each axis.
      Vector m_dims;
  };

  using CenteredViewportI = CenteredViewport<int>;
  using CenteredViewportF = CenteredViewport<float>;
}

# include "CenteredViewport.hxx"

#endif    /* PGE_APP_CENTERED_VIEWPORT_HH */
