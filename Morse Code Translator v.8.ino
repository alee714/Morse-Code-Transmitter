int digit = 1000; //index of the matrix
int letter = 0; //what the letter is
int letterd = 0;
int nLoop = 0; // number of empty loops
int pLoop = 0;  // number of filled loops
const int signal = 2;

int signalState = 0;
char output = 'y'; //send to output


/*  Loop Description: Check for button signal, check with nLoop to determine if it is a dot or a dash. 
    Check if end of word or new letter. Increment the nLoop and do things if new letter or end of word.
*/

void setup() 
  {
    Serial.begin(9600);
    pinMode(signal, INPUT);
    Serial.println("Bootup");
    delay(2000);
  }

void loop() {
  while(digitalRead(signal) == LOW){}
  while(1) //character loop, defines character based on the signal.
  {
    signalState = digitalRead(signal);
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
          break;
        }
        else if(nLoop == 7) //new word
        {
          Serial.println("space");
        }
        //checking if end of word or new letter, changing nLoop
      }
    delay(2000);
  }

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
        output = 'a';
        break;

      case 3110: //d
        output = 'd';
        break;

      case 3130: //k
        output = 'a';
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
    Serial.print("Letter is: ");
    Serial.println(letter);
    Serial.print("Output is: ");
    Serial.println(output);
    letter = 0;
    pLoop = 0;
    delay(2000);
}

int pwr (int base, int exp)
{
  int i;
  for(i = exp; i > 1; i--)
  {
    base = base * 10;
  }
  return base;
}
