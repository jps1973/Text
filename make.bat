cls

del *.exe

windres Resource.rc -o Resource.o

g++ -mwindows -m64 -static -Wall -Wextra ^
 ^
 Text.cpp ^
 ^
 ControlWindow.cpp ^
 RegistryKeyClass.cpp ^
 ToolBarWindow.cpp ^
 ^
 Resource.o ^
 ^
 -o Text.exe -lcomctl32
