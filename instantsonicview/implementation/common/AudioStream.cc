/// @filename AudioStream.cc
/// @brief Manage all audio stream stuff
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

#include "instantsonicview/implementation/common/AudioStream.h"

#include "instantsonicview/src/common.h"

namespace instantsonicview {

AudioStreamBuffer::AudioStreamBuffer()
    : abstract_fifo_(kCapacity),
      audio_buffer_(kCapacity) {
  // Nothing to do here for now
}

AudioStreamBuffer::~AudioStreamBuffer() {
  audio_buffer_.clear();
}

void AudioStreamBuffer::PushData(const float* data, unsigned int count) {
  INSTANTSONICVIEW_ASSERT(data != nullptr);
  INSTANTSONICVIEW_ASSERT(count
    <= static_cast<unsigned int>(abstract_fifo_.getFreeSpace()));

  int start1;
  int size1;
  int start2;
  int size2;

  abstract_fifo_.prepareToWrite(count, start1, size1, start2, size2);
  if (size1 > 0) {
    std::copy_n(data, size1, &audio_buffer_[0] + start1);
  }
  if (size2 > 0) {
    std::copy_n(data + size1, size2, &audio_buffer_[0] + start2);
  }
  abstract_fifo_.finishedWrite (size1 + size2);
}

void AudioStreamBuffer::PopData(float* const data) {
  INSTANTSONICVIEW_ASSERT(data != nullptr);

  int start1;
  int size1;
  int start2;
  int size2;

  int kNumSamples(abstract_fifo_.getNumReady());
  abstract_fifo_.prepareToRead(kNumSamples, start1, size1, start2, size2);
  if (size1 > 0) {
    std::copy_n(&audio_buffer_[0] + start1, size1, data);
  }
  if (size2 > 0) {
    std::copy_n(&audio_buffer_[0] + start2, size2, data + size1);
  }
  abstract_fifo_.finishedRead(size1 + size2);
}

unsigned int AudioStreamBuffer::ElementsCount() const {
  return static_cast<unsigned int>(abstract_fifo_.getNumReady());
}

AudioStreamSource::AudioStreamSource()
    : fifo_(),
      buffer_(4096) {
  // Nothing to do here for now
}

AudioStreamSource::~AudioStreamSource() {
}

unsigned int AudioStreamSource::HowMuchDataAvailable() const {
  return fifo_.ElementsCount();
}

const float* AudioStreamSource::StreamAudioDataOut() {
  fifo_.PopData(&buffer_[0]);
  return &buffer_[0];
}

void AudioStreamSource::StreamAudioDataIn(const float* data,
                                          unsigned int data_length) {
  fifo_.PushData(data, data_length);
}

AudioStreamListenerManager::AudioStreamListenerManager(
  AudioStreamSource* src)
    : source_(src) {
  INSTANTSONICVIEW_ASSERT(src != nullptr);
}

AudioStreamListenerManager::~AudioStreamListenerManager() {
  // Nothing to do here for now
}

void AudioStreamListenerManager::callListeners() {
  unsigned int kElementsCount(source_->HowMuchDataAvailable());
  if (kElementsCount == 0) {
    return;
  }
  const float* kAudioData(source_->StreamAudioDataOut());
  for (AudioStreamListenerManager::StreamListener* listener : listeners_) {
    if (listener != nullptr) {
      listener->ProcessAudio(kAudioData, kElementsCount);
    }
  }
}

void AudioStreamListenerManager::addListener(StreamListener* listener) {
  listeners_.push_back(listener);
}

void AudioStreamListenerManager::removeListener(StreamListener* listener) {
  std::vector<StreamListener*>::iterator iter(std::find(listeners_.begin(), listeners_.end(), listener));
  *iter = nullptr;
}

}  // namespace instantsonicview
