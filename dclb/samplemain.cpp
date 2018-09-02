#include <algorithm>
#include <vector>
#include <iostream>
#include <ctime>
#include <chrono>
#include "Sort.h"

auto main() -> int
{
	std::srand(std::time(nullptr)); // use current time as seed for random generato

	int intArray[] = { 5, 3, 32, -1, 1, 104, 53 };
	int intArrayStd[] = { 5, 3, 32, -1, 1, 104, 53 };

	int arraysize = sizeof(intArray) / sizeof(intArray[0]);
	dc::sort(intArray, intArray+ arraysize);
	std::sort(intArrayStd, intArrayStd + arraysize);

	for (auto n : intArray)
	{
		std::cout << n << " ";
	}
	std::cout << std::endl;

	for (auto n : intArrayStd)
	{
		std::cout << n << " ";
	}

	std::cout << std::endl;


	std::vector<int> VectorTest = { 5, 3, 32, -1, 1, 104, 53 };
	std::vector<int> VectorTestStd = { 5, 3, 32, -1, 1, 104, 53 };
	dc::sort(VectorTest.begin(), VectorTest.end());
	std::sort(VectorTestStd.begin(), VectorTestStd.end());

	for (auto n : VectorTest)
	{
		std::cout << n << " ";
	}
	std::cout << std::endl;

	for (auto n : VectorTestStd)
	{
		std::cout << n << " ";
	}
	std::cout << std::endl;

	std::vector<int> UnsortedVectordcSmall(10);
	for (int i = 0; i < 10; ++i)
	{
		UnsortedVectordcSmall.push_back(std::rand());
	}
	std::vector<int> UnsortedVectorstdSml = UnsortedVectordcSmall;
	dc::sort(UnsortedVectordcSmall.begin(), UnsortedVectordcSmall.end());
	std::sort(UnsortedVectorstdSml.begin(), UnsortedVectorstdSml.end());
	for (auto n : UnsortedVectordcSmall)
	{
		std::cout << n << " ";
	}
	std::cout << std::endl;

	for (auto n : UnsortedVectorstdSml)
	{
		std::cout << n << " ";
	}
	std::cout << std::endl;

	std::vector<int> UnsortedVectordc(200000000);
	for (int i = 0; i < 200000000; ++i)
	{
		UnsortedVectordc.push_back(std::rand());
	}
	std::vector<int> UnsortedVectorstd = UnsortedVectordc;

	auto stdstart = std::chrono::high_resolution_clock::now();
	std::sort(UnsortedVectorstd.begin(), UnsortedVectorstd.end());
	auto stdend = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> std_ms = stdend - stdstart;

	std::cout << "Std Sorting Took " << std_ms.count() << "ms" << std::endl;

	auto dcstart = std::chrono::high_resolution_clock::now();
	dc::sort(UnsortedVectordc.begin(), UnsortedVectordc.end());
	auto dcend = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> dc_ms = dcend - dcstart;
	std::cout << "dc Sorting Took " << dc_ms.count() << "ms" << std::endl;

	
	system("pause");
	return 0;
}