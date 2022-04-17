#define BOOST_DATE_TIME_NO_LIB

#include<boost/interprocess/managed_shared_memory.hpp>
#include<boost/interprocess/containers/vector.hpp>
#include<boost/interprocess/containers/string.hpp>
#include<boost/interprocess/allocators/allocator.hpp>
#include<string>

int main()
{
	using segment_manager_t = boost::interprocess::managed_shared_memory::segment_manager;
	using char_allocator = boost::interprocess::allocator<char, segment_manager_t>;
	using char_string = boost::interprocess::basic_string<char, std::char_traits<char>, char_allocator>;
	using value_allocator = boost::interprocess::allocator<char_string, segment_manager_t>;
	using value_type = std::vector<char_string, value_allocator>;
	using allocator = boost::interprocess::allocator<value_type, segment_manager_t>;
	using shared_vector = boost::interprocess::vector<value_type, allocator>;

	constexpr std::size_t memory_size = 1024;
	const std::string memory_name = "shared_memory";

	boost::interprocess::shared_memory_object::remove(memory_name.c_str());
	boost::interprocess::managed_shared_memory shared_memory(
	boost::interprocess::create_only, memory_name.c_str(), memory_size);

	shared_vector* messages = shared_memory.construct<shared_vector>("messages")
		(shared_memory.get_segment_manager());

	int* number_of_programs = shared_memory.construct<int>("number_of_programs")(0);
	auto input_somewhere = shared_memory.construct<bool>("input_somewhere")(false);

	system("pause");

	boost::interprocess::shared_memory_object::remove(memory_name.c_str());

	return 0;
}