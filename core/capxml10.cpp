#include "pch.h"

#include "Document.h"


Document loadCapXML10(const std::string& path)
{
	return Document{
		.bars = 1337,
		.systems = 4711,
	};
}
