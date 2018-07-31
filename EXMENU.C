#include "exconst.c"

typMenuItem *padMain;
typMenuItem *popFile;
typMenuItem *popEdit;
typMenuItem *popSearch;
typMenuItem *popTask;

typMenuItem *popTaskBeautify;	/* Sub menu of beautify bar. */

int buildMenuSys(void);
int razeMenuSys(void);

int buildpadMain(void);

int buildpopFile(void);
int buildpopEdit(void);
int buildpopSearch(void);
int buildpopTask(void);

int buildpopTaskBeautify(void);

int activateMenuSys(void);

int drawMenu(typMenuItem *, int, int);
int hideMenu(typMenuItem *);

typMenuItem *buildMenu(char **, char **, int);
typMenuItem *(*operateMenu(typMenuItem *, typMenuItem **))(typMenuItem *);
typMenuItem *showMenu(typMenuItem *caller, typMenuItem *menu);
typMenuItem *getMenu(typMenuItem *, int);
int razeMenu(typMenuItem *);

int getheight(typMenuItem *);
int getwidth(typMenuItem *);
int showBar(typMenuItem *, int);

int setpads(typMenuItem *);
int setpops(typMenuItem *);

/* **************************************
	Action for pads
	************************************** */

typMenuItem *actpadFile(typMenuItem *);
typMenuItem *actpadEdit(typMenuItem *);
typMenuItem *actpadSearch(typMenuItem *);
typMenuItem *actpadTask(typMenuItem *);

/* *********************************** */

typMenuItem *actDefault(typMenuItem *);

/* **************************************
	Action for bars of popFile (File pad)
	************************************** */

typMenuItem *actFileNew(typMenuItem *);
typMenuItem *actFileOpen(typMenuItem *);
typMenuItem *actFileSave(typMenuItem *);
typMenuItem *actFileExit(typMenuItem *);

/* *********************************** */

/* **************************************
	Action for bars of popTask (Task pad)
	************************************** */

typMenuItem *actTaskBeautify(typMenuItem *);

/* *********************************** */

/* ************************************************
	Function : buildMenu
	Purpose	: To build up the entire menu system.
	************************************************ */

int buildMenuSys(void)
{
	int oldbkColor;

	oldbkColor = gscrbkColor;
	gscrbkColor = BLACK;

	buildpadMain();

	buildpopFile();
	buildpopEdit();
	buildpopSearch();
	buildpopTask();

	buildpopTaskBeautify();

	drawMenu(padMain, 2, _NONE);

	gscrbkColor = oldbkColor;

	return(0);
}

/* ************************************************
	Function : buildMenus
	Purpose	: To build up the menu pads.
	************************************************ */

typMenuItem *buildMenu(char **list, char **mess, int count)
{
	static int mnuID = 0;
	int i,j,len;
	typMenuItem *head,*item, *last;

	i=0;
	head = item = NULL;

	for(i=0;i<count;i++){

		len = strlen(list[i]);

		item = (typMenuItem *) calloc(1,sizeof(typMenuItem));
		if(!item) quit(_MEM_ERROR);
		item->caption = (char *) calloc(len+1,sizeof(char));
		if(!item->caption) quit(_MEM_ERROR);

		if(mess && mess[i]) {
			item->mess = (char *) calloc(strlen(mess[i])+1,sizeof(char));
			if(!item->mess) quit(_MEM_ERROR);
		}

/*		if(!item || !item->caption)
			return((typMenuItem *) _MEM_ERROR);	/* Termination Signal */

		if(mess && mess[i])	strcpy(item->mess,mess[i]);

		item->mnuid = ++mnuID;
		item->hasSubMenu = _FALSE;
		item->ispad = _FALSE;

		if(!item->ispad)	item->triger = actDefault;
		else	item->triger = NULL;

		item->isdisable = _FALSE;
		item->lastdata = NULL;

		if(list[i]) {
			strcpy(item->caption,list[i]);
			for(j=0;*(item->caption+j);j++)
				if((*(item->caption+j) == '&') && (*(item->caption + ++j))) {
					item->hotkey = *(item->caption+j);
					break;
				}
		}
		else	item->caption = NULL;

		if(!head){
			head = last = item;
		} else {
			last = head->pre;
			last->next = item;
			item->pre = last;
			last = item;
		}

		last->next = head;	/* For cyclic effect */
		head->pre = last;		/* while traversing menus */

	}

	return(head);

}

/* ************************************************
	Function : drawMenu
	Purpose	: To darw menus on screen.
	************************************************ */

