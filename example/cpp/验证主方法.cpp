#include <Sea2.h>
#include <smust.h> // 务必注册账号并添加相应的接口和配置 官网 http://www.easyverify.top
using namespace sutils;

void function_core()
{
	std::cout << s_yellow << "我是核心方法" << std::endl;
}
int main(int argc, char** argv)
{

    method_map.insert({ "main", function_core});

    sverify::init_method(); //尝试没登录调用
    std::cout << "-- 测试单码卡密绑定" << std::endl;
    sverify::verify_json json4 = {}; // 清空结构体数据
    // NOLINTNEXTLINE
    memset(&json4, 0, sizeof(sverify::verify_json));
    sverify::bind_card("1ZCNK502B97GM348JLXVH6", get_imei(3), json4);
    if (json4.success) {
       
        std::cout << "到期时间: " << json4.end_time << std::endl;
      
    } else {
        std::cout << "绑定卡密失败: " << json4.error_message << std::endl;
    }
    sverify::init_method(); //登录后调用
    return 0;
}