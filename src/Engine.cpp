#include <Engine.hpp>

Engine::Engine(int gameWidth, int gameHeight) : 
	m_gameHeight{ gameHeight }, 
	m_gameWidth{ gameWidth }, 
	m_view{ new sf::View(sf::Vector2f(m_gameWidth / 2.f, m_gameHeight / 2.f), sf::Vector2f(m_gameWidth, m_gameHeight)) },
	m_window{ new sf::RenderWindow(sf::VideoMode(static_cast<unsigned int>(m_gameWidth), static_cast<unsigned int>(m_gameHeight), 32), "Tower Defense",
		sf::Style::Titlebar | sf::Style::Close) },
	deltaTime{0},
	threadPool{4}
{
	if (Engine::instance != nullptr)
	{
		std::cerr << "Engine already exist!" << std::endl;
		throw new std::runtime_error("Trying create a new engine!");
	}
	Engine::instance = this;
	m_window->setVerticalSyncEnabled(true);
	m_window->setView(*m_view);
}

bool Engine::IsPlaying()
{
	return isPlaying;
}

void Engine::UpdateView()
{
	m_window->setView(*m_view);
}

Engine::~Engine()
{
	delete m_view;
	delete m_window;
	ClearList(m_update);
	ClearList(m_coroutines);
	ClearList(m_events);
	ClearList(m_start);
	ClearList(m_manualRender);
	ClearList(m_render);
	ClearList(m_textures);
}


void Engine::CrankUp()
{
	isPlaying = true;

	//Start Invoke
	for (auto iterStart = m_start.begin(); iterStart != m_start.end(); ++iterStart)
	{
		(*iterStart)->Start();
	}

	sf::Clock clock;
	
	while (m_window->isOpen())
	{
		// Handle events
		sf::Event event;
		while (m_window->pollEvent(event))
		{
			// Window closed or escape key pressed: exit
			if ((event.type == sf::Event::Closed) ||
				((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
			{
				m_window->close();
				isPlaying = false;
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
			deltaTime = clock.restart().asSeconds();

			//Coroutines Invoke
			for (auto iterCoroutine = m_coroutines.begin(); iterCoroutine != m_coroutines.end(); ++iterCoroutine)
			{
				START:
				if ((*iterCoroutine)->Tick(deltaTime))
				{
					(*iterCoroutine)->m_isStarted = false;
					if ((*iterCoroutine)->m_deleteAfterUse)
						delete (*iterCoroutine);

					iterCoroutine = m_coroutines.erase(iterCoroutine);

					if (iterCoroutine == m_coroutines.end())
						break;
					if (iterCoroutine == m_coroutines.begin())
						goto START;
					--iterCoroutine;
				}

			}

			//Update Invoke
			for (auto iter = m_update.begin(); iter != m_update.end(); ++iter)
			{
				(*iter)->Update();
			}
			m_window->clear();

			//Render Invoke
			if (!m_render.empty())
			{
				for (auto iter = m_render.begin(); iter != m_render.end(); ++iter)
				{
					auto p = (*iter)->render;
					if(p != nullptr)
						m_window->draw(*p);
				}

				for (auto iter = m_manualRender.begin(); iter != m_manualRender.end(); ++iter)
				{
					auto p = (*iter);
					if (p != nullptr)
						m_window->draw(*p);
				}
			}
			m_window->display();
		}



	}
}