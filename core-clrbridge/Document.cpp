#include <msclr/marshal.h>

#include "CLRBridge.h"

#include "../clr-wrappers/CLRWrappers.h"
#include "../core/Document.h"

using namespace msclr::interop;
using namespace CLRWrappers;

public ref class FluteFingers::Core::Document
{
private:
	OwnedBox<::Document>^ inner;

	// TODO overthink namespace structure in core project
	Document(::Document document)
	{
		this->inner = gcnew OwnedBox<::Document>(document);
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