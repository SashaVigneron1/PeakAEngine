#include "PeakAEnginePCH.h"
#include "SpriteRenderer.h"

void SpriteRenderer::AddSprite(const std::string& name, Sprite* pSprite)
{
	pSprite->SetGameObject(m_pGameObject);
	m_Sprites[name] = pSprite; SetActiveSprite(name);
}
