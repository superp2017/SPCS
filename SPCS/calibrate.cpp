#include "calibrate.h"

Calibrate::Calibrate()
{
}

vector<vector<double>> get_S()
{
    vector<vector<double>> S_;
    vector<double> t_;
    t_.push_back(0);t_.push_back(9);t_.push_back(18);t_.push_back(27);t_.push_back(37);t_.push_back(42);t_.push_back(55);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(8);t_.push_back(18);t_.push_back(26);t_.push_back(36);t_.push_back(42);t_.push_back(54);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(9);t_.push_back(16);t_.push_back(25);t_.push_back(37);t_.push_back(40);t_.push_back(53);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(9);t_.push_back(18);t_.push_back(27);t_.push_back(33);t_.push_back(42);t_.push_back(51);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(1);t_.push_back(18);t_.push_back(19);t_.push_back(37);t_.push_back(34);t_.push_back(55);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(9);t_.push_back(2);t_.push_back(11);t_.push_back(37);t_.push_back(42);t_.push_back(39);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(9);t_.push_back(18);t_.push_back(27);t_.push_back(5);t_.push_back(10);t_.push_back(23);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(1);t_.push_back(0);t_.push_back(1);t_.push_back(1);t_.push_back(0);t_.push_back(1);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(0);t_.push_back(2);t_.push_back(2);t_.push_back(0);t_.push_back(2);t_.push_back(2);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(0);t_.push_back(0);t_.push_back(0);t_.push_back(4);t_.push_back(0);t_.push_back(4);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(8);t_.push_back(0);t_.push_back(8);t_.push_back(0);t_.push_back(8);t_.push_back(0);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(0);t_.push_back(16);t_.push_back(16);t_.push_back(0);t_.push_back(0);t_.push_back(16);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(0);t_.push_back(0);t_.push_back(0);t_.push_back(32);t_.push_back(32);t_.push_back(32);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(8);t_.push_back(16);t_.push_back(24);t_.push_back(36);t_.push_back(40);t_.push_back(52);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(8);t_.push_back(18);t_.push_back(26);t_.push_back(32);t_.push_back(42);t_.push_back(50);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(0);t_.push_back(18);t_.push_back(18);t_.push_back(36);t_.push_back(34);t_.push_back(54);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(8);t_.push_back(2);t_.push_back(10);t_.push_back(36);t_.push_back(42);t_.push_back(38);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(8);t_.push_back(18);t_.push_back(26);t_.push_back(4);t_.push_back(10);t_.push_back(22);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(9);t_.push_back(16);t_.push_back(25);t_.push_back(33);t_.push_back(40);t_.push_back(49);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(1);t_.push_back(16);t_.push_back(17);t_.push_back(37);t_.push_back(32);t_.push_back(53);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(9);t_.push_back(0);t_.push_back(9);t_.push_back(37);t_.push_back(40);t_.push_back(37);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(9);t_.push_back(16);t_.push_back(25);t_.push_back(5);t_.push_back(8);t_.push_back(21);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(1);t_.push_back(18);t_.push_back(19);t_.push_back(33);t_.push_back(34);t_.push_back(51);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(9);t_.push_back(2);t_.push_back(11);t_.push_back(33);t_.push_back(42);t_.push_back(35);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(9);t_.push_back(18);t_.push_back(27);t_.push_back(1);t_.push_back(10);t_.push_back(19);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(1);t_.push_back(2);t_.push_back(3);t_.push_back(37);t_.push_back(34);t_.push_back(39);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(1);t_.push_back(18);t_.push_back(19);t_.push_back(5);t_.push_back(2);t_.push_back(23);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(9);t_.push_back(2);t_.push_back(11);t_.push_back(5);t_.push_back(10);t_.push_back(7);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(1);t_.push_back(2);t_.push_back(3);t_.push_back(1);t_.push_back(2);t_.push_back(3);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(1);t_.push_back(0);t_.push_back(1);t_.push_back(5);t_.push_back(0);t_.push_back(5);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(9);t_.push_back(0);t_.push_back(9);t_.push_back(1);t_.push_back(8);t_.push_back(1);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(1);t_.push_back(16);t_.push_back(17);t_.push_back(1);t_.push_back(0);t_.push_back(17);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(1);t_.push_back(0);t_.push_back(1);t_.push_back(33);t_.push_back(32);t_.push_back(33);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(0);t_.push_back(2);t_.push_back(2);t_.push_back(4);t_.push_back(2);t_.push_back(6);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(8);t_.push_back(2);t_.push_back(10);t_.push_back(0);t_.push_back(10);t_.push_back(2);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(0);t_.push_back(18);t_.push_back(18);t_.push_back(0);t_.push_back(2);t_.push_back(18);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(0);t_.push_back(2);t_.push_back(2);t_.push_back(32);t_.push_back(34);t_.push_back(34);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(8);t_.push_back(0);t_.push_back(8);t_.push_back(4);t_.push_back(8);t_.push_back(4);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(0);t_.push_back(16);t_.push_back(16);t_.push_back(4);t_.push_back(0);t_.push_back(20);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(0);t_.push_back(0);t_.push_back(0);t_.push_back(36);t_.push_back(32);t_.push_back(36);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(8);t_.push_back(16);t_.push_back(24);t_.push_back(0);t_.push_back(8);t_.push_back(16);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(8);t_.push_back(0);t_.push_back(8);t_.push_back(32);t_.push_back(40);t_.push_back(32);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(0);t_.push_back(16);t_.push_back(16);t_.push_back(32);t_.push_back(32);t_.push_back(48);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(8);t_.push_back(16);t_.push_back(24);t_.push_back(32);t_.push_back(40);t_.push_back(48);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(0);t_.push_back(16);t_.push_back(16);t_.push_back(36);t_.push_back(32);t_.push_back(52);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(8);t_.push_back(0);t_.push_back(8);t_.push_back(36);t_.push_back(40);t_.push_back(36);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(8);t_.push_back(16);t_.push_back(24);t_.push_back(4);t_.push_back(8);t_.push_back(20);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(0);t_.push_back(18);t_.push_back(18);t_.push_back(32);t_.push_back(34);t_.push_back(50);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(8);t_.push_back(2);t_.push_back(10);t_.push_back(32);t_.push_back(42);t_.push_back(34);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(8);t_.push_back(18);t_.push_back(26);t_.push_back(0);t_.push_back(10);t_.push_back(18);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(0);t_.push_back(2);t_.push_back(2);t_.push_back(36);t_.push_back(34);t_.push_back(38);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(0);t_.push_back(18);t_.push_back(18);t_.push_back(4);t_.push_back(2);t_.push_back(22);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(8);t_.push_back(2);t_.push_back(10);t_.push_back(4);t_.push_back(10);t_.push_back(6);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(1);t_.push_back(2);t_.push_back(3);t_.push_back(5);t_.push_back(2);t_.push_back(7);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(9);t_.push_back(2);t_.push_back(11);t_.push_back(1);t_.push_back(10);t_.push_back(3);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(1);t_.push_back(18);t_.push_back(19);t_.push_back(1);t_.push_back(2);t_.push_back(19);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(1);t_.push_back(2);t_.push_back(3);t_.push_back(33);t_.push_back(34);t_.push_back(35);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(9);t_.push_back(0);t_.push_back(9);t_.push_back(5);t_.push_back(8);t_.push_back(5);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(1);t_.push_back(16);t_.push_back(17);t_.push_back(5);t_.push_back(0);t_.push_back(21);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(1);t_.push_back(0);t_.push_back(1);t_.push_back(37);t_.push_back(32);t_.push_back(37);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(9);t_.push_back(16);t_.push_back(25);t_.push_back(1);t_.push_back(8);t_.push_back(17);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(9);t_.push_back(0);t_.push_back(9);t_.push_back(33);t_.push_back(40);t_.push_back(33);
    S_.push_back(t_);t_.clear();
    t_.push_back(0);t_.push_back(1);t_.push_back(16);t_.push_back(17);t_.push_back(33);t_.push_back(32);t_.push_back(49);
    S_.push_back(t_);t_.clear();

    return S_;
}

