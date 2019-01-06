#include "widgetProgramsList.h"
#include "ui_widgetprogramslist.h"

WidgetProgramsList::WidgetProgramsList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

WidgetProgramsList::~WidgetProgramsList()
{
    delete ui;
}
