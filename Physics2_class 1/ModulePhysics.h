#pragma once
#include "Module.h"
#include "Globals.h"

#define	TIMESTEP (float32) 1.0f / 60.f
#define VELOCITY_ITERATIONS (int32) 10
#define POSITION_ITERATIONS (int32) 8

class b2World;
class b2Body;
class ModulePhysics : public Module
{
public:

	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();
	
	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

private:
	b2World* world;
	b2Body* groundCircle;
	bool debug;
};