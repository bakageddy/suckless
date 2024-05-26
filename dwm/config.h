/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>
#include <stddef.h>

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "iosevka:size=12" };
static const char dmenufont[]       = "iosevka:size=12";

// Grayscale Dark

static const char grayscale_bg[]       = "#101010";
static const char grayscale_fg[]       = "#ababab";
static const char grayscale_gray[]        = "#ababab";

// // Gruvbox

static const char gruvbox_black[]		= "#1D2021";
static const char gruvbox_white[]		= "#D4BE98";
static const char gruvbox_violet[]		= "#D3869B";
static const char gruvbox_blue[]		= "#83A598";
static const char gruvbox_cyan[]		= "#8EC07C";
static const char gruvbox_green[]		= "#B8BB26";
static const char gruvbox_yellow[]		= "#FABD2F";
static const char gruvbox_orange[]		= "#FE8019";
static const char gruvbox_red[]			= "#FF5F5F";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { gruvbox_white, gruvbox_black, gruvbox_black},
	[SchemeSel]  = { gruvbox_white, gruvbox_black, gruvbox_black},
};

/* tagging */
static const char *tags[] = { 
	"ヂ",
	"ネ",
	"セ",
	"フ",
	"ク",
	"マ",
	"ル"
};

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
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
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
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", gruvbox_black, "-nf", gruvbox_white, "-sb", gruvbox_orange, "-sf", gruvbox_black, NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *lfcmd[] = {"kitty", "-e", "lf", NULL};
static const char *zathuracmd[] = {"zathura", NULL};
static const char *browsercmd[] = {"firefox", NULL};
static const char *increase_vol[] = {"amixer", "set", "Master", "5%+", NULL};
static const char *decrease_vol[] = {"amixer", "set", "Master", "5%-", NULL};
static const char *mute[] = {"amixer", "set", "Master", "toggle", NULL};
static const char *screenshotcmd[] = {"/bin/sh", "-c", "scrot ~/Pictures/Screenshots/%Y-%m-%d-%T.png", NULL};
static const char *decrease_light[] = {"xbacklight", "-5", NULL};
static const char *increase_light[] = {"xbacklight", "+5", NULL};

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,						XK_w,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	// User defined remaps
	{ MODKEY | ShiftMask,           XK_b,		spawn,         {.v = browsercmd}},
	{ MODKEY | ShiftMask,			XK_e,		spawn,		   {.v = lfcmd}},
	{ MODKEY | ShiftMask,			XK_z,		spawn,		   {.v = zathuracmd}},

	{0,								XF86XK_AudioLowerVolume, spawn, {.v = decrease_vol}},
	{0,								XF86XK_AudioRaiseVolume, spawn, {.v = increase_vol}},
	{0,								XF86XK_AudioMute,		 spawn, {.v = mute}},
	{MODKEY | ShiftMask,			XK_s,					 spawn, {.v = screenshotcmd}},
	{MODKEY | Mod1Mask,				XK_Up,					 spawn, {.v = increase_light}},
	{MODKEY | Mod1Mask,				XK_Down,			     spawn, {.v = decrease_light}},
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

