#include<iostream>
#include<vector>

int main()
{
	std::vector<int> arr{ 1,1,1 };
	std::cout << "Capacity is " << arr.capacity() << std::endl;
	// ��� ������������� capacity=size

	arr.reserve(10);
	std::cout << "Manually changed capacity is " << arr.capacity() << std::endl;
	// � ������� ������� reserve ������� ��������� ���������� ������ �� ��������, ��������� � �������.

	int old_capacity = arr.capacity();

	while (true)
	{
		arr.push_back(1);
		if (old_capacity != arr.capacity())
		{
			std::cout << "Auto changed capacity is " << arr.capacity() << std::endl;
			old_capacity = arr.capacity();
			// ����� ��������, ��� ���������� ������, ���������� �� ��������� ����, � 1.5 ����
			// ������, ��� �� ����������. � ������ �������� ������ � ������� �������������
			// ���������� std::bad_alloc.
		}
	}

	return 0;
}