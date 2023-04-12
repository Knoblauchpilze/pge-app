#ifndef    PGE_APP_TOP_LEFT_VIEWPORT_HH
# define   PGE_APP_TOP_LEFT_VIEWPORT_HH

# include <maths_utils/Vector2.hh>
# include "Viewport.hh"
# include "olcEngine.hh"

namespace pge {

  /// @brief - Defines a viewport from its top left corner and size.
  template <typename Coordinate>
  class TopLeftViewport: public Viewport<Coordinate> {
    private:
      using Vector = olc::v2d_generic<Coordinate>;

    public:

      /// @brief - Create a viewport with the specified size and top
      /// left corner.
      TopLeftViewport(const Vector& tl,
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

      /// @brief - Moves the reference corner of this viewport to
      /// the new position.
      /// @param topLeft - the new position of the reference corner
      /// for this viewport.
      void
      moveTo(const Vector& topLeft) noexcept;

      /// @brief - Translates this viewport by the specified amount.
      /// @param delta - the delta to apply to the position of this
      /// viewport.
      void
      translate(const Vector& delta) noexcept;

      /// @brief  - Keeps the reference corner constant but scales
      /// the dimensions by the specified factor.
      /// @param factor - the scale to apply on both axes.
      void
      scale(const Coordinate factor) noexcept;

      /// @brief  - Keeps the reference corner constant but scales
      /// the dimensions by the specified factor.
      /// @param sx - the scale on the `x` axis.
      /// @param sy - the scale on the `y` axis.
      void
      scale(const Coordinate sx, const Coordinate sy) noexcept;

    private:

      /// @brief - The top left corner of this viewport.
      Vector m_topLeft;

      /// @brief - The dimensions of the view along each axis.
      Vector m_dims;
  };

  using TopLeftViewportI = TopLeftViewport<int>;
  using TopLeftViewportF = TopLeftViewport<float>;
}

# include "TopLeftViewport.hxx"

#endif    /* PGE_APP_TOP_LEFT_VIEWPORT_HH */
