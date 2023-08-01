# EmulatorViewer (WIP)
 
This is an application I developed in Unreal Engine 5.1 as a small proof of concept for a physics based emulation or HMI software to interact with a wide range of material handling systems.
The plan for this application is to be able to serve as a simulated environment to enable automated and repeatable testing scenarios by creating models that represent material handling system layouts and devices in the field that can provide mock inputs/outputs to any controllers, as well as collection and display of any metrics/statistics relevant to the system. In addition to the emulator functionality, it could also serve in an HMI/SCADA role presenting fault and statistics data to the user and allowing supervisory control of the system to the user.

### Development Environment:
- Unreal Engine 5.1.1 (From Epic Games Launcher, not full source code)
- Visual Studio 2022 Professional v17.6.5
- Visual Assist v10.9.2491
- GitHub Desktop

### Coding Standards and Style Guide:
This project adheres to the [Epic C++ Coding Standard](https://docs.unrealengine.com/5.1/en-US/epic-cplusplus-coding-standard-for-unreal-engine/).
One addition I make to this standard is that I like to prefix all member variables and methods with `this`. When working with a codebase the size of Unreal Engine, this makes it easier to scan code and tell at a glance when something is inherited, a member, or local, etc.

This project also follows Allar's [UE5 Style Guide](https://github.com/Allar/ue5-style-guide) for general folder structure and asset naming conventions except where it would directly contradict the [Epic C++ Coding Standard](https://docs.unrealengine.com/5.1/en-US/epic-cplusplus-coding-standard-for-unreal-engine/).

**Conveyor, Sidepan, and Gravity Chute static mesh objects were created by me in Blender.**

**Other objects such as those seen on the main menu and the primary box objects in the Sandbox scene are *placeholder* assets from Unreal Mega Scans and are extremely high poly. They are just being used in the prototyping phase to test functionality.**

**The project is very early in development and still in the prototyping stage.**

Currently implemented:
- Free movement of the camera within a scene with the ability to rotate, zoom, and snap-to focus on selected objects.

![Keyboard & Mouse movement of the camera](Docs/Gif/CameraAndMovement.gif "Keyboard & Mouse movement of the camera")

 - Physics-based conveyor belts that correctly simulate friction locomotion of items on a conveyor belt. Straight (Level, incline, decline) and 90 degree turns available.

![Physically correct conveyor belts](Docs/Gif/Physics.gif "Physically correct conveyor belts")

 - Customizable item spawner that allows the user to spawn new items onto a conveyor with a variety of settings to control the spawn rate and size of items, as well as introducing randomness to these factors.
 - "Interact Mode" which allows users to "grab" any physics item in the scene and manipulate it for finer control of placement or remove it from the system. 

## Main Menu

![The main menu](Docs/Gif/MainMenu.gif "The main menu")

### Settings

![Settings menu](Docs/Screenshots/SettingsMenu.png "Settings menu")

## Controls

#### Keyboard:
- W/Up: Move forward
- S/Down: Move backwards
- A/Left: Move left
- D/Right: Move right
- Q: Move down vertically
- E: Move up vertically
- F: Move focal point to the currently selected object.
- END: Set focal point back down to floor level.
- ESC: Pauses the sim and opens pause menu.
- P: Pauses the sim and opens pause menu.
- SPACE: If in Interact Mode, grabs a physics object under the cursor. Press again to release object.
- 1: Sets Observe Mode. Default control mode, no interaction allowed.
- 2: Sets Interact Mode. Allows interating with physics objects.
- 3: Sets Build Mode. Allows the creation, modification, and deletion of conveyors, chutes, and other devices. (Still WIP, not implemented).

#### Mouse:
- Middle mouse hold & drag: Rotates camera aroud focal point.
- Left mouse button: Selects an object as the current selection.
- Right mouse button: Opens a details popup window for objects that implement it.
- Mouse wheel scroll: If in Observe Mode, zoom camera closer/further from focal point.
                    If in Interact Mode and holding an object, moves object further or closer to you.
					
#### Pause Menu:
- Resume: Closes menu and unpauses the sim.
- Settings: Opens a menu allowing you to change graphics settings.
- Quit: To Main Menu exits back to the main menu.
      To Desktop exits the program.
	  
#### Useful console commands: 
Press the backtick/tilda `/~ key at any time to open the console.
- "stat fps" Show current fps and render time in ms.
- "t.maxfps <number>" Set a maximum fps (Use 999 to see unlocked framerate. It will be set at 120 by default.)
- "r.setres <XPixels>x<YPixels>" Set the window resolution. (If Window Mode is set to anything other than Fullscreen in the settings menu.)