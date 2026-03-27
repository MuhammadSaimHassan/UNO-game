#include<iostream>
#include<ctime>
#include<cstdlib>
#include<iomanip>
#include<conio.h>
#include<windows.h>
#include<string>
#include<fstream>

using namespace std;

const int colors = 4; // Red, Green, Blue, Yellow
const int cards = 15; // Numbered cards (0-9) and special cards (Skip (10), Reverse (11), Draw 2 (12), Wild (13), Wild Draw 4 (13).)
const int max_hand=106; // Maximum cards a player can hold
const int players = 2; // Number of players
int deck[colors][cards]={0}; // 2D array: rows = colors, columns = card types
int shuffledDeck[2][108]={-1};
int discardPile[max_hand]; // Discard pile
int discardTop = -1; // Index for the top of the discard pile
int deckSize=108;
int card;
int playerHands[players][max_hand];
int handSizes[players] = {0, 0};
int currentPlayer = 0; // Global variable to track current player
bool invalid=false;
bool exitGame=false;
bool uno=false;
bool load;
int Wins_p1=0;
int Wins_p2=0;
int moves_p1=0;
int moves_p2=0;
int totalGames=-1;
// Color Codes:
const int BLACK = 0;
const int BLUE = 1;
const int GREEN = 2;
const int CYAN = 3;
const int RED = 4;
const int MAGENTA = 5;
const int YELLOW = 6;
const int WHITE = 7;

// Both Functions Below were copied From the file shared by Sir Bilal :)
void setColor(int textColor, int bgColor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}
void clearScreen()
{
//      system("clear");  //For Mac /Linux;
		system("CLS"); //For Windows
}

int drawCard(int shuffledDeck[][108]); // Helper Function to withdraw cards from the deck!
char singleInput(); // Helper Function to validate inputs requiring only 1 character!
int validInput(int player, int handSizes[]); // Helper Functoin to validate inputs in string as well as integer!
void gameMechanic(); // Helper Function to manage all the working of the game so that Main function can be clean :)
void reset(); // Helper Function to reset all variables, if user exits to main menu!

// Muhammad Huzaima (24i-3014) ---- Student 1:
void initializeDeck(int deck[][cards]);
void dealCards(int shuffledDeck[][108], int playerHands[][max_hand], int handSizes[], int players);
void handleSpecialCard(int specialCardType);
void printPlayerHand(int player, int playerHands[][max_hand], int handSizes[]);
void printBoard(int card, int player, bool top);
void saveLoadGameResult(bool load, int &Wins_p1, int &Wins_p2, int winner, int moves_p1, int moves_p2);

// Arooj Abrar (24i-3170) ---- Student 2:
void shuffleDeck(int deck[][cards]);
bool isValidPlay(int playerCard, int topCard);
void playTurn(int player, int currentPlayer, int shuffledDeck[][108], int playerHands[][max_hand], int handSizes[]);
void updateDiscardPile(int card, int shuffledDeck[][108], int &deckSize);
bool callUno(bool uno, int player, int playerHands[][max_hand], int handSizes[], int shuffledDeck[][108]);

