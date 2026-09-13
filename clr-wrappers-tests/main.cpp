#include <cstdlib>
#include <format>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../clr-wrappers/Box.h"

using namespace CLRWrappers;
using namespace System::Runtime::CompilerServices;

/*
 * common utility functions
 */
template <typename T> void assertEqual(T expected, T actual)
{
	if (expected != actual) {
		const auto msg = std::format(
			"{} != {}", expected, actual);
		throw std::runtime_error(msg);
	}
	else {
		std::cout << ".";
	}
}

template <typename T> void assertNull(T* ptr)
{
	if (ptr != nullptr) {
		throw std::runtime_error("expected nullptr");
	}
}

/*
 * Tests
 */
void testOwnedBoxOwnership()
{
	std::cout << "testOwnedBoxOwnership";

	// This test makes heavy use of a shared pointer to demonstrate and
	// validate ownership behavior regarding the `OwnedBox` implementation.
	// First, we create a shared pointer holding the value 1337.
	auto ptr = std::make_shared<int>(1337);

	// There is only one owner: ptr
	assertEqual(1L, ptr.use_count());

	// There are two owners now: ptr & owned (via owned->inner). For
	// demonstration purposes we check whether the value is accessible
	// and whether the reference count decreases to 1 after destroying
	// 'owned'.
	struct Owned
	{
		std::shared_ptr<int> inner;
	};
	auto owned = new Owned{ .inner = ptr };
	assertEqual(2L, ptr.use_count());
	assertEqual(1337, *owned->inner.get());
	assertEqual(2L, ptr.use_count());
	delete owned;
	assertEqual(1L, ptr.use_count());

	// Internally, `OwnedBox` makes use of `std::move`. We want to demonstrate
	// what happens when moving a shared pointer manually: `ptr` is unusable,
	// `newPtr` can be resolved and only has one owner.
	auto newPtr = std::move(ptr);
	assertEqual(0L, ptr.use_count());
	assertNull(ptr.get());

	assertEqual(1L, newPtr.use_count());
	assertEqual(1337, *newPtr.get());
	assertEqual(1L, newPtr.use_count());

	// `gcnew OwnedBox` moves does the same: now newPtr is unusable, `boxed` can
	// be resolved, the inner value only has one owner. Resolving the boxed
	// value does not copy the owned value either.
	auto boxed = gcnew OwnedBox<std::shared_ptr<int>>(newPtr);
	assertEqual(0L, newPtr.use_count());
	assertNull(newPtr.get());

	assertEqual(1L, boxed->GetValue().use_count());
	assertEqual(1337, *boxed->GetValue().get());
	assertEqual(1L, boxed->GetValue().use_count());

	std::cout << std::endl;
}

void testOwnedBoxWithComplexStruct()
{
	std::cout << "testOwnedBoxWithComplexStruct";

	struct Book {
		std::string author;
		std::string title;
	};

	struct Person {
		std::string name;
		int age;
		std::vector<Book> books;
	};

	auto me = Person{
		.name = "Florian",
		.age = 24,
		.books = {
			Book{ .author = "Lindrid Astgren", .title = "Rövja ronerdottar" },
			Book{ .author = "R. K. Jowling", .title = "Parry Hotter" },
		}
	};
	auto boxedMe = gcnew OwnedBox<Person>(me);
	assertEqual(
		std::string("Lindrid Astgren"),
		boxedMe->GetValue().books[0].author);
	assertEqual(
		std::string("Parry Hotter"),
		boxedMe->GetValue().books[1].title);

	std::cout << std::endl;
}

class Destructable
{
public:
	static int destructed;

	~Destructable()
	{
		++destructed;
	}
};

int Destructable::destructed = 0;


// Force the runtime to not inline the function because this implicitly extends
// the OwnedBox lifetime. The test intentionally relies on the object becoming
// unreachable, to ensure the OwnedBox finalizer is triggered on GC collection.
[MethodImpl(MethodImplOptions::NoInlining)]
System::WeakReference^ createOwnedDestructableWeakReference()
{
	auto destructable = Destructable{};
	auto owned = gcnew OwnedBox<Destructable>(destructable);

	return gcnew System::WeakReference(owned);
}

void testOwnedBoxDestructionViaGC()
{
	std::cout << "testOwnedBoxDestructionViaGC";

	auto ref = createOwnedDestructableWeakReference();

	assertEqual(1, Destructable::destructed);
	assertEqual(true, ref->IsAlive);

	System::GC::Collect();
	System::GC::WaitForPendingFinalizers();
	System::GC::Collect();

	assertEqual(false, ref->IsAlive);
	assertEqual(2, Destructable::destructed);

	std::cout << std::endl;
}

int main()
{
	std::cout << "running tests..." << std::endl;

	testOwnedBoxOwnership();
	testOwnedBoxWithComplexStruct();
	testOwnedBoxDestructionViaGC();

	std::cout << "done." << std::endl;
	return EXIT_SUCCESS;
}