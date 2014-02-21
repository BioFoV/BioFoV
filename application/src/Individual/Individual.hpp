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

///
/// \brief Class that represents an individual.
///has associated with it the various Events and Snapshots where this same
///individual shows up. An Individual also has several Features that can be used
///for later matching.
///
class Individual{
private:
    /// \brief List of Event where this individual shows up.
	std::list<Event> events;

    /// \brief List of Snapshots of this individual.
	std::list<Snapshot> snapshots;

    /// \brief List of Features for this individual.
	std::list<Feature> features;
	
public:
    /// \brief Simple constructor.
	Individual();
	
    /// \brief Simple destructor.
	~Individual();
};
#endif 
