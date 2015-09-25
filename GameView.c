// GameView.c ... GameView ADT implementation

#include <stdlib.h>
#include <assert.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
// #include "Map.h" ... if you decide to use the Map ADT

#define HUNTER_MAX_HEALTH       9

//Players' Status
typedef struct _player *playerLink //Pointer to Player
typedef struct _player {
	int currentHealth;
	LocationID currentLocation;
    List historyList;
	//TO BE COMPLETED
}Player;

//Players location storing
typedef struct _history *HistoryLink
typedef struct _history {
    LocationID location
    HistoryLink next;
}History
typedef struct _list{
    HistoryLink head;
}HistoryList



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
static void processTurn(char *pastPlays, int counter, GameView gameView); // Processes each turn for each player (process each 7 chars)
static void processHunter (char *pastPlays, int counter, GameView gameView); // Process Hunter Type Turn
static void processDracula (char *pastPlays, int counter, GameView gameView); // Process Dracula Type Turn

//Hunter specific functions
static void hunterRest(int currentHealth, int bool); //Score modifier for resting
static void maxHealth(int currentHealth); //Limit maximum health of Hunter

//Dracula Specific Functions
static void processDoubleBack(char *arrayLocation, LocationID currentLocation); //Processing doubleback turn
static void draculaEncounter(LocationID dracula, LocationID hunter1, LocationID hunter2 ,LocationID hunter3 ,LocationID hunter4, int currentHealth); //Score Modifier for hunter encounter
static void checkSea(LocationID location, int currentHealth); //Score modifier for SEA move

//Technical functions
static int arrayLength (char *pastPlays); //Same as strlen in string.h
static void copyLocation (char *pastPlays, int counter, char *array); // Same as strcpy in string.h
static playerLink playerSelector (PlayerID currentPlayer, gameView g); // Pointer to Player


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
			processTurn(pastPlays,counter,gameView);
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
	return ((playerSelector(player,currentView))->currentHealth);
}

