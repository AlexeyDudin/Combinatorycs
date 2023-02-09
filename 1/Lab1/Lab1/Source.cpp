#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>

std::chrono::time_point<std::chrono::system_clock> m_StartTime;
std::chrono::time_point<std::chrono::system_clock> m_EndTime;
bool m_bRunning = false;

void start()
{
	m_StartTime = std::chrono::system_clock::now();
	m_bRunning = true;
}

void stop()
{
	m_EndTime = std::chrono::system_clock::now();
	m_bRunning = false;
}

double elapsedMilliseconds()
{
	std::chrono::time_point<std::chrono::system_clock> endTime;

	if (m_bRunning)
	{
		endTime = std::chrono::system_clock::now();
	}
	else
	{
		endTime = m_EndTime;
	}

	return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
}

int main()
{
	std::vector<size_t> v = { 7, 1, 12, 5, 9, 20, 15 };
	start();
	std::sort(v.begin(), v.end());
	do
	{
		copy(v.begin(), v.end(), std::ostream_iterator<size_t>(std::cout, " "));
		std::cout << std::endl;
	} while (std::next_permutation(v.begin(), v.end()));
	double duration = elapsedMilliseconds();

	std::cout << duration << " ms." << std::endl;
	system("pause");
	return 0;
}
