#pragma once
class KeyPressOnFrame
{
private:
	bool D_KeyPressedPrev = false;
	bool F_KeyPressedPrev = false;
	bool J_KeyPressedPrev = false;
	bool K_KeyPressedPrev = false;
public:
	bool UpperKeyPressed();
	bool LowerKeyPressed();
};

