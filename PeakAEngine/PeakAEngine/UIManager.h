#pragma once
#include "Singleton.h"

#include "UIElement.h"

class UI_Button;

#define UI UIManager::GetInstance()

class UIManager final : public Singleton<UIManager>
{
	friend class Singleton<UIManager>;

public:
	void Destroy();

	void AddImage(const std::string& imagePath, 
		const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor);

	/*void AddButton(const std::string& imageDefaultPath, const std::string& imageOnHoverPath, const std::string& imageOnClickPath,
		const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor);*/
	void AddButton(UI_Button* pButton);

	//void AddText(text, const std::string& fontPath, const glm::vec2& pos, const glm::vec2& size, AnchorPosition anchor);
	//void AddSlider(...);

	void Update();
	void Render();

private:
	std::vector<UIElement*> m_pUIElements;
};