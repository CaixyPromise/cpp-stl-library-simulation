#include "common.hpp"
#include <chrono>
#include <iomanip>
#include <ctime>

void output_log(const char* title, const char* content)
{
    // 获取当前时间点
    auto now = std::chrono::system_clock::now();
    // 转换为时间戳
    std::time_t time_now = std::chrono::system_clock::to_time_t(now);
    // 获取毫秒部分
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    std::cout << std::put_time(std::localtime(&time_now), "%Y-%m-%d %X");
    std::cout << '.' << std::setfill('0') << std::setw(3) << milliseconds.count();
    std::cout << " [" << title << "]: " << content << std::endl;
}
