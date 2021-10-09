/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
 static const char dmenufont[]       = "monospace:size=10";
 static const char col_gray1[]       = "#171718";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee"; 
static const char col_cyan[]        = "#222222";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "code", "sh", "www", "dc", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Discord",  NULL,	  NULL,	      0,	    0		 -1 },
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask //Super key
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *browsercmd[]  = { "brave", NULL };
static const char *flameshotcmd[]  = { "flameshot", "gui", NULL };
static const char *codecmd[]  = { "code", NULL };
static const char *discordcmd[] = { "discord", NULL };

static Key keys[] = {
	/* modifier                     key        	function        argument */
	{ MODKEY,                       XK_space,  	spawn,          {.v = dmenucmd } },	//Super + space		Open dmenu
	{ MODKEY,		        XK_Return, 	spawn,          {.v = termcmd } },	//Super + Enter 	Open terminal
	{ MODKEY,		        XK_w,		spawn,          {.v = browsercmd } },	//Super + w	 	Open Browser	
	{ NULL,				0xff61,		spawn,		{.v = flameshotcmd } },	//Super + printscr	Screenshot	
	{ MODKEY,			XK_c,		spawn,		{.v = codecmd } },	//Super + c		Open VS code	
	{ MODKEY,			XK_d,		spawn,		{.v = discordcmd } },	//Super + d		Open Discord
	{ MODKEY,                       XK_b,		togglebar,      {0} },			//Super + b 		enable/disable top bar
	{ MODKEY,                       XK_j,      	focusstack,     {.i = +1 } },		//Super + j		Focus on next stack
	{ MODKEY,                       XK_k,      	focusstack,     {.i = -1 } },		//Super + k		Focus on previous stack
	{ MODKEY,                       XK_Up,      	incnmaster,     {.i = +1 } },		
	{ MODKEY,                       XK_Down,      	incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_Left,      	setmfact,       {.f = -0.025} },	//super + Left arrow 	decrease master window size
	{ MODKEY,                       XK_Right,      	setmfact,       {.f = +0.025} },	//super + Right arrow	increase master window size
	//{ MODKEY,                     XK_Return, 	zoom,		{0} },
	{ MODKEY,                       XK_Tab,    	view,           {0} },
	{ MODKEY,		        XK_q,      	killclient,     {0} },			//Super + q		Kill current window
	{ MODKEY,                       XK_t,      	setlayout,      {.v = &layouts[0]} },	//super + t 		change window layout
	{ MODKEY,                       XK_f,      	setlayout,      {.v = &layouts[1]} },	//super + f 		change window layout
	{ MODKEY,                       XK_m,      	setlayout,      {.v = &layouts[2]} },	//super + m 		change window layout
	//{ MODKEY,                     XK_space,  setlayout,      {0} },
	//{ MODKEY|ShiftMask,           XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      	view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      	tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  	focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, 	focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  	tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, 	tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },			//Super + Shift + e	Exit dwm
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
