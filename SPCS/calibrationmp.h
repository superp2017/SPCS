#ifndef CALIBRATIONMP_H
#define CALIBRATIONMP_H

#include <QObject>
#include <map>
#include <vector>

class CalibrationMP : public QObject
{
    Q_OBJECT
protected:
    explicit CalibrationMP(QObject *parent = 0);
    
public:
    static CalibrationMP* instance()
    {
        static CalibrationMP *cmp = new CalibrationMP;
        return cmp;
    }
    static void destroy()
    {
        delete instance();
    }
    double get_mag(QString &freq, size_t id);
    double get_phase(QString &freq, size_t id);
signals:
    

public slots:
    void calibration_path(QString path);
protected:
    void init();
private:
    void load_M(QString &freq, const QString &prefix, std::map<QString, std::vector<double> > &value);
    void load_P(QString &freq, const QString &prefix, std::map<QString, std::vector<double> > &value);

private:
    std::map<QString, std::vector<double> >      m_M2;
    std::map<QString, std::vector<double> >      m_P2;
    QString                                         m_path;
};

#endif // CALIBRATIONMP_H
