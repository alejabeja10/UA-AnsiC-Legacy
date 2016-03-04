/* ========================================================================
 * Copyright (c) 2005-2009 The OPC Foundation, Inc. All rights reserved.
 *
 * OPC Foundation MIT License 1.00
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * The complete license agreement can be found here:
 * http://opcfoundation.org/License/MIT/1.00/
 * ======================================================================*/

#ifndef _OPCUA_CONFIG_H_
#define _OPCUA_CONFIG_H_ 1

/*============================================================================
 * source configuration switches
 *===========================================================================*/
#define OPCUA_CONFIG_YES 1
#define OPCUA_CONFIG_NO  0

/*============================================================================
 * definition of flag indicating if openssl is available or not
 *===========================================================================*/
#define OPCUA_HAVE_OPENSSL                          OPCUA_CONFIG_YES

/*============================================================================
 * modules (removing unneeded modules reduces codesize)
 *===========================================================================*/
/** @brief Define or undefine to enable or disable client functionality */
#define OPCUA_HAVE_CLIENTAPI                        1
/** @brief Define or undefine to enable or disable server functionality */
#define OPCUA_HAVE_SERVERAPI                        1
/** @brief Define or undefine to enable or disable threadpool support. Required if secure listener shall use it. */
#define OPCUA_HAVE_THREADPOOL                       1
/** @brief define or undefine to enable or disable the memory stream module. */
#define OPCUA_HAVE_MEMORYSTREAM                     1
/** @brief define or undefine to enable or disable the soap and http support. */
/*#define OPCUA_HAVE_SOAPHTTP                         1*/
/** @brief define or undefine to enable or disable the https support. */
#define OPCUA_HAVE_HTTPS                            1


/* * @brief AUTOMATIC; activate additional modules required by soap/http */
#ifdef OPCUA_HAVE_SOAPHTTP
# define OPCUA_HAVE_HTTPAPI                         1
# define OPCUA_HAVE_XMLPARSER                       1
# define OPCUA_HAVE_BASE64                          1
# ifndef OPCUA_HAVE_MEMORYSTREAM
#  error SOAP/HTTP UA-SC transport profile requires memory stream!
# endif /* OPCUA_HAVE_MEMORYSTREAM */
#endif /* OPCUA_HAVE_SOAPHTTP */

/* * @brief AUTOMATIC; activate additional modules required by https */
#ifdef OPCUA_HAVE_HTTPS
# define OPCUA_HAVE_HTTPSAPI                        1
# define OPCUA_HAVE_BASE64                          1
#endif /* OPCUA_HAVE_HTTPS */

/*============================================================================
 * dotnet native stack wrapper requires this extension
 *===========================================================================*/
#define OPCUA_SUPPORT_PREENCODED_MESSAGES

/*============================================================================
 * general
 *===========================================================================*/
/** @brief Prefer the use of inline functions instead of function calls (see opcua_string) */
#define OPCUA_PREFERINLINE                          OPCUA_CONFIG_NO

/** @brief Enable the use of safe functions like defined with VS2005 and higher. */
#if defined(_MSC_VER) && (_MSC_VER >= 1400 )
#define OPCUA_USE_SAFE_FUNCTIONS                    OPCUA_CONFIG_YES
#else
#define OPCUA_USE_SAFE_FUNCTIONS                    OPCUA_CONFIG_NO
#endif

/** @brief Some temporary optimizations, to test their impact on performance. */
#define OPCUA_PERFORMANCE_OPTIMIZATION_TESTING      OPCUA_CONFIG_NO

/*============================================================================
 * threading
 *===========================================================================*/
/** @brief Run in multi thread mode. Each listen socket gets its own thread. */
#define OPCUA_MULTITHREADED                         OPCUA_CONFIG_YES

/** @brief Use access synchronization. Required for OPCUA_MULTITHREADED */
#define OPCUA_USE_SYNCHRONISATION                   OPCUA_CONFIG_YES

#if OPCUA_MULTITHREADED
#if !OPCUA_USE_SYNCHRONISATION
#error MT needs SYNCHRO!
#endif
#endif

/** @brief Using a special mutex struct with debug information. */
#define OPCUA_MUTEX_ERROR_CHECKING                  OPCUA_CONFIG_NO

/*============================================================================
 * timer
 *===========================================================================*/
/** @brief Maximum amount of milliseconds to stay inactive in the timer. */
#define OPCUA_TIMER_MAX_WAIT                        1000

/*============================================================================
 * serializer constraints
 *===========================================================================*/
/** @brief The maximum size of memory allocated by a serializer */
#define OPCUA_SERIALIZER_MAXALLOC 16777216

