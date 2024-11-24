#include "include/json.hpp"
#include "include/Sea2.h"

const char *hotfix_host = "www.ayial.love";//project host
const char *hotfix_key = "1fl1yly2r1bibflo3g2jo5abus0huedv";//project key
const char *hotfix_base64 = "164pqrGF3bZwMfh/Ty29j7KHVnsxJDlX8EBegWC5+OzRuiNSmaPt0QLIkUYAdcov";//project base64
const char *hotfix_id = "1825143064403021825";//project id

std::string hotfix_update_version = "1000";
int hotfix_bind_code = 200;//bind code
int hotfix_unbind_code = 202;//unbind code
int hotfix_notice_code = 303;//unbind code
int hotfix_update_code = 404;//update code
int hotfix_variable_code = 444;//variable code


const char *kami = "DDBWIZUMAV3M7B4HU4F8MWL5CUKETN0S";
const char *imei = "abY3702941508FD6B19A636C69C800103A";
int main(int argc, char const *argv[]) {

    hotfix_json json;
    shttp::hotfix_unlink(json,kami,imei);

    
    if (json.status==1)
    {
        std::cout << "[-]解绑失败: " << json.msg << std::endl;
        return 0;
    }
    std::cout << "[+]解绑成功: 成功! " << std::endl;
    return 0;
}