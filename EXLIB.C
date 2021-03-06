#include "exconst.c"

/* **********************************
	Function : Definations
	********************************** */

int setExtent(void);
int setEnv(void);

int getCtrl(void);
int getAlt(void);
int getShift(void);
int setTabs(int);
int makeSound(void);

int showLineNos(unsigned int, unsigned int);
int showMess(char *, char *);
int showMode(void);

int drawWin(typWindow *, typDrawJob);
int defineWindow(int, int, int, int, char *);
int activateWindow(typWindow *);
int clearWindow(int, typSymbols);

int setexMode(typexMode mode);

char convert(int);
char getKey();
char *getPtr(char *, char);
int fillBox(int, int, int, int, char);
int drawBox(int, int, int, int, typDrawStyle);

int to_bin(char *, int);
int to_sdate(char *, int);
int to_dec(char *, int);

/*	************ End of defination ************ */

/* **********************************
	Variable declaration
	********************************** */
int 	lenNotice = 18;

/*	************ End of declration ************ */

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

	textcolor(gscrforeColor);
	lowvideo();

	return(0);
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

	gMaxRows	= tmp.screenheight;
	gMaxCols	= tmp.screenwidth;

	gTop	= 2;
	gBottom = 1;
	gLeft	= 1;
	gRight = 0;

	return(0);
}

/* ************************************************
	Function : makeSound
	Purpose	: To make a sound from the PC-Speaker.
	************************************************ */

int makeSound(void)
{
	sound(7);
	delay(60);
	nosound();

	return(0);
}

/* ************************************************
	Function : setexMode
	Purpose	: To set the editor mode.
	************************************************ */

int setexMode(typexMode mode)
{
	static typexMode lastmode;

	if(mode) {
		lastmode = gEdMode;
		gEdMode = mode;
	} else if (lastmode)
		gEdMode = lastmode;

	return(0);

}

/* ************************************************
	Function : getShift
	Purpose	: To determine whether the CTRL key is
					pressed or not?
	************************************************ */
int getShift(void)
{
	int key;
	key=bioskey(2);
	if(key & 0x01)	return(1);	// Left Shift Pressed
	else if(key & 0x012)	return(2);	// Rightt Shift Pressed
	else	return(0);
}

/* ************************************************
	Function : getCTRL
	Purpose	: To determine whether the CTRL key is
					pressed or not?
	************************************************ */
int getCtrl(void)
{
	int key;
	key=bioskey(2);
	if(key & 0x04)	return(1);	// CTRL Pressed
	else if(key & 0x0100)	return(2);	// Left CTRL Pressed
	else if(key & 0x0400)	return(3);	// Right CTRL Pressed
	else	return(0);
}

/* ************************************************
	Function : getALT
	Purpose	: To determine whether the ALT key is
					pressed or not?
	************************************************ */

int getAlt(void)
{
	int key;
	key=bioskey(2);
	if(key & 0x08)	return(1);	// ALT Pressed
	else if(key & 0x0200)	return(2);	// Left ALT Pressed
	else if(key & 0x0800)	return(3);	// Right ALT Pressed
	else	return(0);
}

/* ************************************************
	Function : Convert
	Purpose	: To convert the bioskey code into
					respective character.
	************************************************ */
