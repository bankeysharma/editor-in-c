#include "exconst.c"

int operateEditor(void);

int operateJob(void);

/* ************************************************
	Function : operateEditor
	Purpose	: To operate the editor.
	************************************************ */

int operateEditor(void)
{

	bool life;
	int oldcursx, oldcursy;

	oldcursx = wherex();
	oldcursy = wherey();

	defineWindow(_DEFAULT,_DEFAULT,_DEFAULT,_DEFAULT,boxFile->filetitle);
	activateWindow(actWin,alignLast);

	gotoxy(actWin->scaleLeft,actWin->scaleTop);

	life = _TRUE;
	while (life) {
		textcolor(gscrforeColor);
		textbackground(gscrbkColor);
		showMode();
		switch (gEdMode) {
			case exRead:
			case exUpdate:
			case exAppend:
			case exCreate:
			case exInsert:
				operateJob();
				break;
			case exKey:
				activate_exKey();
				break;
			case exCmd:
				if(activate_exCmd())	life = _FALSE;
				setexMode(NULL);
				break;
			case exMenu:
				if(activateMenuSys()) life = _FALSE;
				setexMode(NULL);
				break;
		}
	}

	gotoxy(oldcursx,oldcursy);

	return(_NO_ERROR);
}

/* ************************************************
	Function : operateJob
	Purpose	: To perform determined operations.
	************************************************ */

int operateJob(void)
{

	int actKey, spclKey, len, tmp;
	int res;

	bool isCtrl, isShift, isAlt;

	while(_TRUE) {

		gotoxy(actWin->cursx,actWin->cursy);

		actKey = getKeys(&isCtrl, &isShift, &isAlt);

		res = traversal(actKey, isCtrl, isShift, isAlt);

		if(res == 1);
		else {

			if(isCtrl);
			else if(isShift);
			else if(isAlt);

			switch (actKey) {
				case _ESC_KEY:
					setexMode(exKey);
					return(0);
				case _F10_KEY:
					setexMode(exMenu);
					return(0);
				default:
					showMess("Alert","Unrecognized key pressed.");
			}

		}
	}
}