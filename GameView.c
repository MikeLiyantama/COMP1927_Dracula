// GameView.c ... GameView ADT implementation

#include <stdlib.h>
#include <assert.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
// #include "Map.h" ... if you decide to use the Map ADT

#define	EMPTY_LOCATION		0

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
static void processHunter(GameView gameView, char *pastPlays); // Process Hunter Type Turn
static void processDracula(GameView gameView, char *pastPlays); // Process Dracula Type Turn



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
    
	char *playsPointer = &pastPlays[0];
	if (*pastPointer == NULL) {
		break;
	}
	else {
		while (*pastPointer != NULL) {
			gameView->currentRound++;
			processTurn(gameView, pastPlays);
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
	return (gameView->currentScore);
}

// Get the current health points for a given player
int getHealth(GameView currentView, PlayerID player)
{
	int health = 0;
	switch (player) {
	case PLAYER_LORD_GODALMING:
		health = gameView->LG->currentHealth;
		break;
	case PLAYER_DR_SEWARD:
		health = gameView->DS->currentHealth;
		break;
	case PLAYER_VAN_HELSING:
		health = gameView->VH->currentHealth;
		break;
	case PLAYER_MINA_HARKER:
		health = gameView->MH->currentHealth;
		break;
	case PLAYER_DRACULA:
		health = gameView->DC->currentHealth;
		break;
	default:
		printf("INVALID PLAYER INPUT");
		abort();
	}
	return health;
}

// Get the current location id of a given player
LocationID getLocation(GameView currentView, PlayerID player)
{
	LocationID location = NULL;
	switch (player) {
	case PLAYER_LORD_GODALMING:
		location = gameView->LG->currentLocation;
		break;
	case PLAYER_DR_SEWARD:
		location = gameView->DS->currentLocation;
		break;
	case PLAYER_VAN_HELSING:
		location = gameView->VS->currentLocation;
		break;
	case PLAYER_MINA_HARKER:
		location = gameView->MH->currentLocation;
		break;
	case PLAYER_DRACULA:
		location = gameView->DC->currentLocation;
		break;
	default:
		printf("INVALID PLAYER INPUT");
		abort();
	}
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

/*
static void processTurn(GameView gameView, char *pastPlays) {
	if (pastPlays == 'G') {
		processHunter(gameView, *pastPlays);
	} else if (pastPlays == 'S') {
		processHunter(gameView, *pastPlays);
	} else if (pastPlays == 'H') {
		processHunter(gameView, *pastPlays);
	} else if (pastPlays == 'M') {
		processHunter(gameView, *pastPlays);
	} else if (pastPlays == 'D') {
		processDracula(gameView, *pastPlays);
	} else {
		printf("INVALID TURN");
		abort();
	}
}
*/
