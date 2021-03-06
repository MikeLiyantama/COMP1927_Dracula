// HunterView.c ... HunterView ADT implementation

#include <stdlib.h>
#include <assert.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "HunterView.h"
#include "Map.h" //... if you decide to use the Map ADT
     
//Players' Status
typedef struct _player *PlayerLink; //Pointer to Player
typedef struct _player {
	int currentHealth;
	LocationID currentLocation;
    HistoryList historyList;
}Player;

//Players location storing
typedef struct _history *HistoryLink;
typedef struct _history {
    LocationID location;
    HistoryLink next;
}History;
typedef struct _historyList{
    HistoryLink head;
}HistoryList;

//Trap & Vampire storing
typedef struct _torv *TorVLink;
typedef struct _torv{
    LocationID location;
    int v; //Vampire
    int t; //Trap
    TorVLink next;
}TorV;
typedef struct _torvList{
    TorVLink head;
}TorVList;

//LinkedList for map functions
typedef struct _location *LocationLink;
typedef struct _location{
    LocationID location;
    LocationLink next;
}LocationRep;
typedef struct _locationList{
    LocationLink head;
}LocationList;

struct gameView {
    PlayerID currentPlayer;
    Round currentRound;
	int currentScore;
	Player LG; //Lord Godalming
	Player DS; //Dr. Seward
	Player VH; //Van Helsing
	Player MH; //Mina Harker
	Player DC; //Dracula
    TorVList torvList;
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
static PlayerLink playerSelector (PlayerID currentPlayer, gameView g); // Pointer to Player

//LinkedList Functions
static void historyAdd(HistoryList l, LocationID currLocation);
static int historyLength(HistoryList l);
static void torvAdd(TorVList l, LocationID currLocation, int vampire, int trap);
static void torvRemove(TorVList l, LocationID currLocation, int vampire, int trap);

//Linkedlist Map Location
static LocationList newLocation();
void addLocation(LocationList l, LocationID new);
int countLocation(LocationList l);

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
    
    int playLength = arrayLength (pastPlays);
	int counter = 0;
	if(playLength == 0){
		return hunterView;
	} else {
		while(playLength[counter] != NULL){
			processTurn(pastPlays,counter,hunterView);
            counter++;
		}
    }
	return hunterView;
}    
     
