#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4); 

//Constants
const int signal = 2; //Input pin
const int reset = 8; //Reset pin
int delay_speed = 1500; //variable to adjust signal counter's speed

//Variables that change during the program's operation
int signalState = LOW;
int cursorState;

int digit; //index of the letter variable (L-R)
int letter; //dot(1) dash(3) representation of a morse code sequence
char output; //Letter value as a character
int spaceFlag; //Flag for if the previous character was a space

int nLoop; // unpressed button signal counter
int pLoop;  // pressed button signal counter

int x_pos; //Cursor x coordinate
int y_pos; //Cursor y coordinate



/*  
    Loop Description: Check for button signal, check with nLoop to determine if it is a dot or a dash. 
    Check if end of word or new letter. Increment the nLoop and do things if new letter or end of word.
*/

void setup() 
  {
    Serial.begin(9600);
    pinMode(signal, INPUT);
    pinMode(reset, INPUT);
    Serial.println("Bootup");
   
    lcd.init();
    lcd.backlight();
    //delay(2000);
    ////while(digitalRead(signal) == LOW){}
  }

void loop() 
{
  Serial.println("menu screen"); //display menu stuff
  lcd.home();            // go to the top left corner
  x_pos = 0; //Reset x coordinate tracker
  y_pos = 0; //Reset y coordinate tracker
  digit = 3; //Reset 
  letter = 0; //Reset
  nLoop = 0; //Reset
  pLoop = 0;  //Reset
  spaceFlag = 1; //Reset to 1 (so that a lack of signal to start doesn't output "?")
  cursorState = 1; //Reset


  lcd.print("TRANSLATION STATION!"); // write this string on the top row
  lcd.setCursor ( 0, 1 );            // go to the 2nd row
  lcd.print(" BLUE=Go, RED=Reset "); // pad string with spaces for centering
  lcd.setCursor ( 0, 2 );            // go to the third row
  lcd.print("Current Speed:  SLOW"); // pad with spaces for centering
  lcd.setCursor ( 0, 3 );            // go to the fourth row
  lcd.print("  Made By USF IEEE  ");
  lcd.noCursor();
//  lcd.noBlink();

  while(digitalRead(signal) == HIGH) {} //wait on reset screen until green button is pressed
  lcd.clear();          //countdown begins
  lcd.setCursor (8,1);  //cursor to the middle of the screen
  lcd.print("4...");
  lcd.setCursor (8,1);
  delay(delay_speed);
  lcd.print("3...");
  lcd.setCursor (8,1);
  delay(delay_speed);
  lcd.print("2...");
  lcd.setCursor (8,1);
  delay(delay_speed);
  lcd.print("1...");
  lcd.setCursor (8,1);
  delay(delay_speed);

  lcd.clear();
  lcd.setCursor(x_pos, y_pos);

//  lcd.cursor();
//  lcd.blink();
  //lcd.autoscroll();
  
  //printing loop
  while(digitalRead(reset) == HIGH)
  {
    while(digitalRead(reset) == HIGH) //program loop
    {
        if ((nLoop == 3) && (spaceFlag == 0)) //printing word
          {
            switch(letter) //choose letter
            {
              case 1000: //e
                output = 'e';
                break;

              case 3000: //t
                output = 't';
                break;

              case 1100: //i
                output = 'i';
                break;

              case 1300: //a
                output = 'a';
                break;

              case 3100: //n
                output = 'n';
                break;

              case 3300: //m
                output = 'm';
                break;

              case 1110: //s
                output = 's';
                break;

              case 1130: //u
                output = 'u';
                break;

              case 1310: //r
                output = 'r';
                break;

              case 1330: //w
                output = 'w';
                break;

              case 3110: //d
                output = 'd';
                break;

              case 3130: //k
                output = 'k';
                break;

              case 3310: //g
                output = 'g';
                break;

              case 3330: //o
                output = 'o';
                break;

              case 1111: //h
                output = 'h';
                break;

              case 1113: //v
                output = 'v';
                break;

              case 1131: //f
                output = 'f';
                break;

              case 1311: //l
                output = 'l';
                break;

              case 1331: //p
                output = 'p';
                break;

              case 1333: //j
                output = 'j';
                break;

              case 3111: //b
                output = 'b';
                break;

              case 3113: //x
                output = 'x';
                break;
              
              case 3131: //c
                output = 'c';
                break;

              case 3133: //y
                output = 'y';
                break;

              case 3311: //z
                output = 'z';
                break;

              case 3313: //q
                output = 'q';
                break;

              default: //what
                output = '?';
                break;
            }
            //print letter, change cursor placement
            lcd.print(output);
            moveCursor();
            letter = 0;
          }

        if(digitalRead(signal) == LOW) //beep boop, define dot or dash
        {
          pLoop++;
          nLoop = 0;
          spaceFlag = 0;
          Serial.println("pressed");

          if(pLoop == 1)
          {
            
            letter = letter + pwr(10,digit); // dot
          }
          if(pLoop == 3)
          {
            letter = letter + 2 * pwr(10,digit); //dash
            break;
          }
          
          //determine if dot or dash, update letter[] accordingly using nLoop
          Serial.println(letter);
        }

        else //no beep boop, end of digit or character
        {
          Serial.println("Not pressed");
          nLoop++;
          pLoop = 0;
          
          if((nLoop == 1) && (spaceFlag == 0)) //new digit
          { 
            digit--;
          }
          else if(nLoop == 3) //new letter
          { 
            digit = 3;
          }
          else if(nLoop == 7) //new word
          {
            Serial.println("space");
            moveCursor();            
            nLoop = 0;
            letter = 0;
            spaceFlag = 1;
          }
          //checking if end of word or new letter, changing nLoop
        }
        
        //Input timer with cursor
        if (cursorState == 1)
        {
          lcd.cursor();
        }
        else 
        {
          lcd.noCursor();          
        }        
        cursorState = (cursorState ^ 1);
        delay(delay_speed);
    }
  }
//  delay(delay_speed);
}

int pwr (int base, int exp)
{
  int i;
  if(exp == 0)
  {
    return 1;
  }
  if(exp < 0) //new
  {
    return 0;
  }  
  for(i = exp; i > 1; i--)
  {
    base = base * 10;
  }
  return base;
}

void moveCursor()
{
  x_pos++;
  if(x_pos > 19)
  {
    x_pos = 0;
    /*
    if (y_pos == 3)
    {
      //shift each row up one (cutting off top)
    }
    else
    {
    */
    y_pos++;
    //}
  }
  cursorState = 1; //So that the next space always starts with a visible movement of the cursor
  lcd.setCursor(x_pos, y_pos);
}
