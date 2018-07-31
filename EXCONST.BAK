#include<dos.h>
#include<bios.h>
#include<math.h>
#include<stdio.h>
#include<conio.h>
#include<alloc.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

#define _newMode 2

#define _EMPTY NULL
#define _DEFAULT NULL

#define _TRUE 1
#define _FALSE 0

#define _YES 1
#define _NO 0

#define _BACK 0
#define _NEXT 1

#define _LBOUND 0

#define _ALL 0
#define _ONLY 1
#define _NONE  -1

#define _NO_ERROR 0
#define _MEM_ERROR -13
#define _CAN_NOT_OPEN 1

#define RIGHT  0x01
#define LEFT   0x02
#define CTRL   0x04
#define ALT    0x08

#define _ALT_B_KEY 12288
#define _ALT_N_KEY 12544

#define _CTRL_T_KEY 5140
#define _CTRL_D_KEY 8196
#define _CTRL_R_KEY 9740
#define _CTRL_L_KEY 4882
#define _CTRL_END_KEY 29952
#define _CTRL_HOM_KEY 30464
#define _CTRL_PGD_KEY 30208
#define _CTRL_PGU_KEY -31744
#define _CTRL_LARROW_KEY 29440
#define _CTRL_RARROW_KEY 29696

#define _INS_KEY 20992
#define _DEL_KEY 21248
#define _HOM_KEY 18176
#define _END_KEY 20224
#define _PGU_KEY 18688
#define _PGD_KEY 20736
#define _ESC_KEY 283

#define _BSP_KEY 3592

#define _SPC_KEY 14624

#define _ENT_KEY 7178

#define _TAB_KEY 3849
#define _SHIFT_TAB_KEY 3848

#define _F1_KEY 15104
#define _F2_KEY 15360
#define _F3_KEY 15616
#define _F4_KEY 15872
#define _F5_KEY 16128
#define _F6_KEY 16384
#define _F7_KEY 16640
#define _F8_KEY 16896
#define _F9_KEY 17512
#define _F10_KEY 17408

#define _SF1_KEY 21504
#define _SF2_KEY 21760
#define _SF3_KEY 22016
#define _SF4_KEY 22272
#define _SF5_KEY 22528
#define _SF6_KEY 22784
#define _SF7_KEY 23040
#define _SF8_KEY 23296
#define _SF9_KEY 23552
#define _SF10_KEY 23808

#define _LARROW_KEY 19200
#define _RARROW_KEY 19712
#define _UARROW_KEY 18432
#define _DARROW_KEY 20480

#define _COLO_KEY 10042		/* Colon */
#define _SCOL_KEY 10043		/* Semicolon */

#define _EXCL_KEY 545		/* Exclamation */
#define _HASH_KEY 1059		/* Hash (pound) */
#define _DOLL_KEY 1316     /* Doller */
#define _AMPE_KEY 2086 		/* Ampersand */

#define _a_KEY 7777
#define _b_KEY 12386
#define _c_KEY 11875
#define _d_KEY 8292
#define _e_KEY 4709
#define _f_KEY 8550
#define _g_KEY 8807
#define _h_KEY 9064
#define _i_KEY 5993
#define _j_KEY 9322
#define _k_KEY 9579
#define _l_KEY 9836
#define _m_KEY 12909
#define _n_KEY 12654
#define _o_KEY 6255
#define _p_KEY 6512
#define _q_KEY 4209
#define _r_KEY 4978
#define _s_KEY 8051
#define _t_KEY 5236
#define _u_KEY 5749
#define _v_KEY 12150
#define _w_KEY 4471
#define _x_KEY 11640
#define _y_KEY 5497
#define _z_KEY 11386

#define _A_KEY 7745
#define _B_KEY 12354
#define _C_KEY 11843
#define _D_KEY 8260
#define _E_KEY 4677
#define _F_KEY 8518
#define _G_KEY 8775
#define _H_KEY 9032
#define _I_KEY 5961
#define _J_KEY 9290
#define _K_KEY 9547
#define _L_KEY 9804
#define _M_KEY 12877
#define _N_KEY 12622
#define _O_KEY 6223
#define _P_KEY 6480
#define _Q_KEY 4177
#define _R_KEY 4946
#define _S_KEY 8019
#define _T_KEY 5204
#define _U_KEY 5717
#define _V_KEY 12118
#define _W_KEY 4439
#define _X_KEY 11608
#define _Y_KEY 5465
#define _Z_KEY 11354

