#pragma once
#include "Singleton.h"

#include "UIElement.h"

enum class TextAlignment
{
	Left,
	Center,
	Right
};

class UI_Button;
class UI_Text;

#define UI UIManager::GetInstance()

class UIManager final : public Singleton<UIManager>
{
	friend class Singleton<UIManager>;

public:
	void Destroy();

	int AddImage(const std::string& imagePath,
		const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor);

	int AddButton(UI_Button* pButton);

	int AddText(const std::string& text, const std::string& fontPath, int lineSpacing, TextAlignment alignment,
		const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor);

	int AddInputField(const std::string& defaultText, const std::string& fontPath, int charSize, int lineSpacing, TextAlignment alignment, float sizeOffset,
		const std::string& bgImagePath, const SDL_Color& colorActive, const SDL_Color& colorInactive, const SDL_Color& colorDefault,
		const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor);
	int AddInputField(const std::string& defaultText, const std::string& fontPath, int charSize, int lineSpacing, TextAlignment alignment, float sizeOffset,
		const std::string& bgImagePath,
		const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor);


	//void AddText(text, const std::string& fontPath, const glm::vec2& pos, const glm::vec2& size, AnchorPosition anchor);
	//void AddSlider(...);

	UIElement* GetUIElement(int id) const;

	void Update();
	void Render();

private:
	struct UIElementPair
	{
		UIElement* pUIElement;
		int id;
	};

	std::vector<UIElementPair> m_pUIElements;
};