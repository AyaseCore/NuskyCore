@ECHO OFF
REM
REM

SETLOCAL

PUSHD %~dp0

:tar
IF EXIST "Project_Nusky.tgz" DEL "Project_Nusky.tgz"
tar --version 1>&2 2>NUL || (ECHO. & ECHO ERROR: tar not found. try to use seven zip. & GOTO SevenZip)
tar czvf Project_Nusky.tgz cov-int
GOTO End

:SevenZip
IF NOT EXIST "C:\Program Files (x86)\7-Zip\7z.exe" (ECHO. & ECHO ERROR: "C:\Program Files (x86)\7-Zip\7z.exe" not found & GOTO End)
IF EXIST "Project_Nusky.tar" DEL "Project_Nusky.tar"
IF EXIST "Project_Nusky.tgz" DEL "Project_Nusky.tgz"
"C:\Program Files (x86)\7-Zip\7z.exe" a -ttar Project_Nusky.tar cov-int
"C:\Program Files (x86)\7-Zip\7z.exe" a -tgzip Project_Nusky.tgz Project_Nusky.tar
IF EXIST "Project_Nusky.tar" DEL "Project_Nusky.tar"
GOTO End

:End
POPD
ECHO. & ECHO Press any key to close this window...
PAUSE >NUL
ENDLOCAL
EXIT /B