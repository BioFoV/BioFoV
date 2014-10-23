#ifndef FEAT_H
#define FEAT_H

#ifndef INC_INDIVIDUAL
#define INC_INDIVIDUAL
#include <Individual/Individual.hpp>
#endif

#ifndef INC_STRING
#define INC_STRING
#include <string>
#endif

class Individual;

///
/// \brief Class that holds the data of a certain Individual.
///This container can be used for holding deterministic Features or sets of
///samples.
///
class Feature{
private:
	/**
	 * @brief Pointer to the Individual to which this Feature was attributed.
	 */
	Individual *ind;

	/**
	 * @brief Text describing the Feature.
	 */
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
