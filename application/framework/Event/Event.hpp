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

#ifndef INC_PLAYER
#define INC_PLAYER
#include "../player.hpp"
#endif

#ifndef INC_STDEXCEPT
#define INC_STDEXCEPT
#include <stdexcept>
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
    std::deque<Frame*> frames;
    std::deque<Individual*> individuals;
	
    // player variables
    double position;
    double fps;
public:
	// Constructor
	Event();
    void addFrame(Frame* inframe);
    void setFPS(double infps);

    // Capture functions
    bool check_cap();
    bool setFramePos(double frameNum);
    double getFramePos();
    bool getFrame(cv::Mat &frame);
    bool getPrevFrame(cv::Mat &frame);

    // Properties
    double getFrameInt();
    double getFPS();
    double getLengthTime();
    double getLengthFrames();
};
#endif 
