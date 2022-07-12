#include "PeakAEnginePCH.h"
#include "SpriteRenderer.h"

void SpriteRenderer::AddSprite(const std::string& name, Sprite* pSprite)
{
	pSprite->SetGameObject(m_pGameObject);
	m_Sprites[name] = pSprite; SetActiveSprite(name);
}

glm::vec2 SpriteRenderer::GetSpriteDimensions() const
{
	if (!m_pActiveSprite)
		return {};

	return m_pActiveSprite->GetSpriteDimension();
}

int SpriteRenderer::GetPixelsPerUnit() 
{
	if (m_Sprites.size() < 1)
		return 1;

	return m_pActiveSprite->GetPixelsPerUnit();
}