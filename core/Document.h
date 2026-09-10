#pragma once

#include "pch.h"

struct Document
{
	unsigned int const bars;
	unsigned int const systems;
};

__declspec(dllexport) Document loadMusicXML(const std::string& path);
__declspec(dllexport) Document loadCapXML10(const std::string& path);
