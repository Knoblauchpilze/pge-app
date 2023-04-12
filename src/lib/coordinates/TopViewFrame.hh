#ifndef    PGE_APP_TOP_VIEW_FRAME_HH
# define   PGE_APP_TOP_VIEW_FRAME_HH

# include "CoordinateFrame.hh"

namespace pge {

  class TopViewFrame: public CoordinateFrame {
    public:

      TopViewFrame(const CenteredViewportF& cells,
                   const TopLeftViewportF& pixels);

      CenteredViewportF
      cellsViewport() const noexcept override;

      olc::vf2d
      tilesToPixels(float x, float y) const noexcept override;

      olc::vf2d
      pixelsToTiles(float x, float y) const noexcept override;
  };

}

#endif    /* PGE_APP_TOP_VIEW_FRAME_HH */
