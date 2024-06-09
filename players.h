#include <iostream>
#include <ctime>
#include <pthread.h>
#include <cstdlib>
#include <algorithm>
#include <sys/wait.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;


const string RED = "\033[1;31m";
const string GREEN = "\033[1;32m";
const string YELLOW = "\033[1;33m";
const string BLUE = "\033[1;34m";
const string RESET = "\033[0m"; // Reset color

const int BOARD_SIZE = 52;
char design[BOARD_SIZE];
bool alive[4][4], home[4][4];
int token[4][4];
sem_t hello;
int finish = 0;


int final[4][4];
char pl1[6] = {'0', '0', '0', '0', '0', '0'};
char pl2[6] = {'0', '0', '0', '0', '0', '0'};
char pl3[6] = {'0', '0', '0', '0', '0', '0'};
char pl4[6] = {'0', '0', '0', '0', '0', '0'};
int counter[4][4];

void clear_screen();
void initializeBoard();
int getpos(int position);


class players{
private:
    int pov = 0;


public:

    players(){}

    void PositionGoti(int player,int roll)
    {
        token[player-1][roll] = 3;
    }

    // Function to move a token
  void moveToken(int player, int goti, int diceRoll)
   {

        design[token[player][goti]] = '*';
        token[player][goti] += diceRoll;
        //counter[player][goti] += diceRoll;

        int p = token[player][goti];


        //////////////////////////////////player 1///////////////////////////
        if( player == 0 )
        {
            if (counter[player][goti] > 50)
            {

                if (counter[player][goti] > 56) {
                    counter[player][goti] -= diceRoll;
                    initializeBoard();
                } else if (counter[player][goti] == 56) {
                    cout << "Player 1's Goti: " << goti + 1 << " Has won" << endl;
                    pl1[final[player][goti]] = '0';
                    finish++;

                } else {
                    pl1[final[player][goti]] = '0';
                    final[player][goti] = counter[player][goti] - 51;
                    pl1[final[player][goti]] = '1';
                   // sleep(2);
                      clear_screen();
                    initializeBoard();
                }

            }

            if(token[player][goti] == 0 || token[player][goti] == 8 || token[player][goti] == 13 || token[player][goti] == 26 || token[player][goti] == 16 || token[player][goti] == 34 || token[player][goti] == 39 || token[player][goti] == 47)
            {
                design[token[player][goti]] = '1';
                //clear_screen();
              //  sleep(2);
                      clear_screen();
                initializeBoard();
            }

            else{


                    if(design[token[0][goti]] == '2')
                    {
                        int pos = token[player][goti];
                        int p = getpos(pos);
                        if(p){
                            alive[1][p] =false;
                        }
                       // continue;



                        design[token[player][goti]] = '1';
                       // clear_screen();
                    //   sleep(2);
                      clear_screen();
                        initializeBoard();
                        cout<<"Player 1 KILLED Player 2 "<<endl;

                    }
                    else if(design[token[0][goti]] == '3'){
                        int pos = token[player][goti];
                        int p = getpos(pos);
                        if(p){
                            alive[2][p] =false;
                        }
                       // continue;



                        design[token[player][goti]] = '1';
                     //   clear_screen();
                    // sleep(2);
                      clear_screen();
                        initializeBoard();
                        cout<<"Player 1 KILLED Player 3 "<<endl;

                    }
                    else if(design[token[0][goti]] == '4'){
                        int pos = token[player][goti];
                        int p = getpos(pos);
                         if(p){
                            alive[3][p] =false;
                        }
                       // alive[3][p] =false;


                        design[token[player][goti]] = '1';
                      //  clear_screen();
                    //  sleep(2);
                      clear_screen();
                        initializeBoard();
                        cout<<"Player 1 KILLED Player 4 "<<endl;
                    }

                    else
                    {

                           design[token[player][goti]] = '1';
             //   clear_screen();
           //  sleep(2);
                      clear_screen();
                            initializeBoard();
                    }

                 }

        }

            /////////////////////////////////player 2///////////////////////////



        else if(player == 1)
        {

            cout<<"Counter: "<<counter[player][goti]<<endl;
            if (counter[player][goti] > 50) {
                home[player][goti] = true;
                if (counter[player][goti] > 56) {
                    counter[player][goti] -= diceRoll;
                    initializeBoard();
                } else if (counter[player][goti] == 56) {
                    cout << "Player 2's Goti: " << goti + 1 << " Has won" << endl;
                    finish++;
                    pl2[final[player][goti]] = '0';

                } else {
                    pl2[final[player][goti]] = '0';
                    final[player][goti] = counter[player][goti] - 51;
                    pl2[final[player][goti]] = '2';
                //    sleep(2);
                      clear_screen();
                    initializeBoard();
                }
            }


            else
            {



                if(token[player][goti]>=51)
                {
                    if(token[player][goti] == 0 || token[player][goti] == 8 || token[player][goti] == 13 || token[player][goti] == 26 || token[player][goti] == 16 || token[player][goti] == 34 || token[player][goti] == 39 || token[player][goti] == 47)
                    {
                        cout<<token[player][goti]<<endl;
                        int temp = token[player][goti];
                        token[player][goti] =  temp - 51;
                        cout<<token[player][goti]<<endl;
                        design[token[player][goti]] = '2';
                  //      sleep(2);
                      clear_screen();
                        initializeBoard();
                    }

                    else
                    {


                        if(design[token[1][goti]] == '1'){
                            int pos = token[player][goti];
                            int p = getpos(pos);
                             if(p){
                            alive[0][p] =false;
                        }
                           // alive[0][p] =false;
                            // token[1][goti] = 0;

                            cout<<token[player][goti]<<endl;
                            int temp = token[player][goti];
                            token[player][goti] =  temp - 51;
                            cout<<token[player][goti]<<endl;
                            design[token[player][goti]] = '2';
                    //        sleep(2);
                      clear_screen();
                            initializeBoard();
                            cout<<"Player 2 KILLED Player 1"<<endl;

                        }
                        else if(design[token[1][goti]] == '3'){
                                int pos = token[player][goti];
                                int p = getpos(pos);
                                 if(p){
                            alive[2][p] =false;
                        }
                                //alive[2][p] =false;
                            // token[1][goti] = 25;

                            cout<<token[player][goti]<<endl;
                            int temp = token[player][goti];
                            token[player][goti] =  temp - 51;
                            cout<<token[player][goti]<<endl;
                            design[token[player][goti]] = '2';
                    //        sleep(2);
                      clear_screen();
                            initializeBoard();
                            cout<<"Player 2 KILLED Player 3 "<<endl;
                        }

                        else if(design[token[1][goti]] == '4'){
                                int pos = token[player][goti];
                                int p = getpos(pos);
                                 if(p){
                            alive[3][p] =false;
                        }
                               // alive[3][p] =false;
                          //  alive[3][goti] =false;
                            //  token[1][goti] = 38;

                            cout<<token[player][goti]<<endl;
                            int temp = token[player][goti];
                            token[player][goti] =  temp - 51;
                            cout<<token[player][goti]<<endl;
                            design[token[player][goti]] = '2';
                    //        sleep(2);
                      clear_screen();
                            initializeBoard();
                            cout<<"Player 2 KILLED Player 4 "<<endl;

                        }

                        else
                        {
                            cout<<token[player][goti]<<endl;
                            int temp = token[player][goti];
                            token[player][goti] =  temp - 51;
                            cout<<token[player][goti]<<endl;
                            design[token[player][goti]] = '2';
                            //    clear_screen();
                     //       sleep(2);
                      clear_screen();
                            initializeBoard();
                        }


                    }

                }

                else
                {

                    if(token[player][goti] == 0 || token[player][goti] == 8 || token[player][goti] == 13 || token[player][goti] == 26 || token[player][goti] == 16 || token[player][goti] == 34 || token[player][goti] == 39 || token[player][goti] == 47)
                    {
                        cout<<token[player][goti]<<endl;
                        design[token[player][goti]] = '2';
                        //  clear_screen();
                  //      sleep(2);
                      clear_screen();
                        initializeBoard();
                    }

                    else{

                        if(design[token[1][goti]] == '1'){
                            int pos = token[player][goti];
                        int p = getpos(pos);
                         if(p){
                            alive[0][p] =false;
                        }
                       // alive[0][p] =false;
                           // alive[0][goti] =false;
                            // token[1][goti] = 0;

                            cout<<token[player][goti]<<endl;
                            design[token[player][goti]] = '2';
                   //         sleep(2);
                      clear_screen();
                            initializeBoard();
                            cout<<"Player 2 KILLED Player 1 "<<endl;

                        }
                        else if(design[token[1][goti]] == '3'){
                        int pos = token[player][goti];
                        int p = getpos(pos);
                         if(p){
                            alive[2][p] =false;
                        }
                      //  alive[2][p] =false;
                          // alive[2][goti] =false;
                            // token[1][goti] = 25;

                            cout<<token[player][goti]<<endl;
                            design[token[player][goti]] = '2';
                     //       sleep(2);
                      clear_screen();
                            initializeBoard();
                            cout<<"Player 2 KILLED Player 3"<<endl;

                        }
                        else if(design[token[1][goti]] == '4'){
                        int pos = token[player][goti];
                        int p = getpos(pos);
                        if(p){
                            alive[3][p] =false;
                        }
                       // alive[3][p] =false;

                           // alive[3][goti] =false;
                            // token[1][goti] = 38;
                            cout<<token[player][goti]<<endl;
                            design[token[player][goti]] = '2';
                    //        sleep(2);
                      clear_screen();
                            initializeBoard();
                             cout<<"Player 2 KILLED Player 4"<<endl;
                        }
                        else{
                            cout<<token[player][goti]<<endl;
                            design[token[player][goti]] = '2';
                            //  clear_screen();
                     //       sleep(2);
                      clear_screen();
                            initializeBoard();
                        }

                    }

                }
            }
        }


          ///////////////////////////////////player 3///////////////////////////


          else if( player == 2)
          {
              if (counter[player][goti] > 50) {
                    home[player][goti] = true;
                if (counter[player][goti] > 56) {
                    counter[player][goti] -= diceRoll;
               //     sleep(2);
                      clear_screen();
                    initializeBoard();
                } else if (counter[player][goti] == 56) {
                    cout << "Player 3's Goti: " << goti + 1 << " Has won" << endl;
                    finish++;
                    pl3[final[player][goti]] = '0';

                } else {
                    pl3[final[player][goti]] = '0';
                    final[player][goti] = counter[player][goti] - 51;
                    pl3[final[player][goti]] = '3';
               //     sleep(2);
                      clear_screen();
                    initializeBoard();
                }
            }
              else if(token[player][goti]>=51)
              {

                 if(token[player][goti] == 0 || token[player][goti] == 8 || token[player][goti] == 13 || token[player][goti] == 26 || token[player][goti] == 16 || token[player][goti] == 34 || token[player][goti] == 39 || token[player][goti] == 47)
                 {
                    cout<<token[player][goti]<<endl;
                  int temp = token[player][goti];
                  token[player][goti] =  temp - 51;
                  cout<<token[player][goti]<<endl;
                  design[token[player][goti]] = '3';
                //  clear_screen();
              //  sleep(2);
                      clear_screen();
                  initializeBoard();
                 }

                 else{


                    if(design[token[2][goti]] == '1'){
                        int pos = token[player][goti];
                        int p = getpos(pos);
                        if(p){
                            alive[0][p] =false;
                        }
                        //continue;


                   // alive[0][goti] =false;
                   // token[1][goti] = 0;
                    cout<<token[player][goti]<<endl;
                  int temp = token[player][goti];
                  token[player][goti] =  temp - 51;
                  cout<<token[player][goti]<<endl;
                  design[token[player][goti]] = '3';
              //    sleep(2);
                      clear_screen();
                   initializeBoard();
                   cout<<"Player 3 KILLED Player 1 "<<endl;
                    }
                    else if(design[token[2][goti]] == '3'){

                    int pos = token[player][goti];
                        int p = getpos(pos);
                         if(p){
                            alive[1][p] =false;
                        }
                      //  alive[1][p] =false;
                   // alive[1][goti] =false;
                    //token[1][goti] = 25;
                    cout<<token[player][goti]<<endl;
                  int temp = token[player][goti];
                  token[player][goti] =  temp - 51;
                  cout<<token[player][goti]<<endl;
                  design[token[player][goti]] = '3';
               //   sleep(2);
                      clear_screen();
                   initializeBoard();
                   cout<<"Player 3 KILLED Player 3 "<<endl;
                    }
                    else if(design[token[2][goti]] == '4'){
                        int pos = token[player][goti];
                        int p = getpos(pos);
                         if(p){
                            alive[3][p] =false;
                        }
                       // alive[3][p] =false;
                  //  alive[3][goti] =false;
                   // token[1][goti] = 38;

                    cout<<token[player][goti]<<endl;
                  int temp = token[player][goti];
                  token[player][goti] =  temp - 51;
                  cout<<token[player][goti]<<endl;
                  design[token[player][goti]] = '3';
                //  sleep(2);
                      clear_screen();
                   initializeBoard();
                   cout<<"Player 3 KILLED Player 4 "<<endl;

                    }

                    else
                    {
                cout<<token[player][goti]<<endl;
                  int temp = token[player][goti];
                  token[player][goti] =  temp - 51;
                  cout<<token[player][goti]<<endl;
                  design[token[player][goti]] = '3';
                //  clear_screen();
               // sleep(2);
                      clear_screen();
                  initializeBoard();

                    }
                 }
              }

           else
           {
              if(token[player][goti] == 0 || token[player][goti] == 8 || token[player][goti] == 13 || token[player][goti] == 26 || token[player][goti] == 16 || token[player][goti] == 34 || token[player][goti] == 39 || token[player][goti] == 47)
                 {
                     cout<<token[player][goti]<<endl;
                     design[token[player][goti]] = '3';
                     //  clear_screen();
                //     sleep(2);
                      clear_screen();
                     initializeBoard();
                 }

                 else{



                    if(design[token[2][goti]] == '1'){
                        int pos = token[player][goti];
                        int p = getpos(pos);
                         if(p){
                            alive[0][p] =false;
                        }
                        //alive[0][p] =false;
                   // alive[0][goti] =false;
                   // token[1][goti] = 0;

                    design[token[player][goti]] = '3';
               //     sleep(2);
                      clear_screen();
                     initializeBoard();
                     cout<<"Player 3 KILLED Player 1 " <<endl;
                    }
                    else if(design[token[2][goti]] == '3'){
                        int pos = token[player][goti];
                        int p = getpos(pos);
                       if(p){
                            alive[1][p] =false;
                        }
                      //  alive[1][p] =false;
                  //  alive[1][goti] =false;
                    //token[1][goti] = 25;

                    design[token[player][goti]] = '3';
                  //  sleep(2);
                      clear_screen();
                     initializeBoard();
                     cout<<"Player 3 KILLED Player 3 "<<endl;
                    }
                    else if(design[token[2][goti]] == '4'){
                        int pos = token[player][goti];
                        int p = getpos(pos);
                         if(p){
                            alive[3][p] =false;
                        }
                      //  alive[3][p] =false;
                  //  alive[3][goti] =false;
                   // token[1][goti] = 38;

                    design[token[player][goti]] = '3';
                     initializeBoard();
                     cout<<"Player 3 KILLED Player 4 "<<endl;
                    }
                    else{
                cout<<token[player][goti]<<endl;
                design[token[player][goti]] = '3';
             //  clear_screen();
           //  sleep(2);
                      clear_screen();
               initializeBoard();
                    }
           }

          }
          }

/////////////////////////////////player 4///////////////////////////
          else if(player == 3)
          {
             if (counter[player][goti] > 50) {
                    home[player][goti] = true;
                if (counter[player][goti] > 56) {
                    counter[player][goti] -= diceRoll;
                    initializeBoard();
                } else if (counter[player][goti] == 56) {
                    cout << "Player 4's Goti: " << goti + 1 << " Has won" << endl;
                    finish++;
                    pl4[final[player][goti]] = '0';

                } else {
                    pl4[final[player][goti]] = '0';
                    final[player][goti] = counter[player][goti] - 51;
                    pl4[final[player][goti]] = '4';
                //    sleep(2);
                      clear_screen();
                    initializeBoard();
                }
            }

              else if(token[player][goti]>=51)
              {

                if(token[player][goti] == 0 || token[player][goti] == 8 || token[player][goti] == 13 || token[player][goti] == 26 || token[player][goti] == 16 || token[player][goti] == 34 || token[player][goti] == 39 || token[player][goti] == 47)
                 {
                     cout<<token[player][goti]<<endl;
                  int temp = token[player][goti];
                  token[player][goti] =  temp - 51;
                  cout<<token[player][goti]<<endl;
                  design[token[player][goti]] = '4';
                 // clear_screen();
              //   sleep(2);
                      clear_screen();
                  initializeBoard();
                 }

                 else{

                  if(design[token[3][goti]] == '1'){
                    int pos = token[player][goti];
                        int p = getpos(pos);
                         if(p){
                            alive[0][p] =false;
                        }
                       // alive[0][p] =false;
                    //alive[0][goti] =false;
                   // token[1][goti] = 0;

                    cout<<token[player][goti]<<endl;
                  int temp = token[player][goti];
                  token[player][goti] =  temp - 51;
                  cout<<token[player][goti]<<endl;
                  design[token[player][goti]] = '4';
                  sleep(2);
                //      clear_screen();
                   initializeBoard();
                   cout<<"Player 4 KILLED Player 1 "<<endl;
                    }
                    else if(design[token[3][goti]] == '2'){
                        int pos = token[player][goti];
                        int p = getpos(pos);
                         if(p){
                            alive[1][p] =false;
                        }
                      //  alive[1][p] =false;
                   // alive[1][goti] =false;
                   // token[1][goti] = 12;

                    cout<<token[player][goti]<<endl;
                  int temp = token[player][goti];
                  token[player][goti] =  temp - 51;
                  cout<<token[player][goti]<<endl;
                  design[token[player][goti]] = '4';
                //  sleep(2);
                      clear_screen();
                   initializeBoard();
                   cout<<"Player 4 KILLED Player 2 "<<endl;
                    }
                    else if(design[token[3][goti]] == '3'){
                        int pos = token[player][goti];
                        int p = getpos(pos);
                        if(p){
                            alive[2][p] =false;
                        }
                     //   alive[2][p] =false;
                    //alive[2][goti] =false;
                   // token[1][goti] = 25;

                    cout<<token[player][goti]<<endl;
                  int temp = token[player][goti];
                  token[player][goti] =  temp - 51;
                  cout<<token[player][goti]<<endl;
                  design[token[player][goti]] = '4';
               //   sleep(2);
                clear_screen();
                   initializeBoard();
                   cout<<"Player 4 KILLED Player 3 "<<endl;
                    }

                    else{

                    cout<<token[player][goti]<<endl;
                  int temp = token[player][goti];
                  token[player][goti] =  temp - 51;
                  cout<<token[player][goti]<<endl;
                  design[token[player][goti]] = '4';
                 // clear_screen();
             //    sleep(2);
                clear_screen();
                  initializeBoard();
                    }
                 }
              }

           else
           {

               if(token[player][goti] == 0 || token[player][goti] == 8 || token[player][goti] == 13 || token[player][goti] == 26 || token[player][goti] == 16 || token[player][goti] == 34 || token[player][goti] == 39 || token[player][goti] == 47)
                 {
                   design[token[player][goti]] = '4';
                 //   clear_screen();
             //    sleep(2);
                      clear_screen();
                   initializeBoard();
                 }

                 else{



                    if(design[token[3][goti]] == '1')
                    {
                        int pos = token[player][goti];
                        int p = getpos(pos);
                       if(p){
                            alive[0][p] =false;
                        }
                      //  alive[0][p] =false;
                   // alive[0][goti] =false;
                   // token[1][goti] = 0;

                    design[token[player][goti]] = '4';
                //    sleep(2);
                      clear_screen();
                     initializeBoard();
                     cout<<"Player 4 KILLED Player 1 "<<endl;
                    }
                    else if(design[token[3][goti]] == '2'){
                        int pos = token[player][goti];
                        int p = getpos(pos);
                        if(p){
                            alive[1][p] =false;
                        }
                      //  alive[1][p] =false;
                  //  alive[1][goti] =false;
                   // token[1][goti] = 12;

                    design[token[player][goti]] = '4';
                //    sleep(2);
                      clear_screen();
                     initializeBoard();
                     cout<<"Player 4 KILLED Player 2 "<<endl;

                    }
                    else if(design[token[3][goti]] == '3'){
                        int pos = token[player][goti];
                        int p = getpos(pos);
                         if(p){
                            alive[2][p] =false;
                        }
                      //  alive[2][p] =false;
                   // alive[2][goti] =false;
                   // token[1][goti] = 25;

                    design[token[player][goti]] = '4';
                //    sleep(2);
                    clear_screen();
                    initializeBoard();
                    cout<<"Player 4 KILLED Player 3 "<<endl;

                    }
                    else{
                        design[token[player][goti]] = '4';
                      //   clear_screen();
                  //    sleep(2);
                      clear_screen();
                      initializeBoard();
                    }
                }

             }
        }


   }

  };


