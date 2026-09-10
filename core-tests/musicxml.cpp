#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test_musicxml
{
	TEST_CLASS(LoadMusicXMLTests)
	{
		public:
		
			TEST_METHOD(systems)
			{
				const auto with1Systems = loadMusicXML(
					"assets/simple-1sys-3bars.musicxml");
				const auto with2Systems = loadMusicXML(
					"assets/simple-2sys-3bars.musicxml");

				Assert::AreEqual(
					static_cast<unsigned int>(1), with1Systems.systems);
				Assert::AreEqual(
					static_cast<unsigned int>(2), with2Systems.systems);
			}

			TEST_METHOD(bars)
			{
				const auto with1Systems = loadMusicXML(
					"assets/simple-1sys-3bars.musicxml");
				const auto with2Systems = loadMusicXML(
					"assets/simple-2sys-3bars.musicxml");

				Assert::AreEqual(
					static_cast<unsigned int>(3), with1Systems.systems);
				Assert::AreEqual(
					static_cast<unsigned int>(3), with2Systems.systems);
			}
	};
}
