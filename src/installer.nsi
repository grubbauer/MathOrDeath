!define APPNAME "MathOrDeath"
!define APPDIR "$APPDATA\${APPNAME}"
!define EXE_NAME "MathOrDeath_v1.3.2.exe"

Outfile "D:\dev\MathOrDeath\build\MathOrDeath_INSTALLER.exe"
InstallDir "${APPDIR}"

Section "Install"
    SetOutPath "${APPDIR}"
    
    ; Copy files to the installation directory
    File /r "D:\dev\MathOrDeath\build\windows-x64\*.*"

    ; Create a shortcut on the desktop
    CreateShortcut "$DESKTOP\${APPNAME}.lnk" "${APPDIR}\${EXE_NAME}"

    ; Uninstaller creation
    WriteUninstaller "$INSTDIR\Uninstall.exe"

SectionEnd

Section "Uninstall"
    ; Delete installed files
    RMDir /r "${APPDIR}\*.*"

    ; Remove shortcut
    Delete "$DESKTOP\${APPNAME}.lnk"
SectionEnd
