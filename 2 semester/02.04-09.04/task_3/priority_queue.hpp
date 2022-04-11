#pragma once
#include<condition_variable>
#include<mutex>
#include<queue>

template<typename T>
class Priority_queue
{
public:
	using value_type = T;
	using reference = Priority_queue<T>&;
	using const_reference = const Priority_queue<T>&;
	using size_type = std::size_t;
private:
	std::priority_queue<T> m_prior_queue;
	std::condition_variable m_condition_variable;
	mutable std::mutex m_mutex;
public:
	Priority_queue() = default;
	Priority_queue(const_reference);
	reference operator=(const_reference);
	
	const value_type& top() const noexcept;
	bool empty() const noexcept;
	size_type size() const noexcept;
	void push(value_type&&);
	void wait_and_pop();
	bool try_pop();
	void swap(reference) noexcept;
};

template<typename T>
Priority_queue<T>::Priority_queue(const_reference other)
{
	std::lock_guard<std::mutex> lock(other.m_mutex);
	m_prior_queue = other.m_prior_queue;
}

template<typename T>
typename Priority_queue<T>::reference Priority_queue<T>::operator=(const_reference other)
{
	std::scoped_lock lock(m_mutex, other.m_mutex);
	m_prior_queue = other.m_prior_queue;
}

template<typename T>
typename const Priority_queue<T>::value_type& Priority_queue<T>::top() const noexcept
{
	std::lock_guard<std::mutex> lock(m_mutex);
	return m_prior_queue.top();
}

template<typename T>
bool Priority_queue<T>::empty() const noexcept
{
	std::lock_guard<std::mutex> lock(m_mutex);
	return m_prior_queue.empty();
}

template<typename T>
typename Priority_queue<T>::size_type Priority_queue<T>::size() const noexcept
{
	std::lock_guard<std::mutex> lock(m_mutex);
	return m_prior_queue.size();
}

template<typename T>
void Priority_queue<T>::push(T&& value)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	m_prior_queue.push(value);
	m_condition_variable.notify_one();
}

template<typename T>
void Priority_queue<T>::wait_and_pop()
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_condition_variable.wait(lock, [this] {return !m_prior_queue.empty(); });
	m_prior_queue.pop();
}

template<typename T>
bool Priority_queue<T>::try_pop()
{
	std::lock_guard<std::mutex> lock(m_mutex);

	if (m_prior_queue.empty()) return false;

	m_prior_queue.pop();
	return true;
}

template<typename T>
void Priority_queue<T>::swap(reference other) noexcept
{
	std::scoped_lock lock(m_mutex, other.m_mutex);
	m_prior_queue.swap(other);
}
