#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4); 

int digit = 3; //index of the letter variable (L-R)
int letter = 0; //dot(1) dash(3) representation of a morse code sequence

int nLoop = 0; // unpressed button signal counter
int pLoop = 0;  // pressed button signal counter

int x_pos = 0; //Cursor x coordinate
int y_pos = 0; //Cursor y coordinate

int delay_speed = 2000; //variable to adjust signal counter's speed

const int signal = 2;
const int reset = 8;

int signalState = LOW;
char output; //send to output

int dblSpaceFlag = 0;


/*  Loop Description: Check for button signal, check with nLoop to determine if it is a dot or a dash. 
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
    delay(2000);
    ////while(digitalRead(signal) == LOW){}
  }

void loop() 
{
  Serial.println("menu screen"); //display menu stuff
  lcd.home();            // go to the top left corner
  int x_pos = 0; //Reset x coordinate tracker
  int y_pos = 0; //Reset y coordinate tracker
  int digit = 3; //Reset 
  int letter = 0; //Reset
  int nLoop = 0; //Reset
  int pLoop = 0;  //Reset


  lcd.print("Translation Station!"); // write this string on the top row
  lcd.setCursor ( 0, 1 );            // go to the 2nd row
  lcd.print(" GREEN=GO,RED=RESET "); // pad string with spaces for centering
  lcd.setCursor ( 0, 2 );            // go to the third row
  lcd.print("CURRENT SPEED: FAST!"); // pad with spaces for centering
  lcd.setCursor ( 0, 3 );            // go to the fourth row
  lcd.print("  MADE BY USF IEEE  ");
  lcd.noCursor();
  lcd.noBlink();

  while(digitalRead(signal) == HIGH) {} //wait on reset screen until green button is pressed
  
  lcd.clear();
  lcd.cursor();
  lcd.blink();
  
  //printing loop
  while(digitalRead(reset) == LOW)
  {
    
    while(digitalRead(reset) == LOW) //program loop
    {
        //signalState = digitalRead(signal); //do we need to run this line at the start of each loop?

        if ((nLoop == 3) && (dblSpaceFlag == 0)) //printing word
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
            //print letter, change cursor placement, 
            lcd.print(output);
            moveCursor();
            letter = 0;
            //digit = 3; //new
          }
        if(digitalRead(signal) == LOW) //beep boop, define dot or dash
        {
          pLoop++;
          nLoop = 0;
          dblSpaceFlag = 0;
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
          
          if(nLoop == 1) //new digit
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
            dblSpaceFlag = 1;
          }
          //checking if end of word or new letter, changing nLoop
        }
        delay(delay_speed);
    }
  }
  delay(delay_speed);
}

int pwr (int base, int exp)
{
  int i;
  if(exp == 0)
  {
    return 1;
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
  lcd.setCursor(x_pos, y_pos);
}
