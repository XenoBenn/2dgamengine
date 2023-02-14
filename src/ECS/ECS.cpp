#include "ECS.h"
#include <algorithm>
#include "../Logger/Logger.h"

int Entity::GetId() const {
    return id;
}

void System::AddEntityToSystem(Entity entity) {
    entities.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity) {
    entities.erase(std::remove_if(entities.begin(), entities.end(), [&entity](Entity other){
        return entity == other;
    }), entities.end());
}

std::vector<Entity> System::GetSystemEntites() const {
    return entities;
}

const Signature& System::GetComponentSignature() const {
    return componentSignature;
}

Entity Registry::CreateEntity() {
    int entityId;
    
    entityId = numEntites++;

    Entity entity(entityId);
    entitiesToBeAdded.insert(entity);
    
    Logger::Log("Entity created with id = " + std::to_string(entityId));

    return entity;
    
}

void Registry::Update() {
    //TODO:
}