#ifndef FEAT_H
#define FEAT_H
class Individual;

/*
 * Class that holds the data of a certain individual.
 * This container can be used for holding deterministic features or
 * sets of samples.
 */
class Feature{
private:
	// external references
	Individual ind;
	// class data
	std::string description;
	
public:
	// Constructor
	Feature();
};
#endif

