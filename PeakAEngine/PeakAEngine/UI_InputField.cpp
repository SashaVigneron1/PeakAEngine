#include "PeakAEnginePCH.h"
#include "UI_InputField.h"

#include "InputManager.h"
#include "ResourceManager.h"
#include "UI_Image.h"
#include "UI_Text.h"

UI_InputField::UI_InputField(const std::string& defaultText, const std::string& fontPath, int charSize, int lineSpacing, TextAlignment alignment, float sizeOffset, const std::string& bgImagePath, const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor)
	: UI_InputField(
		defaultText, fontPath, charSize, lineSpacing, alignment, sizeOffset,
		bgImagePath, 
		SDL_Color{255,255,255,255}, SDL_Color{200,200,200,255}, SDL_Color{150,150,150,255}, 
		pos, size, pivot, anchor)
{
}

UI_InputField::UI_InputField(const std::string& defaultText, const std::string& fontPath, int charSize, int lineSpacing, TextAlignment alignment, float sizeOffset, const std::string& bgImagePath, const SDL_Color& colorActive, const SDL_Color& colorInactive, const SDL_Color& colorDefault, const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor)
	: UIElement(pos, size, pivot, anchor)
	, m_pBackgroundImage{ std::make_shared<UI_Image>(bgImagePath, pos, size, pivot, anchor) }
	, m_pText{ std::make_shared<UI_Text>(defaultText, fontPath, lineSpacing, alignment, glm::vec2{ pos.x + sizeOffset, pos.y }, glm::vec2{ size.x - sizeOffset, size.y }, pivot, anchor) }
	, m_DefaultText{ defaultText }
	, m_Text{ "" }
	, m_IsSelected{ false }
	, m_ColorActive{ colorActive }
	, m_ColorInactive{ colorInactive }
	, m_ColorDefault{ colorDefault }
	, m_CharSize{ charSize }
{
	m_pText->SetColor(m_ColorDefault);
}

void UI_InputField::OnBeginHover()
{
}

void UI_InputField::OnEndHover()
{
	m_IsSelected = false;
	m_pText->SetColor(m_ColorInactive);
	if (m_pText->GetText().empty())
		m_pText->ChangeText(m_DefaultText);
}

void UI_InputField::OnClick()
{
	m_IsSelected = true;

	if (m_Text.empty())
		m_pText->ChangeText("");

	m_pText->SetColor(m_ColorActive);
}

void UI_InputField::Render()
{
	m_pBackgroundImage->Render();
	m_pText->Render();
}

void UI_InputField::Update()
{
	if (m_IsSelected) 
	{
		if (INPUTMANAGER.IsPressed((char)SDLK_ESCAPE) || INPUTMANAGER.IsPressed(char(SDLK_RETURN)))
		{
			m_IsSelected = false;
			m_pText->SetColor(m_ColorInactive);
			if (m_pText->GetText().empty())
				m_pText->ChangeText(m_DefaultText);

			return;
		}

		std::vector<char> charsToAdd = INPUTMANAGER.GetKeysPressedThisFrame();
		if (charsToAdd.size())
		{
			for (auto character : charsToAdd)
			{
				// Keys To Ignore
				// ToDoo: Fix: this is not optimal + seems to be giving weird results on certain keys
				if (character == SDL_SCANCODE_CAPSLOCK || character == SDL_SCANCODE_LSHIFT)
					continue;


				if (character != SDLK_BACKSPACE)
					m_Text += character;
				else
					m_Text = m_Text.substr(0, m_Text.size() - 1);
			}

			m_pText->ChangeText(m_Text);
		}
	}
	
}
