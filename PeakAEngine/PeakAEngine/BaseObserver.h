#pragma once

enum class Event;
class Component;

class BaseObserver
{
public:
	BaseObserver() = default;
	virtual ~BaseObserver() = default;

	BaseObserver(const BaseObserver& other) = delete;
	BaseObserver(BaseObserver&& other) noexcept = delete;
	BaseObserver& operator=(const BaseObserver& other) = delete;
	BaseObserver& operator=(BaseObserver&& other) noexcept = delete;

	virtual void Notify(Component* pComponent, Event event) = 0;
private:

};

