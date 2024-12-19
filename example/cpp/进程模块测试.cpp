#include <Sea2.h>
#include <smust.h> // 请放到main方法上面 只能被引用一次 里面是包含内存静态库的必要声明

int main(int argc, char** argv)
{
    auto pid = smemory::initalize_by_game_package_return_pid("com.pubg.newstate"); // initalize by game package

    auto base = smemory::get_module_base_pro("libUE4.so:bss", 1, "rw");
    printf("进程pid: %d 模块: %lx\n", pid, base);
    return 0;
}