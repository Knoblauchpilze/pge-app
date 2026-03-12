
/// @brief - A minimalistic implementation for an app using the PixelGameEngine.

#include "App.hh"
#include "AppDesc.hh"
#include "CoreException.hh"
#include "IsometricViewFrame.hh"
#include "log/Locator.hh"
#include "log/PrefixedLogger.hh"
#include "log/StdLogger.hh"

int main(int /*argc*/, char ** /*argv*/)
{
  core::log::StdLogger raw;
  raw.setLevel(core::log::Severity::DEBUG);
  core::log::PrefixedLogger logger("pge", "main");
  core::log::Locator::provide(&raw);

  try
  {
    logger.notice("Starting application");

    auto tiles  = pge::CenteredViewport({0.0f, 0.0f}, {16.0f, 12.0f});
    auto pixels = pge::TopLeftViewport({0.0f, 0.0f}, {800.0f, 600.0f});

    pge::AppDesc desc{.dims       = pge::Vec2i{800, 600},
                      .frame      = std::make_unique<pge::IsometricViewFrame>(tiles, pixels),
                      .name       = "pge-app",
                      .fixedFrame = false,
                      .maxFps     = 50};
    pge::App demo(std::move(desc));

    demo.run();
  }
  catch (const core::CoreException &e)
  {
    logger.error("Caught internal exception while setting up application", e.what());
    return EXIT_FAILURE;
  }
  catch (const std::exception &e)
  {
    logger.error("Caught internal exception while setting up application", e.what());
    return EXIT_FAILURE;
  }
  catch (...)
  {
    logger.error("Unexpected error while setting up application");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
