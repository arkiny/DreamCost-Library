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
	constexpr auto partition(RandomIt lo, RandomIt hi, Compare comp)
	{
		if (lo == hi) return lo;

		auto pivot = *hi;
		auto i = lo;

		for (auto j = lo; j < hi; j++)
		{
			if (*j < pivot)
			{
				dc::swap(*i, *j);
				i++;
			}
		}

		dc::swap(*i, *hi);
		return i;
	};

	template<class RandomIt, class Compare>
	void quicksort(RandomIt lo, RandomIt hi, Compare comp)
	{
		if (lo < hi)
		{
			auto pivot = dc::partition(lo, hi, comp);
			if (lo < pivot)
				quicksort(lo, pivot - 1, comp);
			if (hi > pivot)
				quicksort(pivot + 1, hi, comp);
		}
	}

	template<class RandomIt, class Compare>
	void siftDown(RandomIt first, RandomIt last, unsigned int start, Compare comp)
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
	void heapify(RandomIt first, RandomIt last, Compare comp)
	{
		auto start = static_cast<long>(trunc(floor((last - first) / 2)));
		while (start >= 0)
		{
			dc::siftDown(first, last, start, comp);
			start--;
		}
	}



	template<class RandomIt, class Compare>
	void heapsort(RandomIt first, RandomIt last, Compare comp)
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
	constexpr void introsort(RandomIt lo, RandomIt hi, Compare comp, unsigned int maxdepth)
	{
		if (lo < hi)
		{
			auto pivot = dc::partition(lo, hi, comp);

			//if (maxdepth == 0)
			//{
			//	heapsort(lo, hi, comp);
			//}
			//else
			//{
				if (lo < pivot)
					dc::introsort(lo, pivot - 1, comp, maxdepth - 1);
				if (hi > pivot)
					dc::introsort(pivot + 1, hi, comp, maxdepth - 1);
			//}
		}
	}

	template<class RandomIt, class Compare>
	constexpr void introsort(RandomIt first, RandomIt last, Compare comp)
	{
		auto maxdepth = static_cast<unsigned int>(log(last - first) * 2);

		// because iterator.end() is not the element of array
		dc::introsort(first, --last, comp, maxdepth);
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
}