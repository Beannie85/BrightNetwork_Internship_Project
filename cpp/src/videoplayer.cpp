#include "videoplayer.h"

#include <list>
#include <iostream>



void VideoPlayer::numberOfVideos() {
  std::cout << mVideoLibrary.getVideos().size() << " videos in the library"
            << std::endl;
}

void VideoPlayer::showAllVideos() {
  std::vector<Video> videos = allowedVideos;
  std::cout<<"Here's a list of all available videos:"<<std::endl;
  std::list<std::string> allVideoDetails;
  for(auto it = videos.cbegin(); it != videos.cend(); it++){
      Video vid = *it;
      allVideoDetails.push_back(showVideoDetails(vid));
  }
  allVideoDetails.sort();
  for(auto itt = allVideoDetails.cbegin(); itt != allVideoDetails.cend(); itt++){
    std::cout<< *itt<<std::endl;
  }

}

std::string VideoPlayer::showVideoDetails(Video vid){
    std::string title = vid.getTitle();
    std::string id = "(" + vid.getVideoId() + ")";
    std::string tagString = "[";
    std::vector<std::string> tags = vid.getTags();
    for(auto it = tags.cbegin(); it != tags.cend(); it++){
        std::string tag = *it;
        tagString = tagString + tag + " ";
      }
      if(tagString.size()>1){
      tagString.pop_back();
      }
      tagString+="]";
      if(vid.isFlagged()){
        std::string reason = vid.getFlaggedReason();
        return title+" "+id+" "+tagString+" - FLAGGED (reason: " + reason; 
      }
      else{
    return title+" "+id+" "+tagString;
      }
}


void VideoPlayer::playVideo(const std::string& videoId) {
  if(vidPlaying){
    Video prevVid = *currentVid;
    std::string prevTitle = prevVid.getTitle();
    std::cout << "Stopping video: "<<prevTitle<<std::endl;
  }
  currentVid = (Video*) mVideoLibrary.getVideo(videoId);
    Video vid = *currentVid;
    vidPlaying = true;
    std::string title = vid.getTitle();
    std::cout << "Playing video: "<< title <<std::endl;
}

void VideoPlayer::stopVideo() {
  if(vidPlaying){
    Video vid = *currentVid;
    std::string title = vid.getTitle();
    vidPlaying = false;
    currentVid = nullptr;
    std::cout << "Stopping video: " << title << std::endl;
  }
  else{
    std::cout<< "Cannot stop video: No video is currently playing"<<std::endl;
  }
}

void VideoPlayer::playRandomVideo() {
  std::vector<Video> videos = mVideoLibrary.getVideos();
  int i = rand() % videos.size();
  Video vid = videos[i];
  std::string vidID = vid.getVideoId();
  VideoPlayer::playVideo(vidID);
}

void VideoPlayer::pauseVideo() {
    Video vid = *currentVid;
    std::string title = vid.getTitle();
  if(vidPlaying){
    std::cout << "Pausing video: "<<title<<std::endl;
    vidPlaying = false;
  }
  else if(currentVid == nullptr){
    std::cout <<"Cannot pause video: No video is currently playing" <<std::endl;
  }
  else{
    std::cout << "Video already paused: "<<title<<std::endl;
  }
}

void VideoPlayer::continueVideo() {
  if(!vidPlaying){
    Video vid = *currentVid;
    std::string title = vid.getTitle();
    std::cout << "Continue video: "<<title<<std::endl;
    vidPlaying = false;
  }
  else if(currentVid == nullptr){
    std::cout <<"Cannot continue video: No video is currently playing"<<std::endl;
  }
  else{
    std::cout << "Cannot continue video: Video is not paused"<<std::endl;
  }
}

