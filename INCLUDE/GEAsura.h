#ifndef GEASURA_H
#define GEASURA_H
#include <boost/pool/pool.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/function.hpp>
#include <_win32.h>
#include "GEMessage.h"
#include "GEResult.h"
#include "GEOperator.h"

namespace Asura
{

class GEReadHook
{
public:
    virtual int operator()(GEMessage *, GEResult *) = 0;
    virtual ~GEReadHook(){}
};

class GEWriteHook
{
public:
    virtual int operator()(GEResult *) = 0;
};

//template <class T_>
//class GEReadHookImpl : public GEReadHook
//{
//public:
//    typedef T_                  Hook;
//public:
//    GEReadHookImpl(Hook hook_)
//    {
//        m_hook_ = hook_;
//    }
//    virtual void operator()(GEMessage *msg_, GEResult *res_)
//    {
//        return hook_(msg_,res_);
//    }
//private:
//    Hook                        m_hook_;
//};


class GEAsura
{
public:

    typedef GEMessage::ReadHeader       ReadHeader;
    typedef GEMessage::ReadBody         ReadBody;
    typedef GEResult::WriteHeader       WriteHeader;
    typedef GEResult::WriteBody         WriteBody;
    typedef GEReadHook*                 GEReadHookPtr;
    typedef GEWriteHook*                GEWriteHookPtr;
    typedef GEMessage*                  GEMessage_ptr;
    typedef GEResult*                   GEResult_ptr;
public:
    GEAsura()
        :m_pool_(BODY_LENGTH),
          m_read_hook_(0),
          m_write_hook_(0),
          m_message_ptr_(0),
          m_result_ptr_(0)
    {}
    virtual ~GEAsura()
    {
        if(m_read_hook_) delete m_read_hook_;
        if(m_write_hook_) delete m_write_hook_;
    }

public:
    //uniform memory alloc
    void* malloc()
    {
        return m_pool_.malloc();
    }
    void free(void* p_)
    {
        m_pool_.free(p_);
    }

    //register read hook
    void register_read_hook(GEReadHookPtr hook_)
    {
        if(m_read_hook_) delete m_read_hook_;
        m_read_hook_ = hook_;
    }
    GEReadHookPtr read_hook()
    {
        return m_read_hook_;
    }
    void register_write_hook(GEWriteHookPtr hook_)
    {
        if(m_write_hook_) delete m_write_hook_;
        m_write_hook_ = hook_;
    }
    GEWriteHookPtr write_hook()
    {
        return m_write_hook_;
    }


    void register_message_ptr(GEMessage_ptr msg_)
    {
        m_message_ptr_ = msg_;
    }
    GEMessage_ptr message()
    {
        return m_message_ptr_;
    }
    void register_result_ptr(GEResult_ptr res_)
    {
        m_result_ptr_ = res_;
    }
    GEResult_ptr result()
    {
        return m_result_ptr_;
    }

    void reset()
    {
        m_message_ptr_->reset();
        m_result_ptr_->reset();
    }

    virtual std::string client_message(){ return std::string();}

protected:
    boost::pool<>           m_pool_;
    boost::mutex            m_mutex_;
    GEReadHookPtr           m_read_hook_;
    GEWriteHookPtr          m_write_hook_;
    GEMessage_ptr           m_message_ptr_;
    GEResult_ptr            m_result_ptr_;
};

}

#endif // GEASURA_H
