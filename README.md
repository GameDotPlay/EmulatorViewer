# EmulatorViewer (WIP)
 
This is an application I developed in Unreal Engine 5.1 as a proof of concept for a physics based emulation or HMI software to interact with a wide range of material handling systems.
The plan is for this app is to be able to serve as an emulator environment to enable automated and repeatable testing scenarios by creating models that represent layouts and devices in the field that can provide mock inputs/outputs to any controllers, as well as collection and display of any metrics/statistics relevant to the system. In addition to the emulator functionality, it could also serve in a passive HMI/SCADA role presenting fault and statistics data to the user and allowing supervisory control of the system to the user.
Communication to controllers would be over OPC.

The project is very early in development and still very much in the prototyping stage.

Currently implemented:
 - Physics-based conveyor belts that correctly simulate friction locomotion of items on a conveyor belt. Straight (Level, incline, decline) and 90 degree turns available.
 - Customizable item spawner that allows the user to spawn new items onto a conveyor with a variety of settings to control the spawn rate and size of items, as well as introducing randomness to these factors.
 - "Interact Mode" which allows users to "grab" any physics item in the scene and manipulate it for finer control of placement or remove it from the system. 
 - Free movement of the camera within a scene with the ability to rotate, zoom, and snap-to focus on selected objects.

## Main Menu
### Sandbox
### Settings

## Main Scene

### Controls
### Conveyors
### Item Spawner