void VideoPlayer::showPlaying() {
  Video vid = *currentVid;
  if(currentVid!= nullptr && vidPlaying){
      std::cout<<"Currently playing: "<<showVideoDetails(vid);
  }
  else if(currentVid!=nullptr && !vidPlaying){
    std::string vidDetails = showVideoDetails(vid);
    vidDetails.pop_back();
    std::cout<< "Currently playing: "<<vidDetails<<" PAUSED"<<std::endl;
  }
  else if(currentVid->isFlagged()){
    std::cout << "No video is currently playing"<<std::endl;
  }
  else{
    std::cout << "No video is currently playing"<<std::endl;
  }
}


bool VideoPlayer::containPlaylist(std::string playlist){
    std::string Uplaylist = toUpper(playlist);
    for(auto it = playlistNames.cbegin(); it != playlistNames.cend(); it++){
        std::string currPlaylist = *it;
        if(Uplaylist.compare(currPlaylist)==0){
            return true;
        }
    }
    return false;
}

void VideoPlayer::createPlaylist(const std::string& playlistName) {
  bool playlistFound = containPlaylist(playlistName);
  if(playlistFound){
    std::cout << "Cannot create playlist: A playlist with the same name already exist"<<std::endl;
  }
  else{
    std::string UplaylistName = toUpper(playlistName);
    VideoPlaylist playlist = VideoPlaylist(UplaylistName);
    playlistNames.push_back(UplaylistName);
    playlistMap.emplace(UplaylistName,playlist);
    std::cout<<"Successfully created new playlist: "<<playlistName<<std::endl;
  }
}

void VideoPlayer::addVideoToPlaylist(const std::string& playlistName,
                                     const std::string& videoId) {
  if(containPlaylist(playlistName)){
    VideoPlaylist playlist = playlistMap.at(playlistName);
    bool containVid = playlist.containVideo(videoId);
    if(containVid){
    std::cout <<"Cannot add video to "<< playlistName<<": Video already added"<<std::endl;
    }
    else{
      Video vid = *(mVideoLibrary.getVideo(videoId));
      if(vid.isFlagged()){
        std::cout <<"Cannot add video to "<< playlistName <<": Video is currently flagged (reason: "<<vid.getFlaggedReason()<<std::endl;
      }
      else{
      playlist.addVideo(vid);
      std::string name = vid.getTitle();
      std::cout << "Added video to "<< playlistName <<": "<< name <<std::endl;
      }
    }
  }
  else{
    std::cout <<"Cannot add video to "<< playlistName << ": Playlist does not exist"<<std::endl;
  }
}

void VideoPlayer::showAllPlaylists() {
  if(playlistNames.size()==0){
    std::cout <<"No playlists exist yet"<<std::endl;
  }
  else{
    std::cout <<"Showing all playlists:"<<std::endl;
    for(auto it = playlistNames.cbegin(); it != playlistNames.cend();it++){
      std::cout<< "\t" << *it <<std::endl;
    }
  }
}

void VideoPlayer::showPlaylist(const std::string& playlistName) {
  if(containPlaylist(playlistName)){
    std::cout <<"Showing playlist: "<< playlistName<<std::endl;
    VideoPlaylist playlist = playlistMap.at(playlistName);
    std::vector<Video> videos = playlist.getVideos();
    if(videos.size()==0){
      std::cout << "\t"<<"No videos here yet"<<std::endl;
    }
    else{
      for(auto it = videos.cbegin();it != videos.cend(); it++){
        Video vid = *it;
        std::cout<<"\t"<<showVideoDetails(vid);
      }
    }
  }
  else{
    std::cout <<"Cannot show playlist"<< playlistName <<": Playlist does not exist"<<std::endl;
  }
}

void VideoPlayer::removeFromPlaylist(const std::string& playlistName,
                                     const std::string& videoId) {
  Video vid = *mVideoLibrary.getVideo(videoId);
  std::string name = vid.getTitle();
  if(containPlaylist(playlistName)){
    VideoPlaylist playlist = playlistMap.at(playlistName);
    if(playlist.containVideo(videoId)){
      playlist.removeVideo(vid);
      std::cout <<"Removed video from "<<playlistName<<": "<< name <<std::endl;
    }
    else{
      std::cout <<"Cannot remove video from "<<playlistName<<": Video is not in playlist"<<std::endl;
    }
  }
  else{
    std::cout <<"Cannot remove video from "<< playlistName<<": Playlist does not exist"<<std::endl;
  }
}

