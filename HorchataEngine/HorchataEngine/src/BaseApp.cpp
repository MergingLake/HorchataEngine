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
    m_windowPtr->handleEvents();
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

  m_waypoints = {
    EngineMath::Vector2(510.f, 22.f),
    EngineMath::Vector2(1190.f, 22.f),
    EngineMath::Vector2(1190.f, 400.f),
    EngineMath::Vector2(750.f, 400.f),
		EngineMath::Vector2(750.f, 625.f),
		EngineMath::Vector2(1375.f, 625.f),
		EngineMath::Vector2(1375.f, 875.f),
		EngineMath::Vector2(950.f, 875.f),
		EngineMath::Vector2(900.f, 825.f),
		EngineMath::Vector2(700.f, 825.f),
		EngineMath::Vector2(650.f, 875.f),
		EngineMath::Vector2(510.f, 875.f),
		EngineMath::Vector2(510.f, 500.f),
  };

  m_currentWaypoint = 0;

	// create circle actor
	m_ACircle = EngineUtilities::MakeShared<Actor>("Player Actor");
  if(m_ACircle) {
		m_ACircle->getComponent<CShape>()->createShape(ShapeType::RECTANGLE);
		m_ACircle->getComponent<CShape>()->setFillColor(sf::Color::White);
		m_ACircle->getComponent<Transform>()->setPosition(EngineMath::Vector2(510.f, 500.f));
		m_ACircle->getComponent<Transform>()->setScale(EngineMath::Vector2(1.f, 2.f));
		//m_ACircle->setName("CircleActor");

    if(!resourceMan.loadTexture("Sprites/Mario", "png")) {
      MESSAGE("BaseApp","init","Can't load the texture");
		}
    m_ACircle->setTexture(resourceMan.getTexture("Sprites/Mario"));
	}
  else {
    ERROR("BaseApp",
      "init",
      "Failed to create Circle Actor, check memory allocation");
    return false;
  }

	m_ATrack = EngineUtilities::MakeShared<Actor>("Track Actor");
  if (m_ATrack) {
    m_ATrack->getComponent<CShape>()->createShape(ShapeType::RECTANGLE);
    m_ATrack->getComponent<CShape>()->setFillColor(sf::Color::White);
    m_ATrack->getComponent<Transform>()->setPosition(EngineMath::Vector2(500.f, 50.f));
    m_ATrack->getComponent<Transform>()->setScale(EngineMath::Vector2(10.f, 20.f));

    if(!resourceMan.loadTexture("Sprites/Rainbow_Road", "png")) {
      MESSAGE("BaseApp", "init", "Can't load the texture");
		}
    m_ATrack->setTexture(resourceMan.getTexture("Sprites/Rainbow_Road"));
  }
  else {
    ERROR("BaseApp",
      "init",
      "Failed to create Track Actor, check memory allocation");
    return false;
  }

  return true;
}

void
BaseApp::update() {
  if (!m_windowPtr.isNull()) {
    m_windowPtr->update();
  }
  ImGui::ShowDemoWindow();

  if (!m_ACircle.isNull() && !m_waypoints.empty()) {
    m_ACircle->update(m_windowPtr->deltaTime.asSeconds());

  if(!m_ATrack.isNull()) {
      m_ATrack->update(m_windowPtr->deltaTime.asSeconds());
	}

    // Get current target waypoint
    EngineMath::Vector2 targetPos = m_waypoints[m_currentWaypoint];

    // Move towards the current waypoint
    m_ACircle->getComponent<Transform>()->seek(
      targetPos, 200.f, m_windowPtr->deltaTime.asSeconds(), 10.f);

    // Check if close enough to the waypoint to advance
    EngineMath::Vector2 currentPos = m_ACircle->getComponent<Transform>()->getPosition();
    float distance = EngineMath::Vector2::distance(currentPos, targetPos);
    if (distance < 10.f && m_currentWaypoint < 12) {
      m_currentWaypoint = (m_currentWaypoint + 1); // Loop waypoints
    }
  }
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

  if (!m_ACircle.isNull()) {
		m_ACircle->getComponent<CShape>()->render(m_windowPtr);
  }

	m_windowPtr->render();
  m_windowPtr->display();
}

void
BaseApp::destroy() {
	//m_shapePtr.reset(); // Release the shape pointer
  //m_window->destroy();
}
