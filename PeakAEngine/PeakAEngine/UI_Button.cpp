#include "PeakAEnginePCH.h"
#include "UI_Button.h"

#include "RenderManager.h"
#include "ResourceManager.h"


UI_Button::UI_Button(const std::string& imageDefaultPath, const std::string& imageOnHoverPath, const std::string& imageOnClickPath, const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor)
	: UIElement{ pos, size, pivot, anchor }
	, m_IsPressed{ false }
	, m_pTextureDefault{ ResourceManager::GetInstance().LoadTexture(imageDefaultPath) }
	, m_pTextureOnHover{ ResourceManager::GetInstance().LoadTexture(imageOnHoverPath) }
	, m_pTextureOnClick{ ResourceManager::GetInstance().LoadTexture(imageOnClickPath) }
{
	m_pActiveTexture = m_pTextureDefault;
}

void UI_Button::OnBeginHover()
{
	if (!m_IsPressed) m_pActiveTexture = m_pTextureOnHover;
}

void UI_Button::OnEndHover()
{
	if (!m_IsPressed) m_pActiveTexture = m_pTextureDefault;
}

void UI_Button::OnClick()
{
	m_pActiveTexture = m_pTextureOnClick;

	m_IsPressed = true;

	// Start Timer For Texture
	TIME.AddTimer(std::make_shared<Timer>(1.0f, [=] 
		{
			m_IsPressed = false;

			if (m_IsHovered)
				m_pActiveTexture = m_pTextureOnHover;
			else
				m_pActiveTexture = m_pTextureDefault;
		}));
}

void UI_Button::Render()
{
	const auto& windowSize = RENDERER.GetWindowSize();

	glm::vec2 actualPosition = m_Position;

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


	RENDERER.RenderUITexture(m_pActiveTexture, actualPosition, m_Size, 0);
}
