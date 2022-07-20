#pragma once
#include "PeakAEngine/Scene.h"

class RoomSelectorScene final : public Scene
{
public:
	RoomSelectorScene();
	virtual ~RoomSelectorScene() override;

	RoomSelectorScene(const RoomSelectorScene& other) = delete;
	RoomSelectorScene(RoomSelectorScene&& other) noexcept = delete;
	RoomSelectorScene& operator=(const RoomSelectorScene& other) = delete;
	RoomSelectorScene& operator=(RoomSelectorScene&& other) noexcept = delete;

	virtual void Initialize() override;

protected:


private:
};

