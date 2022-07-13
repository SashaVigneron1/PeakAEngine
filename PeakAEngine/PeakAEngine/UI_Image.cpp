#include "PeakAEnginePCH.h"
#include "UI_Image.h"

#include "RenderManager.h"

UI_Image::UI_Image(const std::string& /*imagePath*/, const glm::vec2& pos, const glm::vec2& size, const glm::vec2& pivot, AnchorPosition anchor)
	: UIElement{pos, size, pivot, anchor}
{
}

void UI_Image::OnBeginHover()
{
	Logger::LogInfo("Beginning To Hover");
}

void UI_Image::OnEndHover()
{
	Logger::LogInfo("Ending To Hover");
}

void UI_Image::OnClick()
{
	Logger::LogInfo("Beginning To CLICK");
}

void UI_Image::Render()
{
	//ToDoo: Render Image In Correct Spot
	//RENDERER.RenderDebugRect(SDL_FRect{100,100,100,100}, true, { 100,100,100,255 });
}
