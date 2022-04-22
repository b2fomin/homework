#pragma once
#include<queue>
#include<condition_variable>
#include<mutex>

template<typename T>
class tsqueue
{
private:
	std::queue<T> m_queue;
	std::condition_variable m_cond;
	mutable std::mutex m_mutex;
public:
	tsqueue() = default;
	~tsqueue() = default;
	tsqueue(const tsqueue&);
	tsqueue& operator=(const tsqueue&) = delete;
public:
	bool empty()
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		return m_queue.empty();
	}

	void push(T value)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_queue.push(value);
		m_cond.notify_one();
	}

	template<typename... Args>
	void emplace(Args... args)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_queue.emplace(args...);
		m_cond.notify_one();
	}

	bool pop()
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		if (m_queue.empty()) return false;
		m_queue.pop();
		return true;
	}

	const T front()
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		return m_queue.front();
	}

	void clear()
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		while(!m_queue.empty()) m_queue.pop();
	}

	void wait()
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_cond.wait(lock, [this] {return !m_queue.empty(); });
	}

};