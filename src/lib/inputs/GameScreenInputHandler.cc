
#include "GameScreenInputHandler.hh"

namespace pge {

GameScreenInputHandler::GameScreenInputHandler()
  : IInputHandler("game")
{}

void GameScreenInputHandler::processUserInput(const controls::State & /*controls*/,
                                              CoordinateFrame & /*frame*/)
{}

void GameScreenInputHandler::performAction(float x, float y, const controls::State & /*state*/)
{
  info("Clicked at " + std::to_string(x) + "x" + std::to_string(y));
}

} // namespace pge
