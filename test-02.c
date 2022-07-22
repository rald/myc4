void swap(int *x,int *y) {
	int t;
	t=*x;
	*x=*y;
	*y=t;
}

int main() {

	int x,y;
	 
	x=1; y=2;

	printf("%d %d\n",x,y);

	swap(&x,&y);

	printf("%d %d\n",x,y);

	return 0;
}
