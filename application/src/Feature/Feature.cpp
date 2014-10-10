#include "Feature.hpp"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
/**
 * @brief Simple constructor.
 */
Feature::Feature(){
	ind = NULL;
}

/**
 * @brief Constructor specifying the Individual to which this Feature was attributed.
 * @param owner Individual to which the Feature was attributed.
 */
Feature::Feature(Individual *owner){
	ind = owner;
}

/**
 * @brief Constructor specifying the Individual to which this Feature was attributed as well as the description of the feature.
 * @param owner Individual to which the Feature was attributed.
 * @param name Description of the Feature.
 */
Feature::Feature(Individual *owner, std::string name){
	ind = owner;
	description = name;
}

/**
 * @brief Constructor providing only the description of the Feature.
 * @param name Description of the Feature.
 */
Feature::Feature(std::string name){
	ind = NULL;
	description = name;
}

/*******************************************************************************
 * Description handling functions
 ******************************************************************************/
/**
 * @brief Gets the description of the Feature.
 * @return Description of the Feature.
 */
std::string Feature::describe(){
	return description;
}

/**
 * @brief Sets the description of the Feature.
 * @param name Description of the Feature.
 */
void Feature::describe(std::string name){
	description = name;
}

/*******************************************************************************
 * Individual (owner) handling functions
 ******************************************************************************/
/**
 * @brief Gets the parent of the Feature.
 * @return A pointer to the Individual to whom the feature is attributed to.
 */
Individual* Feature::parent(){
	return ind;
}

/**
 * @brief Sets the parent of the Feature.
 * @param owner A pointer to the Individual to whom this Feature is attributed to.
 */
void Feature::parent(Individual* owner){
	ind = owner;
}
