#ifndef    COMMON_HH
# define   COMMON_HH

# include <olcEngine.hh>
# include <gtest/gtest.h>

namespace pge {

struct TestCase {
  std::string name;
  olc::vi2d coords;
  olc::vf2d expected;
};

}

#endif    /* COMMON_HH */
