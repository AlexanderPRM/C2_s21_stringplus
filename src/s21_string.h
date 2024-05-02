#include <stdlib.h>

#include "s21_sprintf.h"

/* Memory functions */
void *s21_memchr(const void *str, int c, size_t n);
int s21_memcmp(const void *str1, const void *str2, size_t n);
void *s21_memcpy(void *dest, const void *src, size_t n);
void *s21_memset(void *src, int c, size_t n);

/* String functions */
char *s21_strncat(char *dest, const char *src, size_t n);
char *s21_strchr(const char *src, int c);
int s21_strncmp(const char *str1, const char *str2, size_t n);
char *s21_strncpy(char *dest, const char *src, size_t n);
size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

/* Errors */
#define EPERM 1   /* Operation not permitted */
#define ENOENT 2  /* No such file or directory */
#define ESRCH 3   /* No such process */
#define EINTR 4   /* Interrupted system call */
#define EIO 5     /* I/O error */
#define ENXIO 6   /* No such device or address */
#define E2BIG 7   /* Argument list too long */
#define ENOEXEC 8 /* Exec format error */
#define EBADF 9   /* Bad file number */
#define ECHILD 10 /* No child processes */

#if defined(__linux__)
#define EAGAIN 11 /* Try again */
#elif defined(__APPLE__)
#define EDEADLK 11 /* Resource deadlock avoided */
#endif

#define ENOMEM 12  /* Out of memory */
#define EACCES 13  /* Permission denied */
#define EFAULT 14  /* Bad address */
#define ENOTBLK 15 /* Block device required */
#define EBUSY 16   /* Device or resource busy */
#define EEXIST 17  /* File exists */
#define EXDEV 18   /* Cross-device link */
#define ENODEV 19  /* No such device */
#define ENOTDIR 20 /* Not a directory */
#define EISDIR 21  /* Is a directory */
#define EINVAL 22  /* Invalid argument */
#define ENFILE 23  /* File table overflow */
#define EMFILE 24  /* Too many open files */
#define ENOTTY 25  /* Not a typewriter */
#define ETXTBSY 26 /* Text file busy */
#define EFBIG 27   /* File too large */
#define ENOSPC 28  /* No space left on device */
#define ESPIPE 29  /* Illegal seek */
#define EROFS 30   /* Read-only file system */
#define EMLINK 31  /* Too many links */
#define EPIPE 32   /* Broken pipe */
#define EDOM 33    /* Math argument out of domain of func */
#define ERANGE 34  /* Math result not representable */

#if defined(__linux__)

#define EDEADLK 35      /* Resource deadlock would occur */
#define ENAMETOOLONG 36 /* File name too long */
#define ENOLCK 37       /* No record locks available */

/*
 * This error code is special: arch syscall entry code will return
 * -ENOSYS if users try to call a syscall that doesn't exist.  To keep
 * failures of syscalls that really do exist distinguishable from
 * failures due to attempts to use a nonexistent syscall, syscall
 * implementations should refrain from returning -ENOSYS.
 */
#define ENOSYS 38 /* Invalid system call number */

#define ENOTEMPTY 39       /* Directory not empty */
#define ELOOP 40           /* Too many symbolic links encountered */
#define EWOULDBLOCK EAGAIN /* Operation would block */
#define ENOMSG 42          /* No message of desired type */
#define EIDRM 43           /* Identifier removed */
#define ECHRNG 44          /* Channel number out of range */
#define EL2NSYNC 45        /* Level 2 not synchronized */
#define EL3HLT 46          /* Level 3 halted */
#define EL3RST 47          /* Level 3 reset */
#define ELNRNG 48          /* Link number out of range */
#define EUNATCH 49         /* Protocol driver not attached */
#define ENOCSI 50          /* No CSI structure available */
#define EL2HLT 51          /* Level 2 halted */
#define EBADE 52           /* Invalid exchange */
#define EBADR 53           /* Invalid request descriptor */
#define EXFULL 54          /* Exchange full */
#define ENOANO 55          /* No anode */
#define EBADRQC 56         /* Invalid request code */
#define EBADSLT 57         /* Invalid slot */

#define EDEADLOCK EDEADLK

