#include "Spawner.h"

// The range of time in which a cloud will take to spawn.
const int Spawner::SPAWN_MAX = 1, Spawner::SPAWN_MIN = 1;

Spawner::Spawner(){ spawnCounter = 0; }

void Spawner::initialise(){ Cloud::initialise(); }

void Spawner::create()
{
	// If a cloud has been spawned set a time for the next cloud to be spanwed.
	if (spawnCounter < 0) spawnCounter = rand() % SPAWN_MAX + SPAWN_MIN;
	// If the counter is complete...
	else if (spawnCounter == 0)
	{
		// ...spawn a cloud into the game.
		cloud.push_back(0);
		cloud.back() = new Cloud(0);
		cloud.back() -> create();
	}

	// Deiterates the spawn counter.
	spawnCounter--;
}

void Spawner::step()
{
	// Moves all the clouds.
	for (unsigned int i = 0; i < cloud.size(); i++) cloud.at(i) -> step();

	// Checks to see if any clouds are off-screen, if so they are destroyed.
	for (unsigned int i = 0; i < cloud.size(); i++) if (cloud.at(i) -> isDead()) cloud.erase(cloud.begin() + i);
}

void Spawner::render(){ for (unsigned int i = 0; i < cloud.size(); i++) cloud.at(i) -> render(); }

void Spawner::destroy(){ cloud.clear(); }

void Spawner::terminate(){ Cloud::terminate(); }

Spawner::~Spawner(){ destroy(); }