int drawMenu(typMenuItem *menu, int spc, int bkcolor)
{
	int x, y, j,k, oldx;
	int oldbkColor;

	typMenuItem *head;
	bool isFirst;

	head = menu;

	x = menu->x;
	y = menu->y;

	if(!menu->ispad) --y;

	if(bkcolor != _NONE)	{
		oldbkColor = gscrbkColor;
		gscrbkColor = bkcolor;
		textbackground(gscrbkColor);
	}

	gotoxy(menu->x,menu->y);
	if(menu->ispad) clreol();

	oldx = menu->x;
	isFirst = _TRUE;

	while(_TRUE){

		delay(10);	/* Just for slide effect */

		menu->x	= x;
		menu->y	= y;

		if(!menu->ispad && isFirst) {
			gotoxy(menu->x-2,menu->y);

			cprintf("%c",(char) symbMnuUpLeft);

			for(k=1;k<=menu->width+1;k++)
				cprintf("%c",(char) symbMnuHoriz);

			cprintf("%c",(char) symbMnuUpRight);

			y++;
			x = oldx;
			isFirst= _FALSE;
			continue;
		}

		if(!menu->ispad) {
			gotoxy(menu->x-2,menu->y);
			cprintf("%c",(char) symbMnuVerti);
			gotoxy(menu->x+menu->width,menu->y);
			cprintf("%c",(char) symbMnuVerti);
			gotoxy(menu->x,menu->y);
		}

		x += showBar(menu, gscrbkColor);

		if(!menu->ispad) {
			y++;
			x = oldx;
		}

		for(j=0;j<spc;j++)
			if(!menu->ispad) y++;
			else x++;

		if(!menu->ispad && menu->next == head) {
			gotoxy(menu->x-2,y);

			cprintf("%c",(char) symbMnuDnLeft);

			for(k=1;k<=menu->width+1;k++)
				cprintf("%c",(char) symbMnuHoriz);

			cprintf("%c",(char) symbMnuDnRight);
		}

		menu = menu->next;
		if(menu == head) break;
	}

	if(bkcolor != _NONE) {
		gscrbkColor = oldbkColor;
		textbackground(gscrbkColor);
	}

	return(0);

}

/* ************************************************
	Function :	showBar
	Purpose	: 	To display a bar on screen at its
					corresponding x, y cordinates.
	************************************************ */

int showBar(typMenuItem *menu, int bkcolor)
{
	int k,x;
	char *caption;
	bool hasHotkey;

	x = 0;
	hasHotkey = _FALSE;
	caption = menu->caption;

	if(caption) {

		textbackground(bkcolor);

		gotoxy(menu->x-1,menu->y);
		for(k=0;k<=menu->width;k++)
			cprintf("%c",symbSpace);

		gotoxy(menu->x,menu->y);

		for(;	*caption ; x++) {
			if(*caption == '&'){
				if(*++caption && *caption != symbSpace) {
					if(!hasHotkey)	{
						highvideo();
						cprintf("%c",*caption++);
						lowvideo();
						hasHotkey = _TRUE;
					}
					continue;
				}
				else break;
			}
			cprintf("%c",*caption++);
		}

		if(menu->hasSubMenu && !menu->ispad) {
			gotoxy(menu->x + menu->width - 1, menu->y);
			cprintf("%c",symbRight);
		}
	} else {
		gotoxy(menu->x-2,menu->y);
		cprintf("%c",(char) symbMnuLeftSep);
		for(k=1;k<=menu->width+1;k++)
			cprintf("%c",(char) symbMnuHoriz);
		cprintf("%c",(char) symbMnuRightSep);
	}

	textbackground(gscrbkColor);

	return(x);
}

/* ************************************************
	Function : buildpadMain
	Purpose	: To build pad bar.
	************************************************ */

