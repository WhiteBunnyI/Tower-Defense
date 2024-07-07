#pragma once



struct BaseEventHolder
{
	virtual void Call(sf::Event& event) = 0;
};

template<typename... Args>
struct EventHolder : BaseEventHolder
{
	void (*func)(sf::Event&, EventHolder&);					//���� �-��, ������� ����� �������� ��� ���������
	std::tuple<Args...> data;								//������, ������� �� ����� ������������ � ���� �������

	EventHolder(void (*whatToCall)(sf::Event&, EventHolder&), Args... args) : func{whatToCall}, data{args...}
	{
		Engine::instance->m_events.push_back(this);
	}

	~EventHolder()
	{
		Engine::instance->m_events.remove(this);
	}

	template<std::size_t Index>
	auto get() -> decltype(std::get<Index>(data)) {
		return std::get<Index>(data);
	}

	void Call(sf::Event& event) override
	{
		func(event, *this);
	}
};

