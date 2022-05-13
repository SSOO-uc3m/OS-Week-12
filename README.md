
# Lab 12 Introduction to files

## Goals

- Practice the concepts learned in the theory classes related to the file system of UNIX
- Use the file and directory management services offered by the operating system.

## Statements

###  Exercise 01

There is a disk with a UNIX file system. 
Assuming that the size of the block chosen for the file system is 2KBytes, that the addresses of the blocks are 4 bytes and the inodes have the traditional structure (10 direct pointers, 1 simple indirect, 1 double indirect and 1 triple indirect) 
Find the number of blocks that a 4500 KByte file occupies, including both data and address blocks.

If the previous Unix file system has the following information:

I-nodes Table

| Inode No.              | 1         | 2         | 3    |   |   |
|------------------------|-----------|-----------|------|---|---|
| Type                   | Directory | Directory | File |   |   |
| Physical links counter | 3         | 2         | 1    |   |   |
| Data Block Address     | 11        | 12        | 13   |   |   |
| ...                    |           |           |      |   |   |

Data blocks

| Block No. | 11   | 12   | 13        |   |   |
|-----------|------|------|-----------|---|---|
| Contents  | . 1  | . 2  | File data |   |   |
|           | . . 1 | . . 1 |           |   |   |
|           | d 2  | f1 3 |           |   |   |
|           |      |      |           |   |   |
|           |      |      |           |   |   |

Modify the previous tables to reflect the execution of the following 2 operations:

``
ln f1 /d/f2
``

``
ln –s f1 /d/f3
``
#### Solution 01

a) 

Each block pointer can accommodate:
2 KiB * 1024B / 1KiB * 1 address/ 4B = 512 indirect data blocks address
The first 10 simple pointers will point to the first 20 KiB of the file (each block is 2 KiB).

Each block of pointers that is needed will point to 1 MiB (1024Kbytes) of the file: 
512 block addresses * 2 Kbyte per block = 1024 KiB = 1MiB of the file.

Therefore, to get to 4500 KiB we need 5 blocks of addresses.

The first we get from the simple indirect pointer, which points directly to one of them. For the remaining four we need the double indirect pointer that will point to 1 address block that will point to those 4 necessary address blocks.
Then 5 simple + 1 double = 6 address blocks are needed
The size in data blocks of the file is: 4500𝐾𝑖𝐵2𝐾𝑖𝐵 = 2250 Blocks
Then the total size is 2256 blocks plus the i-node.

![inode](http://4.bp.blogspot.com/-VtVFtgJ-8xE/Vbw7OfVWmAI/AAAAAAAAAfM/Ih7m6ixJ928/s1600/sgg-inode.gif)

b)

create physical link /d/f2 to file f1
````
ln f1 /d/f2
````
I-nodes Table
| Inode No.              | 1         | 2         | 3    |  4 |   |
|------------------------|-----------|-----------|------|---|---|
| Type                   | Directory | Directory | File |   |   |
| Physical links counter | 3         | 2         | 1    |   |   |
| Data Block Address     | 11        | 12        | 13   |   |   |
| ...                    |           |           |      |   |   |

Data blocks

| Block No. | 11   | 12   | 13        |  14 |   |
|-----------|------|------|-----------|---|---|
| Contents  | . 1  | . 2  | File data |  |   |
|           | . . 1 | . . 1 |           |   |   |
|           | d 2  | f1 3 |           |   |   |
|           |      | **f2 3** |           |   |   |
|           |      |  |           |   |   |

create symbolic link /d/f3 to file f1

````
ln –s f1 /d/f3
````
I-nodes Table
| Inode No.              | 1         | 2         | 3    |  4 |   |
|------------------------|-----------|-----------|------|---|---|
| Type                   | Directory | Directory | File |  **Symbolic link **|   |
| Physical links counter | 3         | 2         | 1    |  **1** |   |
| Data Block Address     | 11        | 12        | 13   |  **14** |   |
| ...                    |           |           |      |   |   |

Data blocks
| Block No. | 11   | 12   | 13        |  14 |   |
|-----------|------|------|-----------|---|---|
| Contents  | . 1  | . 2  | File data | **f1**  |   |
|           | . . 1 | . . 1 |           |   |   |
|           | d 2  | f1 3 |           |   |   |
|           |      | **f2 3** |           |   |   |
|           |      | **f3 3**  |           |   |   |


###  Exercise 02

