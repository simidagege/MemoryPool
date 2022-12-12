# MemoryPool
Circle Memory Pool in C

# GNU compile
gcc -o MemoryPoolTest MemoryPoolTest.c MemoryPool.c -lpthread

# Run cmd
chmod +x MemoryPoolTest
./MemoryPoolTest

# Output
ubuntu@ubuntu:~/test/MemoryPool$ ./MemoryPool 
calloc for item[0]: data:0x55c61eb522a0, capacity: 512, length:0
calloc for item[1]: data:0x55c61eb522b0, capacity: 512, length:0
calloc for item[2]: data:0x55c61eb522c0, capacity: 512, length:0
calloc for item[3]: data:0x55c61eb522d0, capacity: 512, length:0
calloc for item[4]: data:0x55c61eb522e0, capacity: 512, length:0
calloc for item[5]: data:0x55c61eb522f0, capacity: 512, length:0
calloc for item[6]: data:0x55c61eb52300, capacity: 512, length:0
calloc for item[7]: data:0x55c61eb52310, capacity: 512, length:0
calloc for item[8]: data:0x55c61eb52320, capacity: 512, length:0
calloc for item[9]: data:0x55c61eb52330, capacity: 512, length:0
calloc for item[10]: data:0x55c61eb52340, capacity: 512, length:0
calloc for item[11]: data:0x55c61eb52350, capacity: 512, length:0
calloc for item[12]: data:0x55c61eb52360, capacity: 512, length:0
calloc for item[13]: data:0x55c61eb52370, capacity: 512, length:0
calloc for item[14]: data:0x55c61eb52380, capacity: 512, length:0
calloc for item[15]: data:0x55c61eb52390, capacity: 512, length:0
calloc for item[16]: data:0x55c61eb523a0, capacity: 512, length:0
calloc for item[17]: data:0x55c61eb523b0, capacity: 512, length:0
calloc for item[18]: data:0x55c61eb523c0, capacity: 512, length:0
calloc for item[19]: data:0x55c61eb523d0, capacity: 512, length:0
current:0
found free memory with idex: 0
succeed to get free memory, item->addr: 0x55c61eb522a0, item->capacity: 512, item->length:0
item->data[0]: 88
item->data[1]: 88
item->data[2]: 88
item->data[3]: 88
item->data[4]: 88
item->data[5]: 88
item->data[6]: 88
item->data[7]: 88
item->data[8]: 0
item->data[9]: 0
current:1
found free memory with idex: 1
succeed to get free memory, item1->addr: 0x55c61eb522b0, item1->capacity: 512, item1->length:0
found item:0
succeed to free item
succeed to destroy memory pool
