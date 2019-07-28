//
// Created by Mike on 7/27/2019.
//
#include "TileMapComponent.h"
#include <fstream>
#include <sstream>
#include <iostream>

TileMapComponent::TileMapComponent(class Actor *owner, int drawOrder)
        : SpriteComponent(owner, drawOrder){

}

void TileMapComponent::LoadTileMap_CSV(std::string fileName) {
    std::ifstream inFile;
    inFile.open(fileName);
    std::vector<int> *temp = new std::vector<int>;
    std::string line;
    while(std::getline(inFile,line)) {
        std::stringstream lineStream(line);
        std::string cell;

        while (std::getline(lineStream, cell, ',')) {
            temp->push_back(stoi(cell));
        }
        /*if (!lineStream && cell.empty())
        {
            // If there was a trailing comma then add an empty element.
            csvMap.push_back(-1);
        }*/
    }
    csvMap.emplace_back(*temp);
}

void TileMapComponent::Draw(SDL_Renderer *renderer) {
    SDL_Rect desRect;
    desRect.w = 32;
    desRect.h = 32;

    for(auto layer : csvMap) {
        desRect.x = 0;
        desRect.y = 0;
        for(auto value : layer) {
            SDL_Rect srcRect;
            if (value != -1) {
                // Determine which tile from the set to draw.
                srcRect.w = 32;
                srcRect.h = 32;
                srcRect.x = (value % 8) * 32;
                srcRect.y = (value / 8) * 32;

                // Draw (have to convert angle from radians to degrees, and clockwise to counter)
                SDL_RenderCopyEx(renderer,
                                 mTileMapTexture,
                                 &srcRect,
                                 &desRect,
                                 -Math::ToDegrees(mOwner->getRotation()), nullptr,
                                 SDL_FLIP_NONE);
            }
            if (desRect.x >= 992) {
                desRect.x = 0;
                desRect.y += 32;
            } else {
                desRect.x += 32;
            }
        }
    }
}
