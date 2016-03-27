#include <stdio.h>
#include <linux/unistd.h>

#define __NR_get_slob_amt_claimed 343
#define __NR_get_slob_amt_free 344

int main() {
	printf("Free: %d (bytes)\n", syscall(__NR_get_slob_amt_free));
	printf("Claimed: %d (bytes)\n", syscall(__NR_get_slob_amt_claimed));

	return 0;
}