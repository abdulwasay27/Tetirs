/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 * */
//-------------------------------------------------------------------------------------//
//------------------------------------Name: Abdul Wasay--------------------------------//
//------------------------------------Roll no: i22-1198--------------------------------//
//-------------------------------------------------------------------------------------//
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include<sstream>
#include <fstream> 
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
using namespace sf;
int main()
{   

    srand(time(0));
    RenderWindow window(VideoMode(320, 480), title);
    Texture obj1, obj2, obj3, obj4, obj5, obj6, obj7;
    //---------------------------------------------------------------------//
    //----------Creation and loading of images into created objects--------//
    //---------------------------------------------------------------------//
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/background.png");
    obj3.loadFromFile("img/frame.png");
    obj4.loadFromFile("img/menu.png");
    obj5.loadFromFile("img/help.png");
    obj6.loadFromFile("img/gameover.png");
    obj7.loadFromFile("img/startscreen.png");
    
    //------------------------------------------------------------------------------------------------//
    //----------Creating an object of Font class with name scorefont and loading font from file-------//
    //------------------------------------------------------------------------------------------------//
    
    Font scorefont;
    scorefont.loadFromFile("Fonts/scorefont.ttf");



    //---------------------------------------------------------------------//
    //----------Loading data from the highscore file into an array---------//
    //---------------------------------------------------------------------//
    int highestScore[10]={0};
    std::ifstream inputFile("score/highscores.txt");      //creating object of ifstream class
    int i=0;
        while(!inputFile.eof())
        {
            inputFile>>highestScore[i];                    //to read data from the file 
            i++;
        }                    

        inputFile.close();
    //---------------------------------------------------------------------//
    //----------Objects of class Text to display the text on screen--------//
    //---------------------------------------------------------------------//
    Text scoring, highscore1, highscore2, highscore3;
    scoring.setCharacterSize(20);
    scoring.setPosition({230,135});  
    scoring.setFont(scorefont);
    scoring.setFillColor(Color::Cyan);

    highscore1.setCharacterSize(20);
    highscore1.setPosition({230,185});  
    highscore1.setFont(scorefont);
    highscore1.setFillColor(Color::Green);

    highscore2.setCharacterSize(20);
    highscore2.setPosition({230,225});  
    highscore2.setFont(scorefont);
    highscore2.setFillColor(Color::Green);

    highscore3.setCharacterSize(20);
    highscore3.setPosition({230,265});  
    highscore3.setFont(scorefont);
    highscore3.setFillColor(Color::Green);

    //-------------------------------------------------------------------------------------------//
    //----------Sprite creation to display objects on the screen + declaring variables-----------//
    //-------------------------------------------------------------------------------------------//    

    Sprite sprite(obj1), background(obj2), frame(obj3), menu(obj4), help(obj5), gameover(obj6), startscreen(obj7);

    int delta_x = 0, colorNum = 1, cleared_count=0, score=0;
    float timer = 0, delay = 0.3;
    bool rotate = 0;
    bool spacebar=false, pause=false, newgame=false, main_screen=true;
    
    //-------------------------------------------------------------------------------------------//
    //------------------------Adding background sound to the game---------------------------------//
    //-------------------------------------------------------------------------------------------// 
    SoundBuffer SoundBuffer;
    Sound sound;
    SoundBuffer.loadFromFile("sounds/backgroundmusic.ogg");     //for playing the background sound
    sound.setBuffer(SoundBuffer);
    sound.play();
    sound.setVolume(20);
    //-------------------------------------------------------------------------------------------//
    //------------------------------------------Start of program---------------------------------//
    //-------------------------------------------------------------------------------------------//

    Clock clock;
    while (window.isOpen())
    {   
        while(!newgame)
        {   
            while(main_screen)                     
            { 
                window.draw(startscreen);
                window.display();
                if (Keyboard::isKeyPressed(Keyboard::Enter))   
                main_screen=false;
                if (Keyboard::isKeyPressed(Keyboard::Escape))
                return 0;
            }

        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        pause=false; 
        spacebar=false; 
        timer += time;
        delta_x = 0;
        delay = 0.3;
        cleared_count=0;
        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e))
        {                                // Event is occurring - until the game is in running state
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close();          // Opened window disposes
            if (e.type == Event::KeyPressed)
            {                                           // If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up)         // Check if the other key pressed is UP key
                  rotate = true;                      // Rotation gets on
                else if (e.key.code == Keyboard::Left)  // Check if the other key pressed is LEFT key
                    delta_x = -1;                       // Change in X-Axis - Negative
                else if (e.key.code == Keyboard::Right) // Check if the other key pressed is RIGHT key
                    delta_x = 1;                        // Change in X-Axis - Positive
                
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) // Just another way to detect key presses without event listener
            delay = 0.05;                           // If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05
        
        if (Keyboard::isKeyPressed(Keyboard::H)) // To pause the game
            pause=true;
        if (Keyboard::isKeyPressed(Keyboard::Space))   //to instantly place the block on the grid 
        spacebar=true;
        
    //-------------------------------------------------------------------------------------------//
    //-----------------------------Execution of pause statements---------------------------------//
    //-------------------------------------------------------------------------------------------//         

        while(pause==true)         //If pause is pressed, the game will be paused and menu will be displayed
        {
            sound.pause();
            window.draw(menu);    //to draw the menu
            window.display();

            if (Keyboard::isKeyPressed(Keyboard::Num1)) //if num1 is pressed, game will restart
            {   sound.play();
                newgame=true;
                pause=false;
                continue;
            }

            if (Keyboard::isKeyPressed(Keyboard::Num2))  //to start the help menu
            {   
                bool escape=true;
                window.draw(help);          //to draw help menu              
                window.display();
                while(escape)
                {
                    if (Keyboard::isKeyPressed(Keyboard::Num0))  //to exit from the help menu
                    escape=false;
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::Num3))  //if num3 is pressed, game will be closed
            return 0;

            if (Keyboard::isKeyPressed(Keyboard::Num4))  //to resume the game
            {
                sound.play();
                break;
            }
        }
        ///////////////////////////////////////////////
        ///*** START CALLING YOUR FUNCTIONS HERE ***///

    //-------------------------------------------------------------------------------------------//
    //------------------------------------Gameover function--------------------------------------//
    //-------------------------------------------------------------------------------------------// 
        if(GameOver())       //gameover is a boolean function which will return either true or false based on the current state of the game
        {   
            calculateScore(highestScore, 10, score);
            std::ofstream outputFile("score/highscores.txt");   //creating an object of ofstream class
              
            for(int j=0; j<10; j++)
            outputFile << highestScore[j]<<'\n';            //to write data to the file 
            
            outputFile.close();

            while(true)
            {
                window.draw(gameover);             //displaying gameover menu and taking user inputs accordingly
                window.display();
                if (Keyboard::isKeyPressed(Keyboard::Num5))
                {
                    newgame=true;
                    break;
                }
                if (Keyboard::isKeyPressed(Keyboard::Num6))
                return 0;
            }
        }
    //-------------------------------------------------------------------------------------------//
    //------------------------------------NewGame function--------------------------------------//
    //-------------------------------------------------------------------------------------------//
        if(newgame)
        {
            NewGame(timer, score);
            newgame=false;
            continue;
        }
    //-------------------------------------------------------------------------------------------//
    //------------------------------------Spacebar function--------------------------------------//
    //-------------------------------------------------------------------------------------------//
        Spacebar(spacebar, delay, timer); 
    //-------------------------------------------------------------------------------------------//
    //---------------------------------Falling piece function------------------------------------//
    //-------------------------------------------------------------------------------------------//
        fallingPiece(timer, delay, colorNum); 
    //-------------------------------------------------------------------------------------------//
    //------------------------------------Sideways function--------------------------------------//
    //-------------------------------------------------------------------------------------------//
        sideways(delta_x); 

    //-------------------------------------------------------------------------------------------//
    //------------------------------------RowClear function--------------------------------------//
    //-------------------------------------------------------------------------------------------//
        cleared_count=RowClear(cleared_count); //row clear function will return the number of rows cleared and that integer will be stored in cleared count
    //-------------------------------------------------------------------------------------------//
    //---------------------------------PointsScored function--------------------------------------//
    //-------------------------------------------------------------------------------------------//
        points_scored(cleared_count, score);  //points scored function will calculate the number of points scored when the player clears a row/s

       
        
        
        
            
    
        
        ///*** YOUR CALLING STATEMENTS END HERE ***///
        //////////////////////////////////////////////

        window.clear(Color::Black);
        window.draw(background);
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (gameGrid[i][j] == 0)
                    continue;
                sprite.setTextureRect(IntRect(gameGrid[i][j] * 18, 0, 18, 18));
                sprite.setPosition(j * 18, i * 18);
                sprite.move(28, 31); // offset
                window.draw(sprite);
            }
        }
        for (int i = 0; i < 4; i++)
        {
            sprite.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
            sprite.setPosition(point_1[i][0] * 18, point_1[i][1] * 18);
            sprite.move(28, 31);
            window.draw(sprite);
        }

    //-----------------------------------------------------------------------------------------------------------------------//
    //---------Creating objects of string stream class that will convert the score to a string and display on screen---------//
    //-----------------------------------------------------------------------------------------------------------------------//
        std::ostringstream userscore, score1, score2, score3;    //score1, score2, score3 display the high scores in descending order
        userscore<<"Score: "<< score;
        
        score1<<"1. "<< highestScore[0];        //index 0 will contain the highest score
        score2<<"2. "<< highestScore[1];       //index 1 will contain the second highest score
        score3<<"3. "<< highestScore[2];       //index 2 will contain the third highest score

        scoring.setString(userscore.str());
        highscore1.setString(score1.str());
        highscore2.setString(score2.str());
        highscore3.setString(score3.str());


        
        window.draw(frame);
        window.draw(scoring);
        window.draw(highscore1);                         //drawing highscores and the current score on screen
        window.draw(highscore2);
        window.draw(highscore3);

        
        
        //---The Window that now Contains the Frame is Displayed---//
        window.display();
        }
    }
    
    return 0;
}
