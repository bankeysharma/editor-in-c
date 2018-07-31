#include "exconst.c"

typWindow *defineDailog(int, int, int, int, char *);
int alignDailog(typWindow *, typAlign);

int showDailog(typWindow *, typAlign);
int hideDailog(typWindow *);
int fillDailog(typWindow *, typSymbols);

int settxtBoxex(typTxtbox *, int);
int placetxtBox(typTxtbox *, int);
int gettxtBox(typTxtbox *, int *);
int razetxtBoxes(typTxtbox *,int);

int setLabels(typLabel *, char **, int);
int dispLabel(typLabel *, int);

typListView *defineListView(int, int);
int showListView(typListView *, int , int);
typListViewNode *getListView(typListView *,int *);
int getlstNode(typListViewNode **, int, int);

int setcmdButtons(typCmdButton *,char **, int);
int showcmdButton(typCmdButton *, typState);
int getcmdButtons(typCmdButton *, int, int *);
int razecmdButtons(typCmdButton *,int);

/* ************************************************
	Function : defineDailog
	Purpose	: Used to define the dailog box.
	************************************************ */

typWindow *defineDailog(int left, int top, int height, int width, char *caption)
{
	static int id;
	typWindow *newBox;

	/* ***********************
		Default cordinates.
		*********************** */
	if(!left) left = gLeft;
	if(!top) top = gTop;
	if(!height) height = gMaxRows - gTop - gBottom;
	if(!width) width = gMaxCols - gLeft - gRight;
	/* *********************** */

	if(width < 20) width = 20;		/* Minimum width for any dailog box. */
	if(height < 5) height = 5;    /* Minimum height for any dailog box. */

	newBox = (typWindow *) calloc(1,sizeof(typWindow));
	if(!newBox) quit(_MEM_ERROR);

	/* *****************************
		Assigning common properties
		***************************** */
	newBox->id = ++id;

	if(caption) {
		newBox->caption = (char *) calloc(strlen(caption)+1,sizeof(char));
		if(!newBox->caption) quit(_MEM_ERROR);
		strcpy(newBox->caption,caption);
	} else newBox->caption = NULL;

	newBox->capAlign = alignRight;

	newBox->left = left;
	newBox->top = top;
	newBox->width = width;
	newBox->height = height;

	newBox->lenNotice = newBox->width - 2;

	newBox->lastdata = NULL;

	newBox->hasVertiScrl = _FALSE;
	newBox->hasVertiScrl = _FALSE;

	/* *********************** */

	return(newBox);

}

/* ************************************************
	Function : alignDailog
	Purpose	: Used to align the dailog box.
	************************************************ */

int alignDailog(typWindow *dailog, typAlign align)
{

	if(!dailog) return(1); /* Failure return. */

/*	if(!dailog->left) dailog->left = gLeft;
	if(!dailog->top) dailog->top = gTop;
	if(!dailog->height) dailog->height = gMaxRows - gTop - gBottom;
	if(!dailog->width) dailog->width = gMaxCols - gLeft - gRight;

	if(dailog->width < 20) dailog->width = 20;
	if(dailog->height < 5) dailog->height = 5;
*/
	switch (align) {
		case alignLeft:
			dailog->left = gLeft;
			break;
		case alignRight:
			dailog->left = gMaxCols - dailog->width;
			break;
		case alignTop:
			dailog->top = gTop;
			break;
		case alignBottom:
			dailog->top = gMaxRows - dailog->height;
			break;
		case alignLeftTop:
			dailog->left = gLeft;
			dailog->top = gTop;
			break;
		case alignRightTop:
			dailog->left = gMaxCols - dailog->width;
			dailog->top = gTop;
			break;
		case alignLeftBottom:
			dailog->left = gLeft;
			dailog->top = gMaxRows - dailog->height;
			break;
		case alignRightBottom:
			dailog->left = gMaxCols - dailog->width;
			dailog->top = gMaxRows - dailog->height;
			break;
		case alignCenter:
			dailog->left = (gMaxCols / 2) - (dailog->width / 2);
			dailog->top = (gMaxRows / 2) - (dailog->height / 2);

			if(dailog->height < gMaxRows - 1) ++dailog->top;

			break;
		default:
			return(0);
	}

	/* **********************************
		Reseting other cordinates.
		********************************** */

	dailog->scaleLeft = dailog->left + 2;
	dailog->scaleTop = dailog->top + 1;
	dailog->scaleWidth = dailog->width - (dailog->scaleLeft - dailog->left) - 1;
	dailog->scaleHeight = dailog->height - (dailog->scaleTop - dailog->top) - 1;

	dailog->cursx = dailog->scaleLeft;
	dailog->cursy = dailog->scaleTop;
	/* ********************************** */

	return(0);

}

