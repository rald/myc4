int my_putchar(int c) {
	return putchar();
}

int my_getchar() {
	return getchar();
}

int main() {
	int c;
	while((c=getchar())!=-1) {
		putchar(c);
	}
	return 0;
}