char convert(int key)
{
	char ch;

	if (isalnum(key & 0xFF) ){
		ch = (char) key;
//		if ( key == 20011 || key == 3317 ) ch = (char) '+';
	} else
		switch (key) {

//			case _SPC_KEY: ch = _SPC_KEY;	break;
//			case _ENT_KEY: ch = _ENT_KEY;	break;

			case _INS_KEY: ch = (char) _INS_KEY;	break;
			case _DEL_KEY:	ch = (char) _DEL_KEY;	break;
			case _HOM_KEY: ch = (char) _HOM_KEY;	break;
			case _END_KEY:	ch = (char) _END_KEY;	break;
			case _PGU_KEY:	ch = (char) _PGU_KEY;	break;
			case _PGD_KEY: ch = (char) _PGU_KEY;	break;
			case _ESC_KEY: ch = (char) _ESC_KEY;	break;
			case _BSP_KEY: ch = (char) _BSP_KEY;	break;

			case _UARROW_KEY: ch = (char) _UARROW_KEY;		break;
			case _DARROW_KEY: ch = (char) _DARROW_KEY;		break;
			case _LARROW_KEY: ch = (char) _LARROW_KEY;		break;
			case _RARROW_KEY: ch = (char) _RARROW_KEY;		break;

			case 14624:	ch = (char) ' ';	break;
			case 7181:	ch = (char) '\n';	break;
			case 3849:	ch = (char) '\t';	break;
			case 3840:	ch = (char) '\b';	break;
			case 10592: ch = (char) '\`'; 	break;
			case 10622: ch = (char) '\~'; 	break;
			case 545: 	ch = (char) '\!'; 	break;
			case 832: 	ch = (char) '\@'; 	break;
			case 1059: 	ch = (char) '\#';  	break;
			case 1316: 	ch = (char) '\$'; 	break;
			case 1573: 	ch = (char) '\%'; 	break;
			case 1886: 	ch = (char) '\^'; 	break;
			case 2086: 	ch = (char) '\&'; 	break;
			case 2346:
			case 14122:	ch = (char) '\*'; 	break;
			case 2600: 	ch = (char) '\('; 	break;
			case 2857: 	ch = (char) '\)'; 	break;
			case 3117:
			case 18989:	ch = (char) '\-'; 	break;
			case 3167: 	ch = (char) '\_'; 	break;
			case 3317:
			case 20011:	ch = (char) '\+'; 	break;
			case 3389: 	ch = (char) '\='; 	break;
			case 11132:	ch = (char) '\|'; 	break;
			case 11100: ch = (char) '\\'; 	break;
			case 6779: 	ch = (char) '\{'; 	break;
			case 7037: 	ch = (char) '\}'; 	break;
			case 6747: 	ch = (char) '\['; 	break;
			case 7005: 	ch = (char) '\]'; 	break;
			case 10042:	ch = (char) '\:'; 	break;
			case 10043:	ch = (char) '\;'; 	break;
			case 10274: ch = (char) '\"'; 	break;
			case 10279:	ch = (char) '\''; 	break;
			case 13116:	ch = (char) '\<'; 	break;
			case 13374:	ch = (char) '\>'; 	break;
			case 13100:	ch = (char) '\,'; 	break;
			case 13358:
			case 21294:	ch = (char) '\.'; 	break;
			case 13631:	ch = (char) '\?'; 	break;
			case 13615:	ch = (char) '\/'; 	break;

			case _F1_KEY:	ch = (char) _F1_KEY;	break;
			case _F2_KEY:	ch	= (char) _F2_KEY;	break;
			case _F3_KEY:	ch	= (char) _F3_KEY;	break;
			case _F4_KEY:	ch = (char) _F4_KEY;	break;
			case _F5_KEY:	ch	= (char) _F5_KEY;	break;
			case _F6_KEY:	ch	= (char) _F6_KEY;	break;
			case _F7_KEY:	ch = (char) _F7_KEY;	break;
			case _F8_KEY:	ch	= (char) _F8_KEY;	break;
			case _F9_KEY:	ch	= (char) _F9_KEY;	break;
			case _F10_KEY:	ch = (char) _F10_KEY;	break;

			case _SF1_KEY:	ch = (char) _SF1_KEY;	break;
			case _SF2_KEY:	ch	= (char) _SF2_KEY;	break;
			case _SF3_KEY:	ch	= (char) _SF3_KEY;	break;
			case _SF4_KEY:	ch = (char) _SF4_KEY;	break;
			case _SF5_KEY:	ch	= (char) _SF5_KEY;	break;
			case _SF6_KEY:	ch	= (char) _SF6_KEY;	break;
			case _SF7_KEY:	ch = (char) _SF7_KEY;	break;
			case _SF8_KEY:	ch	= (char) _SF8_KEY;	break;
			case _SF9_KEY:	ch	= (char) _SF9_KEY;	break;
			case _SF10_KEY: 	ch = (char) _SF10_KEY;	break;

			default: ch = (char) 238;
		}
//	ch = (char) ch;
	return(ch);
}

