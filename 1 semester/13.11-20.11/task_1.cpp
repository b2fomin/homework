#include<iostream>
#include<type_traits>
#include<functional>

template<typename NotFunction>
struct is_function : std::false_type
{};

template<typename Return, typename... Args>
struct is_function<std::function<Return(Args...)>> : std::true_type
{};

int main()
{
	std::cout << std::boolalpha << is_function<int>::value << std::endl << is_function<std::function<int(int, int, double, int)>>::value;
	return 0;
}