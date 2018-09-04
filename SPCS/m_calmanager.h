#ifndef M_CALMANAGER_H
#define M_CALMANAGER_H

#include <QObject>
#include <QCoreApplication>
#include <QWidget>
#include <QProcess>
#include <QFileInfo>
#include <QDir>
#include <QProcess>
#include <QDebug>
#include "_config.h"


/*!
 * \brief The M_CalManager class
 * 之前的校准库管理，目前没有使用
 */
class M_CalManager : public QObject
{
    Q_OBJECT
public:
    explicit M_CalManager(QObject *parent = 0);
    static M_CalManager *instance();
    static void destory();
    QList<QString> BaseLib();
    QList<QString> UserLib();
    void open_calibration(QString &file);
    void rename_file(QString &path);
signals:
    
public slots:
private slots:
    QList<QString> get_files(const char *path);
    void open_file(QString &path);

private:
    QProcess m_process;
    
};

#endif // M_CALMANAGER_H
