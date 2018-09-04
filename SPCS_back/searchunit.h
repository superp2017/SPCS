#ifndef SEARCHUNIT_H
#define SEARCHUNIT_H

#include <QWidget>

namespace Ui {
class SearchUnit;
}

/*!
 * \brief The SearchUnit class
 * ������Ԫ�����������ϵ���������
 */

class SearchUnit : public QWidget
{
    Q_OBJECT
public:
    static SearchUnit* instance()
    {
        static SearchUnit* search = new SearchUnit();
        return search;
    }
    static void destory()
    {
        delete instance();
    }
protected:
    explicit SearchUnit(QWidget *parent = 0);
    ~SearchUnit();
    
private slots:
    void on_pushButton_clicked();
    void on_radioButton_id_clicked();

    void on_radioButton_rowcol_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_2_clicked();

signals:
    void showUnit(int id);
    void showIDs(QString path);
    void close_all();
private:
    Ui::SearchUnit *ui;
};

#endif // SEARCHUNIT_H