/* ************************************************
	Function : showDailog
	Purpose	: Used to display the dailog box.
	************************************************ */

int showDailog(typWindow *dailogBox, typAlign align)
{
	char buf[4096];
	int len;

	alignDailog(dailogBox,align);

	gettext(dailogBox->left,dailogBox->top,(dailogBox->left+dailogBox->width),
				(dailogBox->top+dailogBox->height),buf);

	len = strlen(buf);
	dailogBox->lastdata = (char *) calloc(++len, sizeof(char));
//	dailogBox->lastdata = (char *) calloc((dailogBox->height * dailogBox->width * 2), sizeof(char));
	if(!dailogBox->lastdata) quit(_MEM_ERROR);
	strcpy(dailogBox->lastdata,buf);

	drawWin(dailogBox,prnAll);	/* Draws the outline for the dailog box. */

	fillDailog(dailogBox,symbSpace); /* Fills the governed space with the given
												space except the seprator line area. */

	gotoxy(dailogBox->scaleLeft,dailogBox->scaleTop);

	return(0);

}

/* ************************************************
	Function : hideDailog
	Purpose	: Used to hide the dailog box.
	************************************************ */

int hideDailog(typWindow *dailog)
{

	puttext(dailog->left,dailog->top,(dailog->left+dailog->width),
				(dailog->top+dailog->height),dailog->lastdata);

	free(dailog->lastdata);
		dailog->lastdata = NULL;
	free(dailog->sepLine);
		dailog->sepLine = NULL;
	free(dailog->caption);
		dailog->caption = NULL;
	free(dailog);

	return(0);
}

/* ************************************************
	Function : fillDailog
	Purpose	: Used to fill the dailog with given
					chracter except the seprator lines.
	************************************************ */

int fillDailog(typWindow *dailog, typSymbols fillChar)
{
	int x,y, maxy, maxx, intx;
	int id,count;

	maxy = dailog->top+dailog->height;
	maxx = dailog->left+dailog->width;
	intx = dailog->left + 1;

	id = 0;
	count=dailog->sepCount;

	for(y=dailog->top+1;y<maxy; y++) {

		if(count && y == dailog->top + dailog->sepLine[id]) {
			--count;
			++id;
			continue;
		}

		gotoxy(intx,y);
		for(x=intx; x < maxx; x++)
			cprintf("%c",fillChar);
	}
	return(0);
}

/* ************************************************
	Function : settxtBoxes
	Purpose	: Used to set the attributes of the
					text box.
	************************************************ */

int settxtBoxes(typTxtbox *txtBox,int count)
{

	while(count--) {

		txtBox[count].text = NULL;
		txtBox[count].txtLoc = NULL;

		txtBox[count].offset = 0;

		txtBox[count].left = NULL;
		txtBox[count].top = NULL;

		txtBox[count].backColor = gtxtbkColor;
		txtBox[count].foreColor = gtxtforeColor;
		txtBox[count].disableColor = gtxtdisableColor;
		txtBox[count].maxLen = 0;

		txtBox[count].isMultiline = _FALSE;
		txtBox[count].lines = 0;

		txtBox[count].mess = NULL;

		txtBox[count].trgChange = NULL;
		txtBox[count].trgValidate = NULL;
		txtBox[count].trgActivate = NULL;
		txtBox[count].trgDefault = NULL;
		txtBox[count].trgCancel = NULL;

		txtBox[count].isLocked = _FALSE;
		txtBox[count].isDisable = _FALSE;
	}

	return(0);
}

/* ************************************************
	Function : placetxtBox
	Purpose	: Used to place the text box in the
					dailog box.
	************************************************ */

