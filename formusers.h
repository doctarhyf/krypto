#ifndef FORMUSERS_H
#define FORMUSERS_H

#include <QWidget>

namespace Ui {
class FormUsers;
}

class FormUsers : public QWidget
{
    Q_OBJECT

public:
    explicit FormUsers(QWidget *parent = 0);
    ~FormUsers();

private:
    Ui::FormUsers *ui;
};

#endif // FORMUSERS_H
