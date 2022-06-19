#pragma once

enum class Event;
class Component;
class BaseObserver;


class Subject abstract
{
public:
	Subject() = default;
	virtual ~Subject();

	Subject(const Subject& other) = delete;
	Subject(Subject&& other) noexcept = delete;
	Subject& operator=(const Subject& other) = delete;
	Subject& operator=(Subject&& other) noexcept = delete;

	void AddObserver(BaseObserver* pObserver) { m_pObservers.push_back(pObserver); }
	void RemoveObserver(BaseObserver* pObserver);

	void Notify(Component* pComponent, Event event);
	void RemoveObservers();

private:
	std::vector<BaseObserver*> m_pObservers;

};

