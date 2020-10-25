#include "Component.h"

Component::Component() : enabled(true), gameObject(nullptr) {}

Component::~Component(){}

void Component::Update(){}

void Component::Enable() { enabled = true; }

void Component::Disable() { enabled = false; }

ComponentType Component::GetType()
{
    return type;
}

void Component::SetGameObject(GameObject* g_gameObject)
{
    gameObject = g_gameObject;
}

GameObject* Component::GetGameObject()
{
    return gameObject;
}
