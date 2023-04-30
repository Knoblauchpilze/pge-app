
#pragma once

#include <CoordinateFrame.hh>
#include <Viewport.hh>
#include <gtest/gtest.h>
#include <olcEngine.hh>
#include <optional>

namespace pge {

using ViewportGenerator = std::function<ViewportPtr()>;

struct TestCaseRelative
{
  std::string name;
  ViewportGenerator generator;

  olc::vf2d coords;
  olc::vf2d expected;
};

using RelativeCoordinates = ::testing::TestWithParam<TestCaseRelative>;

auto generateTestNameRelative(const ::testing::TestParamInfo<TestCaseRelative> &info)
  -> std::string;

struct TestCaseAbsolute
{
  std::string name;
  ViewportGenerator generator;

  olc::vf2d coords;
  olc::vf2d expected;
};

using AbsoluteCoordinates = ::testing::TestWithParam<TestCaseAbsolute>;

auto generateTestNameAbsolute(const ::testing::TestParamInfo<TestCaseAbsolute> &info)
  -> std::string;

struct TestCaseVisibility
{
  std::string name;
  ViewportGenerator generator;

  olc::vf2d coords;
  bool expectedVisibility;
};

using Visibility = ::testing::TestWithParam<TestCaseVisibility>;

auto generateTestNameVisibility(const ::testing::TestParamInfo<TestCaseVisibility> &info)
  -> std::string;

struct TestCaseTilesToPixels
{
  std::string name;
  CoordinateFramePtr frame;

  olc::vf2d tiles;
  olc::vf2d expected;
  std::optional<float> tolerance{std::nullopt};
};

using TilesToPixels = ::testing::TestWithParam<TestCaseTilesToPixels>;

auto generateTestNameTilesToPixels(const ::testing::TestParamInfo<TestCaseTilesToPixels> &info)
  -> std::string;

struct TestCasePixelsToTiles
{
  std::string name;
  CoordinateFramePtr frame;

  olc::vf2d pixels;
  olc::vf2d expected;
  std::optional<float> tolerance{std::nullopt};
};

using PixelsToTiles = ::testing::TestWithParam<TestCasePixelsToTiles>;

auto generateTestNamePixelsToTiles(const ::testing::TestParamInfo<TestCasePixelsToTiles> &info)
  -> std::string;

} // namespace pge
