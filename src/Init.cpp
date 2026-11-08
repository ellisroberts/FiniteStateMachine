#include "Init.hpp"
#include "templates.hpp"
#include "Invalid.hpp"

std::shared_ptr<Init> Init::m_Instance = nullptr;

std::shared_ptr<State> Init::GetInstance()
{
    if (!m_Instance)
    {
        m_Instance = std::shared_ptr<Init>(new Init());
    }
    return m_Instance;
}

std::shared_ptr<State> Init::Transition(std::string const& Arg, char input)
{
    if (Utilities::NumString.find(input) != std::string::npos)
    {
        return Number<Type::Regular>::GetInstance();
    }
    
    switch (input)
    {
        case '+':
        case '-':
            return PlusMinus<SignType::Regular>::GetInstance();
        case '.':
            return Dot<DotType::Init>::GetInstance();
        default:
            return Invalid::GetInstance();
    }
}