void VideoPlayer::clearPlaylist(const std::string& playlistName) {
  if(containPlaylist(playlistName)){
    VideoPlaylist playlist = playlistMap.at(playlistName);
    std::cout <<"Successfully removed all videos from "<<playlistName<<std::endl;
  }
  else{
    std::cout <<"Cannot clear playlist "<<playlistName<<": Playlist does not exist"<<std::endl;
  }
}

void VideoPlayer::deletePlaylist(const std::string& playlistName) {
  /*
  std::string uplaylistName = toUpper(playlistName);
  if(containPlaylist(playlistName)){
    //delete from playlistNames first
    for(auto it = playlistNames.cbegin(); it!=playlistNames .cend();it++){
        if(uplaylistName.compare(*it)==0){
          playlistNames.erase(it,it++);
        }
    } 

    //delete from playlistMap
    VideoPlaylist playlist = playlistMap.at(uplaylistName);
    for(auto it = playlistMap.cbegin(); it!=playlistMap.cend();it++){
        std::string currName = it->first;
        if(uplaylistName.compare(currName)==0){
          playlistNames.erase(it,it++);
        }
        std::cout<<"Deleted playlist: "<<playlistName<<"\n";
    } 

  }
  else{
    std::cout <<"Cannot delete playlist "<<playlistName<<": Playlist does not exist\n";
  }
  */
}

void VideoPlayer::searchVideos(const std::string& searchTerm) {
  std::vector<Video> vids = allowedVideos;
  std::vector<Video> vidsSearched;
  for(auto it = vids.cbegin(); it!=vids.cend();it++){
    Video vid = *it;
    std::string title = vid.getTitle();
    if(title.find(searchTerm) != std::string::npos){
      vidsSearched.push_back(vid);
    }
  }
  if(vidsSearched.size() > 0){
    std::list<std::string> vidDeets;
    std::unordered_map<std::string,Video> vidDeetsMap;
    //sorting
    for(auto it = vidsSearched.cbegin(); it!=vidsSearched.cend();it++){
      Video vidx = *it;
      std::string vidDeet = showVideoDetails(vidx);
      vidDeets.push_back(vidDeet);
      vidDeetsMap.emplace(vidDeet, vidx);
    }
    vidDeets.sort();
    std::unordered_map<int, Video> vidxmap;
    std::cout <<"Here are the results for cat:"<<std::endl;
    for(auto it = vidDeets.cbegin(); it!=vidDeets.cend();it++){
      std::string deets = *it;
      Video vidx = vidDeetsMap.at(deets);
      int j =0;
      std::cout<< j <<") "<<deets;
      vidxmap.emplace(j,vidx);
      j++;
    }
    std::cout<< "Would you like to play any of the above? \nIf yes, specify the number of the video.\nIf your answer is not a valid number, we will assume it's a no."<<std::endl;
    int k;
    std::cin >> k;
    int size = vidsSearched.size();
    if(k<size){
      Video vidPlayed = vidxmap.at(k);
      playVideo(vidPlayed.getVideoId());
    }
    else{
      std::cout<< "Have a great Day!"<<std::endl;
      }
  }
  else{
    std::cout << "No search results for "<<searchTerm<<std::endl;
  }
  //lStream.close()
}

