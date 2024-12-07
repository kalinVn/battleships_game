#ifndef Game_H
#define Game_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <vector>
#include <string>

#include "Grid.h"
#include "Cell.h"
#include "config.h"
#include "Vector2D.h"



using namespace std;

class Game {

   
    public:


        void init () {
           
            cout << "Please fill the grid with, height, the number of vessles and range" << endl;
            std::getline(std::cin, inputData);

            // TODO validate inputData
            std::vector<std::string> params = getInputDataParams();
            
            gridWidth = stoi(params[0]);
            gridHeight = stoi(params[1]);
            numberOfVessels = stoi(params[2]);
            string rangeRadius = params[3];

            grid = Grid(gridWidth, gridHeight, numberOfVessels);
            grid.create();
        }

        //TODO method and suparate logic into different method
        void play () {
            int width = grid.getWidth();
            int height = grid.getHeight();
            int score = 0;       
            string gameState = "play";     
            int distance = 0;
            Cell** cells = grid.getCells(); 
            Cell currentCell;
            Vector2D vectorCellOnTopLeft = Vector2D(0, 0);
            Vector2D vectorCellOnTopRight = Vector2D(0, 0);
            Vector2D vectorCellOnBottomLeft = Vector2D(0, 0);
            Vector2D vectorCellOnBottomRight = Vector2D(0, 0);
            Vector2D currentCellCeneter = Vector2D(0, 0);
            Vector2D targetCellCenter = Vector2D(0, 0);

            double distanceToCellTopLeft = 0;
            double distanceToCellTopRight = 0;
            double distanceToCellBottomLeft = 0;
            double distanceToCellBottomRight = 0;
            int cellX = 0;
            int cellY = 0;
            string shootedObj = "Shooted";
            string enemyObjectName = "enemy";
            int currentRocketX = 0;
            int currentRocketY = 0;
            
            bool gotEnemy = false;
            double currentLength = 0;
            bool isCellOnRange = false;
            bool gotWin = false;
            bool gotHit = false;
            double distanceCellsCeneterToCenter = 0;
            string missingMessage = "";
           
            if (isDebug) {
                showEnemiesCoordinates(cells);
            }

            while (score < numberOfVessels ) {
                cout  << "Enter coordinates: " << endl;
                
                std::getline(std::cin, inputData);
                std::vector<std::string> params = getInputDataParams();
                cellX = stoi(params[0]);
                cellY = stoi(params[1]);

                currentRocketX = 0;
                currentRocketY = 0;
                distance =0;
                gotEnemy = false;
                gotHit = false;
                currentLength = 0;
                isCellOnRange = false;
                distanceCellsCeneterToCenter = 0;
                // TODO concatanete miissing message
                missingMessage = "Miss: ";

                 // TODO remove code duplication
                for (int i = 0; i < gridWidth; i++) {
                    for (int j = 0; j < gridHeight; j++) {
                        if (cells[i][j].getObjType() == enemyObjectName) {
                            if (cellX == cells[i][j].getX() && cellY == cells[i][j].getY()) {
                                cout << "Hit!!" << endl;
                                score++;
                                
                                cells[i][j].setObjType(shootedObj);
                                cout <<  cellX << " " << cellY << endl;
                                if (score >= numberOfVessels) {
                                    gotWin = true;
                                    cout << "Win!!!" << endl;
                                }
                                gotHit = true;
                                break;
                            }
                        }
                    }
                }
                // TODO remove code duplication
                for (int i = 0; i < gridWidth; i++) {
                    for (int j = 0; j < gridHeight; j++) {
                        if (gotHit == false) {
                            currentRocketX = i;
                            currentRocketY = j;
                            currentCell = cells[i][j];
                            targetCellCenter = cells[cellX][cellY].getCenter();
                        
                            vectorCellOnTopLeft     = Vector2D(cells[i][j].getCoordTopCellX(), cells[i][j].getCoordTopCellY());
                            vectorCellOnTopRight    = Vector2D(cells[i][j].getCoordTopCellX() + cells[i][j].getSize(), 
                                                            cells[i][j].getCoordTopCellY());

                            vectorCellOnBottomLeft = Vector2D(cells[i][j].getCoordBottomCellX(),
                                                            cells[i][j].getCoordTopCellY() - cells[i][j].getSize());

                            vectorCellOnBottomRight = Vector2D(cells[i][j].getCoordBottomCellX() + cells[i][j].getSize(), 
                                                            cells[i][j].getCoordTopCellY() - cells[i][j].getSize());

                            distanceToCellTopLeft = targetCellCenter.getDistance(vectorCellOnTopLeft);
                            distanceToCellTopRight = targetCellCenter.getDistance(vectorCellOnTopRight);
                            distanceToCellBottomLeft = targetCellCenter.getDistance(vectorCellOnBottomLeft);
                            distanceToCellBottomRight= targetCellCenter.getDistance(vectorCellOnBottomRight);

                            isCellOnRange = circleRadius > distanceToCellTopLeft || circleRadius > distanceToCellTopRight 
                                            || circleRadius > distanceToCellBottomLeft || circleRadius > distanceToCellBottomRight;

                            if (isCellOnRange) {
                                distanceCellsCeneterToCenter = targetCellCenter.getDistance(cells[i][j].getCenter());
                                // cout << "Miss: " << distanceCellsCeneterToCenter << endl;
                                string distanceCellsCeneterToCenterAsString =  std::to_string(distanceCellsCeneterToCenter);
                                missingMessage += distanceCellsCeneterToCenterAsString + " ";

                                gotEnemy = true;
                            }
                        }
                    }
                        
                }
                if (gotEnemy == true ) {
                    cout << missingMessage << endl;
                };


                if (gotWin == true ) break;

            }
        }

    private:
        Grid grid;
        string inputData;
        int gridWidth;
        int gridHeight;
        int numberOfVessels;
        int circleRadius = 540;
        void showEnemiesCoordinates (Cell **cells) {
            string enemyObjectName = "enemy";
            for (int i = 0; i < gridWidth; i++) {
                for (int j = 0; j < gridHeight; j++) {
                    if (cells[i][j].getObjType() == enemyObjectName) {
                        cout << "Current cell: " << cells[i][j].getX() << " " << cells[i][j].getY() << " " << endl;
                    }
                }

            }
        }

        Cell *getCellEnemyObj (Cell **cells) {
            string enemyObjectName = "enemy";
            Cell cellsEnemyObj[] = {}; 

            int counter = 0;
            for (int i = 0; i < gridWidth; i++) {
                for (int j = 0; j < gridHeight; j++) {
                    if (cells[i][j].getObjType() == enemyObjectName) {
                        cout << "Current cell: " << cells[i][j].getX() << " " << cells[i][j].getY() << " " << endl;
                        cellsEnemyObj[counter] = cells[i][j];
                        counter++;
                    }
                }

            }

            return cellsEnemyObj;
        }

        std::vector<std::string> getInputDataParams () { 
            std::vector<std::string> params;
            std::istringstream iss(inputData);
            std::string param;

            while (iss >> param) {
                params.push_back(param);
            }

            return params;
        }

};

#endif