#ifndef INVALID_HPP
#define INVALID_HPP

#include "State.hpp"

class Invalid final : public State
{
private:
    static std::shared_ptr<Invalid> m_Instance;
    Invalid() = default;

public:
    static std::shared_ptr<State> GetInstance();
    std::shared_ptr<State> Transition(std::string const& Arg, char input) override;
};

#endif // INVALID_HPP
