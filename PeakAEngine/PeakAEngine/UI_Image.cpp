#include "PeakAEnginePCH.h"
#include "UI_Image.h"

#include "ResourceManager.h"
#include "RenderManager.h"

UI_Image::UI_Image(const std::string& imagePath, const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor)
	: UIElement{pos, size, pivot, anchor}
	, m_pTexture{ ResourceManager::GetInstance().LoadTexture(imagePath) }
{
}

void UI_Image::OnBeginHover()
{
}

void UI_Image::OnEndHover()
{
}

void UI_Image::OnClick()
{
}

void UI_Image::Render()
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


	RENDERER.RenderUITexture(m_pTexture, actualPosition, m_Size, 0);
}
