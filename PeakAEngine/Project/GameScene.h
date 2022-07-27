#pragma once



#include "PeakAEngine/Scene.h"

class GameScene final : public Scene
{
public:
	GameScene();
	virtual ~GameScene() override;

	GameScene(const GameScene& other) = delete;
	GameScene(GameScene&& other) noexcept = delete;
	GameScene& operator=(const GameScene& other) = delete;
	GameScene& operator=(GameScene&& other) noexcept = delete;

	virtual void Initialize() override;

protected:


private:
};

