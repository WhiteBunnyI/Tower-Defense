#pragma once

#include <tuple>

class BaseCoroutine
{
protected:
	float m_timer;
	friend class Engine;
	virtual bool Tick(float deltaTime) = 0;

public:
	BaseCoroutine(float timer) : m_timer{ timer } {}
	virtual void Start() = 0;

};

template<typename... Args>
class Coroutine : public BaseCoroutine
{
	std::tuple<Args...> m_data;
	void (*m_func)(Coroutine&);
	bool Tick(float deltaTime) override
	{
		m_timer -= deltaTime;

		if (m_timer <= 0.f)
		{
			std::cout << "Coroutine" << std::endl;
			m_func(*this);
			return true;
		}
		return false;
	}

public:
	Coroutine(void (*func)(Coroutine&), float sec, Args... args) : BaseCoroutine(sec), m_data(args...), m_func{ func } { }
	void Start() override
	{
		Engine::instance->m_coroutines.push_back(this);
	}


	template<std::size_t index>
	auto get() -> decltype(std::get<index>(m_data))
	{
		return std::get<index>(m_data);
	}
};

#include <Engine.hpp>
