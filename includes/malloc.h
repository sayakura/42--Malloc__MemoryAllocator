
#include <unistd.h>

/**
 * heap info
 * 
 */
typedef struct  s_heap_info
{

}               t_heap_info;

/**
 * 
 * 
 */
typedef struct  s_arena_info
{

}               t_arena_info;

/**
 * ------------[Allocated chunk]------------
 * 
 *       chunk->  +-------------------+
 *                |     prev_size     |
 *                +-------------+-+-+-+
 *                |     size      |N|P|
 *                +-------------+-+-+-+
 *         mem->  |                   |
 *                |     user_data     |
 *                |                   |
 *                +-------------------+
 *  next_chunk->  
 * ------------[Allocated chunk]------------
 * 
 * ------------[Unallocated chunk]----------
 * 
 *       chunk->  +-------------------+
 *                |     prev_size     |
 *                +-------------+-+-+-+
 *                |     size      |N|P|
 *                +-------------+-+-+-+
 *         mem->  |  pointer to next  |
 *                +-------------------+
 *                |  pointer to prev  |
 *                +-------------------+
 *                |  Unused space     |
 *  next_chunk->  
 * ------------[Unallocated chunk]----------
 * 
 * [prev_size]: If the previous chunk is free, this field contains
 * the size of previous chunk. Else if previous chunk
 * is allocated, this field contains previous chunk’s user data.
 * 
 * [size]:  size of this allocated chunk. 
 * Last 2 bits of this field contains flag information.
 *  - PREV_INUSE (P) – This bit is set when previous chunk is allocated.
 *    if this bit is clear, then the word before size can be used to find 
 *    the front of the previous chunk ( for coalescing)
 *  - NON_MAIN_ARENA (N) – This bit is set when this chunk belongs to a thread arena.
 * 
 * because of memory alignment, the last 3 bits is always zero, 
 * i.e.: 8 (1 0 0 0), 16 (1 0 0 0 0)
 * 
 * [fd]: pointer to the next chunk in the same bin
 * [bk]: pointer to the previous chunk in the same bin 
 * Both of these pointer get overwritten for an allocated chunk,
 * as part of the allocated space for the application
 */
typedef struct  s_malloc_chunk
{
    size_t                  prev_size;
    size_t                  size;
    struct s_malloc_chunk   *fd;
    struct s_malloc_chunk   *bk;
}               t_malloc_chunk;
