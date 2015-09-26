// DracView.c ... DracView ADT implementation

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Globals.h"
#include "Game.h"
#include "dracView.h"
#include "DracView.h"
#include "Map.h" //... if you decide to use the Map ADT

static int arrayLength (char *pastPlays);

     
//Players' Status
typedef struct _player {
	int currentHealth;
	LocationID currentLocation;
    History history;

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

typedef struct _history
{
    LocationID location;
    char torv[2];       //Trap or Vampire
    struct History *next;
};



// Creates a new DracView to summarise the current state of the game
DracView newDracView(char *pastPlays, PlayerMessage messages[])
{
    DracView dracView = malloc(sizeof(struct dracView));
    assert(dracView != NULL);
    
    // Initialize
    dracView->currentRound = 0;
    dracView->LG->currentHealth 
                            = dracView->DS->currentHealth
                            = dracView->VH->currentHealth 
                            = dracView->MH->currentHealth 
                            = GAME_START_HUNTER_LIFE_POINTS;
    dracView->DC->currentHealth = GAME_START_BLOOD_POINTS;
    dracView->currentScore = GAME_START_SCORE;
    dracView->currentPlayer = PLAYER_LORD_GODALMING;
    dracView->LG->currentLocation 
                            = dracView->DC->currentLocation 
                            = dracView->VH->currentLocation 
                            = dracView->MH->currentLocation 
                            = dracView->DC->currentLocation 
                            = UNKNOWN_LOCATION;
    
    int playLength = arrayLength (pastPlays);
    int counter = 0;
    if(playLength == 0){
        return dracView;
    } else {
        while(playLength[counter] != NULL){
            processTurn(pastPlays,counter,dracView);
            counter++;
        }
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
    return ((playerSelector(player,currentView))->currentHealth);
}

// Get the current location id of a given player
LocationID whereIs(DracView currentView, PlayerID player)
{
   return ((playerSelector(player,currentView))->currentLocation);
}

// Get the most recent move of a given player
void lastMove(DracView currentView, PlayerID player,
                 LocationID *start, LocationID *end)
{
    PlayerLink p = playerSelector(player,currentView);
    HistoryLink link = p->historyList->head;
    HistoryList l = p->historyList
    int length = historyLength(l);
    int counter = 1;
    while((counter+1) < length){
        link = link->next;
        counter++;
    }
    //Assign start
    start = link->location;
    end = link->next->location;
}

// Find out what minions are placed at the specified location
void whatsThere(DracView currentView, LocationID where,
                         int *numTraps, int *numVamps)
{
    TorVLink link = currentView->torvList->head;
    if(link == NULL){
        numTraps = 0;
        numVamps = 0;
    }else{
        while(link->next) != NULL && (link->location) != where){
            link = link->next;
        }
        if(link == NULL){
            numTraps = 0;
            numVamps = 0;
        }else{
            numTraps = link->t;
            numVamps = link->v;
        }
    }   
    
    //Free the vars
    link = NULL;
    free(link);
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void giveMeTheTrail(DracView currentView, PlayerID player,
                            LocationID trail[TRAIL_SIZE])
{
    PlayerLink p = playerSelector(player,currentView);
    HistoryLink link = p->historyList->head;
    HistoryList l = p->historyList
    int length = historyLength(l);
    int counter = 0;
    if(length <= 6){ //History less than or equal to 6
        while(link != NULL){
            trail[counter] = link->location;
            link = link->next;
            counter++
        }
        while (counter < 6){
            trail[counter] = UNKNOWN_LOCATION;
            counter++;
        }
    } else { // History more than 6
        int startPos = (length - 6);
        int startCounter = 1;
        while(counter < int startPos){
            link = link->next;
            startCounter++;
        }   
        while(link != NULL){
            trail[counter] = link->location;
            link = link->next;
            counter++;
        }
    }
    
    //Free the vars
     p = NULL;
     link = NULL;
     l = NULL
     free(p);
     free(link);
     free(l);
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

playerLink playerSelector (PlayerID Player, gameView g){
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
        
    //Determining Player to be Processed
    gameView->currentPlayer = currentTurnSelector(char *pastPlays, int counter)
    counter++; // Advance to Location
        
    //Processing Location
    copyLocation(pastPlays,counter,tempNewLocation);
    (playerSelector(gameView->currentPlayer,gameView))->currentLocation = abbrevToID(tempNewLocation);
    counter = counter+2; // Advance to Actions
        
    //Processing Actions
    while(counter % 8 != 0){
        if(pastPlays[counter] == 'T'){
            (playerSelector(gameView->currentPlayer,gameView))->currentHealth = (gameView->LG->currentHealth)-2;
            counter++;
        } else if(pastPlays[counter] == 'V'){
            //VANQUISH IMMATURE VAMPIRE
            counter++
        } else if(pastPlays[counter] == 'D'){
            (playerSelector(gameView->currentPlayer,gameView))->currentHealth = (gameView->LG->currentHealth)-4;
            (playerSelector(gameView->currentPlayer,gameView))->currentHealth = (gameView->DC->currentHealth)-10;
            counter++;
        } else if(pastPlays[counter] == '.'){
            counter++;
        } else{
            printf("INVALID INPUT");
            abort();
        }
    }
}

void processDracula (char *pastPlays, int counter, GameView gameView){
    char tempNewLocation [3];
        
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
    
    //Processing Actions;
    
    
    //TO BE COMPLETED
    
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

void hunterEncounter(LocationID hunter, LocationID dracula, int currentScore){
    if(hunter == dracula){
        currentScore = currentScore - LIFE_LOSS_DRACULA_ENCOUNTER;
    }
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

History newRecord(LocationID location, char torv){
    History *record = malloc(sizeof(History));
    record->location = location;
    record->next = NULL;
    record->torv = torv;
}

void insertHistory(History h, History r){
    if(h == NULL){
        h = r;
        return;
    }
    History *curr = h;
    while(curr->next != NULL){
        curr = curr->next;
    }
    curr->next = NULL;
}
    