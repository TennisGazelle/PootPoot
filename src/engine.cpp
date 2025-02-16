
#include "engine.h"

Engine::Engine(string name, int width, int height)
{
  m_WINDOW_NAME = name;
  m_WINDOW_WIDTH = width;
  m_WINDOW_HEIGHT = height;
  m_FULLSCREEN = false;
}

Engine::Engine(string name)
{
  m_WINDOW_NAME = name;
  m_WINDOW_HEIGHT = 0;
  m_WINDOW_WIDTH = 0;
  m_FULLSCREEN = true;
}

Engine::~Engine()
{
  delete m_window;
  delete m_graphics;
  //if the joystick has been opened, close it!
  std::cout << "inside engine destructor" << std::endl;
  //if (SDL_JoystickOpened(SDL_JoystickIndex(m_joystick))) {
  //  SDL_JoystickClose(m_joystick);
  //}
  m_joystick = NULL;
  m_window = NULL;
  m_graphics = NULL;
}

bool Engine::Initialize()
{
  // Start a window
  m_window = new Window();
  if(!m_window->Initialize(m_WINDOW_NAME, &m_WINDOW_WIDTH, &m_WINDOW_HEIGHT))
  {
    printf("The window failed to initialize.\n");
    return false;
  }
  // Start the graphics
  m_graphics = new Graphics();
  if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT))
  {
    printf("The graphics failed to initialize.\n");
    return false;
  }
  m_graphics->ShiftCamera(UP);

  // start the joystick configuration
  // count num of joysticks
  if (SDL_NumJoysticks() > 0){
    m_joystick = SDL_JoystickOpen(0);
  }

  if (m_joystick) {
    std::cout << "num axes: " << SDL_JoystickNumAxes(m_joystick) << std::endl;
    std::cout << "num buttons: " << SDL_JoystickNumButtons(m_joystick) << std::endl;
  } else if (SDL_NumJoysticks() > 0) {
    printf("There was a joystick detected, but it failed to connect");
  }


  // Set the time
  m_currentTimeMillis = GetCurrentTimeMillis();

  // No errors
  return true;
}

void Engine::Run()
{
  m_running = true;

  while(m_running)
  {
    // Update the DT
    m_DT = getDT();

    // Check the keyboard input
    while(SDL_PollEvent(&m_event) != 0)
    {
      Keyboard();
    }

    // Update and render the graphics
    m_running = m_graphics->Update(m_DT);
    m_graphics->Render();

    // Swap to the Window
    m_window->Swap();
  }
}

void Engine::Keyboard()
{
  if(m_event.type == SDL_QUIT)
  {
    m_running = false;
  }
  else if (m_event.type == SDL_KEYDOWN)
  {
    // handle key down events here
    if (m_event.key.keysym.sym == SDLK_ESCAPE)
    {
      m_running = false;
    }
    switch (m_event.key.keysym.sym) {
			//keypad controls for camera movement
			case SDLK_1:
				m_graphics->ShiftCamera(DOWN);
				break;
			case SDLK_3:
				m_graphics->ShiftCamera(RIGHT);
				break;
			case SDLK_7:
				m_graphics->ShiftCamera(UP);
				break;
      case SDLK_9:
      case SDLK_x:
        m_running = false;
        break;
			default:
				m_graphics->Keyboard(m_event);
        break;
    }
  }
  else {
    m_graphics->Keyboard(m_event);
  }
}

unsigned int Engine::getDT()
{
  long long TimeNowMillis = GetCurrentTimeMillis();
  assert(TimeNowMillis >= m_currentTimeMillis);
  unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
  m_currentTimeMillis = TimeNowMillis;
  return DeltaTimeMillis;
}

long long Engine::GetCurrentTimeMillis()
{
  timeval t;
  gettimeofday(&t, NULL);
  long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
  return ret;
}
