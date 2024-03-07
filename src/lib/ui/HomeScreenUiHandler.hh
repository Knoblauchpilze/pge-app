
#pragma once

#include "IUiHandler.hh"
#include "UiMenu.hh"

namespace pge {

class HomeScreenUiHandler : public IUiHandler
{
  public:
  HomeScreenUiHandler();
  ~HomeScreenUiHandler() override = default;

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
