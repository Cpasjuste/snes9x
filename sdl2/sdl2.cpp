/***********************************************************************************
  Snes9x - Portable Super Nintendo Entertainment System (TM) emulator.

  (c) Copyright 1996 - 2002  Gary Henderson (gary.henderson@ntlworld.com),
                             Jerremy Koot (jkoot@snes9x.com)

  (c) Copyright 2002 - 2004  Matthew Kendora

  (c) Copyright 2002 - 2005  Peter Bortas (peter@bortas.org)

  (c) Copyright 2004 - 2005  Joel Yliluoma (http://iki.fi/bisqwit/)

  (c) Copyright 2001 - 2006  John Weidman (jweidman@slip.net)

  (c) Copyright 2002 - 2006  funkyass (funkyass@spam.shaw.ca),
                             Kris Bleakley (codeviolation@hotmail.com)

  (c) Copyright 2002 - 2010  Brad Jorsch (anomie@users.sourceforge.net),
                             Nach (n-a-c-h@users.sourceforge.net),

  (c) Copyright 2002 - 2011  zones (kasumitokoduck@yahoo.com)

  (c) Copyright 2006 - 2007  nitsuja

  (c) Copyright 2009 - 2011  BearOso,
                             OV2


  BS-X C emulator code
  (c) Copyright 2005 - 2006  Dreamer Nom,
                             zones

  C4 x86 assembler and some C emulation code
  (c) Copyright 2000 - 2003  _Demo_ (_demo_@zsnes.com),
                             Nach,
                             zsKnight (zsknight@zsnes.com)

  C4 C++ code
  (c) Copyright 2003 - 2006  Brad Jorsch,
                             Nach

  DSP-1 emulator code
  (c) Copyright 1998 - 2006  _Demo_,
                             Andreas Naive (andreasnaive@gmail.com),
                             Gary Henderson,
                             Ivar (ivar@snes9x.com),
                             John Weidman,
                             Kris Bleakley,
                             Matthew Kendora,
                             Nach,
                             neviksti (neviksti@hotmail.com)

  DSP-2 emulator code
  (c) Copyright 2003         John Weidman,
                             Kris Bleakley,
                             Lord Nightmare (lord_nightmare@users.sourceforge.net),
                             Matthew Kendora,
                             neviksti

  DSP-3 emulator code
  (c) Copyright 2003 - 2006  John Weidman,
                             Kris Bleakley,
                             Lancer,
                             z80 gaiden

  DSP-4 emulator code
  (c) Copyright 2004 - 2006  Dreamer Nom,
                             John Weidman,
                             Kris Bleakley,
                             Nach,
                             z80 gaiden

  OBC1 emulator code
  (c) Copyright 2001 - 2004  zsKnight,
                             pagefault (pagefault@zsnes.com),
                             Kris Bleakley
                             Ported from x86 assembler to C by sanmaiwashi

  SPC7110 and RTC C++ emulator code used in 1.39-1.51
  (c) Copyright 2002         Matthew Kendora with research by
                             zsKnight,
                             John Weidman,
                             Dark Force

  SPC7110 and RTC C++ emulator code used in 1.52+
  (c) Copyright 2009         byuu,
                             neviksti

  S-DD1 C emulator code
  (c) Copyright 2003         Brad Jorsch with research by
                             Andreas Naive,
                             John Weidman

  S-RTC C emulator code
  (c) Copyright 2001 - 2006  byuu,
                             John Weidman

  ST010 C++ emulator code
  (c) Copyright 2003         Feather,
                             John Weidman,
                             Kris Bleakley,
                             Matthew Kendora

  Super FX x86 assembler emulator code
  (c) Copyright 1998 - 2003  _Demo_,
                             pagefault,
                             zsKnight

  Super FX C emulator code
  (c) Copyright 1997 - 1999  Ivar,
                             Gary Henderson,
                             John Weidman

  Sound emulator code used in 1.5-1.51
  (c) Copyright 1998 - 2003  Brad Martin
  (c) Copyright 1998 - 2006  Charles Bilyue'

  Sound emulator code used in 1.52+
  (c) Copyright 2004 - 2007  Shay Green (gblargg@gmail.com)

  SH assembler code partly based on x86 assembler code
  (c) Copyright 2002 - 2004  Marcus Comstedt (marcus@mc.pp.se)

  2xSaI filter
  (c) Copyright 1999 - 2001  Derek Liauw Kie Fa

  HQ2x, HQ3x, HQ4x filters
  (c) Copyright 2003         Maxim Stepin (maxim@hiend3d.com)

  NTSC filter
  (c) Copyright 2006 - 2007  Shay Green

  GTK+ GUI code
  (c) Copyright 2004 - 2011  BearOso

  Win32 GUI code
  (c) Copyright 2003 - 2006  blip,
                             funkyass,
                             Matthew Kendora,
                             Nach,
                             nitsuja
  (c) Copyright 2009 - 2011  OV2

  Mac OS GUI code
  (c) Copyright 1998 - 2001  John Stiles
  (c) Copyright 2001 - 2011  zones


  Specific ports contains the works of other authors. See headers in
  individual files.


  Snes9x homepage: http://www.snes9x.com/

  Permission to use, copy, modify and/or distribute Snes9x in both binary
  and source form, for non-commercial purposes, is hereby granted without
  fee, providing that this license information and copyright notice appear
  with all copies and any derived work.

  This software is provided 'as-is', without any express or implied
  warranty. In no event shall the authors be held liable for any damages
  arising from the use of this software or it's derivatives.

  Snes9x is freeware for PERSONAL USE only. Commercial users should
  seek permission of the copyright holders first. Commercial use includes,
  but is not limited to, charging money for Snes9x or software derived from
  Snes9x, including Snes9x or derivatives in commercial game bundles, and/or
  using Snes9x as a promotion for your commercial product.

  The copyright holders request that bug fixes and improvements to the code
  should be forwarded to them so everyone can benefit from the modifications
  in future versions.

  Super NES and Super Nintendo Entertainment System are trademarks of
  Nintendo Co., Limited and its subsidiary companies.
 ***********************************************************************************/