int buildpadMain(void)
{
	int width;
	int mnuCount = 8;
	char *lstpadMain[] = {
									"&File","&Edit","&Search","&Task",
									"&View","&Options","&Window","&Help"
								};

	char *mess[] = {
							"File management commands. like Open, Save, Print etc.",
							"Editing job related commands. like Cut, Copy etc.",
							"Commands helpfull in searching & bulk-replacement.",
							"Commands which performs some specific tasks.",
							"Options to set the view of the editor.",
							"Commands to costomize this editor.",
							"Commands related to windows management.",
							"Access on-line help regarding this editor."
						};

	typMenuItem *mnuItem;

	padMain = buildMenu(lstpadMain,mess,mnuCount);
	setpads(padMain);

	mnuItem = padMain;	/* FILE */
	mnuItem->triger = actpadFile;
	mnuItem->x = 6;
	mnuItem->y = 1;

	mnuItem = mnuItem->next; /* Edit */
	mnuItem->triger = actpadEdit;

	mnuItem = mnuItem->next; /* Search */
	mnuItem->triger = actpadSearch;

	mnuItem = mnuItem->next; /* Task */
	mnuItem->triger = actpadTask;

	mnuItem = mnuItem->next; /* View */
	mnuItem->hasSubMenu = _FALSE;

	mnuItem = mnuItem->next; /* Option */
	mnuItem->hasSubMenu = _FALSE;

	mnuItem = mnuItem->next; /* Window */
	mnuItem->hasSubMenu = _FALSE;

	mnuItem = mnuItem->next; /* Help */
	mnuItem->hasSubMenu = _FALSE;

	return(0);
}

/* ************************************************
	Function : buildpopFile
	Purpose	: To build the File popup.
	************************************************ */

int buildpopFile(void)
{
	typMenuItem *mnuItem;
	int mnuCount = 14;

	char *list[] = {
							"&New","&Open...","&Save","S&ave as...",
							NULL,"Sa&ve all",
							NULL,"&Close","C&lose all",
							NULL,
							"&Print","Pa&ge setup",
							NULL,"E&xit"
						};

	char *mess[] = {
							"To create new file.",
							"To open an existing file.",
							"To save the changes commited in current file.",
							"To save the current file with changes commited with another name.",
							NULL,
							"To save the changes of all the opened files.",
							NULL,
							"To close the current file.",
							"To close all the files.",
							NULL,
							"To print contents of the current file.",
							"To set the print & page settings for printing.",
							NULL,
							"To quit from the current session."
						};

	popFile = buildMenu(list,mess,mnuCount);

	mnuItem = popFile; 			/*	New */
	mnuItem->height = getheight(mnuItem);
	mnuItem->triger = actFileNew;

	mnuItem = mnuItem->next; 	/*	Open */
	mnuItem->triger = actFileOpen;

	mnuItem = mnuItem->next;	/*	Save */
	mnuItem->triger = actFileSave;

	mnuItem = mnuItem->next;	/* Save as */

	mnuItem = mnuItem->next;	/* Seprator */

	mnuItem = mnuItem->next;	/* Save All */

	mnuItem = mnuItem->next;	/* Seprator */

	mnuItem = mnuItem->next;	/* Close */

	mnuItem = mnuItem->next;	/* Close All */

	mnuItem = mnuItem->next;	/* Seprator */

	mnuItem = mnuItem->next;	/* Print */

	mnuItem = mnuItem->next;	/* Page Setup */

	mnuItem = mnuItem->next;	/* Seprator */

	mnuItem = mnuItem->next;	/* Exit */
	mnuItem->triger = actFileExit;

	setpops(popFile);

	return(0);
}

/* ************************************************
	Function : buildpopEdit
	Purpose	: To build the Edit popup.
	************************************************ */

int buildpopEdit(void)
{
	typMenuItem *mnuItem;
	int mnuCount = 8;

	char *list[] = {
							"&Undo","&Redo",
							NULL,"Cu&t","&Copy","&Paste",
							NULL,"C&lear clipboard"
						};

	char *mess[] = {
							"Undo the previous task commited.",
							"Redo the previously Undo operation.",
							NULL,
							"Move selected text into the clipboard.",
							"Copy selected text into the clipboard.",
							"Copy text onto current cursor position from the clipboard.",
							NULL,
							"To refresh the clipboard.",
						};

	popEdit = buildMenu(list,mess,mnuCount);

	mnuItem = popEdit; 			/*	Undo */
	mnuItem->height = getheight(mnuItem);

	mnuItem = mnuItem->next; 	/*	Redo */

	mnuItem = mnuItem->next;	/* Seprator */

	mnuItem = mnuItem->next;	/* Cut */

	mnuItem = mnuItem->next;	/* Copy */

	mnuItem = mnuItem->next;	/* Paste */

	mnuItem = mnuItem->next;	/* Seprator */

	mnuItem = mnuItem->next;	/* Clear clipboard */

	setpops(popEdit);

	return(0);
}

/* ************************************************
	Function : buildpopSearch
	Purpose	: To build the Search popup.
	************************************************ */

