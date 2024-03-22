#pragma once
/*
IDENTIFIER GLOSSARY :)
	1 = transform
	more soon!!!!!!!!

	Should add enum values for it for updates.
*/
#include <iostream>
#include "vec2.h"
class componentContainer
{
public:
	unsigned int fatheredEntityID = -1; // the entity which overarchs this component and has this inside of it.
	unsigned int componentID = -1; // this is pain. side note: this is for checking what type of component it will be .
	int getComponentIdentifier() { return this->identifier; } // Identifier will NEVER change.
	const char* tag = "NULL";

	void update();
	void start();

protected:
	int identifier = -1; // this should never be able to be changed.

};
class transform : public componentContainer
{
public:
	vec2 position = {0,0};

	transform() { identifier = 1; }
};
class rigidBody : public componentContainer
{
public:
	rigidBody() { identifier = 2;  }
	int force;
};
class sprite : public componentContainer
{
public:
	// all sprite does is load a sprite. Renderer will manage updates.
	void update();
	void start();
};