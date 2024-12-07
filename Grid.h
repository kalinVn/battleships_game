#ifndef Grid_H
#define Grid_H

#include <algorithm>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <fstream>
#include <cmath>
#include <random>

#include "Cell.h"

using namespace std;

class Grid {

   
    public:
        Grid();

        Grid(int, int, int);

        int getWidth () {
            return width;
        }

        int getHeight () {
            return width;
        }

        Cell** getCells () {
            return cells;
        }

        void create () {
            
            std::vector<int> uniqueRandomVector = generateUniqueRandomVector(numbersOfEnemies, 0, width * height);
            int counter = 0;
            
            cells =  new Cell*[width];
            int cellSize = 200;
           
            string enemyObjectName = "enemy";
            for (int i = 0; i < width; i++) {
                cells[i] = new Cell[height];

                for (int j = 0; j < height; j++) {
                    cells[i][j] = Cell(i, j, cellSize);
                    cells[i][j].create();
                    auto randomValueInGrid = std::find(uniqueRandomVector.begin(), uniqueRandomVector.end(), counter);
                    if (randomValueInGrid != uniqueRandomVector.end() ) {
                        cells[i][j].setObjType(enemyObjectName);
                    } 

                    counter++;
                }
               
            }
        }
    private:
        int width;
        int height;
        int numbersOfEnemies;

        Cell** cells; 

        std::vector<int> generateUniqueRandomVector(int size, int min, int max) {
            
            if (size > (max - min + 1)) {
                throw std::invalid_argument("Size is larger than the range of unique numbers.");
            }

            std::unordered_set<int> uniqueNumbers;
            std::vector<int> randomVector;
            std::random_device rd;  
            std::mt19937 gen(rd()); 
            std::uniform_int_distribution<> distr(min, max); 

            while (uniqueNumbers.size() < size) {
                int randomNum = distr(gen);
                if (uniqueNumbers.insert(randomNum).second) { 
                    randomVector.push_back(randomNum);
                }
            }

            return randomVector;
        }

};

    Grid::Grid () {
        width = 0;
        height = 0;
        numbersOfEnemies = 0;
       

    }

    Grid::Grid (int currentWidth, int currentHeight, int currentNumbersOfEnemies) {
        width = currentWidth;
        height = currentHeight;
        numbersOfEnemies = currentNumbersOfEnemies;
        
    }
 
#endif