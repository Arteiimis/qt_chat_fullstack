#ifndef SINGLETON_H
#define SINGLETON_H

#include "qlogging.h"
#include <memory>
#include <mutex>
#include <spdlog/spdlog.h>


template <class T>
class singleton
{
protected:
    singleton()                            = default;
    singleton(const singleton&)            = delete;
    singleton& operator=(const singleton&) = delete;

    static std::shared_ptr<T> _instence;

public:
    static std::shared_ptr<T> getInstence() {
        // 局部静态变量只会在第一次被调用时初始化
        // call_once 可以精准的保证只被调用一次
        static std::once_flag flag;
        std::call_once(flag, [&]() { _instence = std::shared_ptr<T>(new T); });
        return _instence;
    }

    void get_raw() { spdlog::info("get_raw"); }
    ~singleton() { spdlog::info("singleton destructed"); }
};
// 模板类显示初始化
template <class T>
std::shared_ptr<T> singleton<T>::_instence = nullptr;

#endif  // !SINGLETON_H
