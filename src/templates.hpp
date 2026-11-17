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


template <Type type>
class Number final : public State
{
private:
    static inline std::shared_ptr<Number<type>> m_Instance;
    Number() = default;

public:
    static std::shared_ptr<State> GetInstance();
    std::shared_ptr<State> Transition(std::string const& Arg, char input) override;

};

template <DotType type>
class Dot final : public State
{
private:
    static inline std::shared_ptr<Dot<type>> m_Instance = nullptr;
    Dot() = default;

public:
    static std::shared_ptr<State> GetInstance();
    std::shared_ptr<State> Transition(std::string const& Arg, char input) override;
};

template <SignType type>
class PlusMinus final : public State
{
private:
    static inline std::shared_ptr<PlusMinus<type>> m_Instance = nullptr;
    PlusMinus() = default;

public:
    static std::shared_ptr<State> GetInstance();
    std::shared_ptr<State> Transition(std::string const& Arg, char input) override;
};

extern template class Number<Type::Regular>;
extern template class Number<Type::Exponential>;
extern template class Number<Type::Fraction>;

extern template class Dot<DotType::Regular>;
extern template class Dot<DotType::Init>;

extern template class PlusMinus<SignType::Regular>;
extern template class PlusMinus<SignType::Exponential>;

#endif /* TEMPLATES_HPP_ */
