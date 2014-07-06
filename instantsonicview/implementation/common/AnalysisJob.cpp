/// @filename AnalysisJob.cpp
/// @brief InstantSonicView
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

#include "instantsonicview/implementation/common/AnalysisJob.h"

#include "instantsonicview/src/analyzer/features.h"

AnalysisJob::AnalysisJob()
    : juce::ThreadPoolJob("Analysis thread"),
      data_(nullptr),
      data_length_(0),
      features_value_(nullptr),
      subframes_count_(0),
      analyzer_(48000.0f),
      filter_() {
  // Nothing to do here for now
}

AnalysisJob::~AnalysisJob() {
  delete[] features_value_;
}

juce::ThreadPoolJob::JobStatus AnalysisJob::runJob() {
  if (shouldExit()) {
    return ThreadPoolJob::jobNeedsRunningAgain;
  } else {
    INSTANTSONICVIEW_ASSERT(features_value_ != nullptr);
    subframes_count_ = analyzer_.Process(data_, data_length_, &features_value_[0]);
    return ThreadPoolJob::jobHasFinished;
  }
}

void AnalysisJob::SetSampleRate(double sample_rate) {
  INSTANTSONICVIEW_ASSERT(sample_rate > 0.0);
  //analyzer_.SetSampleRate(sample_rate);
  filter_.SetSampleRate(sample_rate);
}

void AnalysisJob::PrepareToAnalyze(const unsigned int data_length) {
  delete[] features_value_;
  features_value_ = new float[((data_length / 480) + 1) * instantsonicview::analyzer::kAvailableDescriptorsCount];
}

void AnalysisJob::FeedData(const float* const data, const unsigned int data_length) {
  data_ = data;
  data_length_ = data_length;
}

const float* AnalysisJob::GetFeatures(void) const {
  if (!isRunning()) {
    return &features_value_[0];
  } else {
    return nullptr;
  }
}

unsigned int AnalysisJob::SubframesCount(void) const {
  return subframes_count_;
}

unsigned int AnalysisJob::FeaturesCount(void) const {
  return instantsonicview::analyzer::kAvailableDescriptorsCount;
}
