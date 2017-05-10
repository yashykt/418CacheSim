#ifndef _CACHE_H_
#define _CACHE_H_

#include <vector>
#include <math.h>
#include <assert.h>

#define CACHE_BITS 6

enum cache_state {
    Modified = 0,
    Shared,
    Invalid,
    Exclusive,
    Owner,
    ShModified,
    ShClean
};

class CacheLine
{
    public:
        unsigned long tag;
        cache_state status;
        unsigned long lru_num;
        CacheLine();
        CacheLine(unsigned long t, cache_state s);
};

class Set
{
    public:
        unsigned long current_lru;
        std::vector<CacheLine> cl;

        Set(unsigned long ass);
};


class Cache
{
    private:
        static unsigned long cache_lines;
        static unsigned long cache_size; // in MB
        static unsigned long associativity;
        static unsigned long num_set;
        static unsigned long set_bits;
        static unsigned long set_mask;

        std::vector<Set> sets;
    public:
        static unsigned long block_bits;

        Cache();

        void update_cache_lru(unsigned long addr);
        void insert_cache(unsigned long addr, cache_state status);
        cache_state cache_check_status(unsigned long addr);
        void cache_set_status(unsigned long addr, cache_state status);

        static void cache_init(unsigned long size, unsigned long ass);
};

#endif /* _CACHE_H_ */
