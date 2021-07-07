@echo off
@prompt $q$q$g$s
if not exist %1\bld.cmd (
	echo Folder %1 does not exist!
	exit /b
)

@pushd %1
@echo *** Build
@echo on
@call bld.cmd
@echo off
@echo.
@echo *** Run
a.exe
@echo off
@popd
