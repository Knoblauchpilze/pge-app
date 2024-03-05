
#include "LoadGameScreenUiHandler.hh"
#include "ScreenCommon.hh"
#include "UiTextMenu.hh"
#include <filesystem>

namespace pge {

LoadGameScreenUiHandler::LoadGameScreenUiHandler()
  : IUiHandler("load_game")
{
  initialize();
}

namespace {
constexpr auto ENABLED_TEXT_COLOR   = colors::WHITE;
constexpr auto ENABLED_BUTTON_COLOR = colors::ULTRAMARINE;

constexpr auto DISABLED_TEXT_COLOR   = colors::GREY;
constexpr auto DISABLED_BUTTON_COLOR = colors::DARK_GREY;
} // namespace

void LoadGameScreenUiHandler::initializeMenus(const int width,
                                              const int height,
                                              sprites::TexturePack & /*texturesLoader*/)
{
  m_menu = generateDefaultColoredMenu(width, height, colors::BLANK);

  MenuConfig config{};
  auto bg = bgConfigFromColor(DISABLED_BUTTON_COLOR);

  auto text            = textConfigFromColor("Previous page", colors::WHITE);
  config.clickCallback = [this]() { onPreviousButtonClicked(); };
  auto prop            = std::make_unique<UiTextMenu>(config, bg, text);
  m_previousButton     = prop.get();
  m_menu->addMenu(std::move(prop));

  bg = bgConfigFromColor(colors::COBALT_BLUE);

  for (auto id = 0; id < m_gamesPerPage; ++id)
  {
    text                     = textConfigFromColor("", colors::WHITE);
    config.gameClickCallback = [this, id](Game &g) { onSavedGameSelected(id, g); };
    prop                     = std::make_unique<UiTextMenu>(config, bg, text);
    prop->setEnabled(false);

    m_savedGameEntries.push_back(prop.get());

    m_menu->addMenu(std::move(prop));
  }

  bg                   = bgConfigFromColor(DISABLED_BUTTON_COLOR);
  text                 = textConfigFromColor("Next page", DISABLED_TEXT_COLOR);
  config.clickCallback = [this]() { onNextButtonClicked(); };
  prop                 = std::make_unique<UiTextMenu>(config, bg, text);
  m_nextButton         = prop.get();

  m_menu->addMenu(std::move(prop));

  refreshSavedGames();
}

bool LoadGameScreenUiHandler::processUserInput(UserInputData &inputData)
{
  return m_menu->processUserInput(inputData);
}

void LoadGameScreenUiHandler::render(Renderer &engine) const
{
  m_menu->render(engine);
}

void LoadGameScreenUiHandler::updateUi() {}

namespace {
using DirIt = std::filesystem::directory_iterator;
} // namespace

void LoadGameScreenUiHandler::initialize()
{
  DirIt end{};
  DirIt it(m_saveDirectory);

  m_savedGames.clear();

  for (; it != end; ++it)
  {
    const auto dirEntry = *it;

    const auto path = dirEntry.path();

    const auto name           = path.filename();
    const auto stem           = path.stem();
    const auto maybeExtension = path.extension();

    if (maybeExtension.empty() || maybeExtension != m_extension)
    {
      continue;
    }

    if (stem.empty())
    {
      continue;
    }

    m_savedGames.push_back(SavedGame{.displayName = stem, .filePath = path});
  }

  std::sort(m_savedGames.begin(),
            m_savedGames.end(),
            [](const SavedGame &lhs, const SavedGame &rhs) {
              return lhs.displayName < rhs.displayName;
            });
}

void LoadGameScreenUiHandler::refreshSavedGames()
{
  const auto amountOfGamesLeft = static_cast<int>(m_savedGames.size()) - m_savedGameOffset;
  const auto maxSavedGameId    = std::min(amountOfGamesLeft, m_gamesPerPage);

  auto id = 0;
  for (; id < maxSavedGameId; ++id)
  {
    m_savedGameEntries[id]->setText(m_savedGames[m_savedGameOffset + id].displayName);
    m_savedGameEntries[id]->updateTextColor(colors::WHITE);
    m_savedGameEntries[id]->setEnabled(true);
  }

  for (; id < m_gamesPerPage; ++id)
  {
    m_savedGameEntries[id]->setText("");
    m_savedGameEntries[id]->setEnabled(false);
  }

  const auto hasPrevious = m_savedGameOffset > 0;
  m_previousButton->setEnabled(hasPrevious);
  m_previousButton->updateBgColor(hasPrevious ? ENABLED_BUTTON_COLOR : DISABLED_BUTTON_COLOR);
  m_previousButton->updateTextColor(hasPrevious ? ENABLED_TEXT_COLOR : DISABLED_TEXT_COLOR);

  const auto hasNext = m_savedGameOffset + m_gamesPerPage < static_cast<int>(m_savedGames.size());
  m_nextButton->setEnabled(hasNext);
  m_nextButton->updateBgColor(hasNext ? ENABLED_BUTTON_COLOR : DISABLED_BUTTON_COLOR);
  m_nextButton->updateTextColor(hasNext ? ENABLED_TEXT_COLOR : DISABLED_TEXT_COLOR);
}

void LoadGameScreenUiHandler::onPreviousButtonClicked()
{
  m_savedGameOffset -= std::min(m_savedGameOffset, m_gamesPerPage);
  refreshSavedGames();
}

void LoadGameScreenUiHandler::onNextButtonClicked()
{
  const auto amountOfGamesLeft = static_cast<int>(m_savedGames.size()) - m_savedGameOffset;
  m_savedGameOffset += std::min(amountOfGamesLeft, m_gamesPerPage);
  refreshSavedGames();
}

void LoadGameScreenUiHandler::onSavedGameSelected(const int index, Game &g)
{
  const auto finalOffset = m_savedGameOffset + index;
  if (finalOffset >= static_cast<int>(m_savedGames.size()))
  {
    return;
  }

  g.onSavedGameSelected(m_savedGames[finalOffset].filePath);
}

} // namespace pge