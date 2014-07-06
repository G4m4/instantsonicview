/// @filename RecordingThumbnail.cpp
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

#include "instantsonicview/implementation/common/RecordingThumbnail.h"

RecordingThumbnail::RecordingThumbnail()
    : thumbnailCache (10),
      thumbnail (512, formatManager, thumbnailCache),
      nextSampleNum(0),
      displayFullThumb (false) {
  formatManager.registerBasicFormats();
  thumbnail.addChangeListener (this);
}

RecordingThumbnail::~RecordingThumbnail() {
  thumbnail.removeChangeListener (this);
}

void RecordingThumbnail::ProcessAudio(const float* audio_data,
                                      unsigned int samples_count) {
  // TODO(gm): remove this ugly thing
  float* const* tmp_ptr = const_cast<float* const*>(&audio_data);
  const juce::AudioSampleBuffer buffer(tmp_ptr, 1, samples_count);
  getAudioThumbnail().addBlock(nextSampleNum,
      buffer,
      0,
      samples_count);
  nextSampleNum += samples_count;
}

AudioThumbnail& RecordingThumbnail::getAudioThumbnail() {
  return thumbnail;
}

void RecordingThumbnail::setDisplayFullThumbnail (bool displayFull) {
  displayFullThumb = displayFull;
  repaint();
}

void RecordingThumbnail::paint (Graphics& g) {
  g.fillAll (Colours::darkgrey);
  g.setColour (Colours::lightgrey);

  if (thumbnail.getTotalLength() > 0.0) {
    const double endTime = displayFullThumb ? thumbnail.getTotalLength()
                                            : jmax (30.0, thumbnail.getTotalLength());

    Rectangle<int> thumbArea (getLocalBounds());
    thumbnail.drawChannels (g, thumbArea.reduced (2), 0.0, endTime, 1.0f);
  } else {
    g.setFont (14.0f);
    g.drawFittedText ("(No file recorded)", getLocalBounds(), Justification::centred, 2);
  }
}

void RecordingThumbnail::changeListenerCallback (ChangeBroadcaster* source)  {
  if (source == &thumbnail)
    repaint();
}
