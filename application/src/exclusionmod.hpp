#ifndef EXCLUSIONMOD_HPP
#define EXCLUSIONMOD_HPP

#include "modifier.hpp"

/**
 * @brief The ExclusionMod class
 */
class ExclusionMod : public Modifier
{
public:
    ExclusionMod();

    void apply();
    void train();
};

#endif // EXCLUSIONMOD_HPP
