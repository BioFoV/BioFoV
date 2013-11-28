#include "videoplayer.hpp"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
VideoPlayer::VideoPlayer(QWidget *parent) :
    QLabel(parent)
{
}

/*******************************************************************************
 * Destructor
 ******************************************************************************/
VideoPlayer::~VideoPlayer(){

}

/*******************************************************************************
 * Actions
 ******************************************************************************/
void VideoPlayer::play(){

}

void VideoPlayer::pause(){

}

void VideoPlayer::playOrPause(){

}

void VideoPlayer::step(){

}

void VideoPlayer::goTo(int nthFrame){

}

void VideoPlayer::loadVid(Video* nextVid){
    currentVid = nextVid;
}

void VideoPlayer::unload(){
    delete currentVid;
}
