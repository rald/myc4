int O_RDONLY;
int O_WRONLY;
int O_RDWR;
int O_CREAT;
int O_APPEND;
int STRING_MAX;

int strlen(char *str) {
	int len;
	len=0;
	while(str[len]) {
		len++;
	}
	return len;
}

int main() {

	int fd;
	char *msg;
	int len;

	O_RDONLY =    0;
	O_WRONLY =    1;
	O_RDWR   =    2;
	O_CREAT  =   64;
	O_APPEND = 1024;

	STRING_MAX=256;

	fd=open("x.txt",O_CREAT|O_WRONLY);

	msg=malloc(sizeof(char)*STRING_MAX);

	sprintf(msg,"HI%d\n",14344);

	len=strlen(msg);

	write(fd,msg,len);

	close(fd);

	fd=open("x.txt",O_RDONLY);
	
	read(fd,msg,len);
	
	printf("%s",msg);

	close(fd);

	return 0;

}
