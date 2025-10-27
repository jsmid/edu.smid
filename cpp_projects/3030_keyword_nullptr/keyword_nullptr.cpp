/*
    Keyword nullptr Example in C++

    Purpose:
    The keyword nullptr is introduced in C++11 to represent a null pointer constant. 
	It is of type std::nullptr_t and provides a type-safe and unambiguous way to denote null pointers, 
	addressing the limitations of the traditional NULL macro. 

	Key Features of nullptr
		- Type-Safe Null Pointer: Unlike NULL, which is typically defined as (void*)0 or 0, 
		nullptr is not implicitly convertible to integral types. 
		This eliminates ambiguity in function overloads where NULL could be interpreted as an integer.
		- Explicit Pointer Representation: nullptr is explicitly designed for pointers and cannot 
		be assigned to non-pointer types like integers. 
		- Function Overload Resolution: Using nullptr ensures that the correct function overload 
		is selected when dealing with pointers.
		- Comparison and Conversion: nullptr can be compared with any pointer type using == or !=. 
		It is also implicitly convertible to any pointer type but not to integral types, ensuring clarity and safety.
*/

#include <iostream>
using namespace std;

void process(int n) {
	cout << "Processing integer: " << n << endl;
}

void process(char* str) {
	// `nullptr` needs special handling because it represents a null pointer, 
	// meaning it points to no valid memory location. 
	// If you try to use or dereference a `nullptr`, your program will likely crash 
	// or behave unpredictably.
	// ** Key points: **
	// 	- `nullptr` is a safe, explicit way to indicate "no pointer."
	// 	- Always check for `nullptr` before using a pointer to avoid runtime errors.
	// 	- Printing or dereferencing a `nullptr` is unsafe.
	cout << "Processing string pointer: ";
	if (str == nullptr) {
		cout << "nullptr" << endl;
	} else {
		cout << str << endl;
	}
}

int main() {
	process(nullptr); 	// Calls the pointer version
	// process(NULL); 	// Ambiguous call, may lead to compilation error
	process(0);    		// Calls the integer version
	cout << "nullptr type: " << typeid(nullptr).name() << endl; // Outputs the type of nullp
	cout << "Is nullptr equal to NULL? " << (nullptr == NULL ? "Yes" : "No") << endl; // Comparison
	cout << "Is nullptr equal to 0? " << (nullptr == 0 ? "Yes" : "No") << endl; // Comparison
	cout << "Size of nullptr: " << sizeof(nullptr) << " bytes" << endl; // Size of nullptr
	cout << "Size of NULL: " << sizeof(NULL) << " bytes" << endl; // Size of NULL
	cout << "Size of 0: " << sizeof(0) << " bytes" << endl; // Size of 0
	cout << "Address of nullptr: " << static_cast<void*>(nullptr) << endl; // Address representation
	cout << "Address of NULL: " << static_cast<void*>(NULL) << endl; // Address representation
	cout << "Address of 0: " << static_cast<void*>(0) << endl; // Address representation

	// Not convertible to integral types, the following lines would cause a compilation error
	// cout << "Is nullptr convertible to int? " << (static_cast<int>(nullptr) == 0 ? "Yes" : "No") << endl; // Conversion check
	// cout << "Is nullptr convertible to double? " << (static_cast<double>(nullptr) == 0.0 ? "Yes" : "No") << endl; // Conversion check
	// cout << "Is nullptr convertible to float? " << (static_cast<float>(nullptr) == 0.0f ? "Yes" : "No") << endl; // Conversion check
	// cout << "Is nullptr convertible to long? " << (static_cast<long>(nullptr) == 0L ? "Yes" : "No") << endl; // Conversion check
	// cout << "Is nullptr convertible to short? " << (static_cast<short>(nullptr) == 0 ? "Yes" : "No") << endl; // Conversion check
	// cout << "Is nullptr convertible to long long? " << (static_cast<long long>(nullptr) == 0LL ? "Yes" : "No") << endl; // Conversion check
	// cout << "Is nullptr convertible to unsigned int? " << (static_cast<unsigned int>(nullptr) == 0U ? "Yes" : "No") << endl; // Conversion check
	// cout << "Is nullptr convertible to unsigned long? " << (static_cast<unsigned long>(nullptr) == 0UL ? "Yes" : "No") << endl; // Conversion check
	// cout << "Is nullptr convertible to unsigned long long? " << (static_cast<unsigned long long>(nullptr) == 0ULL ? "Yes" : "No") << endl; // Conversion check
	cout << "Is nullptr convertible to char*? " << (static_cast<char*>(nullptr) == nullptr ? "Yes" : "No") << endl; // Conversion check
	cout << "Is nullptr convertible to bool? " << (static_cast<bool>(nullptr) == false ? "Yes, but to no other integral type (int, long, etc.)!" : "No") << endl; // Conversion check
	cout << "Is nullptr convertible to wchar_t*? " << (static_cast<wchar_t*>(nullptr) == nullptr ? "Yes" : "No") << endl; // Conversion check
	cout << "Is nullptr convertible to void*? " << (static_cast<void*>(nullptr) == nullptr ? "Yes" : "No") << endl; // Conversion check
	cout << "Is nullptr convertible to signed char*? " << (static_cast<signed char*>(nullptr) == nullptr ? "Yes" : "No") << endl; // Conversion check
	cout << "Is nullptr convertible to unsigned char*? " << (static_cast<unsigned char*>(nullptr) == nullptr ? "Yes" : "No") << endl; // Conversion check
	cout << "Is nullptr convertible to short*? " << (static_cast<short*>(nullptr) == nullptr ? "Yes" : "No") << endl; // Conversion check
	cout << "Is nullptr convertible to int*? " << (static_cast<int*>(nullptr) == nullptr ? "Yes" : "No") << endl; // Conversion check
	cout << "Is nullptr convertible to long*? " << (static_cast<long*>(nullptr) == nullptr ? "Yes" : "No") << endl; // Conversion check
	cout << "Is nullptr convertible to float*? " << (static_cast<float*>(nullptr) == nullptr ? "Yes" : "No") << endl; // Conversion check
	cout << "Is nullptr convertible to double*? " << (static_cast<double*>(nullptr) == nullptr ? "Yes" : "No") << endl; // Conversion check
	cout << "Is nullptr convertible to bool*? " << (static_cast<bool*>(nullptr) == nullptr ? "Yes" : "No") << endl; // Conversion check
	
	return 0;
}