int main()
{
    menu:
    if(exitGame==true)
    {
        reset();
    }
	moves_p1=0;
    moves_p2=0;
    srand(time(0));
    exitGame=false;
    
	cout<<endl<<setw(9)<<""<<"                            ____________________________________________________ ";
	cout<<endl<<setw(10)<<""<<"                          |                                                    |\n";
	cout<<setw(55)<<"|     __        __ "<< setw(16)<<" __        __ "<<setw(17)<<"  __________      |"<<endl;
	cout<<setw(55)<<"|    |  |      |  |"<<setw(16)<<"|  |\\     |  |"<<setw(16)<<" /  ______  \\     |"<<endl;
	cout<<setw(55)<<"|    |  |      |  |"<<setw(16)<<"|  | \\    |  |"<<setw(17)<<"|  |      |  |    |"<<endl;
	cout<<setw(55)<<"|    |  |      |  |"<<setw(16)<<"|  |  \\   |  |"<<setw(17)<<"|  |      |  |    |"<<endl;
	cout<<setw(55)<<"|    |  |      |  |"<<setw(16)<<"|  |   \\  |  |"<<setw(17)<<"|  |      |  |    |"<<endl;
	cout<<setw(55)<<"|    |  |      |  |"<<setw(16)<<"|  |    \\ |  |"<<setw(17)<<"|  |      |  |    |"<<endl;
	cout<<setw(55)<<"|    |  |______|  |"<<setw(16)<<"|  |     \\|  |"<<setw(17)<<"|  |______|  |    |"<<endl;
	cout<<setw(54)<<"|     \\__________/"<<setw(17)<<"|__|      \\__|"<<setw(16)<<" \\__________/     |"<<endl;
	cout<<setw(10)<<""<<"                          |                                                    |\n";
    cout<<setw(10)<<""<<"                          |____________________________________________________|"<<endl;
	cout<<endl;
	
	cout<<"                                      ___________________________________________________"<<endl;
	cout<<"                                     |                                                   |"<<endl;
	cout<<"                                     |                     Main Menu                     |"<<endl;
	cout<<"                                     |___________________________________________________|"<<endl;
	cout<<"                                     |___________________________________________________|"<<endl;
	cout<<"                                     |                                                   |"<<endl;
	cout<<"                                     |                    1. Play Game                   |"<<endl;
	cout<<"                                     |___________________________________________________|"<<endl;
	cout<<"                                     |___________________________________________________|"<<endl;
	cout<<"                                     |                                                   |"<<endl;
	cout<<"                                     |                   2. Load History                 |"<<endl;
	cout<<"                                     |___________________________________________________|"<<endl;
	cout<<"                                     |___________________________________________________|"<<endl;
	cout<<"                                     |                                                   |"<<endl;
	cout<<"                                     |                   3. Instructions                 |"<<endl;
	cout<<"                                     |___________________________________________________|"<<endl;
	cout<<"                                     |___________________________________________________|"<<endl;
	cout<<"                                     |                                                   |"<<endl;
	cout<<"                                     |                      4. Quit                      |"<<endl;
	cout<<"                                     |___________________________________________________|"<<endl;
	cout<<"                                     |___________________________________________________|"<<endl;
	cout<<"                                     |                                                   |"<<endl;
	cout<<"                                     |               Press the Desired Number            |"<<endl;
	cout<<"                                     |___________________________________________________|"<<endl;
    cout<<endl<<endl;
    char choice;
    char exitKey;
    do
    {
        exitGame=false;
        invalid=false;
        choice=getch();
		switch(choice)
        {
            case '1':
            	clearScreen();
                cout<<"\n                                     ******************STARTING THE GAME.....!!!**********\n\n";
                gameMechanic(); //Calling the gameMechanic function, in this function the game is running!
                exitGame=true;
                cout<<"Press any key to goto Main Menu....\n";
                getch();
                clearScreen();
                goto menu;
                break;

            case '2':
                load=true;
                saveLoadGameResult(load, Wins_p1, Wins_p2, currentPlayer, moves_p1, moves_p2);
                exitGame=true;
                clearScreen();
                goto menu;
                break;

            case '3':
            	clearScreen();
                cout<<"\n                                     ******************Instructions!!!********************\n\n";
                cout<<"-> Press E any time after starting the Game to Exit\n";
                cout<<"-> Press P any time after starting the Game to Pause\n";
                cout<<"-> Press U any time after starting the Game to Call UNO\n";
                cout<<"-> Press D any time after starting the Game to Display Deck\n";
                cout<<"-> Press S any time after starting the Game to Display Special Cards\n";
                cout<<"---------------------------------------------------------------------------------------------\n";
                cout<<"\n\nPress any key to go back to main menu....\n";
                getch();
                clearScreen();
                goto menu;
                break;
            case '4':
            	clearScreen();
                cout<<"\nQuitting......!\n";
                exitGame=true;
                return 0;
                break;
            
            case 'e':
            	clearScreen();
                exitGame=true;
                cout<<"Do You Really Wish to exit? Enter E again to confirm: ";
                exitKey=singleInput();
                if(exitKey=='E' ||exitKey=='e')
                {
                    return 0;
                }
                else
                {
                    exitGame=false;
                    goto menu;
                }
                break;
            case 'E':
            	clearScreen();
                exitGame=true;
                cout<<"Do You Really Wish to exit? Enter E again to confirm: ";
                exitKey=singleInput();
                if(exitKey=='E' ||exitKey=='e')
                {
                	exitGame=true;
                    return 0;
                }
                else
                {
                    exitGame=false;
                    goto menu;
                }
                break;
            default:
                cout<<"Invalid Input! Try Again:\n";
                invalid=true;
                break;
        }
    }while(invalid==true || exitGame==false);
    
    return 0;
}
void reset()
{
    deck[colors][cards]={0}; // 2D array: rows = colors, columns = card types
    shuffledDeck[2][108]={-1};
    discardPile[max_hand]; // Discard pile
    discardTop = -1; // Index for the top of the discard pile
    deckSize=108;
    playerHands[players][max_hand];
    handSizes[0] = 0;
    handSizes[1] = 0;
    currentPlayer = 0; // Global variable to track current player
    invalid=false;
    exitGame=false;
    uno=false;
    moves_p1=0;
    moves_p2=0;
}
char singleInput()
{
    	string choice;
        invalid=false;
        getline(cin,choice);
        if(choice.length()>1)
        {
            invalid=true;
            return 'i'; // returning i means invalid!
        }
        else
        {
        	char option=choice[0];
            return option;
		}
}
int validInput(int player, int handSizes[])
{
        int index;
        int length;
        bool pause=false;
    do
    {
    	string choice;
        invalid=false;
        cout<<"Enter a card (1-"<<handSizes[player]<<"): ";
        getline(cin,choice);
        length=choice.length();index=0;
        for(int i=0;i<choice.length();i++)
        {
            if((choice[i]>=48 && choice[i]<=57) && length<4)
            {
                    invalid=false;
                    index=(choice[i]-48)+index*10;
            }
            else if((choice[i]=='e' || choice[i]=='E') && length==1)
            {
                exitGame=true;
                return -1;
            }
            else if((choice[i]=='u' || choice[i]=='U') && length==1)
            {
            	uno=true;
            	return -1;
			}
			else if((choice[i]=='p' || choice[i]=='P') && length==1)
			{
                char pause;
				do
                {
                    clearScreen();
                    cout<<"The Game is Paused! To Unpause Enter P again: ";
				    pause=getch();
                }while(pause!='p' && pause!='P');
                currentPlayer = (currentPlayer + 1) % players;
                clearScreen();
				return -1;
			}
			else if((choice[i]=='d' || choice[i]=='D') && length==1)
			{
				cout<<"-1 means no card at that position!\n";
				cout<<"COLOR 1: RED, COLOR 2: BLUE, COLOR 3: GREEN, COLOR 4: YELLOW\n";
				cout<<"Cards: (0-9) and special cards (Skip (10), Reverse (11), Draw 2 (12), Wild (13), Wild Draw 4 (14)\n";
				for(int j=0;j<108;j++)
				{
					cout<<"Color: "<<shuffledDeck[0][j]+1<<" Card: "<<shuffledDeck[1][j]<<endl;
				}
				cout<<"\nEnter any key to clear screen";
				getch();
				clearScreen();
				return -1;
			}
			else if((choice[i]=='s' || choice[i]=='S') && length==1)
			{
				cout<<"10: Skip, 11: Reverse, 12: Draw 2, 13: Wild, 14: Wild Draw 4\n";
				for(int j=0;j<108;j++)
				{
					if(shuffledDeck[1][j]>9)
					cout<<"Color: "<<shuffledDeck[0][j]+1<<" Card: "<<shuffledDeck[1][j]<<endl;
				}
				cout<<"\nEnter any key to clear screen";
				getch();
				clearScreen();
				return -1;
			}
            else if(index>handSizes[player])
            {
                cout << "\nInvalid input! Press any key to continue...\n";
                getch();
                clearScreen();
                invalid=true;
            }
            else
            {
                cout << "\nInvalid input!\n";
				invalid=true;
			}
        }
    }while(length<1 || index<0 || invalid==true);
    return index;
}
void gameMechanic()
{
    initializeDeck(deck);
    shuffleDeck(deck);
    dealCards(shuffledDeck, playerHands, handSizes, players);
    
    discardTop = 0;
    discardPile[discardTop] = drawCard(shuffledDeck);
    
    bool Winner = false;
    while (Winner==false)
	{
		invalid=false;
        cout << "\nCurrent discard pile top card: \n\n";
        bool top=true;
		for(int i=0;i<7;i++)
        {
            cout<<" ";
            printBoard(discardPile[discardTop], i, top);
            setColor(WHITE, BLACK);
            cout<<endl;
        }

        cout<<endl;
        playTurn(currentPlayer, currentPlayer, shuffledDeck, playerHands, handSizes);

        if(handSizes[currentPlayer]==0)
		{
            load=false;
            cout<<"\nPlayer "<<currentPlayer + 1<<" wins the game!\n";
            if(currentPlayer==0)
            Wins_p1++;
            else
            Wins_p2++;
            saveLoadGameResult(load, Wins_p1, Wins_p2, currentPlayer+1, moves_p1, moves_p2);
            Winner=true;
            exitGame=true;
        }
        if(invalid==false)
        currentPlayer=(currentPlayer + 1) % players;
        else
    	cout << "Invalid play. Try again!!!\n";
    }
}
void initializeDeck(int deck[][cards])
{
    for(int i=0; i<colors; i++)
	{
        for(int j=0; j<cards; j++)
		{
            deck[i][j]= 2;  // cards 1-12 are 2 in each color
        }
        // Wild Cards and 0's are only 1 in each row/color
        deck[i][0]= 1;
        deck[i][13]= 1;
        deck[i][14]= 1;
    }
}
void shuffleDeck(int deck[][cards])
{
	int row, col;// Variables for randomly selecting a color and card type
    for(int types=0;types<108;types++)
    {
    	do
    	{
    		row=rand()%colors;// Randomly select a color
    		col=rand()%cards;// Randomly select a card
        	shuffledDeck[0][types]=row; // At row=0, colors are stored!
        	shuffledDeck[1][types]=col; // At row=1, corresponding cards are stored!
		}while(deck[row][col]==0);
		deck[row][col]--; //Removing the card from the original Deck
	}
}
void dealCards(int shuffledDeck[][108], int playerHands[][max_hand], int handSizes[], int players)
{
    for(int i=0; i<players; i++)
	{
        for(int j=0; j<7; j++)
		{
            playerHands[i][handSizes[i]++] = drawCard(shuffledDeck);
        }
    }
}
int drawCard(int shuffledDeck[][108])
{
    if(deckSize==0)
    {
        updateDiscardPile(-1, shuffledDeck, deckSize);
    }
    else if(deckSize == 0 && discardTop==0)
    {
        cout<<"\nCannot Withdraw anymore Cards!!!\n----It was a DRAW----\n";
        exitGame=true;
        main();
        return '\0';
    }
    if(deckSize!=0)
    {
        int random;
        do
    	{
            random = rand() % 108;
        }while(shuffledDeck[1][random] == -1);
        card = (shuffledDeck[0][random]* 100) + shuffledDeck[1][random];
        shuffledDeck[1][random] = -1; // Mark the card as used
        deckSize--;
    }
    
    return card;
}
bool isValidPlay(int playerCard, int topCard)
{
    // Extract the color and type of the player's card
    int playerColor = playerCard / 100;
    int cardType = playerCard % 100;
    
    // Extract the color and type of the top card on the discard pile
    int topColor = topCard / 100;
    int topType = topCard % 100;

    // Wild cards (13 for Wild, 14 for Wild Draw Four) are always valid plays
    if(cardType == 13 || cardType == 14)
    {
        return true;
    }

    // Check if the colors match or the types match
    return (playerColor == topColor || cardType == topType);
}
void playTurn(int player, int currentPlayer, int shuffledCards[][108], int playerHands[][max_hand], int handSizes[])
{
    // Display the current player's turn and their hand
    bool refresh=false;
    flagPlay:
    cout << "\nPlayer " << player + 1 << "'s turn:\n";
    
    printPlayerHand(player, playerHands, handSizes);
    
    if(refresh==true)
    {
        for(int i=0;i<7;i++)
        {
            cout<<" ";
            printBoard(discardPile[discardTop], i, true);
            setColor(WHITE, BLACK);
            cout<<endl;
        }
    }
    // Allow the player to select a card or choose to draw a new one
    int choice = validInput(player, handSizes);
    // Check if the player calls UNO during their turn
    if(choice==-1)
    {
        if(uno==true)
        {
            if(callUno(uno, player, playerHands, handSizes, shuffledDeck))
            {
                cout << "You called UNO correctly!\n";
            }
            else
            {
                cout << "Penalty applied for incorrect UNO call.\n";
            }
            return;
        }

		if(exitGame==true)
        {
            cout<<"Do you really want to exit? To confirm Press E again: ";
            char exitKey = getch();
            if(exitKey=='e' || exitKey=='E')
            {
                clearScreen();
                main();
            }
            else
            {
                refresh=true;
                clearScreen();
                goto flagPlay;
            }
        }
    }
    if(handSizes[player] == 2 && !uno)
	{
        // Player has 2 cards but didn't call UNO
        if(!callUno(false, player, playerHands, handSizes, shuffledDeck))
		{
            cout << "Penalty applied for not calling UNO!\n";
            return;
        }
    }
        if(choice == 0)
        { // Player chooses to draw a card
            int drawnCard = drawCard(shuffledDeck); // Draw a card from the deck
            playerHands[player][handSizes[player]++] = drawnCard; // Add it to the player's hand
            cout << "You drew a card.\n";

            // Check if the drawn card can be played
            if(isValidPlay(drawnCard, discardPile[discardTop]))
            {
                flag: 
                cout << "Your drawn card matches the discard pile!\n";
                cout<<"Press any key to continue...\n";
                getch();
                clearScreen();
                cout << "\nPlayer " << player + 1 << "'s turn:\n\n";
                for(int i=0;i<7;i++)
       	 		{
            		cout<<" ";
            		printBoard(discardPile[discardTop], i, true);
            		setColor(WHITE, BLACK);
            		cout<<endl;
        		}
        		cout<<endl;
                printPlayerHand(player, playerHands, handSizes);
                cout << "\nEnter 'P' to play or 'S' to skip: ";
                char action = getch(); // Take player's decision
                if(action == 'P' || action == 'p')
                {
                    // Play the drawn card
                    updateDiscardPile(card, shuffledDeck, deckSize);
                    handSizes[player]--; // Reduce hand size
                    clearScreen();
                    cout << "You placed the drawn card.\n";

                    int cardType = drawnCard % 100; // Check if it's a special card
                    if(cardType >= 10)
                    { 
                        handleSpecialCard(cardType);
                    }
                    return;
                }
                else if(action == 'S' || action == 's')
                {
                    clearScreen();
                    cout << "You skipped your turn.\n";
                    return; // End the turn
                }
                else if(action=='U' || action =='u')
                {
                    uno=true;
                    callUno(uno, player, playerHands, handSizes, shuffledDeck);
                    cout<<"Press Any Key To Continue...";
                    getch();
                    clearScreen();
                }
                else if(action=='e' || action=='E')
                {
                    cout<<"\nDo you really want to exit? To confirm Press E again: ";
                    char exitKey = getch();
                    if(exitKey=='e' || exitKey=='E')
                    {
                        exitGame=true;
                        clearScreen();
                        main();
                    }
                    else
                    {
                        clearScreen();
                        goto flag;
                    }
                }
                else
                {
                    cout << "Invalid input!\n";
                    goto flag; // Re-prompt if input is invalid
                }
            }
            else
            {
                cout << "The drawn card doesn't match the discard pile. Turn skipped.\n";
                cout<<"Enter any key to continue...";
                getch();
                clearScreen();
                return;
            }
        }

        // Validate the selected card choice
        if(choice > handSizes[player])
        {
            cout << "Invalid input! Press any key to continue...\n";
            getch();
            invalid = true; 
            return;
        }

        // Get the selected card and check if it's playable
        int selectedCard = playerHands[player][choice - 1];
        if(isValidPlay(selectedCard, discardPile[discardTop]))
        {
            updateDiscardPile(selectedCard, shuffledDeck, deckSize); 
            handSizes[player]--; // Reduce the player's hand size
            if(player==0)
            moves_p1++;
            else
            moves_p2++;

            // Shift the remaining cards in the player's hand
            for(int i = choice - 1; i < handSizes[player]; i++)
            {
                playerHands[player][i] = playerHands[player][i + 1];
            }

            // Check for special card effects
            int cardType = selectedCard % 100;
            if(cardType >= 10)
            {
                handleSpecialCard(cardType);
            }
            invalid = false; // Input is valid
        }
        else
        {
            cout << "Invalid input! Press any key to continue...\n";
            getch();
            clearScreen();
            invalid = true; // Mark the play as invalid
        }

        clearScreen(); 
}
void handleSpecialCard(int cardType)
{
	char newColor;
    switch(cardType)
	{
        case 10: // Skip
            cout << "Next player skipped!\n";
            currentPlayer = (currentPlayer + 1) % players;
            break;
    	case 11: // Reverse
            cout << "Turn Reversed!\n";
            currentPlayer = (currentPlayer + 1) % players;
            break;
        case 12: // Draw Two
            cout << "Next player draws 2 cards!\n";
            for(int i = 0; i < 2; i++)
			{
                playerHands[(currentPlayer + 1) % players][handSizes[(currentPlayer + 1) % players]++] = drawCard(shuffledDeck);
            }
            currentPlayer = (currentPlayer + 1) % players;
            break;
        case 13: // Wild
            do    
            {
                flag_Wild:
                invalid=false;
                cout << "Choose a new color (1=Red, 2=Blue, 3=Green, 4=Yellow): ";
                newColor=getch();
                if(newColor=='e' || newColor=='E')
                {
                    cout<<"\nDo you really want to exit? To confirm Press E again: ";
                    char exitKey = getch();
                    if(exitKey=='e' || exitKey=='E')
                    {
                        exitGame=true;
                        clearScreen();
                        main();
                    }
                    else
                    {
                        clearScreen();
                        goto flag_Wild;
                    }
                }
                else if(newColor<'1' || newColor>'4')
                invalid=true;
            }while(invalid==true);
            
            switch(newColor)
            {
                case '1':
                    discardPile[discardTop] = 13;
                    break;
                case '2':
                    discardPile[discardTop] = 100 + 13;
                    break;
                case '3':
                    discardPile[discardTop] = 200 + 13;
                    break;
                case '4':
                    discardPile[discardTop] = 300 + 13;
            		break;
			}
            break;
        case 14: // Wild Draw Four
            cout << "Next player draws 4 cards!\n";
            for(int i = 0; i < 4; i++)
			{
                playerHands[(currentPlayer + 1) % players][handSizes[(currentPlayer + 1) % players]++] = drawCard(shuffledDeck);
            }
            do    
            {
                flag_Wild4:
                invalid=false;
                cout << "Choose a new color (1=Red, 2=Blue, 3=Green, 4=Yellow): ";
                newColor=getch();
                if(newColor=='e' || newColor=='E')
                {
                    cout<<"Do you really want to exit? To confirm Press E again: ";
                    char exitKey = getch();
                    if(exitKey=='e' || exitKey=='E')
                    {
                        clearScreen();
                        main();
                    }
                    else
                    {
                        clearScreen();
                        goto flag_Wild4;
                    }
                }
                else if(newColor<'1' || newColor>'4')
                invalid=true;
            }while(invalid==true);
            switch(newColor)
            {
                case '1':
                    discardPile[discardTop] = 14;
                    break;
                case '2':
                    discardPile[discardTop] = 100 + 14;
                	break;
				case '3':
                    discardPile[discardTop] = 200 + 14;
                	break;
				case '4':
                    discardPile[discardTop] = 300 + 14;
            		break;
			}// Encoding The cards...
            currentPlayer = (currentPlayer + 1) % players;
			break;
    }
}
void printPlayerHand(int player, int playerHands[][max_hand], int handSizes[])
{
    const int cardsPerRow = 7; // Maximum number of cards per row
	 // Calculate the number of rows required
    int rows = handSizes[player] / cardsPerRow; // Total rows
	if(handSizes[player] % cardsPerRow != 0)
	{ 
    	rows++; // Adding an extra row for the remaining cards
	}
    bool top = false;

    cout << "Your hand:\n\n";

    for(int row = 0; row < rows; row++)
    {
        int playerss = 0;
        int startIdx = row * cardsPerRow;
        int endIdx;
        if(row == rows - 1)
        {
            endIdx=handSizes[player];
        }
        else
        {
            endIdx=startIdx + cardsPerRow;
        }

        // Print cards in the current row
        for(int line = 0; line < cardsPerRow; line++)
        { // Adjust for card height
            for(int j = startIdx; j < endIdx; j++)
            {
                cout << " ";
                printBoard(playerHands[player][j], playerss, top); // Middle line prints the card value
                setColor(WHITE, BLACK);
                cout << " ";
            }
            playerss++;
            cout << endl;
        }
        setColor(WHITE, BLACK);
        cout << endl;

        // Print card indexes for the current row
        for(int j = startIdx; j < endIdx; j++)
        {
            if(j<10)
            cout << "      " << (j + 1) << "      ";
            else
            cout << "     " << (j + 1) << "     ";
        }
        cout << endl<<endl;
    }
}
// Print a card
void printBoard(int card, int player, bool top)
{
    int color = card / 100, type = card % 100;
    int colorss[] = {RED, BLUE, GREEN, YELLOW};
    string types[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "Skip", "Reverse", "Draw 2", "Wild", "Draw 4"};
    if(type!=13 && type!=14)
    setColor(WHITE, colorss[color]);
    if(top==true)
    setColor(WHITE, colorss[color]);
    if(player==0 || player == 6)
    // Pattern Printing the cards!!!
    cout<< "-----------";
    else if(player==1 || player== 2 || player == 4 || player == 5)
    cout<< "-         -";
    else if(player==3)
    {
        if(type<10)
        cout<<"-    "<<types[type]<<"    -";
        else if(type==12 || type==14)
        cout<<"-  "<<types[type]<<" -";
        else if(type==10 || type==13)
        cout<<"-   "<<types[type]<<"  -";
        else if(type==11)
        cout<<"- "<<types[type]<<" -";
    }
}

