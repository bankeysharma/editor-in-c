#include "exconst.c"

/* ************************************************
	Variables
	************************************************ */
	int maxPathLen = 2000;
	int maxdirLen = 500;
	char *absPath;
	char *directory;
	char ext[10];
	char drive[5];
	char fname[15];

	typLabel *MsgFilename;
	typLabel *MsgMDate;
	typLabel *MsgSize;
	typLabel *MsgPerm;

	typTxtbox *txtboxPath;

/* ************************************************ */

int cmnDailog(typDailog, char **);
typListViewNode *buildListView(typListViewNode *, char *);
int showDetails(void *);
int scanPath(typListView *);

/* ***************************************************
	Function : cmdDailog
	Purpose	: Used to activate the commonm dailog box.
	*************************************************** */

int cmnDailog(typDailog job, char **filename)
{
	typWindow *dailogBox;
	typListView *lstViewBox;
	typListViewNode *lstNode;

	int objId;
	bool life;
	char *lastText = NULL;
	int row, col, lastCol, res;

	int lblCount = 10;
	typLabel labels[10];

	int txtCount = 1;
	typTxtbox txtBox[1];

	char *lblCaptions[] = {
		"File Name: ",
		"Permission: ",
		"Date: ",
		"Size: ",
		"Path: ",
		"Location: ",
		".",
		".",
		".",
		"."
	};

	int cmdCount = 3;
	typCmdButton cmdButtons[3];
	char *cmdCaptions[] = {
		"&Help",
		"&Action",
		"&Close"
	};

	/* *****************************************
		IDs to identify each object individually.
		***************************************** */

	int idtxtPath = 0;			/* IDs for text boxes. */

	int idlblFilename = 0;		/* IDs for labels. */
	int idlblPermission = 1;
	int idlblMdate = 2;
	int idlblSize = 3;
	int idlblPath = 4;
	int idlblLocation = 5;
	int idmsgFilename = 6;
	int idmsgPermission = 7;
	int idmsgMdate = 8;
	int idmsgSize = 9;

	int idcmdHelp = 0;	/* IDs for Command buttons. */
	int idcmdAction = 1;
	int idcmdClose = 2;

	/* ***************************************** */

	dailogBox = (typWindow *) defineDailog(1,1,20,60,NULL);

	dailogBox->sepCount = 2;
	dailogBox->sepLine = (int *) calloc(dailogBox->sepCount,sizeof(int));
	if(!dailogBox->sepLine) quit(_MEM_ERROR);
	dailogBox->sepLine[0] = 3;
	dailogBox->sepLine[1] = dailogBox->height - 2;

	switch (job) {
		case dailogOpen:
			dailogBox->caption = " Open ";
			cmdCaptions[idcmdAction] = "&Open";
			break;
		case dailogSave:
			dailogBox->caption = " Save ";
			cmdCaptions[idcmdAction] = "&Save";
			break;
		case dailogSaveAs:
			dailogBox->caption = " Save As ";
			cmdCaptions[idcmdAction] = "&Save As";
			break;
	}

	showDailog(dailogBox,alignCenter);

	row = dailogBox->scaleTop;
	col = dailogBox->scaleLeft;
	lastCol = dailogBox->scaleLeft + dailogBox->scaleWidth;

	absPath = (char *) calloc(maxPathLen,sizeof(char));
	if(!absPath) quit(_MEM_ERROR);
	directory = (char *) calloc(maxdirLen,sizeof(char));
	if(!directory) quit(_MEM_ERROR);

	/* *******************************
		Object building.
		******************************* */
	settxtBoxes(txtBox,txtCount);
	setLabels(labels,lblCaptions,lblCount);
	lstViewBox = (typListView *) defineListView(11,56);
	lstViewBox->trgMove = showDetails;
	lstViewBox->shouldShowOuter = _YES;
	setcmdButtons(cmdButtons,cmdCaptions,cmdCount);
	*absPath = getdisk() + 'A';
	absPath[1] = ':';
	absPath[2] = '\\';
	objId = getcurdir(_getdrive(),directory);
	strcat(absPath,directory);
	strcat(absPath,"\\");
	/* ******************************* */

	/* *******************************
		Object placement.
		****************************** */
	gotoxy(col,row);
	labels[idlblFilename].isHint = _TRUE;
	labels[idlblFilename].left = col;
	labels[idlblFilename].top = row;
	col += dispLabel(&labels[idlblFilename], lastCol);

	labels[idmsgFilename].isDisable = _TRUE;
	labels[idmsgFilename].left = col;
	labels[idmsgFilename].top = row;
	labels[idmsgFilename].width = dailogBox->left + dailogBox->width - col;
	col += dispLabel(&labels[idmsgFilename], lastCol);
	MsgFilename = &labels[idmsgFilename];

	col = dailogBox->scaleLeft;
	labels[idlblPermission].isHint = _TRUE;
	labels[idlblPermission].left = col;
	labels[idlblPermission].top = ++row;
	col += dispLabel(&labels[idlblPermission], lastCol);

	labels[idmsgPermission].width = 8;
	labels[idmsgPermission].isDisable = _TRUE;
	labels[idmsgPermission].left = col;
	labels[idmsgPermission].top = row;
	col += dispLabel(&labels[idmsgPermission], lastCol);
	MsgPerm = &labels[idmsgPermission];

	labels[idlblMdate].isHint = _TRUE;
	labels[idlblMdate].left = col;
	labels[idlblMdate].top = row;
	col += dispLabel(&labels[idlblMdate], lastCol);

	labels[idmsgMdate].width = 15;
	labels[idmsgMdate].isDisable = _TRUE;
	labels[idmsgMdate].left = col;
	labels[idmsgMdate].top = row;
	col += dispLabel(&labels[idmsgMdate], lastCol);
	MsgMDate = &labels[idmsgMdate];

	labels[idlblSize].isHint = _TRUE;
	labels[idlblSize].left = col;
	labels[idlblSize].top = row;
	col += dispLabel(&labels[idlblSize], lastCol);

	labels[idmsgSize].width = 10;
	labels[idmsgSize].isDisable = _TRUE;
	labels[idmsgSize].left = col;
	labels[idmsgSize].top = row;
	col += dispLabel(&labels[idmsgSize], lastCol);
	MsgSize = &labels[idmsgSize];

	col = dailogBox->scaleLeft;
	labels[idlblPath].left = col;
	labels[idlblPath].top = row+=2;
	col += dispLabel(&labels[idlblPath], lastCol);

	txtBox[idtxtPath].width = 58;
	txtBox[idtxtPath].left = col;
	txtBox[idtxtPath].top = row;
	col = placetxtBox(&txtBox[idtxtPath], lastCol);
	txtboxPath = &txtBox[idtxtPath];

	col = dailogBox->scaleLeft;
	labels[idlblLocation].width = 10;
	labels[idlblLocation].left = col;
	labels[idlblLocation].top = ++row;
	col += dispLabel(&labels[idlblLocation], lastCol);

	col = dailogBox->scaleLeft;
	lstViewBox->headNode = lstViewBox->firstNode = (typListViewNode *)
		buildListView(lstViewBox->headNode,"*.*");
	row += showListView(lstViewBox,col,++row);

	row = dailogBox->scaleTop + dailogBox->scaleHeight;
	col = dailogBox->scaleLeft;
	cmdButtons[idcmdHelp].left = col;
	cmdButtons[idcmdHelp].top = row;
	showcmdButton(&cmdButtons[idcmdHelp],stateNormal);

	col = dailogBox->scaleLeft+dailogBox->scaleWidth - cmdButtons[idcmdClose].width;
	cmdButtons[idcmdClose].left = col;
	cmdButtons[idcmdClose].top = row;
	col -= showcmdButton(&cmdButtons[idcmdClose],stateNormal);

	cmdButtons[idcmdAction].left = --col;
	cmdButtons[idcmdAction].top = row;
	showcmdButton(&cmdButtons[idcmdAction],stateNormal);

	/* ********************************
		Accessing Objects
		******************************** */

	if(txtBox[idtxtPath].maxLen) res = txtBox[idtxtPath].maxLen;
	else res = txtBox[idtxtPath].width;

	lastText = (char *) calloc(res+1,sizeof(char));
	if(!lastText) quit(_MEM_ERROR);

	objId = 0;
	life = _TRUE;
	while(life) {
		switch(objId) {
			case 0:
				gettxtBox(&txtBox[idtxtPath],&objId);
				if(strcmp(lastText,txtBox[idtxtPath].text)) {
					strcpy(lastText,txtBox[idtxtPath].text);
					scanPath(lstViewBox);
				}
				break;
			case 1:
				lstNode = (typListViewNode *) getListView(lstViewBox,&objId);
				if(lstNode && strcmp(lstNode->caption,".\\")) {
					strcpy(txtboxPath->text,lstNode->caption);
					scanPath(lstViewBox);
				}
				break;
			case 2:
				res = getcmdButtons(cmdButtons,cmdCount,&objId);
				if(res == cmdButtons[idcmdClose].id) {
					life = _FALSE;
				}
				break;
			default:
				objId = 0;
				break;
		}
	}

//	*filename = txtBox[idtxtPath].text;

	/* ********************************
		Reclaming the allocated memory
		******************************** */
	razeLabels(labels,lblCount);
	razetxtBoxes(txtBox,txtCount);
	razecmdButtons(cmdButtons,cmdCount);
	buildListView(lstViewBox->headNode,NULL);	/* To destroy the node list. */
	free(lstViewBox);
	hideDailog(dailogBox);
	dailogBox = NULL;
	free(absPath);
	free(directory);
	/* ******************************** */

	textcolor(gscrforeColor);
	textbackground(gscrbkColor);

	return(0);

}