#include <cstdlib>
#include <unistd.h>
#include <cctype>
#include <fcntl.h>
#include <dirent.h>
#include <csignal>
#include <cerrno>
#include <cstring>

#ifdef HAVE_STRINGS_H

#include <strings.h>

#endif

#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>

#ifdef HAVE_SYS_IOCTL_H

#include <sys/ioctl.h>

#endif

#include <chrono>
#include <thread>


#include <SDL2/SDL.h>

#include "port.h"
#include "blit.h"
#include "snes9x.h"
#include "memmap.h"
#include "apu/apu.h"
#include "gfx.h"
#include "snapshot.h"
#include "controls.h"
#include "cheats.h"
#include "movie.h"
#include "logger.h"
#include "display.h"
#include "conffile.h"

static SDL_Window *window = nullptr;

static SDL_Renderer *renderer = nullptr;

static SDL_Texture *texture = nullptr;

static uint16 *texture_pixels = nullptr;

static uint16 *snes_pixels = nullptr;

void exit_handler();

bool S9x_SDL2_ProcessEvents();

void S9x_SDL2_AudioCallback(void *userdata, Uint8 *stream, int len);

void exit_handler() {

    Settings.StopEmulation = TRUE;

    Memory.SaveSRAM(S9xGetFilename(".srm", SRAM_DIR));
    S9xResetSaveTimer(FALSE);

    S9xBlitFilterDeinit();
    S9xBlit2xSaIFilterDeinit();
    S9xBlitHQ2xFilterDeinit();

    S9xUnmapAllControls();
    Memory.Deinit();
    S9xDeinitAPU();
    S9xGraphicsDeinit();

    if (snes_pixels != nullptr) {
        delete[] snes_pixels;
        snes_pixels = nullptr;
    }

    if (texture_pixels != nullptr) {
        delete[] texture_pixels;
        texture_pixels = nullptr;
    }

    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window != nullptr) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
}

