#ifndef COMMON_HH
#define COMMON_HH

#include <Viewport.hh>
#include <gtest/gtest.h>
#include <olcEngine.hh>

namespace pge {

using ViewportIGenerator = std::function<ViewportIPtr()>;

struct TestCaseRelative
{
  std::string name;
  ViewportIGenerator generator;

  olc::vi2d coords;
  olc::vf2d expected;
};

using RelativeCoordinates = ::testing::TestWithParam<TestCaseRelative>;

auto generateTestNameRelative(const ::testing::TestParamInfo<TestCaseRelative> &info)
  -> std::string;

struct TestCaseAbsolute
{
  std::string name;
  ViewportIGenerator generator;

  olc::vf2d coords;
  olc::vi2d expected;
};

using AbsoluteCoordinates = ::testing::TestWithParam<TestCaseAbsolute>;

auto generateTestNameAbsolute(const ::testing::TestParamInfo<TestCaseAbsolute> &info)
  -> std::string;

} // namespace pge

#endif /* COMMON_HH */
