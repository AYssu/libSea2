#include <Sea2.h>
#include <iostream>

#include <thread>
#include <smust.h> // 务必注册账号并添加相应的接口和配置 官网 http://www.easyverify.top
using namespace sutils;
int main(int argc, char** argv)
{

    //单码心跳只有付费模式可用 
    std::cout << "-- 测试单码卡密绑定" << std::endl;
    sverify::verify_json json4 = {}; // 清空结构体数据
    // NOLINTNEXTLINE
    memset(&json4, 0, sizeof(sverify::verify_json));
    sverify::bind_card("1ZCNK502B97GM348JLXVH6", get_imei(3), json4);
    if (json4.success) {
        std::cout << "卡密ID: " << json4.card_id << std::endl;
        std::cout << "到期时间: " << json4.end_time << std::endl;
           auto error = 0;

        sverify::verify_json json = {};// 清空结构体数据
        while (error <= 3) {
            memset(&json, 0, sizeof(sverify::verify_json));
            sverify::heart_beat(std::to_string(json4.card_id), get_imei(3), json4.token, json);
            if (json.success && json.status_code == 200) {
                std::cout << "心跳验证成功！" << std::endl;
            } else {
                error++;
                std::cout << "心跳验证失败: " << error << std::endl;
            }
            // 30秒一次心跳 请勿快速心跳 轻则拉黑用户IP,多次出现拉黑情况直接封程序
            std::this_thread::sleep_for(std::chrono::seconds(30));
        }
        std::cout << "心跳验证失败! 退出程序" << std::endl;
        exit(0);
    } else {
        std::cout << "绑定卡密失败: " << json4.error_message << std::endl;
    }
   
    return 0;
}