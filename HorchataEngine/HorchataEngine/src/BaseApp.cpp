#include <BaseApp.h>
#include <ResourceManager.h>

BaseApp::~BaseApp() {}

int
BaseApp::run() {
  if (!init()) {
    ERROR("BaseApp", "run",
      "Initializes result on a false statement, check method validations");
  }

  while (m_windowPtr->isOpen()) {
    m_windowPtr->handleEvents(m_engineGUI);
    update();
    render();
  }

  destroy();
  return 0;
}

bool
BaseApp::init() {
	ResourceManager& resourceMan = ResourceManager::getInstance();

	m_windowPtr = EngineUtilities::MakeShared<Window>(1920, 1080, "Horchata Engine");
  if (!m_windowPtr) {
    ERROR("BaseApp", 
          "init", 
          "Failed to create window pointer, check memory allocation");
    return false;
	}

	m_engineGUI.init(m_windowPtr);

	m_waypoints = {
		EngineMath::Vector2(510.f, 22.f),
		EngineMath::Vector2(850.f, 22.f),
		EngineMath::Vector2(1190.f, 22.f),
		EngineMath::Vector2(1190.f, 200.f),
		EngineMath::Vector2(1190.f, 400.f),
		EngineMath::Vector2(1050.f, 400.f),
		EngineMath::Vector2(900.f, 400.f),
		EngineMath::Vector2(750.f, 400.f),
		EngineMath::Vector2(750.f, 525.f),
		EngineMath::Vector2(750.f, 625.f),
		EngineMath::Vector2(1050.f, 625.f),
		EngineMath::Vector2(1375.f, 625.f),
		EngineMath::Vector2(1375.f, 750.f),
		EngineMath::Vector2(1375.f, 875.f),
		EngineMath::Vector2(1150.f, 875.f),
		EngineMath::Vector2(950.f, 875.f),
		EngineMath::Vector2(900.f, 825.f),
		EngineMath::Vector2(700.f, 825.f),
		EngineMath::Vector2(650.f, 875.f),
		EngineMath::Vector2(510.f, 875.f),
		EngineMath::Vector2(510.f, 700.f),
		EngineMath::Vector2(510.f, 500.f),
	};

	m_Aplayer = EngineUtilities::MakeShared<APlayer>("Player");
	if (m_Aplayer) {
		m_Aplayer->getComponent<CShape>()->createShape(ShapeType::RECTANGLE);
		m_Aplayer->getComponent<CShape>()->setFillColor(sf::Color::White);
		m_Aplayer->getComponent<Transform>()->setPosition(m_waypoints.back());
		m_Aplayer->getComponent<Transform>()->setScale(EngineMath::Vector2(1.f, 2.f) / 3.f);

		if (!resourceMan.loadTexture("Sprites/Mario", "png")) {
			MESSAGE("BaseApp", "init", "Can't load the texture");
		}
		m_Aplayer->setTexture(resourceMan.getTexture("Sprites/Mario"));
		m_actors.push_back(m_Aplayer);
	}
	else {
		ERROR("BaseApp", "init", "Failed to create Player Actor, check memory allocation");
		return false;
	}

	const std::vector<std::string> botTextures = {
			"Sprites/Luigi",
			"Sprites/Luigi",
			"Sprites/Luigi",
			"Sprites/Luigi",
			"Sprites/Luigi"
	};

	for (int i = 0; i < 5; ++i) {
		EngineUtilities::TSharedPointer<ARacer> racer = EngineUtilities::MakeShared<ARacer>("Bot " + std::to_string(i + 1));
		if (racer) {
			racer->getComponent<CShape>()->createShape(ShapeType::RECTANGLE);
			racer->getComponent<CShape>()->setFillColor(sf::Color::White); // Rojo semi-transparente
			racer->getComponent<Transform>()->setPosition(m_waypoints.back() - EngineMath::Vector2(0, (i + 1) * 30.f));
			racer->getComponent<Transform>()->setScale(EngineMath::Vector2(1.f, 2.f) / 3.f);

			// Cargar y asignar textura única para cada bot
			if (!resourceMan.loadTexture(botTextures[i], "png")) {
				MESSAGE("BaseApp", "init", "Can't load the bot texture: " + botTextures[i]);
			}
			racer->setTexture(resourceMan.getTexture(botTextures[i]));

			// Añade el Steering Behavior de PathFollowing
			racer->addSteeringBehavior(EngineUtilities::MakeShared<PathFollowing>(m_waypoints));

			m_Aracers.push_back(racer);
			m_actors.push_back(racer);
		}
		else {
			ERROR("BaseApp", "init", "Failed to create Racer Actor, check memory allocation");
			return false;
		}
	}

	m_ATrack = EngineUtilities::MakeShared<Actor>("Track Actor");
	if (m_ATrack) {
		m_ATrack->getComponent<CShape>()->createShape(ShapeType::RECTANGLE);
		m_ATrack->getComponent<CShape>()->setFillColor(sf::Color::White);
		m_ATrack->getComponent<Transform>()->setPosition(EngineMath::Vector2(500.f, 50.f));
		m_ATrack->getComponent<Transform>()->setScale(EngineMath::Vector2(10.f, 20.f));

		if (!resourceMan.loadTexture("Sprites/Rainbow_Road", "png")) {
			MESSAGE("BaseApp", "init", "Can't load the texture");
		}
		m_ATrack->setTexture(resourceMan.getTexture("Sprites/Rainbow_Road"));
		m_actors.push_back(m_ATrack);
	}
	else {
		ERROR("BaseApp", "init", "Failed to create Track Actor, check memory allocation");
		return false;
	}

	m_gameManager = EngineUtilities::MakeShared<GameManager>();
	if (m_gameManager) {
		m_gameManager->init(m_ATrack, m_waypoints);
	}
	else {
		ERROR("BaseApp", "init", "Failed to create GameManager, check memory allocation");
		return false;
	}

	return true;
}

void
BaseApp::update() {
  if (!m_windowPtr.isNull()) {
		m_windowPtr->update();
	}
	
	// Actualizar el game manager y los actores
	m_gameManager->update(m_windowPtr->deltaTime.asSeconds(), m_Aracers, m_Aplayer);

	for (const auto& actor : m_actors) {
		if (actor) {
			actor->update(m_windowPtr->deltaTime.asSeconds());
		}
	}

	m_engineGUI.update(m_windowPtr, m_windowPtr->deltaTime);
	m_engineGUI.outliner(m_actors);
	m_engineGUI.inspector(m_actors);
	//ImGui::ShowDemoWindow();
}

void
BaseApp::render() {
  if (!m_windowPtr) {
    return;
    //m_windowPtr->draw(*m_shapePtr);
  }

  m_windowPtr->clear();

  if(!m_ATrack.isNull()) {
    m_ATrack->getComponent<CShape>()->render(m_windowPtr);
	}

	if (!m_Aplayer.isNull()) {
		m_Aplayer->getComponent<CShape>()->render(m_windowPtr);
	}

	for (const auto& racer : m_Aracers) {
		if (!racer.isNull()) {
			racer->getComponent<CShape>()->render(m_windowPtr);
		}
	}

	m_gameManager->renderHUD(m_windowPtr);
	m_windowPtr->render();
  m_engineGUI.render(m_windowPtr);
  m_windowPtr->display();
}

void
BaseApp::destroy() {

  m_engineGUI.destroy();
	//m_shapePtr.reset(); // Release the shape pointer
  //m_window->destroy();
}
