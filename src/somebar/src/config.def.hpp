// somebar - dwl bar
// See LICENSE file for copyright and license details.

#pragma once
#include "common.hpp"

constexpr bool topbar = true;

constexpr int paddingX = 10;
constexpr int paddingY = 3;

// See https://docs.gtk.org/Pango/type_func.FontDescription.from_string.html
constexpr const char* font = "Hack Nerd Font 12";

// Catppuccin Mocha
constexpr ColorScheme colorInactive = {Color(0xcb, 0xa6, 0xf7), Color(0x1e, 0x1e, 0x2e)};
constexpr ColorScheme colorActive = {Color(0xcb, 0xa6, 0xf7), Color(0x1e, 0x1e, 0x2e)};
constexpr ColorScheme colorTagSel = {Color(0x1e, 0x1e, 0x2e), Color(0xcb, 0xa6, 0xf7)};
 
constexpr const char* termcmd[] = {"foot", nullptr};

static std::vector<std::string> tagNames = {
	"1", "2", "3",
	"4", "5", "6",
	"7", "8", "9",
};

constexpr Button buttons[] = {
	{ ClkStatusText,   BTN_RIGHT,  spawn,      {.v = termcmd} },
};
