/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 4;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int user_bh            = 28;       /* 0 means derive from font, otherwise explicit bar height */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=8" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font:size=8";
static const char col_bg[]          = "#1f2335";
static const char col_border[]      = "#9d7cd8";
static const char col_text[]        = "#a9b1d6";
static const char col_inactive[]    = "#292e42";
static const char col_urgent[]      = "#900000";
static const char *colors[][3]      = {
        /*               fg         bg         border   */
        [SchemeNorm] = { col_text,  col_bg,    col_inactive },
        [SchemeSel]  = { col_bg,    col_border,col_border },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",                     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",                  NULL,       NULL,       1 << 3,       0,           -1 },
	{ "com.spt.postlink.gui.Application", NULL, NULL,    1 << 3,       0,           -1 },
	{ "telegram-desktop",         NULL,       NULL,       1 << 3,       0,           -1 },
	{ "nekoray",                  NULL,       NULL,       1 << 8,       0,           -1 },
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

/* commands */
static const char *dmenucmd[] = { "rofi", "-show", "drun", "-run-shell-command", "alacritty -e zsh -ic '{cmd} && read'", NULL };
static const char *combi[]    = { "rofi", "-show", "combi", "-show-icons", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *filemgr[]  = { "alacritty", "-e", "vifm", NULL };
static const char *kbtoggle[] = { "setxkbmap", "-model", "pc105", "-layout", "us,ru", "-variant", "", "-option", "grp:win_space_toggle", NULL };
static const char *volumeup[]   = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+10%", NULL };
static const char *volumedown[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-10%", NULL };
static const char *volumemute[] = { "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL };
static const char *micmute[]    = { "pactl", "set-source-mute", "@DEFAULT_SOURCE@", "toggle", NULL };
static const char *playernext[] = { "playerctl", "next", NULL };
static const char *playerprev[] = { "playerctl", "previous", NULL };
static const char *lockcmd[]    = { "sh", "-c", "setxkbmap us && betterlockscreen --lock blur --span --display 1 && setxkbmap -model pc105 -layout us,ru -variant -option grp:win_space_toggle", NULL };
static const char *screenshot[] = { "sh", "-c", "maim -s | xclip -selection clipboard -t image/png", NULL };

static const Key keys[] = {
        /* modifier                     key                       function        argument */
        { MODKEY,                       XK_Return,                 spawn,          {.v = termcmd } },
        { MODKEY|ShiftMask,             XK_q,                      killclient,     {0} },
        { MODKEY,                       XK_d,                      spawn,          {.v = dmenucmd } },
        { MODKEY|ShiftMask,             XK_d,                      spawn,          {.v = combi } },
        { MODKEY,                       XK_x,                      spawn,          {.v = filemgr } },
        { MODKEY,                       XK_c,                      spawn,          {.v = kbtoggle } },
        { MODKEY|ShiftMask,             XK_s,                      spawn,          {.v = screenshot } },
        { ControlMask|MODKEY,           XK_l,                      spawn,          {.v = lockcmd } },
        { MODKEY,                       XK_b,                      togglebar,      {0} },
        { MODKEY,                       XK_j,                      focusstack,     {.i = +1 } },
        { MODKEY,                       XK_k,                      focusstack,     {.i = -1 } },
        { MODKEY,                       XK_h,                      setmfact,       {.f = -0.05} },
        { MODKEY,                       XK_l,                      setmfact,       {.f = +0.05} },
        { MODKEY|ShiftMask,             XK_f,                      togglefloating, {0} },
        { MODKEY,                       XK_f,                      togglefullscr,  {0} },
        { MODKEY,                       XK_space,                  setlayout,      {0} },
        { MODKEY,                       XK_e,                      setlayout,      {.v = &layouts[0]} },
        { MODKEY,                       XK_w,                      setlayout,      {.v = &layouts[2]} },
        { MODKEY,                       XK_Tab,                    view,           {0} },
        { MODKEY,                       XK_comma,                  focusmon,       {.i = -1 } },
        { MODKEY,                       XK_period,                 focusmon,       {.i = +1 } },
        { MODKEY|ShiftMask,             XK_comma,                  tagmon,         {.i = -1 } },
        { MODKEY|ShiftMask,             XK_period,                 tagmon,         {.i = +1 } },
        { 0,                            XF86XK_AudioRaiseVolume,   spawn,          {.v = volumeup } },
        { 0,                            XF86XK_AudioLowerVolume,   spawn,          {.v = volumedown } },
        { 0,                            XF86XK_AudioMute,          spawn,          {.v = volumemute } },
        { 0,                            XF86XK_AudioMicMute,       spawn,          {.v = micmute } },
        { MODKEY|ShiftMask,             XK_p,                      spawn,          {.v = playerprev } },
        { MODKEY|ShiftMask,             XK_n,                      spawn,          {.v = playernext } },
        { MODKEY|Mod1Mask,              XK_h,                      incrgaps,       {.i = +1 } },
        { MODKEY|Mod1Mask,              XK_l,                      incrgaps,       {.i = -1 } },
        { MODKEY|Mod1Mask|ShiftMask,    XK_0,                      defaultgaps,    {0} },
        { MODKEY|Mod1Mask,              XK_0,                      togglegaps,     {0} },
        TAGKEYS(                        XK_1,                                      0)
        TAGKEYS(                        XK_2,                                      1)
        TAGKEYS(                        XK_3,                                      2)
        TAGKEYS(                        XK_4,                                      3)
        TAGKEYS(                        XK_5,                                      4)
        TAGKEYS(                        XK_6,                                      5)
        TAGKEYS(                        XK_7,                                      6)
        TAGKEYS(                        XK_8,                                      7)
        TAGKEYS(                        XK_9,                                      8)
        TAGKEYS(                        XK_0,                                      9)
        { MODKEY|ShiftMask,             XK_q,                      quit,           {0} },
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

static const char *const autostart[] = {
"xss-lock", "--transfer-sleep-lock", "--", "betterlockscreen", "--nofork", NULL,
"nm-applet", NULL,
"sh", "-c", "~/.screenlayout/default.sh", NULL,
"picom", "-b", NULL,
"feh", "--bg-scale", "~/.config/i3/wallpaper.png", NULL,
NULL
};

