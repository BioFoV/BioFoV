#ifndef INDIV_H
#define INDIV_H

// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

#ifndef INC_SNAPSHOT
#define INC_SNAPSHOT
#include "../Snapshot/Snapshot.hpp"
#endif

#ifndef INC_EVENT
#define INC_EVENT
#include "../Event/Event.hpp"
#endif

#ifndef INC_FEATURE
#define INC_FEATURE
#include "../Feature/Feature.hpp"
#endif

#ifndef INC_LIST
#define INC_LIST
#include <list>
#endif

class Event;
class Snapshot;
class Feature;

/*
 * Class that represents an individual, and has associated with it the
 * various Events and Snapshots where this same individual shows up.
 * An Individual also has several Features that can be used for later
 * matching.
 */
class Individual{
private:
	// external references
	std::list<Event> events;
	std::list<Snapshot> snapshots;
	std::list<Feature> features;
	
public:
	// Constructors
	Individual();
	
	// Destructor
	~Individual();
};
#endif 
