#pragma once
#include "UIElement.h"

#include "UIManager.h"

class Font;
class Texture2D;

class UI_Text final : public UIElement
{
public:
	UI_Text(const std::string& text, const std::string& fontPath, int lineSpacing, TextAlignment alignment
		, const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor);
	virtual ~UI_Text() = default;

	UI_Text(const UI_Text& other) = delete;
	UI_Text(UI_Text&& other) = delete;
	UI_Text& operator=(const UI_Text& other) = delete;
	UI_Text& operator=(UI_Text&& other) = delete;

	virtual void OnBeginHover();
	virtual void OnEndHover();
	virtual void OnClick();

	virtual void Render();
	virtual void Update() {}

	void ChangeText(const std::string& text);
	void SetColor(const SDL_Color& color);

	std::string GetText() const { return m_Text; }

private:
	void UpdateTexture();

	std::shared_ptr<Font> m_pFont;
	std::shared_ptr<Texture2D> m_pTexture;

	std::string m_Text;
	SDL_Color m_Color;

	int m_LineSpacing;
	TextAlignment m_Alignment;
};