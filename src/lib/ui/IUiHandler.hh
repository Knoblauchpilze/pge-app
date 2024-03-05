
#pragma once

#include "Controls.hh"
#include "CoordinateFrame.hh"
#include "Game.hh"
#include "UserInputData.hh"
#include <core_utils/CoreObject.hh>
#include <memory>

namespace pge {

class IUiHandler : public utils::CoreObject
{
  public:
  IUiHandler(const std::string &name);
  ~IUiHandler() override = default;

  virtual void initializeMenus(const int width,
                               const int height,
                               sprites::TexturePack &texturesLoader)
    = 0;
  virtual bool processUserInput(UserInputData &inputData) = 0;
  virtual void render(Renderer &engine) const             = 0;
  virtual void updateUi()                                 = 0;

  virtual void reset();
};

using IUiHandlerPtr = std::unique_ptr<IUiHandler>;

} // namespace pge
