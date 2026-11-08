#include "Exponent.hpp"
#include "templates.hpp"
#include "Invalid.hpp"

std::shared_ptr<Exponent> Exponent::m_Instance = nullptr;

std::shared_ptr<State> Exponent::GetInstance()
{
    if (!m_Instance)
    {
        m_Instance = std::shared_ptr<Exponent>(new Exponent());
    }
    return m_Instance;
}

std::shared_ptr<State> Exponent::Transition(std::string const& Arg, char input)
{
    if (Utilities::NumString.find(input) != std::string::npos)
    {
        return Number<Type::Exponential>::GetInstance();
    }
    if ((input == '+') || (input == '-'))
    	return PlusMinus<SignType::Exponential>::GetInstance();
    return Invalid::GetInstance();
}
