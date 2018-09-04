#ifndef _WIN32_H
#define _WIN32_H
namespace Asura
{
typedef int _ADDR;
typedef int _PTR;
typedef int _FUNC;

typedef char            _b1;
typedef short           _b2;
typedef int             _b4;
typedef unsigned int    _u4;
typedef unsigned char   _u1;


/**
 * /brief message code
 *
 * 0~99         ok
 * 100~199      bad request
 * 200~299      system error
 *
 */

#define G_OK            1
#define G_CONTINUE      2
#define G_BAD_REQUEST   101
#define G_FAILD         201


/**
 *
 * /brief message type
 *
 */
#define A_COM        0x01
#define A_RES        0x02
#define A_COMFIRM    0x10
#define A_USER       0x60

#define R_RESQUEST_CLOSE     0x20
#define R_COMFIRM_CLOSE      0x21
#define R_NORMAL             0x10

//#define HEAT    0x003


/**
 *
 * /brief return code
 *
 */
#define WRITE_CONTINUE      1
#define WRITE_FINISH        0
#define PARSE_FINISH        0
#define PARSE_ERROR         1
#define SYSTEM_ERROR        -1




#define E_OK                     0
#define E_INVALID_HEADER        -101
#define E_INVALID_COMMAND       -201
#define E_PARSE_ERROR           -301
#define E_PENDINGS               1




#define E_ERROR                 -1
#define E_CLOSED                -2

#define COMMAND_DECOLLATOR      -1
#define PARAM_DECOLLATOR        -2



/**
 *
 * /brief message header
 *
 */
typedef struct _msg_header
{
    _b2     version;
    _b2     protocol;
    _b2     header;
    _b2     msg_type;
    _b2     reserved2;
    _b2     return_code;
    _u4     length;
    _b4     magic;
}msg_header;


#define MSG_HEADER  sizeof(msg_header)
#define MSG_MAGIC   0XDACBCABD
#define BODY_LENGTH 8192


}


#endif // _WIN32_H