/* **********************************
	Function declaration
	********************************** */

extern int quit(int);

/*	************ End of declration ************ */

/* **********************************
	Data type declaration
	********************************** */

typedef char bool;		/* Boolean data type */

/* **********************************
	Enumerated data type used to
	determine the printable character
	in the background of window.
	********************************** */

typedef enum enmSymbol {

	symbSpace = ' ',
	symbTight = '±',
	symbLoose = '°',
	symbBold = '²',
	symbTil = '~',

	symbReturn = 20,	/* Return Symbol */

	symbHoriz = 'Í',
	symbVerti= 'º',
	symbUpLeft	= 'É',
	symbUpRight = '»',
	symbDnLeft = 'È',
	symbDnRight = '¼',

	symbRightBar = '¹',
	symbLeftBar = 'Ì',
	symbCross = 'Î',

	symbMnuHoriz = 'Ä',
	symbMnuVerti= '³',
	symbMnuUpLeft	= 'Ú',
	symbMnuUpRight = '¿',
	symbMnuDnLeft = 'À',
	symbMnuDnRight = 'Ù',
	symbMnuLeftSep = 'Ã',
	symbMnuRightSep = '´',
	symbMnuTopSep = 'Â',
	symbMnuBottomSep = 'Á',
	symbMnuCross = 'Å',

	symbUpDn = 18,	/* Up-Down point */
	symbDn = '',
	symbUp = '',
	symbLeft = 17,		/* Left Point */
	symbRight = '',
	symbLeftRight = '',

	symbSolid1 = 'þ',
	symbSolid2 = 'ß',
	symbSolid3 = 'Û',
	symbSolid4 = 'ß',
	symbSolid5 = 'Þ',
	symbSolid6 = 'Ý',

	symbDblLT = '®',
	symbDblGT = '¯',
	symbGTE = 'ò',
	symbLTE = 'ó',
	symbSunSign = 15, /* Sun sign */
	symbPlusMinus = 'ñ'

} typSymbols;

/* **********************************
	Enumerated data type used to
	determine the printable portion of
	the window.
	********************************** */

typedef enum enmDrawJob {

	prnAll		= 0,		/* Print all. */
	prnLeft		= 1, 		/* Print only left line. */
	prnTop		= 2,		/* Print only top line.  */
	prnRight		= 3,     /* Print only Right Line. */
	prnBottom	= 4		/* Print only bottom line. */

}	typDrawJob;

/* **********************************
	Enumerated data type used to
	determine the draw style.
	********************************** */

typedef enum enmDrawStyle {

	styleSingle	= 0,
	styleDouble	= 1

}	typDrawStyle;

/* **********************************
	Enumerated data type used to
	determine the dailog box job type.
	********************************** */

typedef enum enmDailog {

	dailogOpen		= 0,
	dailogSave		= 1,
	dailogSaveAs	= 2

}	typDailog;

/* **********************************
	Enumerated data type used to
	determine the alignment.
	********************************** */

typedef enum enmAlignment {

	alignLast			= 0, 		/* Align to last specification. */

	alignTop				= 1,		/* Align to very first row. */
	alignBottom			= 2, 		/* Align to last row. */

	alignLeft			= 3,		/* Align to very left. */
	alignRight			= 4, 		/* Align to very right. */

	alignCenter			= 5,		/* Align to center. */

	alignJustify		= 6,	   /* Align with left & right justification. */

	alignLeftTop		= 7,		/* Align to left top position in the screen. */
	alignRightTop		= 8,     /* Align to right top position in the screen. */

	alignLeftBottom	= 9,     /* Align to left bottom position in the screen. */
	alignRightBottom	= 10      /* Align to right bottom position in the screen. */

}	typAlign;

/* **********************************
	Enumerated data type used to open
	the file.
	********************************** */

typedef enum enmAccessMode {

	opnRead		= 0,		/* Read Only */
	opnWrite		= 1,		/* Read & Write */
	opnUpdate	= 2,		/* Read & Modify */
	opnTruncate	= 3		/* Truncate previous data */

}	typAccessMode;

