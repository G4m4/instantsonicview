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
      curve_display_(),
      audio_display_(),
      recordingThumbnail(),
      recordButton("Record"),
      replayButton("Replay"),
      analyzeButton("Analyze"),
      nextSampleNum(0),
      was_replaying_(false),
      analyzed_(false),
      debug_infos_() {
  addAndMakeVisible(&curve_display_);
  addChangeListener(&curve_display_);

  addAndMakeVisible(&audio_display_);
  getProcessor()->addChangeListener(&audio_display_);

  addAndMakeVisible (recordingThumbnail);

  addAndMakeVisible (recordButton);
  recordButton.addListener (this);
  recordButton.setColour (TextButton::buttonColourId, Colour (0xffff5c5c));
  recordButton.setColour (TextButton::textColourOnId, Colours::black);

  addAndMakeVisible (replayButton);
  replayButton.addListener (this);
  replayButton.setColour (TextButton::buttonColourId, Colour (0xffff5c5c));
  replayButton.setColour (TextButton::textColourOnId, Colours::black);

  addAndMakeVisible(analyzeButton);
  analyzeButton.addListener (this);
  analyzeButton.setColour (TextButton::buttonColourId, Colour (0xffff5c5c));
  analyzeButton.setColour (TextButton::textColourOnId, Colours::black);

  // DEBUG
  addAndMakeVisible(&debug_infos_);
  this->startTimer(kTimerInterval);
  //  /DEBUG

  getProcessor()->addChangeListener(this);
  // This is where our plugin's editor size is set.
  setSize(kMainWindowSizeX, kMainWindowSizeY);
}

InstantSonicViewAudioProcessorEditor::~InstantSonicViewAudioProcessorEditor() {
  removeChangeListener(&curve_display_);
  getProcessor()->removeChangeListener(&audio_display_);
  getProcessor()->removeChangeListener(this);
}

void InstantSonicViewAudioProcessorEditor::paint(juce::Graphics& g) {
  g.fillAll(Colours::white);
}

void InstantSonicViewAudioProcessorEditor::resized(void) {
  Rectangle<int> area(getLocalBounds());

  audio_display_.setBounds(area.removeFromTop(getHeight() / 8).reduced(8));
  recordingThumbnail.setBounds(area.removeFromTop(getHeight() / 4).reduced(8));
  juce::Rectangle<int> kButtonArea(area.removeFromTop(getHeight() / 16));
  recordButton.setBounds(kButtonArea.removeFromLeft(140).reduced(8));
  replayButton.setBounds(kButtonArea.removeFromLeft(140).reduced(8));
  analyzeButton.setBounds(kButtonArea.removeFromLeft(140).reduced(8));

  curve_display_.setBounds(area.removeFromTop(getHeight() / 3).reduced(8));

  // DEBUG
  debug_infos_.setBounds(area.removeFromTop(getHeight() / 8).reduced(8));
  //  /DEBUG
}

void InstantSonicViewAudioProcessorEditor::changeListenerCallback(
    juce::ChangeBroadcaster *source) {
  InstantSonicViewAudioProcessor* proc(getProcessor());
  // No other change broacaster than the processor for now!
  INSTANTSONICVIEW_ASSERT(source == proc);

  if (getProcessor()->isRecording()) {
    recordingThumbnail.getAudioThumbnail().addBlock(nextSampleNum,
                                                    getProcessor()->GetLastBuffer(),
                                                    0,
                                                    getProcessor()->GetLastBuffer().getNumSamples());
    nextSampleNum += getProcessor()->GetLastBuffer().getNumSamples();
  }

  if (was_replaying_
      && !getProcessor()->isReplaying()) {
    replayButton.setButtonText("Replay");
    was_replaying_ = false;
  }

  if (analyzed_) {
    HandleAnalysisData();
  }
}

void InstantSonicViewAudioProcessorEditor::timerCallback() {
  const double time(getProcessor()->GetLastProcessTime());
  debug_infos_.setText(juce::String(time));
}

void InstantSonicViewAudioProcessorEditor::buttonClicked(Button* button) {
  if (button == &recordButton) {
    if (getProcessor()->isRecording())
      stopRecording();
    else
      startRecording();
  } else if (button == &replayButton) {
    startReplay();
  } else if (button == &analyzeButton) {
    startAnalysis();
  } else {
    // Should never happen
    INSTANTSONICVIEW_ASSERT(false);
  }
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

void InstantSonicViewAudioProcessorEditor::startRecording() {
  getProcessor()->startRecording();
  recordButton.setButtonText ("Stop");
  // Reset our recording thumbnail
  recordingThumbnail.getAudioThumbnail().reset(getProcessor()->getNumOutputChannels(),
                                               getProcessor()->getSampleRate());
  nextSampleNum = 0;
  recordingThumbnail.setDisplayFullThumbnail (false);
}

void InstantSonicViewAudioProcessorEditor::stopRecording() {
  getProcessor()->stopRecording();
  recordButton.setButtonText ("Record");
  recordingThumbnail.setDisplayFullThumbnail (true);
}

void InstantSonicViewAudioProcessorEditor::startReplay(void) {
  getProcessor()->startReplay();
  replayButton.setButtonText("Stop");
  was_replaying_ = true;
}

void InstantSonicViewAudioProcessorEditor::startAnalysis(void) {
  getProcessor()->startAnalysis();
  analyzed_ = true;
}

void InstantSonicViewAudioProcessorEditor::HandleAnalysisData(void) {
  const FeaturesData kFeatures(getProcessor()->GetFeatures());
  if (!kFeatures.data) {
    return;
  }
  curve_display_.clear();
  for (unsigned int feature_idx(0);
       feature_idx < kFeatures.features_count;
       ++feature_idx) {
    juce::Array<float> current_curve_data;
    for (unsigned int subframe_idx(0);
         subframe_idx < kFeatures.subframes_count;
         ++subframe_idx) {
      const float value(kFeatures.data[subframe_idx * kFeatures.features_count + feature_idx]);
      current_curve_data.add(value);
    }  // subframe_idx
    curve_display_.createCurve(current_curve_data);
  }  // feature_idx
  analyzed_ = false;
  // Inform child UI elements of changes
  sendChangeMessage();
}
