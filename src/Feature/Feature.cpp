#include "Feature.hpp"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
Feature::Feature(){
	ind = NULL;
}

Feature::Feature(Individual *owner){
	ind = owner;
}

Feature::Feature(Individual *owner, std::string name){
	ind = owner;
	description = name;
}

Feature::Feature(std::string name){
	ind = NULL;
	description = name;
}

/*******************************************************************************
 * Description handling functions
 ******************************************************************************/
std::string Feature::describe(){
	return description;
}

void Feature::describe(std::string name){
	description = name;
}

/*******************************************************************************
 * Individual (owner) handling functions
 ******************************************************************************/
Individual* Feature::parent(){
	return ind;
}

void Feature::parent(Individual* owner){
	ind = owner;
}
