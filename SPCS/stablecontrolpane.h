#ifndef STABLECONTROLPANE_H
#define STABLECONTROLPANE_H

#include <QWidget>
#include <map>
#include <QString>

namespace Ui {
class StableControlPane;
}


/*!
 * \brief The StableControlPane class
 * �ȶ��Թ��ߵĿ������
 */
class StableControlPane : public QWidget
{
    Q_OBJECT
    
public:
    explicit StableControlPane(QWidget *parent = 0);
    ~StableControlPane();
    void clear_combox();
    void reset();
    void add_item(QString freq);
signals:
    void query(QString freq, QString type, bool isto0);
    void loaddata(QString path);
private slots:
    void on_pushButton_load_clicked();
    void query_data();

private:
    Ui::StableControlPane *ui;
};

#endif // STABLECONTROLPANE_H
