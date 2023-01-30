/*!
 * \file Input.cpp
 * \brief Definition of Input class
 * \author Baptiste D.
 * \version 1.0
 */



#include<cstdlib>
#include<iostream>
#include<fstream>
#include<SDL/SDL.h>
#include<string>
#include<cassert>
#include"Input.hpp"


using namespace std;



Input::Input(){

  for(int i = 0; i<SDLK_LAST; i++){
    key[i] = 0;
  }

  for(int i = 0; i<8; i++){
    mouseButtons[i] = 0;
  }

  mouseX = 0;
  mouseY = 0;
  mouseXRel = 0;
  mouseYRel = 0;

  quit = 0;



}



char Input::getKey(int i) const {return key[i];}
void Input:: setKeyUp(int i){ key[i] = 0;}
int Input::getQuit() const{ return quit;}

char Input::getMouseButton(int i) const{ return mouseButtons[i];}
int Input::getMouseX() const{ return mouseX;}
int Input::getMouseY() const{ return mouseY;}





/*!
 *  \brief update of events
 *
 *  This method aims at updating the Instanciation of class Input when the user
 *  interact with the mouse/keyboard.
 */
void Input::update_event(){

  SDL_Event event;

  while(SDL_PollEvent(&event)){
    switch(event.type){
    case SDL_KEYDOWN:
      key[event.key.keysym.sym] = 1;
      break;
    case SDL_KEYUP:
      key[event.key.keysym.sym] = 0;
      break;
    case SDL_MOUSEMOTION:
      mouseX=event.motion.x;
      mouseY=event.motion.y;
      mouseXRel=event.motion.xrel;
      mouseYRel=event.motion.yrel;
      break;
    case SDL_MOUSEBUTTONDOWN:
      mouseButtons[event.button.button] = 1;
      break;
    case SDL_MOUSEBUTTONUP:
      mouseButtons[event.button.button] = 0;
      break;
    case SDL_QUIT:
      quit = 1;
      break;
    default:
      break;
    }
  }
}


void Input::setQuit(){
  quit = 1;
}







