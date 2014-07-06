/// @filename AudioStreamSource.h
/// @brief Manage all sources feeding the audio stream
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

#ifndef INSTANTSONICVIEW_IMPLEMENTATION_COMMON_AUDIOSTREAM_H_
#define INSTANTSONICVIEW_IMPLEMENTATION_COMMON_AUDIOSTREAM_H_

#include <vector>

#include "JuceHeader.h"

namespace instantsonicview {

class AudioStreamBuffer {
 public:
  AudioStreamBuffer();
  ~AudioStreamBuffer();

  void PushData(const float* data, unsigned int count);
  void PopData(float* const data);

  unsigned int ElementsCount() const;

 private:
  /// @brief: Default (fixed at compile time) fifo capacity
  static const int kCapacity = 8192;

  juce::AbstractFifo abstract_fifo_;
  std::vector<float> audio_buffer_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioStreamBuffer)
};

class AudioStreamSource {
 public:
  AudioStreamSource();
  ~AudioStreamSource();

  unsigned int HowMuchDataAvailable() const;
  const float* StreamAudioDataOut();

 protected:
  void StreamAudioDataIn(const float* data, unsigned int data_length);

 private:
  AudioStreamBuffer fifo_;
  std::vector<float> buffer_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioStreamSource)
};

class AudioStreamListenerManager {
 public:
  AudioStreamListenerManager(AudioStreamSource* broadcaster);
  ~AudioStreamListenerManager();

  void callListeners();

  class StreamListener {
   public:
    virtual ~StreamListener() {}

    virtual void ProcessAudio(const float* audio_data,
                              unsigned int samples_count) = 0;
  };

  void addListener(StreamListener* listener);
  void removeListener(StreamListener* listener);

 private:
  std::vector<StreamListener*> listeners_;
  AudioStreamSource* source_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioStreamListenerManager)
};

}  // namespace instantsonicview

#endif  // INSTANTSONICVIEW_IMPLEMENTATION_COMMON_AUDIOSTREAMSOURCE_H_
