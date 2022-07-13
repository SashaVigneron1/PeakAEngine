#pragma once
#include "UIElement.h"

class UI_Image final : public UIElement
{
public:
	UI_Image(const std::string& imagePath, const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor);
	virtual ~UI_Image() = default;

	UI_Image(const UI_Image& other) = delete;
	UI_Image(UI_Image&& other) = delete;
	UI_Image& operator=(const UI_Image& other) = delete;
	UI_Image& operator=(UI_Image&& other) = delete;

	virtual void OnBeginHover();
	virtual void OnEndHover();
	virtual void OnClick();

	virtual void Render();

private:

};

