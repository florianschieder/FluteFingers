#include <msclr/marshal.h>

#include "CLRBridge.h"

#include "../core/Document.h"

using namespace msclr::interop;

public ref class FluteFingers::Core::Document
{
public:
	// TODO readonly properties & encapsulate ::Document somehow...
	int Bars;
	int Systems;

	// TODO idiomatic constructor definition?
	Document(::Document raw)
	{
		this->Bars = raw.bars;
		this->Systems = raw.systems;
	}

	static Document^ FromCapXML10(System::String^ refPath)
	{
		const auto context = gcnew marshal_context();
		const auto& path = context->marshal_as<const char*>(refPath);
		const auto lowLevelDocument = ::loadCapXML10(path);
		return gcnew Document(lowLevelDocument);
	}

	static Document^ FromMusicXML(System::String^ refPath)
	{
		const auto context = gcnew marshal_context();
		const auto& path = context->marshal_as<const char*>(refPath);
		const auto lowLevelDocument = ::loadMusicXML(path);
		return gcnew Document(lowLevelDocument);
	}
};