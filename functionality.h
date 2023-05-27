/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */
//-------------------------------------------------------------------------------------//
//------------------------------------Name: Abdul Wasay--------------------------------//
//------------------------------------Roll no: i22-1198--------------------------------//
//-------------------------------------------------------------------------------------//
//---Piece Starts to Fall When Game Starts---//
void fallingPiece(float &timer, float &delay, int &colorNum)
{   
    
    if (timer > delay)
    {
        
        for (int i = 0; i < 4; i++)
        {
            point_2[i][0] = point_1[i][0];
            point_2[i][1] = point_1[i][1];
            point_1[i][1] += 1; // How much units downward
        }
        
        
        if (!anamoly())
        {
            for (int i = 0; i < 4; i++)
                gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;

            int n = rand() % 7;
            colorNum = rand() % 7 + 1;
            //---Un-Comment this Part When You Make BLOCKS array---//
            
            for (int i = 0; i < 4; i++)
            {
                point_1[i][0] = BLOCKS[n][i] % 2;
                point_1[i][1] = BLOCKS[n][i] / 2 ;
            }
            
        }
        timer = 0;
    }
}

/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///

/*this function will receive delta x as input and based on the dynamics of the game at that instant, 
it will move the piece left or right*/ 
void sideways(int &delta_x)
{
   bool space;
   

    if(delta_x==1)
        {   
            space=true;               //assumption that there is space available
            for(int i=0; i<4; i++)
            {   
                if(point_1[i][0]>8) 
                {
                    space=false;           //this will check if there is any space for all elements of the shape for maximum sideways movement
                    break;
                }
            }
            for(int i=0; i<4; i++)
            if(gameGrid[point_1[i][1]][point_1[i][0]+1]!=0)  //checks if any adjacent block is present to the right. If there is a block, space would be false 
            {
                space=false;
                break;
            }  
            if(space)
            {
                for(int i=0; i<4; i++)
                point_1[i][0] += 1;        //if there is space avaiable, only then would the shape move one unit right
            }
        }
     else if(delta_x==-1)
        {   
            space=true;                 //assuming that space is available for left movement
            
            for(int i=0; i<4; i++)
            {
                if(point_1[i][0]<1)
                space=false;           //this will check if there is any space for all elements of the shape for sideways movement
            }
             
            for(int i=0; i<4; i++)
            if(gameGrid[point_1[i][1]][point_1[i][0]-1]!=0)  //checks if any adjacent block is present to the left. If there is a block, space would be false.
            {
                space=false;
                break;
            }    
            if(space)
            {
                for(int i=0; i<4; i++)
                point_1[i][0] -= 1;        //if there is space avaiable, only then would the shape move one unit left
            }
        }
}

//-------------------------------------------------------------------------------------------//
//this function will clear rows
int RowClear(int &cleared_count)
{   
    bool cleared=true;    //assumption that row/s is/are cleared
    int counter=0;        //counter will check if a row is cleared
    for(int i=M-1; i>0; i--)   //loop starts from M-1(bottom most row) and iterates to 1(top most row)
    {   
        counter=0;
        for(int j=0; j<N; j++)
        if(gameGrid[i][j]!=0)
        {
            counter++;
        }
        if(counter==N)    //if counter becomes equal to the number of colums, that means the row is cleared
        {   cleared_count++;
            for(int m=i; m>0; m--)
            {
                for(int n=0; n<N; n++)
                gameGrid[m][n]=gameGrid[m-1][n];   //this statement will assign every block above our cleared row to the current row
            }
        }
        
    }
    return cleared_count;

}
//-------------------------------------------------------------------------------------------//
//this function will receive counter(how many rows cleared in one instance) and the current score. It will increase the score accordingly based on given conditons
void points_scored(int &cleared_count, int &score)
{
    switch(cleared_count)
    {   
        case 0:
        return;         //when no row is cleared

        case 1:         //when one row is cleared 
        score+=10;
        return;

        case 2:         //when two rows cleared simultaneously 
        score+=30;
        return;

        case 3:         //when three rows cleared simultaneously 
        score+=60;
        return;

        case 4:         //when four rows cleared simultaneously 
        score+=100;
        return;
    }
}
//-------------------------------------------------------------------------------------------//
//Spacebar will receive inputs and increase delay accordingly 
void Spacebar(bool &spacebar, float &delay, float &timer)
{   
    if(spacebar)
    {
    delay=0.00005;   //if spacebar key is pressed, delay is increased so that the block falls instantly 

    for(int i=M-1; i>0; i--)
    if((gameGrid[point_1[i][1]][point_1[i][0]])!=0)  //this loop will check points on the grid and if any point is !=0,
    timer=0;                                         //it will reset the timer and the next block will be loaded.
    }
}
//-------------------------------------------------------------------------------------------//
//this function will determine whether the blocks have reached the top row or not. If they have, it will return true
bool GameOver()
{
    for(int i=0; i<N; i++)
    {   
        if(gameGrid[2][i]!=0)            //if any of the columns of the second row has any non zero integer, the top row has been reached by the blocks
        return true;
        
    }
    return false;
}
//-------------------------------------------------------------------------------------------//
//this function will reset the timer and the score to zero if a new game has to be started 
void NewGame(float &timer, int &score)
{   timer=0;
    score=0;
    for(int i=M-1; i>0; i--)
    for(int j=0; j<=N; j++)
    gameGrid[i][j]=0;        //to clear the grid 

    for(int i=0; i<4; i++)
    {
        point_1[i][0]=0;
        point_1[i][1]=0;    //to clear the current coordinates contained in point 1 and point 2
        point_2[i][0]=0;
        point_2[i][1]=0;
    }
    
}

//-------------------------------------------------------------------------------------------//
//this function will receive the array as input and determine whether the current square qualifies to be fitted in the highscores list
void calculateScore(int highestScore[],int size, int &score)
{   
    if(highestScore[9]<=score)    //since our array is already sorted, the last element would contain the least highest score
    {   
        highestScore[9]=score;
        int temp=0;
        for(int i=0; i<size; i++)
        {
            for(int j=0; j<size-1-i; j++)
            if(highestScore[j+1]>highestScore[j])     //sorting the array from highest score to loweset
            {
                temp=highestScore[j];
                highestScore[j]=highestScore[j+1];
                highestScore[j+1]=temp;
            }

        }
    }
}
//-------------------------------------------------------------------------------------------//
///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////