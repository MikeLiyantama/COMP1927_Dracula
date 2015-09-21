// DracView.c ... DracView ADT implementation

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Globals.h"
#include "Game.h"
#include "dracView.h"
#include "DracView.h"
// #include "Map.h" ... if you decide to use the Map ADT

static int arrayLength (char *pastPlays);

     
//Players' Status
typedef struct _player {
	int currentHealth;
	LocationID currentLocation;

	//TO BE COMPLETED
}Player;
     
struct dracView {
    PlayerID currentPlayer;
    Round currentRound;
	int currentScore;
	Player LG; //Lord Godalming
	Player DS; //Dr. Seward
	Player VH; //Van Helsing
	Player MH; //Mina Harker
	Player DC; //Dracula
};
     



// Creates a new DracView to summarise the current state of the game
DracView newDracView(char *pastPlays, PlayerMessage messages[])
{
    DracView dracView = malloc(sizeof(struct dracView));
	assert(dracView != NULL);
	
	// Initialize
	dracView->currentRound = 0;
	dracView->LG->currentHealth = dracView->DS->currentHealth
                = dracView->VH->currentHealth 
                = dracView->MH->currentHealth 
                = GAME_START_HUNTER_LIFE_POINTS;
	dracView->DC->currentHealth = GAME_START_BLOOD_POINTS;
	dracView->currentScore = GAME_START_SCORE;
	dracView->currentPlayer = PLAYER_LORD_GODALMING;
	dracView->LG->currentLocation = dracView->DC->currentLocation 
                = dracView->VH->currentLocation
                = dracView->MH->currentLocation 
                = dracView->DC->currentLocation 
                = UNKNOWN_LOCATION;
    int playsLength = arrayLength(pastPlays);

    if(pastPlays = NULL)
        return dracView;
    int counter = 0;
    for(counter = 0; counter < playsLength ; counter++){
        if(pastPlays[counter] == 'G'){
            counter++;
            pastPlays[counter] == 2;
            pastPlays == 2
            
    }
    return dracView;
}
     
     
// Frees all memory previously allocated for the DracView toBeDeleted
void disposeDracView(DracView toBeDeleted)
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
    free( toBeDeleted->currrentScore );

    free( toBeDeleted->LG);
    free( toBeDeleted->DS);
    free( toBeDeleted->VH);
    free( toBeDeleted->MH);
    free( toBeDeleted->DC);

    free( toBeDeleted );
}


//// Functions to return simple information about the current state of the game

// Get the current round
Round giveMeTheRound(DracView currentView)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return(currentView->currentRound);
}

// Get the current score
int giveMeTheScore(DracView currentView)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return (currentView->currentScore);
}

// Get the current health points for a given player
int howHealthyIs(DracView currentView, PlayerID player)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    int health = 0;
    switch (player) {
    case PLAYER_LORD_GODALMING:
        health = currentView->LG->currentHealth;
        break;
    case PLAYER_DR_SEWARD:
        health = currentView->DS->currentHealth;
        break;
    case PLAYER_VAN_HELSING:
        health = currentView->VH->currentHealth;
        break;
    case PLAYER_MINA_HARKER:
        health = currentView->MH->currentHealth;
        break;
    case PLAYER_DRACULA:
        health = currentView->DC->currentHealth;
        break;
    default:
        printf("INVALID PLAYER INPUT");
        abort();
    }
    return health;
}

// Get the current location id of a given player
LocationID whereIs(DracView currentView, PlayerID player)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return 0;
}

// Get the most recent move of a given player
void lastMove(DracView currentView, PlayerID player,
                 LocationID *start, LocationID *end)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return;
}

// Find out what minions are placed at the specified location
void whatsThere(DracView currentView, LocationID where,
                         int *numTraps, int *numVamps)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return;
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void giveMeTheTrail(DracView currentView, PlayerID player,
                            LocationID trail[TRAIL_SIZE])
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
}

//// Functions that query the map to find information about connectivity

// What are my (Dracula's) possible next moves (locations)
LocationID *whereCanIgo(DracView currentView, int *numLocations, int road, int sea)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return NULL;
}

// What are the specified player's next possible moves
LocationID *whereCanTheyGo(DracView currentView, int *numLocations,
                           PlayerID player, int road, int rail, int sea)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return NULL;
}


Player playerstat(Player player, int health, LocationID location){
    player->health = health;
    player->location = location;
    return player;
}
