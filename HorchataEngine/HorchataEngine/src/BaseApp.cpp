#include <BaseApp.h>

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
	m_windowPtr = EngineUtilities::MakeShared<Window>(1920, 1080, "Horchata Engine");
  if (!m_windowPtr) {
    ERROR("BaseApp", 
          "init", 
          "Failed to create window pointer, check memory allocation");
    return false;
	}

  m_waypoints = {
    EngineMath::Vector2(200.f, 150.f),
    EngineMath::Vector2(1200.f, 150.f),
    EngineMath::Vector2(1200.f, 700.f),
    EngineMath::Vector2(200.f, 700.f)
  };

  m_currentWaypoint = 0;

	// create circle actor
	m_ACircle = EngineUtilities::MakeShared<Actor>("Circle Actor");
  if(m_ACircle) {
		m_ACircle->getComponent<CShape>()->createShape(ShapeType::CIRCLE);
		m_ACircle->getComponent<CShape>()->setFillColor(sf::Color::Red);
		m_ACircle->getComponent<Transform>()->setPosition(EngineMath::Vector2(200.f, 700.f));
		//m_ACircle->setName("CircleActor");
	}
  else {
    ERROR("BaseApp",
      "init",
      "Failed to create Circle Actor, check memory allocation");
    return false;
  }

  return true;
}

void
BaseApp::update() {
  if (!m_windowPtr.isNull()) {
    m_windowPtr->update();
  }

  if (!m_ACircle.isNull() && !m_waypoints.empty()) {
    m_ACircle->update(m_windowPtr->deltaTime.asSeconds());

    // Get current target waypoint
    EngineMath::Vector2 targetPos = m_waypoints[m_currentWaypoint];

    // Move towards the current waypoint
    m_ACircle->getComponent<Transform>()->seek(
      targetPos, 200.f, m_windowPtr->deltaTime.asSeconds(), 10.f);

    // Check if close enough to the waypoint to advance
    EngineMath::Vector2 currentPos = m_ACircle->getComponent<Transform>()->getPosition();
    float distance = EngineMath::Vector2::distance(currentPos, targetPos);
    if (distance < 10.f && m_currentWaypoint < 3) {
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

  if (!m_ACircle.isNull()) {
		m_ACircle->getComponent<CShape>()->render(m_windowPtr);
  }

  m_windowPtr->display();
}

void
BaseApp::destroy() {
	//m_shapePtr.reset(); // Release the shape pointer
  //m_window->destroy();
}
