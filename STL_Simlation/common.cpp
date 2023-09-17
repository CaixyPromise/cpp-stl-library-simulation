#include "common.hpp"
#include <chrono>
#include <iomanip>
#include <ctime>

void output_log(const char* title, const char* content)
{
    // ��ȡ��ǰʱ���
    auto now = std::chrono::system_clock::now();
    // ת��Ϊʱ���
    std::time_t time_now = std::chrono::system_clock::to_time_t(now);
    // ��ȡ���벿��
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    std::cout << std::put_time(std::localtime(&time_now), "%Y-%m-%d %X");
    std::cout << '.' << std::setfill('0') << std::setw(3) << milliseconds.count();
    std::cout << " [" << title << "]: " << content << std::endl;
}
