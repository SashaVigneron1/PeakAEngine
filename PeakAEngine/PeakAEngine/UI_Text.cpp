#include "PeakAEnginePCH.h"
#include "UI_Text.h"

#include <SDL_ttf.h>
#include "Font.h"
#include "RenderManager.h"
#include "ResourceManager.h"

#include "Texture2D.h"

UI_Text::UI_Text(const std::string& text, const std::string& fontPath, int lineSpacing, TextAlignment alignment
	, const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor)
	: UIElement{ pos, size, pivot, anchor }
	, m_pFont{ RESOURCEMANAGER.LoadFont(fontPath, unsigned int(100))}
	, m_pTexture{ nullptr }
	, m_Color{ 255,255,255,255 }
	, m_LineSpacing{ lineSpacing }
	, m_Alignment{ alignment }
{
	ChangeText(text);
}

void UI_Text::OnBeginHover()
{
}

void UI_Text::OnEndHover()
{
}

void UI_Text::OnClick()
{
}

void UI_Text::Render()
{
	if (m_Text.empty())
		return;

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

void UI_Text::ChangeText(const std::string& text)
{
	m_Text = text;
	UpdateTexture();
}

void UI_Text::SetColor(const SDL_Color& color)
{
	m_Color = color;
	UpdateTexture();
}

void UI_Text::UpdateTexture()
{
	// Split text in lines
	std::vector<std::string> lines;

	size_t last = 0;
	size_t next;
	while ((next = m_Text.find('\n', last)) != std::string::npos)
	{
		lines.push_back(m_Text.substr(last, next - last));
		last = next + 1;
	}
	lines.push_back(m_Text.substr(last));

	// Get final surface dimensions
	int width = 0;
	int height = 0;

	for (auto& string : lines)
	{
		int linew, lineh;
		TTF_SizeText(m_pFont->GetFont(), string.c_str(), &linew, &lineh);

		width = std::max(width, linew);
		height += lineh;
	}

	height += (static_cast<int>(lines.size()) - 1) * m_LineSpacing;

	// Create final surface
	SDL_Surface* finalSurf = SDL_CreateRGBSurface(0, width, height, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	// Render lines
	for (int i = 0; i < (int)lines.size(); i++)
	{
		SDL_Surface* lineSurf = TTF_RenderText_Blended(m_pFont->GetFont(), lines[i].c_str(), m_Color);

		if (lineSurf != nullptr)
		{
			SDL_Rect dstRect{};
			dstRect.y = i * (lineSurf->h + m_LineSpacing);
			dstRect.w = lineSurf->w;
			dstRect.h = lineSurf->h;

			switch (m_Alignment)
			{
			case TextAlignment::Left:
				dstRect.x = 0;
				break;
			case TextAlignment::Center:
				dstRect.x = (width - lineSurf->w) / 2;
				break;
			case TextAlignment::Right:
				dstRect.x = width - lineSurf->w;
				break;
			}

			SDL_BlitSurface(lineSurf, nullptr, finalSurf, &dstRect);

			// Free Surface
			SDL_FreeSurface(lineSurf);
		}
	}

	// Send to texture
	m_pTexture = std::make_unique<Texture2D>(finalSurf, width, height);

	// Free surface
	SDL_FreeSurface(finalSurf);
}
