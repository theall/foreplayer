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
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef BACKENDINTERFACE_H
#define BACKENDINTERFACE_H

#include <map>
#include <vector>
#include <string>

using namespace std;

typedef pair<string, string> Property;
typedef vector<Property> Properties;

#ifdef __cplusplus
extern "C" {
#endif

#define EXPORT __declspec(dllexport)

typedef unsigned int uint;
typedef long int64 ;
typedef unsigned char byte;

#define MAX_PATH 260

struct TPluginInfo
{
    string name;
    string manufacture;
    string contact;
    string description;
    string createDate;
    string fileName;
};

struct TTrackInfo
{
    string trackName; // Track display name
    int index; // Track index id/start Position
    string indexName; // Track index name if index id is invalid
    string musicFileName; // Pointer to musicFileName of TMusicInfo
    string additionalInfo;
    int64 fileSize;
    string game;
    string artist;
    string system;
    int year;
    int duration;
    int sampleRate;
    int channels;
    TTrackInfo() {
        index = 0;
        fileSize = 0;
        duration = 0;
        channels = 2;
        sampleRate = 44100;
        trackName = "";
    }
};

typedef vector<TTrackInfo*> TTrackInfoList;

struct TMusicInfo
{
    string musicName; // Music diplay name
    string musicFileName;
    string game;
    string artist;
    string system;
    int year;
    int duration;
    int64 fileSize;
    int sampleRate;
    int channels;
    string additionalInfo;
    TTrackInfoList trackList;
    TMusicInfo(){
        fileSize = 0;
        duration = 0;
        channels = 2;
        sampleRate = 44100;
        musicName = "unknown";
    }
};

typedef vector<TMusicInfo*> TMusicInfoList;

typedef void (*TRequestSamples)(int bufSize, byte *buffer);

// Initialize plugin
EXPORT bool initialize();

// Verify this plugin can parse specify suffix of file
EXPORT const char *matchSuffixes();

// Return description of this suffix, for example "mp3" should be "Moving Picture Experts Group Audio Layer III"
EXPORT const char *suffixDescription(const char *suffix);

// Parse file to get details information
EXPORT bool parse(const wchar_t *file, TMusicInfo* musicInfo);

// Load track to prepare for playing
EXPORT bool loadTrack(TTrackInfo* track);

// Close track
EXPORT void closeTrack();

// Request next samples
EXPORT void nextSamples(int bufSize, byte* buffer);

// Optional, for return customized sample size
EXPORT int sampleSize(int sampleRate, int fps);

// Seek time
EXPORT bool seek(int microSeconds);

// Retrieve plugin information
EXPORT void pluginInformation(TPluginInfo *pluginInfo);

// Use to free plugin
EXPORT void destroy();

#ifdef __cplusplus
}
#endif
#endif // BACKENDINTERFACE_H
