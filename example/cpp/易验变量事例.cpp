#include <Sea2.h>
#include <json.hpp>
#include <smust.h> // 务必注册账号并添加相应的接口和配置 官网 http://www.easyverify.top
using namespace sutils;
using json = nlohmann::json;
int main(int argc, char** argv)
{
    std::cout << "-- 测试变量" << std::endl;
    sverify::verify_json json3 = {}; // 清空结构体数据
    // NOLINTNEXTLINE
    memset(&json3, 0, sizeof(sverify::verify_json));
    sverify::get_variables(json3);
    if (json3.success) {
        std::cout << "获取到的变量: " << json3.variables << std::endl;
        std::cout << "服务器时间戳:" << json3.timestamp << std::endl;
        json response = json::parse(json3.variables);
        // 最好这边使用try做一下异常处理 这边只是最简单的例子
        auto str = response["字符串示例"].get<std::string>();
        auto i = response["int"].get<int>();
        auto f = response["float"].get<float>();
        auto b = response["bool"].get<bool>(); //打印0/1 bool本质也就是0/1
        // 键值对嘛 这个json库百度一下就知道怎么用了
        // json最牛逼的那就是套娃 自行理解
        std::cout << "从json获取的字符串: " << str << std::endl;
        std::cout << "从json获取的int: " << i << std::endl;
        std::cout << "从json获取的float: " << f << std::endl;
        std::cout << "从json获取的bool: " << b << std::endl;
        

    } else {
        std::cout << "获取变量失败: " << json3.error_message << std::endl;
    }
    std::cout << "请求状态码: " << json3.status_code << std::endl;

   
    return 0;
}