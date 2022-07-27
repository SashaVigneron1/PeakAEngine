#pragma once

#include "PeakAEngine/Scene.h"

class LoginScene final : public Scene
{
public:
	LoginScene();
	virtual ~LoginScene() override;

	LoginScene(const LoginScene& other) = delete;
	LoginScene(LoginScene&& other) noexcept = delete;
	LoginScene& operator=(const LoginScene& other) = delete;
	LoginScene& operator=(LoginScene&& other) noexcept = delete;

	virtual void Initialize() override;
	virtual void Reload() override;
protected:


private:
};

