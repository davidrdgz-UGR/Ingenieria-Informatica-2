#include <iostream>
#include <random>

int main()
{
	std::random_device device;
	std::default_random_engine engine(device());

	for (int i = 0; i < 100; ++i)
	{
		int a = engine() % 10, b = engine() % 10;

		std::cout << "a = " << a << std::flush
		          << "\t b = " << b << std::flush
		          << "\t a/b = " << a / b << std::endl;
	}
}
