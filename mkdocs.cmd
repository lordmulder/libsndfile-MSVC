@echo off
"%~dp0\..\Prerequisites\Pandoc\pandoc.exe" --from markdown --to html5 --toc -N --standalone --self-contained -c "%~dp0\etc\css\github-pandoc.css" --output "%~dp0\README.html" "%~dp0\README.md"
pause
