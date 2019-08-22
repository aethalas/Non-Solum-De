#pragma once
#include "vector2D.h"

enum EventType{EVENT_NONE, EVENT_EXPLOSION, EVENT_NEWOBJECT, EVENT_OBJECTDESTROYED, EVENT_ITEMPICKUP};


class GameObject;

struct Event
{
	GameObject* pSource;
	EventType type;
	Vector2D position;
	float data1;
	float data2;
};