int buildpopSearch(void)
{
	typMenuItem *mnuItem;
	int mnuCount = 7;

	char *list[] = {
							"&Find...","Find &next",
							NULL,"&Replace...","R&eplace last find",
							NULL,"&Goto line number..."
						};

	char *mess[] = {
							"To seek-out some text within the file scope.",
							"To repeate last find.",
							NULL,
							"To search & replace the selected text with given new one.",
							"To replace the selected text in last find, with given new one.",
							NULL,
							"To reach up to a given line number.",
						};

	popSearch = buildMenu(list,mess,mnuCount);

	mnuItem = popSearch; 	   /* Find */
	mnuItem->height = getheight(mnuItem);

	mnuItem = mnuItem->next; 	/*	Find next */

	mnuItem = mnuItem->next;	/* Seprator */

	mnuItem = mnuItem->next;	/* Replace */

	mnuItem = mnuItem->next;	/* Replace last find */

	mnuItem = mnuItem->next;	/* Seprator */

	mnuItem = mnuItem->next;	/* Goto line number */

	setpops(popSearch);

	return(0);
}

/* ************************************************
	Function : buildpopTask
	Purpose	: To build the task popup.
	************************************************ */

int buildpopTask(void)
{
	typMenuItem *mnuItem;
	int mnuCount = 3;

	char *list[] = {
							"&Beautify",
							NULL,"&Compile with..."
						};

	char *mess[] = {
							"Provides a standard structure to your source-code.",
							NULL,
							"To compile your source-code with specified command-line."
						};

	popTask = buildMenu(list,mess,mnuCount);

	mnuItem = popTask; 	   /* Beautify */
	mnuItem->triger = actTaskBeautify;
	mnuItem->height = getheight(mnuItem);
	mnuItem->hasSubMenu = _TRUE;

	mnuItem = mnuItem->next;	/* Seprator */

	mnuItem = mnuItem->next;	/* Compile with... */

	setpops(popTask);

	return(0);
}

/* ************************************************
	Function : buildpopTaskBeautify
	Purpose	: To build the TaskBeautify popup.
	************************************************ */

int buildpopTaskBeautify(void)
{
	typMenuItem *mnuItem;
	int mnuCount = 6;

	char *list[] = {
							"&1TBS","&Allman","&Whitesmiths","&GNU",
							NULL,
							"&My Style"
						};

	char *mess[] = {
							"One True Bracing Style, used by demigods Kernighan & Ritchie. (K&R Style)",
							"Introduced by Eric Allman, used in writing BSD Utilities. (BSD Style)",
							"Whitesmiths C compiler documentation style.",
							"A hybrid of Allman & Whitesmith, used in writing GNU EMACS code.",
							NULL,
							"Let bankey employ his conventions over your source-code."
						};

	popTaskBeautify = buildMenu(list,mess,mnuCount);

	mnuItem = popTaskBeautify;   	/* 1TBS */
	mnuItem->height = getheight(mnuItem);

	mnuItem = mnuItem->next;		/* Allman */

	mnuItem = mnuItem->next;		/* Whitesmith */

	mnuItem = mnuItem->next;		/* GNU */

	setpops(popTaskBeautify);

	return(0);
}

/* ************************************************
	Function :	setpads
	Purpose	: 	To set each menu item as pad.
	************************************************ */

int setpads(typMenuItem *menu)
{
	typMenuItem *head;

	head = menu;

	while(_TRUE) {

		menu->hasSubMenu = _TRUE;
		menu->ispad	=	_TRUE;
		menu->width =	strlen(menu->caption);
		menu->height = 1;

		menu=menu->next;
		if(head == menu) break;

	}

	return(0);

}

/* ************************************************
	Function :	setpops
	Purpose	: 	To set the width with each menu item.
	************************************************ */

int setpops(typMenuItem *menu)
{
	int width, height;
	typMenuItem *head;

	head = menu;

	width = getwidth(menu);
	height = getheight(menu);

	while(_TRUE) {

		menu->width = width;
		menu->height = height;

		menu=menu->next;

		if(menu == head) break;

	}

	return(0);

}

/* ************************************************
	Function :	getwidth
	Purpose	: 	To determine the maximun width
					possible for any menu set.
	************************************************ */

int getwidth(typMenuItem *menu)
{
	int Maxlen, len;
	typMenuItem *head;
	bool hasSubMenu;

	Maxlen = 0;
	head = menu;

	hasSubMenu = _FALSE;
	while(_TRUE) {

		len = strlen(menu->caption);
		if(Maxlen < len) Maxlen = len;
		menu=menu->next;

		if(!hasSubMenu && menu->hasSubMenu)	hasSubMenu = _TRUE;

		if(menu == head) break;

	}

	if(hasSubMenu) ++Maxlen;

	return(Maxlen);

}

