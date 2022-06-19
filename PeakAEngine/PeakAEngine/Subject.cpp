#include "PeakAEnginePCH.h"
#include "Subject.h"
#include "BaseObserver.h"


Subject::~Subject()
{
	RemoveObservers();
}

void Subject::RemoveObserver(BaseObserver* pObserver)
{
	for (size_t i = 0; i < m_pObservers.size(); i++)
	{
		if (m_pObservers[i] == pObserver)
		{
			m_pObservers[i] = m_pObservers.back();
			m_pObservers.pop_back();
		}
	}
}

void Subject::Notify(Component* pComponent, Event event)
{
	for(auto observer : m_pObservers)
	{
		observer->Notify(pComponent, event);
	}
}

void Subject::RemoveObservers()
{
	for(int i{}; i < (int)m_pObservers.size(); ++i)
	{
		m_pObservers.pop_back();
	}
}
