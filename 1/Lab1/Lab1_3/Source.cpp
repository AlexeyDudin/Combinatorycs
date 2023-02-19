#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>


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

bool VectorContains(std::vector<int> positions, int value)
{
	for (int i = 0; i < positions.size(); i++)
	{
		if (positions[i] == value)
		{
			return true;
		}
	}
	return false;
}

int main()
{
	std::vector<int> v = {1, 2, 3, 4, 5, 6};
	std::vector<int> result(v.size());
	std::vector<int> positions;
	std::srand(std::time(nullptr));

	start();
	std::cout << "Start vector: ";
	copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
	while (positions.size() != v.size())
	{
		int random_variable;
		do
		{
			random_variable = std::rand() % v.size();
		} while (VectorContains(positions, random_variable));
		positions.push_back(random_variable);
	}

	for (int i = 0; i < positions.size(); i++)
	{
		result[positions[i]] = v[i];
	}

	std::cout << "Result vector: ";
	copy(result.begin(), result.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
	stop();

	std::cout << elapsedMilliseconds() << " ms." << std::endl;
	system("pause");
	return 0;
}