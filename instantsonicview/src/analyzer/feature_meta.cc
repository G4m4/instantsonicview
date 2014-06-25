/// @filename feature_meta.cc
/// @brief Feature "Meta" class implementation
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

#include "instantsonicview/src/analyzer/feature_meta.h"

namespace instantsonicview {
namespace analyzer {

FeatureMeta::FeatureMeta(const FeatureDisplayType::Type display_type,
                         const std::string& name,
                         const std::string& description)
    : display_type_(display_type),
      name_(name),
      description_(description) {
  // Nothing to do here for now
}

FeatureDisplayType::Type FeatureMeta::display_type(void) const {
  return display_type_;
}
const std::string& FeatureMeta::name(void) const {
  return name_;
}
const std::string& FeatureMeta::description(void) const {
  return description_;
}

}  // namespace analyzer
}  // namespace instantsonicview
