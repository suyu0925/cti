package DJKeygoe;

public class DJITPComErrorCode {
	public static final int    DJ_ITPCOM_ERRBASE     = 20000;     // Start error code

	public static final int    DJ_EPARAMETER         = (DJ_ITPCOM_ERRBASE + 1);  // Parameter error
	public static final int    DJ_ENODATA            = (DJ_ITPCOM_ERRBASE + 2);  // Receive no data or enough data
	public static final int    DJ_EMEMALLOC          = (DJ_ITPCOM_ERRBASE + 3);  // Allocate memory error
	public static final int    DJ_EMAXSOCKET         = (DJ_ITPCOM_ERRBASE + 4);  // Have set up  128 socket (max)
	public static final int    DJ_EAUTHORIZE         = (DJ_ITPCOM_ERRBASE + 5);  // Authorization not passed
	public static final int    DJ_EPKGFLAG           = (DJ_ITPCOM_ERRBASE + 6);  // Package flag error
	public static final int    DJ_ESENDSELECT        = (DJ_ITPCOM_ERRBASE + 7);  // Before send select error
	public static final int    DJ_EREMOTEDOWN        = (DJ_ITPCOM_ERRBASE + 8);  // Remote connect gracefully closed
	public static final int    DJ_EPKGSIZE           = (DJ_ITPCOM_ERRBASE + 9);  // Package size error(max size 8K)
}

class DJITPComErrorCodeWindows{
	public static final int   DJ_EINTR             = 10004;     // Interrupted system call
	public static final int   DJ_EBADF             = 10009;     // Bad file number
	public static final int   DJ_EACCES            = 10013;     // Permission denied
	public static final int   DJ_EFAULT            = 10014;     // Bad address
	public static final int   DJ_EINVAL            = 10022;     // Invalid argument
	public static final int   DJ_EMFILE            = 10024;     // Too many open files
	public static final int   DJ_EWOULDBLOCK       = 10035;     // Resource temporarily unavailable
	public static final int   DJ_EINPROGRESS       = 10036;     // Operation now in progress
	public static final int   DJ_EALREADY          = 10037;     // Operation already in progress
	public static final int   DJ_ENOTSOCK          = 10038;     // Socket operation on nonsocket
	public static final int   DJ_EDESTADDRREQ      = 10039;     // Destination address required
	public static final int   DJ_EMSGSIZE          = 10040;     // Message too long
	public static final int   DJ_EPROTOTYPE        = 10041;     // Protocol wrong type for socket
	public static final int   DJ_ENOPROTOOPT       = 10042;    // Bad protocol option
	public static final int   DJ_EPROTONOSUPPORT   = 10043;     // Protocol not supported
	public static final int   DJ_ESOCKTNOSUPPORT   = 10044;     // Socket type not supported
	public static final int   DJ_EOPNOTSUPPORT     = 10045;     // Operation not supported on transport endpoint
	public static final int   DJ_EPFNOSUPPORT      = 10046;     // Protocol family not supported
	public static final int   DJ_EAFNOSUPPORT      = 10047; 	   // Address family not supported by protocol family
	public static final int   DJ_EADDRINUSE        = 10048;     // Address already in use
	public static final int   DJ_EADDRNOTAVAIL     = 10049;     // Cannot assign requested address
	public static final int   DJ_ENETDOWN          = 10050;     // Network is down
	public static final int   DJ_ENETUNREACH       = 10051;     // Network is unreachable
	public static final int   DJ_ENETRESET         = 10052;     // Network dropped connection on reset
	public static final int   DJ_ECONNABORTED      = 10053;     // Software caused connection abort
	public static final int   DJ_ECONNRESET        = 10054;     // Connection reset by peer
	public static final int   DJ_ENOBUFS           = 10055;     // No buffer space available
	public static final int   DJ_EISCONN           = 10056;     // Socket is already connected
	public static final int   DJ_ENOTCONN          = 10057;     // Socket is not connected
	public static final int   DJ_ESHUTDOWN         = 10058;     // Cannot send after socket shutdown
	public static final int   DJ_ETIMEDOUT         = 10060;     // Connection timed out
	public static final int   DJ_ECONNREFUSED      = 10061;     // Connection refused
	public static final int   DJ_EHOSTDOWN         = 10064;     // Host is down
	public static final int   DJ_EHOSTUNREACH      = 10065;     // No route to host
}
	
class DJITPComErrorCodeLinux{
	public static final int   DJ_EINTR             = 4;         // Interrupted system call
	public static final int   DJ_EBADF             = 9;         // Bad file number
	public static final int   DJ_EACCES            = 13;        // Permission denied
	public static final int   DJ_EFAULT            = 14;        // Bad address
	public static final int   DJ_EINVAL            = 22;        // Invalid argument
	public static final int   DJ_EMFILE            = 24;        // Too many open files
	public static final int   DJ_EWOULDBLOCK       = 11;        // Resource temporarily unavailable
	public static final int   DJ_EINPROGRESS       = 115;       // Operation now in progress
	public static final int   DJ_EALREADY          = 114;       // Operation already in progress
	public static final int   DJ_ENOTSOCK          = 88;        // Socket operation on nonsocket
	public static final int   DJ_EDESTADDRREQ      = 89;        // Destination address required
	public static final int   DJ_EMSGSIZE          = 90;        // Message too long
	public static final int   DJ_EPROTOTYPE        = 91;        // Protocol wrong type for socket
	public static final int   DJ_ENOPROTOOPT       = 92;        // Bad protocol option
	public static final int   DJ_EPROTONOSUPPORT   = 93;        // Protocol not supported	
	public static final int   DJ_ESOCKTNOSUPPORT   = 94;        // Socket type not supported
	public static final int   DJ_EOPNOTSUPPORT     = 95;        // Operation not supported on transport endpoint
	public static final int   DJ_EPFNOSUPPORT      = 96;        // Protocol family not supported
	public static final int   DJ_EAFNOSUPPORT      = 97 ;	     // Address family not supported by protocol family
	public static final int   DJ_EADDRINUSE        = 98 ;       // Address already in use
	public static final int   DJ_EADDRNOTAVAIL     = 99 ;       // Cannot assign requested address
	public static final int   DJ_ENETDOWN          = 100;       // Network is down
	public static final int   DJ_ENETUNREACH       = 101;       // Network is unreachable
	public static final int   DJ_ENETRESET         = 102;       // Network dropped connection on reset
	public static final int   DJ_ECONNABORTED      = 103;       // Software caused connection abort
	public static final int   DJ_ECONNRESET        = 104;       // Connection reset by peer
	public static final int   DJ_ENOBUFS           = 105;       // No buffer space available
	public static final int   DJ_EISCONN           = 106 ;      // Socket is already connected
	public static final int   DJ_ENOTCONN          = 107 ;      // Socket is not connected
	public static final int   DJ_ESHUTDOWN         = 108 ;      // Cannot send after socket shutdown
	public static final int   DJ_ETIMEDOUT         = 110;       // Connection timed out
	public static final int   DJ_ECONNREFUSED      = 111 ;      // Connection refused
	public static final int   DJ_EHOSTDOWN         = 112 ;      // Host is down
	public static final int   DJ_EHOSTUNREACH      = 113 ;      // No route to host
}