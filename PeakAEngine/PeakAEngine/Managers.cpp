#include "PeakAEnginePCH.h"
#include "Manager.h"
#include "Managers.h"


std::map<const char*, std::shared_ptr<Manager>> Managers::m_managersByType;