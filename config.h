/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 2;        /* 2 is the default spacing around the bar's font */

static const char *fonts[] = { "monospace:size=11",
    "Noto Color Emoji:pixelsize=11:antialias=true:autohint=true"};
static const char dmenufont[]             = "monospace:size=12";
static const char normbgcolor[]           = "#222222";
static const char normbordercolor[]       = "#444444";
static const char normfgcolor[]           = "#bbbbbb";
static const char selfgcolor[]            = "#eeeeee";
static const char selbordercolor[]        = "#005577";
static const char selbgcolor[]            = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor } ,
	[SchemeSel]  = { selfgcolor , selbgcolor ,  selbordercolor  },
};

#include "movestack.c"
#include <X11/XF86keysym.h>
/* volume control */
static const char *inc_vol[] = {"/home/mouad/.local/bin/volume/inc_vol", NULL};
static const char *dec_vol[] = {"/home/mouad/.local/bin/volume/dec_vol", NULL};
static const char *toggle_vol[] = {"/home/mouad/.local/bin/volume/toggle_vol",
                                   NULL};

/* brightness control */
static const char *inc_bright[] = {
    "/home/mouad/.local/bin/brightness/inc_bright", NULL};
static const char *dec_bright[] = {
    "/home/mouad/.local/bin/brightness/dec_bright", NULL};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
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
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", "#000000", "-nf", "#268bd2", "-sb", "#268bd2", "-sf", "#000000", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,			XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_a,	   togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_f,	   zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_space,  setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,			XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } }, 
	{MODKEY,			XK_s,	   togglesticky,   {0}},
	TAGKEYS(XK_ampersand                , 0)
	TAGKEYS(XK_eacute                   , 1)
	TAGKEYS(XK_quotedbl                 , 2)
        TAGKEYS(XK_apostrophe               , 3)
	TAGKEYS(XK_parenleft                , 4)
	TAGKEYS(XK_minus                    , 5)
	TAGKEYS(XK_egrave                   , 6)
	TAGKEYS(XK_underscore               , 7)
	TAGKEYS(XK_ccedilla                 , 8)
	/* Custom commands */

	{MODKEY | ShiftMask, XK_o, spawn, SHCMD("[ $(echo -e 'Yes\nNo' | dmenu -i -p 'Are you sure you want to shutdown?') == 'Yes' ] && shutdown now")},
	{MODKEY | ShiftMask, XK_x, spawn, SHCMD("i3lock -c 252525")},

	/* dunst control */
	{ControlMask, XK_egrave, spawn, SHCMD("dunstctl history-pop")},
	{ControlMask, XK_space, spawn, SHCMD("dunstctl close")},
	{ControlMask | ShiftMask, XK_space, spawn, SHCMD("dunstctl close-all")},

	{0, XF86XK_MonBrightnessUp, spawn, {.v = inc_bright}},
	{0, XF86XK_MonBrightnessDown, spawn, {.v = dec_bright}},

	{0, XF86XK_AudioRaiseVolume, spawn, {.v = inc_vol}},
	{0, XF86XK_AudioLowerVolume, spawn, {.v = dec_vol}},
	{0, XF86XK_AudioMute, spawn, {.v = toggle_vol}},

	{MODKEY, XK_F1, spawn, {.v = dec_vol}},
	{MODKEY, XK_F2, spawn, {.v = inc_vol}},
	{MODKEY, XK_F3, spawn, {.v = toggle_vol}},

	{Mod1Mask, XK_F1, spawn, SHCMD("mpc prev")},
	{Mod1Mask, XK_F2, spawn, SHCMD("mpc toggle")},
	{Mod1Mask, XK_F3, spawn, SHCMD("mpc next")},

	{0, XK_Pause, spawn, SHCMD("playerctl play-pause")},

	/* screenshot */
	{MODKEY, XK_F12, spawn, SHCMD("scrot -e 'mv $f /home/mouad/Pictures/Screenshots/' && notify-send '📸 Screenshot taken'")},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

