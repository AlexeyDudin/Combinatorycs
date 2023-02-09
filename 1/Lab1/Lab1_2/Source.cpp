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

std::vector<int> FillDirection(int sizeOfVector)
{
	std::vector<int> result;
	for (int i = 0; i < sizeOfVector; i++)
	{
		if (i == 0)
			result.push_back(0);
		else
			result.push_back(-1);
	}
	return result;
}

bool CanMove(std::vector<size_t> v, std::vector<int> direction, int id, bool includeZero = true, int prevId = -1)
{
	if ((id == 0 && direction[id] == -1) || (id == v.size() - 1 && direction[id] == 1) || (includeZero && direction[id] == 0))
		return false;
	if (direction[id] == -1 && v[id] < v[id - 1])
		return false;
	if (direction[id] == 1 && v[id] < v[id + 1])
		return false;
	/*if (direction[id] == -1 && (prevId == -1 || (id - prevId != direction[prevId])))
		return CanMove(v, direction, id - 1, false, id);
	if (direction[id] == 1 && (prevId == -1 || (id - prevId != direction[prevId])))
		return CanMove(v, direction, id + 1, false, id);*/
	/*if (direction[id] == -1 && v[id] > v[id - 1])
		return false;
	if (direction[id] == 1 && v[id] < v[id + 1])
		return false;*/
	return true;
}

int main()
{
	std::vector<size_t> v = { 7, 1, 12, 5, 9, 20, 15 };
	std::sort(v.begin(), v.end());
	std::vector<size_t> p = v;
	std::vector<int> direction = FillDirection(v.size());

	int id;
	start();
	while (true)
	{
		copy(v.begin(), v.end(), std::ostream_iterator<size_t>(std::cout, " "));
		std::cout << std::endl;
		id = -1;
		for (int i = 0; i < v.size(); i++)
		{
			if (CanMove(v, direction, i) && ((id == -1) || (v[i] > v[id])))
			{
				id = i;
			}

		}
		if (id == -1)
			break;
		for (int i = 0; i < v.size(); i++)
		{
			if (v[i] > v[id])
				direction[i] = -direction[i];
		}

		if (direction[id] == -1)
		{
			size_t tmp = v[id - 1];
			v[id - 1] = v[id];
			v[id] = tmp;

			int t = direction[id - 1];
			direction[id - 1] = direction[id];
			direction[id] = t;
		}
		else if (direction[id] == 1)
		{
			size_t tmp = v[id + 1];
			v[id + 1] = v[id];
			v[id] = tmp;

			int t = direction[id + 1];
			direction[id + 1] = direction[id];
			direction[id] = t;
		}
	}
	stop();
	std::cout << elapsedMilliseconds() << " ms." << std::endl;
	system("pause");
	return 0;
}