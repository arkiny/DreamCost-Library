#include <algorithm>
#include <vector>
#include <iostream>
#include <ctime>
#include <chrono>
#include "Sort.h"

auto main() -> int
{
	std::vector<int> UnsortedVectordc;

	UnsortedVectordc.reserve(2000000000);
	for (int i = 0; i < 2000000000; ++i)
	{
		UnsortedVectordc.push_back(std::rand() % 10000000);
	}

	std::vector<int> UnsortedVectorstd;
	UnsortedVectorstd = UnsortedVectordc;

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

	//for (auto p : UnsortedVectordc)
	//{
	//	std::cout << p << "  ";
	//}


	system("pause");
	return 0;
}