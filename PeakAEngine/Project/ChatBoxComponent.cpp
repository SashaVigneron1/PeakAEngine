#include "pch.h"
#include "ChatBoxComponent.h"

#include "PeakAEngine/InputManager.h"
#include "PeakAEngine/NetworkManager.h"

ChatBoxComponent::ChatBoxComponent()
	: Component{}
{
}

void ChatBoxComponent::Update()
{
	if (INPUTMANAGER.IsPressed('z'))
		NETWORKMANAGER.SendTextMessage("Hello there!");
}

void ChatBoxComponent::DrawImGui()
{
}

void ChatBoxComponent::RenderGizmos() const
{
}

void ChatBoxComponent::OnBeginHover()
{
}

void ChatBoxComponent::OnEndHover()
{
}

void ChatBoxComponent::OnClick()
{
}
