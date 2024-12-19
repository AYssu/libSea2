#ifndef SEA2_SEA2_H
#define SEA2_SEA2_H
#pragma once
#include <arpa/inet.h>
#include <cerrno>
#include <chrono>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <type_traits>
#include <unistd.h>
#include <unordered_map>
#include <vector>

// some color for you color your termux
#define s_black "\033[1;30m"
#define s_dark_gray "\033[1;30m"
#define s_blue "\033[1;34m"
#define s_light_blue "\033[1;34m"
#define s_green "\033[1;32m"
#define s_light_green "\033[1;32m"
#define s_cyan "\033[1;36m"
#define s_light_cyan "\033[1;36m"
#define s_red "\033[1;31m"
#define s_light_red "\033[1;31m"
#define s_purple "\033[1;35m"
#define s_light_purple "\033[1;35m"
#define s_brown "\033[1;33m"
#define s_yellow "\033[1;33m"
#define s_white "\033[1;37m"

namespace shttp {

struct http_response {
    bool success; // true if the request was successful, false otherwise
    long code; // the HTTP status code
    std::string data; // the response data
    std::string error; // the error message
};
// example usage: http_xxx("你的域名,可带https://头也可不带","请求参数","自定义请求头,自行了解规范",true/*就使用https了需要服务器支持*/,true/*是否打印错误日志*/);
http_response http_get(const std::string& url, const std::string& header = "Content-Type: application/x-www-form-urlencoded", bool log = false); // send a GET request to the specified URL and return the response

http_response http_post(const std::string& url, const std::string& params = "", const std::string& header = "Content-Type: application/x-www-form-urlencoded", bool log = false); // send a GET request to the specified URL and return the response

} // namespace shttp

namespace sverify {

struct verify_json {
    bool success; // 是否成功

    bool have_update; // 是否有更新
    long status_code; // 本次网络请求的状态码 常见200成功 401认证失败 302重定向
    long available; // 剩余可用时间秒

    int card_id; //卡密ID
    int unbind_number; //解绑次数
    int bind_number; //绑定次数
    std::string end_time; // 到期时间
    std::string card_type; // 卡类型
    std::string notice; // 获取的公告
    std::string variables; // 获取的变量
    std::string core; //核心数据

    std::string update_url; // 更新链接
    std::string update_message; // 更新信息
    bool update_must; // 是否强制更新
    time_t timestamp; // 服务器时间戳
    std::string error_message; // 失败的错误信息
};

bool get_notice(verify_json& json, bool log = false); // 获取程序公告
bool get_update(verify_json& json, bool log = false); // 获取程序更新信息
bool get_variables(verify_json& json, bool log = false); // 获取程序变量
bool bind_card(const std::string& kami_, const std::string& imei_, sverify::verify_json& json_, bool log = false); // 单码卡密绑定
bool unbind_card(const std::string& kami_, const std::string& imei_, sverify::verify_json& json_, bool log = false); // 单码卡密换绑

}

namespace sutils {

time_t get_timestamp(); // get timestamp

std::string base64_encode(const std::string& input, const std::string& base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"); // base64 encode
std::string base64_decode(const std::string& input, const std::string& base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"); // base64 decode

std::string obfuscator(const std::string& origin, const std::string& key = "."); // obfuscator string

std::string to_hex(const std::string& origin, bool uppercase = false); // hex
std::string hex_to_string(const std::string& origin); // hex

std::string to_md5(const std::string& origin, bool uppercase = false); // md5
std::string sha256(const std::string& input, bool uppercase = false); // SHA-256

std::string pem_format(const std::string& key, bool private_ = false); // pem format
std::string rsa_public_encrypt(const std::string& clear_text, const std::string& pub_key); // rsa encrypt
std::string rsa_private_decrypt(const std::string& cipher_text, const std::string& pri_key); // rsa decrypt
std::string rsa_public_decrypt(const std::string& cipher_text, const std::string& pub_key); // rsa decrypt
std::string rsa_private_encrypt(const std::string& clear_text, const std::string& pri_key); // rsa encrypt

std::string execute_shell_command(const std::string& command); // execute shell command return
std::string get_imei(int result = 1, bool log = false); // result: 1:默认hex->md5 2.hex->sha256 3.base64 log:是否打印日志
} // namespace utils

namespace smmap {
struct MappedMemory {
    void* ptr;
    size_t size;
    MappedMemory(void* p, size_t s)
        : ptr(p)
        , size(s)
    {
    }
    ~MappedMemory()
    {
        if (ptr != MAP_FAILED) {
            munmap(ptr, size);
        }
    }
};
void* build_mmap_void(const char* file_name, bool readonly, size_t msize); // 传统指针
int open_mmapfile(const char* file_name, bool readonly, size_t msize); // 获取文件句柄
std::unique_ptr<MappedMemory> build_mmap(const char* file_name, bool readonly, size_t msize); // 封装mmap函数库
// 支持手动断开 munmap(ptr, size);

} // namespace smmap

namespace smemory {
// this you can use memory methods
bool initalize_by_game_package(const char* package_name); // initalize by game package
pid_t initalize_by_game_package_return_pid(const char* package_name); // initalize by game package

pid_t get_target_pid(); // get target pid
bool set_target_pid(pid_t pid); // set target pid

pid_t get_pid_by_package_name(const char* package_name); // get pid by game package
bool memory_debug(bool debug); // show memory debug infomation

bool is_memory_trap(uintptr_t address); // check if address is memory trap
bool read(uintptr_t address, void* buffer, size_t size); // public read
bool write(uintptr_t address, void* buffer, size_t size); // public write

uintptr_t lsp64(uintptr_t addres); // 64bit jump address
uintptr_t lsp32(uintptr_t addres); // 32bit jump address

float read_float(uintptr_t address); // read float
int read_int(uintptr_t address); // read int
double read_double(uintptr_t address); // read double

float read_float_max(uintptr_t address, float max); // get value set max value
float read_float_min(uintptr_t address, float min); // get value set min value
float read_float_mix(uintptr_t address, float max, float min); // get value set max and min value

int read_int_max(uintptr_t address, int max); // get value set max value
int read_int_min(uintptr_t address, int min); // get value set min value
int read_int_mix(uintptr_t address, int max, int min); // get value set max and min value

double read_double_max(uintptr_t address, double max); // get value set max value
double read_double_min(uintptr_t address, double min); // get value set min value
double read_double_mix(uintptr_t address, double max, double min); // get value set max and min value

long write_float(uintptr_t address, float value); // write float
long write_int(uintptr_t address, int value); // write int
long write_double(uintptr_t address, double value); // write double

uintptr_t get_module_base(const char* module_name); // get module base
uintptr_t get_module_base_pro(const char* module_name, int index); // get module base cb bss if module_name is contains ":bss"
uintptr_t get_module_base_pro(const char* module_name, int index, const char* split); // get module base cb bss if module_name is contains ":bss" and split

uintptr_t read_pointer64(uintptr_t original_address, std::vector<uintptr_t>& vec); // read pointer with offset vector 64bit
uintptr_t read_pointer32(uintptr_t original_address, std::vector<uintptr_t>& vec); // read pointer with offset vector 32bit

void get_buffer(char* buf, uintptr_t address); // read buffer from address to buf

} // namespace smemory
#endif // SEA2_SEA2_H
