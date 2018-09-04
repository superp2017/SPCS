#ifndef GEBUFFER_H
#define GEBUFFER_H
#include <vector>
#include <boost/asio.hpp>
#include <boost/pool/pool.hpp>
#include <_win32.h>

namespace Asura
{

class GEMBuffer
{
public:
    typedef std::vector<boost::asio::mutable_buffer>    MBuffer;
public:
    GEMBuffer()
        :m_pool_(8192)
    {
        m_size_ = 0;
    }
    ~GEMBuffer()
    {
        reset();
    }

    void reset()
    {
        MBuffer::iterator iter_ = m_mbuff_.begin();
        while(iter_ != m_mbuff_.end())
        {
            m_pool_.free(boost::asio::buffer_cast<void*>(*iter_));
            iter_++;
        }
        m_size_ = 0;
        m_mbuff_.clear();
    }
    size_t size() const
    {
        return m_size_;
    }

public:
    MBuffer& buffer()
    {
        return m_mbuff_;
    }

    operator MBuffer& ()
    {
        return m_mbuff_;
    }

    void to_string(std::string& str_)
    {
        str_.resize(m_size_);
        char *p = const_cast<char*>(str_.c_str());
        MBuffer::iterator iter_ = m_mbuff_.begin();
        int I = 0;
        while(iter_ != m_mbuff_.end())
        {
            size_t N = boost::asio::buffer_size(*iter_);
            memcpy(p+I, boost::asio::buffer_cast<char*>(*iter_), N);
            I += N;
            iter_++;
        }
        str_[m_size_] = 0;
    }
    void expand(size_t s_)
    {
        MBuffer::iterator iter_ = m_mbuff_.begin();
        while(iter_ != m_mbuff_.end())
        {
            m_pool_.free(boost::asio::buffer_cast<void*>(*iter_));
            iter_++;
        }

        m_size_ = s_;
        while(s_ >= BODY_LENGTH)
        {
            m_mbuff_.push_back(boost::asio::buffer(m_pool_.malloc(), BODY_LENGTH));
            s_ -= BODY_LENGTH;
        }
        if(s_ > 0)
        {
            m_mbuff_.push_back(boost::asio::buffer(m_pool_.malloc(), s_));
        }
    }
private:
    MBuffer                                                 m_mbuff_;
    size_t                                                  m_size_;
    boost::pool<>                                           m_pool_;
};

class GECBuffer
{
public:
    typedef std::vector<boost::asio::const_buffer>    CBuffer;
public:
    GECBuffer()
        :m_pool_(8192)
    {
        m_size_ = 0;
    }
    ~GECBuffer()
    {
        reset();
    }

    void reset()
    {
        CBuffer::iterator iter_ = m_cbuff_.begin();
        while(iter_ != m_cbuff_.end())
        {
            m_pool_.free(const_cast<void*>(boost::asio::buffer_cast<const void*>(*iter_)));
            iter_++;
        }
        m_cbuff_.clear();
        m_size_ = 0;
    }

    size_t size() const
    {
        return m_size_;
    }

public:

    CBuffer& buffer()
    {
        return m_cbuff_;
    }

    operator CBuffer& ()
    {
        return m_cbuff_;
    }

    GECBuffer& operator <<(const char *p_)
    {
        size_t n_ = strlen(p_);
        m_size_ += n_;
        size_t i_ = 0;
        while(n_ >= BODY_LENGTH)
        {
            char *b_ = (char*) m_pool_.malloc();
            memcpy(b_ , p_ + i_, BODY_LENGTH);
            m_cbuff_.push_back(boost::asio::buffer(b_, BODY_LENGTH));
            i_ += BODY_LENGTH;
            n_ -= BODY_LENGTH;
        }

        if(n_ > 0)
        {
            char *b_ = (char*) m_pool_.malloc();
            memcpy(b_ , p_ + i_, n_);
            m_cbuff_.push_back(boost::asio::buffer(b_, n_));
        }
        return *this;
    }

    GECBuffer& operator <<(const std::string &str_)
    {
        size_t n_ = str_.length();
        m_size_ += n_;
        size_t i_ = 0;
        while(n_ >= BODY_LENGTH)
        {
            char *b_ = (char*) m_pool_.malloc();
            memcpy(b_ , str_.c_str() + i_, BODY_LENGTH);
            m_cbuff_.push_back(boost::asio::buffer(b_, BODY_LENGTH));
            i_ += BODY_LENGTH;
            n_ -= BODY_LENGTH;
        }

        if(n_ > 0)
        {
            char *b_ = (char*) m_pool_.malloc();
            memcpy(b_ , str_.c_str() + i_, n_);
            m_cbuff_.push_back(boost::asio::buffer(b_, n_));
        }
        return *this;
    }

    void* fill_buffer(size_t s_)
    {
        void *res_;
        if(s_ <= BODY_LENGTH )
        {
            m_size_ += s_;
            res_ = m_pool_.malloc();
            m_cbuff_.push_back(boost::asio::const_buffer(res_, s_));
        }
        return res_;
    }
private:
    CBuffer                                         m_cbuff_;
    size_t                                          m_size_;
//    static size_t                                   s_count_;
    boost::pool<>                                   m_pool_;
};

}

#endif // GEBUFFER_H
