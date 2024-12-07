#ifndef Cell_H
#define Cell_H

#include <iostream>
#include <fstream>
#include <cmath>
#include "Vector2D.h"

using namespace std;

class Cell {

   
    public:
        Cell();

        Cell(int, int, int);

        int getX () {
            return x;
        }

        string getObjType () {
            return objType;
        }

        int setObjType (string currentObjType) {
            objType = currentObjType;
        }

        int getY () {
            return y;
        }

        int getSize () {
            return width;
        }

        double getCoordTopCellX () {
            return coordTopCellX;
        }

        double getCoordTopCellY () {
            return coordTopCellY;
        }

        double getCoordBottomCellX () {
            return coordBottomCellX;
        }

        double getCoordBottomCellY () {
            return coordBottomCellY;
        }

        Vector2D getCenter () {
            return center;
        }

        void create () {
            coordTopCellX = x * width;
            coordTopCellY = y * width;
            coordBottomCellX = (x * width) + width;
            coordBottomCellY = (y * width) + width;
            center = Vector2D( ( (coordTopCellX + coordBottomCellX) / 2),  -((coordTopCellY + coordBottomCellY) / 2)) ;
        }

    private:
        int x;
        int y;
        Vector2D center = Vector2D(0, 0); 
        int width;
        double coordTopCellX = 0;
        double coordTopCellY = 0;
        double coordBottomCellX = 0;
        double coordBottomCellY = 0;

        string objType = "emptyCell";

    };

    Cell::Cell () {
        x = 0;
        y = 0;
        width = 0;
    }

    Cell::Cell (int currentX, int currentY, int currentWidth) {
        x = currentX;
        y = currentY;
        width = currentWidth;
    }
 
#endif