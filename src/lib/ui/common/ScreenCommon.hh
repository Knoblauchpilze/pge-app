
#pragma once

#include "Screen.hh"
#include "UiMenu.hh"

namespace pge {

auto generateDefaultColoredMenu(const int width, const int height, const Color &color) -> UiMenuPtr;
auto generateMenuOption(const std::string &text, const Screen screen, const Color &color)
  -> UiMenuPtr;

} // namespace pge
