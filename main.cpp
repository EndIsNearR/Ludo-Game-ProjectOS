#include"players.h"


int rollDie() {
    return rand() % 6 + 1;
}


void free()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            alive[i][j] = false;
        }
    }
}


// Function to simulate rolling a die


int player() {
    return rand() % 4 + 1;
}

  bool block(int position, int currentPlayer)
  {
    int count = 0;
    int block_pl = -1;

    // Check all players' tokens at the given position
    for (int player = 0; player < 4; player++) {
        for (int goti = 0; goti < 4; goti++) {
            if (token[player][goti] == position && alive[player][goti]) {
                if (block_pl == -1) {
                    block_pl = player;
                }
                if (block_pl == player) {
                    count++;
                }
            }
        }
    }

    // If there are two or more tokens of the same player and it's not the current player, block the position
    if (count >= 2 && block_pl != currentPlayer) {
        return true;
    }

    return false;
}



void showtokens(int player)
{
    int a = 0;

    for(int i=1; i<4; i++)
    {
        if(alive[player][i] == true)
        {
           cout<<" "<<i<<" ";
           a++;
        }
    }

     if(a==0)
     cout<<" No Tokens Available! :( "<<endl;

}



void* playerRoutine(void* arg) {
    int play = *(int*)arg;
    players p1;

    int tokenIndex = 0;

    // while (true) {
    int goti = 0;

    sem_wait(&hello);

    int diceRoll = rollDie();
    cout << "Dice: " << diceRoll << endl;

    cout << "Turn of Player: " << play + 1 << endl;

    if(diceRoll == 6) {
        cout << "If you want to spawn a new token then select any token. \n";
        cout << "Else you can choose the token number you wanna proceed with: ";
        showtokens(play);

    }

    int c = diceRoll;
    int a = 0;

    if(diceRoll != 6) {
        for(int i = 0; i < 4; i++) {
            if(alive[play][i] == true)
                a++;
        }
    }

    if(a > 0 || diceRoll == 6) {
        do {
            cout << "Chose Token: ";
            cin >> goti;

            if (goti < 0 || goti > 4) {
                cout << "Invalid token number. Please choose a valid token number (1-4)." << endl;
                continue;
            }

            if (alive[play][goti] == false && diceRoll != 6)
            {
                cout << "Chosen token is not alive. Please choose an alive token." << endl;
                continue;
            }

            if(play == 0 && alive[0][goti] == false && diceRoll == 6)
            {
                alive[0][goti] = true;
                diceRoll = 0;
                p1.moveToken(play, goti - 1, diceRoll);

            }
            else if(play == 1 && alive[1][goti] == false && diceRoll == 6)
            {
                alive[1][goti] = true;
                diceRoll = 0;

                p1.moveToken(play, goti - 1, diceRoll + 13);

            }
            else if(play == 2 && alive[2][goti] == false && diceRoll == 6)
            {
                alive[2][goti] = true;
                diceRoll = 0;
                p1.moveToken(play, goti - 1, diceRoll + 26);

            }

            else if(play == 3 && alive[3][goti] == false && diceRoll == 6)
            {
                alive[3][goti] = true;
                diceRoll = 0;
                p1.moveToken(play, goti - 1, diceRoll + 39);

            } else
            {
                if(alive[play][goti] == true)
                counter[play][goti-1] += diceRoll;
                p1.moveToken(play, goti - 1, diceRoll);
            }

        } while (alive[play][goti] == false);
    }
    else
    {
        cout << "No active tokens to move." << endl;
    }

    sem_post(&hello);

    // Sleep for some time to simulate game turns



    return NULL;
}



// Function to check for captures
void checkForCaptures(int player, int tokenIndex) {
    // Your capture logic here
}

// Function to check for a winning condition
//bool checkForWin(int player) {
//    // Your winning condition logic here
//}

// Function to display the board
void displayBoard() {
    // Your board display logic here
}

int main()
{
    srand(time(0)); // Seed the random number generator

    for (int i = 0;i<52;i++)
    {
        design[i] = '*';
    }



        for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            token[i][j] = 0;
            counter[i][j] = 1;
            home[i][j] = false;
        }
    }


    sem_init(&hello, 0, 1);
    pthread_t players[4];
   int play = player();
   int shuffle [4] = {0,1,2,3};

    while(finish!=16)
    {

    random_shuffle(shuffle,shuffle+4);


        for (int i = 0; i < 4; i++) {
            pthread_create(&players[i], NULL, playerRoutine, &shuffle[i]);
        }

        // Join threads
        for (int i = 0; i < 4; i++) {
            pthread_join(players[i], NULL);
        }





}


return 0;

}
