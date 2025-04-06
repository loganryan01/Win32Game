#pragma once
#include <vector>
#include <memory>
#include "dewcin/renderer.h"
class UIElement;

class UIManager
{
public:
	void AddElement(std::shared_ptr<UIElement> element);
	void RemoveElement(std::shared_ptr<UIElement> element);
	void Render();

private:
	std::vector<std::shared_ptr<UIElement>> elements;
};

class UIElement
{
public:
	virtual void Render() = 0;
	virtual ~UIElement() = default;
};

class UIText : public UIElement
{
public:
	UIText(int _xPos, int _yPos, int _scale, const char* _text, const dewcin::RGBColor& _color) :
		xPos(_xPos), yPos(_yPos), scale(_scale), text(_text), color(_color)
	{

	}
	
	void Render() override
	{
		dewcin::Renderer::DrawTextOnBitmap(xPos, yPos, scale, text, color);
	}

private:
	int xPos;
	int yPos;
	int scale;
	const char* text;
	const dewcin::RGBColor& color;
};