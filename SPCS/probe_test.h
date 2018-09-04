#ifndef PROBE_TEST_H
#define PROBE_TEST_H
#include <QThread>
#include "H_probe_test.h"

class Probe_test: public QThread
{
    Q_OBJECT
public:
    Probe_test();
    void show_ui();
protected:
    void run();
private:
    H_probe_test     m_test_ui;
};

#endif // PROBE_TEST_H
