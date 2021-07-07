@echo off

for %%f in (*.cpp) do (
	echo %%f
	g++ -std=c++11 %%f
	if errorlevel 1 (
		echo **** ERROR ****
		echo **** In:   %%f
		echo.
	)
)

del a.exe > nul
