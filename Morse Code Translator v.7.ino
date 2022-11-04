int digit = 0; //index of the matrix
String letter ; //what the letter is
int nLoop = 0; // number of empty loops
int pLoop = 0;  // number of filled loops
int signal = 7;

const int buffer = 50;
char buf[buffer];

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
  while(digitalRead(signal) == 0){}
  while(1) //character loop, defines character based on the signal.
  {
      if(digitalRead(signal) == 1) //beep boop, define dot or dash
      {
        pLoop++;
        nLoop = 0;
        Serial.println("pressed");

        if(pLoop == 1)
        {
          letter[digit] = '1'; // dot
        }
        if(pLoop == 3)
        {
          letter[digit] = '3'; //dash
        }
        //determine if dot or dash, update letter[] accordingly using nLoop
      }

      else //no beep boop, end of digit or character
      {
        Serial.println("Not pressed");
        nLoop++;
        pLoop = 0;
        
        if(nLoop == 1) //new digit
        { 
          digit++;
        }
        else
        { 
          digit = 0;
          break;
        }
        //checking if end of word or new letter, changing nLoop
      }
    delay(2000);
  }

    switch(letter.toInt())
    {
      case 1: //e
        output = 'e';
        break;

      case 3: //t
        output = 't';
        break;

      case 13: //a
        output = 'a';
        break;

      default: //what
        output = '?';
        break;
    }
    Serial.print("Letter is: " + letter);
    Serial.println("Output is: ");
    letter = "\0\0\0\0";
    delay(2000);
}
