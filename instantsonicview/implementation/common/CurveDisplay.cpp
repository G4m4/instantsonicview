/// @filename CurveDisplay.cpp
/// @brief InstantSonicView meter widgets manager
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


// This file is NOT generated by Juce (at least not after the first time),
// That's why we apply our coding style here

#include "instantsonicview/implementation/common/CurveDisplay.h"

#include "instantsonicview/implementation/plugin/vst/PluginProcessor.h"

CurveDisplay::CurveDisplay()
    : Component("CurveDisplay"),
      curves_() {
  setOpaque(true);
  clear();
}

void CurveDisplay::changeListenerCallback(ChangeBroadcaster* source) {
  repaint();
}

void CurveDisplay::clear() {
  curves_.clear();
}

void CurveDisplay::paint (Graphics& g) {
  g.fillAll(juce::Colours::black);
  juce::Random kRandomGenerator;
  Rectangle<int> area(getLocalBounds().removeFromTop(10));
  for (unsigned int curve_idx(0); curve_idx < curves_.size(); ++curve_idx) {
    const float kHue(kRandomGenerator.nextFloat());
    g.setColour(juce::Colour(kHue, 1.0f, 0.5f, 1.0f));
    g.drawText(juce::String(curve_idx),
               area.removeFromLeft(20),
               juce::Justification::centredLeft,
               true);
    g.strokePath(curves_[curve_idx], juce::PathStrokeType (2.0f));
  }
}

void CurveDisplay::createCurve(const juce::Array<float>& data) {
  const float kXFactor(static_cast<float>(getWidth()) / data.size());
  const float kYFactor(getHeight());
  juce::Path curve;
  curve.startNewSubPath(0.0f, getHeight());
  for (int idx(0); idx < data.size(); ++idx) {
    const juce::Point<float> kNewEndPoint(kXFactor * idx,
                                          (1.0f - data[idx]) * kYFactor);
    curve.lineTo(kNewEndPoint);
  }
  addCurve(curve);
}

void CurveDisplay::addCurve(juce::Path curve) {
  curves_.add(curve);
}
