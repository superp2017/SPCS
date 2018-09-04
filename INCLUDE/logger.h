#ifndef LOGGER_H
#define LOGGER_H
#include <map>
#include <string>
#include <stdio.h>
#include <boost/thread/mutex.hpp>
#include <QtCore/qglobal.h>
#include <QDebug>
#include <boost/thread/mutex.hpp>
#include <taskmanager.h>

#if defined(LOGGER_LIBRARY)
#  define LOGGERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LOGGERSHARED_EXPORT Q_DECL_IMPORT
#endif


enum Level{LOG_MESSAGE, LOG_DEBUG, LOG_ERROR};

class Logger;

typedef void (*printer)(Logger * logger, const char *msg);

class LOGGERSHARED_EXPORT Logger
{
private:
    Logger(std::string &name, Level lv = LOG_MESSAGE);
    ~Logger();

public:
    static Logger *instance(std::string &name = std::string(""));

    void console(bool b_ = true){ m_console_ = b_; }

    void log(int lv, const char *fmt, ...);

    void register_printer(int lv, printer pnt);

    void print(std::string &msg);

    std::string name(){return m_name_;}

    void toLevel(Level lv){ m_level = lv;}

    void stop();

protected:
    Level   m_level;


friend class InitLogger;
private:
    static std::map<std::string, Logger*>       s_loggers;

private:
    std::map<int, printer>                      m_printers;
    FILE                                        *m_file;
    boost::mutex                                m_mutex;
    std::string                                 m_name_;
    bool                                        m_console_;
};

#endif // LOGGER_H
