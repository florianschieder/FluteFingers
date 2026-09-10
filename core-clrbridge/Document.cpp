#include "../core/Document.h"

#include "CLRBridge.h"

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

	static Document^ FromCapXML10(System::String^ path)
	{
		// TODO System::String^ --> const std::string&
		return gcnew Document(::loadCapXML10("TODO"));
	}

	static Document^ FromMusicXML(System::String^ path)
	{
		// TODO System::String^ --> const std::string&
		return gcnew Document(::loadMusicXML("TODO"));
	}
};