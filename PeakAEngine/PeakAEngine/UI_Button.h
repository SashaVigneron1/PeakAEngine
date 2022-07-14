#pragma once
#include "UIElement.h"

#include <functional>

#include "UIManager.h"
class Texture2D;
class UI_Text;

class UI_Button : public UIElement
{
public:
	UI_Button(const std::string& imageDefaultPath, const std::string& imageOnHoverPath, const std::string& imageOnClickPath,
		const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor);
	virtual ~UI_Button();

	UI_Button(const UI_Button& other) = delete;
	UI_Button(UI_Button&& other) = delete;
	UI_Button& operator=(const UI_Button& other) = delete;
	UI_Button& operator=(UI_Button&& other) = delete;

	virtual void OnBeginHover();
	virtual void OnEndHover();
	virtual void OnClick();

	virtual void Render();

	void SetFunctionToExecute(std::function<void()> function) { m_FunctionToExecute = function; }
	void AddText(const std::string& text, const std::string& fontPath, int lineSpacing, TextAlignment alignment, float sizeOffset);
	void ChangeText(const std::string& text);
	void SetTextColor(const SDL_Color& color);

private:
	bool m_IsPressed;

	UI_Text* m_pText;

	std::function<void()> m_FunctionToExecute;

	std::shared_ptr<Texture2D> m_pActiveTexture;

	std::shared_ptr<Texture2D> m_pTextureDefault;
	std::shared_ptr<Texture2D> m_pTextureOnHover;
	std::shared_ptr<Texture2D> m_pTextureOnClick;
};
