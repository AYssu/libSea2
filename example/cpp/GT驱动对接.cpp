#include <Sea2.h>

pid_t target_pid = 0;
std::string read_name = "kernel_read";

std::string write_name = "kernel_write";

std::unordered_map<std::string, std::function<bool(uintptr_t address, void* buffer, size_t size)>> rw_function;

#include <algorithm>
#include <chrono>
#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <linux/kdev_t.h>
#include <map>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <vector>
using namespace std;

class c_driver {
private:
    int fd;
    pid_t pid;

    typedef struct _COPY_MEMORY {
        pid_t pid;
        uintptr_t address;
        void* buffer;
        size_t size;
    } COPY_MEMORY, *PCOPY_MEMORY;

    typedef struct _MODULE_BASE {
        pid_t pid;
        char* name;
        uintptr_t base;
    } MODULE_BASE, *PMODULE_BASE;

    enum OPERATIONS {
        OP_INIT_KEY = 0x800,
        OP_READ_MEM = 0x801,
        OP_WRITE_MEM = 0x802,
        OP_MODULE_BASE = 0x803,
    };

    
    char* driver_gt()
    {
        // 打开目录
        const char* dev_path = "/dev";
        DIR* dir = opendir(dev_path);
        if (dir == NULL) {
            printf("无法打开/dev目录\n");
            return NULL;
        }

        char* files[] = { "wanbai", "CheckMe", "Ckanri", "lanran", "video188" };
        struct dirent* entry;
        char* file_path = NULL;
        while ((entry = readdir(dir)) != NULL) {
            // 跳过当前目录和上级目录
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            size_t path_length = strlen(dev_path) + strlen(entry->d_name) + 2;
            file_path = (char*)malloc(path_length);
            snprintf(file_path, path_length, "%s/%s", dev_path, entry->d_name);
            for (int i = 0; i < 5; i++) {
                if (strcmp(entry->d_name, files[i]) == 0) {
                    printf("驱动文件：%s\n", file_path);
                    closedir(dir);
                    return file_path;
                }
            }

            // 获取文件stat结构
            struct stat file_info;
            if (stat(file_path, &file_info) < 0) {
                free(file_path);
                file_path = NULL;
                continue;
            }

            // 跳过gpio接口
            if (strstr(entry->d_name, "gpiochip") != NULL) {
                free(file_path);
                file_path = NULL;
                continue;
            }

            // 检查是否为驱动文件
            if ((S_ISCHR(file_info.st_mode) || S_ISBLK(file_info.st_mode))
                && strchr(entry->d_name, '_') == NULL && strchr(entry->d_name, '-') == NULL && strchr(entry->d_name, ':') == NULL) {
                // 过滤标准输入输出
                if (strcmp(entry->d_name, "stdin") == 0 || strcmp(entry->d_name, "stdout") == 0
                    || strcmp(entry->d_name, "stderr") == 0 || strstr(entry->d_name, "pmsg") != nullptr || strcmp(entry->d_name, "loop") == 0) {
                    free(file_path);
                    file_path = NULL;
                    continue;
                }

                size_t file_name_length = strlen(entry->d_name);
                time_t current_time;
                time(&current_time);
                int current_year = localtime(&current_time)->tm_year + 1900;
                int file_year = localtime(&file_info.st_ctime)->tm_year + 1900;
                // 跳过1980年前的文件
                if (file_year <= 1980) {
                    free(file_path);
                    file_path = NULL;
                    continue;
                }

                time_t atime = file_info.st_atime;
                time_t ctime = file_info.st_ctime;
                // 检查最近访问时间和修改时间是否一致并且文件名是否是symbol文件
                if ((atime == ctime) /* && symbol_file(entry->d_name)*/) {
                    // 检查mode权限类型是否为S_IFREG(普通文件)和大小还有gid和uid是否为0(root)并且文件名称长度在7位或7位以下
                    if ((file_info.st_mode & S_IFMT) == 8192 && file_info.st_size == 0
                        && file_info.st_gid == 0 && file_info.st_uid == 0 && file_name_length <= 9 && file_name_length >= 6) {
                        printf("驱动节点：%s\n", file_path);
                        closedir(dir);
                        return file_path;
                    }
                }
            }
            free(file_path);
            file_path = NULL;
        }
        closedir(dir);
        return NULL;
    }

public:
    c_driver()
    {
        char* device_name = driver_gt();
        if (device_name != NULL) {
            fd = open(device_name, O_RDWR);
            if (fd <= 0) {
                printf("[-] 驱动异常或不存在,请安装QX11.4\n");
                exit(0);
            } else {
                printf("[-] 驱动加载成功\n");
            }
        }else
        {
            printf("[-] 驱动未找到\n");
            exit(0);
        }
        
    }

    ~c_driver()
    {
        if (fd > 0) {
            printf("[-] 驱动关闭成功!\n");
            close(fd);
        }
    }

    void init(pid_t pid) { this->pid = pid; }

    bool read(uintptr_t address, void* buffer, size_t size)
    {
        COPY_MEMORY cm;
        cm.pid = this->pid;
        cm.address = address;
        cm.buffer = buffer;
        cm.size = size;
        if (ioctl(fd, OP_READ_MEM, &cm) != 0) {
            return false;
        }
        return true;
    }

    bool write(uintptr_t address, void* buffer, size_t size)
    {
        COPY_MEMORY cm;
        cm.pid = this->pid;
        cm.address = address;
        cm.buffer = buffer;
        cm.size = size;
        if (ioctl(fd, OP_WRITE_MEM, &cm) != 0) {
            return false;
        }
        return true;
    }

    template <typename T>
    T read(uintptr_t address)
    {
        T res;
        if (this->read(address, &res, sizeof(T)))
            return res;
        return {};
    }

    template <typename T>
    bool write(uintptr_t address, T value)
    {
        return this->write(address, &value, sizeof(T));
    }

    uintptr_t get_module_base(const char* name)
    {
        MODULE_BASE mb;
        char buf[0x100];
        strcpy(buf, name);
        mb.pid = this->pid;
        mb.name = buf;
        if (ioctl(fd, OP_MODULE_BASE, &mb) != 0) {
            return 0;
        }
        return mb.base;
    }
};

static c_driver* driver = new c_driver();
bool vm_readv(uintptr_t address, void* buffer, size_t size)
{
    return driver->read(address, buffer, size);
}
bool vm_writev(uintptr_t address, void* buffer, size_t size)
{
    return driver->write(address, buffer, size);
}

bool init_pid(pid_t pid)
{
    driver->init(pid);
    return true;
}


int main(int argc, char** argv)
{
    auto pid = smemory::initalize_by_game_package_return_pid("com.tencent.tmgp.cf"); // initalize by game package
    
    init_pid(pid); // 进程读写需要的初始化pid
    auto base = driver->get_module_base("libil2cpp.so");
    
printf("进程pid %d %lx\n", pid, base);
    rw_function.insert({ "kernel_read", vm_readv });
    rw_function.insert({ "kernel_write", vm_writev });
    smemory::memory_debug(false); //打印自定义读写实例
    std::vector<uintptr_t> pt = {0x123};
    auto i = smemory::read_byte(base);
    printf("读测试 %d \n", i);
    auto p = smemory::read_pointer64(base,pt);
    return 0;
}