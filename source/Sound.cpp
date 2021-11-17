Sound::Sound(){ chunk = nullptr; }

void Sound::create(const std::string arg_file)
{
	// Destroys the previous sound, if there was one.
	destroy();

	// Creates the path that the sound can be found in.
	std::string directory = System::getSoundDirectory() + arg_file + ".sound";

	// Loads the sound into the chunk.
	chunk = Mix_LoadWAV(directory.c_str());
	if (chunk == nullptr) Error::log("Could not create a chunk from a SOUND file!", Error::Type::MIX);
}

void Sound::play(const unsigned int arg_repeat) const{ if (!System::isSoundMuted()) Mix_PlayChannel(-1, chunk, arg_repeat); }

void Sound::destroy()
{
	// If the sound is not already destroyed...
	if (chunk != nullptr)
	{
		// ...then destroy the sound and reset all the values.
		Mix_FreeChunk(chunk);
		chunk = nullptr;
	}
}

Sound::~Sound(){ destroy(); }
