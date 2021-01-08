![Pletenica](https://github.com/Pletenica/GenesisEngine/blob/master/Web/LogoPletenica++.png?raw=true)

### Must be known that Pletenica only have contributed and developed the particle system from this engine, the main core and other functionalities of this engine have been developed by Marc Pagès in his project Genesis Engine. We let the link to his repository below:

https://github.com/marcpages2020/GenesisEngine

### Pletenica have developed itself an engine too as a project but we have decided to use Marc's engine cause its better functionalities and advancements, although we will let the link to Overlevende Engine below:

https://github.com/Pletenica/Overlevende

# Overlevende's Particle System

This is the third assignment of a subject(Videogame Engines) from the UPC CITM University. This system have been developed by two students trying their best to learn and contribute to the developing of videogames. 
As said before you can find the two other assignments explained and done in the Pletenica's Overlevende Engine that consist of creating a simple geometry viewer supporting drag and drop files and orbital camera avoiding dependency from FBX for running our games, organize resources coherently and apply the minimal optimizations of a graphics engine.

# Pletenica's Members
![Josep](https://github.com/Pletenica/GenesisEngine/blob/master/Web/Pepote.png?raw=true)

* **Responsability:** Code
* **Github account:** daskza19(https://github.com/daskza19)

**Main work on:**
* Partical System Base.
* Own Format for the engine created.
* Particle system component window.
* Particle emitter.
* Transparency Map.
* Webpage content.

![Yuye](https://github.com/Pletenica/GenesisEngine/blob/master/Web/Yuye.png?raw=true)

* **Responsability:** Code and Webpage
* **Github account:** Rugiacreed(https://github.com/Rugiacreed)

**Main work on:**
* Particle Animation.
* Particle Save and Load.
* Webpage.
* Running loop smoke particles.
* Rocket Simulator particles.

# Main core sub-systems of Overlevende

### Note that the following sub-systems are developed at the Overlevende's release below and are not the same implemented in the GenesisEngine accompaying our particle system.

## How to use Overlevende Engine:

First of all you will want to identificate the menu bar in the engine, it has 3 drop down options that you can select by left clicking on one of them and moving around the
other. The first one, the “edit” menu will allow you to configure the engine at your own taste and exit the engine, with the new version of the engine you can use the 
following new options: open project and save project. The “help” menu can be used to look for the engine’s information like documentation, 
versions and user’s help. Finally the “Github” menu contains all the links to the contributors of these projects for more information, content and their own engine’s project.

![Menu Bar](https://github.com/Pletenica/Overlevende/blob/master/Readme%20images/MenuBar.PNG?raw=true)

Once you are inside the engine you will see at least 5 different windows, you should be able to identicate the scene window at first sight and the others windows will be 
explained later on. Every window is able to be moved wherever you want on the engine window or outside without affecting its performance. You can do this by selecting the 
title bar of the window with the left click of the mouse and drag the window into a new position.
If the window is inside the engines window you can hide the title bar of each window using the upper left arrow, if they are outside the engines window you can use the same 
button to minimize the entire window.



- **The configuration window:**
	You can open the configuration window to edit some features of the motor or see some performance data. One of the new and remarkable features is the theme and color 
	editor, we think you will enjoy the motor more if you can personalize the aesthetic of your working space with the help of our designers to avoid eye-damaging 
	creations.

	In the last version we have added the Time Configuration. This data will give you information about the motor like the time since the start-up, the time of the game
	this is running and other features. Some of this features will start from the time you start working in Overlevende but some of thesewssee are linked to the options
	window(see below).

![Configuration](https://raw.githubusercontent.com/Pletenica/Overlevende/master/Readme%20images/Configuration.PNG)

- **The scene window:**
	
	These will be where you will be working major of the time, so you can move around the camera using the mouse or the keyboard:
	* Mouse functionalities:
	Middle click and drag to move the camera around.
	Use the mouse wheel to get closer or further from an object.
	se right click and drag to turn the camera around.

	* Key functionalities:
	Use W/S to get closer or further in the scene.
	A/D will let you move left and right.
	F will focus your camera to the gameobject.
	While Right clicking, “WASD” fps-like movement and free look around is enabled.
	Shift will double the speed of movement.

	* Extra functionalities:
	You can use F1 to disable the grid in the scene window.
	You can use 0 to deselect every gameobject from the inspector.

	* Transformations functionalities:
	In the new version you can work with the gameobjects by editing them, you can control this by using the following controls:
		* 1 to enable the position gizmo, drag it to move the gameobject at your disered position.
		* 2 to enable the rotation gizmo, drag it to rotate the gameobject at your disered position.
		* 3 to enable the escale gizmo, drag it to escale the gameobject at your disered size.
		
	Note that you can modify any of these features in the inspector window too.
	

	You can drag a fbx to create a gameobject and see it in the scene, you can select this object and drop its texture too. If the model you import comes with textures 
	linked and they are in the same folder they will be imported at the same time as the fbx. Be aware that Overlevende shares some default assets to work with in the folder 
	“Assets” on files folder.
	Note that, if a gameobjects contanis different meshes this ones will be added as a children of the main gameobject, you can select and edit every gameobject that have a
	mesh independently, this feature has been added to the last version of overlevende's engine.

![Windows](https://github.com/Pletenica/Overlevende/blob/master/Readme%20images/windows.PNG?raw=true)

- **Hierarchy window:**
	This is a simple window where you will see every game object, scene and components of your work. You can open tree groups to select every part of it.
	With the version Overlevende Engine 0.7 yo have some option you will want to know before working with this window: the first one is that you can create empty objects in
	the scene, then you have the option to create an empty object inside an existing gameobject that you have selected, finally be careful with the clear option because it 
	will delete all the gameobjects from the scene or root.
	Knowing this features you wll want to youse too the drag and reaprent feature that will help you making more agile your work, you can select and delete from the hierarchy 
	too.

- **Options window:**
	This window will help the user to take short cuts and make some actions when working with Overlevende: add primitive objects, enable or disable some options on 
	the scene window.
	Now we have added to more enable/disable options: the AABB and OBB drawing that can help you when working with bounding boxes. 
	
	The scene options are:
	* The play button: this will save a temporary scene and start a timer for the game running.
	* Pause button: will pause the temporary scene and timer.
	* Stop button: this will reset the temporary scene to the initial scene and reset the game timing.
	* World/Local option: this feature will allow to make a toggle to move and edit the gameobjects among local or global coordinates.
	
	These new options have been added to the Overlevende Engine v0.7.

- **Inspector window:**
	This window shows you all the information to work with your gameobjects, by selecting your gameobject it will display its options like renaming the gameobject. 
	You can delete game objects from there too if necessary.

	Now with the new version of the engine you can modify the position, the rotation and the scale of every game object in the scene. You can drag every coordinate to
	change it or just introduce the desired value. For the camera's options note the you can change the priority, enable or disable de culling and edit some more options 
	for the Frustum Culling feature.

- **Resource Windows:**
	This window will display all the resources used in the scene.

![Inspector](https://github.com/Pletenica/Overlevende/blob/master/Readme%20images/inspector.PNG?raw=true)

- **Console:**
	The console window shows errors, warnings and other messages generated by Overlevende. This will help you while working with the engine like showing some LOGs while 
	creating meshes.

# Additional features in Overlevende Engine:

* We have added some interface themes, that was when we discovered ImGui and although is not hard code we think its good for the user to have a variety of interfaces colors 
to adapt at their necessities and make a better experience. So you will be able to change the base colors of the engine in a dark, light and bright theme and a few colors for
the active window and buttons.

* The camera of the main scene is linked to the scene window, so you can work with the scene in any position you like more and that’s a helpful tool.

* The option window has different new functionalities: for the game objects you can change to depth sight, activate the cull face, see or unsee the textures, the wireframe 
or normals. For the entire scene you can enable or disable the light too.

![Options](https://github.com/Pletenica/Overlevende/blob/master/Readme%20images/options.PNG?raw=true)

* With the version 0.7 the cameras have been added and modified as a gameobjects. These have the priority feature that will allow the user to enable a priority organitzation 
within them for a better control of the Frustum Culling option. The scene will manage the priorities doing the FC of the camera with more priority allowing you to play with 
different cameras in the game easily.

# Particle System: How it works

![Animation](https://github.com/Pletenica/GenesisEngine/blob/master/Web/inGame.gif?raw=true)

## Creating Particles
First of all you will have to create a new gameobject from the window Game Object, once created you will have to add a component of Particle system in the inspector of that gameobject. The Particle System consist basically on two parts: the base particle and the emitter. So in the inspector, aside from the gameobject name and the transform components you will have the Particle System component.

## The Particle System Component

It's important to know that in the very first moment when you add a particle component this will be disabled, you can still work with it and edit the emitter and particle but you will no see any change or feedback from the editor or game scene. We thought this could help to make the scene lighter when working wioth a lot of assets.
Then we have the Show Configuration Window option that will open the tools to edit our particles and emitters explained below. Finally we will have four options to Save/Load particles.
![Inspector](https://github.com/Pletenica/GenesisEngine/blob/master/Web/InspectorParticle.PNG?raw=true)

## Configuration Window
![Animation](https://github.com/Pletenica/GenesisEngine/blob/master/Web/editorGIF.gif?raw=true)

The Configuration Window is divided by particle options and emitter options. Don't forget to name the particles and the emitters and saving them by **pressing enter** and clicking on the save options in the inspector.
### Particles
**Particle Texture:**
This window allows you to import and add a texture for your particles, althought you have a default texture to work with particles without needing new ones. Remember you can use animations by importing the spritesheet as a texture and using the slides of columns and rows to mark the sprites. Then if you use animation you can edit the time between frames too.
![Animation](https://github.com/Pletenica/GenesisEngine/blob/master/Web/particle%20animation.PNG?raw=true)

**Initial and Final State:**
If you don't use animation you can edit the life of the particle by changing the color and size in the initial state and final state and it gradually will change during its lifetime.
![Paricles](https://github.com/Pletenica/GenesisEngine/blob/master/Web/Particleeditor.PNG?raw=true)

### Emitters
**Emitter form:**
You will have four main options to create your emitter, these consist of: sphere, semisphere, cone, circle. And depending of the form of your emitter you will be able to edit differents components.

**Loop:**
This window edits the main functionality of the emitter. You can edit time of spawning particles, they lifetime, number of particles spawned, their speed and some showing options for the emitter and its AABB.

![Emitters](https://github.com/Pletenica/GenesisEngine/blob/master/Web/emittereditor.PNG?raw=true)

# Resources
### Overlevende Core Repository
 - **Repository:** https://github.com/Pletenica/Overlevende
 - **Last Release:** https://github.com/Pletenica/Overlevende/releases/tag/v0.7

### Overlevende's Particle System
 - **Repository:** https://github.com/Pletenica/GenesisEngine
 - **Last Release:** 

# License
### Copyright 2020 Josep Sànchez Arbona and Roger Pérez Romera.

### Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

### The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

### THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
