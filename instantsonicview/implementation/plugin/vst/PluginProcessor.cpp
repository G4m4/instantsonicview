/// @filename PluginProcessor.cpp
/// @brief InstantSonicView plugin processor (audio)
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

#include "instantsonicview/implementation/plugin/vst/PluginProcessor.h"

#include "instantsonicview/implementation/plugin/vst/PluginEditor.h"

InstantSonicViewAudioProcessor::InstantSonicViewAudioProcessor()
: process_time_(0.0),
  analyzer_(48000.0f) {
}

InstantSonicViewAudioProcessor::~InstantSonicViewAudioProcessor() {
}

const juce::String InstantSonicViewAudioProcessor::getName() const {
  return JucePlugin_Name;
}

int InstantSonicViewAudioProcessor::getNumParameters() {
  return 1;
}

float InstantSonicViewAudioProcessor::getParameter(int index) {
  return 0.0f;
}

void InstantSonicViewAudioProcessor::setParameter(int index, float newValue) {
  // Inform UI of any change
  sendChangeMessage();
}

const juce::String InstantSonicViewAudioProcessor::getParameterName(int index) {
  return juce::String();
}

const juce::String InstantSonicViewAudioProcessor::getParameterText(int index) {
  return juce::String();
}

const juce::String InstantSonicViewAudioProcessor::getInputChannelName(
    int channelIndex) const {
  return juce::String(channelIndex + 1);
}

const juce::String InstantSonicViewAudioProcessor::getOutputChannelName(
    int channelIndex) const {
  return juce::String(channelIndex + 1);
}

bool InstantSonicViewAudioProcessor::isInputChannelStereoPair(int index) const {
  return true;
}

bool InstantSonicViewAudioProcessor::isOutputChannelStereoPair(int index) const {
  return true;
}

bool InstantSonicViewAudioProcessor::acceptsMidi() const {
  #if JucePlugin_WantsMidiInput
  return true;
  #else
  return false;
  #endif
}

bool InstantSonicViewAudioProcessor::producesMidi() const {
  #if JucePlugin_ProducesMidiOutput
  return true;
  #else
  return false;
  #endif
}

bool InstantSonicViewAudioProcessor::silenceInProducesSilenceOut() const {
  return false;
}

double InstantSonicViewAudioProcessor::getTailLengthSeconds() const {
  return 0.0;
}

int InstantSonicViewAudioProcessor::getNumPrograms() {
  return 1;
}

int InstantSonicViewAudioProcessor::getCurrentProgram() {
  return 0;
}

void InstantSonicViewAudioProcessor::setCurrentProgram(int index) {
}

const String InstantSonicViewAudioProcessor::getProgramName(int index) {
  return String::empty;
}

void InstantSonicViewAudioProcessor::changeProgramName(
    int index,
    const juce::String& newName) {
}

void InstantSonicViewAudioProcessor::prepareToPlay(double sampleRate,
                                                   int samplesPerBlock) {
  // Notify UI of the last changes
  sendChangeMessage();
}

void InstantSonicViewAudioProcessor::releaseResources() {
  // When playback stops, you can use this as an opportunity to free up any
  // spare memory, etc.
}

void InstantSonicViewAudioProcessor::processBlock(
    juce::AudioSampleBuffer& buffer,
    juce::MidiBuffer& midiMessages) {
  const double counter_start(juce::Time::getMillisecondCounterHiRes());
  process_time_ = juce::Time::getMillisecondCounterHiRes() - counter_start;
}

bool InstantSonicViewAudioProcessor::hasEditor() const {
  return true;
}

AudioProcessorEditor* InstantSonicViewAudioProcessor::createEditor() {
  return new InstantSonicViewAudioProcessorEditor(this);
}

void InstantSonicViewAudioProcessor::getStateInformation(
    juce::MemoryBlock& destData) {
  // You should use this method to store your parameters in the memory block.
  // You could do that either as raw data, or use the XML or ValueTree classes
  // as intermediaries to make it easy to save and load complex data.
}

void InstantSonicViewAudioProcessor::setStateInformation(const void* data,
                                                         int sizeInBytes) {
}

void InstantSonicViewAudioProcessor::addChangeListener(
    juce::ChangeListener* listener) {
  // Call parent method
  ChangeBroadcaster::addChangeListener(listener);
  // Update newly added listener
  sendChangeMessage();
}

// DEBUG
double InstantSonicViewAudioProcessor::GetLastProcessTime() const {
  return process_time_;
}
//  /DEBUG

AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
  return new InstantSonicViewAudioProcessor();
}
