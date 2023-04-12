#ifndef    APP_HXX
# define   APP_HXX

# include "App.hh"
# include "Action.hh"

namespace pge {

  inline
  void
  App::drawSprite(const SpriteDesc& t, const CoordinateFrame& cf) {
    olc::vf2d p = cf.tilesToPixels(t.x, t.y);

    m_packs->draw(this, t.sprite, p, t.radius * cf.tileSize());
  }

  inline
  void
  App::drawRect(const SpriteDesc& t,
                const CoordinateFrame& cf)
  {
    olc::vf2d p = cf.tilesToPixels(t.x, t.y);
    FillRectDecal(p, t.radius * cf.tileSize(), t.sprite.tint);
  }

}

#endif    /* APP_HXX */
