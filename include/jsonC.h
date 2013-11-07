#define _DEBUG

#ifdef _DEBUG
#define DEBUG(format, args...) printf("[%s:%d] "format, __func__, __LINE__, ##args)
#else
#define DEBUG(args...)
#endif


