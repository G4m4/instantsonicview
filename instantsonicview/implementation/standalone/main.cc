/// @file implementation/main.cc
/// @brief Implementation main entry point
/// @author gm
/// @copyright gm 2014
///
/// This file is part of InstantSonicView
///
/// InstantSonicView is free software: you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// InstantSonicView is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with InstantSonicView.  If not, see <http://www.gnu.org/licenses/>.

#include <cstdio>

#include "instantsonicview/src/common.h"
#include "instantsonicview/src/dummygroup/dummyclass.h"

/// @brief Main function, of course.
int main(int argc, char **argv) {
  instantsonicview::IGNORE(argc);
  instantsonicview::IGNORE(argv);

  const char* kText(instantsonicview::dummygroup::DummyClass().DoSomething());

  printf("Done: %s", kText);

  return 0;
}
