#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class WidgetProgramsList : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetProgramsList(QWidget *parent = 0);
    ~WidgetProgramsList();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
