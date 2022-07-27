#pragma once
#include "Manager.h"

#include "UIElement.h"

enum class TextAlignment
{
	Left,
	Center,
	Right
};

class UI_Button;
class UI_Text;

class UIManager final : public Manager
{
public:
	void Destroy();

	int AddImage(const std::string& sceneName,
		const std::string& imagePath,
		const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor);

	int AddButton(const std::string& sceneName,
		UI_Button* pButton);

	int AddText(const std::string& sceneName,
		const std::string& text, const std::string& fontPath, int lineSpacing, TextAlignment alignment,
		const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor);

	int AddInputField(const std::string& sceneName,
		const std::string& defaultText, const std::string& fontPath, int charSize, int lineSpacing, TextAlignment alignment, float sizeOffset,
		const std::string& bgImagePath, const SDL_Color& colorActive, const SDL_Color& colorInactive, const SDL_Color& colorDefault,
		const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor);
	int AddInputField(const std::string& sceneName,
		const std::string& defaultText, const std::string& fontPath, int charSize, int lineSpacing, TextAlignment alignment, float sizeOffset,
		const std::string& bgImagePath,
		const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor);


	//void AddText(text, const std::string& fontPath, const glm::vec2& pos, const glm::vec2& size, AnchorPosition anchor);
	//void AddSlider(...);

	UIElement* GetUIElement(int id) const;

	void Update();
	void Render();

	void ChangeScene(const std::string& sceneName) { m_ActiveScene = sceneName; }

private:
	struct UIElementPair
	{
		std::string sceneName;
		UIElement* pUIElement;
		int id;
	};

	std::vector<UIElementPair> m_pUIElements;

	std::string m_ActiveScene;
};