int main(int argc, char **argv) {
    if (argc < 2) {
        //S9xUsage();
    }

    printf("Snes9x " VERSION " using SDL2\n");

    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
        S9xExit();
    }
    atexit(exit_handler);

    memset(&Settings, 0, sizeof(Settings));
    Settings.MouseMaster = FALSE;
    Settings.SuperScopeMaster = FALSE;
    Settings.JustifierMaster = FALSE;
    Settings.MultiPlayer5Master = FALSE;
    Settings.FrameTimePAL = 20000;
    Settings.FrameTimeNTSC = 16667;
    Settings.SixteenBitSound = TRUE;
    Settings.Stereo = TRUE;
    Settings.SoundPlaybackRate = 32000;
    Settings.SoundInputRate = 32000;
    Settings.SupportHiRes = TRUE;
    Settings.SoundSync = TRUE;
    Settings.Transparency = TRUE;
    Settings.AutoDisplayMessages = TRUE;
    Settings.InitialInfoStringTimeout = 120;
    Settings.HDMATimingHack = 100;
    Settings.BlockInvalidVRAMAccessMaster = TRUE;
    Settings.StopEmulation = TRUE;
    Settings.WrongMovieStateProtection = TRUE;
    Settings.DumpStreamsMaxFrames = -1;
    Settings.StretchScreenshots = 1;
    Settings.SnapshotScreenshots = TRUE;
    Settings.SkipFrames = AUTO_FRAMERATE;
    Settings.TurboSkipFrames = 15;
    Settings.CartAName[0] = 0;
    Settings.CartBName[0] = 0;

    CPU.Flags = 0;

    //S9xLoadConfigFiles(argv, argc);
    /*
    char *rom_filename = S9xParseArgs(argv, argc);
    if (rom_filename == nullptr) {
        S9xUsage();
    }
    */

    const char *rom_filename = "zelda.zip";
    //const char *rom_filename = "mario.zip";

    if (!Memory.Init()) {
        fprintf(stderr, "Could not initialize Snes9x Memory.\n");
        exit(1);
    }

    if (!S9xInitAPU()) {
        fprintf(stderr, "Could not initialize Snes9x APU.\n");
        exit(1);
    }

    if (!S9xInitSound(100, 0)) {
        fprintf(stderr, "Could not initialize Snes9x Sound.\n");
        exit(1);
    }

    S9xUnmapAllControls();

    S9xSetController(0, CTL_JOYPAD, 0, 0, 0, 0);
    S9xMapButton(0, S9xGetCommandT("Joypad1 Up"), false);
    S9xMapButton(1, S9xGetCommandT("Joypad1 Down"), false);
    S9xMapButton(2, S9xGetCommandT("Joypad1 Left"), false);
    S9xMapButton(3, S9xGetCommandT("Joypad1 Right"), false);
    S9xMapButton(4, S9xGetCommandT("Joypad1 A"), false);
    S9xMapButton(5, S9xGetCommandT("Joypad1 B"), false);
    S9xMapButton(6, S9xGetCommandT("Joypad1 X"), false);
    S9xMapButton(7, S9xGetCommandT("Joypad1 Y"), false);
    S9xMapButton(8, S9xGetCommandT("Joypad1 L"), false);
    S9xMapButton(9, S9xGetCommandT("Joypad1 R"), false);
    S9xMapButton(10, S9xGetCommandT("Joypad1 Start"), false);
    S9xMapButton(11, S9xGetCommandT("Joypad1 Select"), false);

    S9xReportControllers();

    uint32 saved_flags = CPU.Flags;

#ifdef GFX_MULTI_FORMAT
    S9xSetRenderPixelFormat(RGB565);
