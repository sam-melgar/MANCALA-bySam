/*Mancala Code */
#include <stdio.h>
void red();
void green();
void blue();
void purple();
void cyan();
void reset();
int title(void);
int mainmenu(void);
int drawmainmenu(void); 
void instructions(void);  
void initializeBoard(int pockets[]);
void drawGame(int pockets[]);
int whichPocket(int pockets[], int player);
int deposit(int pockets[], int choice, int player);
int endOfTurnSpecifics(int pockets[], int lastStone, int player);
int gameOver(int pockets[]);
void saveGame(int pockets[], int player);
int loadGame (int pockets[]);

int main(void) {
    int pockets[14]; // 14 pockets 
    int option_selected; //basically mainmenu() is supposed to return the userchoice number 
    int Game=0; //keeps the while loop of the actual game running
    int player=1; //for the whichPocket //END OF TURN SWITCHES IT
    int choice;
    int lastStone;
    int playagain=0; //bigger loop that allows the user to play again
    
    while(playagain==0){ //two while loop in main function 
        title();
        option_selected = mainmenu();  //call the mainmenu function and they choose 2 NEW GAME  or 3 LOAD GAME (instructions is in main menu + instructions function)
    
        if (option_selected==2) {
            initializeBoard(pockets); //populate the array with this function initializeBoard()
        } else if (option_selected==3) { //This is load game
        player = loadGame(pockets);
        
        }
    
        while(Game==0){  /* MEAT OF THE CODEEEE*/
            drawGame(pockets);
            choice = whichPocket(pockets, player);
            
                if (choice==-1) { //quits
                    return(0);
                }
                
            lastStone = deposit(pockets, choice, player); //what pocket the last stone lands in
            player = endOfTurnSpecifics(pockets, lastStone, player);
            Game = gameOver(pockets); //gameOver() will return 1 if the game is INDEED over so it exits the while loop
        }
    
        printf("GAME OVER!!!!\n");
        printf("The winner is ");
        
        if (pockets[6]> pockets[13]) {  //compare to see who wins
            printf("PLAYER 1\n");
        }else if (pockets[13] > pockets[6]) {
            printf("PLAYER 2\n");
        }else if (pockets[6] == pockets[13]) {
            printf("NO ONE. It's a tie.\n");
    }
    
    printf("If you want exit press any other number\n");
    printf("If you want to play again press 0\n"); 
    scanf("%d", &playagain); //big big while loop only continues if playagain = 0
    
    Game=0; //to play again
    }    

   return(0);
} 

int title(void) {
    
    printf(" **     **     *     **   *   *****    *    *         *    \n "); 
    printf("* *   * *    * *    * *  *  *        * *   *        * *   \n ");
    printf("*  * *  *   *---*   *  * *  *       *---*  *       *---*  \n ");
    printf("*   *   *  *     *  *   **   ***** *     * ****** *     * \n ");
    return(0);
}


int mainmenu(void) { //RETURNS USERCHOICE TO MAIN() AS "OPTION SELECTED"
    int userchoice;
    int ask=1;
    
    
    while(ask) { //made it a while loop to keep asking the user to input something 
    userchoice = drawmainmenu(); //drawmainmenu hardcodes the menu list and ask the user to input an option and we scan it into userchoice which is returned HERE
    switch(userchoice) //if statements
    {
        case 1: 
            printf("Ok you chose instructions.\n");
            instructions(); //instructions are simply here; did not add to main function because they are IF the user wants them with selecting "1"
            break;
        case 2:
            printf("Ok you chose ");
            red();
            printf("New Game\n\n\n"); //fresh mancala board
            reset();
            ask = 0;
            break;
        case 3: 
            printf("Ok you chose ");
            red();
            printf("Load Game\n"); //call load function at some point
            reset();
            ask = 0;
            break;
        default:
            drawmainmenu(); //simply draw the main menu again to choose a right option
        
    }
    }
    return(userchoice); //returns to MAIN to create a NEW game or LOAD game 
}