#define EBFONT 59          /* Bad font file format */
#define ENOSTR 60          /* Device not a stream */
#define ENODATA 61         /* No data available */
#define ETIME 62           /* Timer expired */
#define ENOSR 63           /* Out of streams resources */
#define ENONET 64          /* Machine is not on the network */
#define ENOPKG 65          /* Package not installed */
#define EREMOTE 66         /* Object is remote */
#define ENOLINK 67         /* Link has been severed */
#define EADV 68            /* Advertise error */
#define ESRMNT 69          /* Srmount error */
#define ECOMM 70           /* Communication error on send */
#define EPROTO 71          /* Protocol error */
#define EMULTIHOP 72       /* Multihop attempted */
#define EDOTDOT 73         /* RFS specific error */
#define EBADMSG 74         /* Not a data message */
#define EOVERFLOW 75       /* Value too large for defined data type */
#define ENOTUNIQ 76        /* Name not unique on network */
#define EBADFD 77          /* File descriptor in bad state */
#define EREMCHG 78         /* Remote address changed */
#define ELIBACC 79         /* Can not access a needed shared library */
#define ELIBBAD 80         /* Accessing a corrupted shared library */
#define ELIBSCN 81         /* .lib section in a.out corrupted */
#define ELIBMAX 82         /* Attempting to link in too many shared libraries */
#define ELIBEXEC 83        /* Cannot exec a shared library directly */
#define EILSEQ 84          /* Illegal byte sequence */
#define ERESTART 85        /* Interrupted system call should be restarted */
#define ESTRPIPE 86        /* Streams pipe error */
#define EUSERS 87          /* Too many users */
#define ENOTSOCK 88        /* Socket operation on non-socket */
#define EDESTADDRREQ 89    /* Destination address required */
#define EMSGSIZE 90        /* Message too long */
#define EPROTOTYPE 91      /* Protocol wrong type for socket */
#define ENOPROTOOPT 92     /* Protocol not available */
#define EPROTONOSUPPORT 93 /* Protocol not supported */
#define ESOCKTNOSUPPORT 94 /* Socket type not supported */
#define EOPNOTSUPP 95      /* Operation not supported on transport endpoint */
#define EPFNOSUPPORT 96    /* Protocol family not supported */
#define EAFNOSUPPORT 97    /* Address family not supported by protocol */
#define EADDRINUSE 98      /* Address already in use */
#define EADDRNOTAVAIL 99   /* Cannot assign requested address */
#define ENETDOWN 100       /* Network is down */
#define ENETUNREACH 101    /* Network is unreachable */
#define ENETRESET 102      /* Network dropped connection because of reset */
#define ECONNABORTED 103   /* Software caused connection abort */
#define ECONNRESET 104     /* Connection reset by peer */
#define ENOBUFS 105        /* No buffer space available */
#define EISCONN 106        /* Transport endpoint is already connected */
#define ENOTCONN 107       /* Transport endpoint is not connected */
#define ESHUTDOWN 108      /* Cannot send after transport endpoint shutdown */
#define ETOOMANYREFS 109   /* Too many references: cannot splice */
#define ETIMEDOUT 110      /* Connection timed out */
#define ECONNREFUSED 111   /* Connection refused */
#define EHOSTDOWN 112      /* Host is down */
#define EHOSTUNREACH 113   /* No route to host */
#define EALREADY 114       /* Operation already in progress */
#define EINPROGRESS 115    /* Operation now in progress */
#define ESTALE 116         /* Stale file handle */
#define EUCLEAN 117        /* Structure needs cleaning */
#define ENOTNAM 118        /* Not a XENIX named type file */
#define ENAVAIL 119        /* No XENIX semaphores available */
#define EISNAM 120         /* Is a named type file */
#define EREMOTEIO 121      /* Remote I/O error */
#define EDQUOT 122         /* Quota exceeded */

#define ENOMEDIUM 123    /* No medium found */
#define EMEDIUMTYPE 124  /* Wrong medium type */
#define ECANCELED 125    /* Operation Canceled */
#define ENOKEY 126       /* Required key not available */
#define EKEYEXPIRED 127  /* Key has expired */
#define EKEYREVOKED 128  /* Key has been revoked */
#define EKEYREJECTED 129 /* Key was rejected by service */

