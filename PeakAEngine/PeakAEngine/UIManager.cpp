#include "PeakAEnginePCH.h"
#include "UIManager.h"

#include "UI_Image.h"

void UIManager::Destroy()
{
	for (auto obj : m_pUIElements) 
	{
		delete obj;
	}
}

void UIManager::AddImage(const std::string& imagePath, const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor)
{
	m_pUIElements.push_back(new UI_Image(imagePath, pos, size, pivot, anchor));
}

void UIManager::Update()
{
	// For All (active) Components
	for (const auto& uiElement : m_pUIElements)
	{
		if (uiElement->IsActive())
		{
			// Check if hovering
			bool wasHovering = uiElement->IsHovered();
			bool isHovering = uiElement->IsMouseOverlapping();

			// If is hovering: OnBeginHover
			if (!wasHovering && isHovering)
			{
				uiElement->OnBeginHover();
				uiElement->SetHovered(true);
			}
			// Else if was hovering but now not: OnEndHover
			else if (wasHovering && !isHovering)
			{
				uiElement->OnEndHover();
				uiElement->SetHovered(false);
			}
		}
	}
}

void UIManager::Render()
{
	for (auto uiElement : m_pUIElements)
	{
		if (uiElement->IsActive())
			uiElement->Render();
	}
}
