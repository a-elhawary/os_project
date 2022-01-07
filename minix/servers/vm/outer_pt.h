#define _SYSTEM 1

#include "pt.h"
#include <minix/config.h>

struct outer_pt
{
    int pageTableCount = 0;
    pt_t inner_tables[NR_SYS_CHUNKS];
} opt;