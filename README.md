# INTRO #

This project is the "v2" of the CommsFramework engine, a previous game engine that I was working on. This version is intended to be better built and more easily workably.

This project has 2 primary goals : 

First to be easy to use, creating an instance of the game engine and drawing an image to the screen should take no more than 5 lines of code. The engine will have sensible defaults that should work for a basic case.

Secondly it will be flexible. The choice of the graphics renderer should be left open, the game will work with abstract classes and the backing renderer can be switched easily.