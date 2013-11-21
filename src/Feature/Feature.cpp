#include "Feature.hpp"

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

std::string Feature::describe(){
	return description;
}

void Feature::describe(std::string name){
	description = name;
}

Individual* Feature::parent(){
	return ind;
}

void Feature::parent(Individual* owner){
	ind = owner;
}
