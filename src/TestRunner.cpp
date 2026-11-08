#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <memory>
#include <vector>
#include <iostream>

#include "Init.hpp"
#include "templates.hpp"
#include "Exponent.hpp"
#include "Invalid.hpp"

class StateMachineTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(StateMachineTest);
    // Original Test Suite
    CPPUNIT_TEST(testSingleSymbolsAndEmpty);
    CPPUNIT_TEST(testPureInteger);
    CPPUNIT_TEST(testStandardDecimal);
    CPPUNIT_TEST(testLeadingDecimal);
    CPPUNIT_TEST(testDoubleDecimal);
    CPPUNIT_TEST(testStandardExponent);
    CPPUNIT_TEST(testLargeExponent);
    CPPUNIT_TEST(testLeadingExponent);
    CPPUNIT_TEST(testDoubleExponent);
    CPPUNIT_TEST(testPositiveInteger);
    CPPUNIT_TEST(testNegativeInteger);
    CPPUNIT_TEST(testMidStringSignPositive);
    CPPUNIT_TEST(testMidStringSignNegative);

    // New Extended Test Requirements
    CPPUNIT_TEST(testValidLeetCodeNumbers);
    CPPUNIT_TEST(testInvalidLeetCodeNumbers);
    CPPUNIT_TEST(testValidLeetCodeNumbers2);
    CPPUNIT_TEST(testInvalidLeetCodeNumbers2);
    CPPUNIT_TEST_SUITE_END();

private:
    bool validateString(const std::string& input)
    {
        if (input.empty()) return false;

        std::shared_ptr<State> current = Init::GetInstance();
        std::string buffer = "";

        for (char c : input)
        {
            buffer += c;
            current = current->Transition(buffer, c);
        }

        // Accepting final terminal positions
        return (current == Number<Type::Regular>::GetInstance() || current == Number<Type::Fraction>::GetInstance() ||
        		current == Number<Type::Exponential>::GetInstance() || current == Dot<DotType::Regular>::GetInstance());
    }

