#include<stdio.h>
#include<conio.h>
#include<io.h>
#include<stat.h>
#include<stdlib.h>

void main()
{
	int i,j;
	FILE *fd;
	char ch;
	fpos_t filepos;
/*	char far *ch;
	ch = 0xb8000000;
*/
	clrscr();

//	fgetpos(stdout, &filepos);

	for(i=0;i<=20;i++) {
		for(j=0;j<=i;j++)
			printf("%d, ",j);
		printf("\n");
	}

	fd = fopen("TMP.X","w");

	i=0;

//	fsetpos(stdout, &filepos);
/*	printf("%u",stdout->flags);
	if(stdout->flags == _F_IN)	printf("\nFIN");
	if(stdout->flags == _F_OUT)	printf("\nFOUT");
	if(stdout->flags == _F_RDWR)	printf("\nRDWR");
	if(stdout->flags == _F_READ)	printf("\nREAD");
	if(stdout->flags == _F_WRIT)	printf("\nWRITE");
	if(stdout->flags == _F_TERM)	printf("\nTERMINAL");
	if(stdout->flags == _F_EOF)	printf("\nEOF");
	if(stdout->flags == _F_BIN)	printf("\nBIN");
	if(stdout->flags == _F_BUF)	printf("\nTERMINAL");
	if(stdout->flags == _F_LBUF)	printf("\nTERMINAL");
	if(stdout->flags == _F_ERR)	printf("\nTERMINAL");
*/

	stdout->flags = _F_RDWR;
	rewind(stdout);
	while(i++ < 50) {
		ch = getc(stdout);
//      getc(stdout);
		if(ch == EOF) 	break;
		putc(ch,fd);
	}

	fclose(fd);
	fprintf(stdout,"\nReaded.... [%d]",i);
	getch();
}