// Frees all memory previously allocated for the HunterView toBeDeleted
void disposeHunterView(HunterView toBeDeleted){
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
    PlayerLink p = playerSelector(player,currentView);
    HistoryLink link = p->historyList->head;
    HistoryList l = p->historyList
    int length = historyLength(l);
    int counter = 0;
    if(length <= 6){ //History less than or equal to 6
        while(link != NULL){
            int unknownPlaceCounter = TRAIL_SIZE - length;
            while(unknownPlaceCounter > 0)
                trail[counter] = UNKNOWN_LOCATION;
                link = link->next;
                counter--;
                unknownPlaceCounter--;
            }
            while(counter > 0){
                trail[counter] = link->location;
                link = link->next;
                counter--;
            }
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
}

//// Functions that query the map to find information about connectivity

// What are my possible next moves (locations)
LocationID *whereCanIgo(HunterView currentView, int *numLocations,
                        int road, int rail, int sea)
{
    Map map = newmap();
    TransportID transport;
    LocationList tempLoc = newLocation();
    if(road == 1) {
        transport = ROAD;
    } else if(rail == 1){
        transport = RAIL;
    } else if(boat == 1) {
        transport = BOAT;
    }
    
    //Scanning transport
    VList temp = map->connections[from];
    while(temp != NULL){
        if(temp->type == transport){
            if(transport == RAIL){
                if(round % 4 == 0){
                    temp = temp->next;
                }
            }else{
                addLocation(tempLoc, temp->v);
                temp = temp->next;
            }
        }else{
            temp = temp->next;
        }
    }
    
    destroyMap(map);
    
    //Counting nodes
    int counter = countLocation(tempLoc);
    
    //Place connected ID to array
    LocationID connectedPlaces[(counter-1)];
    int tempCounter = 0;
    LocationLink tempLink = tempLoc->head;
    while(tempLink !=NULL){
        connectedPlaces[tempCounter] = tempLink->location;
        tempLink = tempLink->next;
        tempCounter++;
    }
    
    return *connectedPlaces;
}

// What are the specified player's next possible moves
LocationID *whereCanTheyGo(HunterView currentView, int *numLocations,
                           PlayerID player, int road, int rail, int sea)
{
    Map map = newmap();
    TransportID transport;
    LocationList tempLoc = newLocation();
    if(road == 1) {
        transport = ROAD;
    } else if(rail == 1){
        transport = RAIL;
    } else if(boat == 1) {
        transport = BOAT;
    }
    
    //Scanning transport
    VList temp = map->connections[from];
    while(temp != NULL){
        if(temp->type == transport){
            if(player == PLAYER_DRACULA && (transport == RAIL || temp->v == ST_JOSEPH_AND_ST_MARYS)){
                temp = temp->next;
            } else if((player == PLAYER_DR_SEWARD || player == PLAYER_LORD_GODALMING || player == PLAYER_MINA_HARKER || player == PLAYER_VAN_HELSING) && transport == RAIL){
                if(round % 4 == 0){
                    temp = temp->next;
                }
            }else{
                addLocation(tempLoc, temp->v);
                temp = temp->next;
            }
        }else{
            temp = temp->next;
        }
    }
    
    destroyMap(map);
    
    //Counting nodes
    int counter = countLocation(tempLoc);
    
    //Place connected ID to array
    LocationID connectedPlaces[(counter-1)];
    int tempCounter = 0;
    LocationLink tempLink = tempLoc->head;
    while(tempLink !=NULL){
        connectedPlaces[tempCounter] = tempLink->location;
        tempLink = tempLink->next;
        tempCounter++;
    }
    
    return *connectedPlaces;
}

///////////////////////////
//Supplementary Functions//
///////////////////////////
int arrayLength (char *pastPlays){
	int length = 0;
	while(pastPlays[length] != NULL){
		length++;
	} return length;
}

void copyLocation (char *pastPlays, int counter, char *array){
    int tempCounter = 0;
    array[tempCounter] = pastPlays[counter];
    array[tempCounter+1] = pastPlays[counter+1];
    array[tempCounter+2] = NULL;
}

PlayerLink playerSelector (PlayerID Player, GameView g){
    PlayerLink *temp = malloc(sizeof(struct _player));
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


//////////////////
//MAIN FUNCTIONS//
//////////////////

void processTurn(char *pastPlays, int counter, GameView gameView){
	if(pastPlays[counter] != 'D'){
        processHunter (pastPlays,counter,gameView);
    }else{
        processDracula(pastPlays,counter,gameView);
    }
}


void processHunter (char *pastPlays, int counter, GameView gameView){
    char tempNewLocation [3];
    int rest = FALSE;
    int turnCounter = counter+6;    
    //Determining Player to be Processed
    gameView->currentPlayer = currentTurnSelector(char *pastPlays, int counter)
    PlayerLink player = (playerSelector(gameView->currentPlayer,gameView)); //Pointer to current Player ADT.
    counter++; // Advance to Location
        
    //Processing Location
    copyLocation(pastPlays,counter,tempNewLocation);
    if(currentLocation == tempNewLocation){
        rest = TRUE;
    }
    player->currentLocation = abbrevToID(tempNewLocation);
    counter = counter+2; // Advance to Actions
        
    //Processing Actions
    while(counter <= turnCounter){
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
    while(counter < (turnCounter-2)){
        if(pastPlays[counter] == 'T' ){
            //Place Trap at currentLocation
        }else if(pastPlays[counter] == 'V'){
            //Place Immature Dracula at currentLocation
        }
        counter++;
    }
    
    //Processing Action;
    while(counter <= turnCounter){
        if(pastPlays[counter] == 'M'){
            //Trap is gone
        }else if (pastPlays[counter] == 'V'){
            //Vampire has Matured
            gameView->currentScore = (gameView->currentScore) - SCORE_LOSS_VAMPIRE_MATURES;
        }
        counter++
    }
    
    //Score modifiers
    draculaEncounter(gameView->DC->currentLocation, gameView->LG->currentLocation, gameView->DS->currentLocation, gameView->VH->currentLocation,gameView->MH->currentLocation,gameView->currentScore);
    checkSea(gameView->DC->currentLocation, gameView->DC->currentHealth);
    draculaCastle(gameView->DC->currentLocation, gameView->DC->currentHealth);
    
    gameView->currentScore = (gameView->currentScore)-SCORE_LOSS_DRACULA_TURN; 
}

/////////////////////////////
//HUNTER SPECIFIC FUNCTIONS//
/////////////////////////////

void hunterRest(int currentHealth, int bool){
    if(bool == TRUE){
        currentHealth = currentHealth + LIFE_GAIN_REST;
        maxHealth(currentHealth);
    }
}

void maxHealth(int currentHealth){
    if(currentHealth > 9)currentHealth = HUNTER_MAX_HEALTH;
}

void hunterHospital(int currentHealth, LocationID currentLocation){ //Teleport to Hospital if Hunter's health below 0
    if(currentHealth < 0){
        currentLocation = ST_JOSEPH_AND_ST_MARYS;
        currentHealth = 0;
    }
}
//////////////////////////////
//DRACULA SPECIFIC FUNCTIONS//
//////////////////////////////
void processDoubleBack(char *arrayLocation, HistoryList l, int nBack, LocationID currlocation){
    int length = (historyLength(l) - nBack);
    int counter = 1;
    HistoryLink link = l->head;
    while(counter < length){
        link = link->next;
        counter++;
    }
    currLocation = link->location;
    link = NULL;
    free(link);
} 

void draculaEncounter(LocationID dracula, LocationID hunter1, LocationID hunter2 ,LocationID hunter3 ,LocationID hunter4, int currentHealth){
    if(dracula == hunter1 || dracula == hunter2 || dracula == hunter3 || dracula == hunter4)currentHealth = currentHealth - LIFE_LOSS_HUNTER_ENCOUNTER;
}

void checkSea(LocationID location, int currentHealth){
    if( idToType(location) == 'SEA')currentHealth = currentHealth - LIFE_LOSS_SEA; 
}

void draculaCastle(LocationID location, int currentHealth){
    if(location == CASTLE_DRACULA)currentHealth = currentHealth + LIFE_GAIN_CASTLE_DRACULA;
}

////////////////////////////////
//HISTORY LINKEDLIST FUNCTIONS//
////////////////////////////////

void historyAdd(HistoryList l, LocationID currLocation){
    HistoryLink link = l;
    History newHistory == malloc(sizeof(History));
    newHistory->location = currLocation;
    newHistory->next = NULL;
    
    link = l->head;
    if(link == NULL){
        l->head = newHistory;
        free(link);
    } else {
        while(link->next != NULL){
            link = link->next;
        }
        link->next = newHistory;
    }
}

int historyLength(HistoryList l){
    int length = 0;
    HistoryLink link = l->head;
    while(link != NULL){
        length++
        link = link->next;
    }
    return length;
}

////////////////////////////
//Trap & Vampire Functions//
////////////////////////////

void torvAdd(TorVList l, LocationID currLocation, int vampire, int trap){
    TorVLink link = l->head;
    if(link == NULL){ //When list is empty
        TorV newTorV == malloc(sizeof(History));
        newTorV->location = currLocation;
        newTorV->v = vampire;
        newTorV->t = trap;
        newTorV->next = NULL;
        link = newTorV;
    }else{
        while(link->next) != NULL && (link->location) != currLocation){
            link = link->next;
        }   
        if(link->location == currentLocation){ //Existing data found
            link->v = (link->v) + vampire;
            link->t = (link->t) + trap;
        }else{ //Create new Entry
            TorV newTorV == malloc(sizeof(History));
            newTorV->location = currLocation;
            newTorV->v = vampire;
            newTorV->t = trap;
            newTorV->next = NULL;
            link->next = newTorV;
        }
    }
}

void torvRemove(TorVList l, LocationID currLocation, int vampire, int trap){
    TorVLink link = l->head;
    while(link->next) != NULL && (link->location) != currLocation){
            link = link->next;
    }
    link->v = (link->v) - vampire;
    link->t = (link->t) - trap;
    
    //Delete Entry if Trap & Vampire = 0
    if(link->v == 0 && link->t == 0){
        TorVLink tempLink = l->head;
        while(tempLink->next != link){
            tempLink->tempLink->next;
        }
        tempLink->next = link->next;
        free(link);
    }  
} 

////////////////////////////
//Map LinkedList Functions//
////////////////////////////
LocationList newLocation(){
    LocationList new = malloc(sizeof(LocationList));
    new->head = NULL;
    return new;
}

void addLocation(LocationList l, LocationID new){
    LocationLink temp = l->head;
    if(temp == NULL){
        LocationRep newLocation = malloc(sizeof(LocationRep));
        newLocation->location = new;
        newLocation->next = NULL;
        temp = newLocation;
    }
    else{
        while(temp->next != NULL){
            temp = temp->next;
        }
        LocationRep newLocation = malloc(sizeof(LocationRep));
        newLocation->location = new;
        newLocation->next = NULL;
        temp->next = newLocation;
    }
}

int countLocation(LocationList l){
    LocationLink temp = l->head;
    int counter = 0;
    while(l != NULL){
        counter++;
        temp = temp->next;
    }
    
    return counter;
}