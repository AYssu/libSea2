//#include "include/json.hpp"
#include "include/Sea2.h"


pid_t target_pid=0;
std::string read_name = "syscall_read";

std::string write_name = "syscall_write";

std::unordered_map<std::string ,std::function<bool(uintptr_t address, void *buffer, size_t size)>> rw_function;

int main()
{
	auto pid = smemory::initalize_by_game_package_return_pid("com.pubg.newstate"); // initalize by game package
	
	auto base =smemory::get_module_base_pro("libUE4.so:bss",1,"rw");
	printf("进程pid %d %lx\n",pid,base);
	return 0;
}