/* ************************************************
	Function :	getheight
	Purpose	: 	To determine the possible height
					from the given menu.
	************************************************ */

int getheight(typMenuItem *menu)
{
	int height;
	typMenuItem *head;

	height = 0;
	head = menu;

	while(menu) {

		++height;

		menu=menu->next;

		if(head == menu) break;

	}

	return(height);

}

/* *****************************************************
	Function : activateMenuSys
	Purpose	: To activate the menu system for use.
	***************************************************** */

int activateMenuSys(void)
{
	int oldcursx, oldcursy;

	typMenuItem *actMenu;
	typMenuItem *(*triger)(typMenuItem *);

	actMenu = NULL;

	oldcursx = wherex();
	oldcursy = wherey();

	_setcursortype(_NOCURSOR);
	triger = operateMenu	(padMain,&actMenu);
	_setcursortype(_NORMALCURSOR);

	showMess(NULL,NULL); /* To make the help-bar empty */
	if(actMenu->ispad) showBar(actMenu,gscrbkColor);

	gotoxy(oldcursx,oldcursy);

	if(triger)
		if(!triger(actMenu))	return(1);

	return(0);

}

/* *****************************************************
	Function : operateMenu
	Purpose	: To operate the menu system.
	***************************************************** */

typMenuItem *(*operateMenu(typMenuItem *menu, typMenuItem **actMenu))(typMenuItem *)
{

	typMenuItem *(*triger)(typMenuItem *);
	int key;

	if(!menu) return(NULL);

	while(_TRUE) {

		showBar(menu,gmnubkColor);
		showMess("Tips",menu->mess);

		switch ((key = getKey())) {
			case _ENT_KEY:
				if(menu->hasSubMenu) {
					if(!menu->isdisable && menu->triger) {
						triger = operateMenu(menu->triger(menu),actMenu);
						hideMenu(menu);
						if(triger) 	{
							showBar(menu,gscrbkColor);
							return(triger);
						}
					}
				} else {
					*actMenu = menu;
					return(menu->triger);
				}
				break;
			case _ESC_KEY:
				showBar(menu,gscrbkColor);
				return(NULL);
			case _UARROW_KEY:
				if(menu->ispad) break;
				if(!menu->pre) break;
				showBar(menu,gscrbkColor);
				menu = getMenu(menu,key);
				break;
			case _LARROW_KEY:
				if(!menu->ispad) break;
				if(!menu->pre) break;
				showBar(menu,gscrbkColor);
				menu = getMenu(menu,key);
				break;
			case _DARROW_KEY:
				if(menu->ispad) break;
				if(!menu->next) break;
				showBar(menu,gscrbkColor);
				menu = getMenu(menu,key);
				break;
			case _RARROW_KEY:
				if(!menu->ispad) break;
				if(!menu->next) break;
				showBar(menu,gscrbkColor);
				menu = getMenu(menu,key);
				break;
			default: continue;
		}
	}
}

/* ************************************************
	Function :	showMenu
	Purpose	: 	To show the given menu.
	************************************************ */

typMenuItem *showMenu(typMenuItem *caller, typMenuItem *menu)
{
	char buf[4096];

	if(caller->ispad) {
		if((menu->width + caller->x + 1) <= gMaxCols)
			menu->x = caller->x + 1;
		else	menu->x = caller->x - menu->width - 1;

		menu->y = caller->y+2;
	} else {
		if((menu->width + caller->x + caller->width + 1) <= gMaxCols)
			menu->x = caller->x + caller->width + 3;
		else	menu->x = caller->x - menu->width - 3;

		menu->y = caller->y;
	}

	gettext(menu->x-2,menu->y-1,(menu->x+menu->width),(menu->y+menu->height+1),buf);

	caller->item = menu;
	caller->lastdata = (char *)	calloc(strlen(buf)+1,sizeof(char));
	if(!caller->lastdata) quit(_MEM_ERROR);

	strcpy(caller->lastdata,buf);

	drawMenu(menu, 0, _NONE);

	return(menu);

}

/* ************************************************
	Function :	hideMenu
	Purpose	: 	To hide the given menu.
	************************************************ */

