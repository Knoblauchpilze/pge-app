
#include "Common.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge {

TEST_P(RelativeCoordinates, Test)
{
  const auto param = GetParam();

  const auto viewport = param.generator();
  ASSERT_NE(nullptr, viewport);

  auto p = viewport->relativeCoords(param.coords.x, param.coords.y);

  EXPECT_FLOAT_EQ(param.expected.x, p.x);
  EXPECT_FLOAT_EQ(param.expected.y, p.y);
}

auto generateTestNameRelative(const TestParamInfo<TestCaseRelative> &info) -> std::string
{
  return info.param.name;
}

TEST_P(AbsoluteCoordinates, Test)
{
  const auto param = GetParam();

  const auto viewport = param.generator();
  ASSERT_NE(nullptr, viewport);

  auto p = viewport->absoluteCoords(param.coords.x, param.coords.y);

  EXPECT_FLOAT_EQ(param.expected.x, p.x);
  EXPECT_FLOAT_EQ(param.expected.y, p.y);
}

auto generateTestNameAbsolute(const TestParamInfo<TestCaseAbsolute> &info) -> std::string
{
  return info.param.name;
}

TEST_P(Visibility, Test)
{
  const auto param = GetParam();

  const auto viewport = param.generator();
  ASSERT_NE(nullptr, viewport);

  auto visible = viewport->visible(param.coords.x, param.coords.y);

  EXPECT_EQ(param.expectedVisibility, visible);
}

auto generateTestNameVisibility(const ::testing::TestParamInfo<TestCaseVisibility> &info)
  -> std::string
{
  return info.param.name;
}

TEST_P(TilesToPixels, Test)
{
  const auto param = GetParam();

  olc::vf2d pixels = param.frame->tilesToPixels(param.tiles.x, param.tiles.y);
  EXPECT_EQ(param.expected, pixels);
}

auto generateTestNameTilesToPixels(const ::testing::TestParamInfo<TestCaseTilesToPixels> &info)
  -> std::string
{
  return info.param.name;
}

TEST_P(PixelsToTiles, Test)
{
  const auto param = GetParam();

  olc::vf2d tiles = param.frame->pixelsToTiles(param.pixels.x, param.pixels.y);
  EXPECT_EQ(param.expected, tiles);
}

auto generateTestNamePixelsToTiles(const ::testing::TestParamInfo<TestCasePixelsToTiles> &info)
  -> std::string
{
  return info.param.name;
}

} // namespace pge