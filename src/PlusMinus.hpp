#ifndef PLUSMINUS_HPP
#define PLUSMINUS_HPP

#include "State.hpp"

class PlusMinus final : public State
{
private:
    static std::shared_ptr<PlusMinus> m_Instance;
    PlusMinus() = default;

public:
    static std::shared_ptr<State> GetInstance();
    std::shared_ptr<State> Transition(std::string const& Arg, char input) override;
};

#endif // PLUSMINUS_HPP
