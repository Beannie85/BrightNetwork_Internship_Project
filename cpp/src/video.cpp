#include "video.h"

#include <iostream>
#include <utility>
#include <vector>

Video::Video(std::string&& title, std::string&& videoId,
             std::vector<std::string>&& tags) :
  mTitle(std::move(title)),
  mVideoId(std::move(videoId)),
  mTags(std::move(tags)) {
}

const std::string& Video::getTitle() const { return mTitle; }

const std::string& Video::getVideoId() const { return mVideoId; }

const std::vector<std::string>& Video::getTags() const { return mTags; }

void Video::flag(){flagged = true;}

bool Video::isFlagged(){return flagged;}

void Video::allow(){
  flagged = false;
  flaggedReason = nullptr;
}

 void Video::set_reason(std::string reason){flaggedReason = reason;}

 std::string Video::getFlaggedReason(){return flaggedReason;}