/* ************************************************
	Function : getKey
	Purpose	: To get a key press from keyboard
	************************************************ */

char getKey()
{
	int key;

	fflush(stdin);	fflush(stdout);
	key = bioskey(0);

	return(convert(key));
}

/* ************************************************
	Function : getKey
	Purpose	: To get a key press from keyboard
	************************************************ */

int getKeys(bool *isCtrl, bool *isShift, bool *isAlt)
{
	int actKey, spclKey;

//	while (bioskey(1) == 0);
	*isCtrl = *isShift = *isAlt = _FALSE;

		fflush(stdin);	fflush(stdout);
	actKey = bioskey(0);
		fflush(stdin);	fflush(stdout);
	spclKey = bioskey(2);

	if (spclKey)
	{
		if (spclKey & RIGHT) *isShift = _TRUE;
		if (spclKey & LEFT)  *isShift = _TRUE;
		if (spclKey & CTRL)  *isCtrl = _TRUE;
		if (spclKey & ALT)   *isAlt = _TRUE;
	}

	return(actKey);
}

/* ************************************************
	Function : showNum
	Purpose	: To print line numbers.
	************************************************ */

int showLineNos(unsigned int start, unsigned int lim)
{
	int y;
	int lastY;

	lastY = actWin->scaleTop + actWin->scaleHeight;

	for(y=actWin->scaleTop; (y <= lastY ) && (start <= lim); y++) {
		gotoxy(actWin->left+1,y);
		cprintf("%d",start++);
	}

	return(0);

}

/* ************************************************
	Function : setTabstr
	Purpose	: To set the spaces for tabs.
	************************************************ */

int setTabs(int len)
{
	int i;

	for(i=0;i<len;i++)	gTabStr[i] = gTabChar;
	gTabStr[i] = '\0';

	return(0);
}

/* ************************************************
	Function : showMess
	Purpose	: To show message on the help-line.
	************************************************ */

int showMess(char *title, char *mess)
{
	int currx, curry;
	int len;
	char *msg;

	currx = wherex();
	curry = wherey();

	gotoxy(1,gMaxRows);

	if(!mess) return(0);

	msg = (char *) calloc(gMaxCols,sizeof(char));

	strncpy(msg,mess,gMaxCols-(strlen(title)+3));

	if(title) {
		highvideo();
		cprintf("%s: ",title);
		lowvideo();
	}
	cprintf("%s",msg);
	clreol();

	gotoxy(currx,curry);

	free(msg);

	return(0);
}

/* ************************************************
	Function : showMode
	Purpose	: To show the current editing mode.
	************************************************ */

int showMode(void)
{
	int x, oldcursx, oldcursy;

	oldcursx = wherex();
	oldcursy = wherey();

	gotoxy(actWin->left+1,actWin->top+actWin->height);

	for(x=1; x < actWin->lenNotice; x++)
		cprintf("%c",symbHoriz);

	highvideo();	/* setting video to high. */
	gotoxy(actWin->left+3,actWin->top+actWin->height);
	cprintf("[ %s ]",lstexMode[gEdMode-1]);
	lowvideo();		/* setting video to low. */

	gotoxy(oldcursx,oldcursy);

	return(0);
}

/* ************************************************
	Function : drawOuter
	Purpose	: To draw outer box.
	************************************************ */

