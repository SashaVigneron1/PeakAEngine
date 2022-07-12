#include "PeakAEnginePCH.h"
#include "CameraComponent.h"

#include "RenderManager.h"

CameraComponent::CameraComponent()
	: Component{}
{
	RENDERER.SetCamera(this);
}
