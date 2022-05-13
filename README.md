
# Lab 12 Introduction to files

## Goals

- Practice the concepts learned in the theory classes related to the file system of UNIX
- Use the file and directory management services offered by the operating system.

## Statements

###  Exercise 01

There is a disk with a UNIX file system. 
Assuming that the size of the block chosen for the file system is 2KBytes, that the addresses of the blocks are 4 bytes and the inodes have the traditional structure (10 direct pointers, 1 simple indirect, 1 double indirect and 1 triple indirect) 

a) Find the number of blocks that a 4500 KByte file occupies, including both data and address blocks.

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

b) Modify the previous tables to reflect the execution of the following 2 operations:

``
ln f1 /d/f2
``

``
ln –s f1 /d/f3
``

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

Answer the following questions:

a) What is the maximum size of a File stored on this disk? Reason for the answer.

b) If the objective is to minimize access to disk blocks, what parameter do you think the administrator should increase / decrease to achieve this purpose?

c) Assuming that the Files system is capable of using hard and symbolic links. Calculate: 
Maximum number of hard links (in addition to the initial name) that can be made from a File on this disk.

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


###  Exercise 05

Given a hard disk with a Unix-like filesystem with the following specifications: the block size is 4KB, the block address length is 4 bytes and the i-nodes have a traditional structure (10 direct pointers, 1 single indirect pointer, 1 double indirect pointers and 1 triple indirect pointer). 
Answer the following questions: 
What is the number of blocks (including both the data and address blocks) that have the following files:
- File A with a size of 20 KBytes
- File B with a size of 200 KBytes
- File C with a size of 2000 KBytes
- File D with a size of 20000 KBytes
  
What is the maximum file size?

###  Exercise 06

Write a program that writes in a File "records.dat" a collection N of records that include a code and a customer name, ordered by code. The program must ask for the client code and name, jump to the corresponding position in the File and write it. If the File does not exist, the program must create it.

Write a program that asks for the code of a client, reads it from the File and displays it in order on the screen. If the customer does not exist, you will need to write an empty record.

