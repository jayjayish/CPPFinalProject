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

#define CheckKeyPressed(t, p, k)\
{\
    if ((k) && (!p))\
    {\
        t = true;\
        p = true;\
    }\
    else if (!k)\
    {\
        p = false;\
    }\
}

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
    CheckKeyPressed(UpperPressed, F_KeyPressedPrev, sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F))
    CheckKeyPressed(UpperPressed, D_KeyPressedPrev, sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))

    LowerPressed = false;
    CheckKeyPressed(LowerPressed, J_KeyPressedPrev, sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J))
    CheckKeyPressed(LowerPressed, K_KeyPressedPrev, sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))

    MousePressed = false;
    CheckKeyPressed(MousePressed, MousePressedPrev, sf::Mouse::isButtonPressed(sf::Mouse::Left))
}



