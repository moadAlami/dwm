/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char normbgcolor[]           = "#2F343F";
static const char normbordercolor[]       = "#2f343f";
static const char normfgcolor[]           = "#ffffff";
static const char selfgcolor[]            = "#ffffff";
static const char selbordercolor[]        = "#7FB095";
static const char selbgcolor[]            = "#005577";

/* alpha patch */
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;

static const char *colors[][3]      = {
	/*               fg         	bg         border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
    [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* alpha patch */
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class			instance    title   tags mask   iscentered    isfloating isterminal	noswallow	monitor */
	{ "Gimp",			NULL,       NULL,   0,          0,				1,		  0,		 0,			-1 },
	{ "firefox",		NULL,       NULL,   1 << 1,	    0,				0,		  0,		 0,			-1 },
	{ "pavucontrol",    NULL,		NULL,	0,			1,				1,		  0,		 0,			-1 },
	{ "discord",   		NULL,		NULL,	1 << 3,		0,				0,		  0,		 0,			-1 },
	{ "steam",   		NULL,		NULL,	1 << 4,		0,				0,		  0,		 0,			-1 },
	{ "kitty",   		NULL,		NULL,	0,			0,				0,		  1,		 1,			-1 },
	{ "st",		   		NULL,		NULL,	0,			0,				0,		  1,		 1,			-1 },
	{ "xclock",		   	NULL,		NULL,	0,			0,				1,		  0,		 0,			-1 },

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */

/* stackmfact patch */
static const float smfact     = 0.00; /* factor of tiled clients [0.00..0.95] */

static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	/* bottomstack patch */
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	/* centeredmaster patch */
	{ "|C|",      centeredmaster },
	{ ">C>",      centeredfloatingmaster },
	/* gridmode patch */
	{ "HHH",      grid },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "kitty", NULL };

/* scratchpad patch */
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

#include <X11/XF86keysym.h>
/* volume control */
static const char *inc_vol[] = { "/home/moadalami/Scripts/volume/inc_vol", NULL };
static const char *dec_vol[] = { "/home/moadalami/Scripts/volume/dec_vol", NULL };
static const char *toggle_vol[] = { "/home/moadalami/Scripts/volume/toggle_vol", NULL };

/* brightness control */
static const char *inc_bright[] = { "/home/moadalami/Scripts/brightness/inc_bright", NULL };
static const char *dec_bright[] = { "/home/moadalami/Scripts/brightness/dec_bright", NULL };

/* music player controls */
static const char *next[] = { "/home/moadalami/Scripts/music/next", NULL };
static const char *previous[] = { "/home/moadalami/Scripts/music/previous", NULL };
static const char *pause_play[] = { "/home/moadalami/Scripts/music/pause-play", NULL };

/* movestack patch */
#include "movestack.c"

