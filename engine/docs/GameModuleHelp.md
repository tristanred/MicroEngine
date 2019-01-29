# Creating a Game Module

## (What)
A Game Module is the basic building block for a game. It contains information 
necessary to manage a module of a game. GameModules usually used to contain a 
part of a game like the Battle system or a level or maybe the inventory screen. 
Any part of the game that can be loaded/unloaded and managed as a single unit 
can be a game module.

## (Why)
The GameModule class exists to facilitate the development of "modules", parts of the game that are distinct from each other. A GameModule groups all objects of a part of the game together and helps the programmer maintain separation of concerns over parts of the game. 

## (How)
To create a Game Module, simply create a class that Extends from GameModule.
Several methods of the base class can be overridden, Update and Draw are the 
most common. The GameModule must implement its constructor to accept a 
GameEngine pointer, that pointer can be kept for later to access the GameEngine
class.

Here is a simply template for a GameModule :

```
class ModuleName : public GameModule
{
public:
    ModuleName(GameEngine* engine);
    virtual ~ModuleName();

    void Update(unsigned int deltaTime) override;
    void Draw(ARenderer* renderer) override;
};
```

A GameModule can be created like this : 

```
GameModule* mod = engine->CreateModule<GameTestModule>();
```

giving the GameModule type in the template parameter of the CreateModule method.