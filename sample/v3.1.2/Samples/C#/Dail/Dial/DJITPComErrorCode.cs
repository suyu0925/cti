using System;
using System.Collections.Generic;
using System.Text;

namespace DJKeygoe
{
    using DJ_U32 = UInt32;

    class DJITPComErrorCode
    {
           //////////////  These error code value is compatible with socket standard  //////////////
        public const DJ_U32 DJ_EINTR                     = 10004 ;    // Interrupted system call
	    public const DJ_U32 DJ_EBADF                    = 10009 ;    // Bad file number
	    public const DJ_U32 DJ_EACCES                  = 10013;     // Permission denied
	    public const DJ_U32 DJ_EFAULT                   = 10014;     // Bad address
	    public const DJ_U32 DJ_EINVAL                   = 10022;     // Invalid argument
	    public const DJ_U32 DJ_EMFILE                   = 10024;     // Too many open files
	    public const DJ_U32 DJ_EWOULDBLOCK      = 10035;     // Resource temporarily unavailable
	    public const DJ_U32 DJ_EINPROGRESS        = 10036;     // Operation now in progress
	    public const DJ_U32 DJ_EALREADY              = 10037;     // Operation already in progress
	    public const DJ_U32 DJ_ENOTSOCK             = 10038;     // Socket operation on nonsocket
	    public const DJ_U32 DJ_EDESTADDRREQ     = 10039;     // Destination address required
	    public const DJ_U32 DJ_EMSGSIZE              = 10040;     // Message too long
	    public const DJ_U32 DJ_EPROTOTYPE          = 10041;     // Protocol wrong type for socket
	    public const DJ_U32 DJ_ENOPROTOOPT       = 10042;     // Bad protocol option
	    public const DJ_U32 DJ_EPROTONOSUPPORT   = 10043;     // Protocol not supported
	    public const DJ_U32 DJ_ESOCKTNOSUPPORT   = 10044;     // Socket type not supported
	    public const DJ_U32 DJ_EOPNOTSUPPORT       = 10045;     // Operation not supported on transport endpoint
	    public const DJ_U32 DJ_EPFNOSUPPORT         = 10046;     // Protocol family not supported
	    public const DJ_U32 DJ_EAFNOSUPPORT         = 10047; 	   // Address family not supported by protocol family
	    public const DJ_U32 DJ_EADDRINUSE              = 10048;     // Address already in use
	    public const DJ_U32 DJ_EADDRNOTAVAIL        = 10049;     // Cannot assign requested address
	    public const DJ_U32 DJ_ENETDOWN                = 10050;     // Network is down
	    public const DJ_U32 DJ_ENETUNREACH           = 10051;     // Network is unreachable
	    public const DJ_U32 DJ_ENETRESET                = 10052;     // Network dropped connection on reset
	    public const DJ_U32 DJ_ECONNABORTED        = 10053;     // Software caused connection abort
	    public const DJ_U32 DJ_ECONNRESET             = 10054;     // Connection reset by peer
	    public const DJ_U32 DJ_ENOBUFS                   = 10055;     // No buffer space available
	    public const DJ_U32 DJ_EISCONN                   = 10056;     // Socket is already connected
	    public const DJ_U32 DJ_ENOTCONN                = 10057;     // Socket is not connected
	    public const DJ_U32 DJ_ESHUTDOWN             = 10058 ;    // Cannot send after socket shutdown
	    public const DJ_U32 DJ_ETIMEDOUT               = 10060;     // Connection timed out
	    public const DJ_U32 DJ_ECONNREFUSED        = 10061;     // Connection refused
	    public const DJ_U32 DJ_EHOSTDOWN             = 10064;     // Host is down
	    public const DJ_U32 DJ_EHOSTUNREACH        = 10065;     // No route to host




            ////////////////////  These error code value of our own system  /////////////////////////
        public const DJ_U32 DJ_ITPCOM_ERRBASE    = 20000;     // Start error code

        public const DJ_U32 DJ_EPARAMETER         = (DJ_ITPCOM_ERRBASE + 1);  // Parameter error
        public const DJ_U32 DJ_ENODATA               = (DJ_ITPCOM_ERRBASE + 2);  // Receive no data or enough data
        public const DJ_U32 DJ_EMEMALLOC          = (DJ_ITPCOM_ERRBASE + 3);  // Allocate memory error
        public const DJ_U32 DJ_EMAXSOCKET        = (DJ_ITPCOM_ERRBASE + 4);  // Have set up  128 socket (max)
        public const DJ_U32 DJ_EAUTHORIZE         = (DJ_ITPCOM_ERRBASE + 5);  // Authorization not passed
        public const DJ_U32 DJ_EPKGFLAG             = (DJ_ITPCOM_ERRBASE + 6);  // Package flag error
        public const DJ_U32 DJ_ESENDSELECT       = (DJ_ITPCOM_ERRBASE + 7);  // Before send select error
        public const DJ_U32 DJ_EREMOTEDOWN    = (DJ_ITPCOM_ERRBASE + 8);  // Remote connect gracefully closed
        public const DJ_U32 DJ_EPKGSIZE              = (DJ_ITPCOM_ERRBASE + 9);  // Package size error(max size 8K)
    }
}
