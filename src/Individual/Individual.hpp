#ifndef INDIV_H
#define INDIV_H
class Event;
class Snapshot;

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
	
public:
	// Constructor
	Individual();
};
#endif 

