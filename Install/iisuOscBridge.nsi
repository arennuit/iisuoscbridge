;================================
; RELEASE NAME	: iisu™ OSC Bridge (for Windows)
; PURPOSE		: iisu™ to OSC networking bridge
; PACKAGER		: are@softkinetic.com

;--------------------------------
; Includes.

!include "MUI2.nsh"
	
;--------------------------------
; Defines.

!define DEFAUT_INSTALL_DIR "C:\iisuOscBridge" ; It should be '$PROGRAMFILES\iisuOscBridge', but as iisu writes files in the install dir, and the install dir is 'read only', this causes a crash or requires the admin rights.
!define INSTALL_DIR_REG_SUB_KEY "Software\Softkinetic\iisuOscBridge"
!define INSTALL_DIR_REG_ENTRY "Install_Dir"

!define LIC_FILE_PATH "License.txt"

!define RESOURCES_FOLDER "..\Resource Files"
!define DEPENDENCIES_FOLDER "..\..\Dependencies"
!define QT_BIN_FOLDER "${DEPENDENCIES_FOLDER}\Qt_4.6.2\bin"
!define DOC_FOLDER "..\Doc"
!define SAMPLES_FOLDER "..\Samples"

;--------------------------------
; General.

; The name of the program to install.
Name "iisuOscBridge™"

; The file to write.
OutFile "iisuOscBridge_setup.exe"

; Default installation folder (the actual installation folder is in '$INSTDIR' and is set via priorities, among which 'InstallDir' is lowest).
InstallDir "${DEFAUT_INSTALL_DIR}"

; Overwrite installation folder from registry if available.
InstallDirRegKey HKLM "${INSTALL_DIR_REG_SUB_KEY}" "${INSTALL_DIR_REG_ENTRY}"

; Request application privileges for Windows Vista.
RequestExecutionLevel admin

;--------------------------------
; Variables.

Var STARTMENU_FOLDER
Var MUI_TEMP

;--------------------------------
; Interface settings.

!define MUI_ICON "${RESOURCES_FOLDER}\SK_logo_256x256.ico"

!define MUI_ABORTWARNING

!define MUI_WELCOMEPAGE_TITLE "Welcome to the iisuOscBridge™ Setup Wizard"
!define MUI_WELCOMEPAGE_TEXT  "This wizard will guide you through the installation of iisuOscBridge™, the bridge between iisu™ and OSC networking.$\r$\n$\r$\nThe iisuOscBridge™ provides the following functionalities:$\r$\n$\r$\n  (1) Launch iisu™,$\r$\n  (2) Configure maps between iisu™ output data and OSC paths,$\r$\n  (3) Send data over a network using the OSC protocol.$\r$\n$\r$\n$_CLICK"

!define MUI_LICENSEPAGE_CHECKBOX

!define MUI_FINISHPAGE_TITLE "Completing the iisuOscBridge™ Setup Wizard"

!define MUI_FINISHPAGE_LINK "Visit the iisuOscBridge™ blog for news and support."
!define MUI_FINISHPAGE_LINK_LOCATION "http://iisuoscbridge.blogspot.com/"


;--------------------------------
; Pages.

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "${LIC_FILE_PATH}"
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_STARTMENU Application $STARTMENU_FOLDER
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

;--------------------------------
; Languages.
 
!insertmacro MUI_LANGUAGE "English"

;--------------------------------
; Functions.

Function .onInit

	; Check for existing installation.
	ReadRegStr $0 HKLM "${INSTALL_DIR_REG_SUB_KEY}" "${INSTALL_DIR_REG_ENTRY}"

	${If} ${FileExists} "$0"
		MessageBox MB_OKCANCEL|MB_ICONEXCLAMATION "iisuOscBridge™ is already installed at $0. $\n$\nClick `OK` to Uninstall and Continue or `Cancel` to Quit setup." /SD IDOK IDOK uninst
		Abort

		; Run the un-installer if there was a previouly existing installation.
		uninst:
			IfSilent 0 +2
				Goto silent
			ExecWait '"$0\Uninstall.exe" _?=$0'
			Goto next
		silent:
			ExecWait '"$0\Uninstall.exe" /S _?=$0'
		next:
	${EndIf}

	; Make sure the install dir's default value is the default one (the default one is normally not used if reg key 'InstallDirRegKey' was defined).
	StrCpy $INSTDIR "${DEFAUT_INSTALL_DIR}"

FunctionEnd

;--------------------------------
; Installer Sections.