int hideMenu(typMenuItem *menu)
{
	char *lastdata;
	typMenuItem *item;

	lastdata = menu->lastdata;
	item = menu->item;

	puttext(item->x-2,item->y-1,(item->x+item->width),(item->y+item->height+1),lastdata);

	free(lastdata);

	menu->lastdata = NULL;
	menu->item = NULL;

	return(0);
}

/* ************************************************
	Function :	getMenu
	Purpose	: 	To get the desired menu.
	************************************************ */

typMenuItem *getMenu(typMenuItem *menu, int key)
{
	typMenuItem *oldMenu;
	oldMenu = menu;

	while (_TRUE) {
		switch (key) {
			case _UARROW_KEY:
			case _LARROW_KEY:
				menu = menu->pre;
				break;
			case _DARROW_KEY:
			case _RARROW_KEY:
				menu = menu->next;
				break;
		}
		if(menu == oldMenu) return(oldMenu);
		if(menu->caption && !menu->isdisable) return(menu);
	}
}

/* ************************************************
	Function :	razeMenuSys
	Purpose	: 	To destroy the entire menu system.
	************************************************ */

int razeMenuSys(void)
{
	razeMenu(padMain);
	razeMenu(popFile);
	razeMenu(popEdit);
	razeMenu(popSearch);
	razeMenu(popTask);

	razeMenu(popTaskBeautify);

	return(0);
}
/* ************************************************
	Function :	razeMenu
	Purpose	: 	To destroy the menu popup.
	************************************************ */

int razeMenu(typMenuItem *menu)
{
	typMenuItem *tmpMenu;

	(menu->pre)->next = NULL;
	while(menu) {

		tmpMenu = menu;
		menu = tmpMenu->next;

		free(tmpMenu->caption);
		free(tmpMenu->key);
		free(tmpMenu->keyCaption);
		free(tmpMenu->mess);
		free(tmpMenu->lastdata);

		free(tmpMenu);

	}

	return(0);
}

/* ************************************************
	Function :	actDefault
	Purpose	: 	To set the default action with the
					menu items, until they got their	own.
	************************************************ */
typMenuItem *actDefault(typMenuItem *menu)
{
	char mess[50] = {"This is default : "};

	showMess("Help",strcat(mess,menu->caption));

	return(menu);
}

/* ************************************************
	Function :	actpadFile
	Purpose	: 	To raise the triger associated with
					File menu.
	************************************************ */
typMenuItem *actpadFile(typMenuItem *menu)
{
	return(showMenu(menu,popFile));
}

/* ************************************************
	Function :	actpadEdit
	Purpose	: 	To raise the triger associated with
					Edit menu.
	************************************************ */
typMenuItem *actpadEdit(typMenuItem *menu)
{
	return(showMenu(menu,popEdit));
}

/* ************************************************
	Function :	actpadSearch
	Purpose	: 	To raise the triger associated with
					Search menu.
	************************************************ */
typMenuItem *actpadSearch(typMenuItem *menu)
{

	return(showMenu(menu,popSearch));

}

/* ************************************************
	Function :	actpadTask
	Purpose	: 	To fire the triger associated with
					Task menu.
	************************************************ */
typMenuItem *actpadTask(typMenuItem *menu)
{

	return(showMenu(menu,popTask));

}

/* ************************************************
	Function :	actFileNew
	Purpose	: 	To raise the triger associated with
					New option of File menu.
	************************************************ */
typMenuItem *actFileNew(typMenuItem *menu)
{
	showMess(NULL,menu->caption);
	return(menu);
}

/* ************************************************
	Function :	actFileOpen
	Purpose	: 	To raise the triger associated with
					Open option of File menu.
	************************************************ */
typMenuItem *actFileOpen(typMenuItem *menu)
{
	cmnDailog(dailogOpen,NULL);
	return(menu);
}

/* ************************************************
	Function :	actFileSave
	Purpose	: 	To raise the triger associated with
					Save option of File menu.
	************************************************ */
typMenuItem *actFileSave(typMenuItem *menu)
{
	save(boxFile->root,NULL,boxFile->filename);
	return(menu);
}

/* ************************************************
	Function :	actFileExit
	Purpose	: 	To raise the triger associated with
					Exit option of File menu.
	************************************************ */
typMenuItem *actFileExit(typMenuItem *menu)
{
	menu = menu;	/* Just to eleminate the warning. */
	return(NULL);
}

/* ************************************************
	Function :	actTaskBeautify
	Purpose	: 	To fire the triger associated with
					Beautify menu.
	************************************************ */
typMenuItem *actTaskBeautify(typMenuItem *menu)
{
	return(showMenu(menu,popTaskBeautify));
}
