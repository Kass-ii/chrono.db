#define POOL_SIZE 100  // The number of pages we can hold in RAM
#define PAGE_SIZE 4096 // 4KB, a common page size

typedef struct
{
    char data[PAGE_SIZE];
    int page_id;   // Which page from disk this is
    int pin_count; // How many tasks are using this page right now
    int is_dirty;  // Has this page been modified since being read?
} Frame;

Frame buffer_pool[POOL_SIZE];