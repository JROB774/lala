#ifndef INCLUDE_MAIN
#define INCLUDE_MAIN

#ifdef PLATFORM_WEB
#include <emscripten.h>
#endif

#include <cstdlib>
#include <ctime>

#include <sstream>
#include <string>
#include <fstream>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC

#include <stb_image.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "Timer.h"
#include "System.h"
#include "Image.h"
#include "Font.h"
#include "Sound.h"
#include "Animation.h"
#include "Background.h"
#include "Creature.h"
#include "Cloud.h"
#include "Spawner.h"
#include "Collider.h"
#include "Menu.h"
#include "Game.h"
#include "Error.h"
#include "Platform.h"

#endif // INCLUDE_MAIN
