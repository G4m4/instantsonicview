/// @file common.h
/// @brief InstantSonicView common utilities header
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

#ifndef INSTANTSONICVIEW_SRC_COMMON_H_
#define INSTANTSONICVIEW_SRC_COMMON_H_

#include <cassert>

#include "instantsonicview/src/configuration.h"

namespace instantsonicview {

/// @brief Ignore unused variables
template<typename Type> void IGNORE(const Type&) {}

/// @brief Assume that the following condition is always true
/// (on some compilers, allows optimization)
#if(_COMPILER_MSVC)
  static inline void ASSUME(const bool condition) {_assume(condition);}
#elif(_COMPILER_GCC)
  static inline void ASSUME(const bool condition) {if (!(condition)) __builtin_unreachable();}
#else
  #define ASSUME(_condition_)
#endif  // _COMPILER_ ?

/// @brief Asserts condition == true
#if(_BUILD_CONFIGURATION_DEBUG)
  #define INSTANTSONICVIEW_ASSERT(_condition_) (assert((_condition_)))
#else
  // Maps to "assume" in release configuration for better optimization
  #define INSTANTSONICVIEW_ASSERT(_condition_) {::instantsonicview::ASSUME((_condition_));}
#endif

/// @brief Attribute for structures alignment
#if (_USE_SSE)
  #if (_COMPILER_MSVC)
    #define ALIGN __declspec(align(16))
  #else
    #define ALIGN __attribute__((aligned(16)))
  #endif
#else
  #define ALIGN
#endif  // (_USE_SSE)

}  // namespace instantsonicview

#endif  // INSTANTSONICVIEW_SRC_COMMON_H_
