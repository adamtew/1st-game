#include <GLFW/glfw3.h>
#include "Game.hpp"
#include "SplashScreen.hpp"

void Game::Start()
{
  if (_gameState != UNINITIALIZED) return;
  if (!glfwInit())
  {
  }
  _mainWindow = glfwCreateWindow(640, 480, "Pang", NULL, NULL);
  glfwMakeContextCurrent(_mainWindow);
  _gameState = Game::PLAYING;
  _gameState = Game::SHOWING_SPLASH;

  //while (!IsExiting())
  //{
  //  GameLoop();
  //}
  { // stuff
    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(_mainWindow))
    {
      int width, height;
      glfwGetFramebufferSize(_mainWindow, &width, &height);
      glViewport(0, 0, width, height);

      double time = glfwGetTime();

      glClearColor(1.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      glfwSwapBuffers(_mainWindow);
      glfwPollEvents();
    }
  }

  glfwTerminate();
}

bool Game::IsExiting()
{
  return _gameState == Game::EXITING ? true : false;
}

void Game::GameLoop()
{
  while (!glfwWindowShouldClose(_mainWindow))
  {
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(_mainWindow);
    glfwPollEvents();
    switch (_gameState)
    {
      case Game::PLAYING:
        {
          glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        }
        break;
      case Game::UNINITIALIZED:
      case Game::SHOWING_SPLASH:
        {
          ShowSplashScreen();
          break;
        }
      case Game::PAUSED:
      case Game::SHOWING_MENU:
        {
          ShowMenu();
          break;
        }
      case Game::EXITING:
      default:
        break;
    }
  }

  glfwTerminate();
}

void Game::ShowSplashScreen()
{
  SplashScreen splashScreen;
  splashScreen.Show(_mainWindow);
  _gameState = Game::SHOWING_SPLASH;
}

void Game::ShowMenu()
{

}

Game::GameState Game::_gameState = UNINITIALIZED;
GLFWwindow* Game::_mainWindow;
