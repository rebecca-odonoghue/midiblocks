# MIDIBlocks - Team Project I 2015
A MIDI synthesizer for Windows, designed for use with or without a custom MIDIBlocks hardware device.

## Windows Build Instructions
### Using Qt Creator to Build
1. Open \MIDIBlocks\MIDIBlocks.pro using Qt Creator
2. Open the Projects tab on the left hand side
3. Change the Release build directory to engg2800g38\MIDIBlocks\build
4. Ensure that the selected build is Release in the bottom left corner
5. Click the Build button in the bottom left corner

### Using the Windows Command Prompt to Build
1. Add both $QT_INSTALL_DIR\Qt5.5.0\5.5\mingw492_32\bin and 
$QT_INSTALL_DIR\Qt5.5.0\Tools\mingw492_32\bin to the PATH environment variable.
2. Run qmake from the MIDIBlocks directory
3. Run mingw32-make release from the same directory
4. Copy \MIDIBlocks\build\release\scales.csv to \MIDIBlocks\release

### Deploying the Qt Libraries
1. Add $QT_INSTALL_DIR\Qt5.5.0\5.5\mingw492_32\bin to the PATH environment variable.
2. Open the Windows Command Prompt to the build directory (\MIDIBlocks\build\release if built in Qt, or \MIDIBlocks\release if built using the command prompt)
3. Run windeployqt MIDIBlocks.exe 