#define EOWNERDEAD 130      /* Owner died */
#define ENOTRECOVERABLE 131 /* State not recoverable */

#define ERFKILL 132 /* Operation not possible due to RF-kill */

#define EHWPOISON 133 /* Memory page has hardware error */

#define LINUX_MESSAGES                                                         \
  {                                                                            \
    "Operation not permitted",                 /* EPERM */                     \
        "No such file or directory",           /* ENOENT */                    \
        "No such process",                     /* ESRCH */                     \
        "Interrupted system call",             /* EINTR */                     \
        "I/O error",                           /* EIO */                       \
        "No such device or address",           /* ENXIO */                     \
        "Argument list too long",              /* E2BIG */                     \
        "Exec format error",                   /* ENOEXEC */                   \
        "Bad file number",                     /* EBADF */                     \
        "No child processes",                  /* ECHILD */                    \
        "Out of memory",                       /* ENOMEM */                    \
        "Permission denied",                   /* EACCES */                    \
        "Bad address",                         /* EFAULT */                    \
        "Block device required",               /* ENOTBLK */                   \
        "Device or resource busy",             /* EBUSY */                     \
        "File exists",                         /* EEXIST */                    \
        "Cross-device link",                   /* EXDEV */                     \
        "No such device",                      /* ENODEV */                    \
        "Not a directory",                     /* ENOTDIR */                   \
        "Is a directory",                      /* EISDIR */                    \
        "Invalid argument",                    /* EINVAL */                    \
        "File table overflow",                 /* ENFILE */                    \
        "Too many open files",                 /* EMFILE */                    \
        "Not a typewriter",                    /* ENOTTY */                    \
        "Text file busy",                      /* ETXTBSY */                   \
        "File too large",                      /* EFBIG */                     \
        "No space left on device",             /* ENOSPC */                    \
        "Illegal seek",                        /* ESPIPE */                    \
        "Read-only file system",               /* EROFS */                     \
        "Too many links",                      /* EMLINK */                    \
        "Broken pipe",                         /* EPIPE */                     \
        "Math argument out of domain of func", /* EDOM */                      \
        "Math result not representable",       /* ERANGE */                    \
        "Resource deadlock would occur",       /* EDEADLK */                   \
        "File name too long",                  /* ENAMETOOLONG */              \
        "No record locks available",           /* ENOLCK */                    \
        "Invalid system call number",          /* ENOSYS */                    \
        "Directory not empty",                 /* ENOTEMPTY */                 \
        "Too many symbolic links encountered", /* ELOOP */                     \
        "Operation would block",         /* EWOULDBLOCK, synonym for EAGAIN */ \
        "No message of desired type",    /* ENOMSG */                          \
        "Identifier removed",            /* EIDRM */                           \
        "Channel number out of range",   /* ECHRNG */                          \
        "Level 2 not synchronized",      /* EL2NSYNC */                        \
        "Level 3 halted",                /* EL3HLT */                          \
        "Level 3 reset",                 /* EL3RST */                          \
        "Link number out of range",      /* ELNRNG */                          \
        "Protocol driver not attached",  /* EUNATCH */                         \
        "No CSI structure available",    /* ENOCSI */                          \
        "Level 2 halted",                /* EL2HLT */                          \
        "Invalid exchange",              /* EBADE */                           \
        "Invalid request descriptor",    /* EBADR */                           \
        "Exchange full",                 /* EXFULL */                          \
        "No anode",                      /* ENOANO */                          \
        "Invalid request code",          /* EBADRQC */                         \
        "Invalid slot",                  /* EBADSLT */                         \
        "Bad font file format",          /* EBFONT */                          \
        "Device not a stream",           /* ENOSTR */                          \
        "No data available",             /* ENODATA */                         \
        "Timer expired",                 /* ETIME */                           \
        "Out of streams resources",      /* ENOSR */                           \
        "Machine is not on the network", /* ENONET */                          \
        "Package not installed",         /* ENOPKG */                          \
        "Object is remote",              /* EREMOTE */                         \
        "Link has been severed",         /* ENOLINK */                         \
        "Advertise error",               /* EADV */                            \
        "Srmount error",                 /* ESRMNT */                          \
        "Communication error on send",   /* ECOMM */                           \
        "Protocol error",                /* EPROTO */                          \
        "Multihop attempted",            /* EMULTIHOP */                       \
        "RFS specific error",            /* EDOTDOT */                         \
        "Not a data message",            /* EBADMSG */                         \
        "Value too large for defined data type",           /* EOVERFLOW */     \
        "Name not unique on network",                      /* ENOTUNIQ */      \
        "File descriptor in bad state",                    /* EBADFD */        \
        "Remote address changed",                          /* EREMCHG */       \
        "Can not access a needed shared library",          /* ELIBACC */       \
        "Accessing a corrupted shared library",            /* ELIBBAD */       \
        ".lib section in a.out corrupted",                 /* ELIBSCN */       \
        "Attempting to link in too many shared libraries", /* ELIBMAX */       \
        "Cannot exec a shared library directly",           /* ELIBEXEC */      \
        "Illegal byte sequence",                           /* EILSEQ */        \
        "Interrupted system call should be restarted",     /* ERESTART */      \
        "Streams pipe error",                              /* ESTRPIPE */      \
        "Too many users",                                  /* EUSERS */        \
        "Socket operation on non-socket",                  /* ENOTSOCK */      \
        "Destination address required",                    /* EDESTADDRREQ */  \
        "Message too long",                                /* EMSGSIZE */      \
        "Protocol wrong type for socket",                  /* EPROTOTYPE */    \
        "Protocol not available",                          /* ENOPROTOOPT */   \
        "Protocol not supported",                        /* EPROTONOSUPPORT */ \
        "Socket type not supported",                     /* ESOCKTNOSUPPORT */ \
        "Operation not supported on transport endpoint", /* EOPNOTSUPP */      \
        "Protocol family not supported",                 /* EPFNOSUPPORT */    \
        "Address family not supported by protocol",      /* EAFNOSUPPORT */    \
        "Address already in use",                        /* EADDRINUSE */      \
        "Cannot assign requested address",               /* EADDRNOTAVAIL */   \
        "Network is down",                               /* ENETDOWN */        \
        "Network is unreachable",                        /* ENETUNREACH */     \
        "Network dropped connection because of reset",   /* ENETRESET */       \
        "Software caused connection abort",              /* ECONNABORTED */    \
        "Connection reset by peer",                      /* ECONNRESET */      \
        "No buffer space available",                     /* ENOBUFS */         \
        "Transport endpoint is already connected",       /* EISCONN */         \
        "Transport endpoint is not connected",           /* ENOTCONN */        \
        "Cannot send after transport endpoint shutdown", /* ESHUTDOWN */       \
        "Too many references: cannot splice",            /* ETOOMANYREFS */    \
        "Connection timed out",                          /* ETIMEDOUT */       \
        "Connection refused",                            /* ECONNREFUSED */    \
        "Host is down",                                  /* EHOSTDOWN */       \
        "No route to host",                              /* EHOSTUNREACH */    \
        "Operation already in progress",                 /* EALREADY */        \
        "Operation now in progress",                     /* EINPROGRESS */     \
        "Stale file handle",                             /* ESTALE */          \
        "Structure needs cleaning",                      /* EUCLEAN */         \
        "Not a XENIX named type file",                   /* ENOTNAM */         \
        "No XENIX semaphores available",                 /* ENAVAIL */         \
        "Is a named type file",                          /* EISNAM */          \
        "Remote I/O error",                              /* EREMOTEIO */       \
        "Quota exceeded",                                /* EDQUOT */          \
        "No medium found",                               /* ENOMEDIUM */       \
        "Wrong medium type",                             /* EMEDIUMTYPE */     \
        "Operation Canceled",                            /* ECANCELED */       \
        "Required key not available",                    /* ENOKEY */          \
        "Key has expired",                               /* EKEYEXPIRED */     \
        "Key has been revoked",                          /* EKEYREVOKED */     \
        "Key was rejected by service",                   /* EKEYREJECTED */    \
        "Owner died",                                    /* EOWNERDEAD */      \
        "State not recoverable",                         /* ENOTRECOVERABLE */ \
        "Operation not possible due to RF-kill",         /* ERFKILL */         \
        "Memory page has hardware error"                 /* EHWPOISON */       \
  }

