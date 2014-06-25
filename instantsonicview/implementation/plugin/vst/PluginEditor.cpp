/// @filename PluginEditor.cpp
/// @brief InstantSonicView plugin editor (UI & control)
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

#include "instantsonicview/implementation/plugin/vst/PluginEditor.h"

#include "instantsonicview/src/common.h"
#include "instantsonicview/src/analyzer/features.h"

InstantSonicViewAudioProcessorEditor::InstantSonicViewAudioProcessorEditor(
    InstantSonicViewAudioProcessor* owner)
    : AudioProcessorEditor(owner),
      widgets_manager_(instantsonicview::analyzer::kFeaturesMeta),
      debug_infos_() {
  addAndMakeVisible(&widgets_manager_);
  // TODO(gm): this is not normal,
  // plus adding/removing change listeners should be done in the same class
  addChangeListener(&widgets_manager_);

  // DEBUG
  addAndMakeVisible(&debug_infos_);
  this->startTimer(kTimerInterval);
  //  /DEBUG

  getProcessor()->addChangeListener(this);
  // This is where our plugin's editor size is set.
  setSize(kMainWindowSizeX, kMainWindowSizeY);
}

InstantSonicViewAudioProcessorEditor::~InstantSonicViewAudioProcessorEditor() {
  getProcessor()->removeChangeListener(this);
}

void InstantSonicViewAudioProcessorEditor::paint(juce::Graphics& g) {
  g.fillAll(Colours::white);
  widgets_manager_.setBounds(0, 0, this->getWidth(), this->getHeight());

  // DEBUG
  debug_infos_.setBounds(0, 500, this->getWidth(), 100);
  //  /DEBUG
}

void InstantSonicViewAudioProcessorEditor::changeListenerCallback(
    juce::ChangeBroadcaster *source) {
  InstantSonicViewAudioProcessor* proc(getProcessor());
  // No other change broacaster than the processor for now!
  INSTANTSONICVIEW_ASSERT(source == proc);
  // Inform all UI subcomponents of any change
  sendChangeMessage();
}

void InstantSonicViewAudioProcessorEditor::timerCallback() {
  const double time(getProcessor()->GetLastProcessTime());
  debug_infos_.setText(juce::String(time));
}

float InstantSonicViewAudioProcessorEditor::GetParamValue(const int param_id) {
  return getProcessor()->getParameter(param_id);
}

void InstantSonicViewAudioProcessorEditor::ParamValueChanged(const int param_id,
                                                     const float value) {
  getProcessor()->setParameterNotifyingHost(param_id, value);
}

void InstantSonicViewAudioProcessorEditor::ParamGestureBegan(const int param_id) {
  getProcessor()->beginParameterChangeGesture(param_id);
}

void InstantSonicViewAudioProcessorEditor::ParamGestureEnded(const int param_id) {
  getProcessor()->endParameterChangeGesture(param_id);
}

InstantSonicViewAudioProcessor* InstantSonicViewAudioProcessorEditor::getProcessor() const {
  return static_cast<InstantSonicViewAudioProcessor*>(getAudioProcessor());
}
