#include "exconst.c"

int save(typLine *, typLine *, char *);


/* *****************************************************
	Function 	: Save
	Purpose		: To save the data into given file.
	Parameters	:
		base		: Start saving from this line.
		last		: Last line upto which wish to save.
		filename	: Name of the file under which you wish
						to save these files.
	***************************************************** */

int save(typLine *base, typLine *last, char *filename)
{
	FILE *dest;
	char *mess;
	int lineCount;
	bool life;

	if(openFile(&dest,filename, opnTruncate)) return(_CAN_NOT_OPEN);

	if(!base) base = boxFile->root;
	if(!last) last = boxFile->end;

	sprintf(mess,"Saving [ %s ]...",filename);
	showMess("Info",mess);

	/* Writing list into given file */
	lineCount = 0;
	life = _TRUE;
	while (life && base) {

		if(base == last) life = _FALSE;

		++lineCount;
		fprintf(dest,"%s",base->line);
		base = base->next;

		if(base) putc('\n',dest);

	}

	sprintf(mess,"File \"%s\" saved successfully. Lines : %d",filename,lineCount);
	showMess("Info",mess);
	fclose(dest);

	return(0);

}
