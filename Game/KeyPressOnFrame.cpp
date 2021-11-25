#include "Precompiled.h"
#include "KeyPressOnFrame.h"

bool KeyPressOnFrame::UpperKeyPressed()
{
    bool returnVal = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F) && !F_KeyPressedPrev)
    {
        F_KeyPressedPrev = true;
        returnVal = true;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F))
    {
        F_KeyPressedPrev = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && !D_KeyPressedPrev)
    {
        D_KeyPressedPrev = true;
        returnVal = true;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        D_KeyPressedPrev = false;
    }

    return returnVal;
}

bool KeyPressOnFrame::LowerKeyPressed()
{
    bool returnVal = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J) && !J_KeyPressedPrev)
    {
        J_KeyPressedPrev = true;
        returnVal = true;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J))
    {
        J_KeyPressedPrev = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K) && !K_KeyPressedPrev)
    {
        K_KeyPressedPrev = true;
        returnVal = true;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))
    {
        K_KeyPressedPrev = false;
    }

    return returnVal;
}
