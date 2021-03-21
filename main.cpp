
/**
 * @brief - Canonical application allowing to instantiate
 *          a working PGE process with configurable hooks
 *          to customize the behavior.
 */

# include <core_utils/StdLogger.hh>
# include <core_utils/LoggerLocator.hh>
# include <core_utils/CoreException.hh>
# include "AppDesc.hh"
# include "TopViewFrame.hh"
# include "DefaultApp.hh"

int main(int /*argc*/, char** /*argv*/) {
  // Create the logger.
  utils::StdLogger logger;
  utils::LoggerLocator::provide(&logger);

  logger.setLevel(utils::Level::Debug);

  const std::string service("tdef");
  const std::string module("main");

  try {
    utils::LoggerLocator::getLogger().logMessage(
      utils::Level::Notice,
      std::string("Starting application"),
      module,
      service
    );

    pge::Viewport tViewport = pge::newViewport(olc::vf2d(-6.0f, -5.0f), olc::vf2d(20.0f, 15.0f));
    pge::Viewport pViewport = pge::newViewport(olc::vf2d(10.0f, 50.0f), olc::vf2d(800.0f, 600.0f));

    pge::CoordinateFrameShPtr cf = std::make_shared<pge::TopViewFrame>(
      tViewport,
      pViewport,
      olc::vi2d(64, 64)
    );
    pge::AppDesc ad = pge::newDesc(
      olc::vi2d(800, 600),
      cf,
      "pge app"
    );
    pge::DefaultApp demo(ad);

    demo.Start();
  }
  catch (const utils::CoreException& e) {
    utils::LoggerLocator::getLogger().logMessage(
      utils::Level::Critical,
      std::string("Caught internal exception while setting up application"),
      module,
      service,
      e.what()
    );
  }
  catch (const std::exception& e) {
    utils::LoggerLocator::getLogger().logMessage(
      utils::Level::Critical,
      std::string("Caught exception while setting up application"),
      module,
      service,
      e.what()
    );
  }
  catch (...) {
    utils::LoggerLocator::getLogger().logMessage(
      utils::Level::Critical,
      std::string("Unexpected error while setting up application"),
      module,
      service
    );
  }

  return EXIT_SUCCESS;
}
