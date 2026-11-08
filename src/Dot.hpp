#ifndef DOT_HPP
#define DOT_HPP

#include "State.hpp"
#include "Number.hpp"
#include "Invalid.hpp"
#include "Exponent.hpp"
#include "enums.hpp"
#include <type_traits>

template <Type type> class Number;

template <DotType type>
class Dot final : public State
{
private:
    static inline std::shared_ptr<Dot<type>> m_Instance = nullptr;
    Dot() = default;

public:
    static std::shared_ptr<State> GetInstance()
    {
        if (!m_Instance)
        {
            m_Instance = std::shared_ptr<Dot<type>>(new Dot<type>());
        }
        return m_Instance;
    }
    std::shared_ptr<State> Transition(std::string const& Arg, char input) override
    {
        if (Utilities::NumString.find(input) != std::string::npos)
        {
            return Number<Type::Fraction>::GetInstance();
        }
        if constexpr(type == DotType::Regular)
		{
			switch (input)
			{
				case 'e':
				case 'E':
					return Exponent::GetInstance();
				default:
					return Invalid::GetInstance();
			}
		}
    }
};

#endif // DOT_HPP