/** @brief Maximum String Length accepted */
#define OPCUA_ENCODER_MAXSTRINGLENGTH               ((OpcUa_UInt32)16777216)

/** @brief Maximum Array Length accepted */
#define OPCUA_ENCODER_MAXARRAYLENGTH                ((OpcUa_UInt32)65536)

/** @brief Maximum ByteString Length accepted */
#define OPCUA_ENCODER_MAXBYTESTRINGLENGTH           ((OpcUa_UInt32)16777216)

/** @brief Maximum Message Length accepted */
#define OPCUA_ENCODER_MAXMESSAGELENGTH              ((OpcUa_UInt32)16777216)

/** @brief Maximum Encodable object recursion depth */
#define OPCUA_ENCODER_MAXRECURSIONDEPTH             ((OpcUa_UInt32)100)

/*============================================================================
 * serializer checks
 *===========================================================================*/
/** @brief OpcUa_True or OpcUa_False; switches checks on or off; dont use with chunking enabled. */
#define OPCUA_SERIALIZER_CHECKLENGTHS               OpcUa_False

/*============================================================================
 * thread pool
 *===========================================================================*/
/** @brief Allow to dynamically create threads to prevent delay in queue if no static thread is free. Not recommended! */
#define OPCUA_THREADPOOL_EXPANSION                  OPCUA_CONFIG_NO

/** @brief Time in milliseconds after which a worker thread looks for further orders. Affects shutdown time. */
#define OPCUA_THREADPOOL_RELOOPTIME                 500

/*============================================================================
 * server call dispatching
 *===========================================================================*/
/** @brief Put fully received requests into the servers thread job queue. (Be carefull with the blocking setting!) */
#define OPCUA_SECURELISTENER_SUPPORT_THREADPOOL     OPCUA_CONFIG_NO

/** @brief Minimum number of threads (static) in the securelisteners job queue. */
#define OPCUA_SECURELISTENER_THREADPOOL_MINTHREADS  5

/** @brief Maximum number of threads (static) in the securelisteners job queue. */
#define OPCUA_SECURELISTENER_THREADPOOL_MAXTHREADS  5

/** @brief Maximum total number of jobs being processed by the thread pool. */
#define OPCUA_SECURELISTENER_THREADPOOL_MAXJOBS     20

/*============================================================================
 * tracer
 *===========================================================================*/
/** @brief Enable output to trace device. */
#ifndef OPCUA_TRACE_ENABLE
#define OPCUA_TRACE_ENABLE                          OPCUA_CONFIG_NO
#endif

/** @brief Enable output to trace device. */
#define OPCUA_TRACE_MAXLENGTH                       200

/** @brief output the messages in errorhandling macros; requires OPCUA_ERRORHANDLING_OMIT_METHODNAME set to OPCUA_CONFIG_NO */
#define OPCUA_TRACE_ERROR_MACROS                    OPCUA_CONFIG_NO

/** @brief Omit the methodname in initialize status macro. */
#define OPCUA_ERRORHANDLING_OMIT_METHODNAME         OPCUA_CONFIG_NO

/** @brief Add __LINE__ and __FILE__ information to the trace line. */
#define OPCUA_TRACE_FILE_LINE_INFO                  OPCUA_CONFIG_NO

/*============================================================================
 * security
 *===========================================================================*/
/** @brief The maximum lifetime of a secure channel security token in milliseconds. */
#define OPCUA_SECURITYTOKEN_LIFETIME_MAX            3600000

/** @brief The minimum lifetime of a secure channel security token in milliseconds. */
#define OPCUA_SECURITYTOKEN_LIFETIME_MIN            600000

/** @brief The interval in which securechannels get checked for lifetime timeout in milliseconds. */
#define OPCUA_SECURELISTENER_WATCHDOG_INTERVAL      10000

/** @brief How many milliseconds a passive secure channel may wait for its activation. */
#define OPCUA_SECURELISTENER_CHANNELTIMEOUT         10000

/** @brief Shall the secureconnection validate the server certificate given by the client application? */
#define OPCUA_SECURECONNECTION_VALIDATE_SERVERCERT  OPCUA_CONFIG_NO

/*============================================================================
 * networking
 *===========================================================================*/
/** @brief The standard port for the opc.tcp protocol, defined in part 6. */
#define OPCUA_TCP_DEFAULT_PORT                      4840

/** @brief The standard port for the http protocol. */
#define OPCUA_HTTP_DEFAULT_PORT                     80

/** @brief Request this buffersize for the sockets sendbuffer. */
#define OPCUA_P_SOCKET_SETTCPRCVBUFFERSIZE          OPCUA_CONFIG_YES
#define OPCUA_P_TCPRCVBUFFERSIZE                    65536
#define OPCUA_P_SOCKET_SETTCPSNDBUFFERSIZE          OPCUA_CONFIG_YES
#define OPCUA_P_TCPSNDBUFFERSIZE                    65536

