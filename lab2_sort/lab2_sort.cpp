#include <iostream>
#include <vector>
#include <random>

struct stats {
	size_t comparison_count = 0;
	size_t copy_count = 0;
};

std::vector<int> create_vector(int n, int min, int max)
{
	std::vector<int> arr;
	int elem;
	srand(time(0));
	for (int i = 0; i < n; i++) {
		elem = - rand() % min + rand() % max;
		arr.push_back(elem);
	}
	return arr;
}

std::vector<int> reverse_vector(std::vector<int> arr) {
	for (int i = 0; i < arr.size() / 2; i++) {
		std::swap(arr[i], arr[arr.size() - 1 - i]);
	}
	return arr;
}

//void print(std::vector<int>& arr) {
//	for (auto i = arr.begin(); i != arr.end(); ++i) {
//		std::cout << *i << " ";
//	}
//	std::cout << std::endl;
//}

stats shaker_sort(std::vector<int>& arr)
{
	int right = arr.size() - 1;
	int left = 1;
	stats info;
	while (left <= right)
	{
		for (auto i = left; i <= right; i++)
		{
			if (arr[i - 1] > arr[i])
			{
				std::swap(arr[i - 1], arr[i]);
				info.copy_count += 1;
			}
			info.comparison_count += 1;
		}
		right--;

		for (auto i = right; i >= left; i--)
		{
			if (arr[i - 1] > arr[i])
			{
				std::swap(arr[i - 1], arr[i]);
				info.copy_count += 1;
			}
			info.comparison_count += 1;
		}
		left++;
	}
	return info;
}

stats inserts_sort(std::vector<int>& arr)
{
	stats info;
	for (int i = 0; i < arr.size(); i++)
	{
		for (int j = i + 1; j - 1 > 0 && j < arr.size(); j--)
		{
			if (arr[j - 1] > arr[j])
			{
				std::swap(arr[j - 1], arr[j]);
				info.copy_count += 1;
			}
			info.comparison_count += 1;
		}
	}
	return info;
}


stats(*sort)(std::vector<int>& arr);

std::vector<stats> generate_stats(int len, stats sort(std::vector<int>& arr))
{
	std::vector<stats> data;

	// а. в среднем (генерация 100 массивов)
	stats info_rand;
	for (int i = 0; i < 100; i++)
	{
		auto vect = create_vector(len, -10000, 10000);
		stats st_rand = sort(vect);
		info_rand.comparison_count += st_rand.comparison_count;
		info_rand.copy_count += st_rand.copy_count;
	}
	info_rand.comparison_count /= 100;
	info_rand.copy_count /= 100;
	data.push_back(info_rand);
	std::cout << "Average comparison " << len << " : " << info_rand.comparison_count << std::endl;
	std::cout << "Average copy " << len << " : " << info_rand.copy_count << std::endl;
	std::cout << std::endl;

	// б. для отсортированного массива
	auto sort_vec = create_vector(len, -10000, 10000);
	sort(sort_vec);
	stats info_sort = sort(sort_vec);
	data.push_back(info_sort);
	std::cout << "Sort comparison " << len << " : " << info_sort.comparison_count << std::endl;
	std::cout << "Sort copy " << len << " : " << info_sort.copy_count << std::endl;
	std::cout << std::endl;

	// в. для обратно отсортированного массива
	auto reverse_vec = reverse_vector(sort_vec);
	auto info_rev = sort(reverse_vec);
	data.push_back(info_rev);
	std::cout << "Reverse comparison " << len << " : " << info_rev.comparison_count << std::endl;
	std::cout << "Reverse copy " << len << " : " << info_rev.copy_count << std::endl;
	std::cout << std::endl;

	return data;
}

void statistic_sort(stats sort(std::vector<int>& arr)) {
	for (int i = 1000; i < 10001; i += 1000) {
		generate_stats(i, sort);
	}
	for (int i = 25000; i < 50001; i += 25000) {
		generate_stats(i, sort);
	}
	for (int i = 50000; i < 100001; i += 50000) {
		generate_stats(i, sort);
	}
}

void all_info()
{
	std::cout << "SHAKER SORT" << std::endl;
	statistic_sort(shaker_sort);
	std::cout << "INSERT SORT" << std::endl;
	statistic_sort(inserts_sort);
}

int main()
{
	/*auto arr = create_vector(10, -10000, 10000);
	shaker_sort(arr);
	print(arr);*/
	all_info();
}
