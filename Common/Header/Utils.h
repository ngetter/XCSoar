/*
Copyright_License {

  XCSoar Glide Computer - http://www.xcsoar.org/
  Copyright (C) 2000 - 2009

	M Roberts (original release)
	Robin Birch <robinb@ruffnready.co.uk>
	Samuel Gisiger <samuel.gisiger@triadis.ch>
	Jeff Goodenough <jeff@enborne.f2s.com>
	Alastair Harrison <aharrison@magic.force9.co.uk>
	Scott Penrose <scottp@dd.com.au>
	John Wharington <jwharington@gmail.com>
	Lars H <lars_hn@hotmail.com>
	Rob Dunning <rob@raspberryridgesheepfarm.com>
	Russell King <rmk@arm.linux.org.uk>
	Paolo Ventafridda <coolwind@email.it>
	Tobias Lohner <tobias@lohner-net.de>
	Mirek Jezek <mjezek@ipplc.cz>
	Max Kellermann <max@duempel.org>

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
}
*/
#if !defined(XCSOAR_UTILS_H)
#define XCSOAR_UTILS_H

#include <windows.h>
#include <math.h>
#include "Task.h"
#include "Airspace.h"
#include <zzip/lib.h>

extern bool LockSettingsInFlight;
extern bool LoggerShortName;

#ifdef FIVV
BOOL DelRegistryKey(const TCHAR *szRegistryKey); // VENTA2-ADDON delregistrykey
#endif
#ifdef PNA
void CleanRegistry(); // VENTA2-ADDON cleanregistrykeyA
bool SetBacklight(); // VENTA4-ADDON for PNA
bool SetSoundVolume(); // VENTA4-ADDON for PNA
#endif

void SectorEndPoint(double StartLat, double StartLon, double  Radial, double Dist, double *EndLat, double *EndLon);
void ConvertFlightLevels(void);
void ReadPort1Settings(DWORD *PortIndex, DWORD *SpeedIndex);
void ReadPort2Settings(DWORD *PortIndex, DWORD *SpeedIndex);
void ReadPort3Settings(DWORD *PortIndex, DWORD *SpeedIndex);
void WritePort1Settings(DWORD PortIndex, DWORD SpeedIndex);
void WritePort2Settings(DWORD PortIndex, DWORD SpeedIndex);
void WritePort3Settings(DWORD PortIndex, DWORD SpeedIndex);
void WriteProfile(const TCHAR *szFile);
void ReadProfile(const TCHAR *szFile);
#if defined(PNA) || defined(FIVV)  // VENTA-ADDON
void SetModelType();
bool SetModelName(DWORD Temp);
#endif
void FormatWarningString(int Type, const TCHAR *Name,
                         AIRSPACE_ALT Base, AIRSPACE_ALT Top,
                         TCHAR *szMessageBuffer, TCHAR *TileBuffer);
BOOL ReadString(ZZIP_FILE* zFile, int Max, TCHAR *String);
BOOL ReadStringX(FILE *fp, int Max, TCHAR *String);

double StrToDouble(const TCHAR *Source, const TCHAR **Stop);
void PExtractParameter(const TCHAR *Source, TCHAR *Destination,
                       int DesiredFieldNumber);



void ExtractDirectory(TCHAR *Dest, const TCHAR *Source);
double DoSunEphemeris(double lon, double lat);

void *bsearch(void *key, void *base0, size_t nmemb, size_t size, int (*compar)(const void *elem1, const void *elem2));
TCHAR *strtok_r(TCHAR *s, const TCHAR *delim, TCHAR **lasts);


void ResetInfoBoxes(void);

/* =====================================================
   Interface Files !
   ===================================================== */

typedef struct {
	TCHAR *key;
	TCHAR *text;
} GetTextSTRUCT;



// Parse string (new lines etc) and malloc the string
TCHAR* StringMallocParse(const TCHAR* old_string);

void ConvertTToC(CHAR* pszDest, const TCHAR* pszSrc);
void ConvertCToT(TCHAR* pszDest, const CHAR* pszSrc);

void propGetFontSettings(const TCHAR *Name, LOGFONT* lplf);
void propGetFontSettingsFromString(const TCHAR *Buffer, LOGFONT* lplf);
int propGetScaleList(double *List, size_t Size);

long GetUTCOffset(void);
int TextToLineOffsets(TCHAR* text, int* LineOffsets, int maxLines);
void RestoreRegistry(void);
void StoreRegistry(void);
void XCSoarGetOpts(LPTSTR CommandLine);

bool CheckRectOverlap(RECT rc1, RECT rc2);
int MeasureCPULoad();

void OpenFLARMDetails();
void CloseFLARMDetails();
const TCHAR* LookupFLARMDetails(long id);
int LookupFLARMDetails(const TCHAR *cn);
bool AddFlarmLookupItem(int id, const TCHAR *name, bool saveFile);
int LookupSecondaryFLARMId(int id);

double HexStrToDouble(TCHAR *Source, TCHAR **Stop);

long CheckFreeRam(void);

void MemCheckPoint();
void MemLeakCheck();
void MyCompactHeaps();
unsigned long FindFreeSpace(const TCHAR *path);
bool MatchesExtension(const TCHAR *filename, const TCHAR* extension);
BOOL PlayResource (const TCHAR* lpName);
void CreateDirectoryIfAbsent(const TCHAR *filename);

bool InterfaceTimeoutZero(void);
void InterfaceTimeoutReset(void);
bool InterfaceTimeoutCheck(void);

#ifdef __cplusplus
extern "C"{
#endif

bool FileExistsW(const TCHAR *FileName);
bool FileExistsA(const char *FileName);

#ifdef _UNICODE
#define FileExists FileExistsW
#else
#define FileExists FileExistsA
#endif

#ifdef __cplusplus
}
#endif



bool RotateScreen(void);

#endif
