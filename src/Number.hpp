#ifndef NUMBER_HPP
#define NUMBER_HPP

#include "State.hpp"
#include "Dot.hpp"
#include "Exponent.hpp"
#include "Invalid.hpp"
#include "enums.hpp"
#include <type_traits>

template <DotType type> class Dot;

template <Type type>
class Number final : public State
{
private:
    static inline std::shared_ptr<Number<type>> m_Instance;
    Number() = default;

public:
    static std::shared_ptr<State> GetInstance()
    {
        if (!m_Instance)
        {
            m_Instance = std::shared_ptr<Number<type>>(new Number<type>());
        }
        return m_Instance;
    }
    std::shared_ptr<State> Transition(std::string const& Arg, char input) override
    {
        if (Utilities::NumString.find(input) != std::string::npos)
        {

            if constexpr(type == Type::Regular)
            {
                return Number<Type::Regular>::GetInstance();
            }
            if constexpr(type == Type::Exponential)
            {
			    return Number<Type::Exponential>::GetInstance();
            }
            if constexpr(type == Type::Fraction)
            {
                return Number<Type::Fraction>::GetInstance();
            }
        }

        if constexpr(type == Type::Regular)
        {
                if (input == '.')
                    return Dot<DotType::Regular>::GetInstance();
        }
        if constexpr(type != Type::Exponential)
        {
            if ((input == 'e')||(input == 'E'))
                return Exponent::GetInstance();
        }
        return Invalid::GetInstance();
    }
};

#endif // NUMBER_HPP
