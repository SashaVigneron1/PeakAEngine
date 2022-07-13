#include "PeakAEnginePCH.h"
#include "UIElement.h"

#include "RenderManager.h"
#include "InputManager.h"

#include "Utils.h"

UIElement::UIElement(const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor)
	: m_IsActive{ true }
	, m_IsHovered{ false }
	, m_Position{ pos }
	, m_Size{ size }
	, m_Pivot{ pivot }
	, m_Anchor{ anchor }
{
	// Pivot should be between (0,0) LeftBottom && (1,1) RightTop
	Clamp(m_Pivot.x, 0.0f, 1.0f);
	Clamp(m_Pivot.y, 0.0f, 1.0f);
}

bool UIElement::IsMouseOverlapping() const
{
	const auto& windowSize = RENDERER.GetWindowSize();
	const auto& mousePos = INPUTMANAGER.GetMouseState().position;

	glm::vec2 actualPosition = m_Position;
	glm::vec2 actualSize = m_Size;


	switch (m_Anchor)
	{
		// LEFT
	case AnchorPosition::LeftTop:
		actualPosition.y = -actualPosition.y + windowSize.y;
		// Move Position According To Pivot & Size
		actualPosition.x += m_Pivot.x * m_Size.x;
		actualPosition.y -= m_Pivot.y * m_Size.y;
		break;
	case AnchorPosition::LeftCenter:
		actualPosition.y = actualPosition.y + windowSize.y / 2.f;
		// Move Position According To Pivot & Size
		actualPosition.x += m_Pivot.x * m_Size.x;
		actualPosition.y += m_Pivot.y * m_Size.y;
		break;
	case AnchorPosition::LeftBottom:
		// Move Position According To Pivot & Size
		actualPosition.x += m_Pivot.x * m_Size.x;
		actualPosition.y += m_Pivot.y * m_Size.y;
		break;

		// MIDDLE
	case AnchorPosition::MiddleTop:
		actualPosition = m_Position;
		actualPosition.x = actualPosition.x + windowSize.x / 2.f;
		actualPosition.y = -actualPosition.y + windowSize.y;
		// Move Position According To Pivot & Size
		actualPosition.x += m_Pivot.x * m_Size.x;
		actualPosition.y -= m_Pivot.y * m_Size.y;
		break;
	case AnchorPosition::MiddleCenter:
		actualPosition.x = actualPosition.x + windowSize.x / 2.f;
		actualPosition.y = actualPosition.y + windowSize.y / 2.f;
		// Move Position According To Pivot & Size
		actualPosition.x += m_Pivot.x * m_Size.x;
		actualPosition.y += m_Pivot.y * m_Size.y;
		break;
	case AnchorPosition::MiddleBottom:
		actualPosition.x = actualPosition.x + windowSize.x / 2.f;
		// Move Position According To Pivot & Size
		actualPosition.x += m_Pivot.x * m_Size.x;
		actualPosition.y += m_Pivot.y * m_Size.y;
		break;
	
		// RIGHT
	case AnchorPosition::RightTop:
		actualPosition.x = -actualPosition.x + windowSize.x;
		actualPosition.y = -actualPosition.y + windowSize.y;
		// Move Position According To Pivot & Size
		actualPosition.x -= m_Pivot.x * m_Size.x;
		actualPosition.y -= m_Pivot.y * m_Size.y;
		break;
	case AnchorPosition::RightCenter:
		actualPosition.x = -actualPosition.x + windowSize.x;
		actualPosition.y = actualPosition.y + windowSize.y / 2.f;
		// Move Position According To Pivot & Size
		actualPosition.x -= m_Pivot.x * m_Size.x;
		actualPosition.y += m_Pivot.y * m_Size.y;
		break;
	case AnchorPosition::RightBottom:
		actualPosition.x = -actualPosition.x + windowSize.x;
		// Move Position According To Pivot & Size
		actualPosition.x -= m_Pivot.x * m_Size.x;
		actualPosition.y += m_Pivot.y * m_Size.y;
		break;
	}

	// Check if mouse is inside
	return (mousePos.x > actualPosition.x
		&& mousePos.x < actualPosition.x + actualSize.x
		&& mousePos.y > actualPosition.y
		&& mousePos.y < actualPosition.y + actualSize.y
		);
}
