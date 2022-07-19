#pragma once
#include "UIElement.h"
#include "UIManager.h"

class Texture2D;
class UI_Text;
class UI_Image;

class UI_InputField final : public UIElement
{
public:
	UI_InputField(const std::string& defaultText, const std::string& fontPath, int charSize, int lineSpacing, TextAlignment alignment, float sizeOffset,
		const std::string& bgImagePath, 
		const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor);
	UI_InputField(const std::string& defaultText, const std::string& fontPath, int charSize, int lineSpacing, TextAlignment alignment, float sizeOffset,
		const std::string& bgImagePath, const SDL_Color& colorActive, const SDL_Color& colorInactive, const SDL_Color& colorDefault,
		const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor);
	virtual ~UI_InputField() = default;

	UI_InputField(const UI_InputField& other) = delete;
	UI_InputField(UI_InputField&& other) = delete;
	UI_InputField& operator=(const UI_InputField& other) = delete;
	UI_InputField& operator=(UI_InputField&& other) = delete;

	virtual void OnBeginHover();
	virtual void OnEndHover();
	virtual void OnClick();

	virtual void Render();
	virtual void Update();

	std::string GetText() const { return m_Text; }
	void SetHideState(bool value) { m_ShouldHide = value; }

private:
	std::shared_ptr<UI_Image> m_pBackgroundImage;
	std::shared_ptr<UI_Text> m_pText;
	std::string m_DefaultText;
	std::string m_Text;
	bool m_ShouldHide;
	bool m_IsSelected;

	SDL_Color m_ColorActive;
	SDL_Color m_ColorInactive;
	SDL_Color m_ColorDefault;

	int m_CharSize;
};

