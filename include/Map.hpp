#ifndef DEF_MAP
#define DEF_MAP

/*!
 * \file Map.hpp
 * \brief Definition of Map class
 * \author Baptiste D.
 * \version 1.0
 */



/**
 * \struct Properties
 * \brief Properties of a tile
 *
 * This structure gives certain characteritic of a tile
 */
typedef struct{
  SDL_Rect rectTile; /*!< Position of the tile within the entire tile_file.bmp */
  bool wall; /*!< true if the character cannot cross this tile, false otherwise */

}Propreties;





/*! \class Map
 * \brief class that models a 2 dimmensional map
 *
 *  This class aims at modelling a 2 dimmensionnal map that will be
 *  generated with a tileSet. In fact the map is modelled with a 2d-grid
 * whose each case contains a number that correspond to a tile.
 */
class Map{


public:
  Map(char *const fileName,int bgx = 0, int bgy = 0);
  Map(Map const& map1);
  ~Map();

  void clear_TileSetColorsKey(int red, int green, int blue);
  int print_Map(SDL_Surface *screen) const;

  void setgrid(int i, int j, int numTile); //Change the number of the tile
  void setTileMap(char *const fileName, int colR, int colG, int colB);
  void set_all_grid(int *t);



  int getwidthTile() const;
  int getheigthTile() const;
  int getbeginX() const;
  int getbeginY() const;
  int getnbTileW() const;
  int getnbTileH() const;
  int getgridW() const;
  int getgridH() const;
  bool getwall(int i) const;
  int getgrid(int i, int j) const;
  SDL_Surface* gettileMap() const;

  Map& operator=(Map const& map1);


private:
  int widthTile; /*!<Width of one tile within the file_tile.bmp (nb of pixel) */
  int heigthTile; /*!<Height of one tile within the file_tile.bmp (nb of pixel) */
  int nbTileW; /*!<Number of tile along the x-direction within the file_tile.bmp */
  int nbTileH; /*!<Number of tile along the y-direction within the file_tile.bmp */
  int gridW; /*!<Number of square along the x-direction within the grid */
  int gridH; /*!<Number of tile along the y-direction within the grid */
  int beginGridx; /*!< Square that represents the beginning of the grid along the x-direction within the grid  */
  int beginGridy;  /*!< Square that represents the beginning of the grid along the y-direction within the grid  */
  int *grid; //grid for the game
  Propreties *tileProp;/*!<Tab that contains the properties of each tile */
  SDL_Surface *tileMap; /*!< file_tile.bmp */
  int clear_colR; /*!< Red pixel to clear in file_tile.bmp */
  int clear_colG; /*!< Green pixel to clear in file_tile.bmp */
  int clear_colV; /*!< Blue pixel to clear file_tile.bmp */
};

#endif // DEF_MAP