#endif

    if (!Memory.LoadROM(rom_filename)) {
        fprintf(stderr, "Could not open ROM: %s\n", rom_filename);
        exit(1);
    }

    //Memory.LoadSRAM(S9xGetFilename(".srm", SRAM_DIR));
    //S9xLoadCheatFile(S9xGetFilename(".cht", CHEAT_DIR));

    CPU.Flags = saved_flags;
    Settings.StopEmulation = FALSE;

    // Initialize filters
    S9xBlitFilterInit();
    S9xBlit2xSaIFilterInit();
    S9xBlitHQ2xFilterInit();

    // Create window
    window = SDL_CreateWindow("Snes9x-SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              IMAGE_WIDTH, IMAGE_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
        S9xExit();
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == nullptr) {
        fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
        S9xExit();
    }

    // Create texture
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB565, SDL_TEXTUREACCESS_STATIC, IMAGE_WIDTH, IMAGE_HEIGHT);
    if (texture == nullptr) {
        fprintf(stderr, "Could not create texture: %s\n", SDL_GetError());
        S9xExit();
    }

    // Allocate texture pixel buffer
    texture_pixels = new(std::nothrow) uint16[IMAGE_WIDTH * IMAGE_HEIGHT];
    if (texture_pixels == nullptr) {
        fprintf(stderr, "Could not allocate pixel buffer.\n");
        S9xExit();
    }

    // Allocate snes pixel buffer
    snes_pixels = new(std::nothrow) uint16[IMAGE_WIDTH * IMAGE_HEIGHT];
    if (snes_pixels == nullptr) {
        fprintf(stderr, "Could not allocate pixel buffer.\n");
        S9xExit();
    }

    // Set up Snes9x GFX
    GFX.Pitch = IMAGE_WIDTH * 2;
    GFX.Screen = snes_pixels;

    S9xGraphicsInit();

    sprintf(String, "\"%s\" on %s %s using SDL2", Memory.ROMName, TITLE, VERSION);
    SDL_SetWindowTitle(window, String);

    S9xSetSoundMute(FALSE);

    // Main loop
    bool quit = false;
    while (!quit) {
        if (!Settings.Paused) {
            S9xMainLoop();
            S9xSetSoundMute(FALSE);
        } else {
            S9xSetSoundMute(TRUE);
        }

        quit = S9x_SDL2_ProcessEvents();
    }

    return 0;
}

/**
 * Handle SDL events. Return true if we should quit.
 */
bool S9x_SDL2_ProcessEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return true;
        }
    }

    const Uint8 *currentKeyStates = SDL_GetKeyboardState(nullptr);

    S9xReportButton(0, currentKeyStates[SDL_SCANCODE_UP] == 1);
    S9xReportButton(1, currentKeyStates[SDL_SCANCODE_DOWN] == 1);
    S9xReportButton(2, currentKeyStates[SDL_SCANCODE_LEFT] == 1);
    S9xReportButton(3, currentKeyStates[SDL_SCANCODE_RIGHT] == 1);
    S9xReportButton(4, currentKeyStates[SDL_SCANCODE_C] == 1);
    S9xReportButton(5, currentKeyStates[SDL_SCANCODE_B] == 1);
    S9xReportButton(6, currentKeyStates[SDL_SCANCODE_N] == 1);
    S9xReportButton(7, currentKeyStates[SDL_SCANCODE_V] == 1);
    S9xReportButton(8, currentKeyStates[SDL_SCANCODE_Z] == 1);
    S9xReportButton(9, currentKeyStates[SDL_SCANCODE_X] == 1);
    S9xReportButton(10, currentKeyStates[SDL_SCANCODE_S] == 1);
    S9xReportButton(11, currentKeyStates[SDL_SCANCODE_A] == 1);

    return false;
}

void S9x_SDL2_AudioCallback(void *userdata, Uint8 *stream, int len) {

    SDL_LockAudio();
    S9xMixSamples(stream, len >> (Settings.SixteenBitSound ? 1 : 0));
    SDL_UnlockAudio();
}

static void S9x_SDL2_SamplesAvailable(void *data) {

    SDL_LockAudio();
    S9xFinalizeSamples();
    SDL_UnlockAudio();
}

///////////////////////////////////////////////////////////////////////////////
// Functions called by Snes9x below
///////////////////////////////////////////////////////////////////////////////

void _splitpath(const char *path, char *drive, char *dir, char *fname, char *ext) {
    *drive = 0;

    const char *slash = strrchr(path, SLASH_CHAR);
    const char *dot = strrchr(path, '.');

    if (dot && slash && dot < slash) {
        dot = nullptr;
    }

    if (!slash) {
        *dir = 0;

        strcpy(fname, path);

        if (dot) {
            fname[dot - path] = 0;
            strcpy(ext, dot + 1);
        } else {
            *ext = 0;
        }
    } else {
        strcpy(dir, path);
        dir[slash - path] = 0;

        strcpy(fname, slash + 1);

        if (dot) {
            fname[dot - slash - 1] = 0;
            strcpy(ext, dot + 1);
        } else {
            *ext = 0;
        }
    }
}

