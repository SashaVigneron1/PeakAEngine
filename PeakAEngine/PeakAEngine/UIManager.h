#pragma once
#include "Singleton.h"

#include "UIElement.h"

#define UI UIManager::GetInstance()

class UIManager final : public Singleton<UIManager>
{
	friend class Singleton<UIManager>;

public:
	void Destroy();

	void AddImage(const std::string& imagePath, const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor);
	//void AddText(text, const std::string& fontPath, const glm::vec2& pos, const glm::vec2& size, AnchorPosition anchor);
	//void AddButton(button, const glm::vec2& pos, const glm::vec2& size, AnchorPosition anchor);
	//void AddSlider(...);

	void Update();
	void Render();

private:
	std::vector<UIElement*> m_pUIElements;
};