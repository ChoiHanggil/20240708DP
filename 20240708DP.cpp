#include <iostream>
#include <vector>
#include<map>
#include<string>
#include <algorithm>

// Time Complexity : O(2^n)
// Space Complexity :O(n)
int Fibonacci(int n)
{
	//base case
	if (n <= 2)
	{
		return 1;
	}

	//recurisive case
	return Fibonacci(n - 1) + Fibonacci(n - 2);
}

std::vector<int> Fibonacci2(int n)
{
	std::vector<int> v{ 1,1 };
	for (int i = 2; i < n-1; i++)
	{
		v.push_back(v[i-1] + v[i-2]);
	}
	return v;
}

// Time Complexity : O(n)
// Time Complexity : O(n)
// Memoization(메모이제이션)
//	- 계산된 값은 저장해두었다가 재활용하는 최적화 기법
//	- Recursion + Cache

int64_t Fibonacci_Memo(int n, std::map<int, int64_t>& memo)
{
	//memo
	if (memo.count(n) == 1)
	{
		return memo[n];
	}
	//base case
	if (n <= 2)
	{
		return 1;
	}

	//recurisive case
	memo[n] = Fibonacci_Memo(n - 1, memo) + Fibonacci_Memo(n - 2, memo);
	return memo[n];
}

// M x N 크기의 사각형이 주어졌을 때, 좌상단에서 출발하여 우하단으로 이동하는 모든 경우의 수를 구하세요.(재귀)
//단 오른쪽이나 아래쪽으로만 이동할 수 있다.
// Time Complexity : O(2 ^ (m+n))
// Space Complexity :O(m+n)
int64_t FindWays(int m, int n)
{
	//base case
	if (m == 0 || n == 0)
	{
		return 0;
	}
	if (m == 1 || n == 1)
	{
		return 1;
	}
	//recurisive case
	return FindWays(m - 1, n) + FindWays(m, n - 1);
}

// Time Complexity : O(2 * (m+n)) = O(m+n)
// Space Complexity :O(m+n)
int64_t FindWays_Memo(int m, int n, std::map<std::string, int64_t>& memo)
{
	const std::string key = std::to_string(m) + "," + std::to_string(n);
	if (memo.count(key) == 1)
	{
		return memo[key];
	}
	//base case
	if (m == 0 || n == 0)
	{
		return 0;
	}
	if (m == 1 || n == 1)
	{
		return 1;
	}

	const std::string rKey = std::to_string(n) + "," + std::to_string(m);
	if (memo.count(rKey) == 1)
	{
		return memo[key];
	}
	//recurisive case
	memo[key] = FindWays_Memo(m - 1, n, memo) + FindWays_Memo(m, n - 1, memo);
	return memo[key];
}

//정수의 배열 numbers에서 숫자들을 조합하여 sum을 마나들어 낼 수 있는지 확인하는
//bool CanAccumulation(sum, numbers)를 만들어 보세요.
//단,동일한 원소를 여러번 사용해도 됩니다.
// 원소는 0이 아닙니다. sum은 양수 입니다.
//ex) 8{2,3,5}
//	True
//ex) 8{5,6}
//	False

// Time Complexity : O(n^m)  m = sum, n = numbers.size()
// Space Complexity :O(m)
bool CanAccumulate(int sum, const std::vector<int>& numbers)
{
	if (sum == 0)
	{
		return true;
	}
	if (sum < 0)
	{
		return false;
	}
	
	for (const auto& e : numbers)
	{
		if (CanAccumulate(sum - e, numbers))
		{
			return true;
		}
	}
	return false;
}
// Time Complexity : O(m*n)
// Space Complexity : O(m^2)
bool CanAccumulate_Memo(int sum,const std::vector<int>& numbers, std::map<int, bool>& memo)
{
	if (memo.count(sum) == 1)
	{
		return memo[sum];
	}
	if (sum == 0)
	{
		return true;
	}
	if (sum < 0)
	{
		return false;
	}

	for (const auto& e : numbers)
	{
		if (CanAccumulate_Memo(sum - e, numbers, memo))
		{
			memo[sum] = true;
			return memo[sum];
		}
	}
	memo[sum] = false;
	return memo[sum];
}