int drawmainmenu(void){
    int userchoice; 
    FILE *checkfile;
    
    checkfile = fopen("loadGame.txt", "r"); 
    
    
    printf("\n \n");
    printf("------------------------Main Menu----------------------------- \n");
    printf("      Choose an option by typing the corresponding #           \n");
    
    green(); //i created color functions 
    printf("                     1. How To Play \n                     ");
    reset(); //reset the color
    
    printf("2. New Game \n                     \n");
    
    /* THIS WILL SHOW AN OPTION FOR LOAD GAME IS THE FILE EXISTS */ 
    if (checkfile != NULL) {										//checks to give option 3
        printf("                     3. Load Game \n  "); 
    }
    
    red();
    printf("                  Please enter a number:\n");
    reset();
    
    scanf("%d", &userchoice); //user input to select an option
    
    if ( !(1<=userchoice && userchoice<=3) ) { //if not within this range 1-3 INVALID INPUT
        printf("INVALID INPUT: please chose an option.");
        drawmainmenu();
    }
    return(userchoice); //go back to mainmenu function to choose a case 
    
}

void instructions(void){
    
    red();
    printf("\n\nINSTRUCTIONS:\n ");  
    reset();
    printf("1. The Mancala Board consists of two rows, each with six pockets.\n ");
    printf("2. The game is set up with 4 stones in each of the 12 pockets and each\n    player claims one side of the boad and the endzone with their\n    player number\n ");
    printf("3. Player 1 starts by choosing a pocket on THEIR side and picks up all \n    stones from this pocket. The amount of stones are the amount of\n    spaces you will pass through while depositing a stone in\n    each space.\n ");
    printf("4. All players move counterclockwise so Player 2 does the same as step 3.\n ");
    printf("5. If a player passes their own endzone they can deposit a stone but you\n    cannot deposit stones into your opponent's endzone, you skip.\n ");
    printf("6. If your last stone is YOUR endzone, you get another turn!\n ");
    printf("7. If a player's stone lands on an empty pocket, they can take their\n    stone + opponents stone that are directly across from that pocket.\n");
    printf("8. GAME OVER when a player has 0 stones on their side. All stones\n    left on their respective sides goes to the player who owns the side.\n");
    printf("9. Whoever has the most stones wins.\n");
    printf("\n \n \n \n"); //spacing
    
    
}

void initializeBoard(int pockets[]) { //array that sets up what's inside these pockets
    int i;
    for (i=0; i<14; i++) {
        if (i==6 || i==13) {
         pockets[i]=0;
        }else{
        pockets[i]= 4;
        }
    }
}

int loadGame(int pockets[]) { //This function should read "loadGame.txt" and return an integer indicating the player whose turn it is next 
    FILE *ifile;
    int i, player;
    
    ifile = fopen("loadGame.txt", "r");
    
    if (ifile==NULL) { //if something went wrong during file reading the function should return -1 
        return(-1);
    }
    for(i=0; i<14; i++) {
        fscanf(ifile, "%d", &pockets[i]); 
        
    }
    fscanf(ifile, "%d", &player);
    return(player);   
}

void drawGame(int pockets[]) { //whenever you want to draw the board  \\1,2,3,4,5,6,7,8,
    int i;
   
   /*PLAYER 1 set up */
    printf("||*\\");
    red();
    printf("P1");
    reset();
    printf("||_______________________________________________________________|\n");
    printf("\n");
    red();
    printf("   |     |    5   |    4   |    3   |    2   |    1    |    0   |\n");
    reset();
    printf("   ^>>>>>^ < < < < < < < < < < < < < < < < < < < < < < < < < < <^<<<<<^\n");   
    printf("   ^     ^        ^        ^        ^        ^         ^        ^     ^\n");
    printf("   ^     ");
    for(i = 5; i > -1; i--) {
      if (i==0) {
           printf(" ^  %2d    ^     ^\n", pockets[i]); 
      }else{
      printf("^  %2d    ", pockets[i]);
      }
    }  
    printf("   ^     ^        ^        ^        ^        ^         ^        ^     ^\n");    
    
    /*Middle line that separates grid symmetrically + place to put the endzone numbers*/
    printf("   ^ %2d  > > > > > > > > > > > > > > > > > > > > > > > > > > > >  %2d  ^\n", pockets[6], pockets[13]);
    
    /*PLAYER 2 set up */
    printf("   ^     ^        ^        ^        ^        ^         ^        ^     ^\n");
    printf("   ^     ");
    for(i=7; i<13; i++){
        if (i==12) {
           printf(" ^  %2d    ^     ^\n", pockets[i]); 
        }else{
        printf("^  %2d    ", pockets[i]);
        }
    }  
    printf("   ^     ^        ^        ^        ^        ^         ^        ^     ^\n");
    printf("   ^     ^        ^        ^        ^        ^         ^        ^     ^\n");
    printf("   ^>>>>>^> > > > > > > > > > > > > > > > > > > > > > > > > > > ^<<<<<^\n");
    printf("                                                    \n");
    cyan();
    printf("   |     |   7    |   8    |   9    |   10   |    11   |   12   | \n");
    reset();
    printf("|_______________________________________________________________||*\\");
    cyan();
    printf(" P2 ");
    reset();
    printf("||\n\n\n");
}

