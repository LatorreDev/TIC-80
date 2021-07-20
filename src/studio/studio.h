// MIT License

// Copyright (c) 2017 Vadim Grigoruk @nesbox // grigoruk@gmail.com

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "tic.h"
#include "api.h"
#include "defines.h"
#include "tools.h"
#include "system.h"
#include "ext/png.h"

#define KEYBOARD_HOLD 20
#define KEYBOARD_PERIOD 3

#define TIC_LOCAL ".local/"
#define TIC_LOCAL_VERSION TIC_LOCAL TIC_VERSION_HASH "/"
#define TIC_CACHE TIC_LOCAL "cache/"

#define TOOLBAR_SIZE 7
#define STUDIO_TEXT_WIDTH (TIC_FONT_WIDTH)
#define STUDIO_TEXT_HEIGHT (TIC_FONT_HEIGHT+1)
#define STUDIO_TEXT_BUFFER_WIDTH (TIC80_WIDTH / STUDIO_TEXT_WIDTH)
#define STUDIO_TEXT_BUFFER_HEIGHT (TIC80_HEIGHT / STUDIO_TEXT_HEIGHT)
#define STUDIO_TEXT_BUFFER_SIZE (STUDIO_TEXT_BUFFER_WIDTH * STUDIO_TEXT_BUFFER_HEIGHT)

#define TIC_COLOR_BG tic_color_black

#define CONFIG_TIC "config.tic"
#define CONFIG_TIC_PATH TIC_LOCAL_VERSION CONFIG_TIC

#define KEYMAP_COUNT (sizeof(tic80_gamepads) * BITS_IN_BYTE)
#define KEYMAP_SIZE (KEYMAP_COUNT)
#define KEYMAP_DAT "keymap.dat"
#define KEYMAP_DAT_PATH TIC_LOCAL_VERSION KEYMAP_DAT

#define CART_EXT ".tic"
#define PNG_EXT ".png"

#if defined(CRT_SHADER_SUPPORT)
#   define CRT_CMD_PARAM(macro) \
    macro(crt, BOOLEAN, "", "enable CRT monitor effect")
#else
#   define CRT_CMD_PARAM(macro)
#endif

#define CMD_PARAMS_LIST(macro)                                                      \
    macro(skip,         BOOLEAN,    "",         "skip startup animation")           \
    macro(nosound,      BOOLEAN,    "",         "disable sound output")             \
    macro(cli,          BOOLEAN,    "",         "console only output")              \
    macro(fullscreen,   BOOLEAN,    "",         "enable fullscreen mode")           \
    macro(fs,           STRING,     "=<str>",   "path to the file system folder")   \
    macro(scale,        INTEGER,    "=<int>",   "main window scale")                \
    macro(cmd,          STRING,     "=<str>",   "run commands in the console")      \
    macro(version,      BOOLEAN,    "",         "print program version")            \
    CRT_CMD_PARAM(macro)

#define SHOW_TOOLTIP(FORMAT, ...)           \
do{                                         \
    static const char Format[] = FORMAT;    \
    static char buf[sizeof Format];         \
    sprintf(buf, Format, __VA_ARGS__);      \
    showTooltip(buf);                       \
}while(0)

typedef struct
{
    bool skip;
    bool nosound;
    bool cli;
    bool fullscreen;
    bool version;
    s32 scale;
    char *fs;
    char *cart;
#if defined(CRT_SHADER_SUPPORT)
    bool crt;
#endif
    char *cmd;
} StartArgs;

typedef enum
{
    TIC_START_MODE,
    TIC_CONSOLE_MODE,
    TIC_RUN_MODE,
    TIC_CODE_MODE,
    TIC_SPRITE_MODE,
    TIC_MAP_MODE,
    TIC_WORLD_MODE,
    TIC_SFX_MODE,
    TIC_MUSIC_MODE,
    TIC_DIALOG_MODE,
    TIC_MENU_MODE,
    TIC_SURF_MODE,
} EditorMode;

