#pragma once
#include <functional>
#include <map>
#include <vector>

//
#include <iostream>

class Game;
class GLFWwindow;

#pragma region macro
#define S(...) __VA_ARGS__

#define EVENTHANDLEREVENT(NAME, ARGS, ARGS_NAMES)\
protected:\
	std::map<void*, void(*)(Game *game, ARGS)> NAME##Handlers;\
	void Remove##NAME##Callback(void *source)\
	{\
		NAME##Handlers.erase(source);\
	}\
public:\
	void Add##NAME##Callback(void *source, void(*callback)(Game *game, ARGS))\
	{\
		NAME##Handlers.insert(std::pair<void*, void(*)(Game *game, ARGS)>(source, callback));\
	}\
	void NAME##Callback(Game *game, ARGS)\
	{\
		for(auto i : NAME##Handlers)\
		{\
			i.second(game, ARGS_NAMES);\
		}\
		for (auto i : children)\
		{\
			i->##NAME##Callback(game, ARGS_NAMES);\
		}\
	}
#pragma endregion 

class EventHandler
{
protected:
	EventHandler *parent;
	std::vector<EventHandler*> children;

	void AddEventHandlerChild(EventHandler *child);
	void RemoveEventHandlerChild(EventHandler *child);
public:
	EventHandler();
	EventHandler(EventHandler *parent);
	~EventHandler();

	void RemoveCallbacks(void *source);

#pragma region events
	EVENTHANDLEREVENT(Error,        S(const char *source, const char *description),                      S(source, description))
#pragma region input events
#ifdef CLIENT
	EVENTHANDLEREVENT(MouseButton,  S(GLFWwindow *window, int button, int action, int mods),             S(window, button, action, mods))
	EVENTHANDLEREVENT(CursorPos,    S(GLFWwindow *window, int x, int y),                                 S(window, x, y))
	EVENTHANDLEREVENT(CursorEnter,  S(GLFWwindow *window, int entered),                                  S(window, entered))
	EVENTHANDLEREVENT(Scroll,       S(GLFWwindow *window, int xOffset, int yOffset),                     S(window, xOffset, yOffset))
	EVENTHANDLEREVENT(Key,          S(GLFWwindow *window, int key, int scancode, int action, int mods),  S(window, key, scancode, action, mods))
	EVENTHANDLEREVENT(Char,         S(GLFWwindow *window, unsigned int character),                       S(window, character))
#endif
#pragma endregion
#pragma endregion
};