int placetxtBox(typTxtbox *txtBox, int lastCol)
{
	int i;
	int maxLen;

	if(!txtBox->left) txtBox->left = wherex();
	if(!txtBox->top) txtBox->top = wherey();

	txtBox->cursx = txtBox->left;
	txtBox->cursy = txtBox->top;

	textbackground(txtBox->backColor);

	if(txtBox->isDisable) textcolor(gtxtdisableColor);
	else textcolor(txtBox->foreColor);

	if(!txtBox->text) {
		maxLen = txtBox->maxLen;
		if(!maxLen) maxLen = txtBox->width;

		txtBox->text = (char *) calloc(maxLen+1,sizeof(char));
		if(!txtBox->text) quit(_MEM_ERROR);
	}

	txtBox->txtLoc = txtBox->text;
	gotoxy(txtBox->left,txtBox->top);

	for(i=0; i < txtBox->width; i++) {
		if(i + txtBox->left >= lastCol) {
			txtBox->width = i;
			break;
		}
		if(*txtBox->txtLoc) {
			cprintf("%c",*txtBox->txtLoc);
			txtBox->txtLoc++;
			txtBox->cursx++;
		}
		else	cprintf("%c",symbSpace);
	}

	return(txtBox->left+txtBox->width);

}

/* ************************************************
	Function : gettxtBox
	Purpose	: Used to place the text box in the
					dailog box.
	************************************************ */

int gettxtBox(typTxtbox *txtBox, int *objId)
{
	char *text;
	bool life;

	if(txtBox->isDisable) {
		++*objId;
		return(0);
	}

	gotoxy(txtBox->cursx,txtBox->cursy);

	textbackground(txtBox->backColor);
	textcolor(txtBox->foreColor);

	if(!txtBox->txtLoc) txtBox->txtLoc = txtBox->text;
	text = txtBox->txtLoc;

	life = _TRUE;
	while(life) {
		*text = getKey();
		switch(*text) {
			case _SHIFT_TAB_KEY:
				--*objId;
				life = _FALSE;
				break;
			case '\n':
			case '\t':
				++*objId;
				life = _FALSE;
				*text = '\0';
				break;
			case '\b':
				if((txtBox->cursx > txtBox->left)) {
					cprintf("%c %c",'\b','\b');
					--text;
					--txtBox->cursx;
				}
				break;
			default:
				if((*text == ' ') && (text == txtBox->text)) break; /* Can't have leading spaces. */
				cprintf("%c",*text);
				++text;
				++txtBox->cursx;
		}

		if(txtBox->cursx - txtBox->left >= txtBox->width - 1) {
			--text;
			--txtBox->cursx;
			gotoxy(txtBox->cursx,txtBox->cursy);
		}
	}
	txtBox->txtLoc = text;
	return(0);
}

/* ************************************************
	Function : razetxtBoxes
	Purpose	: Used to free the memory allocated to
					text boxes.
	************************************************ */

int razetxtBoxes(typTxtbox *txtBox,int count)
{

	if(!count) return(1); /* Failure return. */

	while(count--) {
		free(txtBox[count].text);
			txtBox[count].text = NULL;
		free(txtBox[count].mess);
			txtBox[count].mess = NULL;
	}

	return(0);

}

/* ************************************************
	Function : setcmdButtons
	Purpose	: Used to set the attributes of the
					command buttons.
	************************************************ */

int setcmdButtons(typCmdButton *cmdButtons,char **lstCaption, int count)
{
	static int id;
	int i, len;

	i = len = 0;
	while(i < count) {

		cmdButtons[i].id = ++id;

		if(lstCaption[i]) {
			len=strlen(lstCaption[i]);
			cmdButtons[i].caption = (char *) calloc(len,sizeof(char));
			if(!cmdButtons[i].caption) quit(_MEM_ERROR);

			strcpy(cmdButtons[i].caption,lstCaption[i]);
		} else cmdButtons[i].caption = NULL;

		cmdButtons[i].width = len + 2;
		cmdButtons[i].height = 1;

		cmdButtons[i].foreColor = gcmdforeColor;
		cmdButtons[i].backColor = gcmdbkColor;

		cmdButtons[i].mess = NULL;

		cmdButtons[i].triger = NULL;

		++i;
	}
	return(0);
}