Section "Core" Section_Core

	SetShellVarContext all

	SectionIn 1 RO

	; Deploy files.
	SetOutPath "$INSTDIR"
	File "..\Release\iisuOscBridge.exe"
	File "${QT_BIN_FOLDER}\QtCore4.dll"
	File "${QT_BIN_FOLDER}\QtGui4.dll"
	File "${LIC_FILE_PATH}"
	File "..\Resource Files\SplashScreen.png"

	SetOutPath "$INSTDIR\Doc"
	File "${DOC_FOLDER}\QuickStartGuide.pdf"
	
	SetOutPath "$INSTDIR\Samples\PureData"
	File "${SAMPLES_FOLDER}\PureData\PureData_readMe.txt"
	
	SetOutPath "$INSTDIR\Samples\PureData\SimpleRightHand"
	File "${SAMPLES_FOLDER}\PureData\SimpleRightHand\SimpleRightHand.iob"
	File "${SAMPLES_FOLDER}\PureData\SimpleRightHand\SimpleRightHand.pd"
	
	SetOutPath "$INSTDIR" ; Makes sure the 'Start In' property in the start menu is set on 'INSTDIR'.

	; Install the menu items.
	!insertmacro MUI_STARTMENU_WRITE_BEGIN Application

	CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER"

	CreateShortCut  "$SMPROGRAMS\$STARTMENU_FOLDER\iisuOscBridge.lnk"		"$INSTDIR\iisuOscBridge.exe"
	CreateShortCut  "$SMPROGRAMS\$STARTMENU_FOLDER\License.lnk"				"$INSTDIR\License.txt"
	CreateShortCut  "$SMPROGRAMS\$STARTMENU_FOLDER\Uninstall.lnk"			"$INSTDIR\Uninstall.exe"

	CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER\Doc"

	CreateShortCut  "$SMPROGRAMS\$STARTMENU_FOLDER\Doc\QuickStartGuide.lnk"					"$INSTDIR\Doc\QuickStartGuide.pdf"

	CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER\Samples"

	CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER\Samples\PureData\"
	CreateShortCut  "$SMPROGRAMS\$STARTMENU_FOLDER\Samples\PureData\PureData_readMe.lnk"				"$INSTDIR\Samples\PureData\PureData_readMe.txt"

	CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER\Samples\PureData\SimpleRightHand\"
	CreateShortCut  "$SMPROGRAMS\$STARTMENU_FOLDER\Samples\PureData\SimpleRightHand\SimpleRightHand_bridge.lnk"		"$INSTDIR\Samples\PureData\SimpleRightHand\SimpleRightHand.iob"
	CreateShortCut  "$SMPROGRAMS\$STARTMENU_FOLDER\Samples\PureData\SimpleRightHand\SimpleRightHand_network.lnk"	"$INSTDIR\Samples\PureData\SimpleRightHand\SimpleRightHand.pd"

	SetOutPath "$INSTDIR"

	!insertmacro MUI_STARTMENU_WRITE_END

	; Registry: installation directory.
	WriteRegStr HKLM "${INSTALL_DIR_REG_SUB_KEY}" "${INSTALL_DIR_REG_ENTRY}" $INSTDIR

	; Create uninstaller.
	WriteUninstaller "$INSTDIR\Uninstall.exe"

SectionEnd

Section ".iob Files Associations" Section_FilesAssoc

	SetShellVarContext all
	SectionIn 1
	
	WriteRegStr HKLM "SOFTWARE\Classes\.iob" "" "IobProjectFile"
	WriteRegStr HKLM "SOFTWARE\Classes\IobProjectFile" "" "iisuOscBridge project file"
	WriteRegStr HKLM "SOFTWARE\Classes\IobProjectFile\DefaultIcon" "" '"$INSTDIR\iisuOscBridge.exe"'
	WriteRegStr HKLM "SOFTWARE\Classes\IobProjectFile\shell\open" "" "&Open with iisuOscBridge"
	WriteRegStr HKLM "SOFTWARE\Classes\IobProjectFile\shell\open\command" "" '"$INSTDIR\iisuOscBridge.exe" "%1"'

	; --- Refresh the system ---
	SendMessage ${HWND_BROADCAST} ${WM_WININICHANGE} 0 "STR:Environment" /TIMEOUT=5000

	;WriteRegStr HKLM "SOFTWARE\Classes\.skscript" "" "Interaction Designer script file"

SectionEnd

;--------------------------------
; Descriptions.

; Assign language strings to sections.
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
!insertmacro MUI_DESCRIPTION_TEXT ${Section_Core} "This is the core of iisuOscBridge™, the section actually bridging iisu™ output data with OSC networking."
!insertmacro MUI_DESCRIPTION_TEXT ${Section_FilesAssoc} ".iob files association to iisuOscBridge."
!insertmacro MUI_FUNCTION_DESCRIPTION_END

;--------------------------------
; Uninstaller Section.

Section "Uninstall"

	; Remove the deployed files.
	; Delete "$INSTDIR\Uninstall.exe"
	RMDir /r "$INSTDIR"

	; Uninstall the menu items.
	!insertmacro MUI_STARTMENU_GETFOLDER Application $MUI_TEMP
	RMDIR /r "$SMPROGRAMS\$MUI_TEMP"

	; Remove the register keys.
	DeleteRegKey /ifempty HKLM "${INSTALL_DIR_REG_SUB_KEY}"
	
	; Remove the .iob file associations.
	DeleteRegKey   HKLM "SOFTWARE\Classes\.iob"
	DeleteRegKey   HKLM "SOFTWARE\Classes\IobProjectFile"

SectionEnd