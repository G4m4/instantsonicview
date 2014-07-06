/// @filename Bridge.cpp
/// @brief InstantSonicView Bridge
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

#include "instantsonicview/implementation/common/Bridge.h"

#include <algorithm>

#include "instantsonicview/src/analyzer/features.h"

Bridge::Bridge()
    : job_launched_(false),
      job_done_(false),
      features_value_(nullptr),
      subframes_count_(0),
      job_(),
      thread_pool_(1) {
  // Nothing to do here for now
}

Bridge::~Bridge() {
  thread_pool_.removeAllJobs(true, 100);
  delete[] features_value_;
}

void Bridge::SetSampleRate(double sample_rate) {
  INSTANTSONICVIEW_ASSERT(sample_rate > 0.0);
  //analyzer_.SetSampleRate(sample_rate);
  job_.SetSampleRate(sample_rate);
}

void Bridge::PrepareToAnalyze(const unsigned int data_length) {
  delete[] features_value_;
  features_value_ = new float[((data_length / 480) + 1) * instantsonicview::analyzer::kAvailableDescriptorsCount];
  job_.PrepareToAnalyze(data_length);
}

void Bridge::FeedData(const float* const data, const unsigned int data_length) {
  job_.FeedData(data, data_length);
  job_done_ = false;
  job_launched_ = true;
  thread_pool_.addJob(&job_, false);
}

float Bridge::GetFeatureValue(const unsigned int subframe_idx,
                              const unsigned int feature_idx) {
  CheckForFinishedJob();
  return features_value_[subframe_idx * instantsonicview::analyzer::kAvailableDescriptorsCount
                         + feature_idx];
}

const float* Bridge::GetFeatures(void) {
  CheckForFinishedJob();
  return &features_value_[0];
}

unsigned int Bridge::SubframesCount(void) {
  CheckForFinishedJob();
  return subframes_count_;
}

unsigned int Bridge::FeaturesCount(void) const {
  return instantsonicview::analyzer::kAvailableDescriptorsCount;
}

void Bridge::CheckForFinishedJob() {
  if ((job_done_) || (!job_launched_)) {
    return;
  } else {
    if (!job_.isRunning()) {
      const bool kJobRemoved(thread_pool_.removeJob(&job_, false, 100));
      INSTANTSONICVIEW_ASSERT(kJobRemoved == true);
      subframes_count_ = job_.SubframesCount();
      std::copy_n(job_.GetFeatures(), job_.FeaturesCount() * subframes_count_, &features_value_[0]);
      job_done_ = true;
      job_launched_ = false;
    } else {
      return;
    }
  }
}
