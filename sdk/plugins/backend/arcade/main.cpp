/*
 * Copyright (C) Bilge Theall, wazcd_1608@qq.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "m1thread.h"

#include <backendinterface.h>

#include <string>

#include "stdlib.h"

#include "pluginutils.h"

#define EXPORT __declspec(dllexport)

const wchar_t *szName = L"Arcade";
const wchar_t *szManufacture = L"Bilge Theall";
const wchar_t *szContact = L"wazcd_1608@qq.com";
const wchar_t *szDescription = L"Plugin port to m1";
const wchar_t *szCreateDate = L"2016-10-11";

const char *szM1lib = "m1.dll";

wstring g_error;
wstring g_curRomPath;

static TM1Thread *g_runningThread=NULL;

int findGameIdByName(string name)
{
    int maxGames = m1snd_get_info_int(M1_IINF_TOTALGAMES, 0);
    int gameId = -1;

    for (int i = 0; i < maxGames; i++)
    {
        if (name==m1snd_get_info_str(M1_SINF_ROMNAME, i))
        {
            //High 16 bits store game id.
            gameId = i;
            break;
        }
    }
    return gameId;
}

// callbacks from the core of interest to the user interface
STDCALL int m1ui_message(void *user, int message, char *txt, int iparam)
{
    (void)user;
    (void)iparam;

    int curgame;

    switch (message)
    {
        // called when switching to a new game
        case M1_MSG_SWITCHING:
            printf("\nSwitching to game %s\n", txt);
            break;

        // called to show the current game's name
        case M1_MSG_GAMENAME:
            curgame = m1snd_get_info_int(M1_IINF_CURGAME, 0);
            printf("Game selected: %s (%s, %s)\n", txt, m1snd_get_info_str(M1_SINF_MAKER, curgame), m1snd_get_info_str(M1_SINF_YEAR, curgame));
            break;

        // called to show the driver's name
        case M1_MSG_DRIVERNAME:
            printf("Driver: %s\n", txt);
            break;

        // called to show the hardware description
        case M1_MSG_HARDWAREDESC:
            printf("Hardware: %s\n", txt);
            break;

        // called when ROM loading fails for a game
        case M1_MSG_ROMLOADERR:
            printf("ROM load error, bailing\n");
            //self->loadFailed();
            break;

        // called when a song is (re)triggered
        case M1_MSG_STARTINGSONG:
            break;

        // called if a hardware error occurs
        case M1_MSG_HARDWAREERROR:
            m1snd_shutdown();
            break;

        // called when the hardware begins booting
        case M1_MSG_BOOTING:
            printf("\nBooting hardware, please wait...");
            break;

        // called when the hardware is finished booting and is ready to play
        case M1_MSG_BOOTFINISHED:
            printf("ready!\n\n");
            break;

        // called when there's been at least 2 seconds of silence
        case M1_MSG_SILENCE:
            break;

        // called to let the UI do vu meters/spectrum analyzers/etc
        // txt = pointer to the frame's interleaved 16-bit stereo wave data
        // iparm = number of samples (bytes / 4)
        case M1_MSG_WAVEDATA:
            break;

        case M1_MSG_MATCHPATH:
            {
                if(!g_curRomPath.empty())
                {
                    string romPath = wstring2string(g_curRomPath);
                    m1snd_set_info_str(M1_SINF_SET_ROMPATH, (char *)romPath.c_str(), 0, 0, 0);
                    return 1;
                }
                return 0;
            }
            break;

        case M1_MSG_GETWAVPATH:
            break;

        case M1_MSG_ERROR:
            printf("%s\n", txt);
            break;
    }

    return 0;
}

// Initialize plugin
bool initialize()
{
    if(!g_runningThread)
    {
        g_runningThread = new TM1Thread;
    }

    return true;
}

// Verify this plugin can parse specify suffix of file
const wstring matchSuffixes()
{
    return L"zip";
}

// Parse file to get details information
bool parse(const wstring fileName, TMusicInfo* musicInfo)
{
    string gameName = wstring2string(extractBaseName(fileName));
    int gameId = findGameIdByName(gameName);
    if(gameId < 0)
        return false;

    musicInfo->musicName = char2wstring(m1snd_get_info_str(M1_SINF_VISNAME, gameId));
    musicInfo->year = atoi(m1snd_get_info_str(M1_SINF_YEAR, gameId));
    musicInfo->artist = char2wstring(m1snd_get_info_str(M1_SINF_MAKER, gameId));
    musicInfo->game = char2wstring(m1snd_get_info_str(M1_SINF_ROMNAME, gameId));
    musicInfo->system = L"Arcade";

    //Track list
    int trackCount = m1snd_get_info_int(M1_IINF_TRACKS, gameId);

    for (int i = 0; i < trackCount; i++)
    {
        TTrackInfo *trackInfo = new TTrackInfo;
        int trackCmdParam = (i<<16)|gameId;
        int trackCmd = m1snd_get_info_int(M1_IINF_TRACKCMD, trackCmdParam);
        int trackParam = (trackCmd<<16) | gameId;
        trackInfo->index = i;
        wchar_t buf[20];
        swprintf(buf, L"#%d", trackCmd);
        trackInfo->indexName = buf;

        //Save the duration (unit: ms)
        trackInfo->duration = m1snd_get_info_int(M1_IINF_TRKLENGTH, trackParam)*1000/60;
        if(trackInfo->duration < 0)
            trackInfo->duration = 0;

        // TrackName
        trackInfo->trackName = char2wstring(m1snd_get_info_str(M1_SINF_TRKNAME, trackParam));
        trackInfo->game = musicInfo->game;
        trackInfo->artist = musicInfo->artist;
        trackInfo->year = musicInfo->year;
        trackInfo->additionalInfo = musicInfo->additionalInfo;

        musicInfo->duration += trackInfo->duration;
        musicInfo->trackList.push_back(trackInfo);
    }

    //Mission complete.
    return true;
}

// Load track to prepare for playing
bool loadTrack(TTrackInfo* trackInfo)
{
    g_curRomPath = trackInfo->musicFileName;
    string baseName = wstring2string(extractBaseName(trackInfo->musicFileName));
    int gameId = findGameIdByName(baseName);
    if(gameId < 0)
        return false;

    if(gameId != m1snd_get_info_int(M1_IINF_CURGAME, 0))
    {
        m1snd_run(M1_CMD_GAMEJMP, gameId);
    }

    int songId = trackInfo->index;
    m1snd_run(M1_CMD_SONGJMP, songId);

    return true;
}

// Close track
void closeTrack()
{
    //m1snd_run(M1_CMD_STOP, 0);
}

// Request next samples
void nextSamples(byte* buffer, int bufSize)
{
    // size is the size of 1 channel samples
    m1snd_do_frame((unsigned long)bufSize/4, (signed short*)buffer);
}

// Optional, for return customized sample size
int sampleSize(int sampleRate, int fps)
{
    // 1 channel
    return ((float)sampleRate*10+(fps>>1))/fps+0.5;
}

// Retrieve plugin information
void pluginInformation(TPluginInfo *pluginInfo)
{
    if(!pluginInfo)
        return;

    pluginInfo->name = szName;
    pluginInfo->manufacture = szManufacture;
    pluginInfo->contact = szContact;
    pluginInfo->description = szDescription;
    pluginInfo->createDate = szCreateDate;
}

// Use to free plugin
void destroy()
{
    m1snd_shutdown();
    if(g_runningThread) {
        delete g_runningThread;
        g_runningThread = NULL;
    }
}

bool seek(int microSeconds)
{
    (void)microSeconds;
    return false;
}

const wstring suffixDescription(const wstring suffix)
{
    (void)suffix;
    return L"Arcade rom";
}

EXPORT void send_cmd(
    BackendCmd cmd,
    void *param1,
    void *param2,
    void *param3,
    void *param4)
{
    (void)param4;
    switch (cmd) {
    case BC_INITIALIZE:
        *(bool*)param1 = initialize();
        break;
    case BC_GET_MATCH_SUFFIXES:
        *(wstring*)param1 = matchSuffixes();
        break;
    case BC_GET_SUFFIX_DESCRIPTION:
        *(wstring*)param2 = suffixDescription(*(wstring*)param1);
        break;
    case BC_PARSE:
        *(bool*)param3 = parse(*(wstring*)param1, (TMusicInfo*)param2);
        break;
    case BC_LOAD_TRACK:
        *(bool*)param2 = loadTrack((TTrackInfo*)param1);
        break;
    case BC_CLOSE_TRACK:
        closeTrack();
        break;
    case BC_GET_NEXT_SAMPLES:
        nextSamples((byte*)param1, *(int*)param2);
        break;
    case BC_GET_SAMPLE_SIZE:
        *(int*)param3 = sampleSize(*(int*)param1, *(int*)param2);
        break;
    case BC_SEEK:
        *(bool*)param2 = seek(*(int*)param1);
        break;
    case BC_GET_PLUGIN_INFORMATION:
        pluginInformation((TPluginInfo*)param1);
        break;
    case BC_GET_LAST_ERROR:
        *(wstring*)param1 = g_error;
        break;
    case BC_DESTRORY:
        destroy();
        break;
    default:
        break;
    }
}