void _makepath(char *path, const char *, const char *dir, const char *fname, const char *ext) {
    if (dir && *dir) {
        strcpy(path, dir);
        strcat(path, SLASH_STR);
    } else {
        *path = 0;
    }

    strcat(path, fname);

    if (ext && *ext) {
        strcat(path, ".");
        strcat(path, ext);
    }
}

/**
 * Display port-specific usage information
 */
void S9xExtraUsage() {
}

/**
 * Parse port-specific arguments
 */
void S9xParseArg(char **argv, int &i, int argc) {
}

/**
 * Parse port-specific config
 */
void S9xParsePortConfig(ConfigFile &conf, int pass) {
}

/**
 * Called when Snes9x wants to know the directory dirtype.
 */
const char *S9xGetDirectory(s9x_getdirtype dirtype) {
    static const char *s = ".";
    return s;
}

/**
 * When Snes9x needs to know the name of the cheat/IPS file and so on, this function is called.
 * Check extension and dirtype, and return the appropriate filename.
 * The current ports return the ROM file path with the given extension.
 */
const char *S9xGetFilename(const char *ex, s9x_getdirtype dirtype) {
    static char s[PATH_MAX + 1];

    char drive[_MAX_DRIVE + 1];
    char dir[_MAX_DIR + 1];
    char fname[_MAX_FNAME + 1];
    char ext[_MAX_EXT + 1];

    _splitpath(Memory.ROMFilename, drive, dir, fname, ext);
    snprintf(s, PATH_MAX + 1, "%s%s%s%s", S9xGetDirectory(dirtype), SLASH_STR, fname, ex);

    return s;
}

/**
 * Almost the same as S9xGetFilename function, but used for saving SPC files etc.
 * So you have to take care not to delete the previously saved file, by increasing
 * the number of the filename; romname.000.spc, romname.001.spc, ...
 */
const char *S9xGetFilenameInc(const char *ex, s9x_getdirtype dirtype) {
    static char s[PATH_MAX + 1];

    char drive[_MAX_DRIVE + 1];
    char dir[_MAX_DIR + 1];
    char fname[_MAX_FNAME + 1];
    char ext[_MAX_EXT + 1];

    unsigned int i = 0;
    const char *d;
    struct stat buf;

    _splitpath(Memory.ROMFilename, drive, dir, fname, ext);
    d = S9xGetDirectory(dirtype);

    do
        snprintf(s, PATH_MAX + 1, "%s%s%s.%03d%s", d, SLASH_STR, fname, i++, ex);
    while (stat(s, &buf) == 0 && i < 1000);

    return s;
}

/**
 * Called when Snes9x wants to know the name of the ROM image.
 * Typically, extract the filename from path and return it.
 */
const char *S9xBasename(const char *f) {
    const char *p;

    if ((p = strrchr(f, '/')) != nullptr || (p = strrchr(f, '\\')) != nullptr)
        return p + 1;

    return f;
}

/**
 * If your port can match Snes9x's built-in LoadFreezeFile/SaveFreezeFile command
 * (see controls.cpp), you may choose to use this function. Otherwise return NULL.
 */
const char *S9xChooseFilename(bool8 read_only) {
    return nullptr;
}

/**
 * If your port can match Snes9x's built-in BeginRecordingMovie/LoadMovie command
 * (see controls.cpp), you may choose to use this function. Otherwise return NULL.
 */
const char *S9xChooseMovieFilename(bool8 read_only) {
    return nullptr;
}

/**
 * This function opens a freeze-game file. STREAM is defined as a gzFile if ZLIB is
 * defined else it's defined as FILE *. The read_only parameter is set to true when
 * reading a freeze-game file and false when writing a freeze-game file.
 * Open the file filepath and return its pointer file.
 */
bool8 S9xOpenSnapshotFile(const char *filename, bool8 read_only, STREAM*file) {
    return FALSE;
}

