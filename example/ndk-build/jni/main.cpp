#include "../../../include/Sea2.h"

int main(int argc, char **argv)
{
    auto time = sutils::get_timestamp();
    printf("静态库获取时间戳: %ld",time);
	return 0;
}