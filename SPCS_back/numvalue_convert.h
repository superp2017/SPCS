#ifndef NUMVALUE_CONVERT_H
#define NUMVALUE_CONVERT_H
#include<vector>
#include<qmath.h>
//#include<math.h>
#include<complex>
#include <QDebug>
#include "_global.h"
using namespace CVTS;

/*!
 * \brief The NumValue_Convert class
 * 数值转化类,没有使用
 */
class NumValue_Convert
{
public:
    NumValue_Convert();

    static double complex_to_real(std::complex<double> com);
    static double complex_to_imag(std::complex<double> com);
    static double complex_to_mag(std::complex<double> com);
    static double complex_to_phase(std::complex<double> com);

    static double db_to_line(double db);
    static double db_to_log(double db);
    static double line_to_db(double line);
    static double line_to_log(double line);
    static double log_to_line(double log);
    static double log_to_db(double log);

    static double real_imag_to_mag(double re,double ima);
    static double real_imag_to_phase(double re,double ima);

    static double mag_phase_to_real(double mag,double pha);
    static double mag_phase_to_imag(double mag,double pha);

    //////////////////////////////////////////////

    std::vector<double> db_to_line_vector(std::vector<double> db);
    std::vector<double> db_log_vector(std::vector<double> db);
    std::vector<double> line_to_db_vector(std::vector<double> line);
    std::vector<double> line_to_log_vector(std::vector<double> line);
    std::vector<double> log_to_line_vector(std::vector<double> log);
    std::vector<double> log_to_db_vector(std::vector<double> log);

    std::vector<double> real_imag_to_mag_vector(std::vector<double> rea,std::vector<double> ima);
    std::vector<double> real_imag_to_phase_vector(std::vector<double> rea,std::vector<double> ima);
    std::vector<double> mag_phase_to_real_vector(std::vector<double> mag,std::vector<double> pha);
    std::vector<double> mag_phase_to_imag_vector(std::vector<double> mag,std::vector<double> pha);

};

#endif // NUMVALUE_CONVERT_H
