#ifndef INC_INDIVIDUAL
#define INC_INDIVIDUAL
#include "../Individual/Individual.hpp"
#endif

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
	Individual *ind;
	// class data
	std::string description;
	
public:
	// Constructors
	Feature();
	Feature(Individual* owner);
	Feature(Individual* owner, std::string name);
	Feature(std::string name);
	
	// Description handling functions
	std::string describe();
	void describe(std::string name);
	
	// Individual (owner) handling functions
	Individual* parent();
	void parent(Individual* owner);
};
#endif