/** @brief default buffer(chunk sizes) (also max value) */
#define OPCUA_TCPLISTENER_DEFAULTCHUNKSIZE          ((OpcUa_UInt32)65536)
#define OPCUA_TCPCONNECTION_DEFAULTCHUNKSIZE        ((OpcUa_UInt32)65536)

/** @brief if defined, the tcpstream expects the write call to block until all data is sent */
#define OPCUA_TCPSTREAM_BLOCKINGWRITE               OPCUA_CONFIG_NO

/** @brief The maximum number of client connections supported by a tcp listener. (maybe one reserved, see below) */
#ifndef OPCUA_TCPLISTENER_MAXCONNECTIONS
#define OPCUA_TCPLISTENER_MAXCONNECTIONS            100
#endif

/** @brief The default timeout for server sockets */
#define OPCUA_TCPLISTENER_TIMEOUT                   600000

/** @brief Reserve one of the OPCUA_TCPLISTENER_MAXCONNECTIONS for an "MaxConnectionsReached" error channel?. */
#define OPCUA_TCPLISTENER_USEEXTRAMAXCONNSOCKET     OPCUA_CONFIG_NO

/** @brief The maximum number of sockets supported by a socket manager. */
#ifndef OPCUA_P_SOCKETMANAGER_NUMBEROFSOCKETS
#define OPCUA_P_SOCKETMANAGER_NUMBEROFSOCKETS       110
#endif
/* test with 2000 connections #define OPCUA_P_SOCKETMANAGER_NUMBEROFSOCKETS       4010 */

/** @brief The maximum number of socket managers in multithreading config, supported by the socket module. */
#ifndef OPCUA_SOCKET_MAXMANAGERS
#define OPCUA_SOCKET_MAXMANAGERS                    110
#endif
/* test with 2000 connections #define OPCUA_SOCKET_MAXMANAGERS                    4010 */

/** @brief the time interval in msec at which the secureconnection checks for timeouts. */
#define OPCUA_SECURECONNECTION_TIMEOUTINTERVAL      1000

/** @brief Maximum number of pending messages before the server starts to block. */
#define OPCUA_SECURECONNECTION_MAXPENDINGMESSAGES   10

/*============================================================================
 * HTTPS protocol
 *===========================================================================*/
/** @brief Maximum number of receive buffers per message. */
#ifndef OPCUA_HTTPS_MAX_RECV_BUFFER_COUNT
# define OPCUA_HTTPS_MAX_RECV_BUFFER_COUNT          100
#endif /* OPCUA_HTTPS_MAX_RECV_BUFFER_COUNT */

/** @brief Maximum size of a receive buffer. */
#ifndef OPCUA_HTTPS_MAX_RECV_BUFFER_LENGTH
# define OPCUA_HTTPS_MAX_RECV_BUFFER_LENGTH         65536
#endif /* OPCUA_HTTPS_MAX_RECV_BUFFER_LENGTH */

/** @brief Calculated accepted (total) size limit of a received message. */
#ifndef OPCUA_HTTPS_MAX_RECV_MESSAGE_LENGTH
# define OPCUA_HTTPS_MAX_RECV_MESSAGE_LENGTH        (OPCUA_HTTPS_MAX_RECV_BUFFER_COUNT*OPCUA_HTTPS_MAX_RECV_BUFFER_LENGTH)
#endif /* OPCUA_HTTPS_MAX_RECV_MESSAGE_LENGTH */

/** @brief Maximum length of a single HTTP header line. If a message exceeds this limit, 414 is returned. */
#ifndef OPCUA_HTTPS_MAX_RECV_HEADER_LINE_LENGTH
# define OPCUA_HTTPS_MAX_RECV_HEADER_LINE_LENGTH    1024
#endif /* OPCUA_HTTPS_MAX_RECV_HEADER_LENGTH */

/** @brief Maximum accepted size of an HTTP header. If a message exceeds this limit, 414 is returned. */
#ifndef OPCUA_HTTPS_MAX_RECV_HEADER_LENGTH
# define OPCUA_HTTPS_MAX_RECV_HEADER_LENGTH         1024
#endif /* OPCUA_HTTPS_MAX_RECV_HEADER_LENGTH */

/** @brief Maximum accepted number of HTTP headers in a received message. If a message exceeds this limit, 414 is returned. */
#ifndef OPCUA_HTTPS_MAX_RECV_HEADER_COUNT
# define OPCUA_HTTPS_MAX_RECV_HEADER_COUNT          20
#endif /* OPCUA_HTTPS_MAX_RECV_HEADER_COUNT */


