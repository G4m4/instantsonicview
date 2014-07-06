/// @filename LiveScrollingAudioDisplay.h
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


#ifndef INSTANTSONICVIEW_IMPLEMENTATION_COMMON_LIVESCROLLINGAUDIODISPLAY_H_
#define INSTANTSONICVIEW_IMPLEMENTATION_COMMON_LIVESCROLLINGAUDIODISPLAY_H_

#include "JuceHeader.h"

#include "instantsonicview/implementation/common/AudioStream.h"

class LiveScrollingAudioDisplay : public Component,
                                  private Timer,
                                  public instantsonicview::AudioStreamListenerManager::StreamListener {
 public:
  LiveScrollingAudioDisplay();

  void ProcessAudio(const float* audio_data,
                    unsigned int samples_count) override;

private:
  float samples[1024];
  int nextSample, subSample;
  float accumulator;

  void clear();
  void paint(Graphics& g) override;
  void timerCallback() override;
  void pushSample(const float newSample);

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LiveScrollingAudioDisplay)
};

#endif  // INSTANTSONICVIEW_IMPLEMENTATION_COMMON_LIVESCROLLINGAUDIODISPLAY_H_