#elif defined(__APPLE__)   /* non-blocking and interrupt i/o */
#define EAGAIN 35          /* Resource temporarily unavailable */
#define EWOULDBLOCK EAGAIN /* Operation would block */
#define EINPROGRESS 36     /* Operation now in progress */
#define EALREADY 37        /* Operation already in progress */

/* ipc/network software -- argument errors */
#define ENOTSOCK 38        /* Socket operation on non-socket */
#define EDESTADDRREQ 39    /* Destination address required */
#define EMSGSIZE 40        /* Message too long */
#define EPROTOTYPE 41      /* Protocol wrong type for socket */
#define ENOPROTOOPT 42     /* Protocol not available */
#define EPROTONOSUPPORT 43 /* Protocol not supported */
#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL
#define ESOCKTNOSUPPORT 44 /* Socket type not supported */
#endif
#define ENOTSUP 45 /* Operation not supported */
#if !__DARWIN_UNIX03 && !defined(KERNEL)
/*
 * This is the same for binary and source copmpatability, unless compiling
 * the kernel itself, or compiling __DARWIN_UNIX03; if compiling for the
 * kernel, the correct value will be returned.  If compiling non-POSIX
 * source, the kernel return value will be converted by a stub in libc, and
 * if compiling source with __DARWIN_UNIX03, the conversion in libc is not
 * done, and the caller gets the expected (discrete) value.
 */
