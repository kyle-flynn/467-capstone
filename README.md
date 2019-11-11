# Zeus
#### This is a capstone project for GVSU 467 under the direction of Kyle Flynn, Hayden Townley, Alex Cross, and Sean G.

## Project Setup
Follow the guide below to start developing. Currently, only Microsoft Visual Studio 2019 instructions have been created.

### Microsoft Visual Studio 2019
#### Setup
1. Clone this repository.
2. Open `Zeus.sln` in Visual Studio 2019
3. Download the *entire* SFML folder from the google drive.
4. Place the SFML folder in a location on your computer that doesn't have spaces. (e.g. `C:\C Libraries` - this won't work)

#### Dynamically Linking & Additional Include Directories
1. Once in Visual Studio, look towards the top to the left of the `Local Windows Debugger` button. Change the two dropdowns to `Debug` and `x64`.
2. Go to `Project -> Zeus Properties` in the top menubar.
3. Make sure `Configuration` is `Debug` and `Platform` is `x64`.
4. Under the `Configuration Properties` section, drop down to C/C++. Edit the `Additional Include Directories` to *also* include `<path to your SFML>\source\include`.
5. Next, go to the `Linker` section. Edit the `Additional Library Directories` to *also* include `<path to your SFML>\build\lib\Debug`.
6. Now, under the `Linker` Section, go to the `Input` section. Edit the `Additional Dependencies` to *also* include the following:
    * sfml-graphics-d.lib
    * sfml-window-d.lib
    * sfml-system-d.lib
    * sfml-audio-d.lib
    * sfml-main-d.lib
    * sfml-network-d.lib
7. Finally, go to the `Post-Build Events` section under `Build Events`, and add `xcopy "$(SolutionDir)Resources" "$(TargetDir)"` to the `CommandLine` option.
8. Hit the `OK` button at the bottom of the dialog, and build the project with the `Local Windows Debugger` option.
9. Happy Coding!

### Troubleshooting
#### Could not find `sfml-window-d-2.dll`.
1. Go to the SFML folder location that you decided upon previously. 
2. Navigate to the directory `<YOUR_SFML_DIRECTORY>\build\lib\Debug`.
3. Copy all of the files that end in `-d-2.dll` (e.g. `sfml-audio-d-2.dll`, `sfml-graphics-d-2.dll`, `sfml-network-d-2.dll`, `sfml-system-d-2.dll`, `sfml-window-d-2.dll`).
4. Navigate to the following file location: `<THIS_REPOSITORY_LOCATION>\Zeus\x64\Debug`.
5. Paste the `*.dll` files into the directory.
