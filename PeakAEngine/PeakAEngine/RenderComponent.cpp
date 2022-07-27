#include "PeakAEnginePCH.h"
#include "RenderComponent.h"

#include "GameObject.h"
#include "Transform.h"

#include "Managers.h"

void RenderComponent::Render() const
{
	auto transform = GetGameObject()->GetTransform();
	if (m_Texture && transform)
	{
		RENDERER->RenderTexture_Units(m_Texture, transform->GetWorldPosition(), transform->GetWorldScale(), transform->GetWorldRotation(),
			m_Pivot, m_SourceRect, m_RenderLayer);
	}
}

void RenderComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_Texture = texture;

	if (m_SourceRect.h == 0 && m_SourceRect.w == 0 && m_Texture)
		m_SourceRect = SDL_FRect{ 0.f,0.f,float(texture->GetWidth()),float(texture->GetHeight()) };
}

void RenderComponent::SetSourceRect(const SDL_FRect& srcRect)
{
	m_SourceRect = srcRect;
}

void RenderComponent::ResetSourceRect()
{
	if (m_Texture)
		m_SourceRect = { 0,0,float(m_Texture->GetWidth()), float(m_Texture->GetHeight()) };
}

glm::vec2* RenderComponent::GetWorldRect(glm::vec2* vertices) const
{
	Transform* pTransform = GetGameObject()->GetTransform();

	const auto& pos = pTransform->GetWorldPosition();
	const auto& scale = pTransform->GetWorldScale();
	auto rot = pTransform->GetWorldRotation();

	float vertexLeft{ m_Pivot.x - 1.f };
	float vertexBottom{ m_Pivot.y - 1.f };
	float vertexRight{ m_Pivot.x };
	float vertexTop{ m_Pivot.y };

	vertexLeft *= m_SourceRect.w * scale.x;
	vertexRight *= m_SourceRect.w * scale.x;
	vertexTop *= m_SourceRect.h * scale.y;
	vertexBottom *= m_SourceRect.h * scale.y;

	constexpr float inverse180{ 1.f / 180.f * float(M_PI) };

	float cosAngle = cos(rot * inverse180);
	float sinAngle = sin(rot * inverse180);

	vertices[0] = { vertexLeft * cosAngle - vertexTop * sinAngle, vertexTop * cosAngle + vertexLeft * sinAngle };
	vertices[1] = { vertexRight * cosAngle - vertexTop * sinAngle, vertexTop * cosAngle + vertexRight * sinAngle };
	vertices[2] = { vertexRight * cosAngle - vertexBottom * sinAngle, vertexBottom * cosAngle + vertexRight * sinAngle };
	vertices[3] = { vertexLeft * cosAngle - vertexBottom * sinAngle, vertexBottom * cosAngle + vertexLeft * sinAngle };

	vertices[0] += pos;
	vertices[1] += pos;
	vertices[2] += pos;
	vertices[3] += pos;

	return vertices;
}
