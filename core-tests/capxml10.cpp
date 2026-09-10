#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test_musicxml
{
	TEST_CLASS(LoadCapXML10Tests)
	{
	public:

		TEST_METHOD(systems)
		{
			const auto with1Systems = loadCapXML10(
				"assets/simple-1sys-3bars.capx");
			const auto with2Systems = loadCapXML10(
				"assets/simple-2sys-3bars.capx");

			Assert::AreEqual(
				static_cast<unsigned int>(1), with1Systems.systems);
			Assert::AreEqual(
				static_cast<unsigned int>(2), with2Systems.systems);
		}

		TEST_METHOD(bars)
		{
			const auto with1Systems = loadCapXML10(
				"assets/simple-1sys-3bars.capx");
			const auto with2Systems = loadCapXML10(
				"assets/simple-2sys-3bars.capx");

			Assert::AreEqual(
				static_cast<unsigned int>(3), with1Systems.systems);
			Assert::AreEqual(
				static_cast<unsigned int>(3), with2Systems.systems);
		}
	};
}
