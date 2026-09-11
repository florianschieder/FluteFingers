#include <msclr/marshal.h>

#include "CLRBridge.h"

#include "../core/Document.h"

using namespace msclr::interop;

// TODO document and test heavily, source out and publish as NuGet package
template <class T> public ref class Box
{
protected:
	T* inner;

public:
	Box(T value)
	{
		this->inner = new T(std::move(value));
	}

	~Box()
	{
		delete this->inner;
	}

	T GetValue()
	{
		return *this->inner;
	}
};

public ref class FluteFingers::Core::Document
{
private:
	Box<::Document>^ inner;

	// TODO overthink namespace structure in core project
	Document(::Document document)
	{
		this->inner = gcnew Box<::Document>(document);
	}

public:
	property System::Int64 Bars {
		System::Int64 get() {
			return this->inner->GetValue().bars;
		}
	}
	property System::Int64 Systems {
		System::Int64 get() {
			return this->inner->GetValue().systems;
		}
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