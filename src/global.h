#ifndef GLOBAL_H
#define GLOBAL_H

#include "QStyle"
#include "qwidget.h"
#include <functional>

/**
 * @brief 刷新 qss 样式
 * 
 */
extern std::function<void(QWidget*)> refreshStyle;

#endif  // !GLOBAL_H