/* ************************************************
	Function : buildListView
	Purpose	: Used to build the list for the list
					view box.
	************************************************ */

typListViewNode *buildListView(typListViewNode *headNode, char *filter)
{
	typListViewNode *tmpNode, *lastNode;
	struct ffblk *item;
	bool life;
	struct ffblk itmFile;
	char *tmpPath;

	/* *************************************
		Reclaiming memory allocated to
		previous list.
		************************************* */
	while (headNode) {
		tmpNode = headNode;
		headNode = tmpNode->next;

		free(tmpNode->item);
			tmpNode->item = NULL;
		free(tmpNode->caption);
			tmpNode->caption = NULL;
		free(tmpNode);
	}
	headNode = tmpNode = NULL;
	/* ************************************* */

	if(!filter) return(NULL);
	else if(!*filter) strcpy(filter,"*.*");

	tmpPath = (char *) calloc(strlen(absPath)+strlen(filter)+1,sizeof(char));
	strcpy(tmpPath,absPath);
	strcat(tmpPath,filter);

	life = (bool) !findfirst(tmpPath,&itmFile,_A_NORMAL|FA_DIREC);
	while(life) {
		item = (struct ffblk *) calloc(1,sizeof(struct find_t));
		if(!item) quit(_MEM_ERROR);
		*item = itmFile;

		tmpNode = (typListViewNode *) calloc(1, sizeof(typListViewNode));
		if(!tmpNode) quit(_MEM_ERROR);
		tmpNode->item = (struct ffblk *) item;

		tmpNode->caption = (char *) calloc(strlen(item->ff_name)+5,sizeof(char));
		if(!tmpNode->caption) quit(_MEM_ERROR);
		strcpy(tmpNode->caption,item->ff_name);
		if(item->ff_attrib >= 16 && item->ff_attrib < 32) strcat(tmpNode->caption,"\\");

		tmpNode->maxWidth = 0;

		tmpNode->backColor = glstviewnodebkColor;
		tmpNode->foreColor = glstviewnodeforeColor;

		tmpNode->trgGotFocus = NULL;
		tmpNode->trgDefault = NULL;
		tmpNode->trgCancel = NULL;

		if(!headNode) {
			headNode = lastNode = tmpNode;
		} else {
			lastNode->next = tmpNode;
			tmpNode->pre = lastNode;
			lastNode = lastNode->next;
		}
		life = (bool) !findnext(&itmFile);
	}

	free(tmpPath);
	return(headNode);

}

