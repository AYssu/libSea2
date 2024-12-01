#include "include/json.hpp"
#include "include/Sea2.h"

const char *hotfix_host = "test2.ayial.love";//project host
const char *hotfix_key = "1fl1yly2r1bibflo3g2jo5abus0huedv";//project key
const char *hotfix_base64 = "164pqrGF3bZwMfh/Ty29j7KHVnsxJDlX8EBegWC5+OzRuiNSmaPt0QLIkUYAdcov";//project base64
const char *hotfix_id = "1825143064403021825";//project id

std::string hotfix_update_version = "1001";
int hotfix_bind_code = 200;//bind code
int hotfix_unbind_code = 202;//unbind code
int hotfix_notice_code = 303;//unbind code
int hotfix_update_code = 404;//update code
int hotfix_variable_code = 444;//variable code

const char *kami = "8TDUOUCYL5GVD2G19CG2JBVZ0LRJ4IVT";
const char *imei = "Y3702941508FD6B19A636C69C800103A";

int main(int argc, char const *argv[]) {

    hotfix_json json;
    shttp::hotfix_update(json);

    if (json.status!=1)
    {
        std::cout << "[-]获取更新失败: " << json.msg << std::endl;
        return 0;
    }

    if (json.net_version == hotfix_update_version)
    {
        std::cout << "[-]当前已是最新版本!" << std::endl;
        return {};
    }
    if (!json.update_must)
    {
        std::cout << "[-]当前不强制更新!" << std::endl;
        std::cout << "[-]最新更新公告:" << json.update_message << std::endl;
        return {};
    }

    std::cout << "[-]当前强制更新!" << std::endl;
    std::cout << "[-]最新更新公告:" << json.update_message << std::endl;
    std::cout << "[-]最新更新链接:" << json.update_url << std::endl;
    return 0;
}