/* ************************************************
	Function : showcmdButton
	Purpose	: Used to dispaly command button at
					given cordinates.
	************************************************ */

int showcmdButton(typCmdButton *cmdButton, typState state)
{
	char *caption;
	bool hasHotkey;

	if(!cmdButton->left) cmdButton->left = wherex();
	if(!cmdButton->top) cmdButton->top = wherey();

	textcolor(cmdButton->foreColor);
	switch(state) {
		case stateNormal:
			textbackground(cmdButton->backColor);
			break;
		case stateFocus:
			textbackground(gcmdfocusColor);
			break;
	}

	gotoxy(cmdButton->left,cmdButton->top);

	caption = cmdButton->caption;
	hasHotkey = _FALSE;

	if(state == stateNormal || state == stateFocus) {
		cprintf("%c",symbDblLT);
		for(;	*caption ; ) {
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
			} else cprintf("%c",*caption++);
		}
		cprintf("%c",symbDblGT);
	}

	return(cmdButton->width);

}

/* ************************************************
	Function : getcmdButtons
	Purpose	: Used to activate the command buttons.
	Returns	: The corresponding ID if selected
					else NULL.
	************************************************ */

int getcmdButtons(typCmdButton *cmdButtons, int count, int *objId)
{
	int i;
	bool life;
	int key;

	i = 0;
	--count;

	life= _TRUE;
	_setcursortype(_NOCURSOR);
	while(life) {
		showcmdButton(&cmdButtons[i],stateFocus);
		switch((key=getKey())) {
			case _LARROW_KEY:
				showcmdButton(&cmdButtons[i],stateNormal);
				if(i==0) {
					--*objId;
					life = _FALSE;
				} else --i;
				break;
			case _RARROW_KEY:
				showcmdButton(&cmdButtons[i],stateNormal);
				if(i == count) {
					++*objId;
					life = _FALSE;
				} else ++i;
				break;
			case _TAB_KEY:
				showcmdButton(&cmdButtons[i],stateNormal);
				++*objId;
				life = _FALSE;
				break;
			case _SHIFT_TAB_KEY:
				showcmdButton(&cmdButtons[i],stateNormal);
				--*objId;
				life = _FALSE;
				break;
			case _ENT_KEY:
				showcmdButton(&cmdButtons[i],stateNormal);
				++*objId;
				life = _FALSE;
				break;
		}
	}
	_setcursortype(_NORMALCURSOR);

	if(key == _ENT_KEY) return(cmdButtons[i].id);
	return(NULL);

}

/* ************************************************
	Function : razecmdButtons
	Purpose	: Used to destroy the command buttons.
	************************************************ */

int razecmdButtons(typCmdButton *cmdButtons,int count)
{

	if(!count) return(1);

	while(count--) {
		free(cmdButtons[count].caption);
			cmdButtons[count].caption = NULL;
		free(cmdButtons[count].mess);
			cmdButtons[count].mess = NULL;
	}

	return(0);

}

/* ************************************************
	Function : setLabels
	Purpose	: Used to set the attributes of the
					labels.
	************************************************ */

int setLabels(typLabel *lblList, char **lstCaption, int count)
{
	int i;
	i=0;
	while(i<count) {

		if(lstCaption[i]) {
			lblList[i].width = strlen(lstCaption[i]);
			lblList[i].caption = (char *) calloc(lblList[i].width + 1,sizeof(char));
			if(!lblList[i].caption) quit(_MEM_ERROR);

			strcpy(lblList[i].caption,lstCaption[i]);
		}	else {
			lblList[i].caption = (char *) calloc(lblList[i].width + 1,sizeof(char));
			if(!lblList[i].caption) quit(_MEM_ERROR);
		}

		lblList[i].backColor = glblbkColor;
		lblList[i].foreColor = glblforeColor;
		lblList[i].hintColor = glblhintColor;
		lblList[i].disableColor = glbldisableColor;

		lblList[i].wordwrap = _FALSE;
		lblList[i].isDisable = _FALSE;
		lblList[i].isHint = _FALSE;

		i++;

	}
	return(0);
}

/* **************************************************
	Function : razeLabels
	Purpose	: Used to destroy the labels and reclaim
					the allocated memory .
	************************************************** */

