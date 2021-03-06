/* See LICENSE file for copyright and license details. */

#define TERMINAL "xfce4-terminal"
#define TERMINAL_CLASS "Xfce4-terminal"

#include "push.c"
#include <X11/XF86keysym.h>

/* appearance */
static const char *fonts[] = {
//    "Sans:size=10.5",
    "Liberation Mono:size=10.5",
    "VL Gothic:size=10.5",
    "WenQuanYi Micro Hei:size=10.5",
    "FontAwesome:size=10.5",
};
static const char dmenufont[] = "-*-terminus-medium-r-*-*-16-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#444444";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#005577";
static const char selbgcolor[]      = "#005577";
static const char selfgcolor[]      = "#eeeeee";
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const Bool systraypinningfailfirst = True;   /* True: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const Bool showsystray       = True;     /* False means no systray */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
//1 internet, 2 terminals 3 code 4 social 5 pics/videos 6 files 7 docs
static const char *tags[] = { "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class            instance    title       tags mask     isfloating   monitor */
	{ "Gimp",           NULL,       NULL,       0,            True,        -1 },
	{ "Chromium",       NULL,       NULL,       1,            False,       -1 },
	{ "Subl3",          NULL,       NULL,       1 << 2,       False,       -1 },
	{ "Thunar",         NULL,       NULL,       1 << 5,       False,       -1 },
	{ TERMINAL_CLASS,   NULL,       "Terminal", 0,            False,       -1 },
	{ TERMINAL_CLASS,   NULL,       "Youtube",  1 << 3,       False,       -1 },
	{ TERMINAL_CLASS,   NULL,       "E-mail",   1 << 3,       False,       -1 },
	{ TERMINAL_CLASS,   NULL,       "Twitter",  1 << 3,       False,       -1 },
	{ "mpv",            NULL,       NULL,       ~0,           False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */
static const float popuptermmfact = 0.32; /* factor of master area size for pop-up terminal height [0.05..0.95] */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ " ",      tile },    /* first entry is default */
	{ " ",      NULL },    /* no layout function means floating behavior */
	{ " ",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY|ControlMask,           KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY,                       KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
//static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };
static const char *quake[]  = { TERMINAL, "--drop-down", NULL };
static const char *web1[]  = { "chromium", NULL };
static const char *web2[]  = { "dwb", NULL };
static const char *editor[]  = { "subl3", NULL };
static const char *explorer[]  = { "thunar", NULL };
static const char *volumeup[]  = { "amixer", "set", "-q", "Master", "playback", "5%+", NULL };
static const char *volumedown[]  = { "amixer", "set", "-q", "Master", "playback", "5%-", NULL };
static const char *mute[]       = { "amixer", "set", "-q", "Master", "toggle", NULL };
static const char *youtube[] = { TERMINAL, "-T", "Youtube", "-e", "mpsyt", NULL };
static const char *email[] = { TERMINAL, "-T", "E-mail", "-e", "mutt", NULL };
static const char *twitter[] = { TERMINAL, "-T", "Twitter", "-e", "rainbowstream", NULL };
static const char *mc[] = { TERMINAL, "-T", "Midnight Commander", "-e", "mc", NULL };

static Key keys[] = {
	/* modifier                     key                        function        argument */
	{ MODKEY,                       XK_p,                      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,                 spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_w,                      spawn,          {.v = web1 } },
	{ MODKEY|ShiftMask,             XK_w,                      spawn,          {.v = web2 } },
	{ MODKEY,                       XK_e,                      spawn,          {.v = editor } },
	{ MODKEY,                       XK_f,                      spawn,          {.v = explorer } },
	{ MODKEY,                       XK_y,                      spawn,          {.v = youtube } },
	{ MODKEY,                       XK_m,                      spawn,          {.v = email } },
	{ MODKEY,                       XK_t,                      spawn,          {.v = twitter } },
	{ MODKEY,                       XK_c,                      spawn,          {.v = mc } },
	{ MODKEY,                       XK_Up,                     spawn,          {.v = volumeup } },
	{ MODKEY,                       XK_Down,                   spawn,          {.v = volumedown } },
	{ MODKEY,                       XK_s,                      swapfocus,      {0} },
	{ MODKEY,                       XK_b,                      togglebar,      {0} },
	{ MODKEY,                       XK_j,                      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                      focusstack,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_j,                      pushdown,       {0} },
    { MODKEY|ShiftMask,             XK_k,                      pushup,         {0} },
	{ MODKEY,                       XK_i,                      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,                      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,                      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,                      setcfact,       {.f =  0.00} },
	{ MODKEY,                       XK_Return,                 zoom,           {0} },
	{ MODKEY,                       XK_Tab,                    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,                      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,                      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,                      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,                      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,                  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,                  togglefloating, {0} },
	{ MODKEY,                       XK_0,                      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,                 focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                 tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_Left,                   viewtoleft,     {0} },
	{ MODKEY,                       XK_Right,                  viewtoright,    {0} },
	{ MODKEY|ShiftMask,             XK_Left,                   tagtoleft,      {0} },
	{ MODKEY|ShiftMask,             XK_Right,                  tagtoright,     {0} },
	{ 0,                            XF86XK_AudioLowerVolume,   spawn,          {.v = volumedown } },
	{ 0,                            XF86XK_AudioRaiseVolume,   spawn,          {.v = volumeup } },
	{ 0,                            XF86XK_AudioMute,          spawn,          {.v = mute } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,                      quit,           {0} },
	{ 0,                            XK_F12,                    runorraise,     {.v = quake } },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

