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

#ifndef EVENT_H
#define EVENT_H
class Frame;
class Individual;

/*
 * Class that represents a contiguous set of frames with something
 * interesting on them.
 */
class Event{
private:
	// external references
	Video* vid;
	std::list<Frame> frames;
	std::list<Individual> individuals;
	
public:
	// Constructor
	Event();
};
#endif 
