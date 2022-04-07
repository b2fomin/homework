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
	
};

template<typename T>
Priority_queue<T>::Priority_queue(const_reference other)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	m_prior_queue = other.m_prior_queue;
}

template<typename T>
typename Priority_queue<T>::reference Priority_queue<T>::operator=(const_reference other)
{
	std::scoped_lock lock(m_mutex, other.m_mutex);
	m_prior_queue = other.m_prior_queue;
}
