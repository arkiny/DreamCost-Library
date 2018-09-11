#pragma once

namespace dc
{
	template<typename T>
	constexpr void swap(T& a, T& b)
	{
		T t = a;
		a = b;
		b = t;
	}

	template<typename T>
	constexpr void swap(T* a, T* b)
	{
		T* t = a;
		a = b;
		b = t;
	}

	template<class RandomIt, class Compare>
	constexpr void insertionSort(RandomIt arr, size_t low, size_t n, Compare comp)
	{
		for (size_t i = low + 1; i <= n; i++)
		{
			auto value = *(arr + i);
			auto j = i;
			while (j > low && comp(value, *(arr + (j - 1))))
			{
				*(arr + j) = *(arr + (j - 1));
				j--;
			}
			*(arr + j) = value;
		}
	}

	template<class RandomIt, class Compare>
	constexpr auto partition(RandomIt arr, size_t start, size_t end, Compare comp)
	{
		auto pivot = *(arr + ((start + end) / 2));
		auto i = start - 1;
		auto j = end + 1;

		while (true)
		{
			do
			{
				++i;
			} while (comp(*(arr + i), pivot));
			do
			{
				--j;
			} while (comp(pivot, *(arr + j)));

			if (i >= j)
				return j;

			dc::swap(*(arr + i), *(arr + j));
		}
	};

	template<class RandomIt, class Compare>
	constexpr void siftDown(RandomIt first, RandomIt last, size_t start, Compare comp)
	{
		auto rootIndex = start;
		auto rootItr = first + start;
		auto leftChildIndex = 2 * rootIndex + 1;
		auto end = static_cast<unsigned int>(last - first);

		while (leftChildIndex <= end)
		{
			auto swapIndex = rootIndex;
			rootItr = first + rootIndex;
			RandomIt leftChildItr = first + leftChildIndex;

			if (comp(*(first + swapIndex), *leftChildItr))
			{
				swapIndex = leftChildIndex;
			}
			if (leftChildIndex + 1 <= end
				&& comp(*(first + swapIndex), *(leftChildItr + 1)))
			{
				swapIndex = leftChildIndex + 1;
			}

			if (swapIndex == rootIndex)
			{
				return;
			}
			else
			{
				dc::swap(*rootItr, *(first + swapIndex));
				rootIndex = swapIndex;
				leftChildIndex = 2 * rootIndex + 1;
			}
		}
	}

	template<class RandomIt, class Compare>
	constexpr void heapify(RandomIt first, RandomIt last, Compare comp)
	{
		auto start = static_cast<long>(trunc(floor((last - first) / 2)));
		while (start >= 0)
		{
			dc::siftDown(first, last, start, comp);
			start--;
		}
	}



	template<class RandomIt, class Compare>
	constexpr void heapsort(RandomIt first, RandomIt last, Compare comp)
	{
		heapify(first, last, comp);
		auto endIndex = last - first;

		while (endIndex > 0)
		{
			dc::swap(*(first + endIndex), *first);

			endIndex--;
			siftDown(first, (first + endIndex), 0, comp);
		}
	}

	template<class RandomIt, class Compare>
	constexpr void hybridsort(RandomIt arr, size_t start, size_t end, /*size_t maxdepth,*/ Compare comp)
	{
		if (start < end)
		{
			if (end - start < 55)
			{
				for (size_t i = start + 1; i <= end; i++)
				{
					auto value = *(arr + i);
					auto j = i;
					while (j > start && comp(value, *(arr + (j - 1))))
					{
						*(arr + j) = *(arr + (j - 1));
						j--;
					}
					*(arr + j) = value;
				}
			}
			//else if (maxdepth == 0)
			//{
			//	dc::heapsort(arr, arr + end, comp);
			//}
			else
			{
				auto midind = ((start + end) >> 1);

				// med of three
				if (comp(*arr, *(arr + midind))) dc::swap(*arr, *(arr + midind));
				if (comp(*arr, *(arr + end))) dc::swap(*arr, *(arr + end));
				if (comp(*(arr + midind), *(arr + end))) dc::swap(*(arr + midind), *(arr + end));
			
				auto pivot = *(arr + midind);


				auto i = start - 1;
				auto j = end + 1;

				while (true)
				{
					do
					{
						++i;
					} while (comp(*(arr + i), pivot));
					do
					{
						--j;
					} while (comp(pivot, *(arr + j)));

					if (i >= j)
					{
						break;
					}

					dc::swap(*(arr + i), *(arr + j));
				}

				auto partition = j;

				dc::hybridsort(arr, start, partition, /*maxdepth - 1,*/ comp);
				dc::hybridsort(arr, partition + 1, end, /*maxdepth - 1,*/ comp);
			}
		}

	}

	//template<class RandomIt, class Compare>
	//constexpr void hybridsort(RandomIt first, RandomIt last, Compare comp)
	//{
	//	auto count = last - first;
	//	//auto md = static_cast<size_t>(log(count)) * 2;
	//	dc::hybridsort(first, 0, count - 1, /*md,*/ comp);
	//}

	template<class RandomIt, class Compare>
	constexpr void sort(RandomIt first, RandomIt last, Compare comp)
	{
		auto count = last - first;
		//auto md = static_cast<size_t>(log(count)) * 2;
		dc::hybridsort(first, 0, count - 1, /*md,*/ comp);
	}

	template<class RandomIt>
	constexpr void sort(RandomIt first, RandomIt last)
	{
		auto DefaultComparator = [](auto lhs, auto rhs)
		{
			return lhs < rhs;
		};
		dc::sort(first, last, DefaultComparator);
	}

	// Don't care execution poliycy for now
	//template< class ExecutionPolicy, class RandomIt >
	//void sort(ExecutionPolicy&& policy, RandomIt first, RandomIt last);

	//template< class ExecutionPolicy, class RandomIt, class Compare >
	//void sort(ExecutionPolicy&& policy, RandomIt first, RandomIt last, Compare comp);

	//template<class T, class Compare>
	//constexpr size_t partition_a(T* arr, size_t start, size_t end, Compare comp)
	//{
	//	auto pivot = arr[(start + end) / 2];
	//	auto i = start-1;
	//	auto j = end+1;

	//	while (true)
	//	{
	//		do 
	//		{
	//			++i;
	//		} while (comp(arr[i], pivot));
	//		do
	//		{
	//			--j;
	//		} while (comp(pivot, arr[j]));

	//		if (i >= j)
	//			return j;

	//		dc::swap(arr[i], arr[j]);
	//	}
	//}

	//template<class T, class Compare>
	//constexpr void asort(T* arr, size_t start, size_t end, Compare comp)
	//{
	//	if (start >= end) return;
	//	auto partition = dc::partition_a(arr, start, end, comp);

	//	dc::asort(arr, start, partition, comp);
	//	dc::asort(arr, partition+1,	end, comp);	
	//}

	//template<class T>
	//constexpr void asort(T* arr, size_t start, size_t end)
	//{
	//	auto DefaultComparator = [](auto lhs, auto rhs)
	//	{
	//		return lhs < rhs;
	//	};

	//	dc::asort(arr, start, end, DefaultComparator);
	//}
}