int drawWin(typWindow *win, typDrawJob job)
{
	int x,y, len, count;

	if(!job || job == prnTop) { 		/* Upper line */

		gotoxy(win->left,win->top);
		cprintf("%c", symbUpLeft);

		for(x=1; x < win->width; x++)	cprintf("%c",symbHoriz);
		cprintf("%c", symbUpRight);

		gotoxy(win->left + 2, win->top);
		cprintf("[%c]",symbSolid1);

		len = strlen(win->caption) + 4;
		if(win->caption) {
			switch(win->capAlign) {
				case alignRight:
					gotoxy((win->left + win->width - len), win->top);
					break;
				case alignLeft:
					gotoxy(win->left + 7, win->top);
					break;
				default:
					gotoxy(win->left + (win->width / 2) - (len / 2), win->top);
					break;
			}
			cprintf("%c%s%c",symbRightBar,win->caption,symbLeftBar);
		}
	}

	if(!job || job == prnLeft || job == prnRight) { 	/* Left & Right line */

		for(y = win->top+1; y < win->top+win->height; y++) {

			if(!job || job == prnLeft) {
				gotoxy(win->left,y);
				cprintf("%c",symbVerti);
			}

			if(!job || job == prnRight) {
				gotoxy(win->left+win->width,y);
				cprintf("%c",symbVerti);
			}
		}
	}

	count = win->sepCount;
	while(count--) {

		if(!win->sepLine[count]) continue;

		gotoxy(win->left,win->top+win->sepLine[count]);
		cprintf("%c",symbLeftBar);

		for(x=1; x < win->width; x++)	cprintf("%c",symbHoriz);
		cprintf("%c", symbRightBar);

	}

	if(!job || job == prnBottom) { 			/* Lower line */

		gotoxy(win->left,win->top+win->height);
		cprintf("%c", symbDnLeft);

		for(x=1; x < win->width; x++)	cprintf("%c",symbHoriz);
		cprintf("%c", symbDnRight);

	}

	return(0);

}

/* ************************************************
	Function : defineWindow
	Purpose	: Used to define the window.
	************************************************ */

int defineWindow(int left, int top, int height, int width, char *caption)
{
	static int id;
	typWindow *newWin, *lastWin;


	if(!left) left = gLeft;
	if(!top) top = gTop;
	if(!height) height = gMaxRows - gTop - gBottom;
	if(!width) width = gMaxCols - gLeft - gRight;

	if(width < 20) width = 20;
	if(height < 5) height = 5;

	newWin = (typWindow *) calloc(1,sizeof(typWindow));

	newWin->id = ++id;

	if(caption) {

		newWin->caption = (char *) calloc(strlen(caption)+1,sizeof(char));
		strcpy(newWin->caption,caption);

	}

	newWin->capAlign = alignRight;

	newWin->left = left;
	newWin->top = top;
	newWin->width = width;
	newWin->height = height;

	newWin->scaleLeft = left + 1;
	newWin->scaleTop = top + 1;
	newWin->scaleWidth = newWin->width - (newWin->scaleLeft - newWin->left) - 1;
	newWin->scaleHeight = newWin->height - (newWin->scaleTop - newWin->top) - 1;

	newWin->cursx = newWin->scaleLeft;
	newWin->cursy = newWin->scaleTop;

	newWin->lenNotice = 18;

	newWin->lastdata = NULL;

	newWin->hasVertiScrl = _FALSE;
	newWin->hasVertiScrl = _FALSE;

	if(!baseWin) {
		baseWin = actWin = newWin;
	} else {
		lastWin = baseWin->pre;
		lastWin->next = newWin;
		newWin->pre = lastWin;
		actWin = lastWin;
	}

	baseWin->pre = actWin;
	actWin->next = baseWin;

	return(0);

}

/* ************************************************
	Function : activateWindow
	Purpose	: Used to activate the window.
	************************************************ */

int activateWindow(typWindow *win)
{

	drawWin(win,prnAll);
	boxFile->last = (typLine *) showFile(boxFile->first,boxFile->offset);

	return(0);

}

/* ************************************************
	Function : clearWindow
	Purpose	: Used to clear the window upto last
					line from the current line.
	************************************************ */

int clearWindow(int y, typSymbols backChar)
{
	int x;

	for(;y<actWin->top+actWin->height; y++) {
			gotoxy((x=actWin->left+1),y );
			for(; x < (actWin->left + actWin->width); x++)
				cprintf("%c",backChar);
		}
	return(0);
}

