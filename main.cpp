/**
 * \file main.cpp
 * \brief Runs Rock Paper Scisors.
 * \author Baptiste D.
 * \version 1.0
 * \date January 29th 2022
 *
 * Program that runs the Game
 *
 */




#include<iostream>
#include<fstream>
#include<ctime>
#include<cassert>
#include<vector>
#include<string>
#include <algorithm>
#include<stdio.h>
#include<stdlib.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include"Map.hpp"
#include"Input.hpp"



#define SPEED 100
#define THRESHOLD 3
using namespace std;






void fill_grid(int *grid, int nb_cells, double d_red = 0.33,
              double d_green = 0.33){

  assert(d_red + d_green <= 1 && d_red + d_green > 0);
  srand(time(0));


  int nb_cells_red = int(d_red * nb_cells);
  int nb_cells_green = int(d_green * nb_cells);
  int nb_cells_blue = nb_cells - nb_cells_red - nb_cells_green;

  for(int k = 0; k < nb_cells; k++)
    grid[k] = 2;

  for(int k = 0; k<nb_cells_red; k++){
    int index(0);
    do{
      index = rand() % nb_cells;
    }while(grid[index] == 0);
    grid[index] = 0;
  }

  for(int k = 0; k<nb_cells_green; k++){
    int index(0);
    do{
      index = rand() % nb_cells;
    }while(grid[index] == 0 || grid[index] == 1);
    grid[index] = 1;
  }

}





/*************Rules for Rock Paper Scisors*/

int update_cell(Map &map, int I, int J){


  //Offset to deal with boundaries
  int offset_inf_I(-1), offset_sup_I(1);
  int offset_inf_J(-1), offset_sup_J(1);


  if(I == 0){
    offset_inf_I = 0;
  }else{
    if(I == map.getgridW()-1){
      offset_sup_I = 0;
    }
  }

  if(J == 0){
    offset_inf_J = 0;
  }else{
    if(J == map.getgridH()-1){
      offset_sup_J = 0;
    }
  }

  //Updating
  int nb_red(0), nb_green(0), nb_blue(0); //respectively 0, 1 and 2

  for(int j = J+offset_inf_J; j <= J+offset_sup_J; j++){
    for(int i = I+offset_inf_I; i <= I+offset_sup_I; i++){
      switch(map.getgrid(i,j)){
        case 0:
        nb_red++;
        break;

        case 1:
        nb_green++;
        break;

        case 2:
        nb_blue++;
        break;
      }
    }
  }

  int res(-1);
  switch(map.getgrid(I,J)){
    case 0:
    nb_red--;
    if(nb_green >= THRESHOLD){
      res = 1;
    }else{
      res = 0;
    }
    break;

    case 1:
    nb_green--;
    if(nb_blue >= THRESHOLD){
      res = 2;
    }else{
      res = 1;
    }
    break;

    case 2:
    nb_blue--;
    if(nb_red >= THRESHOLD){
      res = 0;
    }else{
      res = 2;
    }
    break;
  }

  return res;


}


void update_RPS(Map &map){

  int *t = new int[map.getgridW()*map.getgridW()];

  for(int i = 0; i < map.getgridW(); i++){
    for(int j = 0; j < map.getgridH(); j++){
      t[j*map.getgridW()+i] = update_cell(map,i,j);
    }
  }
  map.set_all_grid(t);
  delete []t;

}



/*************Processing data*/

void compute_density(Map const& map, vector<int> &dat){

  int d_red(0), d_green(0), d_blue(0);

  for(int j=0; j<map.getgridH(); j++){
    for(int i=0; i<map.getgridW(); i++){
      switch(map.getgrid(i,j)){
        case 0:
          d_red++;
          break;

        case 1:
          d_green++;
          break;

        case 2:
          d_blue++;
          break;
      }
    }
  }
  dat.push_back(d_red);
  dat.push_back(d_green);
  dat.push_back(d_blue);
}


void post_processing(vector<int> const& dat, int nbcells){

  ofstream stream("data/data.txt");

  for(int k=0; k<int(dat.size()/3); k++){
    stream<<double(SPEED*k)/1000<<" "<<double(dat[3*k])/nbcells<<" "
    <<double(dat[3*k+1])/nbcells<<" "<<double(dat[3*k+2])/nbcells<<endl;
  }

  stream.close();

  system("gnuplot data/script.gnu -persist");
}





//==============================================================================
//================================MAIN==========================================
//==============================================================================


int main(int argc, char *argv[]){

    assert(argc == 4);


    SDL_Surface *screen = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    if(SDL_Init(SDL_INIT_VIDEO) == -1){
        fprintf(stderr,"ERROR INITIALISATION SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    Map map(argv[1]); //Map loading

    screen = SDL_SetVideoMode(map.getgridW() * map.getwidthTile(),
     map.getgridH() * map.getheigthTile(),32, SDL_HWSURFACE| SDL_DOUBLEBUF);
    if(screen == NULL){
        fprintf(stderr,"CANNOT LOAD SCREEN: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetCaption("Rock Paper Scisors", NULL);


    int time(0), previousTime(0);
    Input in;

    int l = map.getgridW()*map.getgridW();
    int *grid = new int[l];
    fill_grid(grid,l,atof(argv[2]),atof(argv[3]));
    map.set_all_grid(grid);

    map.print_Map(screen);
    SDL_Flip(screen);
    delete []grid;

    vector<int> dat;
    compute_density(map,dat);
    while(!(in.getKey(SDLK_ESCAPE)) && !(in.getQuit())){
        in.update_event();

        time = SDL_GetTicks();

        if(time - previousTime > SPEED){
          update_RPS(map);
          SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format, 0, 0, 0));
          map.print_Map(screen);
          SDL_Flip(screen);
          previousTime = time;
          compute_density(map,dat);
        }

      }


    SDL_Quit();

    post_processing(dat,map.getgridW()*map.getgridH());


    return EXIT_SUCCESS;

}