#define EOPNOTSUPP ENOTSUP /* Operation not supported on socket */
#endif                     /* !__DARWIN_UNIX03 && !KERNEL */

#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL
#define EPFNOSUPPORT 46 /* Protocol family not supported */
#endif
#define EAFNOSUPPORT 47  /* Address family not supported by protocol family */
#define EADDRINUSE 48    /* Address already in use */
#define EADDRNOTAVAIL 49 /* Can't assign requested address */

/* ipc/network software -- operational errors */
#define ENETDOWN 50      /* Network is down */
#define ENETUNREACH 51   /* Network is unreachable */
#define ENETRESET 52     /* Network dropped connection on reset */
#define ECONNABORTED 53  /* Software caused connection abort */
#define ECONNRESET 54    /* Connection reset by peer */
#define ENOBUFS 55       /* No buffer space available */
#define EISCONN 56       /* Socket is already connected */
#define ENOTCONN 57      /* Socket is not connected */
#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL
#define ESHUTDOWN 58    /* Can't send after socket shutdown */
#define ETOOMANYREFS 59 /* Too many references: can't splice */
#endif
#define ETIMEDOUT 60    /* Operation timed out */
#define ECONNREFUSED 61 /* Connection refused */

#define ELOOP 62        /* Too many levels of symbolic links */
#define ENAMETOOLONG 63 /* File name too long */

/* should be rearranged */
#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL
#define EHOSTDOWN 64 /* Host is down */
#endif
#define EHOSTUNREACH 65 /* No route to host */
#define ENOTEMPTY 66    /* Directory not empty */

/* quotas & mush */
#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL
#define EPROCLIM 67 /* Too many processes */
#define EUSERS 68   /* Too many users */
#endif
#define EDQUOT 69 /* Disc quota exceeded */

/* Network File System */
#define ESTALE 70 /* Stale NFS file handle */
#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL
#define EREMOTE 71       /* Too many levels of remote in path */
#define EBADRPC 72       /* RPC struct is bad */
#define ERPCMISMATCH 73  /* RPC version wrong */
#define EPROGUNAVAIL 74  /* RPC prog. not avail */
#define EPROGMISMATCH 75 /* Program version wrong */
#define EPROCUNAVAIL 76  /* Bad procedure for program */
#endif

#define ENOLCK 77 /* No locks available */
#define ENOSYS 78 /* Function not implemented */

#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL
#define EFTYPE 79    /* Inappropriate file type or format */
#define EAUTH 80     /* Authentication error */
#define ENEEDAUTH 81 /* Need authenticator */

