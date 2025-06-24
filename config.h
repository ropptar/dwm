/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 15;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Hack Nerd Font:size=12" };
static const char dmenufont[]       = "Hack Nerd Font:size=12";
static const char col_bg[]       = "#282828";
static const char col_bg1[]       = "#3c3836";
static const char col_gray3[]       = "#665c53";
static const char col_fg[]       = "#ebdbb2";
static const char col_blue[]        = "#458588";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_fg, col_bg, col_blue },
	[SchemeSel]  = { col_bg, col_blue,  col_blue },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "S" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class			instance	title	tags mask	isfloating	monitor */
	{ "librewolf",		NULL,		NULL,	1 << 1,		0,			-1 },
	{ "TelegramDesktop",NULL,		NULL,	1 << 2,		0,			-1 },
	{ "Spotify",		NULL,		NULL,	1 << 3,		0,			-1 },
	{ "steam",			NULL,		NULL,	1 << 4,		0,			-1 },
	{ "v2rayN",			NULL,		NULL,	1 << 8,		0,			-1 },
	{ "NoiseTorch",		NULL,		NULL,	1 << 8,		0,			-1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "grid.c"
#include "tatami.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "HHH",      grid },
	{ "|+|",      tatami },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_bg, "-nf", col_fg, "-sb", col_blue, "-sf", col_bg, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *kbdcmd[]  = { "pkill", "-RTMIN+1", "dwmblocks", NULL };

static const Key keys[] = {
	/* modifier										key				function	argument */
	{ MODKEY, /* dmenu */							XK_d,			spawn,			{.v = dmenucmd } },
	{ MODKEY, /* terminal */						XK_Return,		spawn,			{.v = termcmd } },
	{ 0, /* prtscr */								XK_Print,		spawn,			SHCMD("~/scripts/screenshot.sh") },

	{ MODKEY, /* bar on/off */						XK_b,			togglebar,		{0} },
	{ MODKEY, /* next win */						XK_j,			focusstack,		{.i = +1 } },
	{ MODKEY, /* prev win */						XK_k,			focusstack,		{.i = -1 } },
	{ MODKEY,										XK_i,			incnmaster,		{.i = +1 } },
	{ MODKEY,										XK_p,			incnmaster,		{.i = -1 } },
	{ MODKEY, /* resize - */						XK_h,			setmfact,		{.f = -0.05} },
	{ MODKEY, /* resize + */						XK_l,			setmfact,		{.f = +0.05} },
	{ MODKEY|ShiftMask, /*make master */			XK_m,			zoom,			{0} },
	{ MODKEY, /* cycle last 2 tabs*/				XK_Tab,			view,			{0} },
	{ MODKEY|ShiftMask, /* kill app */				XK_q,			killclient,		{0} },

	{ MODKEY, /* tiling */							XK_t,			setlayout,		{.v = &layouts[0]} },
	{ MODKEY|ShiftMask, /* floating */ 				XK_v,			setlayout,		{.v = &layouts[1]} },
	{ MODKEY|ShiftMask, /* monocle(fullscreen) */	XK_f,			setlayout,		{.v = &layouts[2]} },
	{ MODKEY, /* actual fullscreen */				XK_f,			fullscreen,		{0} },
	{ MODKEY, /* grid */							XK_g,			setlayout,		{.v = &layouts[3]} },
	{ MODKEY|ShiftMask, /* tatami */				XK_t,			setlayout,		{.v = &layouts[4]} },
	{ MODKEY|ControlMask, /* toggle win floating*/	XK_v,			togglefloating,	{0} },

	{ MODKEY, /* show all windows*/					XK_0,			view,			{.ui = ~0 } },
	{ MODKEY|ShiftMask, /* tag win 0 */				XK_0,			tag,			{.ui = ~0 } },
	{ MODKEY,										XK_comma,		focusmon,		{.i = -1 } },
	{ MODKEY,										XK_period,		focusmon,		{.i = +1 } },
	{ MODKEY|ShiftMask,								XK_comma,		tagmon,			{.i = -1 } },
	{ MODKEY|ShiftMask,								XK_period,		tagmon,			{.i = +1 } },
 	{ MODKEY,										XK_minus,		setgaps,		{.i = -1 } },
 	{ MODKEY,										XK_equal,		setgaps,		{.i = +1 } },
 	{ MODKEY|ShiftMask,								XK_equal,		setgaps,		{.i = 0 } },
	TAGKEYS(										XK_1,			0)
	TAGKEYS(										XK_2,			1)
	TAGKEYS(										XK_3,			2)
	TAGKEYS(										XK_4,			3)
	TAGKEYS(										XK_5,			4)
	TAGKEYS(										XK_6,			5)
	TAGKEYS(										XK_7,			6)
	TAGKEYS(										XK_8,			7)
	TAGKEYS(										XK_s,			8)
	{ MODKEY, /* signal layout to chg dwmblocks */	XK_space,		spawn,			{.v = kbdcmd} },
	{ MODKEY|ShiftMask, /* kill dwm */				XK_BackSpace,	quit,			{0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

