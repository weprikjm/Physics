#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"

#include "Box2D/Box2d/Box2D.h"
#pragma comment (lib, "Box2D/libx86/Debug/Box2D.lib")

#define GRAVITY_X 0.0f
#define GRAVITY_Y -10.0f

// TODO 1: Include Box 2 header and library

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled), world(NULL), groundCircle(NULL)
{
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	b2Vec2 gravity(GRAVITY_X, GRAVITY_Y);

	
	LOG("Creating Physics 2D environment");
	world = new b2World(gravity);

	// TODO 2: Create a private variable for the world
	// - You need to send it a default gravity
	// - You need init the world in the constructor
	// - Remember to destroy the world after using it
	b2BodyDef circle_def;
	circle_def.type = b2_dynamicBody;
	circle_def.position.Set(0.0f, 2.0f);

	groundCircle = world->CreateBody(&circle_def);

	b2PolygonShape dynamicCircle;
	dynamicCircle.SetAsBox(1.0f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicCircle;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	groundCircle->CreateFixture(&fixtureDef);
	// TODO 4: Create a a big static circle as "ground"
	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	// TODO 3: Update the simulation ("step" the world)

	
	world->Step((float32)TIMESTEP, (int32)VELOCITY_ITERATIONS, (int32)POSITION_ITERATIONS);
	world->ClearForces();
	
	return UPDATE_CONTINUE;
}


update_status ModulePhysics::PostUpdate()
{
	// TODO 5: On space bar press, create a circle on mouse position
	// - You need to transform the position / radius

	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	/*
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
				}
				break;

				// You will have to add more cases to draw boxes, edges, and polygons ...
			}
		}
	}*/

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");
	// Delete the whole physics world!
	world->DestroyBody(groundCircle);
	delete(world);
	
	return true;
}
