#ifndef POWERATE_H
#define POWERATE_H

#include <QObject>
#include <map>
#include <QString>
#include <QVector>

class Powerate : public QObject
{
    Q_OBJECT
public:
    explicit Powerate(const QString &file, QObject *parent = 0);

    double get_avg();
    std::map<QString,QString>& get_freq_map(){return m_freq_mag;}
    QVector<QString> &get_freqs();
private:
    void parse(const QString &file);
    
signals:
    
public slots:
    
private:
    std::map<QString,QString>       m_freq_mag;
    QVector<QString>                m_freqs;
};

#endif // POWERATE_H
