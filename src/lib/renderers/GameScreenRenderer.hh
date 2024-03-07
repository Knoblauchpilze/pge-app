
#pragma once

#include "IRenderer.hh"

namespace pge {

class GameScreenRenderer : public IRenderer
{
  public:
  GameScreenRenderer();
  ~GameScreenRenderer() override = default;

  void loadResources(int width, int height, sprites::TexturePack &texturesLoader) override;
  void render(Renderer &engine, const RenderState &state, const RenderingPass pass) const override;

  private:
  sprites::PackId m_defaultTexturePackId{};
};

} // namespace pge
