#include "PeakAEnginePCH.h"
#include "CameraComponent.h"

#include "Managers.h"

CameraComponent::CameraComponent()
	: Component{}
{
	RENDERER->SetCamera(this);
}
