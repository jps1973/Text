cls

del *.exe

windres Resource.rc -o Resource.o

g++ -mwindows -m64 -static -Wall -Wextra Text.cpp ListBoxWindow.cpp RichEditWindow.cpp Registry.cpp StatusBarWindow.cpp ToolBarWindow.cpp Resource.o -o Text.exe -lcomctl32
