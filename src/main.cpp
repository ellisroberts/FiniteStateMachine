#include <iostream>
#include "Init.hpp"
#include "Invalid.hpp"

int main()
{
    std::string testString = "+12.3E4";
    std::shared_ptr<State> currentState = Init::GetInstance();
    std::shared_ptr<State> trapState = Invalid::GetInstance();
    
    std::string processBuffer = "";

    std::cout << "Validating Input String: " << testString << "\n";
    for (char c : testString)
    {
        processBuffer += c;
        currentState = currentState->Transition(processBuffer, c);

        if (currentState == trapState)
        {
            std::cout << " State transitioned to INVALID at character '" << c << "'\n";
            break;
        }
        else
        {
            std::cout << " Successfully parsed symbol '" << c << "'\n";
        }
    }

    if (currentState != trapState)
    {
        std::cout << "String parsed successfully!\n";
    }
    
    return 0;
}
