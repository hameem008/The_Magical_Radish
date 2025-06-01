# include "igraphics.h"
#include<string.h>

int width=1400, height=700;//screen specifier
double rx=750,ry=500;//initial position of radish and it's coordinate(rx,ry)//also bear the (mx,my) of mouse function
//rx and ry also help to extract the coordinate of mouse click from the iMouse function which is usable outside the iMouse function
double dx=0,dy=0; //initial position of donkey and it's coordinate(dx,dy)
int dif_initial_value;//this variable is using for initialing dif variable(declared for testing)
int dif_initial_value_easy=30;//dif initialing value for easy mode
int dif_initial_value_medium=27;//dif initialing value for medium mode
int dif_initial_value_hard=25;//dif initialing value for hard mode
int dif_decrement=5;//this variable indicates the decrement amount of dif variable after completing a level
int dif;//game difficulty controller //if dif decreases difficulty increases
int dif_timer=10; //donkey movement smoothing controller
int window_controller=0; // this variable control which window will come
int run=0; //donkey running variable
int run_timer=90;//=3*dif; //control the running position of donkey
int level; // this variable control the level related text and window transformation, max value=5
int energy;//this variable control the duration of a level
int initial_energy=120;//standard value is 120 because the energy box's length is 120
int Scores;//this variable count the Scores
char po[10];//this string makes Scores variable printable by iText() function
char po_hs[10];//this string makes high scores variable printable for iText() function
//this po and po_hs variable convert scores and high scores to string to make it printable in game console
int radish_remaning;//how many radish are remaining (max value is 3)
int rot_rad=1;//this variable control the rotating of the radish
int point_ar[6]={0,0,0,0,0,0};//this is an array which is used to decrease the point of an incomplete level
//its max index=max value of level variable
bool save_game_switch=true;//this variable is to read the saved game properties for only one time
bool music=true;//this variable control music
bool gaming=true;//this variable indicates if the game is running at a certain time
//it also have a function to pause or resume the game
//to pause the game press "p" to resume the game press "r"
bool read_high_score_switch=true;//this switch allows the program to read high scores for only once at a time
bool write_high_score_switch=true;//this switch allows the program to write high score for only once at a time
int conx=620,cony=400;//continue box dialog
int new_gamex=610,new_gamey=350; // "New game" dialog box parameter new_game
int setting_x=630,setting_y=300;//setting box coordinate
int music_x=615,music_y=350;//music box coordinate
int control_x=623,control_y=300;//control box coordinate
int high_score_x=605,high_score_y=250;//high score box coordinate
int help_x=640,help_y=200;//help box coordinate
int credits_x=630,credits_y=150;//credits box coordinate
int exit_x=645,exit_y=100;//exit dialog box specifier
int start_again_x=660, start_again_y=360;//coordinate for start_again dialog box
int next_x=685,next_y=350;//next dialog box variable
int easy_x=450,easy_y=275;//easy dialog box specification
int medium_x=easy_x+70+100,medium_y=275;//medium dialog box specification
int hard_x=medium_x+105+100,hard_y=275;//hard dilog box specification
int high_score;//this variable is for showing best score in high score window
//among saved player history it represent the highest value of score
char player_name[80];//this is for player name
int player_name_index=0;
bool read_name_switch=true;//this switch allows the program to read player name for only once a time
char last_player_name_1[80], last_player_name_2[80],last_player_name_3[80],last_player_name_4[80],last_player_name_5[80];
//this variables for storing players name when the program is running
int last_player_score_1,last_player_score_2,last_player_score_3,last_player_score_4,last_player_score_5;
//this variables for storing players scores when the program is running
int i;//this variable for operating the sorting loop