/* *************************************************
	Function : getPtr
	Purpose	: Used to obtain the pointer to the next
					of given character, that exist first
					from the last.
	************************************************** */

char *getPtr(char *path, char ch)
{
	char *ptr;
	ptr = path + strlen(path) - 1;

	while((ptr != path) && (*ptr != ch)) --ptr;

	if(*ptr == ch) ++ptr;

	return(ptr);
}

/* *************************************************
	Function : fillBox
	Purpose	: Used to fill a rectangle of given
					cordinates with the given character.
	************************************************** */

int fillBox(int left, int top, int right, int bottom, char ch)
{
	int x,y;

	y = top;
	while(y <= bottom) {
		x = left;
		gotoxy(x,y++);
		while(x++ <= right)
			cprintf("%c",ch);
	}

	return(0);

}

/* *************************************************
	Function : drawBox
	Purpose	: Used to draw a rectangle of given
					cordinates.
	************************************************** */

int drawBox(int left, int top, int width, int height, typDrawStyle style)
{
	int x,y, maxx, maxy;
	int chlt, chh, chrt, chv, chld, chrd;

	switch (style) {
		case styleSingle:
			chlt = symbMnuUpLeft;
			chh = symbMnuHoriz;
			chrt = symbMnuUpRight;
			chv = symbMnuVerti;
			chld = symbMnuDnLeft;
			chrd = symbMnuDnRight;
			break;
		case styleDouble:
			chlt = symbUpLeft;
			chh = symbHoriz;
			chrt = symbUpRight;
			chv = symbVerti;
			chld = symbDnLeft;
			chrd = symbDnRight;
			break;
	}

	x = left;
	y = top;
	maxx = left + width;
	maxy = top + height;

	gotoxy(x++,y++);			/* Top Line */
	cprintf("%c",chlt);
	for(; x < maxx; x++)	cprintf("%c",chh);
	cprintf("%c",chrt);

	while( y < maxy ) {		/* Middle portion */
		gotoxy(left,y);
		cprintf("%c",chv);
		gotoxy(maxx,y++);
		cprintf("%c",chv);
	}

	x = left;
	gotoxy(x++,maxy);			/* Bottom Line */
	cprintf("%c",chld);
	for(; x < maxx; x++)	cprintf("%c",chh);
	cprintf("%c",chrd);

	return(0);

}

/* *************************************************
	Function : to_bin
	Purpose	: Used to convert a intger number into
					respective binary form.
	************************************************** */
int to_bin(char *str, int num)
{
	char tmp[25];
	int i=0;

	while (num) {
		tmp[i++] = (num % 2) + '0';
		num /= 2;
	}

	while (--i >= 0)	*str++ = tmp[i];
	*str = '\0';

	return(0);
}

/* ********************************************************
	Function : to_dec
	Purpose	: Used to convert n binary bits of
					string to its corresponding decimal number.
	******************************************************** */
int to_dec(char *str, int n)
{
	int dec;
	int num;

	if(!n) return(NULL);

	dec = 0;
	while(n>=0) {
		num = *str - '0';
		dec += num * pow(2,n);
		++str;
		--n;
	}

	return(dec);
}



/* *************************************************
	Function : to_sdate
	Purpose	: Used to convert a intger format of
					date into respective string.
	************************************************** */

int to_sdate(char *str, int date)
{
	int len;
	int day, mon, year;
	char *tmp;
	char *years[] = {	"Jan", "Feb", "Mar", "Apr", "May", "June",
							"July", "Aug", "Sep", "Oct", "Nov", "Dec"
						 };

	to_bin(str,date);
	len = strlen(str);

	day = to_dec(str+(len-=5),4);
	mon = to_dec(str+(len-=4),3);
	year = to_dec(str,--len) + 1980;

	sprintf(str,"%s %d, %d",years[--mon],day,year);
	return(0);
}
