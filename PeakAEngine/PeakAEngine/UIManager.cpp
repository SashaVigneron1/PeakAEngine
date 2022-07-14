#include "PeakAEnginePCH.h"
#include "UIManager.h"

#include "InputManager.h"
#include "UI_Image.h"
#include "UI_Button.h"
#include "UI_Text.h"

void UIManager::Destroy()
{
	for (auto obj : m_pUIElements) 
	{
		delete obj.pUIElement;
	}
}

int UIManager::AddImage(const std::string& imagePath, const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor)
{
	UIElementPair pair{ new UI_Image(imagePath,
		pos, size, pivot, anchor), int(m_pUIElements.size()) };

	m_pUIElements.push_back(pair);

	return pair.id;
}

//void UIManager::AddButton(const std::string& imageDefaultPath, const std::string& imageOnHoverPath, const std::string& imageOnClickPath, const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor)
//{
//	m_pUIElements.push_back(new UI_Button(imageDefaultPath, imageOnHoverPath, imageOnClickPath, 
//		pos, size, pivot, anchor));
//}

int UIManager::AddButton(UI_Button* pButton)
{
	UIElementPair pair{ pButton, int(m_pUIElements.size()) };

	m_pUIElements.push_back(pair);

	return pair.id;
}

int UIManager::AddText(const std::string& text, const std::string& fontPath, int lineSpacing, TextAlignment alignment
	, const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor)
{
	UIElementPair pair{ new UI_Text(text, fontPath, lineSpacing, alignment,
		pos, size, pivot, anchor), int(m_pUIElements.size())};

	m_pUIElements.push_back(pair);

	return pair.id;
}

UIElement* UIManager::GetUIElement(int id) const
{
	if (id >= m_pUIElements.size() || id < 0)
		return nullptr;

	return m_pUIElements[id].pUIElement;
}

void UIManager::Update()
{
	// For All (active) Components
	for (const auto& uiElementPair : m_pUIElements)
	{
		const auto& uiElement = uiElementPair.pUIElement;

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

			if (uiElement->IsHovered() && INPUTMANAGER.GetMouseButtonPressed(MouseButton::LMB))
				uiElement->OnClick();
		}
	}
}

void UIManager::Render()
{
	for (auto uiElementPair : m_pUIElements)
	{
		const auto& uiElement = uiElementPair.pUIElement;

		if (uiElement->IsActive())
			uiElement->Render();
	}
}
