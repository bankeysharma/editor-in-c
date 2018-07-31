#include <conio.h>

int main(void)
{
	int i;

	clrscr();

	textmode(C80);
/*	for (i=0; i<9; i++)
	{
		 textattr(i + ((i+1) << 4));
		 cprintf("This is a test\r\n");
	}
*/
	textbackground(BLUE);
//   textcolor(BLACK);
	gotoxy(5,2);
	cprintf("                     ");
	gotoxy(5,2);
	cprintf("This is a test\r\n");
	getch();

}