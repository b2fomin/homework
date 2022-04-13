#define BOOST_DATE_TIME_NO_LIB

#include<boost/interprocess/managed_shared_memory.hpp>
#include<boost/interprocess/containers/map.hpp>
#include<boost/interprocess/allocators/allocator.hpp>
#include<string>

int main()
{

	using value_type = std::pair<const std::string, std::string>;
	using allocator = boost::interprocess::allocator<value_type,
		boost::interprocess::managed_shared_memory::segment_manager>;
	using My_map = boost::interprocess::map<std::string, std::string,
		std::less<std::string>, allocator>;

	const std::size_t memory_size = 1024;
	const std::string memory_name = "shared_memory";

	boost::interprocess::shared_memory_object::remove(memory_name.c_str());
	boost::interprocess::managed_shared_memory shared_memory(
	boost::interprocess::create_only, memory_name.c_str(), memory_size);

	My_map* messages = shared_memory.construct<My_map>("messages")
		(std::less<std::string>(), shared_memory.get_segment_manager());

	system("pause");

	boost::interprocess::shared_memory_object::remove(memory_name.c_str());

	return 0;
}