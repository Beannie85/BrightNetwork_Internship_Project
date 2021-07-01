#pragma once

#include <iostream>

#include "video.h"
/** A class used to represent a Playlist */

class VideoPlaylist {
    private:
    std::string name;
    std::vector<Video> videos;
    std::string toUpper(std::string);

    public:
    VideoPlaylist(std::string name_give);
    bool containVideo(std::string);
    std::vector<Video> getVideos();
    void addVideo(Video vid);
    void removeVideo(Video vid);
    void removeAllVideo();
};