/* ***************************************
	Enumerated data type used to
	determine the state of command button
	*************************************** */

typedef enum enmState {

	statePush = 0,
	statePop = 1,
	stateNormal = 2,
	stateFocus = 3

}	typState;

/* **********************************
	Enumerated data type for editor's
	working mode.
	********************************** */

typedef enum enmExMode {

	exRead	= 1,	/* Only, reads existing file. */
	exUpdate = 2,	/*	Only, updates existing file. */
	exAppend = 3,	/* Only, appends new lines, at last, in existing file. */
	exCreate	= 4,	/* Creates new file at first save. equals to 1 - 3. */
	exInsert	= 5,	/*	Equals to 1 - 3. */

	exKey		= 6,	/* Each key of keyboard may have its own meaning. */
	exCmd		= 7,	/* The real command interface to the editor. */
	exMenu	= 8	/* The graphical menu system for editor. */

} typexMode;

/* ************************************
	Structure used to define the push
	buttons.
	************************************ */

typedef struct adtCommandButton {

	int id;

	char *caption;

	int left;
	int top;
	int width;
	int height;

	int foreColor;
	int backColor;

	char *mess;

	int (*triger)(void *);

} typCmdButton;

/* ************************************
	Structure used to define the label.
	************************************ */

typedef struct adtLabel {

	char *caption;

	int left;
	int top;

	int width;

	int backColor;			/* Background color. */
	int foreColor;			/* Text color. */
	int hintColor;
	int disableColor;

	bool wordwrap:1;		/* Place a \r after the width length of caption. */
	bool isHint:1;
	bool isDisable:1;

} typLabel;

/* **********************************
	Structure used to define the text
	box.
	********************************** */

typedef struct adtTextBox {

	char *text;
	char *txtLoc;        /* Current loctaion in text for editing. */

	int offset;				/* No. of hidden characters. */

	int left;
	int top;

	int width;

	int cursx;
	int cursy;

	int backColor;			/* Background color. */
	int foreColor;			/* Text color. */
	int disableColor;		/* Text color while textbox is disable. */

	int maxLen;				/* Maximum character that may contain. */

	bool isMultiline:1;	/* Whether textbox suports multiple lines access. */
	int lines;				/* Nos of line if, isMultiline is true. */

	char *mess;

	int (*trgActivate)(struct adtTextBox);
	int (*trgChange)(struct adtTextBox);
	int (*trgValidate)(struct adtTextBox);

	int (*trgDefault)(struct adtTextBox);
	int (*trgCancel)(struct adtTextBox);

	bool isLocked:1;
	bool isDisable:1;

} typTxtbox;

/* ***************************************
	Structure used to define window.
	*************************************** */

typedef struct adtWindow {

	int id;						/* Unique id. */

	char *caption;				/* Caption to be shown on title bar. */

	typAlign capAlign;		/* Caption alignment. */

	int left;					/* X cordinate of the window. */
	int top;						/* Y cordinate of the window. */
	int width;					/* Actual width of the window. */
	int height;					/* Actual height of the window. */

	int scaleLeft;          /* X cordinate of work envelop. */
	int scaleTop;			  	/* Y cordinate of work envelop. */
	int scaleWidth;		 	/* Width of work envelop. */
	int scaleHeight;			/* Height of work envelop. */

	int cursx;					/* X cordinate of cursor. */
	int cursy;					/* Y cordinate of cursor. */

	int sepCount;				/* Seprator count. */
	int *sepLine;				/* Seprator line nos. */

	int lenNotice;				/* Maximum length of the notice, may appear. */

	char *lastdata;			/* Keeps the data on which this window is
										being displayed. */

	bool hasVertiScrl:1;
	bool hasHorizScrl:1;

	struct adtWindow *next;
	struct adtWindow *pre;

} typWindow;

/* **********************************
	Structure used to to define list
	view nodes.
	********************************** */

typedef struct adtListViewNode {

	void *item;

	char *caption;

	int left;
	int top;

	int maxWidth;

	int foreColor;
	int backColor;

	int (*trgGotFocus)(void *item);
	int (*trgDefault)(void *item);
	int (*trgCancel)(void *item);

	struct adtListViewNode *next;
	struct adtListViewNode *pre;

} typListViewNode;

