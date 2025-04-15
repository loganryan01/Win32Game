#ifndef COLLIDER_H
#define COLLIDER_H

#include "dewcin/renderer.h"

#include <memory>
#include <vector>

class GameObject;

class Collider
{
public:
	dewcin::Rect bounds;
	bool isTrigger = false;

	// Current and previous collision state
	std::vector<std::shared_ptr<GameObject>> currentCollisions;
	std::vector<std::shared_ptr<GameObject>> previousCollisions;

	Collider(int x, int y, int w, int h)
	{
		bounds = { x, y, w, h };
	}

	void UpdatePosition(int x, int y)
	{
		bounds.x = x;
		bounds.y = y;
	}
};

#endif