#include "Precompiled.h"
#include "KeyPressOnFrame.h"

bool KeyPressOnFrame::D_KeyPressedPrev = false;
bool KeyPressOnFrame::F_KeyPressedPrev = false;
bool KeyPressOnFrame::J_KeyPressedPrev = false;
bool KeyPressOnFrame::K_KeyPressedPrev = false;
bool KeyPressOnFrame::LowerPressed = false;
bool KeyPressOnFrame::UpperPressed = false;
bool KeyPressOnFrame::MousePressedPrev = false;
bool KeyPressOnFrame::MousePressed = false;

bool KeyPressOnFrame::KeyPressed(NoteTrack track)
{
    if (track == NoteTrack::Upper)
    {
        return UpperPressed;
    }
    else if (track == NoteTrack::Lower)
    {
        return LowerPressed;
    }

    throw "This shouldn't happen";
}

bool KeyPressOnFrame::MouseLeftPressed()
{
    return MousePressed;
}

void KeyPressOnFrame::Update()
{
    UpperPressed = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F) && !F_KeyPressedPrev)
    {
        F_KeyPressedPrev = true;
        UpperPressed = true;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F))
    {
        F_KeyPressedPrev = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && !D_KeyPressedPrev)
    {
        D_KeyPressedPrev = true;
        UpperPressed = true;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        D_KeyPressedPrev = false;
    }

    LowerPressed = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J) && !J_KeyPressedPrev)
    {
        J_KeyPressedPrev = true;
        LowerPressed = true;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J))
    {
        J_KeyPressedPrev = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K) && !K_KeyPressedPrev)
    {
        K_KeyPressedPrev = true;
        LowerPressed = true;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))
    {
        K_KeyPressedPrev = false;
    }

    MousePressed = false;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !MousePressedPrev)
    {
        MousePressedPrev = true;
        MousePressed = true;
    }
    else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        MousePressedPrev = false;
    }
}



