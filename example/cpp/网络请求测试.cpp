#include <Sea2.h>

int main(int argc, char** argv)
{
    // 当然支持https了啊 基本操作 内置的curl允许你直接使用curl相关头文件
    auto http = shttp::http_get("https://www.easyverify.top");
    std::cout << "请求是否成功: " << http.success << std::endl;
    std::cout << "状态码: " << http.code << std::endl;
    std::cout << "响应数据: " << http.data << std::endl;
    std::cout << "错误信息: " << http.error << std::endl;
    return 0;
}