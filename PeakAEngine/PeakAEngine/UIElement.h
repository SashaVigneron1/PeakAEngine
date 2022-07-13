#pragma once

enum class AnchorPosition {
	LeftTop,
	LeftCenter,
	LeftBottom,
	MiddleTop,
	MiddleCenter,
	MiddleBottom,
	RightTop,
	RightCenter,
	RightBottom
};

class UIElement
{
public:
	UIElement(const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor);
	virtual ~UIElement() = default;

	UIElement(const UIElement& other) = delete;
	UIElement(UIElement&& other) = delete;
	UIElement& operator=(const UIElement& other) = delete;
	UIElement& operator=(UIElement&& other) = delete;

	virtual void OnBeginHover() = 0;
	virtual void OnEndHover() = 0;
	virtual void OnClick() = 0;

	virtual void Render() = 0;

	void SetActive(bool value) { m_IsActive = value; }
	bool IsActive() const { return m_IsActive; }

	bool IsMouseOverlapping() const;
	bool IsHovered() const { return m_IsHovered; }
	void SetHovered(bool value) { m_IsHovered = value; }
protected:

	bool m_IsActive;
	bool m_IsHovered;

	glm::vec2 m_Position;
	glm::vec2 m_Size;
	glm::vec2 m_Pivot;
	AnchorPosition m_Anchor;
};

