#define WAITING 0
#define COMPLIERING 10
#define RUNNING 9
#define CE 8
#define WA 5
#define TLE 3
#define OLE 7
#define RE 6
#define PE 2
#define AC 1
#define SYSTEM_ERR 11
#define MLE 4
#define RF 12 
#define STATUS_SIG 7
#define STATUS_AC 8
#define host "localhost"
#define user "root"
#define password ""
#define database "judgeonline"
#define MAXPOSIX 4
#define MAXPROBLEM 2000
//#define MAXTXTSIZE 

#include <sys/syscall.h>

int SYS_J[256]={SYS_ugetrlimit, SYS_rt_sigprocmask, SYS_futex, SYS_read, SYS_mmap2, SYS_stat64, SYS_open, SYS_close, SYS_execve, SYS_access, SYS_brk, SYS_readlink, SYS_munmap, SYS_close, SYS_uname, SYS_clone, SYS_uname, SYS_mprotect, SYS_rt_sigaction, SYS_sigprocmask, SYS_getrlimit, SYS_fstat64, SYS_getuid32, SYS_getgid32, SYS_geteuid32, SYS_getegid32, SYS_set_thread_area, SYS_set_tid_address, SYS_set_robust_list, SYS_exit_group, 0};
int SYS_C[256]={SYS_read, SYS_uname, SYS_write, SYS_open, SYS_close, SYS_execve, SYS_access, SYS_brk, SYS_munmap, SYS_mprotect, SYS_mmap2, SYS_fstat64, SYS_set_thread_area, 252,0};
