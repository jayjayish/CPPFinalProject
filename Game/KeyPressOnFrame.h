#pragma once
#include "NoteTrackEnum.h"

class KeyPressOnFrame
{
private:
	static bool D_KeyPressedPrev;
	static bool F_KeyPressedPrev;
	static bool UpperPressed;

	static bool J_KeyPressedPrev;
	static bool K_KeyPressedPrev;
	static bool LowerPressed;
public:
	bool KeyPressed(NoteTrack);
	void Update();
};

