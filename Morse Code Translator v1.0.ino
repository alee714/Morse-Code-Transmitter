#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4); 

int digit = 3; //index of the matrix
int letter = 0; //what the letter is
int nLoop = 0; // number of empty loops
int pLoop = 0;  // number of filled loops
int x_pos = 0;
int y_pos = 0;
int delay_speed = 2000;
const int signal = 2;
const int menu = 8;

int signalState = 0;
char output = 'y'; //send to output


/*  Loop Description: Check for button signal, check with nLoop to determine if it is a dot or a dash. 
    Check if end of word or new letter. Increment the nLoop and do things if new letter or end of word.
*/

void setup() 
  {
    //Serial.begin(9600);
    pinMode(signal, INPUT);
    //Serial.println("Bootup");
    delay(2000);
    lcd.init();
    lcd.backlight();
    //while(digitalRead(signal) == LOW){}
  }

void loop() 
{
  //Serial.println("menu screen"); //display menu stuff
  while(digitalRead(signal) == LOW)
  {
    lcd.setCursor ( 0, 0 );            // go to the top left corner
    lcd.print("    INSERT NAME!    "); // write this string on the top row
    lcd.setCursor ( 0, 1 );            // go to the 2nd row
    lcd.print(" GREEN=GO,RED=RESET"); // pad string with spaces for centering
    lcd.setCursor ( 0, 2 );            // go to the third row
    lcd.print("CURRENT SPEED: FAST!"); // pad with spaces for centering
    lcd.setCursor ( 0, 3 );            // go to the fourth row
    lcd.print("  MADE BY USF IEEE");
  }
  lcd.clear();
  lcd.cursor();
  lcd.blink();
  //printing loop
  while(digitalRead(menu) == LOW)
  {
      while(digitalRead(menu) == LOW) //program loop
      {
        signalState = digitalRead(signal);
        if(nLoop == 3) //printing word
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
          }
        if(signalState == HIGH) //beep boop, define dot or dash
        {
          pLoop++;
          nLoop = 0;
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
            Serial.print("space");
            moveCursor();
            nLoop = 0;
            letter = 0;
          }
          //checking if end of word or new letter, changing nLoop
        }
      delay(2000);
      }
  }
  delay(2000);
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
    y_pos++;
  }
  lcd.setCursor(x_pos, y_pos);
}
