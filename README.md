# Assignment 3

## Report

In this lab we were tasked to modify the SLOB allocator in the kernel to be a best fit algorithm. 

We did this by performing a linear search through the entire linked list of free pages, and checking for the page that's closest in size to what we're trying to allocate.

```c

```


### Part 2
We couldn't find the SLOB allocator in our menuconfig program, so we followed instructions from The University of Illinois to let us set the allocator. 

1. Search for `CONFIG EMBEDDED` in the `.config` in your kernel dir, and replace it by `CONFIG EMBEDDED=y`
2. in the terminal, type `make menuconfig`
3. Next navigate to General Setup - Choose SLAB allocator. Choose SLOB as the new allocator.

### Part 3
Devise a method to keep track of all of the memory claimed by the SLOB allocator for small allocations (i.e., every time the if(!b) beginning on line 368 of slob.c is entered while the free_slob_small list is iterated through) along with the amount of memory that was not served in an allocation request (i.e. the amount of memory contained in all blocks on the free list). Write separate system calls (refer to lab #1) at the bottom of mm/slob.c to return each of these amounts in bytes. I.e., asmlinkage long sys_get_slob_amt_claimed(void) for the number of requested bytes and asmlinkage long sys_get_slob_amt_free(void)for the number of bytes in the free list (free_slob_small) that cannot be allocated due to fragmentation. Comparing the values returned by each of these functions will give you some idea of the degree of fragmentation suffered by SLOB. Write a simple program that uses these two system calls to make this comparison. For example, this program can ask for memory multiple times using malloc()and between the memory requests it invokes the two system calls to keep track of the memory fragmentation situation. Feel free to add your own design here (e.g., running another program using execve()) in your test program. Fragmentation happens when a memory request cannot be satisfied by any single free block but the sum of all free blocks can. Specifically, this situation happens when the true branch of if(!b) beginning on line 368 of slob.c is entered. At this point, we can at least collect (1) the size of the current memory request (memory claimed) and (2) the total size of memory in the free list (free_slob_small). The two new system calls can report these two numbers in the simplest case. For example, number (1) can be 255 bytes and number  (2) can be 1342 bytes. From these two numbers we can have some idea about the fragmentation. However, this method only reflects the situation at a particular moment, i.e., the latest memory allocation request. But we may want to have information over sometime; then we need to get the accumulated numbers (or average numbers) for (1) and (2). Use two global arrays to store the last 100 measurements of (1) and (2), and the two system calls to report the averages of these measurements, respectively. The header of slob.c (the comments) gives a very useful description about the free list. Please read it carefully, so that you know how to count the total bytes in the free list. Although the Linux SLOB allocator maintains three free lists, for this lab you only need to focus on the free_slob_small free list.

### Part 4
Modify mm/slob.c so that it uses the best-fit algorithm. Begin with the function slob_alloc(), and make changes elsewhere as appropriate. The changes necessary to do this should not be too significant, so if you find yourself writing many lines of code you should rethink your implementation. Make sure you add a section to the file header including the names of your team members, and a description of the changes you made.

### Part 5
Use the program you wrote in task 4 to compare the amount of fragmentation suffered by SLOB using the first-fit algorithm and the amount suffered by SLOB using the best-fit algorithm. Record your observations and conclusions in a README file.

### Part 6
Follow the “Kernel Patch Guide” to make a patch file representing the changes between your modified kernel and the vanilla kernel. Name your patch file linux-2.6.36- best_fit_slob.patch. This will make it easy for the TA to examine your changes. Make sure this patch contains only the changes you want to submit, no experimental changes.
