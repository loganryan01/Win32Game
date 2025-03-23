#ifndef PLATFORM_H
#define PLATFORM_H

#include "GameObject.h"

class Platform : public GameObject
{
public:
	Platform(int xPos, int yPos, int scaleX, int scaleY, const dewcin::RGBColor& color, int platformId);
	void Update(float delta) override;
	void Render() override;

	void OnCollision(GameObject* other) override;

private:
	Matrix3x3 getTransformationMatrix() const;

private:
	const dewcin::RGBColor& platformColor;
};

#endif