vector<vector<complex<double>>> get_S1()
{
    vector<vector<double>> S_ = get_S();
    vector<vector<complex<double>>> res_;
    for(int i_ = 0;i_ < 63;++i_)
    {
        vector<complex<double>> row_;
        for(int j_ = 0;j_ < 7;++j_)
        {
            complex<double> cell_;
            cell_.real(cos(2 * M_PI * S_[i_][j_] / 64));
            cell_.imag(sin(2 * M_PI * S_[i_][j_] / 64));
            row_.push_back(cell_);
        }
        res_.push_back(row_);
    }
    return res_;
}

vector<vector<complex<double>>> get_S2()
{
    vector<vector<double>> S_ = get_S();
    vector<vector<complex<double>>> res_;
    for(int i_ = 0;i_ < 63;++i_)
    {
        vector<complex<double>> row_;

        for(int j_ = 0;j_ < 7;++j_)
        {
            complex<double> cell_;
            cell_.real(cos(2 * M_PI * S_[i_][j_] / 64));
            cell_.imag(sin(2 * M_PI * S_[i_][j_] / 64) * -1.0);
            row_.push_back(cell_);
        }
        res_.push_back(row_);
    }
    return res_;
}


void test_OriginalData_calibrate()
{
    qDebug()<<"on";

    OriginalData originalData_;

    vector<double> Ai_;
    vector<double> Pi_;
    vector<double> An_;
    vector<double> Pn_;

    {
        Ai_.push_back(10);
        Ai_.push_back(10.5);
        Pi_.push_back(10.5);
        Pi_.push_back(10.5);

        An_.push_back(3.00784789707583);
        An_.push_back(6.95376264797447);
        Pn_.push_back(-43.9573311333016 *M_PI /180);
        Pn_.push_back(70.6249278917635 *M_PI/180);

        originalData_.m_Ai = Ai_;
        originalData_.m_Pi = Pi_;
        originalData_.m_An = An_;
        originalData_.m_Pn = Pn_;
    }

    vector<vector<complex<double>>> s1_ = get_S1();
    vector<vector<complex<double>>> s2_ = get_S2();

    vector<double> at0_;
    for(int i_ = 0;i_ > -10;--i_)
        at0_.push_back((double)i_);

    vector<double> s63_;
    for(int i_ = 0;i_ < 64;++i_)
        s63_.push_back((double)i_);

    qDebug()<< "-----------------------------------";
    ::Calibration::ICalibrationSimulateOnOrbit calibrationSimulateOnOrbit_(originalData_);
    qDebug()<< calibrationSimulateOnOrbit_.get_A0();
    qDebug()<< calibrationSimulateOnOrbit_.get_P0();
}
