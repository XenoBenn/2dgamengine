#include "ECS.h"
#include <algorithm>

int Entity::GetId() const {
    return id;
}

void System::AddEntityToSystem(Entity entity) {
    entities.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity) {
    entities.erase(std::remove_if(entities.begin(), entities.end(), [&entity](Entity other){
        return entity.GetId() == other.GetId();
    }), entities.end());
}

std::vector<Entity> System::GetSystemEntites() const {
    return entities;
}

const Signature& System::GetComponentSignature() const {
    return componentSignature;
}