/**
 * This function closes the freeze-game file opened by S9xOpenSnapshotFile function.
 */
void S9xCloseSnapshotFile(STREAM file) {
}

/**
 * Called just before Snes9x begins to render an SNES screen.
 * Use this function if you should prepare before drawing, otherwise let it empty.
 */
bool8 S9xInitUpdate() {
    return TRUE;
}

/**
 * Called at the end of screen refresh if GFX.DoInterlace && GFX.InterlaceFrame == 0 is true (?).
 */
bool8 S9xContinueUpdate(int width, int height) {
    return TRUE;
}

/**
 * Called once a complete SNES screen has been rendered into the GFX.Screen memory buffer,
 * now is your chance to copy the SNES rendered screen to the host computer's screen memory.
 * The problem is that you have to cope with different sized SNES rendered screens:
 * 256*224, 256*239, 512*224, 512*239, 512*448 and 512*478.
 */
bool8 S9xDeinitUpdate(int width, int height) {

    static int prevWidth = 0;
    static int prevHeight = 0;

    if ((width <= SNES_WIDTH) && ((prevWidth != width) || (prevHeight != height))) {
        S9xBlitClearDelta();
    }

    if (width <= SNES_WIDTH && height > SNES_HEIGHT_EXTENDED) {
        S9xBlitPixSimple2x1((uint8 *) GFX.Screen, GFX.Pitch, (uint8 *) texture_pixels, GFX.Pitch, width, height);
    } else if (width <= SNES_WIDTH) {
        S9xBlitPixSimple2x2((uint8 *) GFX.Screen, GFX.Pitch, (uint8 *) texture_pixels, GFX.Pitch, width, height);
    } else if (height <= SNES_HEIGHT_EXTENDED) {
        S9xBlitPixSimple1x2((uint8 *) GFX.Screen, GFX.Pitch, (uint8 *) texture_pixels, GFX.Pitch, width, height);
    } else {
        S9xBlitPixSimple1x1((uint8 *) GFX.Screen, GFX.Pitch, (uint8 *) texture_pixels, GFX.Pitch, width, height);
    }

    if (height < prevHeight) {
        int p = SNES_WIDTH >> 2;
        for (int y = SNES_HEIGHT * 2; y < SNES_HEIGHT_EXTENDED * 2; y++) {
            uint32 *d = (uint32 *) (texture_pixels + y * GFX.Pitch);
            for (int x = 0; x < p; x++) {
                *d++ = 0;
            }
        }
    }

    SDL_UpdateTexture(texture, nullptr, texture_pixels, GFX.Pitch);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);

    prevWidth = width;
    prevHeight = height;

    return TRUE;
}

/**
 * If your port can match Snes9x's built-in SoundChannelXXX command (see controls.cpp),
 * you may choose to use this function. Otherwise return NULL.
 * Basically, turn on/off the sound channel c (0-7), and turn on all channels if c is 8.
 */
void S9xToggleSoundChannel(int c) {

    static uint8 sound_switch = 255;

    if (c == 8)
        sound_switch = 255;
    else
        sound_switch ^= 1 << c;

    S9xSetSoundControl(sound_switch);
}

/**
 * If Settings.AutoSaveDelay is not zero, Snes9x calls this function when the contents of
 * the S-RAM has been changed. Typically, call Memory.SaveSRAM function from this function.
 */
void S9xAutoSaveSRAM() {
    Memory.SaveSRAM(S9xGetFilename(".srm", SRAM_DIR));
}

/**
 * Called at the end of S9xMainLoop function, when emulating one frame has been done.
 * You should adjust the frame rate in this function
 */
