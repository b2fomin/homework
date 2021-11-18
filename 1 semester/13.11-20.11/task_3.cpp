#include<functional>

template<typename T>
struct decay;

template<typename Return, typename... Args>
struct decay<const std::function<Return(Args...)>>
{
	using type = std::function<Return(Args...)>*;
};

template<typename T>
struct decay<T[]>
{
	using type = T*;
};

template<typename T, std::size_t N>
struct decay<T[N]>
{
	using type = T*;
};