void updateDiscardPile(int card, int shuffledDeck[][108], int &deckSize)
{
    // Place the card on top of the discard pile
    discardPile[++discardTop] = card;

    // If the deck is empty, reshuffle the discard pile back into the deck
    if(deckSize == 0 && discardTop>0)
    {
        cout << "Deck is empty. Reshuffling discard pile...!\n\n";

        // Prepare to transfer all cards from the discard pile (except the top card) back into the deck
        int newDeckIndex = 0;
        for(int i = 0; i < discardTop; i++)
        {
            shuffledDeck[0][newDeckIndex] = discardPile[i] / 100; // Extract and store card color
            shuffledDeck[1][newDeckIndex] = discardPile[i] % 100; // Extract and store card type
            newDeckIndex++;
        }
        // Update the deck size with the number of cards transferred
        deckSize = discardTop - 1;

        // Reset the discard pile to only contain the top card
        discardTop = 0;
        discardPile[discardTop] = card;

        // Create a temporary array to hold the deck for reshuffling
        int temp[2][deckSize];
        for(int i = 0; i < deckSize; i++)
        {
            temp[0][i] = shuffledDeck[0][i]; // Copy colors 
            temp[1][i] = shuffledDeck[1][i]; // Copy types 
        }

        // Perform the reshuffling process
        int random1, random2;
        do
        {
            random1 = rand() % deckSize; // Random index in the deck
            random2 = rand() % deckSize; // Another random index in the deck
            shuffledDeck[0][random1] = temp[0][random2]; // Shuffle color
            shuffledDeck[1][random1] = temp[1][random2]; // Shuffle type
        }while(temp[1][random2] == -1); // Ensure no duplication of reshuffled cards

        // Mark the reshuffled card as used
        temp[1][random2] = -1;

        cout << "Discard pile reshuffled back into the deck!\n\n";
    }
}
bool callUno(bool uno, int player, int playerHands[][max_hand], int handSizes[], int shuffledDeck[][108])
{
    if(handSizes[player] == 2)
    { 
        // Player has 2 cards left
        if(uno==true)
        {
            cout << "You correctly called UNO!\n";
        	currentPlayer = (currentPlayer + 1) % players;
            return true; // Successful UNO call
        }
		else
		{
            // Penalty for not calling UNO
            cout << "You didn't call UNO! Drawing two cards as penalty...\n";
            for(int i = 0; i < 2; i++)
            {
                playerHands[player][handSizes[player]++] = drawCard(shuffledDeck);
            }
            return false; // Player failed to call UNO
        }
    }
    else if(uno==true)
    {
        // Invalid UNO call (more than 2 cards)
        cout << "Incorrect UNO call! Drawing two cards as penalty...\n";
        for(int i = 0; i < 2; i++)
		{
            playerHands[player][handSizes[player]++] = drawCard(shuffledDeck);
        }
    	currentPlayer = (currentPlayer + 1) % players;
        return false;
    }

    return true; // Default case: No UNO-related actions
}

