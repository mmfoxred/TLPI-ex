#include <error_functions.h>
#include <get_num.h>
#include <stdio.h>
#include <stdlib.h>
#include <tlpi_hdr.h>
#include <unistd.h>
#define MAXALLOCS 1000000

int main(int argc, const char* argv[])
{
    //参数设置
    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("\n");
    int numBlock, blockSize, step, freeMin, freeMax;
    numBlock = getInt(argv[1], GN_GT_0, "numBlock");
    if (numBlock > MAXALLOCS)
        errExit("numBlock > MAXALLOCS %d", MAXALLOCS);
    blockSize = getInt(argv[2], GN_GT_0, "blockSize");
    step      = argc > 3 ? getInt(argv[3], GN_GT_0, "setp") : 1;
    freeMin   = argc > 4 ? getInt(argv[4], GN_GT_0, "freeMin") : 1;
    freeMax   = argc > 5 ? getInt(argv[5], GN_GT_0, "freeMax") : numBlock;
    if (freeMax > MAXALLOCS)
        errExit("freeMax > MAXALLOCS %d", MAXALLOCS);
    //分配内存
    printf("Initial program break: %10p\n", sbrk(0));
    void* ptrs[MAXALLOCS];
    for (int i = 0; i < numBlock; i++)
    {
        ptrs[i] = malloc(blockSize);
        if (ptrs[i] == NULL)
            errExit("ptrs[%d] error", i);
        printf("now program break:%10p\n", sbrk(0));
        //使用main 1000 1024 1即可清除地看到“周期性地分配大内存，将小片内存给调用者”
    }
    printf("After malloc, program break: %10p\n", sbrk(0));
    printf("freeing blocks from %d to %d in step of %d\n", freeMin, freeMax, step);
    for (int i = freeMin; i < freeMax; i += step)
    {
        free(ptrs[i]);
    }
    printf("After free, program break: %10p\n", sbrk(0));
    return 0;
}