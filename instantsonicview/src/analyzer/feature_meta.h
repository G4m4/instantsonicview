/// @filename feature_meta.h
/// @brief Feature "Meta" class: handle feature metadata
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

#ifndef INSTANTSONICVIEW_SRC_ANALYZER_FEATURE_META_H_
#define INSTANTSONICVIEW_SRC_ANALYZER_FEATURE_META_H_

#include <string>

namespace instantsonicview {
namespace analyzer {

/// @brief Available feature display type
namespace FeatureDisplayType {
  enum Type {
    kLinear = 0,
    kLog,
    kFrequency,
    kCount
  };
}  // namespace FeatureDisplayType

/// @brief Feature metadata: holds a feature descriptor, e.g. everything
/// an external user needs to know in order to display a feature.
///
/// A feature is always a normalized floating point value,
/// and its descriptor cannot change!
class FeatureMeta {
 public:
  /// @brief Default constructor, allowing members initialisation
  explicit FeatureMeta(
    const FeatureDisplayType::Type display_type = FeatureDisplayType::kLinear,
    const std::string& name = "Name",
    const std::string& description = "Description");

  /// Getters

  FeatureDisplayType::Type display_type(void) const;
  const std::string& name(void) const;
  const std::string& description(void) const;

 private :
  // No assignment operator for this class
  FeatureMeta& operator=(const FeatureMeta& right);

  const FeatureDisplayType::Type display_type_;  ///< How to interpret the value
  const std::string name_;  ///< Parameter name - can be used in a maximized UI
  const std::string description_;  ///< Thorough information about what
                             /// the parameter actually does
};

}  // namespace analyzer
}  // namespace instantsonicview

#endif  // INSTANTSONICVIEW_SRC_ANALYZER_FEATURE_META_H_
