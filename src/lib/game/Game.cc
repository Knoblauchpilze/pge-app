
#include "Game.hh"

#include "GameScreenInputHandler.hh"
#include "GameScreenRenderer.hh"

#include "GameOverScreenUiHandler.hh"
#include "HomeScreenUiHandler.hh"
#include "LoadGameScreenUiHandler.hh"

namespace pge {

Game::Game()
  : utils::CoreObject("game")
{
  setService("game");
}

auto Game::getScreen() const noexcept -> Screen
{
  return m_state.screen;
}

void Game::setScreen(const Screen &screen)
{
  info("Set screen to " + str(screen));

  const auto ui = m_uiHandlers.find(screen);
  if (ui != m_uiHandlers.cend())
  {
    ui->second->reset();
  }

  m_state.screen = screen;
  if (m_state.screen == Screen::EXIT)
  {
    terminate();
  }
}

void Game::generateRenderers(int width, int height, Renderer &engine)
{
  auto game = std::make_unique<GameScreenRenderer>();
  game->loadResources(width, height, engine.getTextureHandler());
  m_renderers[Screen::GAME] = std::move(game);
}

void Game::generateInputHandlers()
{
  m_inputHandlers[Screen::GAME] = std::make_unique<GameScreenInputHandler>();
}

void Game::generateUiHandlers(int width, int height, Renderer &engine)
{
  m_uiHandlers[Screen::HOME]      = std::make_unique<HomeScreenUiHandler>();
  m_uiHandlers[Screen::LOAD_GAME] = std::make_unique<LoadGameScreenUiHandler>();
  m_uiHandlers[Screen::GAME_OVER] = std::make_unique<GameOverScreenUiHandler>();

  for (const auto &[_, handler] : m_uiHandlers)
  {
    handler->initializeMenus(width, height, engine.getTextureHandler());
  }
}

namespace {
bool applyUserInputToUi(const controls::State &controls,
                        const Screen currentScreen,
                        Game &g,
                        const std::unordered_map<Screen, IUiHandlerPtr> &uiHandlers)
{
  UserInputData uid{.controls = controls};
  bool userInputRelevant{false};
  const auto uiHandler = uiHandlers.find(currentScreen);
  if (uiHandler != uiHandlers.end())
  {
    userInputRelevant = uiHandler->second->processUserInput(uid);

    for (const auto &action : uid.actions)
    {
      action(g);
    }
  }

  return userInputRelevant;
}
} // namespace

void Game::processUserInput(const controls::State &controls, CoordinateFrame &frame)
{
  const auto maybeInputHandler = m_inputHandlers.find(getScreen());
  const auto inputHandlerExist = maybeInputHandler != m_inputHandlers.cend();
  if (inputHandlerExist)
  {
    maybeInputHandler->second->processUserInput(controls, frame);
  }

  const auto inputRelevantForUi = applyUserInputToUi(controls, getScreen(), *this, m_uiHandlers);

  if (!inputRelevantForUi && inputHandlerExist && controls.released(controls::mouse::LEFT))
  {
    Vec2f it;
    const auto tp = frame.pixelsToTilesAndIntra(Vec2f(controls.mPosX, controls.mPosY), &it);
    maybeInputHandler->second->performAction(tp.x + it.x, tp.y + it.y, controls);
  }
}

void Game::render(const RenderState &state, const RenderingPass pass) const
{
  const auto itRenderer = m_renderers.find(getScreen());
  const auto itUi       = m_uiHandlers.find(getScreen());

  switch (pass)
  {
    case RenderingPass::SPRITES:
      break;
    case RenderingPass::DECAL:
      if (itRenderer != m_renderers.end())
      {
        itRenderer->second->render(state.renderer, state, pass);
      }
      break;
    case RenderingPass::UI:
      if (itUi != m_uiHandlers.end())
      {
        itUi->second->render(state.renderer);
      }
      break;
    case RenderingPass::DEBUG:
      if (itRenderer != m_renderers.end())
      {
        itRenderer->second->render(state.renderer, state, pass);
      }
      break;
    default:
      warn("Unknown rendering pass " + str(pass));
      break;
  }
}

void Game::terminate() noexcept
{
  info("Game has been terminated");
  m_state.terminated = true;
}

bool Game::terminated() const noexcept
{
  return m_state.terminated;
}

bool Game::step(float /*elapsedSeconds*/)
{
  const auto it = m_uiHandlers.find(m_state.screen);
  if (it != m_uiHandlers.end())
  {
    it->second->updateUi();
  }

  return true;
}

void Game::onSavedGameSelected(const std::string &filePath)
{
  info("Picked game \"" + filePath + "\"");
  setScreen(Screen::GAME);
}

void Game::resetUi()
{
  for (const auto &[_, handler] : m_uiHandlers)
  {
    handler->reset();
  }
}

} // namespace pge
