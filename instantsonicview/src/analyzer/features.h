/// @filename features.h
/// @brief List of available features through the analyzer
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

#ifndef INSTANTSONICVIEW_SRC_ANALYZER_FEATURES_H_
#define INSTANTSONICVIEW_SRC_ANALYZER_FEATURES_H_

#include <array>

#include "instantsonicview/src/common.h"
#include "instantsonicview/src/analyzer/feature_meta.h"

#include "externals/chartreuse/chartreuse/src/interface/analyzer.h"

namespace instantsonicview {
namespace analyzer {

using chartreuse::interface::kAvailableDescriptorsCount;

/// @brief Avalaible features metadata
const std::array<FeatureMeta, kAvailableDescriptorsCount> kFeaturesMeta = {{
  FeatureMeta(FeatureDisplayType::kLinear,
              "Audio Power",
              "Square power of the signal"),
  FeatureMeta(FeatureDisplayType::kLinear,
              "Audio Spectrum Centroid",
              "Gravity center of the signal spectrum"),
  FeatureMeta(FeatureDisplayType::kLinear,
              "Audio Spectrum Spread",
              "Spread around the gravity center of the signal spectrum"),
  FeatureMeta(FeatureDisplayType::kFrequency,
              "Audio Fundamental frequency",
              "Signal estimated fundamental frequency"),
  FeatureMeta(FeatureDisplayType::kLinear,
              "Audio Harmonicity",
              "Matching between the signal and its estimated combed version"),
}};

}  // namespace analyzer
}  // namespace instantsonicview

#endif  // INSTANTSONICVIEW_SRC_ANALYZER_FEATURES_H_