/* Intelligent device errors */
#define EPWROFF 82   /* Device power is off */
#define EDEVERR 83   /* Device error, e.g. paper out */
#endif

#define EOVERFLOW 84 /* Value too large to be stored in data type */

/* Program loading errors */
#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL
#define EBADEXEC 85   /* Bad executable */
#define EBADARCH 86   /* Bad CPU type in executable */
#define ESHLIBVERS 87 /* Shared library version mismatch */
#define EBADMACHO 88  /* Malformed Macho file */
#endif

#define ECANCELED 89 /* Operation canceled */

#define EIDRM 90  /* Identifier removed */
#define ENOMSG 91 /* No message of desired type */
#define EILSEQ 92 /* Illegal byte sequence */
#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL
#define ENOATTR 93 /* Attribute not found */
#endif

#define EBADMSG 94   /* Bad message */
#define EMULTIHOP 95 /* Reserved */
#define ENODATA 96   /* No message available on STREAM */
#define ENOLINK 97   /* Reserved */
#define ENOSR 98     /* No STREAM resources */
#define ENOSTR 99    /* Not a STREAM */
#define EPROTO 100   /* Protocol error */
#define ETIME 101    /* STREAM ioctl timeout */

#if __DARWIN_UNIX03 || defined(KERNEL)
/* This value is only discrete when compiling __DARWIN_UNIX03, or KERNEL */
#define EOPNOTSUPP 102 /* Operation not supported on socket */
#endif                 /* __DARWIN_UNIX03 || KERNEL */

#define ENOPOLICY 103 /* No such policy registered */

#if __DARWIN_C_LEVEL >= 200809L
#define ENOTRECOVERABLE 104 /* State not recoverable */
#define EOWNERDEAD 105      /* Previous owner died */
#endif

#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL
#define EQFULL 106 /* Interface output queue is full */
#define ELAST 106  /* Must be equal largest errno */
#endif

/* non-blocking and interrupt i/o */
#define EAGAIN 35          /* Resource temporarily unavailable */
#define EWOULDBLOCK EAGAIN /* Operation would block */
#define EINPROGRESS 36     /* Operation now in progress */
#define EALREADY 37        /* Operation already in progress */

/* ipc/network software -- argument errors */
#define ENOTSOCK 38        /* Socket operation on non-socket */
#define EDESTADDRREQ 39    /* Destination address required */
#define EMSGSIZE 40        /* Message too long */
#define EPROTOTYPE 41      /* Protocol wrong type for socket */
#define ENOPROTOOPT 42     /* Protocol not available */
#define EPROTONOSUPPORT 43 /* Protocol not supported */
#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL
#define ESOCKTNOSUPPORT 44 /* Socket type not supported */
#endif
#define ENOTSUP 45 /* Operation not supported */
#if !__DARWIN_UNIX03 && !defined(KERNEL)
/*
 * This is the same for binary and source copmpatability, unless compiling
 * the kernel itself, or compiling __DARWIN_UNIX03; if compiling for the
 * kernel, the correct value will be returned.  If compiling non-POSIX
 * source, the kernel return value will be converted by a stub in libc, and
 * if compiling source with __DARWIN_UNIX03, the conversion in libc is not
 * done, and the caller gets the expected (discrete) value.
 */
#define EOPNOTSUPP ENOTSUP /* Operation not supported on socket */
#endif                     /* !__DARWIN_UNIX03 && !KERNEL */

#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL
#define EPFNOSUPPORT 46 /* Protocol family not supported */
#endif
#define EAFNOSUPPORT 47  /* Address family not supported by protocol family */
#define EADDRINUSE 48    /* Address already in use */
#define EADDRNOTAVAIL 49 /* Can't assign requested address */

/* ipc/network software -- operational errors */
#define ENETDOWN 50      /* Network is down */
#define ENETUNREACH 51   /* Network is unreachable */
#define ENETRESET 52     /* Network dropped connection on reset */
#define ECONNABORTED 53  /* Software caused connection abort */
#define ECONNRESET 54    /* Connection reset by peer */
#define ENOBUFS 55       /* No buffer space available */
#define EISCONN 56       /* Socket is already connected */
#define ENOTCONN 57      /* Socket is not connected */
#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL
#define ESHUTDOWN 58    /* Can't send after socket shutdown */
#define ETOOMANYREFS 59 /* Too many references: can't splice */
#endif
#define ETIMEDOUT 60    /* Operation timed out */
#define ECONNREFUSED 61 /* Connection refused */