enum
{
    tic_icon_cut        = 80,
    tic_icon_copy       = 81,
    tic_icon_paste      = 82,
    tic_icon_undo       = 83,
    tic_icon_redo       = 84,
    tic_icon_bank       = 85,
    tic_icon_pin        = 86,
    tic_icon_tab        = 87,
    tic_icon_code       = 88,
    tic_icon_sprite     = 89,
    tic_icon_map        = 90,
    tic_icon_sfx        = 91,
    tic_icon_music      = 92,
    tic_icon_rec        = 93,
    tic_icon_rec2       = 94,
    tic_icon_bookmark   = 95,
    tic_icon_shadow     = 96,
    tic_icon_shadow2    = 97,
    tic_icon_run        = 98,
    tic_icon_hand       = 99,
    tic_icon_find       = 100,
    tic_icon_goto       = 101,
    tic_icon_outline    = 102,
    tic_icon_world      = 103,
    tic_icon_grid       = 104,
    tic_icon_down       = 105,
    tic_icon_up         = 106,
    tic_icon_fill       = 107,
    tic_icon_select     = 108,
    tic_icon_pen        = 109,
    tic_icon_tiles      = 110,
    tic_icon_sprites    = 111,
    tic_icon_left       = 112,
    tic_icon_right      = 113,
    tic_icon_piano      = 114,
    tic_icon_tracker    = 115,
    tic_icon_follow     = 116,
    tic_icon_sustain    = 117,
    tic_icon_playnow    = 118,
    tic_icon_playframe  = 119,
    tic_icon_stop       = 120,
    tic_icon_rgb        = 121,
    tic_icon_tinyleft   = 122,
    tic_icon_pos        = 123,
    tic_icon_tinyright  = 124,
    tic_icon_bigup      = 125,
    tic_icon_bigdown    = 126,
    tic_icon_bigleft    = 127,
    tic_icon_bigright   = 128,
    tic_icon_fliphorz   = 129,
    tic_icon_flipvert   = 130,
    tic_icon_rotate     = 131,
    tic_icon_erase      = 132,
    tic_icon_bigpen     = 133,
    tic_icon_bigpicker  = 134,
    tic_icon_bigselect  = 135,
    tic_icon_bigfill    = 136,
};

void setCursor(tic_cursor id);

bool checkMousePos(const tic_rect* rect);
bool checkMouseClick(const tic_rect* rect, tic_mouse_btn button);
bool checkMouseDown(const tic_rect* rect, tic_mouse_btn button);

void drawToolbar(tic_mem* tic, bool bg);
void drawBitIcon(s32 id, s32 x, s32 y, u8 color);

tic_cartridge* loadPngCart(png_buffer buffer);
void studioRomLoaded();
void studioRomSaved();
void studioConfigChanged();

void setStudioMode(EditorMode mode);
void resumeRunMode();
EditorMode getStudioMode();
void exitStudio();

void toClipboard(const void* data, s32 size, bool flip);
bool fromClipboard(void* data, s32 size, bool flip, bool remove_white_spaces);

typedef enum
{
    TIC_CLIPBOARD_NONE,
    TIC_CLIPBOARD_CUT,
    TIC_CLIPBOARD_COPY,
    TIC_CLIPBOARD_PASTE,
} ClipboardEvent;

ClipboardEvent getClipboardEvent();

typedef enum
{
    TIC_TOOLBAR_CUT,
    TIC_TOOLBAR_COPY,
    TIC_TOOLBAR_PASTE,
    TIC_TOOLBAR_UNDO,
    TIC_TOOLBAR_REDO,
} StudioEvent;

void setStudioEvent(StudioEvent event);
void showTooltip(const char* text);

tic_key* getKeymap();

void setSpritePixel(tic_tile* tiles, s32 x, s32 y, u8 color);
u8 getSpritePixel(tic_tile* tiles, s32 x, s32 y);

typedef void(*DialogCallback)(bool yes, void* data);
void showDialog(const char** text, s32 rows, DialogCallback callback, void* data);
void hideDialog();


bool studioCartChanged();
void playSystemSfx(s32 id);

void runGameFromSurf();
void gotoCode();
void gotoSurf();

void showGameMenu();
void hideGameMenu();
void exitGameMenu();

void runProject();
void drawBGAnimation(tic_mem* tic, s32 ticks);
void drawBGAnimationScanline(tic_mem* tic, s32 row);

tic_tiles* getBankTiles();
tic_palette* getBankPalette(bool ovr);
tic_flags* getBankFlags();
tic_map* getBankMap();

char getKeyboardText();
bool keyWasPressed(tic_key key);
bool anyKeyWasPressed();

const StudioConfig* getConfig();
struct Start* getStartScreen();
struct Sprite* getSpriteEditor();

const char* md5str(const void* data, s32 length);
void sfx_stop(tic_mem* tic, s32 channel);
const char* studioExportMusic(s32 track, const char* filename);
const char* studioExportSfx(s32 sfx, const char* filename);
s32 calcWaveAnimation(tic_mem* tic, u32 index, s32 channel);
void map2ram(tic_ram* ram, const tic_map* src);
void tiles2ram(tic_ram* ram, const tic_tiles* src);

#if defined(CRT_SHADER_SUPPORT)
void switchCrtMonitor();
#endif

void fadePalette(tic_palette* pal, s32 value);