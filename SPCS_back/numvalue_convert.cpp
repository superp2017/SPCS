#include "numvalue_convert.h"


NumValue_Convert::NumValue_Convert()
{
}

double NumValue_Convert::complex_to_real(std::complex<double> com)
{
    return com.real();
}

double NumValue_Convert::complex_to_imag(std::complex<double> com)
{
    return com.imag();
}

double NumValue_Convert::complex_to_mag(std::complex<double> com)
{
    double re  = complex_to_real(com);
    double ima = complex_to_imag(com);
    return real_imag_to_mag(re,ima);
}

double NumValue_Convert::complex_to_phase(std::complex<double> com)
{
    double re  = complex_to_real(com);
    double ima = complex_to_imag(com);
    return real_imag_to_phase(re,ima);
}

double NumValue_Convert::db_to_line(double db)
{
    return   pow(10,db/20);
}

double NumValue_Convert::db_to_log(double db)
{
    return db/20;
}
double NumValue_Convert::line_to_db(double line)
{
    return SPCS_dB::dB(line);
}

double NumValue_Convert::line_to_log(double line)
{
    return log(line);
}

double NumValue_Convert::log_to_line(double log)
{
    return pow(10,log);
}

double NumValue_Convert::log_to_db(double log)
{
    return 20*log;
}

double NumValue_Convert::real_imag_to_mag(double re,double ima)
{
    return qSqrt(re*re+ima*ima);
}

double NumValue_Convert::real_imag_to_phase(double re,double ima)
{
//    if(re ==0)
//    {
//        if(ima <0)
//            return -90;
//        if(ima == 0)
//            return 0;
//        if(ima >0)
//            return 90;
//    }
//    if(re <0)
//    {
//        if(ima <0)
//            return atan(re/ima)-180;
//        if(ima == 0)
//            return 180;
//        if(ima >0)
//            return atan(-(re/ima))+90;
//    }
//    if(re > 0)
//    {
//        if(ima <0)
//            return -atan(-(re/ima));
//        if(ima == 0)
//            return 0;
//        if(ima >0)
//            return atan(re/ima);
//    }
    double res = qAtan2(ima,re)/3.141592653*180;
    if(res == 0)
    {
        qDebug() << "real = " << re;
        qDebug() << "imag = " << ima;
    }
    return res;
}

double NumValue_Convert::mag_phase_to_real(double mag,double pha)
{
    if(pha>0)
        return sin(pha)*mag;
    else
        return -sin(pha)*mag;
}

double NumValue_Convert::mag_phase_to_imag(double mag,double pha)
{
    if(pha>0)
        return cos(pha)*mag;
    else
        return -cos(pha*mag);
}


/////////////////////////////////////////////////////////////////////


std::vector<double> NumValue_Convert::db_to_line_vector(std::vector<double> db)
{
    std::vector<double> vec;
    for(size_t i=0;i<db.size();++i)
    {
        vec.push_back(db_to_line(db[i]));
    }
    return vec;
}

std::vector<double> NumValue_Convert::db_log_vector(std::vector<double> db)
{
    std::vector<double> vec;
    for(size_t i=0;i<db.size();++i)
    {
        vec.push_back(db_to_log(db[i]));
    }
    return vec;
}

std::vector<double> NumValue_Convert::line_to_db_vector(std::vector<double> line)
{
    std::vector<double> vec;
    for(size_t i=0;i<line.size();++i)
    {
        vec.push_back(line_to_db(line[i]));
    }
    return vec;
}

std::vector<double> NumValue_Convert::line_to_log_vector(std::vector<double> line)
{
    std::vector<double> vec;
    for(size_t i=0;i<line.size();++i)
    {
        vec.push_back(db_to_log(line[i]));
    }
    return vec;
}

std::vector<double> NumValue_Convert::log_to_line_vector(std::vector<double> log)
{
    std::vector<double> vec;
    for(size_t i=0;i<log.size();++i)
    {
        vec.push_back(log_to_line(log[i]));
    }
    return vec;
}
std::vector<double> NumValue_Convert::log_to_db_vector(std::vector<double> log)
{
    std::vector<double> vec;
    for(size_t i=0;i<log.size();++i)
    {
        vec.push_back(log_to_db(log[i]));
    }
    return vec;
}

std::vector<double> NumValue_Convert::real_imag_to_mag_vector(std::vector<double> rea,std::vector<double> ima)
{
    std::vector<double> vec;
    if(rea.size()== ima.size())
    {
        for(size_t i=0;i<ima.size();++i)
        {
            vec.push_back(real_imag_to_mag(rea[i],ima[i]));
        }
    }
    return vec;
}

std::vector<double> NumValue_Convert::real_imag_to_phase_vector(std::vector<double> rea,std::vector<double> ima)
{
    std::vector<double> vec;
    if(rea.size()== ima.size())
    {
        for(size_t i=0;i<rea.size();++i)
        {
            vec.push_back(real_imag_to_phase(rea[i],ima[i]));
        }
    }
    return vec;
}
std::vector<double> NumValue_Convert::mag_phase_to_real_vector(std::vector<double> mag,std::vector<double> pha)
{
    std::vector<double> vec;
    if(mag.size()== pha.size())
    {
        for(size_t i=0;i<pha.size();++i)
        {
            vec.push_back(mag_phase_to_real(mag[i],pha[i]));
        }
    }
    return vec;
}
std::vector<double> NumValue_Convert::mag_phase_to_imag_vector(std::vector<double> mag,std::vector<double> pha)
{
    std::vector<double> vec;
    if(mag.size()== pha.size())
    {
        for(size_t i=0;i<pha.size();++i)
        {
            vec.push_back(mag_phase_to_imag(mag[i],pha[i]));
        }
    }
    return vec;
}
