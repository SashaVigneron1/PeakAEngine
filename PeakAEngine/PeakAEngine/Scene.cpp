#include "PeakAEnginePCH.h"
#include "Scene.h"

#include "PhysicsHandler.h"
#include "GameObject.h"

#include "imgui.h"

unsigned int Scene::m_IdCounter = 0;

Scene::Scene()
	: m_pPhysicsHandler(std::make_unique<PhysicsHandler>())
{}

Scene::~Scene() = default;

const std::string& Scene::GetName() const
{
	return m_Name;
}

void Scene::SetName(const std::string& name)
{
	m_Name = name;
}

GameObject* Scene::AddChild(const std::string& name)
{
	const auto object = std::shared_ptr<GameObject>(new GameObject(name, nullptr, this)); // Cant use make_shared because of private constructor
	const auto pObject = object.get();

	m_ObjectsToAdd.push_back(object);

	return pObject;
}

std::vector<GameObject*> Scene::GetObjects() const
{
	std::vector<GameObject*> vecRaw;

	vecRaw.reserve(m_Objects.size());
	std::transform(m_Objects.cbegin(), m_Objects.cend(), std::back_inserter(vecRaw),
		[](auto& ptr) { return ptr.get(); });

	return vecRaw;
}

void Scene::RootInitialize()
{
	for (const auto& object : m_Objects)
	{
		if (object->IsEnabled())
			object->Initialize();
	}

	Initialize();
}

void Scene::DrawImGui()
{
	if (m_Settings.enableGUI)
	{
		std::string title{ "Scene: " + m_Name };
		ImGui::Begin(title.c_str());
		

		for (const auto& object : m_Objects)
		{
			if (object->IsEnabled())
				object->DrawImGui();
		}

		ImGui::End();
	}

	
}

void Scene::Update() const
{
	for (const auto& object : m_Objects)
	{
		if (object->IsEnabled())
			object->Update();
	}
}

void Scene::FixedUpdate() const
{
	// Fixed Update on objects
	for (const auto& object : m_Objects)
	{
		if (object->IsEnabled())
			object->FixedUpdate();
	}

	// Update physics
	m_pPhysicsHandler->UpdatePhysics();
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		if (object->IsEnabled())
			object->Render();
	}
}

void Scene::RenderGizmos() const
{
	for (const auto& object : m_Objects)
	{
		if (object->IsEnabled())
			object->RenderGizmos();
	}
}


void Scene::ChangeSceneGraph()
{
	// Add Objects
	for (const auto& object : m_ObjectsToAdd)
		m_Objects.push_back(object);

	for (const auto& object : m_ObjectsToAdd)
		object->Initialize();

	m_ObjectsToAdd.clear();

	// Destroy marked root objects
	for (const auto& object : m_Objects)
	{
		if (object->IsMarkedForDestroy())
			object->OnDestroy();
	}

	const auto pos = std::remove_if(m_Objects.begin(), m_Objects.end(),
		[](const auto& o) { return o->IsMarkedForDestroy(); });

	m_Objects.erase(pos, m_Objects.end());

	// Call on remaining objects
	for (const auto& object : m_Objects)
	{
		object->ChangeSceneGraph();
	}
}

