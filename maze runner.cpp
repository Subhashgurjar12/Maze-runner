// Prog6maze.cpp
//     Play a simple maze game.
//
// Program: #6, Navigating a maze using classes
//

#include <iostream>  // Needed to avoid compiler error for the exit() command
#include <cctype>    // For toupper()
#include <fstream>  // For reading input file
#include <iomanip>
using namespace std;

//class player for the live location of player
class player
{
  int plr,plc;
public:
  void updatePlayer(int r,int c);//function for updating the live location of player
}p;

void player :: updatePlayer(int r,int c)
{
  p.plr=r;
  p.plc=c;
}

//-----------------------------------------------------------------------------------------------


//inventory class or bag
class inventory
{
public:
  int health,herbs,gold;
  void initialInventory();
  void updateInventory(char s);
  void printInventory();
}i;

//intializing the bag of the player
void inventory ::initialInventory()
{
  i.health=3;
  i.herbs=0;
  i.gold=0;
}


//printing the memebrs of inventory with their quantity
void inventory :: printInventory()
{
cout<<"Player health: "<<i.health<<endl;
cout<<"Player has "<<i.herbs<<" healing items."<<endl;
cout<<"Player has "<<i.gold<<" gold coins."<<endl;
}

//void inventory :: updateInventory(char s)
//{
//  if(s=='H')
//  {
//    i.herbs++;
//  }
//  else if(s=='C')
//  {
//    i.gold++;
//  }
//}

//-----------------------------------------------------------------------------------------------
//board class containing all imp information of game and gameplay
class board
{
  int p,q;
public:
  char b[1000][1000];
  int result,pr,pc;

  void startBoard(int r,int c,int  pr,int pc);
  void updateBoard(char s,int r1,int c1);
  void intialBoard();
  void displayBoard(int r,int c);
  void playgame(char s,int pr,int pc);
}o;


//initializing board with '.' value without reading the text
void board :: intialBoard()
{
  int i,j;
  for(i=0;i<1000;i++)
  {
    for(j=0;j<1000;j++)
    {
      o.b[i][j]='.';
    }
  }
}


//function for displaying the board on the console
void board :: displayBoard(int r,int c)
{
  int i,j;

  cout<<endl;
  for(i=0;i<r;i++)
  {
    for(j=0;j<c;j++)
    {
      cout<<" "<<o.b[i][j];
    }
    cout<<endl;
  }
}


//making the boundary of the box
void board :: startBoard(int r,int c,int pr,int pc)
{
  int i,j;
      for(i=0;i<r;i++)
      {
        o.b[i][0]='*';
        o.b[i][c-1]='*';
      }
      for(j=0;j<c;j++)
      {
        o.b[0][j]='*';
        o.b[r-1][j]='*';
      }
      o.b[pr][pc]='P';
}


//updating the board
void board :: updateBoard(char s,int r1,int c1)
{
  o.b[r1][c1]=s;
}


