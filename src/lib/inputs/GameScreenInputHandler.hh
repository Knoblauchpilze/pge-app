
#pragma once

#include "IInputHandler.hh"

namespace pge {

class GameScreenInputHandler : public IInputHandler
{
  public:
  GameScreenInputHandler();
  ~GameScreenInputHandler() override = default;

  void processUserInput(const controls::State &controls, CoordinateFrame &frame) override;
  void performAction(float x, float y, const controls::State &controls) override;
};

} // namespace pge
