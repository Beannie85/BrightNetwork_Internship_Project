#pragma once

#include <string>
#include <unordered_map>

#include "videolibrary.h"
#include "videoplaylist.h"

/**
 * A class used to represent a Video Player.
 */
class VideoPlayer {
 private:
  VideoLibrary mVideoLibrary;
  std::vector<Video> allowedVideos = mVideoLibrary.getVideos();
  std::vector<std::string> playlistNames;
  std::unordered_map<std::string, VideoPlaylist> playlistMap;
  bool vidPlaying = false;
  Video* currentVid = nullptr; 
  std::string showVideoDetails(Video vid);
  std::string toUpper(std::string);

 public:
  bool containPlaylist(std::string);
  VideoPlayer() = default;

  // This class is not copyable to avoid expensive copies.
  VideoPlayer(const VideoPlayer&) = delete;
  VideoPlayer& operator=(const VideoPlayer&) = delete;

  // This class is movable.
  VideoPlayer(VideoPlayer&&) = default;
  VideoPlayer& operator=(VideoPlayer&&) = default;

  void numberOfVideos();
  void showAllVideos();
  void playVideo(const std::string& videoId);
  void stopVideo();
  void playRandomVideo();
  void pauseVideo();
  void continueVideo();
  void showPlaying();
  void createPlaylist(const std::string& playlistName);
  void addVideoToPlaylist(const std::string& playlistName, const std::string& videoId);
  void showAllPlaylists();
  void showPlaylist(const std::string& playlistName);
  void removeFromPlaylist(const std::string& playlistName, const std::string& videoId);
  void clearPlaylist(const std::string& playlistName);
  void deletePlaylist(const std::string& playlistName);
  void searchVideos(const std::string& searchTerm);
  void searchVideosWithTag(const std::string& videoTag);
  void flagVideo(const std::string& videoId);
  void flagVideo(const std::string& videoId, const std::string& reason);
  void allowVideo(const std::string& videoId);
};
