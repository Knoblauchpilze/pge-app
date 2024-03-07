
#pragma once

#include "IUiHandler.hh"
#include "UiTextMenu.hh"

namespace pge {

class LoadGameScreenUiHandler : public IUiHandler
{
  public:
  LoadGameScreenUiHandler();
  ~LoadGameScreenUiHandler() override = default;

  void initializeMenus(const int width,
                       const int height,
                       sprites::TexturePack &texturesLoader) override;
  bool processUserInput(UserInputData &inputData) override;
  void render(Renderer &engine) const override;
  void updateUi() override;

  private:
  UiMenuPtr m_menu{};

  int m_gamesPerPage{10};
  std::string m_saveDirectory{"data/saves"};
  std::string m_extension{".ext"};

  struct SavedGame
  {
    std::string displayName{};
    std::string filePath{};
  };

  std::vector<SavedGame> m_savedGames{};
  int m_savedGameOffset{0};
  std::vector<UiTextMenu *> m_savedGameEntries{};

  UiTextMenu *m_previousButton{};
  UiTextMenu *m_nextButton{};

  void initialize();

  void refreshSavedGames();

  void onPreviousButtonClicked();
  void onNextButtonClicked();
  void onSavedGameSelected(const int index, Game &g);
};

} // namespace pge
