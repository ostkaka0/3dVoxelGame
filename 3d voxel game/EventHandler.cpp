#include "EventHandler.h"

EventHandler::EventHandler()
	: parent(nullptr)
{
}

EventHandler::EventHandler(EventHandler *parent)
	: parent(parent)
{
	parent->AddEventHandlerChild(this);
}

EventHandler::~EventHandler()
{
	if (parent)
		parent->RemoveEventHandlerChild(this);
}


#pragma region protected
	void EventHandler::AddEventHandlerChild(EventHandler *child)
	{
		children.push_back(child);
	}

	void EventHandler::RemoveEventHandlerChild(EventHandler *child)
	{
		for (auto c = children.begin(); c != children.end(); ++c)
		{
			if (*c == child)
			{
				children.erase(c);
				break;
			}
		}
	}
#pragma endregion

#pragma region public
void EventHandler::RemoveCallbacks(void *source)
{
#pragma region events
	RemoveErrorCallback(source);
#pragma region input events
#ifdef CLIENT
	RemoveMouseButtonCallback(source);
	RemoveCursorPosCallback(source);
	RemoveCursorEnterCallback(source);
	RemoveScrollCallback(source);
	RemoveKeyCallback(source);
	RemoveCharCallback(source);
#endif
#pragma endregion
#pragma endregion
}
#pragma endregion