#include "PeakAEnginePCH.h"
#include "UIManager.h"

#include "Managers.h"
#include "UI_Image.h"
#include "UI_Button.h"
#include "UI_Text.h"
#include "UI_InputField.h"

void UIManager::Destroy()
{
	for (auto obj : m_pUIElements) 
	{
		delete obj.pUIElement;
	}
}

int UIManager::AddImage(const std::string& sceneName,
	const std::string& imagePath, const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor)
{
	UIElementPair pair{ sceneName, new UI_Image(imagePath,
		pos, size, pivot, anchor), int(m_pUIElements.size()) };

	m_pUIElements.push_back(pair);

	return pair.id;
}

int UIManager::AddButton(const std::string& sceneName,
	UI_Button* pButton)
{
	UIElementPair pair{ sceneName, pButton, int(m_pUIElements.size()) };

	m_pUIElements.push_back(pair);

	return pair.id;
}

int UIManager::AddText(const std::string& sceneName,
	const std::string& text, const std::string& fontPath, int lineSpacing, TextAlignment alignment
	, const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor)
{
	UIElementPair pair{ sceneName, new UI_Text(text, fontPath, lineSpacing, alignment,
		pos, size, pivot, anchor), int(m_pUIElements.size())};

	m_pUIElements.push_back(pair);

	return pair.id;
}

int UIManager::AddInputField(const std::string& sceneName,
	const std::string& defaultText, const std::string& fontPath, int charSize, int lineSpacing, TextAlignment alignment, float sizeOffset, const std::string& bgImagePath, const SDL_Color& colorActive, const SDL_Color& colorInactive, const SDL_Color& colorDefault, const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor)
{
	UIElementPair pair{ sceneName, new UI_InputField(defaultText, fontPath, charSize, lineSpacing, alignment, sizeOffset, bgImagePath,
		colorActive, colorInactive, colorDefault,
		pos, size, pivot, anchor), int(m_pUIElements.size()) };

	m_pUIElements.push_back(pair);

	return pair.id;
}

int UIManager::AddInputField(const std::string& sceneName,
	const std::string& defaultText, const std::string& fontPath, int charSize, int lineSpacing, TextAlignment alignment, float sizeOffset, const std::string& bgImagePath, const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor)
{
	UIElementPair pair{ sceneName, new UI_InputField(defaultText, fontPath, charSize, lineSpacing, alignment, sizeOffset, bgImagePath,
		pos, size, pivot, anchor), int(m_pUIElements.size()) };

	m_pUIElements.push_back(pair);

	return pair.id;
}

UIElement* UIManager::GetUIElement(int id) const
{
	if (id >= (int)m_pUIElements.size() || id < 0)
		return nullptr;

	return m_pUIElements[id].pUIElement;
}

void UIManager::Update()
{
	// For All (active) Components
	for (const auto& uiElementPair : m_pUIElements)
	{
		if (uiElementPair.sceneName != m_ActiveScene)
			continue;

		const auto& uiElement = uiElementPair.pUIElement;

		if (uiElement->IsActive())
		{
			// HOVERING EVENTS
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

			if (uiElement->IsHovered() && INPUTMANAGER->GetMouseButtonPressed(MouseButton::LMB))
				uiElement->OnClick();

			// UPDATE
			uiElement->Update();
		}
	}
}

void UIManager::Render()
{
	for (auto uiElementPair : m_pUIElements)
	{
		if (uiElementPair.sceneName != m_ActiveScene)
			continue;

		const auto& uiElement = uiElementPair.pUIElement;

		if (uiElement->IsActive())
			uiElement->Render();
	}
}
