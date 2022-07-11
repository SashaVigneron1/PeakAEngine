#pragma once
#include "Component.h"

class Texture2D;

//*************************
// Sprites use column-based animations.
// Seperate rows define seperate animations (for example: different direction)
// Note!
// As for sideways animations, LEFT is the default
//*************************

enum class Direction
{
	FacingCamera = 0,
	FacingLeft = 1,
	FacingRight = 2,
	FacingAwayFromCamera = 3
};
struct SpriteRow
{
	SpriteRow(Direction direction, int rowId, bool inverse = false)
		: direction{ direction }
		, rowId{ rowId }
		, inverse{ inverse }
	{
	}
	int rowId = 0;
	Direction direction = Direction::FacingCamera;
	bool inverse = false;
};

class Sprite final
{
public:
	Sprite(const std::string& fileName, const std::vector<SpriteRow>& rows, int nrCols, float frameSec, int layerId = 0);
	Sprite(const std::string& fileName, const std::vector<SpriteRow>& rows, int nrCols, float frameSec, const glm::vec2& scale, int layerId = 0);
	Sprite(const std::string& fileName, const std::vector<SpriteRow>& rows, int nrCols, float frameSec, const glm::vec2& scale, const glm::vec2& pivot, int layerId = 0);
	~Sprite();
	Sprite(const Sprite& other) = delete;
	Sprite(Sprite&& other) = delete;
	Sprite& operator=(const Sprite& other) = delete;
	Sprite& operator=(Sprite&& other) = delete;

	void Update();
	void Render() const;

	void SetGameObject(GameObject* pGameObject) { m_pGameObject = pGameObject; }

	void SetDirection(Direction direction);
	void ResetTimer() { m_ActFrame = 0; m_AccSec = 0.0f; }

	void SetTexture(const std::string& fileName);
	void SetTexture(std::shared_ptr<Texture2D> newTexture) { m_pTexture = newTexture; }

private:
	GameObject* m_pGameObject;

	std::shared_ptr<Texture2D> m_pTexture;
	std::vector<SpriteRow> m_Rows;

	int m_CurrentRow = 0;
	bool m_IsInverse = false;

	int m_NrRows{ 0 };
	int m_NrCols{ 0 };
	float m_AccSec{ 0.f };
	float m_FrameSec{ 0.f };
	int m_ActFrame{ 0 };

	glm::vec2 m_Scale{};
	glm::vec2 m_Pivot{ 0.5f, 0.5f };

	int m_LayerId{ -1 };
};



