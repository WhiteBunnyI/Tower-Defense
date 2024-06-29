#include <Engine.hpp>

Engine::Engine() : map{Vector2(200,200)}
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


void Engine::CrankUp(int gameWidth, int gameHeight)
{
	sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(gameWidth), static_cast<unsigned int>(gameHeight), 32), "Tower Defense",
		sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	for (auto iterStart = m_gameObjects.begin(); iterStart != m_gameObjects.end(); ++iterStart)
	{
		iterStart->Start();
	}

	sf::Clock clock;
	isPlaying = true;
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

		}

		if (isPlaying)
		{
			float deltaTime = clock.restart().asSeconds();
			for (auto iterCoroutine = m_coroutines.begin(); iterCoroutine != m_coroutines.end(); ++iterCoroutine)
			{
				if (iterCoroutine->Tick(deltaTime))
				{
					iterCoroutine = m_coroutines.erase(iterCoroutine);
					if (iterCoroutine == m_coroutines.end())
						break;
					if (iterCoroutine != m_coroutines.begin())
						--iterCoroutine;
				}

			}
		}

		window.clear();
		if (!m_drawable.empty())
		{
			for (auto iter = m_drawable.begin(); iter != m_drawable.end(); ++iter)
			{
				if (*iter != nullptr)
					window.draw(**iter);
			}
		}
		window.display();


	}
}