#pragma once

#include <utility>

namespace CLRWrappers
{
	/// <summary>
	/// Easily wrap non-managed values on managed classes.
	/// </summary>
	/// <typeparam name="T">
	/// A native C++ type that can be moved, dynamically allocated
	/// and deleted.
	/// </typeparam>
	template <class T> public ref class OwnedBox
	{
	protected:
		T* inner;

	public:
		/// <summary>Create a new `OwnedBox`.</summary>
		/// <param name="value">
		/// A non-managed value. When passing it into `gcnew OwnedBox(...)`, it is
		/// consumed (`std::move`) and MUST NOT be used afterwards.
		/// </param>
		OwnedBox(T& value)
		{
			this->inner = new T(std::move(value));
		}

		~OwnedBox()
		{
			this->!OwnedBox();
		}

		!OwnedBox()
		{
			delete this->inner;
			this->inner = nullptr;
		}

		/// <summary>
		/// Get the wrapped, non-managed value. Does not transfer ownership.
		/// </summary>
		/// <returns>A reference to the wrapped value.</returns>
		T& GetValue()
		{
			return *this->inner;
		}
	};
}