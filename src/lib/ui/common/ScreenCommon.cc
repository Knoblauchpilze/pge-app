
#include "ScreenCommon.hh"
#include "Game.hh"
#include "UiTextMenu.hh"

namespace pge {

constexpr auto DEFAULT_MENU_TO_WINDOW_RATIO = 0.75;

auto generateDefaultColoredMenu(const int width, const int height, const Color &color) -> UiMenuPtr
{
  const Vec2i dims{
    static_cast<int>(DEFAULT_MENU_TO_WINDOW_RATIO * width),
    static_cast<int>(DEFAULT_MENU_TO_WINDOW_RATIO * height),
  };

  const Vec2i pos = (Vec2i{width, height} - dims) / 2;

  const MenuConfig config{.pos = pos, .dims = dims};
  const auto bg = bgConfigFromColor(color);

  return std::make_unique<UiMenu>(config, bg);
}

auto generateMenuOption(const std::string &text, const Screen screen, const Color &color)
  -> UiMenuPtr
{
  const MenuConfig config{.gameClickCallback = [screen](Game &g) { g.setScreen(screen); }};
  const auto bg       = bgConfigFromColor(color);
  const auto textConf = textConfigFromColor(text, colors::WHITE);

  return std::make_unique<UiTextMenu>(config, bg, textConf);
}

} // namespace pge
