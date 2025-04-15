#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <Windows.h>

#include "dewcin/renderer.h"
#include "maths/Vector.h"
#include "Collider.h"

class GameObject
{
public:
	int id;
	dewcin::Rect bounds;

	Collider* collider = nullptr;

	// Transform
	Vector2 position;
	Vector2 scale;

	virtual ~GameObject() = default;

	virtual void Update(float delta) = 0;
	virtual void Render() = 0;

	virtual void OnCollisionEnter(GameObject* other) 
	{ 
		// EMPTY 
	}
	virtual void OnCollisionStay(GameObject* other) 
	{
		// EMPTY
	}
	virtual void OnCollisionExit(GameObject* other) 
	{
		// EMPTY
	}
};

#endif