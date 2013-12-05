#include "Snapshot.hpp"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
Snapshot::Snapshot(){
	
}

Snapshot::Snapshot(Frame *img){
	image = img;
}

Snapshot::Snapshot(Frame *img, cv::Mat inmask){
    const void * address = static_cast<const void*>(this);
    std::stringstream ss;
    ss << address;
    filename = ss.str() + SNAP_EXT;

    image = img;
    cv::imwrite( filename, inmask );
}


/*******************************************************************************
 * Destructor
 ******************************************************************************/
Snapshot::~Snapshot(){
    remove(filename.c_str());
}

/*******************************************************************************
 * Functions
 ******************************************************************************/
cv::Mat Snapshot::getMask(){
    cv::Mat mask = cv::imread(filename, 0);
    return mask;
}
