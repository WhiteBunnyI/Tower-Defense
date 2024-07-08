#pragma once

#include <tuple>

class BaseCoroutine
{
protected:
	bool m_deleteAfterUse;
	bool m_isStarted;
	float m_timer;
	float m_specTimer;
	friend class Engine;
	virtual bool Tick(float deltaTime) = 0;

public:
	BaseCoroutine(float timer, bool deleteAfterUse = true) : m_specTimer{ timer }, m_timer{ 0 }, m_isStarted { false }, m_deleteAfterUse{ deleteAfterUse } {}

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
			m_func(*this);
			return true;
		}
		return false;
	}

public:
	Coroutine(void (*func)(Coroutine&), float sec, Args... args, bool deleteAfterUse = true) : BaseCoroutine(sec, deleteAfterUse), m_data(args...), m_func{ func } { }

	~Coroutine()
	{
		if(m_isStarted)
			Engine::instance->m_coroutines.remove(this);
	}

	void Start() override
	{
		m_timer = m_specTimer;
		m_isStarted = true;
		Engine::instance->m_coroutines.push_back(this);
	}


	template<std::size_t index>
	auto get() -> decltype(std::get<index>(m_data))
	{
		return std::get<index>(m_data);
	}
};

#include <Engine.hpp>
