/// @filename dcblock.cc
/// @brief DC block filter class: remove very low frequency components
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

#include "instantsonicview/src/analyzer/dcblock.h"

#include "instantsonicview/src/common.h"

namespace instantsonicview {
namespace analyzer {

/// @brief Target gain bend frequency, e.g. -3dB at this frequency
static const double kCutOffFrequency(40.0f);

DCBlock::DCBlock()
    : coeff_(0.0),
      history_(0.0f) {
  // Nothing to do here for now
}

float DCBlock::operator()(float sample) {
  const float out(static_cast<float>(1.0 - coeff_) * sample
                  - static_cast<float>(coeff_ * history_));
  history_ = out;
  return out;
}

void DCBlock::SetSampleRate(double sample_rate) {
  INSTANTSONICVIEW_ASSERT(sample_rate > 0.0);
  Design(sample_rate);
}

void DCBlock::Design(double sample_rate) {
  coeff_ = 1.0 - (3.141592 * 2.0 * kCutOffFrequency / sample_rate);
}

}  // namespace analyzer
}  // namespace instantsonicview
