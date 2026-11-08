#ifndef EXPONENT_HPP
#define EXPONENT_HPP

#include "State.hpp"

class Exponent final : public State
{
private:
    static std::shared_ptr<Exponent> m_Instance;
    Exponent() = default;

public:
    static std::shared_ptr<State> GetInstance();
    std::shared_ptr<State> Transition(std::string const& Arg, char input) override;
};

#endif // EXPONENT_HPP
