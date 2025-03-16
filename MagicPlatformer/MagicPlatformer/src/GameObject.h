#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <Windows.h>

#include "dewcin/renderer.h"
#include "maths/Vector.h"

class GameObject
{
public:
	int id;
	dewcin::Rect bounds;

	// Transform
	Vector2 position;
	Vector2 scale;

	virtual ~GameObject() = default;

	virtual void Update(float delta) = 0;
	virtual void Render() = 0;

	virtual void OnCollision(GameObject* other) = 0;
};

#endif