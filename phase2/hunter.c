// hunter.c
// Implementation of your "Fury of Dracula" hunter AI

#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "HunterView.h"

char *idToAbbrev(LocationID p);
void LocationCopy (char *from, char *to);

void decideHunterMove(HunterView gameState)
{
    if(giveMeTheRound(gameState) == 1){
        //Initial Round
        registerBestPlay("MA","Greetings");
    } else{
        
        //Subsequent Round
        char dest[3]; //Destination var
        
        //Rest if health <5
        if(howHealthIs(gameState,whoAmI(gameState)) < 5){
            char currentLocation[] = idToAbbrev(whereIs(gameState,whoAmI(gameState)));
            LocationCopy(currentLocation,dest);
            registerBestPlay(dest,"Gonna need some Rest....");
            free(currentLocation);
            return;
        }
       
        LocationID dracLocation = whereIs(gameState,PLAYER_DRACULA);
        
        //Check dracula Reach by Road
        int dracReach = FALSE;
        int size, *reachableLocation;
        reachableLocation = whereCanIgo(gameState,&size,1,0,0);
        for(i = 0; i < size && dracReach = FALSE; i++){
            if(edges[i] == dracLocation){
                dracReach = TRUE;
                LocationCopy(dracLocation,dest);
                registerBestPlay(dest, "Found You!");
                return;
            }
        }
        free(size);
        free(reachableLocation);
        
        //Check dracula Reach by Rail
        int dracReach = FALSE;
        int size, *reachableLocation;
        reachableLocation = whereCanIgo(gameState,&size,0,1,0);
        for(i = 0; i < size && dracReach = FALSE; i++){
            if(edges[i] == dracLocation){
                dracReach = TRUE;
                LocationCopy(dracLocation,dest);
                registerBestPlay(dest, "Found You!");
                return;
            }
        }
        free(size);
        free(reachableLocation);
        
        //Check dracula Reach by Sea
        int dracReach = FALSE;
        int size, *reachableLocation;
        reachableLocation = whereCanIgo(gameState,&size,0,0,1);
        for(i = 0; i < size && dracReach = FALSE; i++){
            if(edges[i] == dracLocation){
                dracReach = TRUE;
                LocationCopy(dracLocation,dest);
                registerBestPlay(dest, "Found You!");
                return;
            }
        }
        free(size);
        free(reachableLocation);
        
        //Go to random places (dracula cannot be found)
        int size , *reachableLocation;
        int magicNum = giveMeTheRound(gameState);
        reachableLocation = whereCanIgo(gameState,&size,1,0,0);
        while(magicNum > size){
            magicNum = magicNum % size;
        }
        LocationCopy(edges[magicNum],dest);
        registerBestPlay(dest,"Boring..");
        return;
    }
}

void LocationCopy (char *from, char *to){
    int tempCounter = 0;
    to[0] = from[0];
    to[1] = from[1];
    to[2] = '\0';
    free(tempCounter);
}

char *idToAbbrev(LocationID p)
{
   assert(validPlace(p));
   return places[p].abbrev;
}