// GameView.c ... GameView ADT implementation

#include <stdlib.h>
#include <assert.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
// #include "Map.h" ... if you decide to use the Map ADT

//Players' Status
typedef struct _player {
	int currentHealth;
	LocationID currentLocation;

	//TO BE COMPLETED
}Player;

struct gameView {
    PlayerID currentPlayer;
    Round currentRound;
	int currentScore;
	Player LG; //Lord Godalming
	Player DS; //Dr. Seward
	Player VH; //Van Helsing
	Player MH; //Mina Harker
	Player DC; //Dracula

	//TO BE COMPLETED
};

//Supplementary functions
static void processTurn(GameView gameView, char *pastPlays); // Processes each turn for each player (process each 7 chars)
//static void processHunter(GameView gameView, char *pastPlays); // Process Hunter Type Turn
//static void processDracula(GameView gameView, char *pastPlays); // Process Dracula Type Turn


//Technical functions
static int arrayLength (char *pastPlays);
static void copyLocation (char *pastPlays, int counter, char *array)


// Creates a new GameView to summarise the current state of the game
GameView newGameView(char *pastPlays, PlayerMessage messages[]){
    GameView gameView = malloc(sizeof(struct gameView));
	assert(gameView != NULL);
	
	// Initialize
	gameView->currentRound = 0;
	gameView->LG->currentHealth = gameView->DS->currentHealth = gameView->VH->currentHealth = gameView->MH->currentHealth = GAME_START_HUNTER_LIFE_POINTS;
	gameView->DC->currentHealth = GAME_START_BLOOD_POINTS;
	gameView->currentScore = GAME_START_SCORE;
	gameView->currentPlayer = PLAYER_LORD_GODALMING;
	gameView->LG->currentLocation = gameView->DC->currentLocation = gameView->VH->currentLocation = gameView->MH->currentLocation = gameView->DC->currentLocation = UNKNOWN_LOCATION;
    
	int playLength = arrayLength (pastPlays);
	int counter = 0;
	if(playLength == 0){
		return gameView;
	} else {
		while(playLength[counter] != NULL){
			processTurn(gameView, pastPlays);
            counter++;
		}
	}
	
	
	return gameView;
}
     
     
// Frees all memory previously allocated for the GameView toBeDeleted
void disposeGameView(GameView toBeDeleted)
{
    assert(toBeDeleted != NULL);

    free( toBeDeleted->LG->currentHealth );
    free( toBeDeleted->DS->currentHealth );
    free( toBeDeleted->VH->currentHealth );
    free( toBeDeleted->MH->currentHealth );
    free( toBeDeleted->DC->currentHealth );

    free( toBeDeleted->LG->currentLocation );
    free( toBeDeleted->DS->currentLocation);
    free( toBeDeleted->VH->currentLocation );
    free( toBeDeleted->MH->currentLocation );
    free( toBeDeleted->DC->currentLocation );

    free( toBeDeleted->currentRound );
    free( toBeDeleted->currentPlayer );
    free( toBeDeleted->currrentScore );'

    free( toBeDeleted->LG);
    free( toBeDeleted->DS);
    free( toBeDeleted->VH);
    free( toBeDeleted->MH);
    free( toBeDeleted->DC);

    free( toBeDeleted );
}


//// Functions to return simple information about the current state of the game

// Get the current round
Round getRound(GameView currentView)
{
    return(currentView->currentRound);
}

// Get the id of current player - ie whose turn is it?
PlayerID getCurrentPlayer(GameView currentView)
{
    return(currentView->currentPlayer);
}

// Get the current score
int getScore(GameView currentView)
{
	return (currentView->currentScore);
}

// Get the current health points for a given player
int getHealth(GameView currentView, PlayerID player)
{
	int health;
    if(player == PLAYER_LORD_GODALMING){
        health = currentView->LG->currentHealth;
    } else if (player == PLAYER_DR_SEWARD){
        health = currentView->DS->currentHealth;
    } else if (player == PLAYER_VAN_HELSING){
        health = currentView->VH->currentHealth;
    } else if (player == PLAYER_MINA_HARKER){
        health = currentView->MH->currentHealth;
    } else if (player == PLAYER_DRACULA){
        health = currentView->DC->currentHealth;
    } else
        printf("INVALID PLAYER INPUT");
        abort();
	return health;
}

// Get the current location id of a given player
LocationID getLocation(GameView currentView, PlayerID player)
{
	LocationID location = NULL;
	int health;
    if(player == PLAYER_LORD_GODALMING){
        health = currentView->LG->currentLocation;
    } else if (player == PLAYER_DR_SEWARD){
        health = currentView->DS->currentLocation;
    } else if (player == PLAYER_VAN_HELSING){
        health = currentView->VH->currentLocation;
    } else if (player == PLAYER_MINA_HARKER){
        health = currentView->MH->currentLocation;
    } else if (player == PLAYER_DRACULA){
        health = currentView->DC->currentLocation;
    } else
        printf("INVALID PLAYER INPUT");
        abort();
		
	return location;
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void getHistory(GameView currentView, PlayerID player,
                            LocationID trail[TRAIL_SIZE])
{
    
}

//// Functions that query the map to find information about connectivity

// Returns an array of LocationIDs for all directly connected locations

LocationID *connectedLocations(GameView currentView, int *numLocations,
                               LocationID from, PlayerID player, Round round,
                               int road, int rail, int sea)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return NULL;
}

