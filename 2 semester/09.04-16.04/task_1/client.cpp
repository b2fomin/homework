#define BOOST_DATE_TIME_NO_LIB

#include<boost/interprocess/managed_shared_memory.hpp>
#include<boost/interprocess/containers/vector.hpp>
#include<boost/interprocess/containers/string.hpp>
#include<boost/interprocess/allocators/allocator.hpp>
#include<boost/interprocess/sync/interprocess_mutex.hpp>
#include<boost/interprocess/sync/interprocess_condition.hpp>
#include<boost/functional/hash.hpp>

#include<string>
#include<iostream>
#include<conio.h>
#include<mutex>

using segment_manager_t = boost::interprocess::managed_shared_memory::segment_manager;
using char_allocator = boost::interprocess::allocator<char, segment_manager_t>;
using char_string = boost::interprocess::basic_string<char, std::char_traits<char>, char_allocator>;
using value_allocator = boost::interprocess::allocator<char_string, segment_manager_t>;
using value_type = std::vector<char_string, value_allocator>;
using allocator = boost::interprocess::allocator<value_type, segment_manager_t>;
using My_vector = boost::interprocess::vector<value_type, allocator>;

char_string get_id(char_string string, boost::interprocess::managed_shared_memory& shared_memory)
{
	std::size_t seed = 0;
	boost::hash_combine(seed, string);
	auto string_seed = std::to_string(seed);

	char_string result(shared_memory.get_segment_manager());
	for (auto& elem : string_seed) result += elem;

	return result;
}

int main()
{

	const std::string memory_name = "shared_memory";

	boost::interprocess::managed_shared_memory shared_memory(boost::interprocess::open_only, memory_name.c_str());
	
	auto number_of_programs = shared_memory.find<int>("number_of_programs").first;
	++*number_of_programs;

	const std::string mutex_name = "mutex"+std::to_string(*number_of_programs);
	const std::string condition_name = "condition";

	auto mutex = shared_memory.construct<boost::interprocess::interprocess_mutex>(mutex_name.c_str())();
	auto condition = shared_memory.find_or_construct<boost::interprocess::interprocess_condition>(condition_name.c_str())();
	auto input_somewhere = shared_memory.find<bool>("input_somewhere").first;

	auto messages = shared_memory.find<My_vector>("messages").first;

	for (auto& message : *messages) std::cout << "id: " << message[0]<< "\tmessage: " << message[1] << std::endl;

	while (true)
	{
		mutex->lock();
		while(!*input_somewhere && !_kbhit());
		*input_somewhere = true;
		mutex->unlock();

		if (*input_somewhere && _kbhit())
		{
			std::string string;
			char_string message(shared_memory.get_segment_manager());
			std::getline(std::cin, string);
			for(char& elem : string) message += elem;

			char_string id(get_id(message, shared_memory), shared_memory.get_segment_manager());

			value_type message_with_id({ id, message }, shared_memory.get_segment_manager());

			std::lock_guard<boost::interprocess::interprocess_mutex> lock(*mutex);
			messages->push_back(message_with_id);

			*input_somewhere = false;
			condition->notify_all();
		}
		else
		{
			std::unique_lock<boost::interprocess::interprocess_mutex> lock(*mutex);
			condition->wait(lock, [&messages, &input_somewhere] {return !messages->empty() && !*input_somewhere; });
			std::cout << (*messages)[messages->size() - 1][1] << std::endl;
		}
	}
	return 0;
}