/* **********************************
	Structure used to to define list
	view.
	********************************** */

typedef struct adtListView {

	int left;
	int top;
	int width;
	int height;

	int scaleLeft;
	int scaleTop;
	int scaleWidth;
	int scaleHeight;

	int offset;
	int secLen;			/* Nos of files, an individual section within
								the list view, may contain. */
	int foreColor;
	int backColor;

	typListViewNode *headNode;
	typListViewNode *tailNode;
	typListViewNode *firstNode;
	typListViewNode *lastNode;
	typListViewNode *currNode;

	bool hasHorizScroll:1;
	bool shouldShowOuter:1;

	int (*trgGotFocus)(void *item);
	int (*trgMove)(void *item);
	int (*trgValidate)(void *item);

	int (*trgDefault)(void *item);
	int (*trgCancel)(void *item);

} typListView;

/* **********************************
	Structure used to keep store the
	lines of the file opened.
	********************************** */

typedef struct adtLine {

	char *line;

	struct adtLine *next;
	struct adtLine *pre;

} typLine;

/* ******************************************
	Structure used to keep the info.
	regarding the in-memory copy of the file.
	****************************************** */

typedef struct adtFile {

	int id;						/* Unique file id. */

	char *filename;  			/* Complete file name i.e. absolute path. */
	char *filetitle;			/* The actual file name. */

	int offset;					/* X postion on actual string. */

	typLine *root;
	typLine *end;
	typLine *first;
	typLine *last;
	typLine *curr;

	int lines;					/* Total line in the file. */

	bool hasChanged:1;      /* Indicates whether the file has been changed
										since last save. */

	struct adtFile *next;
	struct adtFile *pre;

} typFile;

/* **********************************
	Structure used to define the menu
	system for the editor.
	********************************** */

typedef struct adtMenuItem {

	int	mnuid;			/* Unique menu-id for each menu item. */

	char 	hotkey;			/* Hot key defined for menu item. */
	char 	*caption;		/* Caption shown on menu item. */
	char 	*key;				/* The key combination may be used to activate the menu item. */
	char 	*keyCaption;	/* Caption shown in respect to key defined & used. */
	char 	*mess;			/* Message relative to menu item. */

	struct adtMenuItem *(*triger)(struct adtMenuItem *);   /* Associated action triger. */

	int 	x;					/* X cordinate where that menu item displayed. */
	int 	y;             /* Y cordinate where that menu item displayed. */

	int 	height;			/* Height of the entire popup in which that menu item exist. */
	int   width;			/* Width of that menu item. (i.e. caption len + keycaption len + margins) */

	bool	hasSubMenu:1;		/* Whether this menu item generates another menu or not? */
	bool	ispad:1;			/* Whether this menu item is pad or not? */
	bool 	isdisable:1;		/* Whether this menu item is disabled or not? */

	char *lastdata;		/* Keeps the data of the rectangle in which the sub-menu will appear. */
	struct adtMenuItem *item;  /* Header of the menu-popup that is being appear as sub-menu. */

	struct adtMenuItem *next;
	struct adtMenuItem *pre;

} typMenuItem;

/* ********************************** */

/* **********************************
	Variable declaration
	********************************** */

extern int gMaxRows, gMaxCols, gTop, gLeft, gRight, gBottom;
extern int gTablen;
extern int gscrbkColor, gscrforeColor, gmnubkColor,
				gtxtbkColor, gtxtforeColor, gtxtdisableColor,
				glblbkColor, glblforeColor, glblhintColor, glbldisableColor,
				glstviewbkColor, glstviewforeColor, glstviewnodebkColor,
				glstviewnodeforeColor, glstviewselColor,
				gcmdforeColor, gcmdbkColor, gcmdshadowColor, gcmdfocusColor;

extern char gTabStr[20];
extern char gTabChar;

extern bool isAlpha;

extern typMenuItem *padMain;
extern typMenuItem *popFile;

extern typFile *Folder, *boxFile;
extern typWindow *baseWin, *actWin;

extern char *lstexMode[];

extern typexMode gEdMode;

extern struct text_info txtsetting;

/*	************ End of declration ************ */