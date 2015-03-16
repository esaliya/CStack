#include<stdio.h>

int main(int argc, char **argv)
{

	printf("\nIt's good to be working with C agai\n");

	double balance[2] = {10.1, 12.2};
	
	printf("\n%p  %p  %f\n",balance, &balance, *(balance));
	double *dp = balance;
	printf("\n%p  %p\n",dp, &dp);

	int x = 10;
	int *xp = &x;

	printf("%p  %d  %p  %p\n", &x, x, xp, &xp);

	char *arr = "abc";
	printf("%p  %p\n",arr, arr+1);
	printf("%c  %c\n",*arr, *(arr+1));
	// arr[0] = 'd'; // will cause segmentation fault because string literals are not modifiable
	// compare this to the case when strings are used to initialize an array
	char brr[] = "abc";
	brr[0] = 'd'; // This works as expected




}
