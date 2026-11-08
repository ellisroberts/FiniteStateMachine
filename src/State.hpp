#ifndef STATE_HPP
#define STATE_HPP

#include <memory>
#include <string>

namespace Utilities
{
    const std::string NumString = "0123456789";
}

class State
{
public:
    virtual ~State() = default;
    virtual std::shared_ptr<State> Transition(std::string const& Arg, char input) = 0;  
    virtual void Reset() {} // Allows singletons to clear temporary context between strings
};

#endif // STATE_HPP
