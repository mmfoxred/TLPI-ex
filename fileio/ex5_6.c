/*
分析：
1.fd2 同样指向fd1文件，它们共享同一个打开的文件句柄
所以前两个write正常写入 “Hello,world”
2.lseek将文件偏移量置于文件起始处
3.写入的HELLO,覆盖掉Hello,即HELLO,world
4.fd3重新打开了一份文件，并不与fd1共享打开的文件句柄，fd3指向文件表中另一个条目，所以文件偏移量也是不一样的，它从SEEK_SET处开始。
5.再次使用Giddy覆盖HELLO 即Giddy,world
*/