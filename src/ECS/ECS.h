#ifndef ECS_H
#define ECS_H

#include <vector>
#include <bitset>
#include <set>
#include <unordered_map>
#include <typeindex>

const unsigned int MAX_COMPONENTS = 32;

///////////////////////////////////////////////////////////////////
// Signature
///////////////////////////////////////////////////////////////////
// We use a bitset (1s and 0s) to keep track of which components an entity has,
// and also helps keep track of which entities a system is interested in
///////////////////////////////////////////////////////////////////
typedef std::bitset<MAX_COMPONENTS> Signature;

struct IComponent {
    protected:
        static int nextId;
};

// Used to assign a uinique id to a component type
template <typename T>
class Component: public IComponent {
    // Returns the uniqe id of Component<T>
    static int GetId() {
        static auto id = nextId++;
        return id;
    }
};

class Entity {
    private:
        int id;

    public:
        Entity(int id): id(id) {};
        Entity(const Entity& entity) = default;
        int GetId() const;

        Entity& operator = (const Entity& other) = default;
        bool operator == (const Entity& other) const { return id == other.id; }
        bool operator != (const Entity& other) const { return id != other.id; }
        bool operator > (const Entity& other) const { return id > other.id; }
        bool operator < (const Entity& other) const { return id < other.id; }

};

///////////////////////////////////////////////////////////////////
// System
///////////////////////////////////////////////////////////////////
// The system processes entitites that contain a specific signature
///////////////////////////////////////////////////////////////////

class System {
    private:
        Signature componentSignature;
        std::vector<Entity> entities;

    public:
        System() = default;
        ~System() = default;

        void AddEntityToSystem(Entity entity);
        void RemoveEntityFromSystem(Entity entity);
        std::vector<Entity> GetSystemEntites() const;
        const Signature& GetComponentSignature() const;

        //Defines the component type that entitiies must have to be considered by the system
        template <typename TComponent> void RequireComponent();

};

///////////////////////////////////////////////////////////////////
// Pool
///////////////////////////////////////////////////////////////////
// A pool is jsut a vector (contigous data) of objects of type T
///////////////////////////////////////////////////////////////////
class IPool {
    public:
        virtual ~IPool() {}
};

template <typename T>
class Pool: public IPool {
    private:
        std::vector<T> data;

    public:
        Pool(int size = 100) {
            data.resize(size);
        }
        
        virtual ~Pool() = default;

        bool isEmpty() const {
            return data.empty();
        }

        int GetSize() const {
            return data.size();
        }

        void Resize(int n ) {
            data.resize(n);
        }

        void Clear() {
            data.clear();
        }

        void Add(T object) {
            data.push_back(object);
        } 

        void Set(int index, T object) {
            data[index] = object;
        }

        T& Get(int index) {
            return static_cast<T&>(data[index]);
        }

        T& operator[](unsigned int index) {
            return data[index];
        }

};

///////////////////////////////////////////////////////////////////
// Registry
///////////////////////////////////////////////////////////////////
// The registry manages the creation and destructions of entities
// and components.
///////////////////////////////////////////////////////////////////
class Registry {
    private:
        int numEntites = 0;

        // Vector of component pools, each pool contains all the data for a certain component type
        // [Vector index = component type id]
        // [Pool index = entity id]
        std::vector<IPool*> componentPools;

        // Vector of component signatures per entity, saying which component is turned "on" for a given entity
        // [Vector index = entity id]
        std::vector<Signature> entityComponentSignatures;

        std::unordered_map<std::type_index, System*> systems;

        // Set of entities that are flagged to be added or removed in the next rtegistry Update()
        std::set<Entity> entitiesToBeAdded;
        std::set<Entity> entitiesToBeKilled;

    public:
        Registry() = default;
        
        void Update();

        // Entity management
        Entity CreateEntity();

        //Component management
        template <typename TComponent, typename ...TArgs> void AddComponent(Entity entity, TArgs&& ...args);

        // TODO: void AddEntityToSystem(Entity entity);
        
};

template <typename TComponent>
void System::RequireComponent() {
    const auto componentId = Component<TComponent>::GetId();
    componentSignature.set(componentId);
}

template <typename TComponent, typename ...TArgs>
void Registry::AddComponent(Entity entity, TArgs&& ...args) {
    const auto componentId = Component<TComponent>::GetId();
    const auto entityId = entity.GetId();

    if (componentId >= componentPools.size=())
    {
        componentPools.resize(componentId + 1, nullptr); 
    }
    
    if (!componentPools[componentId])
    {
        Pool<TComponent>* newComponentPool = new Pool<TComponent>();
        componentPools[componentId] = newComponentPool;
    }

    Pool<TComponent>* componentPool = componentPools[componentId];

    if (entityId >= componentPool->GetSize())
    {
        componentPool-> Resize(numEntites);
    }
    
    TComponent newComponent(std::forward<TArgs>(args)...);

    componentPool->Set(entityId, newComponent);
    
    entityComponentSignatures[entity].set(componentId);
}

#endif