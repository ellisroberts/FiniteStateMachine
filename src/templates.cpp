/*
 * templates.cpp
 *
 *  Created on: Nov 8, 2026
 *      Author: ellis
 */

#include "templates.hpp"

//Number class methods

template <Type type>
std::shared_ptr<State>  Number<type>::GetInstance()
{
	if (!m_Instance)
	{
		m_Instance = std::shared_ptr<Number<type>>(new Number<type>());
	}
	return m_Instance;
}

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

template class Number<Type::Regular>;
template class Number<Type::Exponential>;
template class Number<Type::Fraction>;

//Dot Class Methods

template <DotType type>
std::shared_ptr<State> Dot<type>::GetInstance()
{
	if (!m_Instance)
	{
		m_Instance = std::shared_ptr<Dot<type>>(new Dot<type>());
	}
	return m_Instance;
}

template <DotType type>
std::shared_ptr<State> Dot<type>::Transition(std::string const& Arg, char input)
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

template class Dot<DotType::Regular>;
template class Dot<DotType::Init>;

//Sign Type Functions

template <SignType type>
std::shared_ptr<State> PlusMinus<type>::GetInstance()
{
	if (!m_Instance)
	{
		m_Instance = std::shared_ptr<PlusMinus<type>>(new PlusMinus<type>());
	}
	return m_Instance;
}

template <SignType type>
std::shared_ptr<State> PlusMinus<type>::Transition(std::string const& Arg, char input)
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
};

template class PlusMinus<SignType::Regular>;
template class PlusMinus<SignType::Exponential>;





