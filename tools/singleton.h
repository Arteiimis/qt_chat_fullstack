#ifndef SINGLETON_H
#define SINGLETON_H

#include "qdebug.h"
#include "qlogging.h"
#include <memory>
#include <mutex>


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
    }

    void get_raw() { qDebug() << _instence.get(); }
    ~singleton() { qDebug() << "singleton destructed"; }
};
// 模板类显示初始化
template <class T>
std::shared_ptr<T> singleton<T>::_instence = nullptr;

#endif  // !SINGLETON_H
