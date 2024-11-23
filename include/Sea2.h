#ifndef SEA2_SEA2_H
#define SEA2_SEA2_H
#pragma once
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>
#include <memory>
#include <iostream>
#include <type_traits>
#include <iostream>
#include <type_traits>
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <chrono>
#include <cstring>
#include <cstddef>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <cerrno>
#include <memory>
#include <unordered_map>
#include <functional>
struct t3_json {

    int status;// 成功状态码 1 成功 0 失败

    time_t time;// 返回网络时间
    int available;// 单码登录剩余时间 秒

    std::string id;// 卡密ID
    std::string end_time;// 到期时间
    std::string amount;// 卡密类型 3天/7天/一年
    std::string token;// 校验码
    std::string date;// 登录的时间 纯数字
    std::string imei;// 登录成功的卡密
    std::string state_code;// 登录状态码
    std::string change;// 解绑次数
    std::string core;// 核心数据 自动转为16进制 alldate保持10进制
    std::string msg;// 登录失败或卡密解绑等其他提示

    std::string ver;// 版本号
    std::string version;// 版本号
    std::string uplog;// 更新公告
    std::string upurl;// 更新地址

    std::string all_data;// 返回所有数据 用户自定义

};

struct hotfix_json {
    int status;// 成功状态码 1 成功 0 失败

    time_t time;// 服务器时间戳
    long available;// 单码登录剩余时间 秒

    std::string kamiId;// 卡密ID
    std::string endTime;// 到期时间
    std::string bindTime;//绑定时间
    std::string kamiType;// 卡密类型 3天/7天/一年

    int code;// 登录状态码
    int unBindNumber;// 解绑次数
    int useNumber;// 使用次数
    std::string msg;// 登录失败或卡密解绑等其他提示

    std::string notice;// 公告

    std::string net_version;// 后台版本号
    bool update_must;// 是否强制更新
    std::string update_message;// 更新公告
    std::string update_url;// 更新地址

    std::string variables;// 变量列表 需自行提取 JSON
    std::string all_data;// 返回所有数据 用户可以自己处理
};

// T3 configuration from C++ normal
extern const char *t3_host;// "w.t3yanzheng.com"
extern const char *t3_base64;// "bCY/Pxg0VMUsXahjNIoi4LDzfAKRZTQ7S3dkWvOqwl9Jycnm1p5Ft6uBHr+2EeG8"
extern const char *t3_key;// "aa199d730b93da766143de1fe640bcb2"

// T3 login/unlink configuration
extern const char *t3_login_url;// "/E5633A3CA5023084"
extern const char *t3_unlink_url;// "/520AE8C6B453B9C0"
extern int t3_login_code;// 200
extern int t3_unlink_code;// 200

// T3 notice/update configuration
extern const char *t3_notice_url;// notice
extern const char *t3_update_url;// update
extern int t3_notice_code;// notice code
extern int t3_update_version;// update version (1029)  if (1029) < network version then update
extern int t3_update_code;// update code

extern const char *hotfix_host;//project host
extern const char *hotfix_key;//project key
extern const char *hotfix_base64;//project base64
extern const char *hotfix_id;//project id

extern std::string hotfix_update_version;//update version
extern int hotfix_bind_code;//bind code
extern int hotfix_unbind_code;//unbind code
extern int hotfix_notice_code;   //unbind code
extern int hotfix_update_code;//update code
extern int hotfix_variable_code;//variable code

extern pid_t target_pid;
extern std::string read_name;  // 自定义读
extern std::string write_name; // 自定义写
extern std::unordered_map<std::string ,std::function<bool(uintptr_t address, void *buffer, size_t size)>> rw_function; // 自定义读写容器
namespace shttp {
    int http_post(const char *host_name, const char *url, const char *parmas, char **request_result);// post
    int http_post_json(const char *host_name, const char *url, const char *parmas, char **request_result);// post
    // you must think why not get the response from the server bucase of love

    int init_safe_modle(bool debug);// init the safe modle if you open debug while log safe status will be true
    int t3_login(t3_json &json, const char *kami, const char *imei);// login
    int t3_unlink(t3_json &json, const char *kami, const char *imei);// unlink
    int t3_notice(t3_json &json);// notice
    int t3_update(t3_json &json);// update

    int hotfix_login(hotfix_json &json, const char *kami, const char *imei);// login
    int hotfix_unlink(hotfix_json &json, const char *kami, const char *imei);// unlink
    int hotfix_notice(hotfix_json &json);// notice
    int hotfix_update(hotfix_json &json);// update
    int hotfix_variable(hotfix_json &json);// variable
    // variable net
    uintptr_t hexStringToUintptr(const std::string &hexStr); // 将十六进制字符串转换为无符号整数
    long hexStringToLong(std::string &hexStr);// 将十六进制字符串转换为长整数
    void string_load_vector(std::vector<uintptr_t> &vec, const std::string &str); // 将字符串转换vector
    void string_load_vector(std::vector<long> &vec, const std::string &str); // 将字符串转换vector
    void string_load_vector(std::vector<int> &vec, const std::string &str); // 将字符串转换vector
    void string_load_vector(std::vector<float> &vec, const std::string &str); // 将字符串转换vector

}// namespace shttp

