#include "toolbar.h"

ToolBar::ToolBar(QString title, QWidget *parent) :
    QToolBar(parent)
{
    setWindowTitle(title);
    connect(this,SIGNAL(visibilityChanged(bool)),this,SLOT(visibility(bool)));
    QString ls_sheet = QString::fromUtf8("font: 10pt \"\346\245\267\344\275\223\";");
    this->setStyleSheet(ls_sheet);
}

void ToolBar::visibility(bool flag)
{
    emit P_show(this->windowTitle(),flag);
}
