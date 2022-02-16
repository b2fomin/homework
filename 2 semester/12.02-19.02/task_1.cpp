#include<iostream>
#include<vector>

int main()
{
	std::vector<int> arr{ 1,1,1 };
	std::cout << "Capacity is " << arr.capacity() << std::endl;
	// При инициализации capacity=size

	arr.reserve(10);
	std::cout << "Manually changed capacity is " << arr.capacity() << std::endl;
	// С помощью команды reserve вручную изменятся выделяемая память на величину, указанную в скобках.

	int old_capacity = arr.capacity();

	while (true)
	{
		arr.push_back(1);
		if (old_capacity != arr.capacity())
		{
			std::cout << "Auto changed capacity is " << arr.capacity() << std::endl;
			old_capacity = arr.capacity();
			// Можно заметить, что количество памяти, выделенное на следующем шаге, в 1.5 раза
			// больше, чем на предыдущем. В случае нехватки памяти в системе выбрасывается
			// исключение std::bad_alloc.
		}
	}

	return 0;
}