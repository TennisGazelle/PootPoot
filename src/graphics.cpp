#include "graphics.h"

Graphics::Graphics()
{

}

Graphics::~Graphics()
{

}

bool Graphics::Initialize(int width, int height)
{
  // Used for the linux OS
  #if !defined(__APPLE__) && !defined(MACOSX)
    // cout << glewGetString(GLEW_VERSION) << endl;
    glewExperimental = GL_TRUE;

    auto status = glewInit();

    // This is here to grab the error that comes from glew init.
    // This error is an GL_INVALID_ENUM that has no effects on the performance
    glGetError();

    //Check for error
    if (status != GLEW_OK)
    {
      std::cerr << "GLEW Error: " << glewGetErrorString(status) << "\n";
      return false;
    }
  #endif

  // For OpenGL 3
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Init Camera
  m_camera = new Camera();
  if(!m_camera->Initialize(width, height))
  {
    printf("Camera Failed to Initialize\n");
    return false;
  }

  //set up the holder
  bulletHolder = new BulletHolder();

  // Create the object
  m_player = new Player(bulletHolder);
  m_opponent = new Player(bulletHolder);

  m_opponent->setPosition(glm::vec3(10.0, 0.0, 10.0));  

  // set up the sides
  boundarySize = 25;
  m_boundary = new Object();
  m_boundary->Init("../models/plane.obj");
  m_boundary->resize(glm::vec3(boundarySize));
  m_boundary->setPosition(glm::vec3(0.0));

  // set up the bullet holder
  // Set up the shaders
  m_shader = new Shader();
  if(!m_shader->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }

  // Add the vertex shader
  if(!m_shader->AddShader(GL_VERTEX_SHADER))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shader
  if(!m_shader->AddShader(GL_FRAGMENT_SHADER))
  {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }

  // Connect the program
  if(!m_shader->Finalize())
  {
    printf("Program to Finalize\n");
    return false;
  }

  // Locate the projection matrix in the shader
  m_projectionMatrix = m_shader->GetUniformLocation("projectionMatrix");
  if (m_projectionMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_projectionMatrix not found\n");
    return false;
  }

  // Locate the view matrix in the shader
  m_viewMatrix = m_shader->GetUniformLocation("viewMatrix");
  if (m_viewMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_viewMatrix not found\n");
    return false;
  }

  // Locate the model matrix in the shader
  m_modelMatrix = m_shader->GetUniformLocation("modelMatrix");
  if (m_modelMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_modelMatrix not found\n");
    return false;
  }

  m_preMultipliedMVPMatrix= m_shader->GetUniformLocation("mvpMatrix");

  if (m_preMultipliedMVPMatrix == INVALID_UNIFORM_LOCATION)
  {
    printf("m_preMultipliedMVPMatrix not found\n");
    return false;
  }

  //enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  return true;
}

bool Graphics::Update(unsigned int dt)
{
  // Update the object
  m_player->update(dt);
  m_opponent->update(dt);

  bulletHolder->Update(dt);

  CheckBounds();
  
  // update the camera to follow the player  
  //m_camera->updateFocusPoint(glm::vec3(m_player->GetModel()[3]));

  // kill the game if the keyboard said so
  if (gameState == EXIT) {
    return false;
  }

  // kill the game if/when there's a bullet hitting the player
  int shot = this->hasPlayerBeenShot();
  if (shot == 1 || shot == 3) {
    m_player->decrementHealth();
    std::cout << "player health is now: " << m_player->getHealth() << std::endl;
  }
  if (shot == 2 || shot == 3) {
    m_opponent->decrementHealth();
    std::cout << "opponent health is now: " << m_opponent->getHealth() << std::endl;
  }

  if (m_player->getHealth() <= 0) {
    std::cout << "You lost!" << std::endl;
    return false;    
  }
  if (m_opponent->getHealth() <= 0) {
    std::cout << "You Won!" << std::endl;
    return false;
  }
  // opponent AI stuff
  static unsigned int movementTimer = 0;
  static unsigned int shootingTimer = 0;
  static int mod = 4;
  Direction opponentDir;
  
  switch(movementTimer % mod) {
     case 0:
       opponentDir = UP; break;
     case 1:
       opponentDir = DOWN; break;
     case 2:
       opponentDir = LEFT; break;
     case 3:
       opponentDir = RIGHT; break;
  }

  if (movementTimer % 100 < 7) {
    m_opponent->moveDirection(opponentDir);
  }
  if (shootingTimer % 157 == 0) {
    m_opponent->shootDirection(opponentDir);
  }

  movementTimer = rand() % 100;
  shootingTimer++;
  return true;
}

