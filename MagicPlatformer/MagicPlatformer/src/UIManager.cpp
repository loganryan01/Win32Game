#include "UIManager.h"

void UIManager::AddElement(std::shared_ptr<UIElement> element)
{
	elements.push_back(element);
}

void UIManager::RemoveElement(std::shared_ptr<UIElement> element)
{
	for (int i = 0; i < elements.size(); i++)
	{
		if (elements[i] == element)
		{
			auto iter = elements.begin() + i;
			elements.erase(iter);
		}
	}
}

void UIManager::Render()
{
	for (auto& uiElement : elements)
	{
		uiElement->Render();
	}
}
