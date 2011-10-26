;================================
; RELEASE NAME : iisu� OSC Bridge (for Windows)
; PURPOSE      : iisu� to OSC networking bridge
; PACKAGER     : are@softkinetic.com

;--------------------------------
; Includes

  !include "MUI2.nsh"

;--------------------------------
; General

  ; The name of the program to install
  Name "iisuOscBridge"

  ; The file to write
  OutFile "iisuOscBridge_setup.exe"

  ; Default installation folder
  InstallDir "$PROGRAMFILES\iisuOscBridge"
  
  ; Overwrite installation folder from registry if available.
  InstallDirRegKey HKCU "Software\Softkinetic\iisuOscBridge" ""

  ; Request application privileges for Windows Vista
  RequestExecutionLevel admin
  
;--------------------------------
; Variables

  Var STARTMENU_FOLDER
  Var MUI_TEMP

;--------------------------------
; Defines 

!define REG_KEY_NAME "Software\Softkinetic\iisuOscBridge"

;--------------------------------
; Interface settings

!define MUI_ICON "..\Resource Files\SK_logo_256x256.ico"

!define MUI_ABORTWARNING

!define MUI_WELCOMEPAGE_TITLE "Welcome to the iisuOscBridge� Setup Wizard"
!define MUI_WELCOMEPAGE_TEXT  "This wizard will guide you through the installation of iisuOscBridge�, the bridge between iisu� and OSC networking.$\r$\n$\r$\nThe iisuOscBridge� provides the following functionalities:$\r$\n$\r$\n  (1) Launch iisu�,$\r$\n  (2) Configure maps between iisu� output data and OSC paths,$\r$\n  (3) Send data over a network using the OSC protocol.$\r$\n$\r$\n$_CLICK"

!define MUI_LICENSEPAGE_CHECKBOX

!define MUI_FINISHPAGE_TITLE "Completing the iisuOscBridge� Setup Wizard"

!define MUI_FINISHPAGE_LINK "Visit the Softkinetic site for the latest news and support."
!define MUI_FINISHPAGE_LINK_LOCATION "http://www.softkinetic.com/"

;--------------------------------
; Pages

  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_LICENSE "License.txt"
  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  !insertmacro MUI_PAGE_STARTMENU Application $STARTMENU_FOLDER
  !insertmacro MUI_PAGE_FINISH
  
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  
;--------------------------------
; Languages
 
  !insertmacro MUI_LANGUAGE "English"

;--------------------------------
; Installer Sections

Section "Core" Section_Core
  
    ; SetShellVarContext all

    ; SectionIn 1 RO

    ; Deploy files.
    SetOutPath "$INSTDIR"

    File "..\Release\iisuOscBridge.exe"
    File "License.txt"
  
  ; Install the menu items.
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
  
    CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER"

    SetOutPath "$INSTDIR" ; SetOutPath sets the working directory of the shortcut

    CreateShortCut  "$SMPROGRAMS\$STARTMENU_FOLDER\iisuOscBridge.lnk"         "$INSTDIR\iisuOscBridge.exe"
    CreateShortCut  "$SMPROGRAMS\$STARTMENU_FOLDER\License.lnk"               "$INSTDIR\License.txt"
    CreateShortCut  "$SMPROGRAMS\$STARTMENU_FOLDER\Uninstall.lnk"             "$INSTDIR\Uninstall.exe"

    SetOutPath "$INSTDIR"

  !insertmacro MUI_STARTMENU_WRITE_END
  
  ; Store installation folder in a regitry key.
  WriteRegStr HKCU "Software\Softkinetic\iisuOscBridge" "" $INSTDIR
  
  ; Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

SectionEnd

;--------------------------------
; Descriptions

  ; Language strings
  LangString DESC_iisuOscBridgeCore ${LANG_ENGLISH} "This is the core of iisuOscBridge�, the section actually bridging iisu� output data with OSC networking."

  ; Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${Section_Core} $(DESC_iisuOscBridgeCore)
  !insertmacro MUI_FUNCTION_DESCRIPTION_END

;--------------------------------
; Uninstaller Section

Section "Uninstall"
  
  ; Remove the deployed files.
  ; Delete "$INSTDIR\Uninstall.exe"
  RMDir /r "$INSTDIR"

  ; Uninstall the menu items.
  !insertmacro MUI_STARTMENU_GETFOLDER Application $MUI_TEMP
  RMDIR /r "$SMPROGRAMS\$MUI_TEMP"

  ; Delete registry keys.
  DeleteRegKey /ifempty HKCU "Software\Softkinetic\iisuOscBridge"

SectionEnd