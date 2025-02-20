#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <Windows.h>

class GameObject
{
public:
	virtual ~GameObject() = default;

	virtual void Update(float delta) = 0;
	virtual void Render() = 0;
};

#endif