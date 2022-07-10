#pragma once

#include "PeakAEngine/Scene.h"

class TestScene final : public Scene
{
public:
	TestScene();
	virtual ~TestScene() override;

	TestScene(const TestScene& other) = delete;
	TestScene(TestScene&& other) noexcept = delete;
	TestScene& operator=(const TestScene& other) = delete;
	TestScene& operator=(TestScene&& other) noexcept = delete;

	virtual void Initialize() override;

protected:


private:
};

