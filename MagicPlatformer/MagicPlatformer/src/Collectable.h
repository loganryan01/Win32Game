#ifndef COLLECTABLE_H
#define COLLECTABLE_H
#include "GameObject.h"

class Collectable : public GameObject
{
public:
	Collectable(int xPos, int yPos, int scaleX, int scaleY, const dewcin::RGBColor& color, int collectableId);
	void Update(float delta) override;
	void Render() override;

	void OnCollisionEnter(GameObject* other) override;

private:
	Matrix3x3 getTransformationMatrix() const;

private:
	const dewcin::RGBColor& collectableColor;
};

#endif