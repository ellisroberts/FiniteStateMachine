#ifndef INIT_HPP
#define INIT_HPP

#include "State.hpp"

class Init final : public State
{
private:
    static std::shared_ptr<Init> m_Instance;
    Init() = default;

public:
    static std::shared_ptr<State> GetInstance();
    std::shared_ptr<State> Transition(std::string const& Arg, char input) override;
};

#endif // INIT_HPP
