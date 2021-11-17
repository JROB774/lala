#include "Creature.h"

// The dimensions of all creature's sprites.
const int Creature::SPRITE_WIDTH = 104, Creature::SPRITE_HEIGHT = 104;
// The center point of all sprites.
const SDL_Point Creature::SPRITE_CENTER = { (SPRITE_WIDTH / 2), (SPRITE_HEIGHT / 2) };
// The idle animation.
Animation Creature::idle;
// The active animation.
Animation Creature::active;

void Creature::initialise()
{
	// Creates the animations for all creatures.
	idle.create(0, 0, SPRITE_WIDTH, SPRITE_HEIGHT, 1, 0);
	active.create(SPRITE_WIDTH, 0, SPRITE_WIDTH, SPRITE_HEIGHT, 1, 0);
}

void Creature::create(const int arg_x, const int arg_y, const double arg_angle, const std::string arg_file)
{
	// Sets the creature's position.
	x = arg_x, y = arg_y;
	// Sets the creature's angle.
	angle = arg_angle;
	// Sets the frame counter.
	frameCounter = 0;

	// Loads and creates the image and sound files for the creature.
	image.create(arg_file);
	sound.create(arg_file);

	// Sets the state.
	state = State::IDLE;
}

void Creature::activate()
{
	// If the creature is not already active...
	if (state != State::ACTIVE)
	{
		// ...set the creature's state.
		state = State::ACTIVE;
		// And set the frame counter so it's ready for use.
		frameCounter = 40;
		// Plays the creature's sound effect.
		sound.play(0);
	}
}

void Creature::step()
{
	// If the creature is active...
	if (state == State::ACTIVE)
	{
		// ...check to see if the frame counter is empty if so set the state to idle.
		if (frameCounter <= 0) state = State::IDLE;
		// Otherwise deiterate the frame counter.
		else frameCounter--;
	}
}

void Creature::render()
{
	// Renders the creature's correct sprite to the screen based on what state it is in.
	if (state == State::IDLE) image.render(x, y, angle, &SPRITE_CENTER, SDL_FLIP_NONE, idle.getCurrentSprite());
	else if (state == State::ACTIVE) image.render(x, y, angle, &SPRITE_CENTER, SDL_FLIP_NONE, active.getCurrentSprite());
}

int Creature::isActive() const{ return static_cast <int> (state); }

void Creature::destroy()
{
	// Resets the creature's values.
	x = 0, y = 0;
	angle = 0.0;
	frameCounter = 0;

	// Destroys the image and sound files.
	image.destroy();
	sound.destroy();

	// Resets the state.
	state = State::IDLE;
}

void Creature::terminate()
{
	// Destroys the creature's animations.
	idle.destroy();
	active.destroy();
}

Creature::~Creature(){ destroy(); }