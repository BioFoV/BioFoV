#ifndef EVENT_H
#define EVENT_H

#ifndef INC_VIDEO
#define INC_VIDEO
#include "../Video/Video.hpp"
#endif

#ifndef INC_FRAME
#define INC_FRAME
#include "../Frame/Frame.hpp"
#endif

#ifndef INC_INDIVIDUAL
#define INC_INDIVIDUAL
#include "../Individual/Individual.hpp"
#endif

#ifndef INC_LIST
#define INC_LIST
#include <list>
#endif

#ifndef INC_PLAYER
#define INC_PLAYER
#include "../player.hpp"
#endif

class Frame;
class Individual;
class Video;

/*
 * Class that represents a contiguous set of frames with something
 * interesting on them.
 */
class Event : public Player {
private:
	// external references
	Video* vid;
    std::list<Frame*> frames;
    std::list<Individual*> individuals;
	
public:
	// Constructor
	Event();
    void addFrame(Frame* inframe);

    // Capture functions
    bool check_cap();
    bool setFramePos(double frameNum);
    double getFramePos();
    bool get_frame(cv::Mat &frame);
    bool getPrevFrame(cv::Mat &frame);

    // Properties
    double getFrameInt();
    double getFPS();
    double getLengthTime();
    double getLengthFrames();
};
#endif 
