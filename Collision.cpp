#include "Collision.h"

bool Collision::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB)
{
	if (rectA.x + rectA.w < rectB.x || //rectA is to the left of rectB
		rectB.x + rectB.w < rectA.x || //rectB is to the right of rectA
		rectA.y + rectA.h < rectB.y || //rectA is over rectB
		rectB.y + rectB.h < rectA.y)   //rectB is over rectA
	{
		return false;
	}

	return true;
}

