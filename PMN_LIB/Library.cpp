#include "stdafx.h"
#include <iostream>

extern "C"
{

	int __stdcall power(int a, int b)
	{
		return pow(b, a);
	}
	int __stdcall abser(int a)
	{
		return abs(a);
	}
	int __stdcall nout(int value)
	{
		std::cout << value;
		return 0;
	}
	int __stdcall sout(char* ptr)
	{
		if (ptr == nullptr)
		{
			std::cout << std::endl;
		}
		for (int i = 0; ptr[i] != '\0'; i++)
			std::cout << ptr[i];
		return 0;
	}
	int __stdcall noutl(int value)
	{
		std::cout << value << std::endl;
		return 0;
	}
	int __stdcall soutl(char* ptr)
	{
		if (ptr == nullptr)
		{
			std::cout << std::endl;
		}
		for (int i = 0; ptr[i] != '\0'; i++)
			std::cout << ptr[i];
		std::cout << std::endl;
		return 0;
	}
	int __stdcall SYSPAUSE()
	{
		system("pause");
		return 0;
	}
}