/*
	function iDraw() is called again and again by the system.
*/
void iDraw()
{
    //place your drawing codes here

    if(window_controller==0){ //start menu of the game. the value of window_controller=0 means main menu
        iClear();
        iShowBMP(0,0,"images//main_menu.bmp");//showing the background of main_menu
        iShowBMP2(500,450,"images//game_name.bmp",0);//game name image

        if(save_game_switch==true){
                FILE *r;//reading the variables which is the key for saved game
                r=fopen("files//save_game.txt","r");
                fscanf(r,"%d %d %d %d",&level,&Scores,&radish_remaning,&dif);//reading this variable
                if(read_name_switch==true) fscanf(r,"%s",player_name);//this means it will only take input the name from save game file if
                //the last game was not over (level not equal to zero)
                fclose(r);
                itoa(Scores,po,10);//this function convert the Scores variable(integer) to a string to be valid for iText() function
                save_game_switch=false;//this statement turns off the save_game_switch
        }

        if(level!=0){//continue dialog box
                iSetColor(255,255,255);
                iRectangle(conx,cony,110,40);//continue dialog box
                iSetColor(255,255,255);
                iText(conx+10,cony+10,"Continue",GLUT_BITMAP_TIMES_ROMAN_24);//writing continue
                if(rx>=conx&&rx<=(conx+110)&&ry>=cony&&ry<=(cony+40)){//going to game field by using continue
                    rx=750; ry=500;//initialing radish coordinate to avoid error
                    dx=0; dy=0;//initialing donkey coordinate
                    energy=initial_energy;//initialing energy
                    read_high_score_switch=true;//initialing the switch variable every time to make the block of codes executable in game over window
                    //and next/game complete window
                    write_high_score_switch=true;//initialing the switch variable every time to make the block of codes executable in game over window
                    //and next/game complete window
                    iResumeTimer(0); iResumeTimer(1); iResumeTimer(2); iResumeTimer(3); gaming=true;//resuming the game in case the game was paused before
                    window_controller=1;//going to game field
                }
        }

        iSetColor(255,255,255);
        iRectangle(new_gamex,new_gamey,130,40); //play dialog box
        iSetColor(255,255,255);
        iText(new_gamex+10,new_gamey+10,"New Game",GLUT_BITMAP_TIMES_ROMAN_24); //writing play
        if(rx>=new_gamex&&rx<=(new_gamex+130)&&ry>=new_gamey&&ry<=(new_gamey+40)){ //after clicking on play going to game field
            //every variable will be initialize in the difficulty window after selecting a difficulty mode
            read_high_score_switch=true;//initialing the switch variable every time to make the block of codes executable in game over window
            //and next/game complete window
            write_high_score_switch=true;//initialing the switch variable every time to make the block of codes executable in game over window
            //and next/game complete window
            strcpy(player_name," ");//making free the player name
            player_name_index=0;//initialing index of player name
            iResumeTimer(0); iResumeTimer(1); iResumeTimer(2); iResumeTimer(3); gaming=true;//resuming the game in case the game was paused before
            window_controller=11; //going to difficulty window
        }

        iSetColor(255,255,255);
        iRectangle(exit_x,exit_y,60,40);//exit dialog box
        iSetColor(255,255,255);
        iText(exit_x+10,exit_y+10,"Exit",GLUT_BITMAP_TIMES_ROMAN_24);//writing exit
        if(rx>=exit_x&&rx<=(exit_x+60)&&ry>=exit_y&&ry<=(exit_y+40)) {//saving the game in a file
                FILE *w;
                w=fopen("files//save_game.txt","w");
                fprintf(w,"%d %d %d %d %s",level,Scores,radish_remaning,dif,player_name);//by saving this five variable, the game can be saved
                fclose(w);
                exit(1);//exiting game
        }

        iSetColor(255,255,255);
        iRectangle(help_x,help_y,70,40);//help dialog box
        iText(help_x+10,help_y+10,"Help",GLUT_BITMAP_TIMES_ROMAN_24);//writing help
        if(rx>=help_x&&rx<=(help_x+70)&&ry>=help_y&&ry<=(help_y+40)){//going to help window
            window_controller=6;
        }

        iSetColor(255,255,255);
        iRectangle(setting_x,setting_y,90,40);//setting dialog box
        iSetColor(255,255,255);
        iText(setting_x+10,setting_y+10,"Setting",GLUT_BITMAP_TIMES_ROMAN_24);//writing setting
        if(rx>=setting_x&&rx<=(setting_x+100)&&ry>=setting_y&&ry<=(setting_y+40)){//going to setting window
            rx=0; ry=0;//initialing rx and ry to avoid error
            window_controller=8;
        }
        iSetColor(255,255,255);
        iRectangle(high_score_x,high_score_y,140,40);//hifh score dialog box
        iSetColor(255,255,255);
        iText(high_score_x+10,high_score_y+10,"High Scores",GLUT_BITMAP_TIMES_ROMAN_24);//writing high score
        if(rx>=high_score_x&&rx<=(high_score_x+140)&&ry>=high_score_y&&ry<=(high_score_y+40)){
            read_high_score_switch=true;//switching on for assurance to avoid read error
            window_controller=10;
        }
        iSetColor(255,255,255);
        iRectangle(credits_x,credits_y,90,40);//credits dialog box
        iSetColor(255,255,255);
        iText(credits_x+10,credits_y+10,"Credits",GLUT_BITMAP_TIMES_ROMAN_24);//writing credits
        if(rx>=credits_x&&rx<=(credits_x+90)&&ry>=credits_y&&ry<=(credits_y+40)){//going to credits window
            window_controller=9;
        }
    }
    else if(window_controller==1){  // here window_controller=1 means game field window
        iClear();

        {//displaying the background of game_field for different level
            if(level==0) iShowBMP(0,0,"images//level1.bmp");
            else if(level==1) iShowBMP(0,0,"images//level2.bmp");
            else if(level==2) iShowBMP(0,0,"images//level3.bmp");
            else if(level==3) iShowBMP(0,0,"images//level4.bmp");
            else if(level==4) iShowBMP(0,0,"images//level5.bmp");
        }

        {//rotating and displaying the radish
            //displaying the radish corresponding to the value of rot_rat variable
            if(rot_rad==1) iShowBMP2(rx,ry,"images//rot_rad_1.bmp",0);
            else if(rot_rad==2) iShowBMP2(rx,ry,"images//rot_rad_2.bmp",0);
            else if(rot_rad==3) iShowBMP2(rx,ry,"images//rot_rad_3.bmp",0);
            else if(rot_rad==4) iShowBMP2(rx,ry,"images//rot_rad_4.bmp",0);
        }

        iSetColor(255,255,255); iText(120,650,"Scores: ",GLUT_BITMAP_TIMES_ROMAN_24);//displaying the word "Scores: "
        iSetColor(255,255,255); iText(195,650,po,GLUT_BITMAP_TIMES_ROMAN_24);//displaying the value of Scores variable

    {//writing level during playing
        if(level==0){
            iSetColor(255,255,255);
            iText(640,100,"Level 1",GLUT_BITMAP_TIMES_ROMAN_24);
        }
        else if(level==1){
            iSetColor(255,255,255);
            iText(640,100,"Level 2",GLUT_BITMAP_TIMES_ROMAN_24);
        }
        else if(level==2){
            iSetColor(255,255,255);
            iText(640,100,"Level 3",GLUT_BITMAP_TIMES_ROMAN_24);
        }
        else if(level==3){
            iSetColor(255,255,255);
            iText(640,100,"Level 4",GLUT_BITMAP_TIMES_ROMAN_24);
        }
        else if(level==4){
            iSetColor(255,255,255);
            iText(640,100,"Level 5",GLUT_BITMAP_TIMES_ROMAN_24);
        }
    }

    {//creating the visual expression of remaining radish
        if(radish_remaning==3){
            iShowBMP2(10,470,"images//radish.bmp",0);//showing radish image
            iSetColor(255,255,255);
            iText(60,490,"X3",GLUT_BITMAP_TIMES_ROMAN_24);//writing how many of radish are remaining
        }
        else if(radish_remaning==2){
            iShowBMP2(10,470,"images//radish.bmp",0);//showing radish image
            iSetColor(255,255,255);
            iText(60,490,"X2",GLUT_BITMAP_TIMES_ROMAN_24);//writing how many of radish are remaining
        }
        else if(radish_remaning==1){
            iShowBMP2(10,470,"images//radish.bmp",0);//showing radish image
            iSetColor(255,255,255);
            iText(60,490,"X1",GLUT_BITMAP_TIMES_ROMAN_24);//writing how many of radish are remaining
        }
    }

        iSetColor(255,255,255);
        iText(20,600,"Energy of donkey",GLUT_BITMAP_TIMES_ROMAN_24);//writing energy of donkey
        iSetColor(0,0,0);
        iRectangle(20,560,120,30);//energy box specification
        iSetColor(255,0,0);
        iFilledRectangle(20,560,energy,30); //energy indicator

        if(energy==0){//going to next level window
            rx=750; ry=500; //initialing value of coordinate of radish
            level=level+1;//increasing level
            window_controller=3; //condition for going to next level (when the energy of donkey is zero)
        }

        iSetColor(255,255,255);
        iRectangle(20,640,70,40);//quit dialog box specification
        iSetColor(255,255,255);
        iText(30,650,"Quit",GLUT_BITMAP_TIMES_ROMAN_24); //quit option
        if(rx>=20&&rx<=(20+70)&&ry>=640&&ry<=(640+40)){//quit condition
            Scores=Scores-point_ar[level];//subtracting the scores of incomplete level from total scores
            itoa(Scores,po,10);//this function convert the Scores variable(integer) to a string to be valid for iText() function
            point_ar[level]=-1;//initialing this variable for avoiding scoring error
            //if it wasn't use the score can increase by one after every quit and exit(saving the game can also be hampered)
            window_controller=0; //going  to main menu
        }

    {//donkey movement section
        if (dx>rx){//animated movement of donkey
            if(run%2==0) iShowBMP2(dx,dy,"images//rundonleft1.bmp",0);
            else iShowBMP2(dx,dy,"images//rundonleft2.bmp",0);
        }
        else if(dx<rx){//animated movement of donkey
            if(run%2==0) iShowBMP2(dx,dy,"images//rundonright1.bmp",0);
            else iShowBMP2(dx,dy,"images//rundonright2.bmp",0);
        }
    }

        if(fabs(rx-dx)<60&&fabs(ry-dy)<60&&gaming==true){ //game over or reducing remaining radish condition where the donkey gets radish
                rx=750; ry=500; //initialing value of coordinate of radish //initialing again for avoiding error
                radish_remaning=radish_remaning-1;//decreasing remaining radish
                if(radish_remaning!=0) window_controller=4; //going to radish remaining window
                else window_controller=2; //going to game over window
        }

    }
    else if(window_controller==2){ //here window_controller=2 means game over window
        iClear();
        //displaying the background of game_field
        if(level==0) iShowBMP(0,0,"images//level1.bmp");
        else if(level==1) iShowBMP(0,0,"images//level2.bmp");
        else if(level==2) iShowBMP(0,0,"images//level3.bmp");
        else if(level==3) iShowBMP(0,0,"images//level4.bmp");
        else if(level==4) iShowBMP(0,0,"images//level5.bmp");
        iShowBMP2(100,40,"images//eating_radish.bmp",0);

        iSetColor(255,255,255);
        iText(645,450,"Game Over",GLUT_BITMAP_TIMES_ROMAN_24); //declaring game over

        iSetColor(255,255,255); iText(190,650,"Scores: ",GLUT_BITMAP_TIMES_ROMAN_24);//displaying the word "Scores: "
        iSetColor(255,255,255); iText(265,650,po,GLUT_BITMAP_TIMES_ROMAN_24);//displaying the value of Scores variable

    {//writing level complete after game over//now max level is 5
        if(level==1){//if level 1 is complete and the donkey gets radish in level 2 (if the game over after completing level 1)
            iSetColor(255,255,255);
            iText(620,420,"Level 1 complete",GLUT_BITMAP_TIMES_ROMAN_24);
        }
         else if(level==2){//if level 2 is complete and the donkey gets radish in level 3 (if the game over after completing level 3)
            iSetColor(255,255,255);
            iText(620,420,"Level 2 complete",GLUT_BITMAP_TIMES_ROMAN_24);
        }
        else if(level==3){//if level 3 is complete and the donkey gets radish in level 4 (if the game over after completing level 3)
            iSetColor(255,255,255);
            iText(620,420,"Level 3 complete",GLUT_BITMAP_TIMES_ROMAN_24);
        }
        else if(level==4){//if level 4 is complete and the donkey gets radish in level 5 (if the game over after completing level 4)
            iSetColor(255,255,255);
            iText(620,420,"Level 4 complete",GLUT_BITMAP_TIMES_ROMAN_24);
        }
    }
    {//this portion repeats in the next/game complete window
         if(read_high_score_switch==true){//this portion of code can read the previous players name and scores from file
            FILE *hs;
            hs=fopen("files//high_score.txt","r");
            fscanf(hs,"%d",&high_score);//reading high score from a separate file
            fclose(hs);
            FILE *cp;
            cp=fopen("files//last_player.txt","r");//reading previous players name and scores
            fscanf(cp,"%d %s",&last_player_score_1,last_player_name_1);
            fscanf(cp,"%d %s",&last_player_score_2,last_player_name_2);
            fscanf(cp,"%d %s",&last_player_score_3,last_player_name_3);
            fscanf(cp,"%d %s",&last_player_score_4,last_player_name_4);
            fscanf(cp,"%d %s",&last_player_score_5,last_player_name_5);
            fclose(cp);
            read_high_score_switch=false;//switching of so that it can't execute again. but in future this switch can be on and it can execute.
        }
        {//this portion do the inverse appending. the 3rd player gets the name and score of 2nd player
            //the 2nd player  gets the name and scores of 1st player
            //the 1st player gets the name and scores of current player
            strcpy(last_player_name_5,last_player_name_4);
            strcpy(last_player_name_4,last_player_name_3);
            strcpy(last_player_name_3,last_player_name_2);
            strcpy(last_player_name_2,last_player_name_1);
            strcpy(last_player_name_1,player_name);
            last_player_score_5=last_player_score_4;
            last_player_score_4=last_player_score_3;
            last_player_score_3=last_player_score_2;
            last_player_score_2=last_player_score_1;
            last_player_score_1=Scores;
        }
        {//this portion just calculating the highest value of scores among three player
        if(last_player_score_1>=last_player_score_2&&last_player_score_1>=last_player_score_3&&last_player_score_1>=last_player_score_4&&last_player_score_1>=last_player_score_5) high_score=last_player_score_1;
        else if(last_player_score_2>=last_player_score_1&&last_player_score_2>=last_player_score_3&&last_player_score_2>=last_player_score_4&&last_player_score_2>=last_player_score_5) high_score=last_player_score_2;
        else if(last_player_score_3>=last_player_score_1&&last_player_score_3>=last_player_score_2&&last_player_score_3>=last_player_score_4&&last_player_score_3>=last_player_score_5) high_score=last_player_score_3;
        else if(last_player_score_4>=last_player_score_1&&last_player_score_4>=last_player_score_2&&last_player_score_4>=last_player_score_3&&last_player_score_4>=last_player_score_5) high_score=last_player_score_4;
        else if(last_player_score_5>=last_player_score_1&&last_player_score_5>=last_player_score_2&&last_player_score_5>=last_player_score_3&&last_player_score_5>=last_player_score_4) high_score=last_player_score_5;
        }
         if(write_high_score_switch==true){//this portion of code can write the previous players name and scores in file
            FILE *hs;
            hs=fopen("files//high_score.txt","w");
            fprintf(hs,"%d",high_score);//writing high score in a separate file
            fclose(hs);
            FILE *cp;
            cp=fopen("files//last_player.txt","w");//writing the new list
            for(i=0;i<5;i++){//the sorting loop
                    //this loop calculate the maximum score, print it in file and make it zero
                    //again and again it will happen
                    //it is like a shorting method
                if(last_player_score_1>=last_player_score_2&&last_player_score_1>=last_player_score_3&&last_player_score_1>=last_player_score_4&&last_player_score_1>=last_player_score_5){
                    fprintf(cp,"%d %s\n",last_player_score_1,last_player_name_1);
                    last_player_score_1=0;
                }
                else if(last_player_score_2>=last_player_score_1&&last_player_score_2>=last_player_score_3&&last_player_score_2>=last_player_score_4&&last_player_score_2>=last_player_score_5){
                    fprintf(cp,"%d %s\n",last_player_score_2,last_player_name_2);
                    last_player_score_2=0;
                }
                else if(last_player_score_3>=last_player_score_1&&last_player_score_3>=last_player_score_2&&last_player_score_3>=last_player_score_4&&last_player_score_3>=last_player_score_5){
                    fprintf(cp,"%d %s\n",last_player_score_3,last_player_name_3);
                    last_player_score_3=0;
                }
                else if(last_player_score_4>=last_player_score_1&&last_player_score_4>=last_player_score_2&&last_player_score_4>=last_player_score_3&&last_player_score_4>=last_player_score_5){
                    fprintf(cp,"%d %s\n",last_player_score_4,last_player_name_4);
                    last_player_score_4=0;
                }
                else if(last_player_score_5>=last_player_score_1&&last_player_score_5>=last_player_score_2&&last_player_score_5>=last_player_score_3&&last_player_score_5>=last_player_score_4){
                    fprintf(cp,"%d %s\n",last_player_score_5,last_player_name_5);
                    last_player_score_5=0;
                }
            }
            fclose(cp);
            write_high_score_switch=false;//switching of so that it can't execute again. but in future this switch can be on and it can execute.
        }
    }

        iSetColor(255,255,255);
        iRectangle(20,640,140,40);//main menu dialog box specification
        iSetColor(255,255,255);
        iText(30,650,"Main Menu",GLUT_BITMAP_TIMES_ROMAN_24);//the main menu
        if(rx>=20&&rx<=(20+140)&&ry>=640&&ry<=(640+40)){ //condition for going to main menu
            level=0;//initialing level variable
            window_controller=0; // going to main menu
        }
    }
    else if(window_controller==3){//window for going to next level or game complete window
        iClear();
        //displaying the background of game field
        if(level==1) iShowBMP(0,0,"images//level1.bmp");
        else if(level==2) iShowBMP(0,0,"images//level2.bmp");
        else if(level==3) iShowBMP(0,0,"images//level3.bmp");
        else if(level==4) iShowBMP(0,0,"images//level4.bmp");
        else if(level==5) iShowBMP(0,0,"images//level5.bmp");

        iSetColor(255,255,255); iText(190,650,"Scores: ",GLUT_BITMAP_TIMES_ROMAN_24);//displaying the word "Scores: "
        iSetColor(255,255,255); iText(265,650,po,GLUT_BITMAP_TIMES_ROMAN_24);//displaying the value of Scores variable

        if(level<5){
            iSetColor(255,255,255);
            iText(640,450,"Level Complete",GLUT_BITMAP_TIMES_ROMAN_24); //declaring level complete
            iSetColor(255,255,255);
            iText(665,410,"Click Next",GLUT_BITMAP_TIMES_ROMAN_24); //click next dialog
        }
        else if(level==5){//this portion is same as game over portion
                iSetColor(255,255,255);
                iText(640,450,"Game Complete",GLUT_BITMAP_TIMES_ROMAN_24); //declaring game complete
                    if(read_high_score_switch==true){//this potion of code can read the previous players name and scores from file
                        FILE *hs;
                        hs=fopen("files//high_score.txt","r");
                        fscanf(hs,"%d",&high_score);//reading high score from a separate file
                        fclose(hs);
                        FILE *cp;
                        cp=fopen("files//last_player.txt","r");//reading previous players name and scores
                        fscanf(cp,"%d %s",&last_player_score_1,last_player_name_1);
                        fscanf(cp,"%d %s",&last_player_score_2,last_player_name_2);
                        fscanf(cp,"%d %s",&last_player_score_3,last_player_name_3);
                        fscanf(cp,"%d %s",&last_player_score_4,last_player_name_4);
                        fscanf(cp,"%d %s",&last_player_score_5,last_player_name_5);
                        fclose(cp);
                        read_high_score_switch=false;//switching of so that it can't execute again. but in future this switch can be on and it can execute.
                    }
                    {//this portion do the inverse appending. the 3rd player gets the name and score of 2nd player
                        //the 2nd player  gets the name and scores of 1st player
                        //the 1st player gets the name and scores of current player
                        strcpy(last_player_name_5,last_player_name_4);
                        strcpy(last_player_name_4,last_player_name_3);
                        strcpy(last_player_name_3,last_player_name_2);
                        strcpy(last_player_name_2,last_player_name_1);
                        strcpy(last_player_name_1,player_name);
                        last_player_score_5=last_player_score_4;
                        last_player_score_4=last_player_score_3;
                        last_player_score_3=last_player_score_2;
                        last_player_score_2=last_player_score_1;
                        last_player_score_1=Scores;
                    }
                    {//this portion just calculating the highest value of scores among three player
                    if(last_player_score_1>=last_player_score_2&&last_player_score_1>=last_player_score_3&&last_player_score_1>=last_player_score_4&&last_player_score_1>=last_player_score_5) high_score=last_player_score_1;
                    else if(last_player_score_2>=last_player_score_1&&last_player_score_2>=last_player_score_3&&last_player_score_2>=last_player_score_4&&last_player_score_2>=last_player_score_5) high_score=last_player_score_2;
                    else if(last_player_score_3>=last_player_score_1&&last_player_score_3>=last_player_score_2&&last_player_score_3>=last_player_score_4&&last_player_score_3>=last_player_score_5) high_score=last_player_score_3;
                    else if(last_player_score_4>=last_player_score_1&&last_player_score_4>=last_player_score_2&&last_player_score_4>=last_player_score_3&&last_player_score_4>=last_player_score_5) high_score=last_player_score_4;
                    else if(last_player_score_5>=last_player_score_1&&last_player_score_5>=last_player_score_2&&last_player_score_5>=last_player_score_3&&last_player_score_5>=last_player_score_4) high_score=last_player_score_5;
                    }
                    if(write_high_score_switch==true){//this portion of code can write the previous players name and scores in file
                        FILE *hs;
                        hs=fopen("files//high_score.txt","w");//writing high score in a separate file
                        fprintf(hs,"%d",high_score);
                        fclose(hs);
                        FILE *cp;
                        cp=fopen("files//last_player.txt","w");//writing the new list
                        for(i=0;i<5;i++){//the sorting loop
                                //this loop calculate the maximum score ,print it in file and make it zero
                                //again and again it will happen
                                if(last_player_score_1>=last_player_score_2&&last_player_score_1>=last_player_score_3&&last_player_score_1>=last_player_score_4&&last_player_score_1>=last_player_score_5){
                                    fprintf(cp,"%d %s\n",last_player_score_1,last_player_name_1);
                                    last_player_score_1=0;
                                }
                                else if(last_player_score_2>=last_player_score_1&&last_player_score_2>=last_player_score_3&&last_player_score_2>=last_player_score_4&&last_player_score_2>=last_player_score_5){
                                    fprintf(cp,"%d %s\n",last_player_score_2,last_player_name_2);
                                    last_player_score_2=0;
                                }
                                else if(last_player_score_3>=last_player_score_1&&last_player_score_3>=last_player_score_2&&last_player_score_3>=last_player_score_4&&last_player_score_3>=last_player_score_5){
                                    fprintf(cp,"%d %s\n",last_player_score_3,last_player_name_3);
                                    last_player_score_3=0;
                                }
                                else if(last_player_score_4>=last_player_score_1&&last_player_score_4>=last_player_score_2&&last_player_score_4>=last_player_score_3&&last_player_score_4>=last_player_score_5){
                                    fprintf(cp,"%d %s\n",last_player_score_4,last_player_name_4);
                                    last_player_score_4=0;
                                }
                                else if(last_player_score_5>=last_player_score_1&&last_player_score_5>=last_player_score_2&&last_player_score_5>=last_player_score_3&&last_player_score_5>=last_player_score_4){
                                    fprintf(cp,"%d %s\n",last_player_score_5,last_player_name_5);
                                    last_player_score_5=0;
                                }
                        }
                        fclose(cp);
                        write_high_score_switch=false;//switching of so that it can't execute again. but in future this switch can be on and it can execute.
                    }
        }

        if(level<5){//max level is 5//condition->(level<max_level-1)//condition for going to next level
            iSetColor(255,255,255);
            iRectangle(next_x,next_y,70,40);//next dialog box specification
            iSetColor(255,255,255);
            iText(next_x+10,next_y+10,"Next",GLUT_BITMAP_TIMES_ROMAN_24);
            if(rx>=next_x&&rx<=(next_x+70)&&ry>=next_y&&ry<=(next_y+40)){ //condition for going to next level(game field)
                rx=750; ry=500; //initialing value of coordinate of radish
                dx=0; dy=0; //initialing value of coordinate of donkey
                energy=initial_energy; //initialing the value of energy
                dif=dif-dif_decrement;//game difficulty controller //if dif decreases difficulty increases
                //after every level the game is getting hard
                window_controller=1; //going to field
            }
        }

        iSetColor(255,255,255);
        iRectangle(20,640,140,40);//main menu dialog box specification
        iSetColor(255,255,255);
        iText(30,650,"Main Menu",GLUT_BITMAP_TIMES_ROMAN_24);//the main menu
        if(rx>=20&&rx<=(20+140)&&ry>=640&&ry<=(640+40)){ //condition for going to main menu
            dif=dif-dif_decrement;//game difficulty controller //if dif decreases difficulty increases
            //after every level the game is getting hard
            if(level==5) level=0;//initialing the level variable after the game complete
            window_controller=0; // going to main menu
        }
    }
    else if(window_controller==4){//radish remaining window
        iClear();
        //displaying the background of game_field
        if(level==0) iShowBMP(0,0,"images//level1.bmp");
        else if(level==1) iShowBMP(0,0,"images//level2.bmp");
        else if(level==2) iShowBMP(0,0,"images//level3.bmp");
        else if(level==3) iShowBMP(0,0,"images//level4.bmp");
        else if(level==4) iShowBMP(0,0,"images//level5.bmp");

        iShowBMP2(100,40,"images//eating_radish.bmp",0);//displaying a donkey which is eating a radish

        iSetColor(255,255,255); iText(190,650,"Scores: ",GLUT_BITMAP_TIMES_ROMAN_24);//displaying the word "Scores: "
        iSetColor(255,255,255); iText(265,650,po,GLUT_BITMAP_TIMES_ROMAN_24);//displaying the value of Scores variable

        iSetColor(255,255,255);
        iRectangle(20,640,140,40);//main menu dialog box specification
        iSetColor(255,255,255);
        iText(30,650,"Main Menu",GLUT_BITMAP_TIMES_ROMAN_24);//the main menu
        if(rx>=20&&rx<=(20+140)&&ry>=640&&ry<=(640+40)){ //condition for going to main menu
            window_controller=0; // going to main menu
        }

        if(radish_remaning==2){//showing dialog when the number if remaining radish is 2
            iSetColor(255,255,255);
            iText(590,450,"Donkey have got 1 radish",GLUT_BITMAP_TIMES_ROMAN_24);//writing dialog
            iSetColor(255,255,255);
            iText(620,410,"Radish remaining 2",GLUT_BITMAP_TIMES_ROMAN_24);//writing dialog

            iSetColor(255,255,255);
            iRectangle(start_again_x-10,start_again_y-10,130,40);//start again dialog box specification
            iSetColor(255,255,255);
            iText(start_again_x,start_again_y,"Start Again",GLUT_BITMAP_TIMES_ROMAN_24);//writing start again
            if(rx>=(start_again_x-10)&&rx<=(start_again_x+120)&&ry>=(start_again_y-10)&&ry<=(start_again_y+30)){ //going to game field again after losing a radish
                rx=750; ry=500; //initialing value of coordinate of radish t
                dx=0; dy=0; //initialing value of coordinate of donkey
                energy=initial_energy; //initialing the value of energy
                window_controller=1; //going to field
            }
        }
        else if(radish_remaning==1){
            iSetColor(255,255,255);
            iText(590,450,"Donkey have got 2 radish",GLUT_BITMAP_TIMES_ROMAN_24);//writing dialog
            iSetColor(255,255,255);
            iText(620,410,"Radish remaining 1",GLUT_BITMAP_TIMES_ROMAN_24);//writing dialog

            iSetColor(255,255,255);
            iRectangle(start_again_x-10,start_again_y-10,130,40);//start again dialog box specification
            iSetColor(255,255,255);
            iText(start_again_x,start_again_y,"Start Again",GLUT_BITMAP_TIMES_ROMAN_24);//writing start again
            if(rx>=(start_again_x-10)&&rx<=(start_again_x+120)&&ry>=(start_again_y-10)&&ry<=(start_again_y+30)){ //condition for going to game field again after losing a radish
                rx=750; ry=500; //initialing value of coordinate of radish t
                dx=0; dy=0; //initialing value of coordinate of donkey
                energy=initial_energy; //initialing the value of energy
                window_controller=1; //going to field
            }
        }
    }
    else if(window_controller==5){//difficulty window
        iClear();
        iShowBMP(0,0,"images//level3.bmp");//showing the background of main_menu

        iSetColor(255,255,255);
        iRectangle(20,640,140,40);//main menu dialog box specification
        iSetColor(255,255,255);
        iText(30,650,"Main Menu",GLUT_BITMAP_TIMES_ROMAN_24);//the main menu
        if(rx>=20&&rx<=(20+140)&&ry>=640&&ry<=(640+40)){//going to main window
            window_controller=0;
        }

        iSetColor(255,255,255);
        iText(590,350,"Select Difficulty?",GLUT_BITMAP_TIMES_ROMAN_24);//writing select difficulty

        iSetColor(255,255,255);
        iRectangle(easy_x,easy_y,70,40);//easy dialog box
        iSetColor(255,255,255);
        iText(easy_x+10,easy_y+10,"Easy",GLUT_BITMAP_TIMES_ROMAN_24);//writing easy
        if(rx>=easy_x&&rx<=(easy_x+70)&&ry>=easy_y&&ry<=(easy_y+40)){//selecting easy
            rx=750; ry=500; //initialing value of coordinate of radish
            dx=0; dy=0; //initialing value of coordinate of donkey
            energy=initial_energy; //initialing the value of energy
            dif=dif_initial_value_easy;//game difficulty controller //if dif decreases difficulty increases
            level=0;//initialing level variable
            radish_remaning=3;//initialing the number of remaining radish
            Scores=0;//initialing point 0
            itoa(Scores,po,10);//showing "Scores: 0" text in iText() function
            window_controller=1;//going to game field
        }

        iSetColor(255,255,255);
        iRectangle(medium_x,medium_y,105,40);//medium dialog box
        iSetColor(255,255,255);
        iText(medium_x+10,medium_y+10,"Medium",GLUT_BITMAP_TIMES_ROMAN_24);//writing medium
        if(rx>=medium_x&&rx<=(medium_x+105)&&ry>=medium_y&&ry<=(medium_y+40)){//selecting medium
            rx=750; ry=500; //initialing value of coordinate of radish
            dx=0; dy=0; //initialing value of coordinate of donkey
            energy=initial_energy; //initialing the value of energy
            dif=dif_initial_value_medium;//game difficulty controller //if dif decreases difficulty increases
            level=0;//initialing level variable
            radish_remaning=3;//initialing the number of remaining radish
            Scores=0;//initialing point 0
            itoa(Scores,po,10);//showing "Scores: 0" text in iText() function
            window_controller=1;//going to game field
        }

        iSetColor(255,255,255);
        iRectangle(hard_x,hard_y,70,40);//hard dialog box
        iSetColor(255,255,255);
        iText(hard_x+10,hard_y+10,"Hard",GLUT_BITMAP_TIMES_ROMAN_24);//writing hard
        if(rx>=hard_x&&rx<=(hard_x+70)&&ry>=hard_y&&ry<=(hard_y+40)){//selecting hard
            rx=750; ry=500; //initialing value of coordinate of radish
            dx=0; dy=0; //initialing value of coordinate of donkey
            energy=initial_energy; //initialing the value of energy
            dif=dif_initial_value_hard;//game difficulty controller //if dif decreases difficulty increases
            level=0;//initialing level variable
            radish_remaning=3;//initialing the number of remaining radish
            Scores=0;//initialing point 0
            itoa(Scores,po,10);//showing "Scores: 0" text in iText() function
            window_controller=1;//going to game field
        }
    }
    else if(window_controller==6){//help window
         iClear();
         iShowBMP(0,0,"images//help.bmp");//showing the background of main_menu

        iSetColor(255,255,255);
        iRectangle(20,640,140,40);//main menu dialog box specification
        iSetColor(255,255,255);
        iText(30,650,"Main Menu",GLUT_BITMAP_TIMES_ROMAN_24);//writing main menu
        if(rx>=20&&rx<=(20+140)&&ry>=640&&ry<=(640+40)){//going to main menu
            window_controller=0;
        }
    }
    else if(window_controller==7){//control window
        iClear();
        iShowBMP(0,0,"images//control.bmp");

        iSetColor(255,255,255);
        iRectangle(20,640,70,40);//main menu dialog box specification
        iSetColor(255,255,255);
        iText(30,650,"Back",GLUT_BITMAP_TIMES_ROMAN_24);//writing back
        if(rx>=20&&rx<=(20+140)&&ry>=640&&ry<=(640+40)){//going to setting window
            rx=0; ry=0;//initialing rx and ry to avoid error
            window_controller=8;
        }
    }
    else if(window_controller==8){//setting window
        iClear();
        iShowBMP(0,0,"images//level2.bmp");

        iSetColor(255,255,255);
        iRectangle(20,640,140,40);//main menu dialog box specification
        iSetColor(255,255,255);
        iText(30,650,"Main Menu",GLUT_BITMAP_TIMES_ROMAN_24);//writing main menu
        if(rx>=20&&rx<=(20+140)&&ry>=640&&ry<=(640+40)){//going to main menu window
            window_controller=0;
        }

        iSetColor(255,255,255);
        iRectangle(music_x,music_y,120,40);//music box specification
        iSetColor(255,255,255);
        if(music==true) iText(music_x+10,music_y+10,"Music On",GLUT_BITMAP_TIMES_ROMAN_24);
        //this means music is on
        else if(music==false) iText(music_x+10,music_y+10,"Music Off",GLUT_BITMAP_TIMES_ROMAN_24);
        //this means music is off

        iSetColor(255,255,255);
        iRectangle(control_x,control_y,105,40);//control dialog box
        iSetColor(255,255,255);
        iText(control_x+10,control_y+10,"Controls",GLUT_BITMAP_TIMES_ROMAN_24);//writing dialog
        if(rx>=control_x&&rx<=(control_x+105)&&ry>=control_y&&ry<=(control_y+40)){//going to control window
            window_controller=7;
        }
    }
    else if(window_controller==9){//credits window
        iClear();
        iShowBMP(0,0,"images//credits.bmp");

        iSetColor(255,255,255);
        iRectangle(20,640,140,40);//main menu dialog box specification
        iSetColor(255,255,255);
        iText(30,650,"Main Menu",GLUT_BITMAP_TIMES_ROMAN_24);//writing main menu
        if(rx>=20&&rx<=(20+140)&&ry>=640&&ry<=(640+40)){//going to main menu
            window_controller=0;
        }
    }
    else if(window_controller==10){//high scores window
            iClear();
            iShowBMP(0,0,"images//level4.bmp");

        if(read_high_score_switch==true){
            FILE *hs;
            hs=fopen("files//high_score.txt","r");
            fscanf(hs,"%d",&high_score);
            fclose(hs);
            FILE *cp;
            cp=fopen("files//last_player.txt","r");
            fscanf(cp,"%d %s",&last_player_score_1,last_player_name_1);
            fscanf(cp,"%d %s",&last_player_score_2,last_player_name_2);
            fscanf(cp,"%d %s",&last_player_score_3,last_player_name_3);
            fscanf(cp,"%d %s",&last_player_score_4,last_player_name_4);
            fscanf(cp,"%d %s",&last_player_score_5,last_player_name_5);
            fclose(cp);
            read_high_score_switch=false;
        }
        //printing best score in game console
        itoa(high_score,po_hs,10);
        iSetColor(255,255,255); iText(320+300,400,"Best Score: ",GLUT_BITMAP_TIMES_ROMAN_24);//displaying the word "Scores: "
        iSetColor(255,255,255); iText(440+300,400,po_hs,GLUT_BITMAP_TIMES_ROMAN_24);//displaying the value of Scores variable
        iSetColor(255,255,255); iText(590,350,"Names",GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(255,255,255); iText(730,350,"Scores",GLUT_BITMAP_TIMES_ROMAN_24);
        //printing saved players info
        itoa(last_player_score_1,po_hs,10);
        iSetColor(255,255,255); iText(600,320,last_player_name_1,GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(255,255,255); iText(750,320,po_hs,GLUT_BITMAP_TIMES_ROMAN_24);
        itoa(last_player_score_2,po_hs,10);
        iSetColor(255,255,255); iText(600,290,last_player_name_2,GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(255,255,255); iText(750,290,po_hs,GLUT_BITMAP_TIMES_ROMAN_24);
        itoa(last_player_score_3,po_hs,10);
        iSetColor(255,255,255); iText(600,260,last_player_name_3,GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(255,255,255); iText(750,260,po_hs,GLUT_BITMAP_TIMES_ROMAN_24);
        itoa(last_player_score_4,po_hs,10);
        iSetColor(255,255,255); iText(600,230,last_player_name_4,GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(255,255,255); iText(750,230,po_hs,GLUT_BITMAP_TIMES_ROMAN_24);
        itoa(last_player_score_5,po_hs,10);
        iSetColor(255,255,255); iText(600,200,last_player_name_5,GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(255,255,255); iText(750,200,po_hs,GLUT_BITMAP_TIMES_ROMAN_24);

        iSetColor(255,255,255);
        iRectangle(20,640,140,40);//main menu dialog box specification
        iSetColor(255,255,255);
        iText(30,650,"Main Menu",GLUT_BITMAP_TIMES_ROMAN_24);//the main menu
        if(rx>=20&&rx<=(20+140)&&ry>=640&&ry<=(640+40)){
            read_high_score_switch=true;
            window_controller=0;
        }
    }
    else if(window_controller==11){//taking input of player name
        iClear();
        iShowBMP(0,0,"images//level5.bmp");

        iSetColor(255,255,255);
        iText(590,280,"Type your name:",GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(255,255,255);
        iText(760,280,player_name,GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(255,255,255);
        iText(530,50,"Press Enter after typing name",GLUT_BITMAP_TIMES_ROMAN_24);

        iSetColor(255,255,255);
        iRectangle(20,640,140,40);//main menu dialog box specification
        iSetColor(255,255,255);
        iText(30,650,"Main Menu",GLUT_BITMAP_TIMES_ROMAN_24);//writing main menu
        if(rx>=20&&rx<=(20+140)&&ry>=640&&ry<=(640+40)){//going to main menu window
            window_controller=0;
        }
    }
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    //printf("x = %d, y= %d\n",mx,my);
    //place your codes here
    //dragging option for game testing
     //rx=mx;
     //ry=my;
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
        //printf("x = %d, y= %d\n",mx,my);
        rx=mx; // taking input of the coordinate of radish(rx)
        ry=my; // taking input of the coordinate of radish(ry)
        //taking input of rx, ry also represent the coordinate of mouse point outside the iMouse function
        if(gaming==true){
            if(window_controller==1){//when player is in the game field
                Scores++;//Scores are increasing after every click
                itoa(Scores,po,10);//this function convert the Scores variable(integer) to a string to be valid for iText() function
            }
            point_ar[level]++;//this value calculate scores for a certain incomplete level to subtract the value from total scores for clicking on quit
        }
        if((music==true)&&(window_controller==8)&&(rx>=music_x&&rx<=(music_x+120)&&ry>=music_y&&ry<=(music_y+40))){
            //music true means music is playing
            //condition to off music
            music=false;//making music false
            PlaySound(0,0,0);//playing null music
        }
        else if((music==false)&&(window_controller==8)&&(rx>=music_x&&rx<=(music_x+120)&&ry>=music_y&&ry<=(music_y+40))){
            //music false means music is not playing
            //condition to on music
            music=true;//making music true
            PlaySound("gamemusic.wav",NULL,SND_LOOP|SND_ASYNC);//playing music
        }
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
         rx=mx; // taking input of the coordinate of radish(rx)
         ry=my; // taking input of the coordinate of radish(ry)
         if(gaming==true){//gaming true means the game is running that means it is not paused
            if(window_controller==1){//when player is in the game field
                Scores++;//Scores are increasing after every click
                itoa(Scores,po,10);//this function convert the Scores variable(integer) to a string to be valid for iText() function
            }
            point_ar[level]++;//this value calculate scores for a certain incomplete level to subtract the value from total scores for clicking on quit
        }
    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    // using this you can change color
    //place your codes for other keys here
    if(window_controller==1){
        if(key=='p'&&window_controller==1) gaming==true;//making the gaming variable true
        else if(key=='r'&&window_controller==1) gaming==false;//making the gaming variable false
        if(gaming==true){//this will pause the game
            iPauseTimer(0);
            iPauseTimer(1);
            iPauseTimer(2);
            iPauseTimer(3);
            gaming=false;//making gaming variable false
        }
        else if(gaming==false){//this will resume the game
            iResumeTimer(0);
            iResumeTimer(1);
            iResumeTimer(2);
            iResumeTimer(3);
            gaming=true;//making gaming variable true
        }
    }

    else if(window_controller==11){//taking input from game console
            if(key=='\x0D') window_controller=5;//it will execute after press enter
            else{
                if(key!='\b'){
                player_name[player_name_index]=key;
                player_name_index++;
                player_name[player_name_index]='\0';
            }
            else{
                if(player_name_index<=0) player_name_index=0;
                else player_name_index--;
                player_name[player_name_index]='\0';
            }
        }
    }
}
/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_END)
    {
        exit(0);
    }
    //place your codes for other keys here
}
void movement()
{
    //this function is the core function for the movement of the donkey
    //in this section dx,dy always try to be equal to rx,ry
    dx=dx+(rx-dx)/dif;
    dy=dy+(ry-dy)/dif;
}
void running()
{
    //this function can create a little vibe of animation
    run++;//run variable is becoming odd and even number correspondingly to animate
    if(run>100) run=0; //reseting run variable
}
void energy_decreasing()
{
        energy=energy-1;//decreasing energy
}
void rotation_of_radish()
{//this function is controlling the value of rot_rad variable
    rot_rad++;//increasing the rot_rad variable
    if(rot_rad>4) rot_rad=1;//reseting the rot_rad variable
}
int main()
{
    //place your own initialization codes here.
    FILE *f;
    f=fopen("files//save_game.txt","r");
    fscanf(f,"%d",&level);//reading the value of level
    //it means the program can understand if the game was saved of not
    fclose(f);
     if(level==0){//if the game was saved (if the game was saved level will not equal to 0) by a player the program won't ask for a new name
        read_name_switch=false;//switching off so that it can,t read the name of previous player from save game file
    }
    PlaySound("gamemusic.wav",NULL,SND_LOOP|SND_ASYNC);//playing sound after start playing the game
    iSetTimer(dif_timer,movement);//calling movement function periodically
    iSetTimer(run_timer,running); //running positions (run_timer=4*dif) //this timer control the speed of animation
    iSetTimer(100,energy_decreasing);//timer for energy decreasing
    iSetTimer(250,rotation_of_radish);//this timer is calling rotation_of_radish function periodically to change the value of rot_rad
    iInitialize(width,height,"The Magical Radish");//making the game console and the declaration of the name of game
    return 0;
}