namespace sutils
{
    time_t get_timestamp();                                                                // get timestamp
    std::unique_ptr<char[]> read_file(const char *file_path);                              // red file
    bool write_file(const char *file_path, const char *content);                           // write file
    char *strstrstr(const char *str, const char *front, const char *rear, bool is_static); // split string
    int hex_to_int(const char *hex);                                                       // hex to int
    bool keep_cup_affinity(unsigned int max_fps);                                          // only support one thred
    bool kepp_while_for_end();                                                             // put it while or for end from your code
    std::string base64_encode(const char *text, const char *base64_table);                 // base64 encode
    std::string base64_decode(const std::string &str, const char *base64_table);           // base64 decode
    char *to_hex(const char *text);                                                        // to hex
    std::string hex_to_string(const std::string &hex_string);                              // hex to string
    void one_group(unsigned int M[]);                                                      // one group
    std::string to_md5(char *pstr, unsigned long long len_B_);                             // md5
    std::string execute_shell_command(const std::string &command);                      //shell command
    std::string get_imei();                                                                 //imei
} // namespace utils
namespace smmap
{
    struct MappedMemory
    {
        void *ptr;
        size_t size;
        MappedMemory(void *p, size_t s) : ptr(p), size(s) {}
        ~MappedMemory()
        {
            if (ptr != MAP_FAILED)
            {
                munmap(ptr, size);
            }
        }
    };
    void *build_mmap_void(const char *file_name, bool readonly, size_t msize);             // 传统指针
    int open_mmapfile(const char *file_name, bool readonly, size_t msize);                        // 获取文件句柄
    std::unique_ptr<MappedMemory> build_mmap(const char *file_name, bool readonly, size_t msize); // 封装mmap函数库
    // 支持手动断开 munmap(ptr, size);

} // namespace smmap


namespace smemory
{
    // this you can use memory methods
    bool initalize_by_game_package(const char *package_name); // initalize by game package
    pid_t initalize_by_game_package_return_pid(const char *package_name); // initalize by game package

    pid_t get_target_pid(); // get target pid
    bool set_target_pid(pid_t pid); // set target pid

    pid_t get_pid_by_package_name(const char *package_name);  // get pid by game package
    bool memory_debug(bool debug);                                      // show memory debug infomation

    bool is_memory_trap(uintptr_t address);                   // check if address is memory trap
    bool read(uintptr_t address, void *buffer, size_t size);  // public read
    bool write(uintptr_t address, void *buffer, size_t size); // public write

    uintptr_t lsp64(uintptr_t addres); // 64bit jump address
    uintptr_t lsp32(uintptr_t addres); // 32bit jump address

    float read_float(uintptr_t address);   // read float
    int read_int(uintptr_t address);       // read int
    double read_double(uintptr_t address); // read double

    float read_float_max(uintptr_t address, float max);            // get value set max value
    float read_float_min(uintptr_t address, float min);            // get value set min value
    float read_float_mix(uintptr_t address, float max, float min); // get value set max and min value

    int read_int_max(uintptr_t address, int max);          // get value set max value
    int read_int_min(uintptr_t address, int min);          // get value set min value
    int read_int_mix(uintptr_t address, int max, int min); // get value set max and min value

    double read_double_max(uintptr_t address, double max);             // get value set max value
    double read_double_min(uintptr_t address, double min);             // get value set min value
    double read_double_mix(uintptr_t address, double max, double min); // get value set max and min value

    long write_float(uintptr_t address, float value);   // write float
    long write_int(uintptr_t address, int value);       // write int
    long write_double(uintptr_t address, double value); // write double

    uintptr_t get_module_base(const char *module_name);                // get module base
    uintptr_t get_module_base_pro(const char *module_name, int index); // get module base cb bss if module_name is contains ":bss"
    uintptr_t get_module_base_pro(const char *module_name, int index,const char* split); // get module base cb bss if module_name is contains ":bss" and split

    uintptr_t read_pointer64(uintptr_t original_address, std::vector<uintptr_t> &vec); // read pointer with offset vector 64bit
    uintptr_t read_pointer32(uintptr_t original_address, std::vector<uintptr_t> &vec); // read pointer with offset vector 32bit

    void get_buffer(char *buf, uintptr_t address); // read buffer from address to buf

} // namespace smemory
#endif//SEA2_SEA2_H