//Supplementary Functions

void processTurn(char *pastPlays, int counter){
	char tempNewLocation [3];
    if(pastPlays[counter] == 'G'){
        counter++; // Advance to Location
        
        //Processing Location
        copyLocation(pastPlays,counter,tempNewLocation);
        gameView->LG->currentLocation = abbrevToID(tempNewLocation);
        counter = counter+2; // Advance to Actions
        
        //Processing Actions
        while(counter % 8 != 0){
            if(pastPlays[counter] == 'T'){
                gameView->LG->currentHealth = (gameView->LG->currentHealth)-2;
                counter++;
            } else if(pastPlays[counter] == 'V'){
                //VANQUISH IMMATURE VAMPIRE
                counter++
            } else if(pastPlays[counter] == 'D'){
                gameView->LG->currentHealth = (gameView->LG->currentHealth)-4;
                gameView->DC->currentHealth = (gameView->DC->currentHealth)-10;
                counter++;
            } else if(pastPlays[counter] == '.'){
                counter++;
            } else{
                printf("INVALID INPUT");
                abort();
            }
        }
    }else if(pastPlays[counter] == 'S'){
        counter++; // Advance to Location
        
        //Processing Location
        copyLocation(pastPlays,counter,tempNewLocation);
        gameView->DS->currentLocation = abbrevToID(tempNewLocation);
        counter = counter+2; // Advance to Actions
        
        //Processing Actions
        while(counter % 8 != 0){
            if(pastPlays[counter] == 'T'){
                gameView->DS->currentHealth = (gameView->DS->currentHealth)-2;
                counter++;
            } else if(pastPlays[counter] == 'V'){
                //VANQUISH IMMATURE VAMPIRE
                counter++
            } else if(pastPlays[counter] == 'D'){
                gameView->DS->currentHealth = (gameView->DS->currentHealth)-4;
                gameView->DC->currentHealth = (gameView->DC->currentHealth)-10;
                counter++;
            } else if(pastPlays[counter] == '.'){
                counter++;
            } else{
                printf("INVALID INPUT");
                abort();
            }
        }
    }else if(pastPlays[counter] == 'H'){
        counter++; // Advance to Location
        
        //Processing Location
        copyLocation(pastPlays,counter,tempNewLocation);
        gameView->VH->currentLocation = abbrevToID(tempNewLocation);
        counter = counter+2; // Advance to Actions
        
        //Processing Actions
        while(counter % 8 != 0){
            if(pastPlays[counter] == 'T'){
                gameView->VH->currentHealth = (gameView->VH->currentHealth)-2;
                counter++;
            } else if(pastPlays[counter] == 'V'){
                //VANQUISH IMMATURE VAMPIRE
                counter++
            } else if(pastPlays[counter] == 'D'){
                gameView->VH->currentHealth = (gameView->VH->currentHealth)-4;
                gameView->DC->currentHealth = (gameView->DC->currentHealth)-10;
                counter++;
            } else if(pastPlays[counter] == '.'){
                counter++;
            } else{
                printf("INVALID INPUT");
                abort();
            }
        }
    }else if(pastPlays[counter] == 'M'){
        counter++; // Advance to Location
        
        //Processing Location
        copyLocation(pastPlays,counter,tempNewLocation);
        gameView->MH->currentLocation = abbrevToID(tempNewLocation);
        counter = counter+2; // Advance to Actions
        
        //Processing Actions
        while(counter % 8 != 0){
            if(pastPlays[counter] == 'T'){
                gameView->MH->currentHealth = (gameView->MH->currentHealth)-2;
                counter++;
            } else if(pastPlays[counter] == 'V'){
                //VANQUISH IMMATURE VAMPIRE
                counter++
            } else if(pastPlays[counter] == 'D'){
                gameView->MH->currentHealth = (gameView->MH->currentHealth)-4;
                gameView->DC->currentHealth = (gameView->DC->currentHealth)-10;
                counter++;
            } else if(pastPlays[counter] == '.'){
                counter++;
            } else{
                printf("INVALID INPUT");
                abort();
            }
        }
    }else if(pastPlays[counter] == 'D'){
        counter++; // Advance to Location
        
        //Processing Location
        copyLocation(pastPlays,counter,tempNewLocation);
        gameView->DC->currentLocation = abbrevToID(tempNewLocation);
        counter = counter+2; // Advance to Actions
        
        //Processing Actions
        
        //TOBECOMPLETED
    }
}


int arrayLength (char *pastPlays){
	int length = 0;
	while(pastPlays[length] != NULL){
		counter++;
	}
	return counter;
}

void copyLocation (char *pastPlays, int counter, char *array){
    int tempCounter = 0;
    array[tempCounter] = pastPlays[counter];
    array[tempCounter+1] = pastPlays[counter+1];
    array[tempCounter+2] = NULL;
}
