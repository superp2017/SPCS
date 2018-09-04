#ifndef CALIBRATE_H
#define CALIBRATE_H
#include "icalibraion.h"
#include "icalibrationsimulateonorbit.h"
#include "ioriginaldata.h"
#include <boost/numeric/mtl/mtl.hpp>
#include <QDebug>
#include <iostream>
#include <qmath.h>

class OriginalData
    :public ::Calibration::IOriginalData
{
public:
    OriginalData():IOriginalData(complex<double>(),complex<double>(),vector<complex<double>>(),vector<complex<double>>()){}
    int get_N(){return 7;}
    int get_I(){return 10;}
    vector<double> get_Ai(){return m_Ai;}
    vector<double> get_Pi(){return m_Pi;}
    vector<double> get_An(){return m_An;}
    vector<double> get_Pn(){return m_Pn;}
    vector<complex<double>> get_Wn()
    {
        vector<complex<double>> res_;
        int n_ = this->get_N();
        vector<double> An_ = get_An();
        vector<double> Pn_ = get_Pn();

        for(int i_ = 0;i_ < n_;++i_)
        {
            complex<double> w_;
            w_.real(An_[i_] * cos(Pn_[i_]));
            w_.imag(An_[i_] * sin(Pn_[i_]));
            res_.push_back(w_);
        }
        return res_;
    }

public:
    vector<double>	    m_Ai;
    vector<double>      m_Pi;
    vector<double>      m_An;
    vector<double>      m_Pn;
};

vector<vector<double>> get_S();
vector<vector<complex<double>>> get_S1();
vector<vector<complex<double>>> get_S2();

class Calibrate
{
public:
    Calibrate();
};



/// test interface
void test_OriginalData_calibrate();

#endif // CALIBRATE_H
