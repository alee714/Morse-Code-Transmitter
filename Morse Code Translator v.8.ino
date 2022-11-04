int digit = 3; //index of the matrix
int letter = 0; //what the letter is
int nLoop = 0; // number of empty loops
int pLoop = 0;  // number of filled loops
int signal = 7;


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
          letter = letter + 1 * (10^digit); // dot
        }
        if(pLoop == 3)
        {
          letter = letter + 2 * (10^digit); //dash
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
          digit--;
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

    switch(letter)
    {
      case 1000: //e
        output = 'e';
        break;

      case 3000: //t
        output = 't';
        break;

      case 1300: //a
        output = 'a';
        break;

      default: //what
        output = '?';
        break;
    }
    Serial.print("Letter is: " + letter);
    Serial.print(output);
    Serial.println("Output is: " + output);
    letter = 0;
    delay(2000);
}
