#include <Sea2.h>
#include <json.hpp>
#include <smust.h> // 务必注册账号并添加相应的接口和配置 官网 http://www.easyverify.top
using namespace sutils;
using json = nlohmann::json;

struct variable_struct {
    uintptr_t 矩阵头;
    std::vector<uintptr_t> 对象数组;
    std::vector<int> 载具ID;
    long 子弹防抖;
    int 开镜值;
    float 某个修改值;
    bool 某个功能开关;
};


int main(int argc, char** argv)
{
    std::cout << "-- 测试变量" << std::endl;

    variable_struct struct_data = {};
   
    sverify::verify_json json3 = {}; // 清空结构体数据
    // NOLINTNEXTLINE
    memset(&json3, 0, sizeof(sverify::verify_json));
    sverify::get_variables(json3);
    if (json3.success) {
        json response = json::parse(json3.variables);
        auto success = response["success"].is_null()?false:response["success"].get<bool>();
        if(success) {
            auto data = response["PUBG2"];
            string_to_uintptr(struct_data.矩阵头,data["矩阵头"].get<std::string>());
            string_to_long(struct_data.子弹防抖,data["子弹防抖"].get<std::string>());
            string_load_vector(struct_data.对象数组,data["对象数组"].get<std::string>());
            string_load_vector(struct_data.载具ID,data["载具ID"].get<std::string>());
            struct_data.开镜值 = data["开镜值"].get<int>();
            struct_data.某个修改值 = data["某个修改值"].get<float>();
            struct_data.某个功能开关 = data["某个功能开关"].get<bool>();

            std::cout << "变量解析成功--打印" << std::endl;
            std::cout << "矩阵头: 0x" << std::hex << std::uppercase << struct_data.矩阵头 << std::dec <<  std::endl;
            std::cout << "子弹防抖: " << struct_data.子弹防抖 << std::endl; // 默认输出10进制
            std::cout << "开镜值: " << struct_data.开镜值 << std::endl;
            std::cout << "对象数组: ";
            for (auto &i : struct_data.对象数组) {
                std::cout << "0x" << std::hex << std::uppercase << i << " ";
            }
            std::cout << std::dec << std::endl;
            std::cout << "载具ID: ";
            for (auto &i : struct_data.载具ID) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
            std::cout << "某个修改值: " << struct_data.某个修改值 << std::endl;
            std::cout << "某个功能开关：" << (struct_data.某个功能开关?"开启":"关闭") << std::endl;            
        }else {
            std::cout << "变量解析失败" << std::endl;
        }

    } else {
        std::cout << "获取变量失败: " << json3.error_message << std::endl;
    }
    std::cout << "请求状态码: " << json3.status_code << std::endl;

   
    return 0;
}