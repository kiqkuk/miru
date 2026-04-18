/* Taken from https://github.com/djpohly/dwl/issues/466 */
#define COLOR(hex)    { ((hex >> 24) & 0xFF) / 255.0f, \
                        ((hex >> 16) & 0xFF) / 255.0f, \
                        ((hex >> 8) & 0xFF) / 255.0f, \
                        (hex & 0xFF) / 255.0f }
/* appearance */
static const int sloppyfocus               = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const int smartgaps                 = 0;  /* 1 means no outer gap when there is only one window */
static const int monoclegaps               = 0;  /* 1 means outer gaps in monocle layout */
static const unsigned int borderpx         = 1;  /* border pixel of windows */
static const unsigned int gappih           = 20; /* horiz inner gap between windows */
static const unsigned int gappiv           = 20; /* vert inner gap between windows */
static const unsigned int gappoh           = 20; /* horiz outer gap between windows and screen edge */
static const unsigned int gappov           = 20; /* vert outer gap between windows and screen edge */
/* catppuccin mocha */
static const float rootcolor[]             = COLOR(0x1e1e2eff);
static const float bordercolor[]           = COLOR(0x45475aff);
static const float focuscolor[]            = COLOR(0xb4befeff);
static const float urgentcolor[]           = COLOR(0xf38ba8ff);
/* This conforms to the xdg-protocol. Set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]         = COLOR(0x1e1e2eff); /* You can also use glsl colors */
static const int respect_monitor_reserved_area = 0; /* 1 to monitor center while respecting the monitor's reserved area, 0 to monitor center */

/* tagging - TAGCOUNT must be no greater than 31 */
#define TAGCOUNT (9)

/* logging */
static int log_level = WLR_ERROR;

