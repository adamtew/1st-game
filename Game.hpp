#ifndef _GAME_HPP
#define _GAME_HPP

class Game
{
public:
  static void Start();

private:
  static bool IsExiting();
  static void GameLoop();

  static void ShowSplashScreen();
  static void ShowMenu();

  enum GameState {
    UNINITIALIZED,
    SHOWING_SPLASH,
    PAUSED,
    SHOWING_MENU,
    PLAYING,
    EXITING
  };

  static GameState _gameState;
  static GLFWwindow* _mainWindow;
  
};

#endif
