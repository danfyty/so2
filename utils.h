#include <errno.h>

#define FATAL(err) do {\
    if(err) \
        fprintf(stderr, "%s\n", strerror(errno)); \
}while(0)
