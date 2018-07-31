#include "exconst.c"

int traversal(int, bool, bool, bool);

/* ************************************************
	Function : traversFile
	Purpose	: To perform traversal in the file.
	************************************************ */

int traversal( int actKey,
					bool isCtrl, bool isShift, bool isAlt)
{
	int len;

	bool willShow, willgetCurrLine, willMaxcursY;
	bool hasExecuted;

	willShow = willgetCurrLine = willMaxcursY = _FALSE;
	hasExecuted = _FALSE;

	showMess(NULL,NULL);	/* To make the help-line empty. */

	if(isCtrl) {
		switch (actKey) {
			case _CTRL_END_KEY:
				hasExecuted = _TRUE;
				boxFile->first = boxFile->end;
				actKey = _PGU_KEY;
				willMaxcursY = _TRUE;
				break;
			case _CTRL_HOM_KEY:
				hasExecuted = _TRUE;
				boxFile->first = boxFile->root;
				actKey = _PGU_KEY;
				willShow = _TRUE;
				willgetCurrLine = _TRUE;
				break;
			case _CTRL_PGD_KEY:
				hasExecuted = _TRUE;
				boxFile->last  = boxFile->curr;
				actKey = _PGD_KEY;
				actWin->cursy = actWin->scaleTop;
				break;
			case _CTRL_PGU_KEY:
				hasExecuted = _TRUE;
				boxFile->first = boxFile->curr;
				actKey = _PGU_KEY;
				actWin->cursy = actWin->scaleTop + actWin->scaleHeight;
				break;
			case _CTRL_T_KEY:
				hasExecuted = _TRUE;
				actWin->cursy = actWin->scaleTop;
				willgetCurrLine = _TRUE;
				break;
			case _CTRL_D_KEY:
				hasExecuted = _TRUE;
				actWin->cursy = actWin->scaleTop + actWin->scaleHeight;
				willgetCurrLine = _TRUE;
				break;
			case _CTRL_R_KEY:
				hasExecuted = _TRUE;
				actWin->cursx = actWin->scaleLeft;
				break;
			case _CTRL_L_KEY:
				hasExecuted = _TRUE;
				actWin->cursx = actWin->scaleLeft + actWin->scaleWidth;
				break;
		}
	}	else if(isAlt) {
			int loc, oldx;
			switch (actKey) {
				case _ALT_N_KEY:
					hasExecuted = _TRUE;
					loc = actWin->cursx;
					if(!(loc % gTablen))
						loc = (gTablen * (loc/gTablen));
					else
						loc = (gTablen * (loc/gTablen))+gTablen;
					while((loc - boxFile->offset + actWin->scaleLeft) >= actWin->cursx)
						++(actWin->cursx);
					--(actWin->cursx);
					break;
			}
	}	else if(isShift);

		/* **********************************
			Key job.
			********************************** */

		switch (actKey) {
			case _F1_KEY:
				hasExecuted = _TRUE;
				boxFile->curr = boxFile->first;
				boxFile->curr =
					(typLine *) getcurrLine(boxFile->first,boxFile->end,&actWin->cursy);
				break;
			case _SPC_KEY:
				hasExecuted = _TRUE;
				showMess(NULL,(boxFile->curr)->line);
				break;
			case _F3_KEY:
				hasExecuted = _TRUE;
				showMess(NULL,boxFile->last->line);
				break;
			case _RARROW_KEY:
				hasExecuted = _TRUE;
				if(actWin->cursx < (actWin->scaleLeft+actWin->scaleWidth))
					++(actWin->cursx);
				else {
					++(boxFile->offset);
					willShow = _TRUE;
				}
				break;
			case _LARROW_KEY:
				hasExecuted = _TRUE;
				if(actWin->cursx > actWin->scaleLeft) --(actWin->cursx);
				else if(boxFile->offset) {
					--(boxFile->offset);
					willShow = _TRUE;
				}
				break;
			case _DARROW_KEY:
				hasExecuted = _TRUE;
				if(boxFile->curr == boxFile->end) break;
				if(actWin->cursy < (actWin->scaleTop+actWin->scaleHeight))
					++(actWin->cursy);
				else if((boxFile->last)->next) {
					boxFile->first = (boxFile->first)->next;
					boxFile->last = (boxFile->last)->next;
					willShow = _TRUE;
				}
				boxFile->curr = (boxFile->curr)->next;
				break;
			case _UARROW_KEY:
				hasExecuted = _TRUE;
				if(!(boxFile->curr)->pre)	break;
				if((actWin->cursy > actWin->scaleTop)) --(actWin->cursy);
				else if((boxFile->first)->pre) {
					boxFile->first = (boxFile->first)->pre;
					boxFile->last = (boxFile->last)->pre;
					willShow = _TRUE;
				}
				boxFile->curr = (boxFile->curr)->pre;
				break;
			case _HOM_KEY:
				hasExecuted = _TRUE;
				if(boxFile->offset) {
					boxFile->offset = 0;
					willShow = _TRUE;
				}
				actWin->cursx = actWin->scaleLeft;
				break;
			case _END_KEY:
				hasExecuted = _TRUE;
				if(!(len = length((boxFile->curr)->line))) {
					if(boxFile->offset) {
						boxFile->offset = 0;
						willShow = _TRUE;
					}
					actWin->cursx = actWin->scaleLeft;
					break;
				}
				boxFile->offset = actWin->scaleWidth * (len / actWin->scaleWidth);
				if (!(len % actWin->scaleWidth))
					boxFile->offset = boxFile->offset - actWin->scaleWidth;
				actWin->cursx = len - boxFile->offset + actWin->scaleLeft;
				willShow = _TRUE;
				break;
			case _PGU_KEY:
				hasExecuted = _TRUE;
				if(boxFile->first == boxFile->root) {
					actWin->cursy = actWin->scaleTop;
					break;
				}
				boxFile->first = (typLine *)
					getLine(boxFile->first,actWin->scaleHeight,_BACK);
				willShow = _TRUE;
				willgetCurrLine = _TRUE;
				break;
			case _PGD_KEY:
				hasExecuted = _TRUE;
				if(boxFile->last == boxFile->end)	{
					willMaxcursY = _TRUE;
					break;
				}
				boxFile->first = boxFile->last;
				willShow = _TRUE;
				willgetCurrLine = _TRUE;
				break;
		}

		/* ******************************
			Key dependent job.
			****************************** */

		if(willShow) {
			switch (actKey) {
				case _PGU_KEY:
				case _PGD_KEY:
				case _HOM_KEY:
				case _END_KEY:
				case _LARROW_KEY:
				case _RARROW_KEY:
					boxFile->last = (typLine *) showFile(boxFile->first);
					break;
				case _DARROW_KEY:
					gotoxy(actWin->scaleLeft,actWin->scaleTop);
					delline();
					gotoxy(actWin->scaleLeft,actWin->scaleTop+actWin->scaleHeight);
					insline();
					placeLine((boxFile->last)->line,actWin->scaleLeft,(actWin->scaleTop+actWin->scaleHeight));
					break;
				case _UARROW_KEY:
					gotoxy(actWin->scaleLeft,actWin->scaleTop+actWin->scaleHeight);
					delline();
					gotoxy(actWin->scaleLeft,actWin->scaleTop);
					insline();
					placeLine((boxFile->first)->line,actWin->scaleLeft,actWin->scaleTop);
					break;
			}
		}

		if(willMaxcursY)	actWin->cursy = actWin->scaleTop+actWin->scaleHeight;

		if(willgetCurrLine || willMaxcursY)
				(boxFile->curr) =
					(typLine *) getcurrLine(boxFile->first,boxFile->end, &actWin->cursy);

	return(hasExecuted);
}