int whichPocket(int pockets[], int player) { //ask the player what pocket to choose
    int choice;
//validate the user's choice CAN'T be empty; can't be another player's row
//return player's chose pocket 
//-1 IF THE PLAYER WISHES TO PAUSE THE GAME
 if (player==1) { //only pick pocket 0-5
     printf("Player 1: Which pocket? ");
     scanf("%d", &choice);
     if (choice == -1) {  //pause game
         
         purple();
         printf("You wish to PAUSE the game\n");
         saveGame(pockets, player); //call save game since they want to pause 
         red();
         printf("Save Game now exiting"); //made pause the way to exit 
         reset(); //color 
         
         return(choice);
         
     }else if(choice>5 || choice<0 ) { //this is the second option because we don't want this to prevent a player to pause the game 
        printf("INVALID INPUT: choose pockets between 0-5 \n");
        return(whichPocket(pockets, player)); //return whickpocket to ask until the computer gets a valid input
        
     }else if( pockets[choice] == 0){
         printf("Oops choose a pocket with more than zero stones. \n");
         return(whichPocket(pockets, player));
         
     }else{
         return(choice);
     }
 }
 if (player==2) { //only pick pocket 0-5
     printf("Player 2: Which pocket? ");
     scanf("%d", &choice);
     if (choice == -1) { 
     
         purple();
         printf("You wish to PAUSE the game\n");
         saveGame(pockets, player);
         red();
         printf("Save Game now exiting");
         reset(); //color 
         return(choice);
         
     }else if(choice<7 || choice>12 ) { //can't choose pockets 0, 1,2,3,4,5,6, 13 + INVALID
        printf("INVALID INPUT: choose pockets between 7-12 \n");
        return(whichPocket(pockets, player)); //recursively ask until they get a valid input
     }else if( pockets[choice] == 0){
         printf("Oops choose a pocket with more than zero stones.  \n");
         return(whichPocket(pockets, player));
     }else{
         return(choice);
     }
 }
	return(-1); //quits there was some error with player selection to avoid warning in terminal
}

int deposit(int pockets[], int choice, int player) { //RETURN Last pocket where last pebble placed ***PRAY THIS WORKS******
    int x, i, wrap;
    x = pockets[choice]; //X IS THE AMOUNT OF PEBBLESSSSSSS
    pockets[choice] = 0; //empty out the pocket before we move on but the pebble # is stored in x

    i=1;
    
    while( x>0) { //while the number of stones in that chosen pocket is grearter than 0 do this>>
        
        wrap = (choice+i)%14; // wrap adds 1 to choice which means take the next pocket; if you choose pockets[5]; wrap = 5 + i (<-1) % 14 = 6 
                              //(player 1 can actually go into this pockets[6] but player 2? needs to skip which is why the if statements are there to address this issue 
        //The modulus ^^ is a way to deal with the loop around so if you choose pockets[13]. 13= choice; wrap = 13 + i % 14 = 0 so pockets[wrap] = pockets[0] loop around works!!!
            if(player==1 && wrap==13) { //This if and else if statement makes sure that player's don't go into the opponent's endzone
                i++; //(move one forward in the board to avoid player 2's endzone)
                wrap=0;
            } 
            else if(player==2 && wrap==6){
                i++;//move one forward in the board to avoid player 1's endzone
                wrap=7; //wrap just become the next eligible/allowed pocket 
            }
        pockets[wrap]+= 1; // pockets[wrap] = pockets[wrap] + 1 INCREASE what's inside the pocket + 1 (add the stone basically)
        x--; //decrease the pebbles by each space you take
        i++; //increments i so that the wrap = choice +1 can focus on the subsequent pockets for every stone picked up 
        
        
    }
    drawGame(pockets);
    
    return(wrap); 
}

