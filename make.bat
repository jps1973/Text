cls

del *.exe

windres Resource.rc -o Resource.o

g++ -mwindows -m64 -static -Wall -Wextra Text.cpp ListBoxWindow.cpp RichEditWindow.cpp StatusBarWindow.cpp Resource.o -o Text.exe