int razeLabels(typLabel *lblList, int count)
{
	if(!count) return(1);

	while(count--)	{
		free(lblList[count].caption);
			lblList[count].caption = NULL;
	}

	return(0);
}

/* ************************************************
	Function : dispLabels
	Purpose	: Used to display the labels.
	************************************************ */

int dispLabel(typLabel *label, int lastCol)
{
	char *caption;
	int x;

	if(!label) return(NULL);

	x = label->left;
	gotoxy(label->left,label->top);

	caption = label->caption;
	if(!caption) return(label->width);

	textbackground(label->backColor);

	if(label->isDisable) textcolor(label->disableColor);
	else if(label->isHint) textcolor(label->hintColor);
	else textcolor(label->foreColor);

	while(*caption) {
		cprintf("%c",*caption++);
		x++;
		if(x >= lastCol) {
			label->width = x - label->left;
			break;
		}
	}

	while(x++ < label->left+label->width)	{
		cprintf("%c",symbSpace); /* clearing rest line. */
		if(x >= lastCol) {
			label->width = x - label->left;
			break;
		}
	}

	return(label->width);

}

/* ************************************************
	Function : defineListView
	Purpose	: Used to define the list view box.
	************************************************ */

typListView *defineListView(int height, int width)
{
	typListView *item;

	item = (typListView *) calloc(1,sizeof(typListView));
	if(!item) quit(_MEM_ERROR);

	if(height < 5) height = 5;
	if(width < 20) width = 20;

	item->height = height;
	item->width = width;

	item->scaleHeight = height;
	item->scaleWidth = width;

	item->offset = 0;
	item->secLen = item->scaleHeight;

	item->foreColor = glstviewforeColor;
	item->backColor = glstviewbkColor;

	item->headNode = NULL;
	item->tailNode = NULL;
	item->firstNode = NULL;
	item->lastNode = NULL;
	item->currNode = NULL;

	item->hasHorizScroll = _FALSE;
	item->shouldShowOuter = _NO;

	item->trgGotFocus = NULL;
	item->trgMove = NULL;
	item->trgValidate = NULL;
	item->trgDefault = NULL;
	item->trgCancel = NULL;

	return(item);
}

/* ************************************************
	Function : showListView
	Purpose	: Used to show the list view box.
	************************************************ */

int showListView(typListView *lstViewBox, int x, int y)
{
	int secWidth, tmpLen, secLen, maxCol;
	typListViewNode *currNode, *tmpNode;

	if(x)	lstViewBox->left = x;
	if(y) lstViewBox->top = y;

	textcolor(lstViewBox->foreColor);
	textbackground(lstViewBox->backColor);

	if(lstViewBox->shouldShowOuter) {
		lstViewBox->scaleLeft = lstViewBox->left + 1;
		lstViewBox->scaleTop = lstViewBox->top + 1;
		lstViewBox->scaleHeight = lstViewBox->height - 2;
		lstViewBox->scaleWidth = lstViewBox->width - 2;
		lstViewBox->secLen = lstViewBox->scaleHeight;

		drawBox(lstViewBox->left, lstViewBox->top,
					lstViewBox->width, lstViewBox->height, styleSingle);
	} else {
		lstViewBox->scaleLeft = lstViewBox->left;
		lstViewBox->scaleTop = lstViewBox->top;
		lstViewBox->scaleHeight = lstViewBox->height;
		lstViewBox->scaleWidth = lstViewBox->width;
		lstViewBox->secLen = lstViewBox->height;
	}

	fillBox(lstViewBox->scaleLeft, lstViewBox->scaleTop,
				(lstViewBox->scaleLeft+lstViewBox->scaleWidth),
				(lstViewBox->scaleTop+lstViewBox->scaleHeight),symbSpace);

	x = lstViewBox->scaleLeft;
	y = lstViewBox->scaleTop;
	secLen = lstViewBox->scaleTop+lstViewBox->secLen;
	maxCol = lstViewBox->scaleLeft + lstViewBox->scaleWidth;
	secWidth = 0;

	currNode = lstViewBox->currNode = lstViewBox->firstNode;
	while(currNode) {
		if(y > secLen) {
			y = lstViewBox->scaleTop;
			tmpNode = currNode;
			tmpLen = getlstNode(&tmpNode,secLen,_NEXT);
			x += secWidth += 2;
			secWidth = 0;
			if(x + tmpLen >= maxCol) {
				lstViewBox->lastNode = currNode->pre;
				break;
			}
		}

		tmpLen = strlen(currNode->caption);
		if(tmpLen > secWidth) secWidth = tmpLen;

		currNode->left = x;
		currNode->top = y++;

		gotoxy(currNode->left,currNode->top);
		cprintf("%s",currNode->caption);

		lstViewBox->lastNode = currNode;
		currNode = currNode->next;
	}

	if(!lstViewBox->headNode) {
		textcolor(DARKGRAY);
		gotoxy(lstViewBox->scaleLeft,lstViewBox->scaleTop);
		cprintf("%s","No list item found.");
	}

	return(0);

}

