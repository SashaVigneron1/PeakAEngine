#include "pch.h"
#include "TestComponent.h"

TestComponent::TestComponent() 
	: Component()
{

}

void TestComponent::Update()
{
	Logger::LogInfo("Yes");
}
