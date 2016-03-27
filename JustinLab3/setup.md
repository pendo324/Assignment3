Alright, so the setup isn't too bad.

Everything that I added to slob.c is preceeded by a comment /* Lab 3 ... */ and also followed by a comment /* Lab 3 */.

This way, even though we are modifying the same file, you can easily copy things from this version (which should have working syscalls) and your version.

So yeah, just find every comment, copy the stuff in the middle into the same location in your file and that's it for slob.c! 

Next, you have to edit syscall_table_32.S and unistd_32.h. At the end of syscall_table_32.S do the same thing we did for our other labs by adding

```	.long sys_get_slob_amt_claimed
	.long sys_get_slob_amt_free```

to the end of the file. Then, you're going to have to add 

```	#define __NR_get_slob_amt_claimed 343
	#define __NR_get_slob_amt_free 344```

to unistd_32.h, at the end, where we added the other syscalls. The 343 and 344 numbers might not be the same for you, so make sure they are sequential with
the other syscalls in that file.

After you add the defines, make sure to increase the #define NR_syscalls X to X + 2. (It should end up at 344 or 345). 

Now you are ready to compile.

After that, compile the tester (Note: make sure you change the values in the define to match the ones in your kernel), using ```gcc test.c -o out```.

If it returns a value that doesn't look like complete nonsense, then it worked!