#define ELOOP 62        /* Too many levels of symbolic links */
#define ENAMETOOLONG 63 /* File name too long */

/* should be rearranged */
#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL
#define EHOSTDOWN 64 /* Host is down */
#endif
#define EHOSTUNREACH 65 /* No route to host */
#define ENOTEMPTY 66    /* Directory not empty */

/* quotas & mush */
#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL
#define EPROCLIM 67 /* Too many processes */
#define EUSERS 68   /* Too many users */
#endif
#define EDQUOT 69 /* Disc quota exceeded */

/* Network File System */
#define ESTALE 70 /* Stale NFS file handle */
#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL
#define EREMOTE 71       /* Too many levels of remote in path */
#define EBADRPC 72       /* RPC struct is bad */
#define ERPCMISMATCH 73  /* RPC version wrong */
#define EPROGUNAVAIL 74  /* RPC prog. not avail */
#define EPROGMISMATCH 75 /* Program version wrong */
#define EPROCUNAVAIL 76  /* Bad procedure for program */
#endif

#define ENOLCK 77 /* No locks available */
#define ENOSYS 78 /* Function not implemented */

#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL
#define EFTYPE 79    /* Inappropriate file type or format */
#define EAUTH 80     /* Authentication error */
#define ENEEDAUTH 81 /* Need authenticator */

/* Intelligent device errors */
#define EPWROFF 82   /* Device power is off */
#define EDEVERR 83   /* Device error, e.g. paper out */
#endif

#define EOVERFLOW 84 /* Value too large to be stored in data type */

/* Program loading errors */
#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL
#define EBADEXEC 85   /* Bad executable */
#define EBADARCH 86   /* Bad CPU type in executable */
#define ESHLIBVERS 87 /* Shared library version mismatch */
#define EBADMACHO 88  /* Malformed Macho file */
#endif

#define ECANCELED 89 /* Operation canceled */

#define EIDRM 90  /* Identifier removed */
#define ENOMSG 91 /* No message of desired type */
#define EILSEQ 92 /* Illegal byte sequence */
#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL
#define ENOATTR 93 /* Attribute not found */
#endif

#define EBADMSG 94   /* Bad message */
#define EMULTIHOP 95 /* Reserved */
#define ENODATA 96   /* No message available on STREAM */
#define ENOLINK 97   /* Reserved */
#define ENOSR 98     /* No STREAM resources */
#define ENOSTR 99    /* Not a STREAM */
#define EPROTO 100   /* Protocol error */
#define ETIME 101    /* STREAM ioctl timeout */

#if __DARWIN_UNIX03 || defined(KERNEL)
/* This value is only discrete when compiling __DARWIN_UNIX03, or KERNEL */
#define EOPNOTSUPP 102 /* Operation not supported on socket */
#endif                 /* __DARWIN_UNIX03 || KERNEL */

#define ENOPOLICY 103 /* No such policy registered */

#if __DARWIN_C_LEVEL >= 200809L
#define ENOTRECOVERABLE 104 /* State not recoverable */
#define EOWNERDEAD 105      /* Previous owner died */
#endif

#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL
#define EQFULL 106 /* Interface output queue is full */
#define ELAST 106  /* Must be equal largest errno */

