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
	Video vid;
	std::list<Frame> frames;
	std::list<Individual> individuals;
	
public:
	// Constructor
	Event();
};
#endif 
