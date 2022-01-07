#define _SYSTEM 1;

#include "outer_pt.h";

#define FIFO 1
#define LRU 2
int algorithm = FIFO;

void fifo(pt_t *pt)
{
    boolean isInMemory = false;
    for (int i = 0; i < NR_SYS_CHUNKS; i++)
    {
        if (opt->inner_tables[i] == pt)
        {
            // page table is in memory
            isInMemory = true;
            break;
        }
    }
    if (!isInMemory)
    {
        if (opt->pageTableCount < MAX_PT)
        {
            opt->inner_tables[opt->pageTableCount++] = pt;
        }
        else
        {
            for (int i = 0; i < opt->pageTableCount - 1; i++)
            {
                opt->inner_tables[i] = opt->inner_tables[i + 1];
            }
            opt->inner_tables[pageTableCount] = pt;
        }
    }
}

void lru(pt_t *pt)
{
    boolean isInMemory = false;
    int foundIndex = -1;
    for (int i = 0; i < NR_SYS_CHUNKS; i++)
    {
        if (opt->inner_tables[i] == pt)
        {
            // page table is in memory
            isInMemory = true;
            foundIndex = i;
            break;
        }
    }
    if (!isInMemory)
    {
        if (opt->pageTableCount < MAX_PT)
        {
            opt->inner_tables[opt->pageTableCount++] = pt;
        }
        else
        {
            for (int i = 0; i < opt->pageTableCount - 1; i++)
            {
                opt->inner_tables[i] = opt->inner_tables[i + 1];
            }
            opt->inner_tables[pageTableCount] = pt;
        }
    }
    else
    {
        temp = opt->inner_tables[foundIndex];
        for (int i = foundIndex; i < opt->pageTableCount - 1; i++)
        {
            opt->inner_tables[i] = opt->inner_tables[i + 1];
        }
        opt->inner_tables[pageTableCount] = temp;
    }
}

void page_replace_or_alloc(pt_t *pt)
{
    switch (algorithm)
    {
    case FIFO:
        fifo(pt);
        break;
    case LRU:
        lru(pt);
        break;
    }
}
