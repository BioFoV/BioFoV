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
    /// \brief Pointer to the Individual to which this Feature was attributed.
	Individual *ind;
    /// \brief Text describing the Feature.
	std::string description;
	
public:
	// Constructors
    /// \brief Simple constructor.
	Feature();
    /// \brief Constructor specifying the Individual to which this Feature was
    ///attributed.
    /// \param owner Individual to which the Feature was attributed.
	Feature(Individual* owner);
    /// \brief Constructor specifying the Individual to which this Feature was
    ///attributed as well as the description of the feature.
    /// \param owner Individual to which the Feature was attributed.
    /// \param name Description of the Feature.
	Feature(Individual* owner, std::string name);
    /// \brief Constructor providing only the description of the Feature.
    /// \param name Description of the Feature.
	Feature(std::string name);
	
	// Description handling functions
    /// \brief Gets the description of the Feature.
    /// \return Description of the Feature.
	std::string describe();
    /// \brief Sets the description of the Feature.
    /// \param name Description of the Feature.
	void describe(std::string name);
	
	// Individual (owner) handling functions
    /// \brief Gets the parent of the Feature.
    /// \return A pointer to the Individual to whom the feature is attributed
    ///to.
	Individual* parent();
    /// \brief Sets the parent of the Feature.
    /// \param owner A pointer to the Individual to whom this Feature is
    ///attributed to.
	void parent(Individual* owner);
};
#endif