#define APPLE_MESSAGES                                                         \
  {                                                                            \
    "Resource temporarily unavailable",  /* EAGAIN */                          \
        "Operation would block",         /* EWOULDBLOCK, synonym for EAGAIN */ \
        "Operation now in progress",     /* EINPROGRESS */                     \
        "Operation already in progress", /* EALREADY */                        \
        "Socket operation on non-socket",    /* ENOTSOCK */                    \
        "Destination address required",      /* EDESTADDRREQ */                \
        "Message too long",                  /* EMSGSIZE */                    \
        "Protocol wrong type for socket",    /* EPROTOTYPE */                  \
        "Protocol not available",            /* ENOPROTOOPT */                 \
        "Protocol not supported",            /* EPROTONOSUPPORT */             \
        "Socket type not supported",         /* ESOCKTNOSUPPORT */             \
        "Operation not supported",           /* ENOTSUP */                     \
        "Operation not supported on socket", /* EOPNOTSUPP */                  \
        "Protocol family not supported",     /* EPFNOSUPPORT */                \
        "Address family not supported by protocol family", /* EAFNOSUPPORT */  \
        "Address already in use",                          /* EADDRINUSE */    \
        "Can't assign requested address",                  /* EADDRNOTAVAIL */ \
        "Network is down",                                 /* ENETDOWN */      \
        "Network is unreachable",                          /* ENETUNREACH */   \
        "Network dropped connection on reset",             /* ENETRESET */     \
        "Software caused connection abort",                /* ECONNABORTED */  \
        "Connection reset by peer",                        /* ECONNRESET */    \
        "No buffer space available",                       /* ENOBUFS */       \
        "Socket is already connected",                     /* EISCONN */       \
        "Socket is not connected",                         /* ENOTCONN */      \
        "Can't send after socket shutdown",                /* ESHUTDOWN */     \
        "Too many references: can't splice",               /* ETOOMANYREFS */  \
        "Operation timed out",                             /* ETIMEDOUT */     \
        "Connection refused",                              /* ECONNREFUSED */  \
        "Too many levels of symbolic links",               /* ELOOP */         \
        "File name too long",                              /* ENAMETOOLONG */  \
        "Host is down",                                    /* EHOSTDOWN */     \
        "No route to host",                                /* EHOSTUNREACH */  \
        "Directory not empty",                             /* ENOTEMPTY */     \
        "Too many processes",                              /* EPROCLIM */      \
        "Too many users",                                  /* EUSERS */        \
        "Disc quota exceeded",                             /* EDQUOT */        \
        "Stale NFS file handle",                           /* ESTALE */        \
        "Too many levels of remote in path",               /* EREMOTE */       \
        "RPC struct is bad",                               /* EBADRPC */       \
        "RPC version wrong",                               /* ERPCMISMATCH */  \
        "RPC prog. not avail",                             /* EPROGUNAVAIL */  \
        "Program version wrong",                           /* EPROGMISMATCH */ \
        "Bad procedure for program",                       /* EPROCUNAVAIL */  \
        "No locks available",                              /* ENOLCK */        \
        "Function not implemented",                        /* ENOSYS */        \
        "Inappropriate file type or format",               /* EFTYPE */        \
        "Authentication error",                            /* EAUTH */         \
        "Need authenticator",                              /* ENEEDAUTH */     \
        "Device power is off",                             /* EPWROFF */       \
        "Device error, e.g. paper out",                    /* EDEVERR */       \
        "Value too large to be stored in data type",       /* EOVERFLOW */     \
        "Bad executable",                                  /* EBADEXEC */      \
        "Bad CPU type in executable",                      /* EBADARCH */      \
        "Shared library version mismatch",                 /* ESHLIBVERS */    \
        "Malformed Macho file",                            /* EBADMACHO */     \
        "Operation canceled",                              /* ECANCELED */     \
        "Identifier removed",                              /* EIDRM */         \
        "No message of desired type",                      /* ENOMSG */        \
        "Illegal byte sequence",                           /* EILSEQ */        \
        "Attribute not found",                             /* ENOATTR */       \
        "Bad message",                                     /* EBADMSG */       \
        "Reserved",                                        /* EMULTIHOP */     \
        "No message available on STREAM",                  /* ENODATA */       \
        "Reserved",                                        /* ENOLINK */       \
        "No STREAM resources",                             /* ENOSR */         \
        "Not a STREAM",                                    /* ENOSTR */        \
        "Protocol error",                                  /* EPROTO */        \
        "STREAM ioctl timeout",                            /* ETIME */         \
        "Operation not supported on socket",               /* EOPNOTSUPP */    \
        "No such policy registered",                       /* ENOPOLICY */     \
        "State not recoverable",          /* ENOTRECOVERABLE */                \
        "Previous owner died",            /* EOWNERDEAD */                     \
        "Interface output queue is full", /* EQFULL */                         \
  }
#endif

#endif