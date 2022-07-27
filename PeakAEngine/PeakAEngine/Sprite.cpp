#include "PeakAEnginePCH.h"
#include "Sprite.h"

#include "PeakAEnginePCH.h"
#include "Sprite.h"

#include "Managers.h"
#include "GameObject.h"
#include "Transform.h"

#include "Texture2D.h"
#include "Time.h"

Sprite::Sprite(const std::string& fileName, const std::vector<SpriteRow>& rows, int nrCols, float frameSec, int layerId)
	: Sprite{ fileName,rows, nrCols, frameSec, {1,1}, {0.5f, 0.5f}, layerId}
{
}
Sprite::Sprite(const std::string& fileName, const std::vector<SpriteRow>& rows, int nrCols, float frameSec, const glm::vec2& scale, int layerId)
	: Sprite{ fileName,rows, nrCols, frameSec, scale, {0.5f, 0.5f}, layerId }
{
}
Sprite::Sprite(const std::string& fileName, const std::vector<SpriteRow>& rows, int nrCols, float frameSec, const glm::vec2& scale, const glm::vec2& pivot, int layerId)
	: m_pTexture{ RESOURCEMANAGER->LoadTexture(fileName) }
	, m_Rows{ rows }
	, m_NrCols{ nrCols }
	, m_FrameSec{ frameSec }
	, m_AccSec{ 0.f }
	, m_ActFrame{ 0 }
	, m_NrRows{ 0 }
	, m_CurrentRow{ 0 }
	, m_LayerId{ layerId }
	, m_Pivot{ pivot }
	, m_Scale{ scale }
	, m_pGameObject{ nullptr }
{
	// Add Rows
	std::vector<int> indices;
	for (auto row : rows)
	{
		bool foundIndex{ false };
		for (int i : indices)
		{
			if (row.rowId == i) foundIndex = true;
		}

		if (!foundIndex)
		{
			++m_NrRows;
			indices.push_back(row.rowId);
		}
	}

}

Sprite::~Sprite()
{
}

void Sprite::Update()
{
	m_AccSec += Time::DeltaTime();
	if (m_AccSec >= m_FrameSec)
	{
		++m_ActFrame %= m_NrCols;
		m_AccSec = 0;
	}
}
void Sprite::Render() const
{
	if (m_pGameObject)
	{
		SDL_FRect srcRect;
		srcRect.w = m_pTexture->GetWidth() / (float)m_NrCols;
		srcRect.h = m_pTexture->GetHeight() / (float)m_NrRows;
		srcRect.x = m_ActFrame * srcRect.w;
		srcRect.y = m_CurrentRow * srcRect.h;

		glm::vec2 pos{ m_pGameObject->GetTransform()->GetWorldPosition().x, m_pGameObject->GetTransform()->GetWorldPosition().y };
		glm::vec2 scale{ m_pGameObject->GetTransform()->GetWorldScale().x * m_Scale.x, m_pGameObject->GetTransform()->GetWorldScale().y * m_Scale.y };
		float rotation{ m_pGameObject->GetTransform()->GetWorldRotation() };

		RENDERER->RenderTexture_Units(m_pTexture, pos, scale, rotation, m_Pivot, srcRect, m_LayerId);
	}
}

void Sprite::SetTexture(const std::string& fileName)
{
	m_pTexture = RESOURCEMANAGER->LoadTexture(fileName);
}
void Sprite::SetPixelsPerUnit(int value)
{
	m_pTexture.get()->SetPixelsPerUnit(value);
}
int Sprite::GetPixelsPerUnit() const
{
	return m_pTexture.get()->GetPixelsPerUnit();
}
glm::vec2 Sprite::GetSpriteDimension() const
{

	return { m_pTexture.get()->GetWidth() / m_NrCols, m_pTexture.get()->GetHeight() / (m_Rows.size()-1) };

}
void Sprite::SetDirection(Direction direction)
{
	for (auto spriteRow : m_Rows)
	{
		if (spriteRow.direction == direction)
		{
			if (spriteRow.inverse) m_IsInverse = true;
			else m_IsInverse = false;

			m_CurrentRow = spriteRow.rowId;
			return;
		}
	}
}