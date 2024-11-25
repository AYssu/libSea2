#include "include/Sea2.h"

int main()
{
    auto imei = sutils::get_imei();
	printf("imei: %s",imei.c_str());
	return 0;
}