void S9xSyncSpeed() {

    /*
    // Sync sound
    if (Settings.SoundSync) {
        while (!S9xSyncSound()) {
            std::this_thread::sleep_for(std::chrono::microseconds(1));
        }
    }

    // Initalize nextFrame as now + 1 microsecond
    static auto nextFrameTime = std::chrono::high_resolution_clock::now() + std::chrono::microseconds(1);

    // Get current time
    auto now = std::chrono::high_resolution_clock::now();

    unsigned limit = (Settings.SkipFrames == AUTO_FRAMERATE) ? (nextFrameTime < now ? 10 : 1) : Settings.SkipFrames;
    IPPU.RenderThisFrame = ++IPPU.SkippedFrames >= limit;
    if (IPPU.RenderThisFrame) {
        IPPU.SkippedFrames = 0;
    } else if (nextFrameTime < now) {
        auto lag = now - nextFrameTime;
        if (lag >= std::chrono::microseconds(500000)) {
            nextFrameTime = now;
        }
    }

    while (nextFrameTime > now) {
        auto timeLeft = nextFrameTime - now;
        std::this_thread::sleep_for(timeLeft);
        now = std::chrono::high_resolution_clock::now();
    }

    nextFrameTime = now + std::chrono::microseconds(Settings.FrameTime);
    */
#ifndef NOSOUND
    if (Settings.SoundSync) {
        while (!S9xSyncSound())
            usleep(0);
    }
#endif

    if (Settings.DumpStreams)
        return;

#ifdef NETPLAY_SUPPORT
    if (Settings.NetPlay && NetPlay.Connected)
    {
#if defined(NP_DEBUG) && NP_DEBUG == 2
        printf("CLIENT: SyncSpeed @%d\n", S9xGetMilliTime());
#endif

        S9xNPSendJoypadUpdate(old_joypads[0]);
        for (int J = 0; J < 8; J++)
            joypads[J] = S9xNPGetJoypad(J);

        if (!S9xNPCheckForHeartBeat())
        {
            NetPlay.PendingWait4Sync = !S9xNPWaitForHeartBeatDelay(100);
#if defined(NP_DEBUG) && NP_DEBUG == 2
            if (NetPlay.PendingWait4Sync)
                printf("CLIENT: PendingWait4Sync1 @%d\n", S9xGetMilliTime());
#endif

            IPPU.RenderThisFrame = TRUE;
            IPPU.SkippedFrames = 0;
        }
        else
        {
            NetPlay.PendingWait4Sync = !S9xNPWaitForHeartBeatDelay(200);
#if defined(NP_DEBUG) && NP_DEBUG == 2
            if (NetPlay.PendingWait4Sync)
                printf("CLIENT: PendingWait4Sync2 @%d\n", S9xGetMilliTime());
#endif

            if (IPPU.SkippedFrames < NetPlay.MaxFrameSkip)
            {
                IPPU.RenderThisFrame = FALSE;
                IPPU.SkippedFrames++;
            }
            else
            {
                IPPU.RenderThisFrame = TRUE;
                IPPU.SkippedFrames = 0;
            }
        }

        if (!NetPlay.PendingWait4Sync)
        {
            NetPlay.FrameCount++;
            S9xNPStepJoypadHistory();
        }

        return;
    }
#endif

    if (Settings.HighSpeedSeek > 0)
        Settings.HighSpeedSeek--;

    if (Settings.TurboMode) {
        if ((++IPPU.FrameSkip >= Settings.TurboSkipFrames) && !Settings.HighSpeedSeek) {
            IPPU.FrameSkip = 0;
            IPPU.SkippedFrames = 0;
            IPPU.RenderThisFrame = TRUE;
        } else {
            IPPU.SkippedFrames++;
            IPPU.RenderThisFrame = FALSE;
        }

        return;
    }

    static struct timeval next1 = {0, 0};
    struct timeval now;

    while (gettimeofday(&now, NULL) == -1);

    // If there is no known "next" frame, initialize it now.
    if (next1.tv_sec == 0) {
        next1 = now;
        next1.tv_usec++;
    }

    // If we're on AUTO_FRAMERATE, we'll display frames always only if there's excess time.
    // Otherwise we'll display the defined amount of frames.
    unsigned limit = (Settings.SkipFrames == AUTO_FRAMERATE) ? (timercmp(&next1, &now, <) ? 10 : 1)
                                                             : Settings.SkipFrames;

    IPPU.RenderThisFrame = (++IPPU.SkippedFrames >= limit) ? TRUE : FALSE;

    if (IPPU.RenderThisFrame)
        IPPU.SkippedFrames = 0;
    else {
        // If we were behind the schedule, check how much it is.
        if (timercmp(&next1, &now, <)) {
            unsigned lag = (now.tv_sec - next1.tv_sec) * 1000000 + now.tv_usec - next1.tv_usec;
            if (lag >= 500000) {
                // More than a half-second behind means probably pause.
                // The next line prevents the magic fast-forward effect.
                next1 = now;
            }
        }
    }

    // Delay until we're completed this frame.
    // Can't use setitimer because the sound code already could be using it. We don't actually need it either.
    while (timercmp(&next1, &now, >)) {
        // If we're ahead of time, sleep a while.
        unsigned timeleft = (next1.tv_sec - now.tv_sec) * 1000000 + next1.tv_usec - now.tv_usec;
        usleep(timeleft);

        while (gettimeofday(&now, NULL) == -1);
        // Continue with a while-loop because usleep() could be interrupted by a signal.
    }

    // Calculate the timestamp of the next frame.
    next1.tv_usec += Settings.FrameTime;
    if (next1.tv_usec >= 1000000) {
        next1.tv_sec += next1.tv_usec / 1000000;
        next1.tv_usec %= 1000000;
    }
}

