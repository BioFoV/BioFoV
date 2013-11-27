#include "Frame.hpp"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
Frame::Frame(){
	vid = NULL;
}

Frame::Frame(Video *source_vid){
	vid = source_vid;
}
