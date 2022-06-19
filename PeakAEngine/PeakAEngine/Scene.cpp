#include "PeakAEnginePCH.h"
#include "Scene.h"

#include "PhysicsHandler.h"
#include "GameObject.h"

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name)
	: m_Name(name)
	, m_pPhysicsHandler(std::make_unique<PhysicsHandler>())
{}

Scene::~Scene() = default;

const std::string& Scene::GetName() const
{
	return m_Name;
}

GameObject* Scene::CreateChildObject(const std::string& name)
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

void Scene::Initialize() const
{
	for (const auto& object : m_Objects)
	{
		if (object->IsEnabled())
			object->Initialize();
	}
}

void Scene::DrawImGui()
{
#ifdef _DEBUG
	DisplaySceneGraph();
#endif

	for (const auto& object : m_Objects)
	{
		if (object->IsEnabled())
			object->DrawImGui();
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

void Scene::DisplaySceneGraph()
{
	// HIERARCHY
	//----------
	//ImGui::Begin(ICON_FA_SHAPES " Hierarchy");
	//for (const auto& rootObject : m_Objects)
	//{
	//	DisplayObjectInSceneGraph(rootObject.get());
	//}
	//ImGui::End();

	//// PROPERTIES
	////-----------
	//ImGui::Begin(ICON_FA_SLIDERS " Properties");
	//if (m_pSelectedObjectInHierarchy != nullptr)
	//{
	//	m_pSelectedObjectInHierarchy->DrawProperties();
	//}
	//ImGui::End();
}

void Scene::DisplayObjectInSceneGraph(GameObject* /*pObject*/)
{
	//ImGui::PushID(pObject);

	//const int withArrow = pObject->GetChildren().empty() ? ImGuiTreeNodeFlags_Leaf : 0;
	//const int selected = m_pSelectedObjectInHierarchy == pObject ? ImGuiTreeNodeFlags_Selected : 0;
	//const bool isOpen = ImGui::TreeNodeEx(pObject->GetName().c_str(), ImGuiTreeNodeFlags_OpenOnArrow | withArrow | selected);

	//if (ImGui::IsItemClicked())
	//	m_pSelectedObjectInHierarchy = pObject;

	//if (isOpen)
	//{
	//	// Display all children recursively
	//	for (const auto child : pObject->GetChildren())
	//	{
	//		DisplayObjectInSceneGraph(child);
	//	}

	//	ImGui::TreePop();
	//}

	//ImGui::PopID();
}