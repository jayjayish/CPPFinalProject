#include "Precompiled.h"
#include "KeyHighlightStruct.h"

KeyHighlight::KeyHighlight(double beat, HitType hit)
	:m_Beat(beat),
	m_HitType(hit)
{}

KeyHighlight::KeyHighlight()
	:m_Beat(0.0),
	m_HitType(HitType::Perfect)
{}
