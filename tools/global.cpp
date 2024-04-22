#include "global.h"
#include "qwidget.h"
#include <functional>

std::function<void(QWidget*)> refreshStyle = [](QWidget* widget) {
    widget->style()->unpolish(widget);
    widget->style()->polish(widget);
};
