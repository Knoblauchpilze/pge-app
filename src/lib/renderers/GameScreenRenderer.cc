
#include "GameScreenRenderer.hh"
#include "ScreenCommon.hh"

namespace pge {

GameScreenRenderer::GameScreenRenderer()
  : IRenderer("game")
{}

namespace {
constexpr auto WIDTH_IN_TILES  = 8;
constexpr auto HEIGHT_IN_TILES = 13;
} // namespace

void GameScreenRenderer::loadResources(int /*width*/,
                                       int /*height*/,
                                       sprites::TexturePack &texturesLoader)
{
  const auto pack = sprites::PackDesc{.file = "data/tiles/default.png",
                                      .sSize{16, 16},
                                      .layout{WIDTH_IN_TILES, HEIGHT_IN_TILES}};

  m_defaultTexturePackId = texturesLoader.registerPack(pack);
}

void GameScreenRenderer::render(Renderer &engine,
                                const RenderState &state,
                                const RenderingPass pass) const
{
  if (pass != RenderingPass::DECAL)
  {
    return;
  }

  for (int y = 0; y < HEIGHT_IN_TILES; ++y)
  {
    const auto interpL = colorGradient(colors::BLUE,
                                       colors::RED,
                                       1.0f * y / HEIGHT_IN_TILES,
                                       alpha::OPAQUE);
    const auto interpR = colorGradient(colors::YELLOW,
                                       colors::GREEN,
                                       1.0f * y / HEIGHT_IN_TILES,
                                       alpha::OPAQUE);

    for (int x = 0; x < WIDTH_IN_TILES; ++x)
    {
      SpriteDesc t;
      t.xTiles = x;
      t.yTiles = y;

      t.radius = 1.0f;

      t.sprite.pack   = m_defaultTexturePackId;
      t.sprite.sprite = {x, y};
      t.sprite.tint   = colorGradient(interpL, interpR, 1.0f * x / HEIGHT_IN_TILES, alpha::OPAQUE);

      engine.drawWarpedSprite(t, state.frame);
    }
  }
}

} // namespace pge
