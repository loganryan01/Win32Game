#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "renderer.h"

class Player : public GameObject
{
public:
	Player(int x, int y, const dewcin::RGBColor& color);
	void Update(float delta) override;
	void Render() override;

private:
	int posX, posY;
	const dewcin::RGBColor& playerColor;
};

#endif