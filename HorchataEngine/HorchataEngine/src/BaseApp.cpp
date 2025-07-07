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

  //m_window = new Window(1920, 1080, "Horchata Engine");
	m_shapePtr = EngineUtilities::MakeShared<CShape>();
  if (m_shapePtr) {
		    m_shapePtr->createShape(ShapeType::CIRCLE);
        m_shapePtr->setFillColor(sf::Color::Red);
        m_shapePtr->setPosition(200.f, 150.f);
  }
  return true;
}

void
BaseApp::update() {
}

void
BaseApp::render() {
  m_windowPtr->clear();
  if (m_shapePtr) {
		m_shapePtr->render(m_windowPtr);
		//m_windowPtr->draw(*m_shapePtr);
  }

  m_windowPtr->display();
}

void
BaseApp::destroy() {
	m_shapePtr.reset(); // Release the shape pointer
  //m_window->destroy();
}
