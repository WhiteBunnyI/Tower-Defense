#include <Engine.hpp>

Engine::Engine(int gameWidth, int gameHeight) : m_gameHeight{ gameHeight }, m_gameWidth{ gameWidth }, m_view{nullptr}, m_window{nullptr}
{
	if (Engine::instance != nullptr)
	{
		std::cerr << "Engine already exist!" << std::endl;
		throw new std::runtime_error("Trying create a new engine!");
	}
	Engine::instance = this;
}

bool Engine::IsPlaying()
{
	return isPlaying;
}

void Engine::UpdateView()
{
	m_window->setView(*m_view);
}


void Engine::CrankUp()
{
	isPlaying = true;
	sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(m_gameWidth), static_cast<unsigned int>(m_gameHeight), 32), "Tower Defense",
		sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	m_window = &window;

	m_view = new sf::View(sf::Vector2f(m_gameWidth / 2.f, m_gameHeight / 2.f), sf::Vector2f(m_gameWidth, m_gameHeight));
	window.setView(*m_view);

	//Start Invoke
	for (auto iterStart = m_start.begin(); iterStart != m_start.end(); ++iterStart)
	{
		(*iterStart)->Start();
	}

	sf::Clock clock;
	
	while (window.isOpen())
	{
		// Handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Window closed or escape key pressed: exit
			if ((event.type == sf::Event::Closed) ||
				((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
			{
				window.close();
				break;
			}

			//Event Invoke
			for (auto iter = m_events.begin(); iter != m_events.end(); ++iter)
			{
				(*iter)->Call(event);
			}

		}

		if (isPlaying)
		{
			float deltaTime = clock.restart().asSeconds();

			//Coroutines Invoke
			for (auto iterCoroutine = m_coroutines.begin(); iterCoroutine != m_coroutines.end(); ++iterCoroutine)
			{
				if ((*iterCoroutine)->Tick(deltaTime))
				{
					iterCoroutine = m_coroutines.erase(iterCoroutine);
					if (iterCoroutine == m_coroutines.end())
						break;
					if (iterCoroutine != m_coroutines.begin())
						--iterCoroutine;
				}

			}

			//Update Invoke
			for (auto iter = m_update.begin(); iter != m_update.end(); ++iter)
			{
				(*iter)->Update();
			}
		}

		window.clear();

		//Render Invoke
		if (!m_render.empty())
		{
			for (auto iter = m_render.begin(); iter != m_render.end(); ++iter)
			{
				auto p = (*iter)->render;
				if(p != nullptr)
					window.draw(*p);
			}
		}
		window.display();


	}
}