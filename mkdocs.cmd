@echo off

if not exist "%JAVA_HOME%\bin\java.exe" (
	echo Java could not be found, please make sure JAVA_HOME is set correctly!
	pause && goto:eof
)

"%~dp0\..\Prerequisites\Pandoc\pandoc.exe" --from markdown --to html5 --toc -N --standalone --self-contained -c "%~dp0\etc\css\github-pandoc.css" --output "%~dp0\README.html" "%~dp0\README.md"

"%JAVA_HOME%\bin\java.exe" -jar "%~dp0\..\Prerequisites\HTMLCompressor\bin\htmlcompressor-1.5.3.jar" --compress-css -o "%~dp0\README.min.html" "%~dp0\README.html"
move /Y "%~dp0\README.min.html" "%~dp0\README.html"

pause
