#include "Collider.h"

bool Collider::checkCollision(const SDL_Rect arg_first, const SDL_Rect arg_second)
{
	// Checks to see if the rects are overlapping, if not then the function returns false.
	if ((arg_first.y + arg_first.h) <= arg_second.y) return false;
	if (arg_first.y >= (arg_second.y + arg_second.h)) return false;
	if ((arg_first.x + arg_first.w) <= arg_second.x) return false;
	if (arg_first.x >= (arg_second.x + arg_second.w)) return false;

	// Otherwise the function returns true.
	return true;
}

Collider::Collider(){ collider = { 0, 0, 0, 0 }; }

void Collider::render(const Uint8 arg_r, const Uint8 arg_g, const Uint8 arg_b) const
{
	// If colliders should be rendered then...
	if (System::getRenderColliders())
	{
		// ...set the colour to render the collider...
		SDL_SetRenderDrawColor(System::getRenderer(), arg_r, arg_g, arg_b, 255);
		// ...and render the filled collider.
		SDL_RenderFillRect(System::getRenderer(), &collider);
	}
}

void Collider::setPosition(const int arg_x, const int arg_y){ collider.x = arg_x, collider.y = arg_y; }

void Collider::setDimensions(const int arg_w, const int arg_h){ collider.w = arg_w, collider.h = arg_h; }

SDL_Rect Collider::getCollider() const{ return collider; }

void Collider::destroy(){ collider = { 0, 0, 0, 0 }; }

Collider::~Collider(){ destroy(); }