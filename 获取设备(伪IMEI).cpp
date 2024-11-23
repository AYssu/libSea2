#include "include/Sea2.h"


int main()
{
    auto imei = sutils::get_imei();
	printf("当前手机 IMEI: %s\n",imei.c_str());
	return 0;
}