void Graphics::Render()
{
  //clear the screen
  glClearColor(0.0, 0.0, 0.0, 1.0);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the correct program
  m_shader->Enable();

  // Send in the projection and view to the shader
  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection())); 
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView())); 
  glm::mat4 mvp;

  // do the same thing for the box rendering
  mvp = m_camera->GetProjection() * m_camera->GetView() * m_boundary->GetModel(); 
  glUniformMatrix4fv(m_preMultipliedMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvp));
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_boundary->GetModel()));
  m_boundary->Render();

  for (int i = 0; i < bulletHolder->getSize(); i++) {
    // Send in premultiplied matrix to shader
    mvp = m_camera->GetProjection() * m_camera->GetView() * bulletHolder->GetModelAt(i); 
    glUniformMatrix4fv(m_preMultipliedMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvp));
    glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(bulletHolder->GetModelAt(i)));
    bulletHolder->Render(i);
  }

  // Send in premultiplied matrix to shader
  mvp = m_camera->GetProjection() * m_camera->GetView() * m_player->GetModel(); 
  glUniformMatrix4fv(m_preMultipliedMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvp));
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_player->GetModel()));
  m_player->Render();  

  //do the same thing for the opponent rendering
  mvp = m_camera->GetProjection() * m_camera->GetView() * m_opponent->GetModel(); 
  glUniformMatrix4fv(m_preMultipliedMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvp));
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_opponent->GetModel()));
  m_opponent->Render();  
 

  // Get any errors from OpenGL
  auto error = glGetError();
  if ( error != GL_NO_ERROR )
  {
    string val = ErrorString( error );

    std::cout<< "Error initializing OpenGL! " << error << ", " << val << std::endl;
  }
}

void Graphics::ShiftCamera(Direction dir) {
  switch (dir) {
    case DOWN:
      m_camera->goToFrontView();
      break;
    case UP:
      m_camera->goToTopView();
      break;
    case RIGHT:
      m_camera->goToSideView();
      break;
    default:
      break;
  }
}

void Graphics::Keyboard(SDL_Event sdl_event) {
  switch (sdl_event.key.keysym.sym) {
    case SDLK_UP:
      m_player->moveDirection(UP);
      break;
    case SDLK_DOWN:
      m_player->moveDirection(DOWN);
      break;
    case SDLK_RIGHT:
      m_player->moveDirection(RIGHT);
      break;
    case SDLK_LEFT:
      m_player->moveDirection(LEFT);
      break;

    case SDLK_w:
      m_player->shootDirection(UP);
      break;
    case SDLK_a:
      m_player->shootDirection(LEFT);
      break;
    case SDLK_s:
      m_player->shootDirection(DOWN);
      break;
    case SDLK_d:
      m_player->shootDirection(RIGHT);
      break;
    case SDLK_x:
      gameState = EXIT;

    case SDLK_KP_PLUS:
      m_camera->zoomIn();
      break;
    case SDLK_KP_MINUS:
      m_camera->zoomOut();
     break;
    default:
      std::cout << "invalid button input: " << sdl_event.key.keysym.sym << std::endl;
      break;
  }
}

std::string Graphics::ErrorString(GLenum error)
{
  if(error == GL_INVALID_ENUM)
  {
    return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
  }

  else if(error == GL_INVALID_VALUE)
  {
    return "GL_INVALID_VALUE: A numeric argument is out of range.";
  }

  else if(error == GL_INVALID_OPERATION)
  {
    return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
  }

  else if(error == GL_INVALID_FRAMEBUFFER_OPERATION)
  {
    return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
  }
  else if(error == GL_OUT_OF_MEMORY)
  {
    return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
  }
  else
  {
    return "None";
  }
}

void Graphics::CheckBounds() {
  // if the bullet goes outside, or if the player goes outside the

  // boundaries, force them back to the opposite side
  bulletHolder->checkBounds(boundarySize);
  
  // FOR THE OPPONENT
  glm::vec4 position = m_opponent->GetModel()[3];
  if (position.x > boundarySize) position.x = -boundarySize;
  else if (position.x < -boundarySize) position.x = boundarySize;
  if (position.z > boundarySize) position.z = -boundarySize;
  else if (position.z < -boundarySize) position.z = boundarySize;
  m_opponent->setPosition(glm::vec3(position));

  // FOR THE PLAYER
  position = m_player->GetModel()[3];
  if (position.x > boundarySize) position.x = -boundarySize;
  else if (position.x < -boundarySize) position.x = boundarySize;
  if (position.z > boundarySize) position.z = -boundarySize;
  else if (position.z < -boundarySize) position.z = boundarySize;
  m_player->setPosition(glm::vec3(position));

}

bool areWithinHittingDistance(glm::mat4 first, glm::mat4 second) {
  glm::vec3 distance = glm::vec3(first[3]) - glm::vec3(second[3]);
  return glm::distance(first[3], second[3]) <= 1.0;
}

int Graphics::hasPlayerBeenShot() {
  int offenderIndex = bulletHolder->checkForCollision(m_player->GetModel());
  if (offenderIndex != -1) {
    bulletHolder->destroyBullet(offenderIndex);
    return 1;
  }

  offenderIndex = bulletHolder->checkForCollision(m_opponent->GetModel());
  if (offenderIndex != -1) {
    bulletHolder->destroyBullet(offenderIndex);
    return 2;
  }
  //check player to player collision
  if (areWithinHittingDistance(m_player->GetModel(), m_opponent->GetModel())) {
    return 3;
  }
  return 0;
}
