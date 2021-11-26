#pragma once
#include "HitType.h"

struct KeyHighlight
{
	double m_Beat;
	HitType m_HitType;
public:
	KeyHighlight(double beat, HitType hit);
	KeyHighlight();
};