public:
    void testSingleSymbolsAndEmpty()
    {
        CPPUNIT_ASSERT(!validateString("+"));
        CPPUNIT_ASSERT(!validateString("-"));
        CPPUNIT_ASSERT(!validateString("."));
        CPPUNIT_ASSERT(!validateString("e"));
        CPPUNIT_ASSERT(!validateString(""));
        CPPUNIT_ASSERT(validateString("1"));
    }

    void testPureInteger() { CPPUNIT_ASSERT(validateString("234567")); }
    void testStandardDecimal() { CPPUNIT_ASSERT(validateString("2.345")); }
    void testLeadingDecimal() { CPPUNIT_ASSERT(validateString(".2345")); }
    void testDoubleDecimal() { CPPUNIT_ASSERT(!validateString(".2.3")); }
    void testStandardExponent() { CPPUNIT_ASSERT(validateString("24e3")); }
    void testLargeExponent() { CPPUNIT_ASSERT(validateString("2e45")); }
    void testLeadingExponent() { CPPUNIT_ASSERT(!validateString("e4")); }
    void testDoubleExponent() { CPPUNIT_ASSERT(!validateString("2e3e4")); }
    void testPositiveInteger() { CPPUNIT_ASSERT(validateString("+2345")); }
    void testNegativeInteger() { CPPUNIT_ASSERT(validateString("-2345")); }
    void testMidStringSignPositive() { CPPUNIT_ASSERT(!validateString("+2-3")); }
    void testMidStringSignNegative() { CPPUNIT_ASSERT(!validateString("-2+4")); }

    // New Test Cases: Verified Valid Lists
    void testValidLeetCodeNumbers()
    {
        CPPUNIT_ASSERT_MESSAGE("Failed on '2'", validateString("2"));
        CPPUNIT_ASSERT_MESSAGE("Failed on '0089'", validateString("0089"));
        CPPUNIT_ASSERT_MESSAGE("Failed on '-0.1'", validateString("-0.1"));
        CPPUNIT_ASSERT_MESSAGE("Failed on '+3.14'", validateString("+3.14"));
        CPPUNIT_ASSERT_MESSAGE("Failed on '4.'", validateString("4."));
        CPPUNIT_ASSERT_MESSAGE("Failed on '-.9'", validateString("-.9"));
        CPPUNIT_ASSERT_MESSAGE("Failed on '2e10'", validateString("2e10"));
        CPPUNIT_ASSERT_MESSAGE("Failed on '-90E3'", validateString("-90E3"));
        CPPUNIT_ASSERT_MESSAGE("Failed on '3e+7'", validateString("3e+7"));
        CPPUNIT_ASSERT_MESSAGE("Failed on '+6e-1'", validateString("+6e-1"));
        CPPUNIT_ASSERT_MESSAGE("Failed on '53.5e93'", validateString("53.5e93"));
        CPPUNIT_ASSERT_MESSAGE("Failed on '-123.456e789'", validateString("-123.456e789"));
    }

    // New Test Cases: Verified Invalid Lists
    void testInvalidLeetCodeNumbers()
    {
        CPPUNIT_ASSERT_MESSAGE("'abc' should be invalid", !validateString("abc"));
        CPPUNIT_ASSERT_MESSAGE("'1a' should be invalid", !validateString("1a"));
        CPPUNIT_ASSERT_MESSAGE("'1e' should be invalid", !validateString("1e"));
        CPPUNIT_ASSERT_MESSAGE("'e3' should be invalid", !validateString("e3"));
        CPPUNIT_ASSERT_MESSAGE("'99e2.5' should be invalid", !validateString("99e2.5"));
        CPPUNIT_ASSERT_MESSAGE("'--6' should be invalid", !validateString("--6"));
        CPPUNIT_ASSERT_MESSAGE("'-+3' should be invalid", !validateString("-+3"));
        CPPUNIT_ASSERT_MESSAGE("'95a54e53' should be invalid", !validateString("95a54e53"));
    }

    void testValidLeetCodeNumbers2()
    {
        // ... your existing valid tests ...

        // Crucial boundary extensions that MUST pass
        CPPUNIT_ASSERT_MESSAGE("Failed on '0'", validateString("0"));
        CPPUNIT_ASSERT_MESSAGE("Failed on '.0'", validateString(".0"));
        CPPUNIT_ASSERT_MESSAGE("Failed on '0.'", validateString("0."));
        CPPUNIT_ASSERT_MESSAGE("Failed on '4.e3'", validateString("4.e3"));
        CPPUNIT_ASSERT_MESSAGE("Failed on '+4.e-3'", validateString("+4.e-3"));
        CPPUNIT_ASSERT_MESSAGE("Failed on '.5e3'", validateString(".5e3"));
    }

    void testInvalidLeetCodeNumbers2()
    {
        // ... your existing invalid tests ...

        // Crucial boundary extensions that MUST fail
        CPPUNIT_ASSERT_MESSAGE("'+.' should be invalid", !validateString("+."));
        CPPUNIT_ASSERT_MESSAGE("'-.' should be invalid", !validateString("-."));
        CPPUNIT_ASSERT_MESSAGE("'1e.' should be invalid", !validateString("1e."));
        CPPUNIT_ASSERT_MESSAGE("'1e.5' should be invalid", !validateString("1e.5"));
        CPPUNIT_ASSERT_MESSAGE("'1e+' should be invalid", !validateString("1e+"));
        CPPUNIT_ASSERT_MESSAGE("'1e-' should be invalid", !validateString("1e-"));
        CPPUNIT_ASSERT_MESSAGE("'6e7.' should be invalid", !validateString("6e7."));
        CPPUNIT_ASSERT_MESSAGE("' 1 ' should be invalid", !validateString(" 1 "));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(StateMachineTest);

int main()
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry& registry = CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());

    std::cout << "\n--- Running Comprehensive Finite State Machine Tests ---\n";
    bool wasSuccessful = runner.run("", false);

    return wasSuccessful ? 0 : 1;
}
