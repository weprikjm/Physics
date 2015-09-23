#pragma once
#include "Module.h"
#include "Globals.h"

#define	TIMESTEP (float32) 1.0f / 60.f
#define VELOCITY_ITERATIONS (int32) 10
#define POSITION_ITERATIONS (int32) 8

#define GRAVITY_X 0.0f
#define GRAVITY_Y -10.0f

/*#define X_METERS 0.02f * xPixels
#define Y_METERS 0.02f * yPixels

#define X_PIXELS 50.0f * xMeters
#define Y_PIXELS 50.0f * yMeters
*/
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


	float pixelsToMeters(unsigned int num_pixels);
	int metersToPixels(float num_meters);

private:
	b2World* world;
	b2Body* groundCircle;
	bool debug;
};