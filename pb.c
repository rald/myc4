#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int TAB_SIZE;

int	MEM_MAX;
int	STK_MAX;
int	PRC_MAX;

int *m;
int *s;
int *p;
char *c;

int mp;
int cp;
int sp;

int f;
int n;
char b;
int i;
int d;
int ch;

int ln;
int cl;

int scp;



void error(int code,int scp,char *msg) {

	ln=0; cl=0; i=0;

	while(i<scp) {

		if(c[i]=='\t') cl=cl+TAB_SIZE;
		else if(c[i]=='\n') { ln++; cl=0; } 
		else cl++;

		i++;				
	}

	ln++; cl++;

	printf("ERR: LN %d CL %d: %s\n",ln,cl,msg);

	exit(code);
	
}



void push(int x) {
	s[--sp]=x;
}



int pop() {
	int x;
	x=s[sp++];
	return x;
}



void check() {

	i=0;

	while(i<n) {

		if(c[i]=='[' || c[i]=='(') {

			if(sp==0) error(14,i,"ERR: Stack Overflow"); 

			push(i);
			
		} else if(c[i]==']' || c[i]==')') { 

			if(sp==n) error(15,i,"ERR: Unbalanced");

			if(	(c[s[sp]]=='[' && c[i]!=']') || 
					(c[s[sp]]=='(' && c[i]!=')') )
				error(16,s[sp],"ERR: Unbalanced");			

			pop();
		}

		i++;
	}	
	if(sp<n) error(17,s[sp],"ERR: Unbalanced"); 
}



int main(int argc,char **argv) {



	TAB_SIZE = 2;



	MEM_MAX = 65536;
	STK_MAX = 256;
	PRC_MAX = 256;
	


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

	if((c=malloc(sizeof(char)*n))==0) {
		printf("error allocating memory\n");
		return 3;
	}

	if((f=open(argv[1],0))==-1) {
		printf("error opening file %s\n",argv[1]);
		return 4;
	} 	

	if(read(f,c,n)!=n) {
		printf("error reading file\n");
		return 5;
	}
	c[n]=0;	

	close(f);



	s=malloc(sizeof(int)*n);
	sp=n;

	check();



	m=malloc(sizeof(int)*MEM_MAX);

	i=0;
	while(i<MEM_MAX) {
		m[i]=0;
		i++;
	}
        
	mp=0;
	cp=0;



	free(s);

	s=malloc(sizeof(int)*STK_MAX);
	sp=STK_MAX;



	p=malloc(sizeof(int)*PRC_MAX);

	i=0;
	while(i<PRC_MAX) {
		p[i]=-1;
		i++;
	}


	
	while(cp<n) {

		if(c[cp]=='+') { 
			m[mp]++; 
			if(m[mp]>255) m[mp]=0; 
		} else if(c[cp]=='-') { 
			m[mp]--; 
			if(m[mp]<0) m[mp]=255; 
		} else if(c[cp]=='<') { 
			mp--; 
			if(mp<0) error(6,cp,"ERR: Memory Pointer Underflow");
		} else if(c[cp]=='>') { 
			mp++; 
			if(mp>=MEM_MAX) error(7,cp,"ERR: Memory Pointer Overflow");
		} else if(c[cp]=='.') {
			putchar(m[mp]);
		} else if(c[cp]==',') { 
			ch=getchar(); 
			if(ch==-1) m[mp]=0; else m[mp]=ch & 0xFF; 
		} else if(c[cp]=='[') {
			scp=cp;
			if(m[mp]==0) {
				d=1;
				while(d) {
					cp++;
					if(cp>=n) error(8,scp,"ERR: Unbalanced");
					if(c[cp]=='[') d++; else if(c[cp]==']') d--; 
				}
			}
		} else if(c[cp]==']') {
			scp=cp;
			if(m[mp]) {
				d=1;
				while(d) {
					cp--;
					if(cp<0) error(9,scp,"ERR: Unbalanced");
					if(c[cp]=='[') d--; else if(c[cp]==']') d++; 
				}
			}
		} else if(c[cp]=='(') {

			p[m[mp]]=cp;

			scp=cp;
			d=1;
			while(d) {
				cp++;
				if(cp>=n) error(10,scp,"ERR: Unbalamced");
				if(c[cp]=='(') d++; else if(c[cp]==')') d--; 
			}

		} else if(c[cp]==')') {

			if(sp==STK_MAX) error(11,cp,"ERR: Unbalanced");

			cp=pop();
		
		} else if(c[cp]==':') {

			if(sp==0) error(12,cp,"ERR: Call Stack Overflow");
			if(p[m[mp]]==-1) error(13,cp,"ERR: Invalid Procedure Number");
			
			push(cp);

			cp=p[m[mp]];
			
		} else if(c[cp]=='#' || (cp<n-1 && c[cp]=='/' && c[cp+1]=='/')) {
			while(c[cp]!='\n' && cp<n) {
				cp++;
			}			
		} else if(cp<n-1 && c[cp]=='/' && c[cp+1]=='*') {
			while(cp<n-1 && !(c[cp]=='*' && c[cp+1]=='/')) {
				cp++;
			}
			cp++;				
		}		

		cp++;		

	}

	free(p);
	free(s);
	free(m);
	free(c);
		
	return 0;
}
