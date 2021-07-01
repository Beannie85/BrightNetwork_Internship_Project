#pragma once

#include <string>
#include <vector>

/**
 * A class used to represent a video.
 */
class Video {
 private:
  std::string mTitle;
  std::string mVideoId;
  std::vector<std::string> mTags;
  bool flagged = false;
  //bool allowed = true;
  std::string flaggedReason;

 public:
  Video(std::string&& title, std::string&& videoId,
        std::vector<std::string>&& tags);

  // Returns the title of the video.
  const std::string& getTitle() const;

  // Returns the video id of the video.
  const std::string& getVideoId() const;

  // Returns a readonly collection of the tags of the video.
  const std::vector<std::string>& getTags() const;

  void flag();

  bool isFlagged();

  void set_reason(std::string);

  std::string getFlaggedReason();

  void allow();

  bool isAllowed();
};