/* ************************************************
	Function : getListView
	Purpose	: Used to get the values from list
					view box.
	************************************************ */

typListViewNode *getListView(typListView *lstViewBox, int *objId)
{
	bool life, isChanged;
	int key;

	typListViewNode *currNode;

	if(!lstViewBox->headNode) {
		++*objId;
		return(NULL);
	}

	textcolor(lstViewBox->foreColor);
	textbackground(lstViewBox->backColor);

	currNode = lstViewBox->currNode;
	life = _TRUE;
	_setcursortype(_NOCURSOR);
	while(life) {
		if(currNode->pre && currNode->next)
			if(currNode == lstViewBox->lastNode) {
				getlstNode(&lstViewBox->firstNode,lstViewBox->secLen,_NEXT);
				showListView(lstViewBox,_DEFAULT,_DEFAULT);
			} else if(currNode == lstViewBox->firstNode) {
				getlstNode(&lstViewBox->firstNode,lstViewBox->secLen,_BACK);
				showListView(lstViewBox,_DEFAULT,_DEFAULT);
			}
		if(isChanged) {
			if(lstViewBox->trgMove)
				lstViewBox->trgMove((typListViewNode *) currNode);
			textcolor(lstViewBox->foreColor);
			textbackground(glstviewselColor);
			gotoxy(currNode->left,currNode->top);
			cprintf("%s",currNode->caption);
			textbackground(lstViewBox->backColor);
		}
		isChanged = _TRUE;

		switch((key=getKey())) {
			case _ENT_KEY:
				life = _FALSE;
				break;
			case _DARROW_KEY:
				if(currNode->next && currNode != lstViewBox->lastNode) {
					gotoxy(currNode->left,currNode->top);
					cprintf("%s",currNode->caption);
					currNode = currNode->next;
				}
				break;
			case _UARROW_KEY:
				if(currNode->pre) {
					gotoxy(currNode->left,currNode->top);
					cprintf("%s",currNode->caption);
					currNode = currNode->pre;
				}
				break;
			case _SHIFT_TAB_KEY:	/* Shift + Tab */
				--*objId;
				life = _FALSE;
				break;
			case _TAB_KEY:	/* Tab */
				++*objId;
				life = _FALSE;
				break;
			default:
				isChanged = _FALSE;
				break;
		}
	}
	_setcursortype(_NORMALCURSOR);
	gotoxy(currNode->left,currNode->top);
	cprintf("%s",currNode->caption);
	if(key == _ENT_KEY)	return((lstViewBox->currNode = currNode));
	return(NULL);

}

/* ************************************************
	Function : getlstNode
	Purpose	: Used to get a node situate n node
					next or forth.
	Returns	: Section width.
	************************************************ */

int getlstNode(typListViewNode **currNode, int n, int act)
{
	int maxWidth, len;
	typListViewNode *tmpNode;

	tmpNode = *currNode;

	if(!tmpNode) return(0);

	maxWidth = 0;
	for(;n>=0;n--) {
		if(maxWidth < (len=strlen(tmpNode->caption))) maxWidth = len;

		if(!act && tmpNode->pre) tmpNode = tmpNode->pre;
		else if(act && tmpNode->next) tmpNode = tmpNode->next;
		else break;
	}

	*currNode = tmpNode;

	return(maxWidth);

}