/**
 * Called by Snes9x to poll for buttons that should be polled.
 */
bool S9xPollButton(uint32 id, bool *pressed) {
    return false;
}

/**
 * Called by Snes9x to poll for axises that should be polled.
 */
bool S9xPollAxis(uint32 id, int16 *value) {
    return false;
}

/**
 * Called by Snes9x to poll for poiters that should be polled.
 */
bool S9xPollPointer(uint32 id, int16 *x, int16 *y) {
    return false;
}

/**
 * Handle port-specific commands (?).
 */
void S9xHandlePortCommand(s9xcommand_t cmd, int16 data1, int16 data2) {
}

/**
 * S9xInitSound function calls this function to actually open the host sound device.
 */
bool8 S9xOpenSoundDevice(void) {

#ifdef NOSOUND
    return TRUE;
#else

    SDL_AudioSpec *audiospec = (SDL_AudioSpec *) malloc(sizeof(SDL_AudioSpec));

    audiospec->freq = Settings.SoundPlaybackRate;
    audiospec->channels = Settings.Stereo ? 2 : 1;
    audiospec->format = Settings.SixteenBitSound ? AUDIO_S16SYS : AUDIO_U8;
    audiospec->samples = (100 * audiospec->freq / 1000) >> 1;
    audiospec->callback = S9x_SDL2_AudioCallback;

    printf("SDL sound driver initializing...\n");
    printf("    --> (Frequency: %dhz, Latency: %dms)...",
           audiospec->freq,
           (audiospec->samples * 1000 / audiospec->freq) << 1);

    if (SDL_OpenAudio(audiospec, NULL) < 0) {
        printf("Failed\n");
        free(audiospec);
        return FALSE;
    }
    printf("OK\n");

    SDL_PauseAudio(0);

    S9xSetSamplesAvailableCallback(S9x_SDL2_SamplesAvailable, NULL);

    return TRUE;

#endif
}

/**
 * Called when some fatal error situation arises or when the “q” debugger command is used.
 */
void S9xExit() {
    exit(0);
}

/**
 * When Snes9x wants to display an error, information or warning message, it calls this function.
 * Check in messages.h for the types and individual message numbers that Snes9x currently passes as parameters.
 * The idea is display the message string so the user can see it, but you choose not to display anything at all,
 * or change the message based on the message number or message type.
 * Eventually all debug output will also go via this function, trace information already does.
 */
void S9xMessage(int type, int number, const char *message) {
    printf("S9xMessage: type: %d number: %d message: %s\n", type, number, message);
}

/**
 * Used by Snes9x to ask the user for input.
 */
const char *S9xStringInput(const char *message) {
    static char buffer[256];

    printf("%s: ", message);
    fflush(stdout);

    if (fgets(buffer, sizeof(buffer) - 2, stdin)) {
        return buffer;
    }

    return nullptr;
}

/**
 * Called when the SNES color palette has changed.
 * Use this function if your system should change its color palette to match the SNES's.
 * Otherwise let it empty.
 */
void S9xSetPalette() {
}
