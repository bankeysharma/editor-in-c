#include "exconst.c"

/* **********************************
	Variable declaration
	********************************** */

struct 	text_info txtsetting;
int gMAXROWS, gMAXCOLS, gROWS, gCOLS, gTOP, gLEFT, gRIGHT, gBOTTOM;

/*	************ End of declration ************ */

/* **********************************
	Function : Definations
	********************************** */

int setEnv(void);
int resetEnv(void);
int setExtent(void);
int drawOuter(unsigned int,int, char *);

int readLine(FILE **, char *);
int buildList(FILE **, typLine **, typLine **);
int openFile(FILE **, char *, int);
int placeLine(char *, int , int , int);
int length(char *);

typLine *showFile(typLine *,int);
typLine *getLine(typLine *,int, int);
typLine *getcurrLine(typLine *,typLine *,int *);

/*	************ End of defination ************ */


/* ************************************************
	Function : setEnv
	Purpose	: To set the textmode etc for working.
	************************************************ */

int setEnv(void)
{
	extern struct text_info txtsetting;
	gettextinfo(&txtsetting);

	clrscr();

	textmode(C80);

	return(0);
}

/* ************************************************
	Function : resetEnv
	Purpose	: To reset the textmode as on starting.
	************************************************ */
int resetEnv(void)
{
	textmode(txtsetting.currmode);
	return(0);
}

/* ************************************************
	Function : length
	Purpose	: To determine pseudo length of the
					string.
	************************************************ */
int length(char *line)
{
	int len, loc, tmpx;

	loc = _LBOUND;
	len = 0;

	while (*line) {
		if((*line) == '\t') {
			loc = (gTABLEN * (loc/gTABLEN))+gTABLEN;
			while((loc) >=	len) ++len;
			--len;
		} else {
			++len;
			loc++;
		}
		line++;
	}
	return(len);
}

/* ************************************************
	Function : setExtent
	Purpose	: To set all the extents of the base
					editor screen.
	************************************************ */
int setExtent(void)
{
	struct text_info tmp;

	gettextinfo(&tmp);

	gMAXROWS	= tmp.screenheight;
	gMAXCOLS	= tmp.screenwidth;

	gTOP	= 3;
	gBOTTOM = 1;
	gLEFT	= 2;
	gRIGHT = 1;

	gROWS	= (gMAXROWS - gTOP - gBOTTOM);
	gCOLS	= (gMAXCOLS - gLEFT - gRIGHT);

	return(0);
}

/* ************************************************
	Function : drawOuter
	Purpose	: To draw outer box.
	************************************************ */

int drawOuter(unsigned int index,int job, char *title)
{
	int i,j,lim, len;
	char uleft, uright, dleft, dright, hsymb, lvsymb, scrlBase;

	hsymb	= (char) '\Í';
	lvsymb= (char) '\º';
	scrlBase	= (char) '\±';
	uleft	= (char) '\É';
	uright = (char) '\»';
	dleft = (char) '\È';
	dright = (char) '\¼';

	if(!index)
		setExtent();
	else {

		for(lim=1,i=9; index>i; i=(i*10)+9,lim++);

		gLEFT += lim;
		gCOLS -= lim;
	}

	if(!job || job == 1) { /* Upper line */
		len = strlen(title);
		gotoxy(gLEFT-1, gTOP-1);
		cprintf("%c", uleft);

		for(i=gLEFT; i<=gMAXCOLS-gRIGHT; i++)	cprintf("%c",hsymb);
		cprintf("%c", uright);

		if(len) {
/*			gotoxy((gLEFT-1)+(gCOLS/2)-(len/2)+2,gTOP-1);
			cprintf("%c %s %c",'¹',title,'Ì');
*/			gotoxy(gLEFT+gCOLS-len-2,gTOP-1);
			cprintf("%c%s%c",'¹',title,'Ì');
		}
	}

	if(!job || job==2) { /* Middle Portion */
		for(i=gTOP; i<gMAXROWS-gBOTTOM; i++) {
			gotoxy(gLEFT-1,i);  cprintf("%c",lvsymb);
			gotoxy(gMAXCOLS-gRIGHT+1,i);
			if(i==gTOP)
				cprintf("%c",'');
			else if(i==gMAXROWS-gBOTTOM-1)
				cprintf("%c",'');
			else
				cprintf("%c",scrlBase);
		}
	}

	if(!job || job==3) { /* Lower line */
		gotoxy(gLEFT-1, gMAXROWS-gBOTTOM);
		cprintf("%c", dleft);

		for(i=gLEFT; i<gMAXCOLS-gRIGHT; i++) {
			if(i<=18)	cprintf("%c",hsymb);
			else if(i==19)	cprintf("%c",(char) 17);
			else if(i==gMAXCOLS-gRIGHT-1)	cprintf("%c",'');
			else	cprintf("%c",scrlBase);
		}
		cprintf("%c%c", hsymb,dright);

		if(gLinecount) {
			gotoxy(gLEFT+1,gMAXROWS-gBOTTOM);
			cprintf("Lines:%d",gLinecount);
		}
	}
	return(0);
}