//만들어 낼 수 있는 방법을 찾으시오
// Time Complexity : O(m*n)
// Space Complexity : O(m^2)
std::shared_ptr<std::vector<int>> How_Accumulate(int sum, const std::vector<int>& numbers)
{
	if (sum == 0)
	{
		return std::make_shared<std::vector<int>>();
	}
	if (sum < 0)
	{
		return nullptr;
	}

	for (const auto& e : numbers)
	{
		auto ret = How_Accumulate(sum - e, numbers);
		if(ret)// = if (ret != nullptr)
		{
			ret->push_back(e);
			return ret;
		}
	}
	return nullptr;
}

// Time Complexity : O(m*n)
// Space Complexity : O(m^2)
using accum_memo = std::map<int, std::shared_ptr<std::vector<int>>>;
std::shared_ptr<std::vector<int>> HowAccumulate(int sum, const std::vector<int>& numbers, accum_memo& memo)
{
	if (memo.count(sum) == 1)
	{
		return memo[sum];
	}
	if (sum == 0)
	{
		return std::make_shared<std::vector<int>>();
	}
	if (sum < 0)
	{
		return nullptr;
	}

	for (const auto& e : numbers)
	{
		auto ret = HowAccumulate(sum - e, numbers,memo);
		if (ret)// = if (ret != nullptr)
		{
			ret->push_back(e);
			memo[sum] = ret;
			return memo[sum];
		}
	}
	memo[sum] = nullptr;
	return memo[sum];
}

//만들어 낼 수 있는 집합 중 최소 갯수

std::shared_ptr<std::vector<int>> OptimizeAccumulate(int sum, const std::vector<int>& numbers, accum_memo& memo)
{
	if (memo.count(sum) == 1)
	{
		return memo[sum];
	}
	if (sum == 0)
	{
		return std::make_shared<std::vector<int>>();
	}
	if (sum < 0)
	{
		return nullptr;
	}

	std::shared_ptr<std::vector<int>> best = nullptr;
	for (const auto& e : numbers)
	{
		auto ret = OptimizeAccumulate(sum - e, numbers, memo);
		if (ret)
		{
			std::shared_ptr<std::vector<int>> temp = std::make_shared<std::vector<int>>();
			temp->resize(ret->size());
			std::copy(ret->begin(), ret->end(), temp->begin());
			temp->push_back(e);
			if (best == nullptr || temp->size() < best->size())
			{
				best = temp;
			}
		}
	}
	memo[sum] = best;
	return memo[sum];
}

void Print(std::shared_ptr<std::vector<int>> result)
{
	std::cout << "{ ";
	if (result)
	{
		for (auto e : *result)
		{
			std::cout << e << " ";
		}
		std::cout << "} " << std::endl;
	}
	else
	{
		std::cout << "Nullptr" << std::endl;
	}
	
}

int main()
{/*
	std::map<int, int64_t> m;
	for (int i = 1; i < 50; i++)
	{
		std::cout << Fibonacci_Memo(i, m) << " ";
	}
	std::cout << std::endl;
	*/
	/*
	for (const auto e : Fibonacci2(50))
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
	*/

	//std::map<std::string, int64_t> memo;
	//std::cout << FindWays_Memo(30, 30, memo) << std::endl;

	//std::map<int, bool> memo;
	//std::cout << CanAccumulate_Memo(999, {1,2,3,4,5}, memo) << std::endl;

	//Print(How_Accumulate(8, { 2,3,5 }));

	//accum_memo m;
	//Print(HowAccumulate(8, { 2,3,5 }, m));

	accum_memo m;
	Print(OptimizeAccumulate(7, { 1,3,4,5 }, m));


}

//Memoization
//	1. Brete Force
//		a. 문제를 Tree 표현 가능하냐
//		b. 재귀호출
// 
//	2. Dynamic Programming _ Memoization
//		a. 반복되는 패턴
//		b. 저장하고 재활용
// 
//	3. 테스트
//		a. 1과 2의 결과가 같아야 함
//		b. 1의 결과는 대충 정리해 두시는 것이 좋음(TestCase 작성)
// 
//Decision Problem
//	True, false
// 
//Combination Problem
//	어떻게 조합을 만들어 내느냐
// 
//Optimization Problem
//	가장 최선의 조합은 무엇이냐?
// 
//