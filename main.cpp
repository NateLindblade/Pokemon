/* Name: Nathan Lindblade
Date: April 21, 2023
Assignment: Final Homework Assignment 
Due Date: April 28, 2023
About this project: Simulates a Pokemon-GO-like game
Assumptions: User will only hunt in a region that exists in the file

All work below was performed by Nathan Lindblade */

//Libraries
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

//Structure Declaration
struct Pokemon
{
     int pokeNumber;
     string pokeName;
     string pokeType;
     string region;
     int catchPercent;
     string dexEntry;
     int numCaught;
     int numSeen;
};

//Functions
void statistics (const Pokemon&);
void inventory (int pokeBalls, int greatBalls, int ultraBalls);
void menu();

int main()
{
     //Declarations and some Initializations
     int SIZE, chooseBall, randPoke, counter, counter2, pokeBalls = 10, greatBalls = 10, ultraBalls = 10;
     int together, counter3, placement, randomChance = rand() % 100 + 1;
     
     string name, where, menuSelect, menuSelect2, menuSelect3;
     Pokemon X;
     
     X.numCaught = 0;
     X.numSeen = 0;
     
     //Seed Time
     srand(time(0));
     
     //Pointer and File Declaration
     Pokemon * dex;
     ifstream IN;
     
     //Opening File
     IN.open("poke.txt");
     
     //If file fails to open...
     if(!IN)
     {
         cout << "POKE.TXT FILE FAILED TO OPEN, ENDING PROGRAM.";
         exit(0);
     }
     
     //Read in first integer of the file
     IN >> SIZE;
     
     //Creating another array after SIZE is read in
     int line[SIZE] = {};
     
     //Dynamic Array Creation
     dex = new Pokemon[SIZE + 1];
     
     //Loop to fill in the dynamic array
     for(int i = 1; i <= SIZE; i++)
    {    
         IN >> X.pokeNumber;
         IN.ignore();
         getline(IN, X.pokeName, ',' );
         getline(IN, X.pokeType, ',');
         getline(IN, X.region, ',');
         
         IN >> X.catchPercent;
         IN.ignore();
         getline(IN, X.dexEntry, '\n');
         
         dex[i] = {X.pokeNumber, X.pokeName, X.pokeType, X.region, X.catchPercent, X.dexEntry};
     }
     
     //Closes the file
     IN.close();
     
     //Start of program
     cout << "What's your name, trainer? > ";
     getline (cin, name);
     
     //Welcomes the user 
     cout << "\nWelcome, " << name << " to the Programming I Safari Zone!\n";
     cout << "You'll have 30 chances to catch Pokemon, make them count!\n";
     cout << "The hunt will end when you choose or when you run out of Pokeballs!\n";
     
     //Asks the user for a zone to visit
     cout << "\nWhich region would you like to visit?\n";
     cout << "Enter Kanto, Johto, Hoenn, or Sinnoh.\n> ";
     getline(cin, where);
     
     //Changes user entry to all capital letters
     for (int i = 0; i < where.size(); i++)
        where[i] = toupper(where[i]);
     
     //If user doesn't type the region correctly, program asks again
     while (where != "KANTO" && where != "JOHTO" && where != "HOENN" && where != "SINNOH")
     {
         cout << "Enter Kanto, Johto, Hoenn, or Sinnoh.\n> ";
         cin >> where;
         for (int i = 0; i < where.size(); i++)
            where[i] = toupper(where[i]);
     }
     
     //Goes to the region the user typed in and then prints menu.
     cout << "\nTravelling to " << where << "\n\n";
     menu();
     
     //Allows user to enter in a menu selection
     do
    {
         //Gets user input
         cout << "Selection > ";   
         getline(cin, menuSelect);
         
         //Changes user input to all capital letters
         for (int i = 0; i < menuSelect.size(); i++)
             menuSelect[i] = toupper(menuSelect[i]); 
              
         //If the user runs out of Poke Balls
         if (menuSelect == "HUNT" && pokeBalls == 0 && greatBalls == 0 && ultraBalls == 0)
         {
             cout << "You are out of Poke Balls and therefore cannot hunt. "; 
             cout << "Please select another menu option\n";
         }
         //Hunt Option
         else if (menuSelect == "HUNT")
        {
             //Random number generation
             if (where == "KANTO")
                 randPoke = rand() % 151 + 1;
             else if (where == "JOHTO")
                 randPoke = rand() % 100 + 152;
             else if (where == "HOENN")
                 randPoke = rand() % 135 + 252;
             else if (where == "SINNOH")
                 randPoke = rand() % 107 + 387;
                 
             cout << "\nA wild " << dex[randPoke].pokeName << " has appeared!\n\n";
             
             //If a Baby Pokemon is not found
            if(dex[randPoke].catchPercent != 0)
            {
             cout << "Choose a ball to throw:\n1 - Poke Ball\t(You have: " << pokeBalls;
             cout << ")\n2 - Great Ball\t(You have: " << greatBalls << ")\n3 - Ultra ";
             cout << "Ball\t(You have: " << ultraBalls << ")\nChoose a ball > ";
             cin >> chooseBall;
             
                 //If the user does not enter in a 1, 2, or 3
                 while (chooseBall != 1 && chooseBall != 2 && chooseBall != 3)
                 {
                     cout << "Invalid selection. Try Again\n";
                     cout << "Choose a ball > ";
                     cin >> chooseBall;
                 }
                 do
                 {
                     //If the user chooses the Poke Balls
                    if (chooseBall == 1)
                    {
                        if(pokeBalls == 0)
                        {
                            cout << "No more Poke Balls left, please select another.\n";
                            cout << "Choose a ball > ";
                            cin >> chooseBall;
                            counter = 0;
                        }
                        else if (pokeBalls > 0)
                        {
                            cout << "Threw a Poke Ball!\n";
                            pokeBalls--;
                            together = dex[randPoke].catchPercent;
                            counter = 1;
                        }
                    }
                    //If the user chooses the Great Balls
                    else if (chooseBall == 2)
                    {
                        if (greatBalls == 0)
                        {
                            cout << "No more Great Balls left, please select another.\n";
                            cout << "Choose a ball > ";
                            cin >> chooseBall;
                            counter = 0;
                        }
                        else if (greatBalls > 0)
                        {
                            cout << "Threw a Great Ball!\n";
                            greatBalls--;
                            together = dex[randPoke].catchPercent;
                            together = together + 20;
                            counter = 1;
                        }
                    }
                    //If the user chooses the Ultra Balls
                    else if (chooseBall == 3)
                    {
                        if (ultraBalls == 0)
                        {
                            cout << "No more Ultra Balls left, please select another.\n";
                            cout << "Choose a ball > ";
                            cin >> chooseBall;
                            counter = 0;
                        }
                        else if (ultraBalls > 0)
                        {
                            
                            cout << "Threw an Ultra Ball!\n";
                            ultraBalls--;
                            together = dex[randPoke].catchPercent;
                            together = together + 40;
                            counter = 1;
                        }
                    }
                 }while(counter != 1); 
                 
                 if (counter == 1)
                 {
                     
                     if (randomChance <= together)
                        { 
                             //Congratulates user and puts their Pokemon into a separate array
                            cout << "Congratulations! You caught " << dex[randPoke].pokeName << endl << endl;
                            X.numCaught++;
                            X.numSeen++;
                            
                            for (int i = 0; i <= SIZE; i++)
                            {
                                if(line[i] > 0 && counter2 == 1)
                                {
                                    line[i + counter2] == dex[randPoke].pokeNumber;
                                    break;
                                }
                            }
                            for (int i = 0; i < SIZE; i++)
                            {    
                                if(line[i] == 0)
                                {
                                    line[i] = dex[randPoke].pokeNumber;
                                    counter2++;
                                    break;
                                }
                            }
                        }
                     //If the user failed to catch the Pokemon    
                     else if (randomChance > together)
                        { 
                             cout << dex[randPoke].pokeName << " ran away! :-(\n\n";
                             X.numSeen++;
                        }
                }
            }     
            //If the user finds a Baby Pokemon
            else if (dex[randPoke].catchPercent == 0)
            {
                cout << "Oh! That's a baby pokemon! We'll take them to the daycare!\n\n";
                X.numCaught++;
                X.numSeen++;
                for (int i = 0; i <= SIZE; i++)
                {
                    if(line[i] > 0 && counter2 == 1)
                    {
                        line[i + counter2] == dex[randPoke].pokeNumber;
                        break;
                    }
                }
                for (int i = 0; i < SIZE; i++)
                {    
                    if(line[i] == 0)
                    {
                        line[i] = dex[randPoke].pokeNumber;
                        counter2++;
                        break;
                    }
                }
            }
        }
         //Menu selection for seeing how many Pokemon the user caught
         else if (menuSelect == "POKEMON")
             {
                 if (line[0] == 0)
                    cout << "\nNo Pokemon Caught Yet.\n";
                 else if (line[0] > 1)
                 {
                     cout << endl << name << "'s POKEMON:\n";
                     for (int i = 0; i < SIZE; i++)
                     {
                         placement = line[i];
                         if (dex[placement].pokeNumber >= 1)
                         {
                             cout << "no. " << dex[placement].pokeNumber << "\t";
                             cout << dex[placement].pokeName << endl;
                         }
                     }
                 }
                 cout << "\n";
             }
         //Menu option for seeing the player's stats
         else if (menuSelect == "STATISTICS")
             statistics(X);
         //Menu option for seeing how many Pokeballs the player has left
         else if (menuSelect == "INVENTORY")
             inventory(pokeBalls, greatBalls, ultraBalls);
         //Menu option to see the entire menu again
         else if (menuSelect == "MENU")
             menu();
         //Menu option for seeing the Dex of a Pokemon
         else if (menuSelect.substr(0 , 3) == "DEX")
         {
             menuSelect2 = menuSelect.substr(0 , 3);
             menuSelect3 = menuSelect.substr(4);
              
            for (int i = 0; i < menuSelect3.size(); i++)
                menuSelect3[i] = tolower(menuSelect3[i]);
             
            menuSelect3[0] = toupper(menuSelect3[0]);
             
            if(menuSelect2 == "DEX")
            {
                 //Searches for Pokemon in the dex array
                for (int i = 1; i <= SIZE; i++)
                {
                    if (menuSelect3 == dex[i].pokeName)
                    {
                        cout << "\nNAME: " << dex[i].pokeName << endl;
                        cout << "TYPE: " << dex[i].pokeType << endl;
                        cout << dex[i].dexEntry << endl << endl;
                        counter3 = 1;
                        break;
                    }
                }
                 //If the user has not gotten any Pokemon yet
                for (int i = 1; i <= SIZE; i++)
                {
                    if (menuSelect3 != dex[i].pokeName && counter3 == 0)
                    {
                        cout << "No Pokemon Named " << menuSelect3 << endl << endl;
                        break;
                    }
                }
            }
           
            counter = 0;
         }   
     }while (menuSelect != "EXIT");
     
         //Prints the user's pokemon again before the program shuts off
         if (line[0] == 0)
            cout << "\nNo Pokemon Caught Yet.";
         else if (line[0] > 1)
         {
             cout << endl << name << "'s POKEMON:\n";
             for (int i = 0; i < SIZE; i++)
             {
                 placement = line[i];
                 if (dex[placement].pokeNumber >= 1)
                 {
                     cout << "no. " << dex[placement].pokeNumber << "\t";
                     cout << dex[placement].pokeName << endl;
                 }
              }
         }
        cout << "\n";
        
     delete [] dex;
     dex = 0;
     
     return 0;
}
//Function for the stat menu option
void statistics (const Pokemon& stat)
{
     cout << "Total Pokemon Caught: " << stat.numCaught << endl;
     cout << "Total Pokemon Seen: " << stat.numSeen << endl;
     cout << fixed << showpoint << setprecision(2);
     if (stat.numCaught == 0 && stat.numSeen == 0)
         cout << "Overall Catch Rate: 0.00%\n\n";
     else   
         cout << "Overall Catch Rate: " << ((stat.numCaught * 1.0) / stat.numSeen) * 100.00 << "%\n\n";
     return;
}
//Function for the inventory menu option
void inventory (int pokeBalls, int greatBalls, int ultraBalls)
{
     cout << "\nYou Have:\n" << pokeBalls << " PokeBalls\n" << greatBalls;
     cout << " Great Balls\n" << ultraBalls << " Ultra Balls\n\n";
     return;
}
//Function for the menu option
void menu()
{
     cout << "HUNT\t\t(Go Hunting For Pokemon!)\nPOKEMON\t\t(See The Pokemon You've Caught)\n";
     cout << "STATISTICS\t(See Your Catch Statistics!)\nINVENTORY\t(See Your Current Inventory)\n";
     cout << "DEX NAME\t(Ex. DEX BULBASAUR Would View Bulbasaur's Pokedex Entry!)\n";
     cout << "MENU\t\t(Reprint This Menu!)\nEXIT\n";
     return;
}