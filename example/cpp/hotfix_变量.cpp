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

const char *kami = "8TDUOUCYL5GVD2G19CG2JBVZ0LRJ4IVT";
const char *imei = "Y3702941508FD6B19A636C69C800103A";

int main(int argc, char const *argv[]) {

    hotfix_json json;
    shttp::hotfix_variable(json);

    if (json.status!=1)
    {
        std::cout << "[-]变量获取失败: " << json.msg << std::endl;
        return 0;
    }

    std::vector<uintptr_t> 测试列表;

   
    std::cout << "[+]变量列表:" << json.variables << std::endl;
    auto json_data = nlohmann::ordered_json::parse(json.variables);
    auto 测试_string = json_data["指针"].get<std::string>();
    auto 测试2_string = json_data["偏移"].get<std::string>();
    shttp::string_load_vector(测试列表,测试_string);
    
    for (auto data:测试列表)
    {
    	printf("指针集 %lx \n",data);
    }
    auto 测试2 = shttp::hexStringToLong(测试2_string);
    printf("偏移 %lx",测试2);
    
    
    return 0;
}