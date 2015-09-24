// HunterView.c ... HunterView ADT implementation

#include <stdlib.h>
#include <assert.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "HunterView.h"
// #include "Map.h" ... if you decide to use the Map ADT
     
//Pointers Misc
typedef struct _player *playerLink //Pointer to Player
     
     
//Players' Status
typedef struct _player {
	int currentHealth;
	LocationID currentLocation;

	//TO BE COMPLETED
}Player;     
     
struct hunterView {
    PlayerID currentPlayer;
    Round currentRound;
	int currentScore;
	Player LG; //Lord Godalming
	Player DS; //Dr. Seward
	Player VH; //Van Helsing
	Player MH; //Mina Harker
	Player DC; //Dracula
};
     

static playerLink playerSelector (PlayerID currentPlayer, gameView g);

// Creates a new HunterView to summarise the current state of the game
HunterView newHunterView(char *pastPlays, PlayerMessage messages[])
{
    HunterView hunterView = malloc(sizeof(struct hunterView));
	assert(hunterView != NULL);
	
	// Initialize
	hunterView->currentRound = 0;
	hunterView->LG->currentHealth = hunterView->DS->currentHealth = hunterView->VH->currentHealth = hunterView->MH->currentHealth = GAME_START_HUNTER_LIFE_POINTS;
	hunterView->DC->currentHealth = GAME_START_BLOOD_POINTS;
	hunterView->currentScore = GAME_START_SCORE;
	hunterView->currentPlayer = PLAYER_LORD_GODALMING;
	hunterView->LG->currentLocation = hunterView->DC->currentLocation = hunterView->VH->currentLocation = hunterView->MH->currentLocation = hunterView->DC->currentLocation = UNKNOWN_LOCATION;
    
    return hunterView;
}
     
     
// Frees all memory previously allocated for the HunterView toBeDeleted
void disposeHunterView(HunterView toBeDeleted)
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
Round giveMeTheRound(HunterView currentView)
{
    return (currentView->currentRound);
}

// Get the id of current player
PlayerID whoAmI(HunterView currentView)
{
    return (currentView->currentPlayer);
}

// Get the current score
int giveMeTheScore(HunterView currentView)
{
    return (currentView->currentScore);
}

// Get the current health points for a given player
int howHealthyIs(HunterView currentView, PlayerID player)
{
    return ((playerSelector(player,currentView))->currentHealth);
}

// Get the current location id of a given player
LocationID whereIs(HunterView currentView, PlayerID player)
{   
    return ((playerSelector(player,currentView))->currentLocation);
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void giveMeTheTrail(HunterView currentView, PlayerID player,
                            LocationID trail[TRAIL_SIZE])
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
}

//// Functions that query the map to find information about connectivity

// What are my possible next moves (locations)
LocationID *whereCanIgo(HunterView currentView, int *numLocations, int road, int sea)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return NULL;
}

// What are the specified player's next possible moves
LocationID *whereCanTheyGo(HunterView currentView, int *numLocations,
                           PlayerID player, int road, int rail, int sea)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return NULL;
}


//Suplementary Functions
playerLink playerSelector (PlayerID Player, gameView g){
    player *temp = malloc(sizeof(struct _player));
    if(Player == 0){
        temp = gameView->LG;
    }else if(currentPlayer == 1){
        temp = gameView->DS;
    }else if(currentPlayer == 2){
        temp = gameView->VH;
    }else if(currentPlayer == 3){
        temp = gameView->MH;
    }else if(currentPlayer == 4){
        temp = gameView->DC;
    }
    
    return temp;
}