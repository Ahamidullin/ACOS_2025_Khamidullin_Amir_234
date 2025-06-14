#define _GNU_SOURCE
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>



struct sigmap { const char *name; int num; };

static const struct sigmap tbl[] = {
    {"HUP",  SIGHUP},   {"INT",  SIGINT},   {"QUIT", SIGQUIT},
    {"ILL",  SIGILL},   {"TRAP", SIGTRAP},  {"ABRT", SIGABRT},
    {"BUS",  SIGBUS},   {"FPE",  SIGFPE},   {"KILL", SIGKILL},
    {"USR1", SIGUSR1},  {"SEGV", SIGSEGV},  {"USR2", SIGUSR2},
    {"PIPE", SIGPIPE},  {"ALRM", SIGALRM},  {"TERM", SIGTERM},
    {"CHLD", SIGCHLD},  {"CONT", SIGCONT},  {"STOP", SIGSTOP},
    {"TSTP", SIGTSTP},  {"TTIN", SIGTTIN},  {"TTOU", SIGTTOU},
    {"URG",  SIGURG},   {"XCPU", SIGXCPU},  {"XFSZ", SIGXFSZ},
    {"VTALRM", SIGVTALRM},{"PROF", SIGPROF}, {"WINCH", SIGWINCH},
    {"SYS",  SIGSYS},


#if defined(SIGPOLL)
    {"POLL", SIGPOLL},
#elif defined(SIGIO)
    {"POLL", SIGIO},
#endif

#if defined(SIGPWR)
    {"PWR",  SIGPWR},
#endif
};

int lookup_signal(const char *s)
{

  char *end;
  long n = strtol(s, &end, 10);
  if (*end == '\0' && n > 0 && n < NSIG)
    return (int)n;

  if (strncasecmp(s, "SIG", 3) == 0)
    s += 3;

  for (size_t i = 0; i < sizeof(tbl)/sizeof(tbl[0]); ++i)
    if (strcasecmp(s, tbl[i].name) == 0)
      return tbl[i].num;
  return -1;
}
