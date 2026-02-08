#pragma once

#include <string>
#include <ostream>

namespace DGE {
	enum class EventType {
		KeyRelease,
		KeyPress
	};

	class Event {
	public:
		Event() : handled(false) {}
		virtual ~Event() = default;


		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		//virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }
		bool handled;
	};

	class EventDispatcher {
	public:
		EventDispatcher(Event& e) : e_(e)  {}
		~EventDispatcher() {}

		template <typename T, typename F>
		bool dispatch(const F& func) 
		{
			if (e_.GetEventType() == T::getStaticType())
			{
				e_.handled |= func(static_cast<T&>(e_));
				return true;
			}
			return false;
		}

	private:
		Event& e_;
	};

#define EVENT_OVERRIDE_VIRTUAL_FUNCTIONS(type) 		\
	static EventType getStaticType() {return EventType::type;} \
	virtual EventType GetEventType()  const override { return EventType::type; }\
	virtual const char* GetName()  const override {return #type;}\
	//virtual int GetCategoryFlags() const = 0;

	class KeyEvent : public Event {
	public:
		KeyEvent(int keycode) : keycode_(keycode) {}
		virtual ~KeyEvent() override = default;

		virtual EventType GetEventType()  const override= 0;
		virtual const char* GetName()  const override= 0;

		int getKeyCode() const { return keycode_; }

	private:
		int keycode_;
	};

	class KeyPressEvent : public KeyEvent {
	public:
		KeyPressEvent(int keycode) : KeyEvent(keycode) {}
		~KeyPressEvent() override = default;

		EVENT_OVERRIDE_VIRTUAL_FUNCTIONS(KeyPress);

	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}


}