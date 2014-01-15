#ifndef MODIFIER_HPP
#define MODIFIER_HPP

///
/// \brief The Modifier class
///
class Modifier
{
public:
    virtual void apply() = 0;
    virtual void train() = 0;
};

#endif // MODIFIER_HPP
