#ifndef DEF_INPUT
#define DEF_INPUT

/*!
 * \file Input.hpp
 * \brief Definition of Input class
 * \author Baptiste D.
 * \version 1.0
 */



/*! \class Input
 * \brief class that contains all the inner informations the user send to the program
 *        while interacting with the mouse/keyboard
 */
class Input{

public:
  Input();

  void update_event();

  char getKey(int i) const;
  void setKeyUp(int i);

  int getQuit() const;

  char getMouseButton(int i) const;
  int getMouseX() const;
  int getMouseY() const;

  void setQuit();


private:
  char key[SDLK_LAST]; /*!<Tab of all Keys */
  int mouseX; /*!<x-coordinate of the mouse on the screen (in pixel) */
  int mouseY; /*!<y-coordinate of the mouse on the screen (in pixel) */
  int mouseXRel; /*!<Adjusted x-coordinate of the mouse on the screen (in pixel) */
  int mouseYRel; /*!<Adjusted y-coordinate of the mouse on the screen (in pixel) */
  char mouseButtons[8]; /*!<Tab of all mouse keys */
  char quit; /*!<??? */



};




#endif // DEF_INPUT