/* ************************************************
	Function : readLine
	Purpose	: To read a line from file descripter.
	************************************************ */
int readLine(FILE **file, char *buf)
{
	int count=0;
	char ch;

	while (1){
		ch = getc(*file);
		if((ch=='\n') || (ch==EOF)) {
			*(buf+count) = '\0';
			break;
		}
		*(buf+count) = ch;
		count++;
	}
	return(count);
}

/* ************************************************
	Function : buildList
	Purpose	: To build-up the linked list of the
					lines from the file descriptor.
	************************************************ */
int buildList(FILE **file, typLine **root, typLine **end)
{
	typLine *item;
	char *buf;
	int count=0;

	buf = (char *) calloc(1000,sizeof(char));

	if(!buf) return(_MEM_ERROR); /* Termination signal */

	while (!feof(*file) ) {
		readLine(file,buf);

		item = (typLine *) calloc(1,sizeof(typLine));
		item->line = (char *) calloc((strlen(buf)+1),sizeof(char));

		if(!item || !item->line) return(_MEM_ERROR);	/* Termination Signal */

		strcpy(item->line,buf);

		if(!(*root)){
			*root = *end = item;
		} else {
			(*end)->next = item;
			item->pre = *end;
			*end = item;
		}

		count++;
	}

	free(buf);
	return(count);
}


/* ************************************************
	Function : openFile
	Purpose	: To open file.
	************************************************ */

int openFile(FILE **file, char *filename, int mode)
{
	switch (mode) {
		case _READ:
			if(!access(filename,4)) {
				*file = fopen(filename,"r");
			} else return(1);
			break;
		case _WRITE:
			if(!access(filename,2)) {
				*file = fopen(filename,"r+");
			} else return(1);
			break;
		case _TRUNCATE:
			if(!access(filename,2)) {
				*file = fopen(filename,"w");
			} else return(1);
			break;
	}
	return(0);
}

/* ************************************************
	Function : showFile
	Purpose	: To show file on the editor screen.
					line-by-line.
	************************************************ */

typLine *showFile(typLine *list, int xpos)
{
	int y, cx, cy, count ;

	if(!list)	return(list);

	_setcursortype(_NOCURSOR);

	cx = wherex();
	cy = wherey();

	for(count=0; count<gROWS; count++) {

		placeLine(list->line,gLEFT,(count+gTOP),xpos);

		if(list->next)	list = list->next;
		else break;

	}

	if(count == gROWS) list = list->pre;

	for(count++;count<gROWS; count++)
		placeLine("",gLEFT,count+gTOP,xpos);

	_setcursortype(_NORMALCURSOR);

	gotoxy(cx,cy);

	return(list);
}

/* ************************************************
	Function : placeLine
	Purpose	: To place a line on to editor screen.
	************************************************ */

int placeLine(char *line, int x, int y, int xpos)
{
	int loc, tmpx, oldx;
	char rvsymb, lvsymb;

	lvsymb= (char) '\º';
	rvsymb	= (char) '\±';
//	gTABLEN=3;

	loc = _LBOUND;
	oldx = x;

	gotoxy(gLEFT-1,y);	cprintf("%c",lvsymb);

	gotoxy(x,y);

	while ((x <= (gLEFT+gCOLS)) && (*line)) {
		if((*line) == '\t') {
			loc = (gTABLEN * (loc/gTABLEN))+gTABLEN;
			while(((loc-xpos+gLEFT) >= x) && (x <= (gLEFT+gCOLS))) {
				cprintf("%c",gTABCHAR);
				x++;
			}
			x--;
		} else {
			tmpx = loc-xpos+gLEFT;
			if(tmpx >= oldx){
				gotoxy(tmpx,y);
				cprintf("%c",*line);
				x++;
			}
			loc++;
		}
		line++;
	}
	clreol();
	gotoxy(gLEFT+gCOLS+gRIGHT,y);		cprintf("%c",rvsymb);
	return(0);
}

/* ************************************************
	Function : getLine
	Purpose	: To get a line, placed 'n' lines back
					or forth.
	************************************************ */

typLine *getLine(typLine *curr,int n, int act)
{

	if(!curr) return(curr);

	for(;n>0;n--)
		if(!act){
			if(curr->pre) curr = curr->pre;
			else break;
		}
		else {
			if(curr->next) curr = curr->next;
			else break;
		}

	return(curr);
}


/* ************************************************
	Function : getcurrLine
	Purpose	: To get the line on which cursor is
					currently blinking.
	************************************************ */

typLine *getcurrLine(typLine *first,typLine *end,int *y)
{
	int oldY;

	oldY = *y;

	if(!first) {
		(*y) = gTOP;
		return(first);
	}

	for((*y)=gTOP; ((*y <= oldY) && (first != end)); ++*y)
		first = first->next;

	if(first!=end) {
		--*y;
		first = first->pre;
	}

	return(first);
}

