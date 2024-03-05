
#include "HomeScreenUiHandler.hh"
#include "ScreenCommon.hh"

namespace pge {

HomeScreenUiHandler::HomeScreenUiHandler()
  : IUiHandler("home")
{}

void HomeScreenUiHandler::initializeMenus(const int width,
                                          const int height,
                                          sprites::TexturePack & /*texturesLoader*/)
{
  m_menu = generateDefaultColoredMenu(width, height, colors::BLANK);

  m_menu->addMenu(generateMenuOption("New game", Screen::GAME, colors::AMETHYST));
  m_menu->addMenu(generateMenuOption("Load game", Screen::LOAD_GAME, colors::AMETHYST));
  m_menu->addMenu(generateMenuOption("Quit", Screen::EXIT, colors::AMETHYST));
}

bool HomeScreenUiHandler::processUserInput(UserInputData &inputData)
{
  return m_menu->processUserInput(inputData);
}

void HomeScreenUiHandler::render(Renderer &engine) const
{
  m_menu->render(engine);
}

void HomeScreenUiHandler::updateUi() {}

} // namespace pge
