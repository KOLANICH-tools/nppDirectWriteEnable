//this file is part of notepad++
//Copyright (C)2003 Don HO <donho@altern.org>
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#define UNICODE

#include "PluginInterface.h"
#include "Scintilla.h"

const TCHAR NPP_PLUGIN_NAME[] = TEXT("DirectWrite enabler");
void about(){
	MessageBox(NULL, TEXT("Just sets SCI_SETTECHNOLOGY to SC_TECHNOLOGY_DIRECTWRITE and SCI_SETBUFFEREDDRAW to 0, enabling DirectWrite. On Windows this has a biproduct of enabling ligatures for the fonts like Fira Code (NPP users used to use scripting languages plugins to just set this var, see https://github.com/notepad-plus-plus/notepad-plus-plus/issues/2287), changes subpixel smoothing a bit and probably hardware-accelerates rendering. In Wine it just causes poor performance (https://bugs.winehq.org/show_bug.cgi?id=47689, https://bugs.winehq.org/show_bug.cgi?id=47690)."), NPP_PLUGIN_NAME, MB_OK);
}

FuncItem funcItems[]={
	{._itemName={TEXT("DirectWrite enabler")}, ._pFunc=about, ._init2Check=false, ._pShKey=nullptr}
};

BOOL APIENTRY DllMain(HANDLE, DWORD, LPVOID)
{
	return true;
}


extern "C" __declspec(dllexport) void setInfo(NppData nppData)
{
	// SC_TECHNOLOGY_DEFAULT
	// SC_TECHNOLOGY_DIRECTWRITE
	// SC_TECHNOLOGY_DIRECTWRITERETAIN
	// SC_TECHNOLOGY_DIRECTWRITEDC
	
	int which = -1;
	SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);
	if (which == -1)
		return;
	HWND curScintilla = (which == 0) ? nppData._scintillaMainHandle : nppData._scintillaSecondHandle;
	SendMessage(curScintilla, SCI_SETTECHNOLOGY, SC_TECHNOLOGY_DIRECTWRITE, 0); // https://www.scintilla.org/ScintillaDoc.html#SCI_SETTECHNOLOGY
	SendMessage(curScintilla, SCI_SETBUFFEREDDRAW, 0, 0); // https://www.scintilla.org/ScintillaDoc.html#SCI_SETBUFFEREDDRAW
}

extern "C" __declspec(dllexport) const TCHAR * getName()
{
	return NPP_PLUGIN_NAME;
}

extern "C" __declspec(dllexport) FuncItem * getFuncsArray(int *nbF)
{
	*nbF = sizeof(funcItems)/sizeof(*funcItems);
	return funcItems;
}


extern "C" __declspec(dllexport) void beNotified(SCNotification *)
{
	return;
}


extern "C" __declspec(dllexport) LRESULT messageProc(UINT, WPARAM, LPARAM)
{
	return true;
}

#ifdef UNICODE
extern "C" __declspec(dllexport) BOOL isUnicode()
{
	return true;
}
#endif //UNICODE
