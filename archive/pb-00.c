int main(int argc,char **argv) {

	int	TAB_SIZE;
	int	MEM_MAX;
	int	PRC_MAX;
	int	STK_MAX;

	char *m;
	char *c;
	int *s;
	int *p;

	int mp;
	int cp;
	int sp;

	int d;
	int scp;
	int n;
	int ln;
	int cl;
	int i;
	int f;
	int ch;
	char b;

	TAB_SIZE=4;
	MEM_MAX=65536;
	PRC_MAX=256;
	STK_MAX=256;

	m=malloc(MEM_MAX);
	s=malloc(STK_MAX);
	p=malloc(PRC_MAX);

	if(argc<2) {
		printf("usage: %s filename\n",argv[0]);
		return 1;
	}
        
	if((f=open(argv[1],0))==-1) {
		printf("error opening file %s\n",argv[1]);
		return 2;
	} 

	n=0;
  while(read(f,&b,1)>0) {
  	n++;
  }

	close(f);

	if((c=malloc(n))==0) {
		printf("error allocating memory\n");
		return 3;
	}

	if((f=open(argv[1],0))==-1) {
		printf("error opening file %s\n",argv[1]);
		return 2;
	} 	

	if(read(f,c,n)!=n) {
		printf("error reading file\n");
		return 4;
	}

	close(f);

	i=0;
	while(i<MEM_MAX) {
		m[i]=0;
		i++;
	}

	i=0;
	while(i<STK_MAX) {
		s[i]=0;
		i++;
	}

	i=0;
	while(i<PRC_MAX) {
		p[i]=-1;
		i++;
	}
        
	mp=0;
	cp=0;
	ln=1;
	cl=1;
	sp=-1;
	
	while(cp<n) {

		d=1;

		if(c[cp]=='+') m[mp]++;
		else if(c[cp]=='-') m[mp]--;
		else if(c[cp]=='<') mp--;
		else if(c[cp]=='>') mp++;
		else if(c[cp]=='.') putchar(m[mp]);
		else if(c[cp]==',') m[mp]=((ch=getchar())==-1?0:ch);
		else if(c[cp]=='[') {
			while(d!=0) {
				cp++;
				d-=(c[cp]==']')-(c[cp]=='[');
			}
		}
		if(c[cp]==']') {
			while(d!=0) {
				cp--;
				d-=(c[cp]=='[')-(c[cp]==']');
			}
		}
		else if(c[cp]=='(') { 
			p[m[mp]]=cp;
			while(d!=0) {
				cp++;
				d-=(c[cp]==')')-(c[cp]=='(');
			}
		}
		else if(c[cp]==')') { 
			while(d!=0) {
				cp--;
				d-=(c[cp]=='(')-(c[cp]==')');
			}
			if(sp>=0) { cp=s[sp]; sp--; }
		}
		else if(c[cp]==':') {
			if(sp<STK_MAX-1) { sp++; s[sp]=cp; cp=p[m[mp]]; } 
		}
		
		cp++;
		
	}

	free(c);

	printf("\n");
		
	return 0;
}
