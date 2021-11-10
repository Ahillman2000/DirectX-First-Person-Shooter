#pragma once
class KeyboardEvent
{
public:
	enum EventType
	{
		Press,
		Release,
		Invalid
	};

	KeyboardEvent();
	KeyboardEvent(const EventType type, const unsigned char key);
	bool IsPressed() const;
	bool IsReleased() const;
	bool isValid() const;
	unsigned char GetKeyCode() const;

private:
	EventType type;
	unsigned char key;
};

