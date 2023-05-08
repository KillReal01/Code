#include <iostream>
#include <fstream>
#include "structures.h"

void galopingModeLeft(int* array, int* tmp, int left, int middle, int& i, int j, int& pos_arr);
void galopingModeRight(int* array, int* tmp, int left, int middle, int right, int i, int& j, int& pos_arr);

void insertionSort(int* array, int left, int right);
void findRun(int* array, int& pos, int& right);

void mergeLogic(int* array, myStack*& stack, TInf& x, TInf& y, TInf& z);
void mergeArrays(int* array, int left, int middle, int right);
void mergeRunsXY(myStack*& stack, int* array, TInf x, TInf y);
void mergeRunsYZ(myStack*& stack, int* array, TInf y, TInf z);

void printArray(int* array);
int getMinrun();
int* readFile(std::string name);
void writeFile(int* array, std::string name);

int N, minrun;

int main() {
	myStack* stack = 0;
	TInf pair, tmp, x, y, z;
	//position in current array, range run
	int pos = 0, left = 0, right = 0;
	int * array = readFile("input.txt");

	//std::cin >> N;
	//int* array = new int[N];
	//srand(time(0));
	//for (int i = 0; i < N; i++) {
	//	array[i] = rand() % 100001;
	//}

	minrun = getMinrun();
	std::cout << "N: " << N << " minrun: " << minrun << "\n";

	while (pos < N) {
		left = pos;
		findRun(array, pos, right);//find run
		insertionSort(array, left, right);//sort run
		pair.first = left;
		pair.second = right - left + 1;
		pushItemStack(stack, pair);//run to stack
		mergeLogic(array, stack, x, y, z);//merge runs
	}
	while (y.second) {//merge remaining items on the stack
		mergeRunsXY(stack, array, x, y);
		getLastThreeSubarray(stack, x, y, z);
	}

	//printArray(array);
	writeFile(array, "output.txt");
	std::cout << "The array is sorted, check file 'output.txt'\n";
	//freeing memory
	popItemStack(stack);
	delete[] array;
	return 0;
}

void mergeLogic(int * array, myStack*& stack, TInf& x, TInf& y, TInf& z) {
	getLastThreeSubarray(stack, x, y, z);
	while (!(z.second > x.second + y.second && y.second > x.second)) {
		if (z.second) {// >= 3 items on stack
			if (x.second < z.second) {
				mergeRunsXY(stack, array, x, y);
			}
			else {
				mergeRunsYZ(stack, array, y, z);
			}
		}
		else if (y.second) {// >= 2 items on stack
			if (y.second <= x.second) {
				mergeRunsXY(stack, array, x, y);
				getLastThreeSubarray(stack, x, y, z);
			}
			break;
		}
		else break;
		getLastThreeSubarray(stack, x, y, z);
	}
}

void galopingModeLeft(int* array, int* tmp, int left, int middle, int& i, int j, int& pos_arr) {
	int old_i = i, k = 1, size_tmp = middle - left + 1;
	int deg = pow(2, k), deg_prev = pow(2, k - 1);
	while ((i + deg) < size_tmp && tmp[i + deg_prev] < array[j] && !(array[j] <= tmp[i + deg])) {
		deg = pow(2, k);
		deg_prev = pow(2, k - 1);
		i += deg_prev;
		k++;
	}
	memcpy(array + left + old_i + j - middle - 1, tmp + old_i, sizeof(int) * (i - old_i + 1));
	pos_arr += i - old_i;
}

void galopingModeRight(int* array, int* tmp, int left, int middle, int right, int i, int& j, int& pos_arr) {
	int old_j = j, k = 1;
	int deg = pow(2, k), deg_prev = pow(2, k - 1);
	while ((j + deg) <= right && array[j + deg_prev] <= tmp[i] && !(tmp[i] < array[j + deg])) {
		deg = pow(2, k);
		deg_prev = pow(2, k - 1);
		j += deg_prev;
		k++;
	}
	memmove(array + left + i + old_j - middle - 1, array + old_j, sizeof(int) * (j - old_j + 1));
	pos_arr += j - old_j;
}

