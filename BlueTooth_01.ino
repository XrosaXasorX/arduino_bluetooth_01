///////////////////////////////////////////////////////////////////
//
// BoF :: "BlueTooth_01.ino"
//
// 2014/09/21 - 23:00 GMT+1
//
// xsarox @ synkhro.com
//
///////////////////////////////////////////////////////////////////

int  led = 13;
char msg[ 64 ];

int msg_pos;  // Position within whole-length message.

const int g_tK = 150;  // K = milliseconds multiply-factor (change it as you need).

int g_tLenDot     ;  // time: lenght of a 'dot'
int g_tLenDash    ;  // time: lenght of a 'dash'
int g_tSpcParts   ;  // time: space between parts of the same letter
int g_tSpcLetters ;  // time: space between letters of the same word
int g_tSpcWords   ;  // time: space between words

bool g_bAcked ;
int g_bLoop = 0;

///////////////////////////////////////////////////////////////////

void setup()
  {
  g_bAcked = true;  
  
  // Init serial port.
  Serial.begin( 9600 );
  Serial.println( "Type an AT command!" );

  // Init output pins.
  pinMode(  2, OUTPUT );
  pinMode(  8, OUTPUT );
  pinMode(  9, OUTPUT );     
  pinMode( 10, OUTPUT );     
  pinMode( 11, OUTPUT );     
  pinMode( 13, OUTPUT );
     
  }//setup
///////////////////////////////////////////////////////////////////

void loop() 
  {
  int l_iSounder;

  // Read a character from serial input.
  char c = Serial.read();
 
  // Turn on LED.
  if( c == 'H' )
    {
    digitalWrite( 2, HIGH );
    delay( 1000 );
    }
  // Turn off LED.
  if( c == 'L' )
    {
    digitalWrite( 2, LOW );
    delay( 1000 );
    }
  // Stop looped sound.
  if( c == 'A' )
    {
    g_bAcked = true;
    }
  // Start looped sound.
  if( c == 'N' )
    {
    g_bAcked = false;
    }
  // Play a rising tone.
  if( c == 'P' )
    {
    if( g_bLoop == 0 )
      g_bLoop = 1 ;
    else
      g_bLoop = 0 ;
    }
  
  // Ack.
  if( g_bAcked == false )
    {
    for( l_iSounder = 1000; l_iSounder <= 2000; l_iSounder+=1000 )
      {    
      digitalWrite(  2, HIGH );
      digitalWrite( 13, HIGH );
      tone( 8, 1000 );
      delay(100);
      digitalWrite(  2, LOW );
      digitalWrite( 13, LOW );
      tone( 8, 4000 );
      delay(100);
      tone( 8, 0 );                           
      }//for
    }//if_ack_yes
  if( g_bAcked == true )
    {
    // NOP
    }

  // Looping sound.
  if( g_bLoop )
    {
    if( g_bLoop < 4000 )
      g_bLoop+=10;
    else
      g_bLoop = 0;
    if( g_bLoop < 2000 )
       tone( 8, g_bLoop );
    else
       tone( 8, 4000 - g_bLoop );
    delay( 5 );
    }

  }//loop
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// EoF :: "BlueTooth_01.ino"
///////////////////////////////////////////////////////////////////
