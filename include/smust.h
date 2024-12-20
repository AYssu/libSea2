#include <functional>
#include <iostream>
#include <obfuscate.h>
#include <unordered_map>

pid_t target_pid;                                                                                              // 内存插件目标进程pid
std::string read_name;                                                                                         // 自定义读写
std::string write_name;                                                                                        // 自定义读写
std::unordered_map<std::string, std::function<bool(uintptr_t address, void *buffer, size_t size)>> rw_function;// 读写函数

std::string verify_host = OBFUSCATE("http://www.easyverify.top/api");// 域名

std::string verify_project_id = OBFUSCATE("10018");                                                               // 程序PID
std::string verify_project_key = OBFUSCATE("KWN1KBXDE9FA");                                                       //程序密钥
std::string verify_project_base64 = OBFUSCATE("UCPm8YnZsldF1pwVyhoKu3MkAJW2cDREfLSgxqT/iHabN0Qt5z6Ivj4B+OeGX7r9");// base64自定义编码集

std::string verify_project_public_key = OBFUSCATE("MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAw0lDF9vj2o0KdiGeguV9fig+DCf+4WTf6hs5KDw7tFtqDFk9C6giFCP2K5SHNjH/PFYQ/Arn+ccBZwO/5wpz/HzKF41zgoF5gyEV1T1FoqjgC40HO7iXM1WO0ORTS4/T7U1obwHf42pfm4kjBkl/yzngPSdK7aBffI50kLc4gDlRQLffEP3ilKiEJ/HSOqtunadAXWUrnecn0CRdu+gZ1FlfLO7D1qcqaOl4dPtEgn/1tzr77fUMs7rElxaQvbV51R3HTuLz9HZfSg4ZNOqMzEx424T9XTvht0WKisTyhBd/xWUWevwYOMaarHDlJoqU/Hn04ALrrWpTeWAYW0rthQIDAQAB");// rsa公钥

std::string verify_notice_link = OBFUSCATE("MISZX3JLIWZ1");// 获取公告的链接
std::string verify_notice_code = OBFUSCATE("200");         // 获取公告的code

std::string verify_update_link = OBFUSCATE("EH7K9I01FTMJ");// 更新链接
std::string verify_update_version = OBFUSCATE("100");      // 版本号
std::string verify_update_code = OBFUSCATE("200");         // 更新返回code

std::string verify_bind_link = OBFUSCATE("XK28IPSO66A8");// 绑定链接
std::string verify_bind_code = OBFUSCATE("200");         // 绑定返回code

std::string verify_unbind_link = OBFUSCATE("SL19ZU9K9IKE");// 解绑/换绑链接 返回数据无加密 无需设置code

std::string verify_variable_link = OBFUSCATE("9OBL5CHT35OP");// 变量链接
std::string verify_variable_code = OBFUSCATE("200");         // 变量返回code

int verify_encryption = 1;// 默认1 base64 自定义编码集 2 rsa非对称加密