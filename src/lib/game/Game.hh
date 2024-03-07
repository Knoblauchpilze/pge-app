
#pragma once

#include "Controls.hh"
#include "IInputHandler.hh"
#include "IRenderer.hh"
#include "IUiHandler.hh"
#include "RenderState.hh"
#include "Renderer.hh"
#include "RenderingPass.hh"
#include "Screen.hh"
#include <core_utils/CoreObject.hh>
#include <memory>
#include <unordered_map>

namespace pge {

class IRenderer;
using IRendererPtr = std::unique_ptr<IRenderer>;

class IUiHandler;
using IUiHandlerPtr = std::unique_ptr<IUiHandler>;

class IInputHandler;
using IInputHandlerPtr = std::unique_ptr<IInputHandler>;

class Game : public utils::CoreObject
{
  public:
  Game();
  ~Game() override = default;

  auto getScreen() const noexcept -> Screen;
  void setScreen(const Screen &screen);

  void generateRenderers(int width, int height, Renderer &engine);
  void generateInputHandlers();
  void generateUiHandlers(int width, int height, Renderer &engine);

  void processUserInput(const controls::State &controls, CoordinateFrame &frame);
  void render(const RenderState &state, const RenderingPass pass) const;

  /// @brief - Returns whether or not the game has been terminated. The game is
  /// terminated when the user wants to exit the app (usually).
  bool terminated() const noexcept;

  /// @brief - Forward the call to step one step ahead in time to the internal world.
  /// @param elapsedSeconds - the duration of the last frame in seconds.
  /// @param bool - `true` in case the game continues, and `false` otherwise (i.e. if
  /// the game is ended).
  bool step(float elapsedSeconds);

  void onSavedGameSelected(const std::string &filePath);

  private:
  /// @brief - Convenience information defining the state of the
  /// game. It includes information about whether the menus should
  /// be displayed and if the user actions should be interpreted
  /// or not.
  struct State
  {
    /// @brief - Defines the current screen selected in this game. Updated whenever
    /// the user takes action to change it.
    Screen screen{Screen::HOME};

    /// @brief - Whether the game was terminated (usually because the app was closed).
    bool terminated{false};
  };

  /// @brief - The definition of the game state.
  State m_state{};

  std::unordered_map<Screen, IRendererPtr> m_renderers{};
  std::unordered_map<Screen, IInputHandlerPtr> m_inputHandlers{};
  std::unordered_map<Screen, IUiHandlerPtr> m_uiHandlers{};

  /// @brief - Requests the game to be terminated. This is applied to the next
  /// iteration of the game loop.
  void terminate() noexcept;

  void resetUi();
};

using GameShPtr = std::shared_ptr<Game>;
} // namespace pge