void saveLoadGameResult(bool load, int &Wins_p1, int &Wins_p2, int winner, int moves_p1, int moves_p2)
{
    fstream file;

    if(load==true)
    {
        // Load game results and display them
        file.open("game_log.txt", fstream::in);
        if(file.is_open())
        {
            char line[200];
            cout << "\nGame History:\n";
            while(file.getline(line, 200))
            {
                cout << line << endl;
            }
            file.close();
        }
        else
        {
            cout << "No previous game history found.\n";
        }
        cout<<"\nPress Any Key To Go Back...";
        getch();
    }
    else
    {
        // Save the game result
        file.open("game_log.txt", fstream::out | fstream::app);
        if(file.is_open())
        {
            int totalGames=Wins_p1+Wins_p2;
            file <<"Total Games: "<< totalGames<<"\n"; 
            file <<"Player 1 Wins: "<<Wins_p1<<endl;
            file <<"Player 2 Wins: "<<Wins_p2<<endl;
            file << "Game "<<totalGames<<" Results:\n"; 
            file << "  Winner: Player " << winner << "\n";
            file << "  Player 1 Moves: " << moves_p1 << "\n";
            file << "  Player 2 Moves: " << moves_p2 << "\n";
            file << "  Total Turns: " << moves_p1+moves_p2 << "\n";
            file << "---------------------\n";
            file.close();
        }
    }
}