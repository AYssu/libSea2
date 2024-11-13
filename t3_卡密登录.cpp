#include "include/Sea2.h"

const char* t3_host = ("w.t3yanzheng.com"); //"w.t3yanzheng.com";
const char* t3_base64 = ("LYR+MlEUPkqQ97aJ0BuDXKyGpHsjrvfbCnwthVO5iTFZIxego4Szm/26WN1A8d3c"); //  "bCY/PxYfjrVvtzNIoi4LDzfAKRZTQ7S3dkWvOqwl9Jycnm1p5Ft6uBHr+2EeG8";
const char* t3_key = ("80f939e0121b3963e3913f92552f2fc1"); //"aa199d730b93da766143de1fe640bcb2";
// T3 login/unlink coniguration

const char* t3_login_url = ("/02B54F9E1FDBA628"); // login
const char* t3_unlink_url = ("/76E1E768B0FA4956"); // unlink
int t3_login_code = 200; // login code
int t3_unlink_code = 201; // unlink code

// T3 notice/update configurtion
const char* t3_notice_url = ("/499D930AE737D128"); // notice
const char* t3_update_url = ("/578A36D8184A1D17"); // update
int t3_notice_code = 200; // notice code
int t3_update_version = 902; // update version (1029)  if (1029) < network version then update
int t3_update_code = 200; // update code

const char *kami = "M05261847E467CD2E62008D3C1A9885B";
const char* imei = "808FD6B19A636C69C800103A";

int main(int argc, char const *argv[]) {

    t3_json json;
    shttp::t3_login(json,kami,imei);

    if (json.status!=1)
    {
        std::cout << "[-]登录失败: " << json.msg << std::endl;
        return 0;
    }
    std::cout << "[+]所有数据: " << json.all_data << std::endl;
  
    return 0;
}