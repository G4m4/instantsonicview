/// @filename dcblock.h
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

#ifndef INSTANTSONICVIEW_SRC_ANALYZER_DCBLOCK_H_
#define INSTANTSONICVIEW_SRC_ANALYZER_DCBLOCK_H_

namespace instantsonicview {
namespace analyzer {

/// @brief DCBlock filter, a static (non adjustable) filter tailored to
/// cut all very low frequencies.
class DCBlock {
 public:
  explicit DCBlock();

  /// @brief Actual processing function
  float operator()(float sample);

  /// @brief Method to be explicitly called at each sample rate change
  void SetSampleRate(double sample_rate);

 private:
  /// @brief Compute internal coefficients
  void Design(double sample_rate);

  double coeff_;
  float history_;
};

}  // namespace analyzer
}  // namespace instantsonicview

#endif  // INSTANTSONICVIEW_SRC_ANALYZER_DCBLOCK_H_