/* x,y,w,h in pixels; do not exceed screen resolution */
static const Rule rules[] = {
	/* app_id             title       tags mask     isfloating   monitor   x      y      w       h */
	{ "foot",        "Clipboard",     0,            1,           -1,      460,   290,   1000,   490 },
  { "foot",        "Wi-Fi",         0,            1,           -1,      760,   440,   400,    200 },
  { "foot",        "Cheatsheet",    0,            1,           -1,      560,   40,    800,    1000 },
  { "foot",        "Music",         0,            1,           -1,      710,   419,   500,    242 },
  { "foot",        "Launch",        0,            1,           -1,      810,   365,   300,    350 },
    /* default/example rule: can be changed but cannot be eliminated; at least one rule must exist */
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* monitors */
/* (x=-1, y=-1) is reserved as an "autoconfigure" monitor position indicator
 * WARNING: negative values other than (-1, -1) cause problems with Xwayland clients due to
 * https://gitlab.freedesktop.org/xorg/xserver/-/issues/899 */
static const MonitorRule monrules[] = {
   /* name        mfact  nmaster scale layout       rotate/reflect                x    y
    * example of a HiDPI laptop monitor:
    { "eDP-1",    0.5f,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 }, */
	{ NULL,       0.55f, 1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
	/* default monitor rule: can be changed but cannot be eliminated; at least one monitor rule must exist */
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
	/* example:
	.options = "ctrl:nocaps",
	*/
	.options = NULL,
};

static const int repeat_rate = 25;
static const int repeat_delay = 600;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 0;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;
/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER
*/
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.0;

/* You can choose between:
LIBINPUT_CONFIG_TAP_MAP_LRM -- 1/2/3 finger tap maps to left/right/middle
LIBINPUT_CONFIG_TAP_MAP_LMR -- 1/2/3 finger tap maps to left/middle/right
*/
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

/* If you want to use the windows key for MODKEY, use WLR_MODIFIER_LOGO */
#define MODKEY WLR_MODIFIER_LOGO

#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, SKEY,           tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,SKEY,toggletag, {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[] = { "foot", NULL };
/* static const char *menucmd[] = { "wmenu-run", "-i", "-N", "1e1e2e", "-n", "cdd6f4", "-S", "b4befe", "-s", "1e1e2e", NULL }; */
/* vol-control is a script to handle wpctl and someblocks signals */
static const char *volup[]   = { "vol-control", "set-volume", "-l", "1.0", "@DEFAULT_AUDIO_SINK@", "5%+", NULL };
static const char *voldn[]   = { "vol-control", "set-volume", "@DEFAULT_AUDIO_SINK@", "5%-", NULL };
static const char *volmute[] = { "vol-control", "set-mute", "@DEFAULT_AUDIO_SINK@", "toggle", NULL };
static const char *screenshot[] = { "screenshot", NULL };
static const char *webcmd[] = { "qutebrowser", NULL };
static const char *wifitui[] = { "foot", "-T", "Wi-Fi", "tui-wifi", NULL };
static const char *helptui[] = { "foot", "-T", "Cheatsheet", "tui-cheatsheet", NULL };
static const char *cliptui[] = { "foot", "-T", "Clipboard", "tui-clipboard", NULL };
static const char *musictui[] = { "foot", "-T", "Music", "tui-music", NULL};
static const char *menutui[] = { "foot", "-T", "Launch", "tui-menu", NULL};

static const Key keys[] = {
	/* Note that Shift changes certain key codes: 2 -> at, etc. */
	/* modifier                  key                  function          argument */
	
  /*--- navigation ---*/
  { MODKEY,                    XKB_KEY_j,           focusstack,       {.i = +1} },
  { MODKEY,                    XKB_KEY_k,           focusstack,       {.i = -1} },
  { MODKEY,                    XKB_KEY_comma,       incnmaster,       {.i = +1} },
  { MODKEY,                    XKB_KEY_period,      incnmaster,       {.i = -1} },
  { MODKEY,                    XKB_KEY_h,           setmfact,         {.f = -0.05f} },
  { MODKEY,                    XKB_KEY_l,           setmfact,         {.f = +0.05f} },
  { MODKEY,                    XKB_KEY_Return,      zoom,             {0} },
  { MODKEY,                    XKB_KEY_q,           killclient,       {0} },
  { MODKEY,                    XKB_KEY_Tab,         view,             {0} },
  { MODKEY,                    XKB_KEY_t,           setlayout,        {.v = &layouts[0]} },
  { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_T,           setlayout,        {.v = &layouts[1]} },
  { MODKEY|WLR_MODIFIER_ALT,   XKB_KEY_t,           setlayout,        {.v = &layouts[2]} },
  { MODKEY,                    XKB_KEY_space,       setlayout,        {0} },
  { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_space,       togglefloating,   {0} },
  { MODKEY,                    XKB_KEY_f,           togglefullscreen, {0} },
  { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_q,           quit,             {0} },
  { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_question,    spawn,            {.v = helptui} },

  /*--- media keys ---*/
  { 0,			        XF86XK_AudioRaiseVolume,        spawn,	          {.v = volup} },
  { 0,			        XF86XK_AudioLowerVolume,        spawn,	          {.v = voldn} },
  { 0,			        XF86XK_AudioMute,	              spawn,	          {.v = volmute} },
  /* brightness control using acpi handler */
  
  /*--- apps ---*/
  { MODKEY,                    XKB_KEY_s,           spawn,            {.v = screenshot} },
  { MODKEY,                    XKB_KEY_v,           spawn,            {.v = cliptui} },
  { MODKEY,                    XKB_KEY_b,           spawn,            {.v = webcmd} },
  { MODKEY,                    XKB_KEY_c,           spawn,            {.v = wifitui} },
  { MODKEY,                    XKB_KEY_p,           spawn,            {.v = menutui} },
  { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Return,      spawn,            {.v = termcmd} },
  { MODKEY,                    XKB_KEY_m,           spawn,            {.v = musictui} },

  /*--- tag keys ---*/
  TAGKEYS(          XKB_KEY_1, XKB_KEY_exclam,                        0),
  TAGKEYS(          XKB_KEY_2, XKB_KEY_at,                            1),
  TAGKEYS(          XKB_KEY_3, XKB_KEY_numbersign,                    2),
  TAGKEYS(          XKB_KEY_4, XKB_KEY_dollar,                        3),
  TAGKEYS(          XKB_KEY_5, XKB_KEY_percent,                       4),
  TAGKEYS(          XKB_KEY_6, XKB_KEY_asciicircum,                   5),
  TAGKEYS(          XKB_KEY_7, XKB_KEY_ampersand,                     6),
  TAGKEYS(          XKB_KEY_8, XKB_KEY_asterisk,                      7),
  TAGKEYS(          XKB_KEY_9, XKB_KEY_parenleft,                     8),

  /*--- gaps control ---*/
  { MODKEY|WLR_MODIFIER_ALT,   XKB_KEY_h,           incgaps,   	      {.i = +1 } },
  { MODKEY|WLR_MODIFIER_ALT,   XKB_KEY_l,           incgaps,	        {.i = -1 } },
  { MODKEY|WLR_MODIFIER_ALT|WLR_MODIFIER_SHIFT,     XKB_KEY_H,        incogaps,      {.i = +1 } },
  { MODKEY|WLR_MODIFIER_ALT|WLR_MODIFIER_SHIFT,     XKB_KEY_L,        incogaps,      {.i = -1 } },
  { MODKEY|WLR_MODIFIER_ALT|WLR_MODIFIER_CTRL,      XKB_KEY_h,        incigaps,      {.i = +1 } },
  { MODKEY|WLR_MODIFIER_ALT|WLR_MODIFIER_CTRL,      XKB_KEY_l,        incigaps,      {.i = -1 } },
  { MODKEY|WLR_MODIFIER_ALT,   XKB_KEY_0,           togglegaps,       {0} },
  { MODKEY|WLR_MODIFIER_ALT|WLR_MODIFIER_SHIFT,     XKB_KEY_parenright,defaultgaps,    {0} },
  { MODKEY,                    XKB_KEY_y,           incihgaps,        {.i = +1 } },
  { MODKEY,                    XKB_KEY_o,           incihgaps,        {.i = -1 } },
  { MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_y,           incivgaps,        {.i = +1 } },
  { MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_o,           incivgaps,        {.i = -1 } },
  { MODKEY|WLR_MODIFIER_ALT,   XKB_KEY_y,           incohgaps,        {.i = +1 } },
  { MODKEY|WLR_MODIFIER_ALT,   XKB_KEY_o,           incohgaps,        {.i = -1 } },
  { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Y,           incovgaps,        {.i = +1 } },
  { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_O,           incovgaps,        {.i = -1 } },

	/*--- other tag options ---*/
  { MODKEY,                    XKB_KEY_0,           view,             {.ui = ~0} },
  { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_parenright,  tag,              {.ui = ~0} },

  /*--- multimon control ---*/
  { MODKEY|WLR_MODIFIER_ALT,   XKB_KEY_comma,       focusmon,         {.i = WLR_DIRECTION_LEFT} },
  { MODKEY|WLR_MODIFIER_ALT,   XKB_KEY_period,      focusmon,         {.i = WLR_DIRECTION_RIGHT} },
  { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_less,        tagmon,           {.i = WLR_DIRECTION_LEFT} },
  { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_greater,     tagmon,           {.i = WLR_DIRECTION_RIGHT} },

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_Terminate_Server, quit, {0} },
	/* Ctrl-Alt-Fx is used to switch to another VT, if you don't know what a VT is
	 * do not remove them.
	 */
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
};
