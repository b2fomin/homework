template<bool Condition, typename T>
struct enable_if;

template<typename T>
struct enable_if<true, T>
{
	using type = T;
};

template<typename T>
struct enable_if<false, T>
{
	class X{};
	using type = typename X::type;
};

template<bool Condition, typename T>
using enable_if_t = typename enable_if<Condition, T>::type;
