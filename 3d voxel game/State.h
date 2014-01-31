#pragma once
class Game;
class IRenderer;

class State
{
public:
	virtual void Draw(Game *game, IRenderer *renderer)=0;
	virtual void Update(Game *game)=0;
	//virtual void Reshape(int w, int h)=0;
	//virtual void Mouse(int button, int state, int x, int y)=0;
	//virtual void KeyboardKeyboard(unsigned char c, int x, int y)=0;
};