static Key keys[] = {
	/* modifier             key        					function        argument */

	{ 0,					XK_Num_Lock,				spawn,			SHCMD("kill -9 $(cat /home/moadalami/github/dwm-bar/dwmpid)") },
	{ MODKEY|ShiftMask,		XK_o,						spawn,			SHCMD("shutdown now") },
	{ MODKEY|ShiftMask,		XK_x,						spawn,			SHCMD("i3lock") },

	{ MODKEY,               XK_t,						setlayout,      {.v = &layouts[0]} },
	{ MODKEY,               XK_space,					setlayout,      {.v = &layouts[1]} },
	{ MODKEY,               XK_m,						setlayout,      {.v = &layouts[2]} },
	{ MODKEY,               XK_v,						setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,     XK_v,						setlayout,      {.v = &layouts[4]} },
	{ MODKEY,               XK_u,						setlayout,      {.v = &layouts[5]} },
	{ MODKEY,               XK_o,						setlayout,      {.v = &layouts[6]} },
	{ MODKEY,               XK_g,						setlayout,      {.v = &layouts[7]} },

	/* moveresize patch */
	{ Mod1Mask,					XK_j,	moveresize,		{.v = (int []){ 0, 25, 0, 0 }}},
	{ Mod1Mask,					XK_k,		moveresize,		{.v = (int []){ 0, -25, 0, 0 }}},
	{ Mod1Mask,					XK_l,	moveresize,		{.v = (int []){ 25, 0, 0, 0 }}},
	{ Mod1Mask,					XK_h,	moveresize,		{.v = (int []){ -25, 0, 0, 0 }}},
	{ Mod1Mask|ShiftMask,			XK_j,	moveresize,		{.v = (int []){ 0, 0, 0, 25 }}},
	{ Mod1Mask|ShiftMask,			XK_k,	moveresize,		{.v = (int []){ 0, 0, 0, -25 }}},
	{ Mod1Mask|ShiftMask,			XK_l,	moveresize,		{.v = (int []){ 0, 0, 25, 0 }}},
	{ Mod1Mask|ShiftMask,			XK_h,	moveresize,		{.v = (int []){ 0, 0, -25, 0 }}},


	{ 0,					XF86XK_MonBrightnessUp, 	spawn,			{.v = inc_bright } },
	{ 0,					XF86XK_MonBrightnessDown, 	spawn,			{.v = dec_bright } },

	{ 0,					XF86XK_AudioRaiseVolume,	spawn,			{.v = inc_vol } },
	{ 0,					XF86XK_AudioLowerVolume,	spawn,			{.v = dec_vol } },
	{ 0,					XF86XK_AudioMute,			spawn,			{.v = toggle_vol } },

	{ MODKEY,				XK_F1,						spawn,			{.v = next } },
	{ MODKEY,				XK_F2,						spawn,			{.v = pause_play } },
	{ MODKEY,				XK_F3,						spawn,			{.v = previous } },

	{ MODKEY,               XK_s,      					togglesticky,   {0} },
	{ MODKEY,               XK_a,  	   					togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,               XK_h,      					setmfact,       {.f = -0.05} },
 	{ MODKEY,               XK_l,      					setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,     XK_j,      					movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_k,      					movestack,      {.i = -1 } },

	{ MODKEY,               XK_equal,				   	setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_equal,					setgaps,        {.i = -1 } },

	{ Mod1Mask|ShiftMask,   XK_equal,					setborderpx,    {.i = -1 } },
	{ Mod1Mask,             XK_equal,					setborderpx,    {.i = +1 } },
	{ Mod1Mask,   			XK_agrave, 					setborderpx,    {.i = 0 } },


	{ MODKEY,               XK_d,						spawn,          {.v = dmenucmd } },
	{ MODKEY,			    XK_Return,					spawn,          {.v = termcmd } },
	{ MODKEY,               XK_b,						togglebar,      {0} },
	{ MODKEY,               XK_j,						focusstack,     {.i = +1 } },
	{ MODKEY,               XK_k,						focusstack,     {.i = -1 } },
	{ MODKEY,               XK_i,						incnmaster,     {.i = +1 } },
	{ MODKEY,               XK_p,						incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,     XK_f,						zoom,           {0} },
	{ MODKEY,               XK_Tab,						view,           {0} },
	{ MODKEY|ShiftMask,     XK_q,						killclient,     {0} },
	{ MODKEY,             	XK_f,						fullscreen,     {0} },
	{ MODKEY|ShiftMask,     XK_space,					togglefloating, {0} },
	{ MODKEY,               XK_0,						view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,     XK_0,						tag,            {.ui = ~0 } },
	{ MODKEY,               XK_comma,					focusmon,       {.i = -1 } },
	{ MODKEY,               XK_period,					focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_comma,					tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,     XK_period,					tagmon,         {.i = +1 } },
	TAGKEYS(                XK_ampersand,                  0)
	TAGKEYS(                XK_eacute,                     1)
	TAGKEYS(                XK_quotedbl,                   2)
	TAGKEYS(                XK_apostrophe,                 3)
	TAGKEYS(                XK_parenleft,                  4)
	TAGKEYS(                XK_minus,                      5)
	TAGKEYS(                XK_egrave,                     6)
	TAGKEYS(                XK_underscore,                 7)
	TAGKEYS(                XK_ccedilla,                   8)
	/* { MODKEY|ShiftMask,             XK_q,      quit,           {0} }, */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