int getpos(int position)
{


    for (int player = 0; player < 4; player++) {
        for (int goti = 0; goti < 4; goti++) {
            if (token[player][goti] == position && alive[player][goti]) {
                return goti; // Return the token number
            }
        }
    }
    return 0; // Return -1 if no token is found at the given position
}

void clear_screen()
{
    system("clear || cls");
}


void initializeBoard()
{


    // Your initialization logic here

    cout<<RED<<"+-----------+ " <<RESET<<design[10] <<"|"<< design[11]<<"|"<< design[12] << GREEN<<" +-----------+" <<RESET<< endl;
    cout<<RED<<"| 1      1  | " <<RESET<<design[9]  <<"|" << pl2[0]<< "|" <<GREEN<< design[13] <<RESET<< GREEN<< " | 2      2  |" <<RESET<< endl;
    cout<<RED<<"|           | " <<RESET<<RED<<design[8]<<RESET  <<"|" << pl2[1]<< "|" << design[14] << GREEN<< " |           |" <<RESET<< endl;
    cout<<RED<<"|           | " <<RESET<<design[7]  <<"|" << pl2[2]<< "|" << design[15] << GREEN<< " |           |" <<RESET<< endl;
    cout<<RED<<"| 1      1  | " <<RESET<<design[6]  <<"|" <<pl2[3]<< "|" << design[16]  << GREEN<< " | 2      2  |" <<RESET<< endl;
    cout<<RED<<"+-----------+ " <<RESET<<design[5]  <<"|" << pl2[4]<< "|" << design[17] << GREEN<< " +-----------+" <<RESET<< endl;

    cout << "|" << design[51] << "|" <<RED<< design[0] <<RESET << "|" << design[1] << "|" << design[2] << "|" << design[3] << "|" << design[4] << "|" << "       " << "|" << design[18] << "|" << design[19] << "|" << design[20] << "|" << GREEN <<design[21] <<RESET<< "|" << design[22] << "|" << design[23] << "|" << endl;
    cout << "|" << design[50] << "|" << pl1[0] << "|" << pl1[1] << "|" << pl1[2] << "|" << pl1[3] << "|" << pl1[4] << "|" << "       " << "|" << pl3[4] << "|" << pl3[3] << "|" << pl3[2] << "|" << pl3[1] << "|" << pl3[0] << "|" << design[24] << "|" << endl;
    cout << "|" << design[49] << "|" << design[48] << "|" << BLUE<< design[47]<<RESET << "|" << design[46] << "|" << design[45] << "|" << design[44] << "|" << "       " << "|" << design[30] << "|" << design[29] << "|" << design[28] << "|" << design[27] << "|" << YELLOW<<design[26]<< RESET << "|" << design[25] << "|" << endl;


      cout<<BLUE<< "+-----------+ " <<RESET<< design[43] << "|" << pl4[4] << "|" << design[31]<< YELLOW<< " +-----------+" <<RESET<< endl;
      cout<<BLUE<< "| 4      4  | " <<RESET<< design[42] << "|" << pl4[3] << "|" <<design[32] << YELLOW<< " | 3      3  |" <<RESET<< endl;
      cout<<BLUE<< "|           | " <<RESET<< design[41] << "|" << pl4[2] << "|" <<design[33] << YELLOW<<" |           |" <<RESET<< endl;
      cout<<BLUE<< "|           | " <<RESET<<design[40] << "|" << pl4[1] << "|" <<design[34]<< YELLOW << " |           |" <<RESET<< endl;
      cout<<BLUE<< "| 4      4  | " <<RESET<<BLUE<<design[39]<<RESET << "|" << pl4[0] << "|" << design[35]<< YELLOW << " | 3      3  |"<<RESET << endl;
      cout<<BLUE<< "+-----------+ "<<RESET << design[38] << "|" << design[37] << "|" <<design[36] << YELLOW<< " +-----------+" <<RESET<< endl;

}




