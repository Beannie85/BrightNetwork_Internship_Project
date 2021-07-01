#include "videoplaylist.h"

#include <iostream>

VideoPlaylist::VideoPlaylist(std::string name_given){
    name = name_given;
}

bool VideoPlaylist::containVideo(std::string videoID){
    std::string uvideoID = toUpper(videoID);
    for(auto it = videos.cbegin();it!= videos.cend();it++){
        Video vid = *it;
        std::string currVidID = toUpper(vid.getVideoId());
        if(uvideoID.compare(currVidID)==0)
        {
            return true;
        }
        
    }
    return false;
}

std::vector<Video> VideoPlaylist::getVideos(){return videos;}

void VideoPlaylist::addVideo(Video vid){videos.push_back(vid);}

void VideoPlaylist::removeVideo(Video vid){
    std::string vidID = toUpper(vid.getVideoId());
    for(auto it = videos.cbegin(); it!=videos.cend();it++){
        Video currvid = *it;
        std::string currVidID = toUpper(currvid.getVideoId());
        if(currVidID.compare(vidID)==0){
            videos.erase(it);
        }
    }
}

void VideoPlaylist::removeAllVideo(){videos.clear();}

std::string VideoPlaylist::toUpper(std::string str){
  std::string uStr;
  int size = str.length();
  for (int i=0; i<size ; i++)
        uStr[i]=char(toupper(str[i]));
  return uStr;
}