
#pragma once

#include <string>

namespace pge {

enum class Screen
{
  HOME,
  LOAD_GAME,
  GAME,
  GAME_OVER,
  EXIT
};

auto str(const Screen s) noexcept -> std::string;

} // namespace pge
