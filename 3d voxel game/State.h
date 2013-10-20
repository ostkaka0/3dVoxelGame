class State
{
public:
	virtual void Display()=0;
	virtual State *Idle()=0;
	virtual void Reshape(int w, int h)=0;
	virtual void Mouse(int button, int state, int x, int y)=0;
	virtual void KeyboardKeyboard(unsigned char c, int x, int y)=0;
};