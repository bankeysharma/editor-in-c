#include "exconst.c"

int activate_exCmd(void);	/* To activate the exMode. */
int parseCmd(char *);		/* To parse a command into command interprator. */
int getCmd(char *);        /* To take the command-line. */
int getOpt(char **);			/* To extract the option-clause from the command line. */

/* *****************************************************
	Function : activate_exCmd
	Purpose	: To activate the exCmd mode.
	***************************************************** */

int activate_exCmd(void)
{
	int oldcursx, oldcursy;
	char cmd[80];
	int res;

	oldcursx = wherex();
	oldcursy = wherey();

	while(_TRUE) {

		if(getCmd(cmd) && strlen(cmd)) continue;
		else if(!strlen(cmd)) {
			res = 0;
			break;
		}

		res = parseCmd(cmd);

		if(res && (res != 1))	bioskey(0);
		else break;

	}

	setexMode(NULL);

/*	gotoxy(1,gMaxRows);
	clreol();
*/	gotoxy(oldcursx,oldcursy);

	return(res);
}

/* *****************************************************
	Function : getCmd
	Purpose	: To get the command from the keyboard.
	***************************************************** */

int getCmd(char *cmd)
{
	char ch;
	int cursx, cursy;
	bool life;

	cursx = 1;
	cursy = gMaxRows;

	gotoxy(cursx,cursy);
	clreol();
	cprintf(":");

	life = _TRUE;

	while(life) {

		if (cursx > gMaxCols-2) makeSound();

		*cmd = getKey();

		switch (*cmd) {
			case '\n':
			case '\t':
				life = _FALSE;
				break;
			case (char) _ESC_KEY:
				*cmd = '\0';
				return(1);
		}

		if(life) {
			if((*cmd == '\b') && (cursx >= 2)) {
				cprintf("%c %c",'\b','\b');
				--cmd;
				--cursx;
			} else if ((*cmd != '\b') && (cursx <= gMaxCols-2)) {
				cprintf("%c",*cmd);
				++cmd;
				++cursx;
			}
		}
		else *cmd = '\0';
	}
	return(0);
}

/* *****************************************************
	Function : parseCmd
	Purpose	: To parse the command into the command
					interpretor.
	***************************************************** */

int parseCmd(char *cmd)
{

	bool life;

	if(!*cmd) return(0);

	life = _TRUE;
	while (life) {

		switch (*cmd) {
			case ' ':	/* To eliminate the extra spaces */
				++cmd;
				continue;
			case 'q':		/* To quit the session */
				/* Syntax : q[!] */
				if(*(cmd+1) == '!') ++cmd;    	/* To get the clause ( ! ), if exists. */
				if(boxFile->hasChanged) {
				  if (*cmd == '!') return(1);
				  else showMess("Alert","Please! save the changes first.");
				  return(-1);
				} else  return(1);
			case 's':
				/* s <filename> */
				switch (save(boxFile->root,boxFile->end,++cmd)) {
					case _CAN_NOT_OPEN:
						showMess("Error","Invalid file path to save.");
						life = _FALSE;
						break;
				}
				life = _FALSE; /* tis should be deleted afterward. */
//				getKey();
				break;
			default:
				*cmd = '\b';	/* Just to indicate that an invalid symbol
										was encountered. */
		}

		if(*cmd == '\b') {
			showMess("Error","Invaid symbol encountered. While interpreting...");
			return(-1);
		}
		else if(*cmd) ++cmd;

		if(!*cmd) life = _FALSE;

	}

	return(0);	/* Well, this return is being placed
						just to eliminate	the warnings. */

}