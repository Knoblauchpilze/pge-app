
#include "GameOverScreenUiHandler.hh"
#include "ScreenCommon.hh"

namespace pge {

GameOverScreenUiHandler::GameOverScreenUiHandler()
  : IUiHandler("game_over")
{}

void GameOverScreenUiHandler::initializeMenus(const int width,
                                              const int height,
                                              sprites::TexturePack & /*texturesLoader*/)
{
  m_menu = generateDefaultColoredMenu(width, height, colors::BLANK);

  m_menu->addMenu(generateMenuOption("Back to main screen", Screen::HOME, colors::BRONZE));
  m_menu->addMenu(generateMenuOption("Restart", Screen::GAME, colors::BRONZE));
  m_menu->addMenu(generateMenuOption("Quit", Screen::EXIT, colors::BRONZE));
}

bool GameOverScreenUiHandler::processUserInput(UserInputData &inputData)
{
  return m_menu->processUserInput(inputData);
}

void GameOverScreenUiHandler::render(Renderer &engine) const
{
  m_menu->render(engine);
}

void GameOverScreenUiHandler::updateUi() {}

} // namespace pge
