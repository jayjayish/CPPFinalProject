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

	static bool MousePressedPrev;
	static bool MousePressed;
public:
	static bool MouseLeftPressed();
	static bool KeyPressed(NoteTrack);
	static void Update();

	KeyPressOnFrame() = default;
	KeyPressOnFrame(const KeyPressOnFrame&) = delete;
	KeyPressOnFrame& operator=(const KeyPressOnFrame&) = delete;
};