//gameplay function
void board :: playgame(char s,int pr,int pc)
{
  int i1,j1;
  //player wants to move forward
  if(s=='W')
  {
    i1=-1,j1=0;
  }

  //player wants to move down
  if(s=='S')
  {
    i1=1;j1=0;
  }

  //player wants to move toward left
  if(s=='A')
  {
    i1=0;j1=-1;
  }
  
  //player wants to move toward right
  if(s=='D')
  {
    i1=0;j1=1;
  }

  //when player encounters the blocked condition
  if(o.b[pr+i1][pc+j1]=='*')
  {
      cout<<"The location is blocked. You can't move there!\nTry again!\n";
      return ;
  }

  //when player encounters a trap
  if(o.b[pr+i1][pc+j1]=='T')
  {
    cout<<"You stepped on a trap!\n";
      i.health--;
      o.b[pr][pc]='.';
      o.b[pr+i1][pc+j1]='P';
      o.pr=pr+i1;
      o.pc=pc+j1;
      return ;
  }
    //if user finds the door
  if(o.b[pr+i1][pc+j1]=='D')
  {
      o.result=1;
      o.b[pr][pc]='.';
      o.b[pr+i1][pc+j1]='P';
      o.pr=pr+i1;
      o.pc=pc+j1;
      return ;
  }
    //normal step
  if(o.b[pr+i1][pc+j1]=='.')
  {
      o.b[pr][pc]='.';
      o.b[pr+i1][pc+j1]='P';
            o.pr=pr+i1;
      o.pc=pc+j1;
      return ;
  }
  
  //when player founds a healing item
  if(o.b[pr+i1][pc+j1]=='H')
  {
      cout<<"You found a healing item!\n";
      i.herbs++;
      o.b[pr][pc]='.';
      o.b[pr+i1][pc+j1]='P';
            o.pr=pr+i1;
      o.pc=pc+j1;
      return ;
  }
  
  //when player finds chest or gold
  if(o.b[pr+i1][pc+j1]=='C')
  {
    cout<<"You found a chest!\n";
      i.gold++;
      o.b[pr][pc]='.';
      o.b[pr+i1][pc+j1]='P';
            o.pr=pr+i1;
      o.pc=pc+j1;
      return ;
  }
}
//-----------------------------------------------------------------------------------------------
void displayInstructions()
{
    cout << ""
         << "Let's Play!\n"
         << "Move the player icon up, down, right, or left\n"
         << "with w, s, d ,a keys\n"
         << "press i to display player inventory\n"
         << "At any point press x to exit the game.\n\n";
} // end displayInstructions()


//-------------------------------------------------------------------------------------
int main() {



    ifstream file;
    file.open("maze.txt");

    int r,c,pr,pc;

    file>>r; //total rows;
    file>>c; //total columns
    file>>pr; //initial player's row;
    file>>pc; //initial player's column

    o.intialBoard();
    o.startBoard(r,c,pr,pc);
    p.updatePlayer(pr,pc);
    i.initialInventory();

    //reading the instruction for gameplay
    while(file)
    {
      char s;
      int r1,c1;
      //reading the character and it's location
      file>>s>>r1>>c1;
      s=toupper(s);
      if(s=='W') s='*';
      o.updateBoard(s,r1,c1);
//      i.updateInventory(s);
    }

   // Read "maze.txt" file and create the proper board
    cout << "Reading the maze file...\n"<<endl;

    int n=1000,i1,j1;
     for(i1=0;i1<r;i1++)
  {
    for(j1=0;j1<c;j1++)
    {
      cout<<" "<<o.b[i1][j1];
    }
    cout<<endl;
  }

    displayInstructions();//displaying instruction on the console screen

    while(n--)
    {

    // display the board

     // Display game instructinos

    char in;
   // cout<<"(user input)";
    cin>>in;
    in=toupper(in);
    
    //if user wants to check the stock of bag or inventory
    if(in=='I')
    {
      i.printInventory();
      o.displayBoard(r,c);

    }

    //if user wants to exit out of the game
    else if(in=='X'
    {
        cout<<"Exiting...\n";
      return 0;
    }

    //user's instructs to move up,down,left or right
    else if(in=='W'||in=='S'||in=='A'||in=='D')
    {
      o.playgame(in,pr,pc);
          pr=o.pr;
    pc=o.pc;
    //if user finds the door
      if(o.result==1)
      {
        o.displayBoard(r,c);
        cout<<"You have reached the door!\n";
        cout<<"Thank you for playing, here is a summary of your game: \n";
        i.printInventory();
        return 0;
      }
    //if health reduces to zero
      if(i.health==0)
      {
          //if there are herbs to refill the health
        if(i.herbs!=0)
        {
          i.health++;//refilling health
          i.herbs--;//decrementing the herb value by 1
        }
        //if there are no herbs to refill the health
        else
        {
            cout<<"You died!";//player dies in the game
          return 0;
        }
      }
      o.displayBoard(r,c);
    }
    }
    return 0;
} // end main()
