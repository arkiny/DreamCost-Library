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
			} while (comp(*(arr+i), pivot));
			do
			{
				--j;
			} while (comp(pivot, *(arr+j)));

			if (i >= j)
				return j;

			dc::swap(*(arr+i), *(arr+j));
		}
	};

	template<class RandomIt, class Compare>
	constexpr void siftDown(RandomIt first, RandomIt last, size_t start, Compare comp)
	{
		auto rootIndex = start;
		auto rootItr = first+start;
		//iLeftChild(i) = 2 * i + 1
		auto leftChildIndex = 2 * rootIndex + 1;
		auto end = static_cast<unsigned int>(last - first);

		while (leftChildIndex <= end)
		{
			auto swapIndex = rootIndex;
			rootItr = first + rootIndex;
			RandomIt leftChildItr = first + leftChildIndex;

			if (comp(*(first+swapIndex), *leftChildItr))
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
		auto endIndex = last-first;

		while (endIndex > 0)
		{
			dc::swap(*(first+endIndex), *first);

			endIndex--;
			siftDown(first, (first+endIndex), 0, comp);
		}
	}

	template<class RandomIt, class Compare>
	constexpr void introsort(RandomIt arr, size_t start, size_t end, Compare comp)
	{
		if (start >= end) return;

		while (start < end)
		{
			if (end - start < 10)
			{
				dc::insertionSort(arr, start, end, comp);
				break;
			}
			else
			{
				auto partition = dc::partition(arr, start, end, comp);
				if (partition - start < end - partition)
				{
					dc::introsort(arr, start, partition, comp);
					start = partition + 1;
				}
				else
				{
					dc::introsort(arr, partition + 1, end, comp);
					end = partition - 1;
				}
			}
		} 
	}

	template<class RandomIt, class Compare>
	constexpr void introsort(RandomIt first, RandomIt last, Compare comp)
	{
		auto count = last - first;
		dc::introsort(first, 0, count-1 , comp);
	}

	template<class RandomIt, class Compare>
	constexpr void sort(RandomIt first, RandomIt last, Compare comp)
	{
		dc::introsort(first, last, comp);
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

	template<class T, class Compare>
	constexpr size_t partition_a(T* arr, size_t start, size_t end, Compare comp)
	{
		auto pivot = arr[(start + end) / 2];
		auto i = start-1;
		auto j = end+1;

		while (true)
		{
			do 
			{
				++i;
			} while (comp(arr[i], pivot));
			do
			{
				--j;
			} while (comp(pivot, arr[j]));

			if (i >= j)
				return j;

			dc::swap(arr[i], arr[j]);
		}
	}

	template<class T, class Compare>
	constexpr void asort(T* arr, size_t start, size_t end, Compare comp)
	{
		if (start >= end) return;
		auto partition = dc::partition_a(arr, start, end, comp);

		dc::asort(arr, start, partition, comp);
		dc::asort(arr, partition+1,	end, comp);	
	}

	template<class T>
	constexpr void asort(T* arr, size_t start, size_t end)
	{
		auto DefaultComparator = [](auto lhs, auto rhs)
		{
			return lhs < rhs;
		};

		dc::asort(arr, start, end, DefaultComparator);
	}
}