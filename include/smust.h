#include <functional>
#include <iostream>
#include <obfuscate.h>
#include <unordered_map>

pid_t target_pid;                                                                                              // 内存插件目标进程pid
std::string read_name;                                                                                         // 自定义读写
std::string write_name;                                                                                        // 自定义读写
std::unordered_map<std::string, std::function<bool(uintptr_t address, void *buffer, size_t size)>> rw_function;// 读写函数

std::string verify_host = OBFUSCATE("https://www.easyverify.top/api");// 域名

std::string verify_project_id = OBFUSCATE("10019");                                                               // 程序PID
std::string verify_project_key = OBFUSCATE("KK7XOGWF62NI");                                                       //程序密钥
std::string verify_project_base64 = OBFUSCATE("");// base64自定义编码集

std::string verify_project_public_key = OBFUSCATE("MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA/SRDhcHRh+yOKair6NeCyXRMZziwW54A/0L0XTa9JN568q9yZD4U4p3Ws93xqOPo6SxUWr32Dy9OB4xNPZJgrJ/lulW3Z2eUwYYNIIKMo6hQQs/UWczEAjLDlj7WbuTe0DpxhOzdAu71zkSe6C11VGiPglGTjwvztEoB5BnDHdpuyX29v4nJXfgbMFsl+d78DmghWc/ImUl1My1OY1KWQXXBeHO4RtaBXLoTk3EGXicp3pO38c0hrzpSGms5HFiPzVfpoJIA1tjpVcVOMc1cSyKDzuz0+tRBh7gHwe+VZsqWR7j56n4K+wVxW1RAvL0cy6B13amr/+OK6ZVWp1AsSwIDAQAB");

std::string verify_notice_link = OBFUSCATE("");// 获取公告的链接
std::string verify_notice_code = OBFUSCATE("");         // 获取公告的code

std::string verify_update_link = OBFUSCATE("MEGC6J9WBWZQ");// 更新链接
std::string verify_update_version = OBFUSCATE("100");      // 版本号
std::string verify_update_code = OBFUSCATE("200");         // 更新返回code

std::string verify_bind_link = OBFUSCATE("N70F11KCWBTV");// 绑定链接
std::string verify_bind_code = OBFUSCATE("200");         // 绑定返回code

std::string verify_unbind_link = OBFUSCATE("");// 解绑/换绑链接 返回数据无加密 无需设置code

std::string verify_variable_link = OBFUSCATE("");// 变量链接
std::string verify_variable_code = OBFUSCATE("");         // 变量返回code

std::string verify_heart_link = OBFUSCATE("") ;// 心跳验证 返回数据无加密 无需设置code

std::string verify_heart_code = OBFUSCATE("");// 心跳返回code



std::string main_method_name = OBFUSCATE("main"); // 主方法
std::unordered_map<std::string ,std::function<void()>> method_map;

int verify_encryption = 2;// 默认1 base64 自定义编码集 2 rsa非对称加密