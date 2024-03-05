
#pragma once

#include "IUiHandler.hh"
#include "UiMenu.hh"

namespace pge {

class GameOverScreenUiHandler : public IUiHandler
{
  public:
  GameOverScreenUiHandler();
  ~GameOverScreenUiHandler() override = default;

  void initializeMenus(const int width,
                       const int height,
                       sprites::TexturePack &texturesLoader) override;
  bool processUserInput(UserInputData &inputData) override;
  void render(Renderer &engine) const override;
  void updateUi() override;

  private:
  UiMenuPtr m_menu{};
};

} // namespace pge