We have purchased a 100MB hard drive for high performance tasks.
The final characteristics that will be applied when creating the Files system using the mkfs command are:
- Block size: 1024 bytes. 
- Size of the address of the blocks: 4 bytes.
- Number of i-nodes: 50
- A load block (Boot) that occupies 2 blocks.
- A Superblock that occupies 8 Kbytes and a Bitmap is used to indicate which blocks are used and which are free.
- Fields of an i-node:

File attributes:
- Owner and group ID.
- Read, Write and Execute permissions for the owner, group and the rest of the world.
- Link counter (1 byte).
- 4 indirect pointers, 4 simple indirect pointers., 4 double indirect pointers.

Answer the following questions
a) What is the maximum size of a File stored on this disk? Reason for the answer.
b) If the objective is to minimize access to disk blocks, what parameter do you think the administrator should increase / decrease to achieve this purpose?
c) Assuming that the Files system is capable of using hard and symbolic links.

Calculate:

Maximum number of hard links (in addition to the initial name) that can be made from a File on this disk.

#### Solution 02

a) The maximum size of a File depends on the inode references and the number of block addresses that fit in a data block (indirect reference) which is equal to the block size (1024 bytes) between the size of the address of block (4 bytes), like this:
| REFERENCES              |  Block No.S        |
|------------------------|-----------|
| 4 direct Pointers       | 4 | 
| 4 Single indirect Pointers:| 4*1024 / 4 = 1024         | 
| 4 Double indirect Pointers:   | 4*(1024 /4)*(1024 / 4) = 262144       | 
       
Therefore the No. of blocks is: 4 + 1024 + 262144 = 263172 blocks; Thus, the maximum size (in bytes) of a File in this File system is: 263172 * 1024 = 269488128 bytes => 263172 KB (approximately 263 Mbytes)
Since the disk is 100 MB, a File of maximum size would not fit; therefore the size of a File is limited by the capacity of the disk. For this case, the maximum disk size must be calculated as follows:

Maximum size of a File = (Disk size / Block size) - Number of blocks occupied by the rest of the structures

The typical structures that the statement defines us are:

| Boot              |  SuperBlock      | Bits map | I-Nodes | Data and folders |
|------------------------|-----------|-----------|-----------|-----------|
| 1024 B|8 KB| |50|-----------|


Thus:
```
Boot size = 2 blocks
Superblock size = 8 blocks
Bitmap Size = (100 * 2 ^ 20) / 2 ^ 10 = 102.400 bits => 13 blocks
I-Node Size = 50
Maximum file size = (100 * 2 ^ 20/2 ^ 10) - (2 + 8 + 13 + 50) = 102400– 73 = 102327 blocks
```
Maximum size in bytes = 102327 * 1024 bytes = 99,92 MiB

b) In general, the parameter that is used to achieve the least number of disk accesses is the block size. The transfer of a File requires looking for each block that forms it on disk, waiting for the latency time and making the data transfer.

The trade-off to the large block size is the amount of internal fragmentation is high and that causes the percentage of disk usage to decrease.

c) The number of hard links only depends on the size of the link counter. that indicates the number of hard links made, the link counter of an inode of this Files system has 1 byte, so there can be from 0 to 255 hard links. Since the initial name is also a hard link, the No. of possible hard links, in addition to the initial name, will be 254 links. 
The number of symbolic links only depends on the number of Files that can be created. Since the disk only has 50 inodes, the maximum number of Files will be 50. There are at least two occupied inodes on the disk (the one in the root Directory and the one in the "original" File). Therefore the maximum number of symbolic links to a File can be 48.

###  Exercise 03

Write a C program that receives a name from Directory and shows on the screen the names of Files and Directories it contains, their mode, whether or not they have read permission for the owner, if they are Directorys, and for Files modified in the last 10 days shows your access date.


###  Exercise 04

Given the file system in the figure, whose block size is 512 bytes 
| ... | Blk: 100    | Blk: 101  | Blk: 102    | Blk: 103       | Blk: 104    | ... |
|-----|-------------|------------|------------|----------------|------------|-----|
| ... | i-nodo: 0    | i-nodo: 1   | i-nodo: 2   | i-nodo: 3       | i-nodo: 4   | ... |
|     | Links:4     | Links:2    | Links:2    | Links:1        | Links:2    |     |
|     | Type:dir    | Type:dir   | Type:dir   | Type: symbolic | Type: file |     |
|     | Block: 200 | Block:204 | Block:202 | Block:203     | Block:201 |     |

| ... | Block 200    |Block 201   |Block 202    | Block 203       | Block 204   | ... |
|-----|-------------|------------|------------|----------------|------------|-----|
|     | . 0    | ABF01F    | . 2    | /tmp/romeo&juliet       | . 1   |     |
|     | . . 0   | 54FF45   | . . 0   |  |   . . 0 |   |
|     | tmp   1 | 4700C4F  | michael  4|      | shakespeare 3 |     |
|     | aux  2 |  | |      | romeo&juliet 4|     |