// Get the current location id of a given player
LocationID getLocation(GameView currentView, PlayerID player)
{
	return ((playerSelector(player,currentView))->currentLocation);
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void getHistory(GameView currentView, PlayerID player,
                            LocationID trail[TRAIL_SIZE])
{
    int trailCounter = 0;
    
    
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
///////////////////////////
//Supplementary Functions//
///////////////////////////
void processTurn(char *pastPlays, int counter, GameView gameView){
	if(pastPlays[counter] != 'D'){
        processHunter (pastPlays,counter,gameView);
    }else{
        processDracula(pastPlays,counter,gameView);
    }
}


int arrayLength (char *pastPlays){
	int length = 0;
	while(pastPlays[length] != NULL){
		length++;
	}
	return length;
}

void copyLocation (char *pastPlays, int counter, char *array){
    int tempCounter = 0;
    array[tempCounter] = pastPlays[counter];
    array[tempCounter+1] = pastPlays[counter+1];
    array[tempCounter+2] = NULL;
}

playerLink playerSelector (PlayerID Player, GameView g){
    playerLink *temp = malloc(sizeof(struct _player));
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

void processHunter (char *pastPlays, int counter, GameView gameView){
    char tempNewLocation [3];
    int rest = FALSE;
    int turnCounter = counter+6;    
    //Determining Player to be Processed
    gameView->currentPlayer = currentTurnSelector(char *pastPlays, int counter)
    playerLink player = (playerSelector(gameView->currentPlayer,gameView)); //Pointer to current Player ADT.
    counter++; // Advance to Location
        
    //Processing Location
    copyLocation(pastPlays,counter,tempNewLocation);
    if(currentLocation == tempNewLocation){
        rest = TRUE;
    }
    player->currentLocation = abbrevToID(tempNewLocation);
    counter = counter+2; // Advance to Actions
        
    //Processing Actions
    while(counter < turnCounter){
        if(pastPlays[counter] == 'T'){
            player->currentHealth = (player->currentHealth)-2;
            void hunterHospital(int currentHealth, LocationID currentLocation);
            counter++;
        } else if(pastPlays[counter] == 'V'){
            //VANQUISH IMMATURE VAMPIRE
            counter++
        } else if(pastPlays[counter] == 'D'){
            player->currentHealth = (player->currentHealth)-LIFE_LOSS_DRACULA_ENCOUNTER;
            gameView->DC->currentHealth = (gameView->DC->currentHealth)-LIFE_LOSS_HUNTER_ENCOUNTER ;
            counter++;
        } else if(pastPlays[counter] == '.'){
            counter++;
        } else{
            printf("INVALID INPUT");
            abort();
        }
    }
    hunterRest(player->currentHealth, rest);
}

void processDracula (char *pastPlays, int counter, GameView gameView){
    char tempNewLocation [3];
    int turnCounter = counter+6;
    //Set currentTurn
    gameView->currentPlayer = currentTurnSelector(char *pastPlays, int counter)
    counter++; // Advance to Location
            
    //Processing Location
    copyLocation(pastPlays,counter,tempNewLocation);
    if(tempNewLocation == 'C?'){
        gameView->DC->currentLocation = CITY_UNKNOWN
    }else if (tempNewLocation == 'S?'){
        gameView->DC->currentLocation = SEA_UNKNOWN
    }else if (tempNewLocation == 'HI'){
        //Stays, do nothing;
    }else if (tempNewLocation == 'TP'){
        gameView->DC->currentLocation = CASTLE_DRACULA
    }else if (tempNewLocation[0] == 'D' && tempNewLocation[1] != 'U'){ // Not Dublin
        processDoubleBack(tempNewLocation,gameView->DC->currentLocation); 
    }else{
        gameView->DC->currentLocation = abbrevToID(tempNewLocation);
    }
    counter = counter+2; // Advance to Actions
    
    //Processing Encounter;
    while(counter < (turnCounter-3)){
        if(pastPlays[counter] == 'T' ){
            //Place Trap at currentLocation
        }else if(pastPlays[counter] == 'V'){
            //Place Immature Dracula at currentLocation
        }
        counter++;
    }
    
    //Processing Action;
    while(counter < turnCounter){
        if(pastPlays[counter] == 'M'){
            //Trap is gone
        }else if (pastPlays[counter] == 'V'){
            //Vampire has Matured
            gameView->currentScore = (gameView->currentScore) - SCORE_LOSS_VAMPIRE_MATURES;
        }
        counter++
    }
    counter++
    
    //Score modifiers
    draculaEncounter(gameView->DC->currentLocation, gameView->LG->currentLocation, gameView->DS->currentLocation, gameView->VH->currentLocation,gameView->MH->currentLocation,gameView->currentScore);
    checkSea(gameView->DC->currentLocation, gameView->DC->currentHealth);
    draculaCastle(gameView->DC->currentLocation, gameView->DC->currentHealth);
    
    gameView->currentScore = (gameView->currentScore)-SCORE_LOSS_DRACULA_TURN; 
}

PlayerID currentTurnSelector(char *pastPlays, int counter){
    PlayerID player;
    if(pastPlays[counter] == 'G'){
        player = PLAYER_LORD_GODALMING;
    }else if(pastPlays[counter] == 'S'){
        player = PLAYER_DR_SEWARD;
    }else if(pastPlays[counter] == 'H'){
        player = PLAYER_VAN_HELSING;
    }else if(pastPlays[counter] == 'M'){
        player = PLAYER_MINA_HARKER;
    }else if(pastPlays[counter] == 'D'){
        player = PLAYER_DRACULA ;
    }
    return player;
}

void hunterRest(int currentHealth, int bool){
    if(bool == TRUE){
        currentHealth = currentHealth + LIFE_GAIN_REST;
        maxHealth(currentHealth)
    }
}

void maxHealth(int currentHealth){
    if(currentHealth > 9){
        currentHealth = HUNTER_MAX_HEALTH;
    }
}

void hunterHospital(int currentHealth, LocationID currentLocation){ //Teleport to Hospital if Hunter's health below 0
    if(currentHealth < 0){
        currentLocation = ST_JOSEPH_AND_ST_MARYS;
        currentHealth = 0;
    }
}

void processDoubleBack(char *arrayLocation, LocationID currentLocation){
    int turn = arrayLocation[1] - '0';
    //Read X turn before current turn, assign current location to that X turn location
} 

void draculaEncounter(LocationID dracula, LocationID hunter1, LocationID hunter2 ,LocationID hunter3 ,LocationID hunter4, int currentHealth){
    if(dracula == hunter1 || dracula == hunter2 || dracula == hunter3 || dracula == hunter4){
        currentHealth = currentHealth - LIFE_LOSS_HUNTER_ENCOUNTER;
    }
}

void checkSea(LocationID location, int currentHealth){
    if( idToType(location) == 'SEA')currentHealth = currentHealth - LIFE_LOSS_SEA; 
}

void draculaCastle(LocationID location, int currentHealth){
    if(location == CASTLE_DRACULA){
        currentHealth = currentHealth + LIFE_GAIN_CASTLE_DRACULA;
    }
}