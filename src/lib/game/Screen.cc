
#include "Screen.hh"

namespace pge {

auto str(const Screen s) noexcept -> std::string
{
  switch (s)
  {
    case Screen::HOME:
      return "home";
    case Screen::LOAD_GAME:
      return "load_game";
    case Screen::GAME:
      return "game";
    case Screen::GAME_OVER:
      return "game_over";
    case Screen::EXIT:
      return "exit";
    default:
      return "unknown";
  }
}

} // namespace pge