Execute the following instructions in the order indicated, stating what information from the Files system is used at all times and what it is used for, and what are the modifications that must be made at each moment.

````
cat  /aux/michael
rm  /tmp/romeo&juliet
cat  /tmp/shakespeare
rm  /aux/michael
rm  /tmp/shakespeare
````

NOTE: 

cat command: displays a text file on the screen. 

rm command : delete a File.

#### Solution 04

````
cat /aux/michael
````
1) Read the inode of the root Directory (inode 0 - Block 100) and then the first Block of data of metioned Directory (Block 200) is read, as there is the entry of 'aux' (inode 2) there is no need to read more Blocks.
2) Read the inode of aux (inode 2 - Block 102), it is verified that it is a Directory and the first Block of data is read (Block 202), as there is the entry of 'michael' (inode 4) it is not necessary to read more Blocks.
3) Read the inode of michael (inode 4 - Block 104), it is verified that it is a file and the first data block is read (block 203) obtaining the content ABF01F54FF454700C4F

````
rm  /tmp/romeo&juliet
````
1) Read the inode of the root Directory (inode 0 - Block 100) and then the first Block of data of metioned Directory (Block 200) is read, as there is the entry of 'tmp' (inode 1) there is no need to read more Blocks.
2) Read the inode of aux (inode 1 - Block 101), it is verified that it is a Directory and the first Block of data is read (Block 204), as there is the entry of 'romeo&juliet' (inode 4) it is not necessary to read more Blocks.
3) Read the inode of michael (inode 4 - Block 104), it is verified that it is a file 
to delete it, the number of links is decremented (remaining at 1)

Final state of the filesystem.

| ... | Blk: 100    | Blk: 101  | Blk: 102    | Blk: 103       | Blk: 104    | ... |
|-----|-------------|------------|------------|----------------|------------|-----|
| ... | i-nodo: 0    | i-nodo: 1   | i-nodo: 2   | i-nodo: 3       | i-nodo: 4   | ... |
|     | Links:4     | Links:2    | Links:2    | Links:1        | **Links: 2-1=1**    |     |
|     | Type:dir    | Type:dir   | Type:dir   | Type: symbolic | Type: file |     |
|     | Block: 200 | Block:204 | Block:202 | Block:203     | Block:201 |     |

| ... | Block 200    |Block 201   |Block 202    | Block 203       | Block 204   | ... |
|-----|-------------|------------|------------|----------------|------------|-----|
|     | . 0    | ABF01F    | . 2    | /tmp/romeo&juliet       | . 1   |     |
|     | . . 0   | 54FF45   | . . 0   |  |   . . 0 |   |
|     | tmp   1 | 4700C4F  | michael  4|      | shakespeare 3 |     |
|     | aux  2 |  | |      | **-----deleted------**|     |

````
rm  /aux/michael
````
1) Read the inode of the root Directory (inode 0 - Block 100) and then the first Block of data of metioned Directory (Block 200) is read, as there is the entry of 'aux' (inode 2) there is no need to read more Blocks.
2) Read the inode of aux (inode 1 - Block 101), it is verified that it is a Directory and the first Block of data is read (Block 204), as there is the entry of 'michael (inode 4) it is not necessary to read more Blocks.
3) Read the inode of michael (inode 4 - Block 104), it is verified that it is a file to delete it, the number of links is decremented, since it is equal to zero, its inode and its data blocks are deleted. (block 201) for this, the bitmap will have to be updated.

| ... | Blk: 100    | Blk: 101  | Blk: 102    | Blk: 103       | Blk: 104    | ... |
|-----|-------------|------------|------------|----------------|------------|-----|
| ... | i-nodo: 0    | i-nodo: 1   | i-nodo: 2   | i-nodo: 3       |  **-----deleted------**  | ... |
|     | Links:4     | Links:2    | Links:2    | Links:1        |    |     |
|     | Type:dir    | Type:dir   | Type:dir   | Type: symbolic |  |     |
|     | Block: 200 | Block:204 | Block:202 | Block:203     | |     |

| ... | Block 200    |Block 201   |Block 202    | Block 203       | Block 204   | ... |
|-----|-------------|------------|------------|----------------|------------|-----|
|     | . 0    |  **-----deleted------**    | . 2    | /tmp/romeo&juliet       | . 1   |     |
|     | . . 0   |   | . . 0   |  |   . . 0 |   |
|     | tmp   1 |  | **-----deleted------**|      | shakespeare 3 |     |
|     | aux  2 |  | |      |      |

