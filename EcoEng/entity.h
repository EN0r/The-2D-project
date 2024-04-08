#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include "errorHandler.h"
#include "renderer.h"
#include "component.h" // Components are not related by inheritance now. theyre related via ID's.
/*
	have a ID list relational to each component so i can check
	transform = 1;
	if (transform == 1 ) then it is an transform component. else continue;
*/
class entity;
class component;

class entityManager
{
public:
	//requestUpdate
	// Because each one of them has an ID whenever you request to add a component it can know which is which without any complications.
	template<typename enT>
	void requestEntityUpdate(SDL_Renderer& renderer) // need to eventually elaborate on this.... Also, Require documentation.
	{
		if (std::is_base_of<entityManager, enT>())
		{
			std::vector<int> entities;
			for (auto entID : entityList)
			{
				//std::cout << entID.first << ": Is the entity ID of component" << std::endl;
				std::static_pointer_cast<enT>(entID.second)->setEID(entID.first); // Kinda painful but its somewhat of a workaround... Idk why this is happening in the first place.
				std::static_pointer_cast<enT>(entID.second)->update(renderer);
			}
		}
	}

	// Returns 0 if an entity with the same tag exists.
	// Creates an empty entity with a tag and emplaces it into entity list returns ID of entity.
	// if returns -1 then template argument is not a form of entity!
	template<typename enT>
	int createEntity() 
	{
		if (std::is_base_of<entityManager, enT>())
		{
			entityCount++;
			enT* x = new enT(entityCount);
			//std::cout << x->thisEntityID <<"ID" << std::endl;
			std::shared_ptr<void*> entBuf = std::make_shared<void*>(static_cast<void*>(x));
			entityList.emplace(entityCount, entBuf);
			return entityCount;
		}
		return -1;
	}

	// need to implement system later on to make sure that when entity has been updated to make sure it exists.
	bool deleteEntity(int entityID); // returns false if not found.

	// component stuffs
	// Add a component to a entity via a entity Identifier.
	template <typename component>
	int addComponent(int entityID) // if returns -1 then not a valid component.
	{
		if (std::is_base_of<componentContainer, component>()) // checks if it is a derivative of component container
		{
			componentRelationalCounter++;
			// the words of todd howard, It just works :) VVVVVVVVVVVVVVVVVVVVVVVV
			componentContainer* componentT = dynamic_cast<componentContainer*>(new component); // coding haram.... Raw ptr mixed in with shared...
			componentT->fatheredEntityID = entityID;
			componentT->componentID = componentRelationalCounter;
			std::shared_ptr<void*> cContainer = std::make_shared<void*>(static_cast<void*>(componentT));
			componentList.emplace(componentRelationalCounter, cContainer);
			entityComponentRelationship.emplace(entityID, componentT->getComponentIdentifier());
			delete componentT; // cleanup. Should use smart pointers for this one when im using them elsewhere but i am not.
			return componentRelationalCounter; // returns component ID
		}
		return -1;
	}

	// returns the identifier of the component in a INT value.
	template <typename T>
	int retCompIdentifier()
	{
		componentContainer* componentID = dynamic_cast<componentContainer*>(new T);
		return componentID->getComponentIdentifier();
	}

	// GetComponent returns the component it has aquired from the entity.
	template <typename component>
	std::shared_ptr<component> getComponent(int entityID) // if return nullptr then component not found
	{
		// Syntax ideally be getComponent<transform>(ENTID);
		if (std::is_base_of<componentContainer, component>()) // already made sure here to typecheck prior.
		{
			 /*
			 game plan!
				Get component Identifer e.g in the relationship status with its parent class.
				Once identifier has been got in the list i can recast it.
			 
			 */
			componentContainer* compCont = dynamic_cast<componentContainer*>(new component);
			for (auto identifiers : entityComponentRelationship)
			{
				// Get the relationship between this component's transformID and a component inside of the relationship map
				if (identifiers.first == entityID && identifiers.second == compCont->getComponentIdentifier())
				{
					for(auto compList : componentList)
					{
						if (compList.first != entityID)
							continue; // save memory and just skip instead of lookign at irrelevant entities.
						else
							return std::static_pointer_cast<component>(compList.second);
					}
					delete compCont;
				}
			}
		}
		else
			throw_line("Component requested does exist. Please create a for the entity.");
	}

	// n
	void update(SDL_Renderer& renderer) {};
	void start(SDL_Renderer& renderer) {};
private:
	// buffer so i can cast type into this. Needed
protected:
	int entityCount = 0;
	int componentRelationalCounter = 0;
	//             entity ID      entity object
	//                V                 V
	std::unordered_map<int, std::shared_ptr<void>> entityList; // Container for entities
	std::unordered_map<int, std::shared_ptr<void>> componentList; // Container for component  
	// ID of entity and ID of the component included inside of it.
	std::unordered_multimap<int, int> entityComponentRelationship;
	// Components in management.
	std::vector<std::shared_ptr<void>> managedComponents;
};


class entity : public entityManager
{
public:
	void update(SDL_Renderer& renderer);
	void start(std::shared_ptr<renderer> renderer);
	entity(int id) { thisEntityID = id; }
	void setEID(int id) { this->thisEntityID = id; }
private:
	int thisEntityID = -1;

	/*
	Data should be formatted as
	DATA:VALUE; 
	*/
	// all components are tags. E.g add a tag of "transform" and the entityManager will be watching for any transform
	//std::unordered_map<std::string, std::string> componentList; // Container for components. Key = component name, Value = Data.


};