int endOfTurnSpecifics(int pockets[], int lastStone, int player) { //RETURN WHO'S TURN IS NEXT. + STEALING
    
    /*THE "IF THE LAST STONE LANDS IN YOUR ENDZONE RULE" */
    if (player==1 && lastStone==6) { //player 1 can go again because lastStone is the deposit() function which returns the Last pocket where last pebble placed 
        red();
        printf("Player 1 get's to go again!!!\n"); //so if last stone is 6 meaning at pockets[6] that's player 1's ENDZONE 
        reset();
        return(player);
    }else if(player==2 && lastStone==13) { //same logic here, if last stone is 13 so pocket[13] player 2's ENDZONE it means they can go again!
        cyan();
        printf("Player 2 get's to go again!!!\n");
        reset();
        return(player);
    }
    
    /*If statements that check for stealing + executes the stealing and if not goes about their day in the else statement to switch turns*/
    if (player==1 && (lastStone<6 && pockets[lastStone]==1) && pockets[12-lastStone]!=0){ //stealing 
        red();
        printf("Player 1 STEALS >:) \n");
        reset();
        pockets[6] += pockets[lastStone] + pockets[12 - lastStone]; // pockets[6]=pockets[6] +  pockets[lastStone] + pockets[12 - lastStone]
        pockets[12-lastStone] = 0; //we just stole the corresponding players stones
        pockets[lastStone]=0;
        return(player=2);
    }else if(player==2 && (lastStone>6 && pockets[lastStone]==1) && pockets[12-lastStone]!=0){
        cyan();
        printf("Player 2 STEALS >:) \n");
        reset();
        pockets[13] += pockets[lastStone] + pockets[12 - lastStone]; //add the stolen stones into player's endzone 
        pockets[12-lastStone]=0; 
        pockets[lastStone]=0;
        return(player=1);
    }else{
        if (player == 1){ 
            return(2);
        }else{
            return(1); //has to be player ==2
        }
        }
}

int gameOver( int pockets[]){
    int total1=0;
    int total2=0;
    int i;
    
    for (i=0; i<=5; i++) { 
        total1= pockets[i] + total1;
        total2= pockets[12-i] + total2; //relationship between row 1 and row 2 
    }
    if (total1==0 || total2 == 0) {
        for(i=0; i<=5; i++) {
            pockets[i] = 0; //empty the pockets now that the game is over
            pockets[12-i] = 0; 
        }
        pockets[6] = pockets[6] + total1;  //add the remaining stones 
        pockets[13] = pockets[13] + total2;
        drawGame(pockets); //could do this in main function
        return(1);
        
        
    }else{
        return(0);
    }
}

void saveGame(int pockets[], int player) {
    FILE *ifile;
    int i;
    printf(":-)");
    ifile= fopen("loadGame.txt", "w"); //will create the file in the thayer server 
    
    for(i=0; i<14; i++) {
        fprintf(ifile, "%d ", pockets[i]); //space to separate each number
        printf("THe LOOP WORKS ");
    }
    fprintf(ifile, " %d", player); //last number in the list is player
    fclose(ifile);
    printf("CLOSE FILE");
}


//colors----------------
void red() {
    printf("\033[1;31m");
}
void green() {
    printf("\033[1;32m");
}
void blue() {
    printf("\033[1;34m");
}
void purple() {
    printf("\033[1;35m");
}
void cyan() {
    printf("\033[1;36m");
}
void reset(){
    printf("\033[0m");
}
