#pragma once
#include "Component.h"

#include <unordered_map>
#include "Sprite.h"


class SpriteRenderer final : public Component
{

public:
	SpriteRenderer() = default;
	virtual ~SpriteRenderer() override = default;
	SpriteRenderer(const SpriteRenderer& other) = delete;
	SpriteRenderer(SpriteRenderer&& other) noexcept = delete;
	SpriteRenderer& operator=(const SpriteRenderer& other) = delete;
	SpriteRenderer& operator=(SpriteRenderer&& other) noexcept = delete;

	void Update() override { if (m_pActiveSprite) m_pActiveSprite->Update(); }
	void FixedUpdate() override {}
	void Render() const override { if (m_pActiveSprite) m_pActiveSprite->Render(); }

	void SetDirection(Direction direction) { if (m_pActiveSprite) m_pActiveSprite->SetDirection(direction); };

	void AddSprite(const std::string& name, std::shared_ptr<Sprite> pSprite);
	void SetActiveSprite(const std::string& name) { m_pActiveSprite = m_Sprites[name].get(); }

	void SetPixelsPerUnit(int value) { for (auto sprite : m_Sprites) sprite.second->SetPixelsPerUnit(value); }
	int GetPixelsPerUnit();

	glm::vec2 GetSpriteDimensions() const;

private:
	Sprite* m_pActiveSprite{nullptr};
	std::unordered_map<std::string, std::shared_ptr<Sprite>> m_Sprites;
};