void VideoPlayer::searchVideosWithTag(const std::string& videoTag) {
  std::vector<Video> vids = allowedVideos;
  std::vector<Video> vidsSearched;
  for(auto it = vids.cbegin(); it!=vids.cend();it++){
    Video vid = *it;
    std::vector<std::string> tags = vid.getTags();
    for(auto itt = tags.cbegin(); itt!=tags.cend(); itt++ ){
      std::string tag = *itt;
      std::string utag = toUpper(tag);
      if(toUpper(videoTag).compare(utag)==0){
        vidsSearched.push_back(vid);
      }
    }
  }
  if(vidsSearched.size() > 0){
    std::list<std::string> vidDeets;
    std::unordered_map<std::string,Video> vidDeetsMap;
    //sorting
    for(auto it = vidsSearched.cbegin(); it!=vidsSearched.cend();it++){
      Video vidx = *it;
      std::string vidDeet = showVideoDetails(vidx);
      vidDeets.push_back(vidDeet);
      vidDeetsMap.emplace(vidDeet, vidx);
    }
    vidDeets.sort();
    std::unordered_map<int, Video> vidxmap;
    std::cout <<"Here are the results for cat:"<<std::endl;
    for(auto it = vidDeets.cbegin(); it!=vidDeets.cend();it++){
      std::string deets = *it;
      Video vidx = vidDeetsMap.at(deets);
      int j =0;
      std::cout<< j <<") "<<deets;
      vidxmap.emplace(j,vidx);
      j++;
    }
    std::cout<< "Would you like to play any of the above? \nIf yes, specify the number of the video.\nIf your answer is not a valid number, we will assume it's a no.";
    int k;
    std::cin >> k;
    int size = vidsSearched.size();
    if(k<size){
      Video vidPlayed = vidxmap.at(k);
      playVideo(vidPlayed.getVideoId());
    }
    else{
      std::cout<< "Have a great Day"<<std::endl;
      }
  }
  else{
    std::cout << "No search results for "<<videoTag<<std::endl;
  }
}

void VideoPlayer::flagVideo(const std::string& videoId) {
  flagVideo(videoId, "Not supplied");
}

void VideoPlayer::flagVideo(const std::string& videoId, const std::string& reason= "Not supplied") {
  std::vector<Video> videos = mVideoLibrary.getVideos();
  VideoPlaylist playlist = VideoPlaylist("VID LIBRARY");
  for(auto it= videos.cbegin(); it!= videos.cend();it++){
    Video vid = *it;
    playlist.addVideo(vid);
  }
  if(playlist.containVideo(videoId)){
    Video flaggedVid = *(mVideoLibrary.getVideo(videoId));
    if(flaggedVid.isFlagged()){
      std::cout << "Cannot flag video: Video is already flagge"<<std::endl;
    }
    else{
    flaggedVid.flag();
    flaggedVid.set_reason(reason);
    std::cout <<"Successfully flagged video: "<< flaggedVid.getTitle() << " (reason: "<<flaggedVid.getFlaggedReason()<<")"<<std::endl;
    //allowedVideos.remove(flaggedVid)
    }
  }
  else{
    std::cout << "Cannot flag video: Video does not exist"<<std::endl;
  }
}

void VideoPlayer::allowVideo(const std::string& videoId) {
  std::vector<Video> videos = mVideoLibrary.getVideos();
  VideoPlaylist playlist = VideoPlaylist("VID LIBRARY");
  for(auto it= videos.cbegin(); it!= videos.cend();it++){
    Video vid = *it;
    playlist.addVideo(vid);
  }
  if(playlist.containVideo(videoId)){
  Video vid = *(mVideoLibrary.getVideo(videoId));
  if(vid.isFlagged()){
    vid.allow();
    std::cout <<"Successfully removed flag from video: "<<vid.getTitle()<<std::endl;
    allowedVideos.push_back(vid);
  }
  else{
    std::cout <<"Cannot remove flag from video: Video is not flagged"<<std::endl;
  }
  }
  else{
    std::cout << "Cannot remove flag from video: Video does not exist"<<std::endl;
  }
}

std::string VideoPlayer::toUpper(std::string str){
  std::string uStr;
  int size = str.length();
  for (int i=0; i<size ; i++)
        uStr[i]=char(toupper(str[i]));
  return uStr;
}