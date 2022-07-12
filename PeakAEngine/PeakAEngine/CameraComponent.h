#pragma once

#include "Component.h"

class CameraComponent final : public Component
{
public:
	CameraComponent();
	virtual ~CameraComponent() override = default;
	CameraComponent(const CameraComponent& other) = delete;
	CameraComponent(CameraComponent&& other) noexcept = delete;
	CameraComponent& operator=(const CameraComponent& other) = delete;
	CameraComponent& operator=(CameraComponent&& other) noexcept = delete;

private:

};

