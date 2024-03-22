#include "entity.h"

/*
template<typename enT>
int entityManager::createEntity()
{
    entityCount++;
    std::shared_ptr<void*> entBuf = static_cast<void*>(new enT);
    entityList.insert(entityCount,new enT);
    return entityCount;
}
*/

bool entityManager::deleteEntity(int entityID)
{
    for (auto entity : entityList)
    {
        if (entity.first == entityID)
        {
            entityList.erase(entity.first); 
            return true; // return true if entity has been found and deleted
        }
    }
    return false; // returns false if entity has not been sucessfully found.
}


/*

void entityManager::requestEntityUpdate(std::string childTag, std::vector<std::string> componentList)
{
    switch (comp)
    {
    case transform:

    default:
        break;
    }


}

// Scrapped VVVVVVVVVVVV
template<typename enT>
int entityManager::createEntity(std::string tag)
{
    std::unordered_map<std::string, std::shared_ptr<void*> >::const_iterator got = entityList.find(tag);
    if (got != entityList.end())
        return 0; // Entity Already Exists!
    entityCount++; // add More entities;
    enT* reserveBuffer;
    entityList.emplace(tag, std::make_shared<void*>(static_cast<void*>(reserveBuffer)));
    return 1;
}

*/

/*
bool entityManager::deleteEntity(std::string tag)
{
    if (entityList.erase(tag) == 0 ) // entity not found
        return false;
    entityCount--;
    return true;
}
*/
/*
bool entity::addComponent(std::string component)
{
    std::string strBuffer;
    for (auto letters : component) { strBuffer += tolower(letters); }
    for (auto c : componentList) { if (c.first == strBuffer) { return false; } }
    componentList.emplace(strBuffer);
    return true;
}
*/
/*


    bool entity::removeComponent(std::string component)
    {
        std::string strBuffer;
        for (auto letters : component)
        {
            strBuffer += tolower(letters);
        }
        for (auto i = 0; i < componentList.size(); i++)
        {
            if (componentList[i] == strBuffer)
                componentList[i].erase();
        }
        return false;
    }

*/
