#ifndef GEPARAM_H
#define GEPARAM_H
#include <vector>
#include <string>
#include "_win32.h"
#include <boost/tokenizer.hpp>


namespace Asura
{
class GEParam
{
    friend class GEComParam;
public:
    GEParam(const char *buff_)
        :m_str_(buff_)
    {
        reset();
    }
    GEParam(std::string &str_)
        :m_str_(str_)
    {
        reset();
    }
    GEParam()
    {
        reset();
    }
    virtual ~GEParam()
    {

    }
    void reset()
    {
        m_valid_ = false;
        m_param_.clear();
    }

    operator bool()
    {
        return m_valid_;
    }

    GEParam& operator =(bool b_)
    {
        m_valid_ = b_;
        return *this;
    }

    void push_param(char *param_)
    {
        m_param_.push_back(std::string(param_));
    }
public:
    operator std::vector<std::string>& ()
    {
        return m_param_;
    }

    size_t size()
    {
        return m_param_.size();
    }
    std::string& operator [](size_t i_)
    {
        return m_param_[i_];
    }
    std::string to_string()
    {
        std::string res_;
        std::vector<std::string>::iterator iter_ = m_param_.begin();
        while(iter_ != m_param_.end())
        {
            res_ += "[";
            res_ += *iter_;
            res_ += "]";
            iter_++;
        }
        return res_;
    }

public:
    std::vector<std::string>    m_param_;
    std::string                 m_str_;
    bool                        m_valid_;
};

}

#endif // GEPARAM_H