````
rm  /tmp/shakespeare
````
1) Read the inode of the root Directory (inode 0 - Block 100) and then the first Block of data of metioned Directory (Block 200) is read, as there is the entry of 'tmp' (inode 1) there is no need to read more Blocks.
2) Read the inode of aux (inode 1 - Block 101), it is verified that it is a Directory and the first Block of data is read (Block 204), as there is the entry of 'shakespeare' (inode 3) it is not necessary to read more Blocks.
3) Read the inode of michael (inode 3 - Block 103), it is verified that it is a file to delete it, the number of links is decremented, since it is equal to zero, its inode and its data blocks are deleted. (block 203) for this, the bitmap will have to be updated.


| ... | Blk: 100    | Blk: 101  | Blk: 102    | Blk: 103       | Blk: 104    | ... |
|-----|-------------|------------|------------|----------------|------------|-----|
| ... | i-nodo: 0    | i-nodo: 1   | i-nodo: 2   | **-----deleted------**      |   | ... |
|     | Links:4     | Links:2    | Links:2    |        |    |     |
|     | Type:dir    | Type:dir   | Type:dir   |  |  |     |
|     | Block: 200 | Block:204 | Block:202 |      | |     |

| ... | Block 200    |Block 201   |Block 202    | Block 203       | Block 204   | ... |
|-----|-------------|------------|------------|----------------|------------|-----|
|     | . 0    |     | . 2    |  **-----deleted------**     | . 1   |     |
|     | . . 0   |   | . . 0   |  |   . . 0 |   |
|     | tmp   1 |  | |      |  **-----deleted------**|     |
|     | aux  2 |  | |      |      |


###  Exercise 05

Given a hard disk with a Unix-like filesystem with the following specifications: the block size is 4KB, the block address length is 4 bytes and the i-nodes have a traditional structure (10 direct pointers, 1 single indirect pointer, 1 double indirect pointers and 1 triple indirect pointer). 
Answer the following questions: 
What is the number of blocks (including both the data and address blocks) that have the following files:
- File A with a size of 20 KBytes
- File B with a size of 200 KBytes
- File C with a size of 2000 KBytes
- File D with a size of 20000 KBytes
  
What is the maximum file size?

#### Solution 05

In each address block 1024 block addresses can be allocated: 4KBytes /4 bytes =1024 addresses

Number of blocks

1. File A with a size of 20 KBytes  
A 20KB file will use 5 data blocks, using the first 5 direct pointers. That is, it will use 5 blocks
2. File B with a size of 200 KBytes
A 200Kb file will use 50 data blocks. The first 10 will be addressed by the direct pointers. The remaining 40 will be pointed by the single indirect pointers (an extra block is needed). 
That is, it will use 50 blocks + 1 block (related to the single indirect pointer) = 51 blocks
3. File C with a size of 2000 KBytes
A 2000KB file will use 500 data blocks. The first 10 will be addressed by the direct pointers. The remaining 490 will be pointed by the single indirect pointers (an extra block is needed) 
That is, it will use 500 blocks + 1 block (related to the single indirect pointer) = 501 blocks
4. File D with a size of 20 000 Kbytes
A 20000KB file will use 5000 data blocks. The first 10 will be addressed by the direct pointers. The next 1024 blocks will be pointed by the single indirect pointers (an extra block is needed). The remaining 3966 blocks will be addressed using the double indirect pointers (using 1 block to keep the pointer block addresses (1024 address block) plus 4 blocks to point the 3966 data blocks.
That is: 5000 blocks + 1 block (single indirect) + 5 blocks (double indirect) = 5006 blocks

b) What is the maximum possible file size?

The maximum number of blocks of a file is:
-  10 blocks addressed by direct pointers
-  1024 blocks addressed by single indirect pointers
-  1024*1024 blocks addressed by double indirect pointers
-  1024* 1024* 1024 blocks addressed by triple indirect pointers

The overall number of block is 1G+1M+1K+10 blocks which is approximately 4 TBytes (not considering 4GB, 4MB and 40KB because are much smaller than the first term).

###  Exercise 06

Write a program that writes in a File "records.dat" a collection N of records that include a code and a customer name, ordered by code. The program must ask for the client code and name, jump to the corresponding position in the File and write it. If the File does not exist, the program must create it.

Write a program that asks for the code of a client, reads it from the File and displays it in order on the screen. If the customer does not exist, you will need to write an empty record.

