/*
 * templates.hpp
 *
 *  Created on: Nov 7, 2026
 *      Author: ellis
 */

#ifndef TEMPLATES_HPP_
#define TEMPLATES_HPP_

#include "State.hpp"
#include "Invalid.hpp"
#include "Exponent.hpp"
#include "enums.hpp"
#include <type_traits>

template <DotType type> class Dot;
template <Type type> class Number;

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
    std::shared_ptr<State> Transition(std::string const& Arg, char input) override;

};

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
			if ((input == 'e')||(input == 'E'))
			{
			    return Exponent::GetInstance();
			}
		}
        return Invalid::GetInstance();
    }
};

template <SignType type>
class PlusMinus final : public State
{
private:
    static inline std::shared_ptr<PlusMinus<type>> m_Instance = nullptr;
    PlusMinus() = default;

public:
    static std::shared_ptr<State> GetInstance()
    {
        if (!m_Instance)
        {
            m_Instance = std::shared_ptr<PlusMinus<type>>(new PlusMinus<type>());
        }
        return m_Instance;
    }
    std::shared_ptr<State> Transition(std::string const& Arg, char input) override
    {
        if (Utilities::NumString.find(input) != std::string::npos)
        {
        	if constexpr (type == SignType::Regular)
                return Number<Type::Regular>::GetInstance();
        	else
                return Number<Type::Exponential>::GetInstance();
        }
        if constexpr (type == SignType::Regular)
		{
			if (input == '.')
			{
				return Dot<DotType::Init>::GetInstance();
			}
		}
        return Invalid::GetInstance();
    }
};

template <Type type>
std::shared_ptr<State> Number<type>::Transition(std::string const& Arg, char input)
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




#endif /* TEMPLATES_HPP_ */
