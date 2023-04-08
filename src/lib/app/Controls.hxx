#ifndef    PGE_APP_CONTROLS_HXX
# define   PGE_APP_CONTROLS_HXX

# include "Controls.hh"

namespace pge {
  namespace controls {

    inline
    State
    newState() noexcept {
      State c;

      c.mPosX = 0;
      c.mPosY = 0;

      c.keys.resize(keys::KeysCount, false);
      c.buttons.resize(mouse::ButtonsCount, ButtonState::Free);

      c.tab = false;

      return c;
    }

  }
}

#endif    /* PGE_APP_CONTROLS_HXX */
