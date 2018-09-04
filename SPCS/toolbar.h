#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>

/*!
 * \brief The ToolBar class
 * 工具条类
 */
class ToolBar : public QToolBar
{
    Q_OBJECT
public:
    explicit ToolBar(QString title ,QWidget *parent = 0);
    
signals:
    void P_show(QString name,bool isshow);
public slots:
    void visibility(bool flag);

};

#endif // TOOLBAR_H