void writeFile(int* array, std::string name) {
	std::ofstream file;
	file.open(name);
	if (!file.is_open())
		std::cout << "Error!\n";
	else {
		file << N;
		for (int i = 0; i < N; i++) {
			if (i % minrun == 0) {
				file << "\n";
			}
			file << array[i] << " ";
		}
		file.close();
	}
}

int* readFile(std::string name) {
	std::ifstream file;
	file.open(name);
	if (!file.is_open())
		std::cout << "Error!\n";
	else {
		file >> N;
		int* array = new int[N];
		int i = 0;
		while (!file.eof()) {
			file >> array[i++];
		}
		file.close();
		return array;
	}
	return 0;
}

void printArray(int* array) {
	std::cout << "\nArray:\n";
	for (int i = 0; i < N; i++) {
		std::cout << array[i] << " ";
		//if (i % 20 == 0 && i != 0)
		//	std::cout << "\n";
	}
}

int getMinrun() {
	int r = 0, tmp = N;
	while (tmp >= 64) {
		r |= tmp & 1;
		tmp >>= 1;
	}
	return tmp + r;
}

void insertionSort(int* array, int left, int right) {
	int tmp, j;
	for (int i = left + 1; i <= right; i++) {
		tmp = array[i];
		j = i - 1;
		while (tmp < array[j] && j >= left) {
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = tmp;
	}
}

void mergeArrays(int* array, int left, int middle, int right) {
	//pointers to temporary array and right run
	int i = 0, j = middle + 1;
	//position in current array and size temporary array
	int pos_arr = left, size_tmp = middle - left + 1;
	//temporary array
	int* tmp = new int[size_tmp];
	memcpy(tmp, array + left, sizeof(int) * size_tmp);//copy to temporary array

	//for galoping mode
	bool is_first_arr = false, is_second_arr = false;
	int count = 0;

	while (i < size_tmp && j <= right) {
		if (tmp[i] < array[j]) {
			array[pos_arr] = tmp[i++];
			if (is_first_arr)
				count++;
			else
				count = 0;
			if (count == 7) {
				galopingModeLeft(array, tmp, left, middle, i, j, pos_arr);
				count = 0;
			}
			is_first_arr = true;
			is_second_arr = false;
		}
		else {
			array[pos_arr] = array[j++];
			if (is_second_arr)
				count++;
			else
				count = 0;
			if (count == 7) {
				galopingModeRight(array, tmp, left, middle, right, i, j, pos_arr);
				count = 0;
			}
			is_second_arr = true;
			is_first_arr = false;
		}
		pos_arr++;
	}
	if (j > right) {//copy remaining items
		memcpy(array + left + i + j - middle - 1, tmp + i, sizeof(int) * (size_tmp - i));
	}
	delete[] tmp;
}

void findRun(int* array, int& pos, int& right) {
	int left = pos;
	if (array[pos] <= array[pos + 1] && pos < N - 1) {//increasing sequence
		while (array[pos] <= array[pos + 1] && pos < N - 1) {
			pos++;
		}
	}
	else {
		while (array[pos] > array[pos + 1] && pos < N - 1) {//descending sequence
			pos++;
		}
		for (int i = 0; i < (pos - left + 1) / 2; i++) {//reverse run
			std::swap(array[left + i], array[pos - i]);
		}
	}
	right = pos + 1;
	//if run size is less than minrun, then append to run next items
	while ((right - left + 1 <= minrun) && (right < N)) {
		right++;
	}
	pos = right;
	right--;
}

void mergeRunsXY(myStack*& stack, int* array, TInf x, TInf y) {
	TInf pair;
	mergeArrays(array, y.first, y.first + y.second - 1, x.first + x.second - 1);
	pair.first = y.first;
	pair.second = x.second + y.second;
	for (int i = 0; i < 2; i++)
		popItemStack(stack);
	pushItemStack(stack, pair);
}

void mergeRunsYZ(myStack*& stack, int* array, TInf y, TInf z) {
	TInf pair, tmp;
	mergeArrays(array, z.first, z.first + z.second - 1, y.first + y.second - 1);
	tmp = topItemStack(stack);
	pair.first = z.first;
	pair.second = y.second + z.second;
	for (int i = 0; i < 3; i++)
		popItemStack(stack);

	pushItemStack(stack, pair);
	pushItemStack(stack, tmp);
}