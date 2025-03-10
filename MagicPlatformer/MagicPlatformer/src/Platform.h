#ifndef PLATFORM_H
#define PLATFORM_H

#include "GameObject.h"

class Platform : public GameObject
{
public:
	Platform(float x, float y, const dewcin::RGBColor& color, int platformId);
	void Update(float delta) override;
	void Render() override;

	void OnCollision(GameObject* other) override;

private:
	Matrix3x3 getTransformationMatrix() const;

private:
	float scaleX, scaleY;

	const dewcin::RGBColor& platformColor;
};

#endif