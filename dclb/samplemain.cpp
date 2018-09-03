#include <algorithm>
#include <vector>
#include <iostream>
#include <ctime>
#include <chrono>
#include "Sort.h"

auto main() -> int
{
	
	std::vector<int> UnsortedVectordc(200000000);
	for (int i = 0; i < 200000000; ++i)
	{
		UnsortedVectordc.push_back(std::rand() % 200000);
	}
	std::vector<int> UnsortedVectorstd(200000000);
	UnsortedVectorstd = UnsortedVectordc;

	std::vector<int> UnsortedVectorarr(200000000);
	UnsortedVectorarr = UnsortedVectordc;

	auto stdstart = std::chrono::high_resolution_clock::now();
	std::sort(UnsortedVectorstd.begin(), UnsortedVectorstd.end());
	auto stdend = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> std_ms = stdend - stdstart;

	std::cout << "Std Sorting Took " << std_ms.count() << "ms" << std::endl;

	auto arrstart = std::chrono::high_resolution_clock::now();
	JFFoundation::Sort(&UnsortedVectorarr[0], 0, UnsortedVectorarr.size()-1);
	auto arrend = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> arr_ms = arrend - arrstart;
	std::cout << "Jaraffe Sorting Took " << arr_ms.count() << "ms" << std::endl;

	auto dcstart = std::chrono::high_resolution_clock::now();
	dc::sort(UnsortedVectordc.begin(), UnsortedVectordc.end());
	auto dcend = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> dc_ms = dcend - dcstart;
	std::cout << "dc Sorting Took " << dc_ms.count() << "ms" << std::endl;


	system("pause");
	return 0;
}