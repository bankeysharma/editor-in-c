#include "exconst.c"

int activate_exKey(typLine **, typLine **, typLine **, int **);


/* *****************************************************
	Function : activate_exKey
	Purpose	: To activate the exKey mode.
	***************************************************** */

int activate_exKey()
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
					setexMode(NULL);
					return(0);
				case _F10_KEY:
					setexMode(exMenu);
					return(0);
				case _COLO_KEY:
					setexMode(exCmd);
					return(0);
				case _i_KEY:
					setexMode(exInsert);
					return(0);
				case _a_KEY:
					setexMode(exAppend);
					return(0);
				case _u_KEY:
					setexMode(exUpdate);
					return(0);
				case _r_KEY:
					setexMode(exRead);
					return(0);
				default:
					showMess("Alert","Unrecognized key pressed.");
			}
		}
	}
}