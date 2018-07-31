#include "exconst.c"

/* **********************************
	Variable declaration
	********************************** */

/*	************ End of declration ************ */

/* **********************************
	Function : Definations
	********************************** */

int openFile(FILE **, char *, typAccessMode);
int buildList(FILE **, typLine **, typLine **);
int assemble_boxFile(char *);

int readLine(FILE **, char *);
int placeLine(char *, int , int);
int length(char *);

typLine *showFile(typLine *);
typLine *getcurrLine(typLine *, typLine *, int *);
typLine *getLine(typLine *,int, int);

/*	************ End of defination ************ */

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
			loc = (gTablen * (loc/gTablen))+gTablen;
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
	char *buf, *line;
	int count=0;

	*root = *end = NULL;

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

int openFile(FILE **file, char *filename, typAccessMode mode)
{
	int res = 0;

	switch (mode) {
		case opnRead:
			if(!access(filename,4)) {
				*file = fopen(filename,"r");
			} else res = 1;
			break;
		case opnWrite:
			if(!access(filename,2)) {
				*file = fopen(filename,"r+");
			} else res = 1;
			break;
		case opnTruncate:
			*file = fopen(filename,"w");
			res = !*file;
			break;
		default:
			res = 1;
			break;
	}
	return(res);
}

/* ************************************************
	Function : showFile
	Purpose	: To show file on the editor screen.
					line-by-line.
	************************************************ */

typLine *showFile(typLine *list)
{
	int x, cx, cy, count ;

	if(!list)	return(list);

	_setcursortype(_NOCURSOR);

	cx = wherex();
	cy = wherey();

	for(count=0; count <= actWin->scaleHeight; count++) {

		placeLine(list->line,actWin->scaleLeft,(count+actWin->scaleTop));

		if(list->next)	list = list->next;
		else break;

	}

	if(count <= actWin->scaleHeight)
		clearWindow(count+actWin->scaleTop+1,symbTight); /* Clearing the rest window space */
	else list = list->pre;

	_setcursortype(_NORMALCURSOR);

	gotoxy(cx,cy);

	return(list);
}

/* ************************************************
	Function : placeLine
	Purpose	: To place a line on to editor screen.
	************************************************ */

int placeLine(char *line, int x, int y)
{
	int loc, tmpx, oldx, lastx;
	char rvsymb, lvsymb;

	loc = _LBOUND;
	oldx = x;

	gotoxy(actWin->left,y);	cprintf("%c",symbVerti);

	gotoxy(x,y);
	lastx = actWin->scaleLeft+actWin->scaleWidth;
	while ((x <= lastx) && (*line)) {
		if((*line) == '\t') {
			loc = (gTablen * (loc/gTablen))+gTablen;
			while(((loc-boxFile->offset+actWin->scaleLeft) >= x)
					&& (x <= lastx)) {
				cprintf("%c",gTabChar);
				x++;
			}
			x--;
		} else {
			tmpx = loc - boxFile->offset + actWin->scaleLeft;
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
	gotoxy(actWin->left+actWin->width,y);	cprintf("%c",symbVerti);

	return(0);
}

/* ************************************************
	Function : getcurrLine
	Purpose	: To get the line on which cursor is
					currently blinking.
	************************************************ */

typLine *getcurrLine(typLine *first,typLine *end,int *y)
{
	int oldY;

	if((*y) >= (actWin->scaleTop + actWin->scaleHeight))
		*y = (actWin->scaleTop + actWin->scaleHeight);

	oldY = *y;

	if(!first) {
		(*y) = actWin->scaleTop;
		return(first);
	}

	for((*y)=actWin->scaleTop; ((*y <= oldY) && (first != end)); ++*y)
		first = first->next;

	if(first!=end) {
		--*y;
		first = first->pre;
	}

	return(first);
}

/* ************************************************
	Function : assemble_boxFile
	Purpose	: open the given file, and assemble a
					boxFile of its contents.
	************************************************ */

int assemble_boxFile(char *filename)
{
	static int id;
	int lines;

	FILE *file;
	typLine *root, *end;
	typFile *newFile, *lastFile;

	if(openFile(&file,filename, opnRead) == _CAN_NOT_OPEN)
		return(_CAN_NOT_OPEN);

	if((lines=buildList(&file,&root,&end)) == _MEM_ERROR)
		quit(_MEM_ERROR);

	newFile = (typFile *) calloc(1,sizeof(typFile));

	newFile->id = ++id;

	newFile->filename = (char *) calloc(strlen(filename),sizeof(char));

	strcpy(newFile->filename,strupr(filename));
	newFile->filetitle = newFile->filename;

	newFile->root = root;
	newFile->end = end;
	newFile->first = root;
	newFile->curr = root;

	newFile->offset = 0;
	newFile->hasChanged = _FALSE;

	newFile->lines = lines;

	if(!Folder) {
		Folder = boxFile = newFile;
	} else {
		lastFile = Folder->pre;
		lastFile->next = newFile;
		newFile->pre = lastFile;
		boxFile = lastFile;
	}

	Folder->pre = boxFile;
	boxFile->next = Folder;

	fclose(file);

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
		if(!act && curr->pre) curr = curr->pre;
		else if(act && curr->next) curr = curr->next;
		else break;

	return(curr);

}