/* *************************************************************
	Function : showDetails
	Purpose	: Used to show the information regarding the
					selected file on detail section of dailog box.
	************************************************************** */

int showDetails(void *item)
{
	typListViewNode *node;
	struct ffblk *file;
	long int kb, mb;
	float size;
	char tmp[20];

	node = (typListViewNode *) item;
	file = (struct ffblk *) node->item;

	/* File name. */
	strncpy(MsgFilename->caption,absPath,(MsgFilename->width - strlen(node->caption) - 1));
	strcat(MsgFilename->caption,node->caption);
	dispLabel(MsgFilename,MsgFilename->left+MsgFilename->width);

	/* Permissions. */
	if(file->ff_attrib >= 16 && file->ff_attrib <32) MsgPerm->caption[0] = 'd';
	else MsgPerm->caption[0] = '-';

	if(!access(MsgFilename->caption,04)) MsgPerm->caption[1] = 'r';
	else MsgPerm->caption[1] = '-';

	if(!access(MsgFilename->caption,02)) MsgPerm->caption[2] = 'w';
	else MsgPerm->caption[2] = '-';

	if(!access(MsgFilename->caption,01)) MsgPerm->caption[3] = 'x';
	else MsgPerm->caption[3] = '-';
	MsgPerm->caption[4] = '\0';

	dispLabel(MsgPerm,MsgPerm->left+MsgPerm->width);

	/* Size */
	kb = 1024;
	mb = kb * 1024;

	if(file->ff_fsize >= mb) {
		size = file->ff_fsize / mb;
		sprintf(MsgSize->caption,"%5.1f MB",(float) size);
	}	else if(file->ff_fsize >= kb) {
			size = file->ff_fsize / kb;
		sprintf(MsgSize->caption,"%5.1f KB",(float) size);
	}	else 	sprintf(MsgSize->caption,"%ld byte",file->ff_fsize);

	sprintf(tmp,"%d byte",file->ff_attrib);

	strncpy(MsgSize->caption,tmp,MsgSize->width-1);
	dispLabel(MsgSize,MsgSize->left+MsgSize->width);

	/* Last Modification date */
	to_sdate(MsgMDate->caption,file->ff_fdate);
	dispLabel(MsgMDate,MsgMDate->left+MsgMDate->width);

	return(0);
}

/* *************************************************************
	Function : scanPath
	Purpose	: Used to scane & arrange the path and its relative
					variables.
	************************************************************** */

int scanPath(typListView *lstViewBox)
{
		if(*(txtboxPath->text+1) == ':')
			strcpy(absPath,txtboxPath->text);

		fnsplit(txtboxPath->text,drive,directory,fname,ext);
		strcat(fname,ext);
		strcpy(txtboxPath->text,fname);

		if(directory)	strcat(absPath,directory);

		lstViewBox->headNode = lstViewBox->firstNode = (typListViewNode *)
			buildListView(lstViewBox->headNode,txtboxPath->text);
		showListView(lstViewBox,NULL,NULL);
		placetxtBox(txtboxPath,txtboxPath->left+txtboxPath->width);

		return(0);
}