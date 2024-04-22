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

enum reqID {
    ID_GET_VERIFY_CODE = 1001,
    ID_REGIST_USER     = 1002,
};

enum modules {
    MODULE_REGIST = 2001,
};

enum errorCodes {
    SUCESS        = 0,
    JSON_ERROR    = 1,
    NETWORK_ERROR = 2,
};

#endif  // !GLOBAL_H
