#include <iostream>
#include <string>

template <class T> concept Addable = requires (T t) { t + t; };

int main()
{
	int x = 1, y = 2;
	Addable auto z = x + y;
	
	std::string a = "a", b = "b";
	Addable auto c = a + b;
	
	std::cout << x << " + " << y << " = " << z << std::endl
	          << "'" << a << "'" << " + " << "'" << b << "' = '" << c << "'" << std::endl;
}
