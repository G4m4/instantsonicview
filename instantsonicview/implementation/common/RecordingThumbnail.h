/// @filename RecordingThumbnail.h
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


#ifndef INSTANTSONICVIEW_IMPLEMENTATION_COMMON_RECORDINGTHUMBNAIL_H_
#define INSTANTSONICVIEW_IMPLEMENTATION_COMMON_RECORDINGTHUMBNAIL_H_

#include "JuceHeader.h"

class RecordingThumbnail : public Component,
                           private ChangeListener {
 public:
  RecordingThumbnail();

  ~RecordingThumbnail();

  AudioThumbnail& getAudioThumbnail();
  void setDisplayFullThumbnail(bool displayFull);

  void paint(Graphics& g) override;

private:
  AudioFormatManager formatManager;
  AudioThumbnailCache thumbnailCache;
  AudioThumbnail thumbnail;
  bool displayFullThumb;

  void changeListenerCallback(ChangeBroadcaster* source) override;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RecordingThumbnail)
};

#endif  // INSTANTSONICVIEW_IMPLEMENTATION_COMMON_RECORDINGTHUMBNAIL_H_