/** @brief Maximum number of send buffers (result in HTTP chunks) per message. */
#ifndef OPCUA_HTTPS_MAX_SEND_CHUNK_COUNT
# define OPCUA_HTTPS_MAX_SEND_CHUNK_COUNT           50
#endif /* OPCUA_HTTPS_MAX_SEND_CHUNK_COUNT */

/** @brief Maximum size of a send chunk (equals HTTP chunk size). */
#ifndef OPCUA_HTTPS_MAX_SEND_CHUNK_LENGTH
# define OPCUA_HTTPS_MAX_SEND_CHUNK_LENGTH          262144
#endif /* OPCUA_HTTPS_MAX_SEND_CHUNK_LENGTH */

/** @brief Maximum size of outgoing HTTP header. (also includes chunk header) */
#ifndef OPCUA_HTTPS_MAX_SEND_HEADER_LENGTH
# define OPCUA_HTTPS_MAX_SEND_HEADER_LENGTH         350
#endif /* OPCUA_HTTPS_MAX_SEND_HEADER_LENGTH */

/** @brief Maximum size of outgoing HTTP footer. */
#ifndef OPCUA_HTTPS_MAX_SEND_FOOTER_LENGTH
# define OPCUA_HTTPS_MAX_SEND_FOOTER_LENGTH         3
#endif /* OPCUA_HTTPS_MAX_SEND_FOOTER_LENGTH */

/** @brief Calculated size of a send buffer. */
#ifndef OPCUA_HTTPS_MAX_SEND_BUFFER_LENGTH
# define OPCUA_HTTPS_MAX_SEND_BUFFER_LENGTH         (OPCUA_HTTPS_MAX_SEND_HEADER_LENGTH + OPCUA_HTTPS_MAX_SEND_CHUNK_LENGTH + OPCUA_HTTPS_MAX_SEND_FOOTER_LENGTH)
#endif /* OPCUA_HTTPS_MAX_SEND_BUFFER_LENGTH */

/** @brief Calculated size of outgoing message. */
#ifndef OPCUA_HTTPS_MAX_SEND_MESSAGE_LENGTH
# define OPCUA_HTTPS_MAX_SEND_MESSAGE_LENGTH        (OPCUA_HTTPS_MAX_SEND_CHUNK_COUNT*OPCUA_HTTPS_MAX_SEND_BUFFER_LENGTH)
#endif /* OPCUA_HTTPS_MAX_SEND_MESSAGE_LENGTH */

/** @brief the time interval in msec at which the https connection checks for timeouts. */
#ifndef OPCUA_HTTPSCONNECTION_TIMEOUTINTERVAL
# define OPCUA_HTTPSCONNECTION_TIMEOUTINTERVAL      1000
#endif /* OPCUA_HTTPSCONNECTION_TIMEOUTINTERVAL */

/** @brief the maximum idle time on a keep-alive https connection. */
#ifndef OPCUA_HTTPSCONNECTION_KEEP_ALIVE_TIMEOUT
# define OPCUA_HTTPSCONNECTION_KEEP_ALIVE_TIMEOUT   60000
#endif /* OPCUA_HTTPSCONNECTION_KEEP_ALIVE_TIMEOUT */

/** @brief Defines the number of maximum pending requests/connection to a server. */
#ifndef OPCUA_HTTPS_CONNECTION_MAXPENDINGREQUESTS
# define OPCUA_HTTPS_CONNECTION_MAXPENDINGREQUESTS  10
#endif /* OPCUA_HTTPS_CONNECTION_MAXPENDINGREQUESTS */

/** @brief Defines max number of sockets. (a single client needs one socket per parallel request!) */
#ifndef OPCUA_HTTPSLISTENER_MAXCONNECTIONS
# define OPCUA_HTTPSLISTENER_MAXCONNECTIONS         50
#endif /* OPCUA_HTTPSLISTENER_MAXCONNECTIONS */

/** @brief The standard port for the https protocol. */
#ifndef OPCUA_HTTPS_DEFAULT_PORT
# define OPCUA_HTTPS_DEFAULT_PORT                   443
#endif /* OPCUA_HTTP_DEFAULT_PORT */

/** @brief if defined, the httpsstream expects the write call to block until all data is sent */
#ifndef OPCUA_HTTPSSTREAM_BLOCKINGWRITE
# define OPCUA_HTTPSSTREAM_BLOCKINGWRITE            OPCUA_CONFIG_NO
#endif /* OPCUA_HTTPSSTREAM_BLOCKINGWRITE */

/*============================================================================
 * type support
 *===========================================================================*/
/** @brief type exclusion configuration */
#include "opcua_exclusions.h"

#endif /* _OPCUA_CONFIG_H_ */
