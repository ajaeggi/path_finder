# path_finder
A visualized A* path finder

## Compile
I compiled with mingw on Windows
1. Install g++ v7.3.0 with the corresponding SFML libraries (any other version might work as well but I used this)
2. Copy SFML libs to /i686-w64-mingw32/lib/, the SFML include to /i686-w64-mingw32/include/ and the SFML bins to /i686-w64-mingw32/bin/
3. Add the C:\mingw32\bin to the system environment PATH
4. execute `compile.bat`

## Run/Debug in VS Code
1. The official C/C++ extension needs to be installed 
2. Define the `tasks.json` file 
```JSON
{
    "version": "2.0.0",
    "tasks": [
        {
            "type": "shell",
            "label": "g++.exe build active file",
            "command": "g++",
            "args": [
                "-g",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe",
                "-I",
                "${workspaceFolder}\\include\\",
                "${workspaceFolder}\\*.cpp",
                "-lsfml-graphics",
                "-lsfml-window",
                "-lsfml-system"
            ],
            "options": {
                "cwd": "C:\\mingw32\\bin"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
```
