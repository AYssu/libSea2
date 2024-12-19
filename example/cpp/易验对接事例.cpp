#include <Sea2.h>
#include <smust.h> // 务必注册账号并添加相应的接口和配置 官网 http://www.easyverify.top
using namespace sutils;
int main(int argc, char** argv)
{

    std::cout << "-- 测试公告" << std::endl;
    sverify::verify_json json = {}; // 清空结构体数据
    // NOLINTNEXTLINE
    memset(&json, 0, sizeof(sverify::verify_json));
    sverify::get_notice(json);
    if (json.success) {
        std::cout << "获取到的公告: " << json.notice << std::endl;
        std::cout << "服务器时间戳:" << json.timestamp << std::endl;

    } else {
        std::cout << "获取公告失败: " << json.error_message << std::endl;
    }
    std::cout << "请求状态码: " << json.status_code << std::endl;

    std::cout << "-- 测试更新" << std::endl;
    sverify::verify_json json2 = {}; // 清空结构体数据
    // NOLINTNEXTLINE
    memset(&json2, 0, sizeof(sverify::verify_json));
    sverify::get_update(json2);
    if (json2.success) {
        if (json2.have_update) {
            std::cout << "是否强制更新: " << json2.update_must << std::endl;
            std::cout << "更新公告: " << json2.update_message << std::endl;
            std::cout << "更新链接: " << json2.update_url << std::endl;
        } else {
            std::cout << "当前最新版本，公告(更新增强): " << json2.notice << std::endl;
        }
    } else {
        std::cout << "获取更新失败: " << json2.error_message << std::endl;
    }
    std::cout << "请求状态码: " << json2.status_code << std::endl;

    std::cout << "-- 测试变量" << std::endl;
    sverify::verify_json json3 = {}; // 清空结构体数据
    // NOLINTNEXTLINE
    memset(&json3, 0, sizeof(sverify::verify_json));
    sverify::get_variables(json3);
    if (json3.success) {
        std::cout << "获取到的变量: " << json3.variables << std::endl;
        std::cout << "服务器时间戳:" << json3.timestamp << std::endl;

    } else {
        std::cout << "获取变量失败: " << json3.error_message << std::endl;
    }
    std::cout << "请求状态码: " << json3.status_code << std::endl;

    std::cout << "-- 测试单码卡密绑定" << std::endl;
    sverify::verify_json json4 = {}; // 清空结构体数据
    // NOLINTNEXTLINE
    memset(&json4, 0, sizeof(sverify::verify_json));
    sverify::bind_card("1ZCNK502B97GM348JLXVH6", get_imei(3), json4);
    if (json4.success) {
        std::cout << "卡密ID: " << json4.card_id << std::endl;
        std::cout << "到期时间: " << json4.end_time << std::endl;
        std::cout << "到期时间戳: " << json4.available << std::endl;
        std::cout << "卡密类型: " << json4.card_type << std::endl;
        std::cout << "绑定次数: " << json4.bind_number << std::endl;
        std::cout << "解绑次数: " << json4.unbind_number << std::endl;
        std::cout << "核心数据: " << json4.core << std::endl;
        std::cout << "程序变量: " << json4.variables << std::endl;
    } else {
        std::cout << "绑定卡密失败: " << json4.error_message << std::endl;
    }
    std::cout << "请求状态码: " << json4.status_code << std::endl;

    std::cout << "-- 测试单码卡密换绑" << std::endl;
    sverify::verify_json json5 = {}; // 清空结构体数据
    // NOLINTNEXTLINE
    memset(&json5, 0, sizeof(sverify::verify_json));
    sverify::unbind_card("1ZCNK502B97GM348JLXVH6", get_imei(3), json5);
    if (json5.success) {
        std::cout << "换绑成功: 换绑成功" << std::endl;
    } else {
        std::cout << "换绑失败: " << json5.error_message << std::endl;
    }
    std::cout << "请求状态码: " << json5.status_code << std::endl;

    return 0;
}