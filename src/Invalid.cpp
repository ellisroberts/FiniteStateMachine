#include "Invalid.hpp"

std::shared_ptr<Invalid> Invalid::m_Instance = nullptr;

std::shared_ptr<State> Invalid::GetInstance()
{
    if (!m_Instance)
    {
        m_Instance = std::shared_ptr<Invalid>(new Invalid());
    }
    return m_Instance;
}

std::shared_ptr<State> Invalid::Transition(std::string const& Arg, char input)
{
    return m_Instance;
}
