@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by LOGPLOT.HPJ. >"hlp\LogPlot.hm"
echo. >>"hlp\LogPlot.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\LogPlot.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\LogPlot.hm"
echo. >>"hlp\LogPlot.hm"
echo // Prompts (IDP_*) >>"hlp\LogPlot.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\LogPlot.hm"
echo. >>"hlp\LogPlot.hm"
echo // Resources (IDR_*) >>"hlp\LogPlot.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\LogPlot.hm"
echo. >>"hlp\LogPlot.hm"
echo // Dialogs (IDD_*) >>"hlp\LogPlot.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\LogPlot.hm"
echo. >>"hlp\LogPlot.hm"
echo // Frame Controls (IDW_*) >>"hlp\LogPlot.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\LogPlot.hm"
REM -- Make help for Project LOGPLOT


echo Building Win32 Help files
start /wait hcrtf -x "hlp\LogPlot.hpj"
echo.
if exist Debug\nul copy "hlp\LogPlot.hlp" Debug
if exist Debug\nul copy "hlp\LogPlot.cnt" Debug
if exist Release\nul copy "hlp\LogPlot.hlp" Release
if exist Release\nul copy "hlp\LogPlot.cnt" Release
echo.


