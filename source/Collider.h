#ifndef INCLUDE_COLLIDER
#define INCLUDE_COLLIDER

#include "System.h"

// A collider objects, stores and manipulates the position and dimensions of a collison box.

class Collider
{
	public:
		// Checks to see if their is a collisison between two colliders.
		static bool checkCollision(const SDL_Rect, const SDL_Rect);
		// The constructor.
		Collider();
		// Renders the collider.
		void render(const Uint8, const Uint8, const Uint8) const;
		// Sets the position of the collider.
		void setPosition(const int, const int);
		// Sets the dimensions of the collider.
		void setDimensions(const int, const int);
		// Returns the collider rect itself.
		SDL_Rect getCollider() const;
		// Destroys the collider after use.
		void destroy();
		// The destructor.
		~Collider();
	private:
		// A rect that stores the collision box's information.
		SDL_Rect collider;
};

#endif // INCLUDE_COLLIDER