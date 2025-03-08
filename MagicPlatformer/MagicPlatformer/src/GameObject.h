#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <Windows.h>

#include "dewcin/renderer.h"

// TODO: Create ground object

class GameObject
{
public:
	dewcin::Rect bounds;

	virtual ~GameObject() = default;

	virtual void Update(float delta) = 0;
	virtual void Render() = 0;

	virtual void OnCollision(GameObject* other) = 0;
};

#endif