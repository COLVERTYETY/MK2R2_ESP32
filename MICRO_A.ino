#include <Arduino.h>

String ID = "A";

String x_str;
String message_retour;

String FR_received;
String MR_received;
String BR_received;
String FL_received;
String ML_received;
String BL_received;

String bf0;
String bf1;
String bf2;
String bf3;
String bf4;
String bf5;
String bf6;

int ind0;
int ind1;
int ind2;
int ind3;
int ind4;
int ind5;
int ind6;
int ind7;
int ind8;
int ind9;
int ind10;
int ind11;
int ind12;

int FR_fwd_speed;
int MR_fwd_speed;
int BR_fwd_speed;

int FL_fwd_speed;
int ML_fwd_speed;
int BL_fwd_speed;

// Motor 1
int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14; 

// Motor 2
int motor2Pin1 = 25; 
int motor2Pin2 = 33; 
int enable2Pin = 32;

// Motor 3
int motor3Pin1 = 16; 
int motor3Pin2 = 4; 
int enable3Pin = 17;

// Motor 4
int motor4Pin1 = 18; 
int motor4Pin2 = 19; 
int enable4Pin = 5;

// Motor 5
int motor5Pin1 = 2; 
int motor5Pin2 = 15; 
int enable5Pin = 21;

// Motor 6
int motor6Pin1 = 13; 
int motor6Pin2 = 12; 
int enable6Pin = 23;


// Setting PWM properties
const int freq = 30000;

const int pwmChannel1 = 1;
const int pwmChannel2 = 2;
const int pwmChannel3 = 3;
const int pwmChannel4 = 4;
const int pwmChannel5 = 5;
const int pwmChannel6 = 6;

const int resolution = 8;
int dutyCycle = 200;


void setup(){

    Serial.begin(115200);
    Serial.setTimeout(10); 

    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(enable1Pin, OUTPUT);

    pinMode(motor2Pin1, OUTPUT);
    pinMode(motor2Pin2, OUTPUT);
    pinMode(enable2Pin, OUTPUT);

    pinMode(motor3Pin1, OUTPUT);
    pinMode(motor3Pin2, OUTPUT);
    pinMode(enable3Pin, OUTPUT);

    pinMode(motor4Pin1, OUTPUT);
    pinMode(motor4Pin2, OUTPUT);
    pinMode(enable4Pin, OUTPUT);

    pinMode(motor5Pin1, OUTPUT);
    pinMode(motor5Pin2, OUTPUT);
    pinMode(enable5Pin, OUTPUT);

    pinMode(motor6Pin1, OUTPUT);
    pinMode(motor6Pin2, OUTPUT);
    pinMode(enable6Pin, OUTPUT);

    // configure LED PWM functionalitites
    ledcSetup(pwmChannel1, freq, resolution);
    ledcSetup(pwmChannel2, freq, resolution);
    ledcSetup(pwmChannel3, freq, resolution);
    ledcSetup(pwmChannel4, freq, resolution);
    ledcSetup(pwmChannel5, freq, resolution);
    ledcSetup(pwmChannel6, freq, resolution);
    
    // attach the channel to the GPIO to be controlled
    ledcAttachPin(enable1Pin, pwmChannel1);
    ledcAttachPin(enable2Pin, pwmChannel2);
    ledcAttachPin(enable3Pin, pwmChannel3);
    ledcAttachPin(enable4Pin, pwmChannel4);
    ledcAttachPin(enable5Pin, pwmChannel5);
    ledcAttachPin(enable6Pin, pwmChannel6);
}

/*motor control*/
void go_advance(int speed){
    FR_fwd(speed);
    FL_fwd(speed); 
    MR_fwd(speed);
    ML_fwd(speed);
    BR_fwd(speed);
    BL_fwd(speed);
}
void go_back(int speed){
    FR_bck(speed);
    FL_bck(speed); 
    MR_bck(speed);
    ML_bck(speed);
    BR_bck(speed);
    BL_bck(speed);
}

void FR_fwd(int speed)  //front-right wheel forward turn
{
    digitalWrite(motor4Pin1,HIGH);
    digitalWrite(motor4Pin2,LOW); 
    ledcWrite(pwmChannel4, speed);
}
void FR_bck(int speed) // front-right wheel backward turn
{
    digitalWrite(motor4Pin1,LOW);
    digitalWrite(motor4Pin2,HIGH); 
    ledcWrite(pwmChannel4, speed);
}
void FL_fwd(int speed) // front-left wheel forward turn
{
    digitalWrite(motor1Pin1,HIGH);
    digitalWrite(motor1Pin2,LOW);
    ledcWrite(pwmChannel1, speed);
}
void FL_bck(int speed) // front-left wheel backward turn
{
    digitalWrite(motor1Pin1,LOW);
    digitalWrite(motor1Pin2,HIGH);
    ledcWrite(pwmChannel1, speed);
}

void MR_fwd(int speed)  //mid-right wheel forward turn
{
    digitalWrite(motor5Pin1, HIGH);
    digitalWrite(motor5Pin2,LOW); 
    ledcWrite(pwmChannel5, speed);
}
void MR_bck(int speed)  //mid-right wheel backward turn
{
    digitalWrite(motor5Pin1, LOW);
    digitalWrite(motor5Pin2,HIGH); 
    ledcWrite(pwmChannel5, speed);
}
void ML_fwd(int speed)  //mid-left wheel forward turn
{
    digitalWrite(motor2Pin1,HIGH);
    digitalWrite(motor2Pin2,LOW);
    ledcWrite(pwmChannel2, speed);
}
void ML_bck(int speed)    //mid-left wheel backward turn
{
    digitalWrite(motor2Pin1,LOW);
    digitalWrite(motor2Pin2,HIGH);
    ledcWrite(pwmChannel2, speed);
}
 
void BR_fwd(int speed)  //mid-right wheel forward turn
{
    digitalWrite(motor6Pin1, HIGH);
    digitalWrite(motor6Pin2,LOW); 
    ledcWrite(pwmChannel6, speed);
}
void BR_bck(int speed)  //mid-right wheel backward turn
{
    digitalWrite(motor6Pin1, LOW);
    digitalWrite(motor6Pin2,HIGH); 
    ledcWrite(pwmChannel6, speed);
}
void BL_fwd(int speed)  //mid-left wheel forward turn
{
    digitalWrite(motor3Pin1,HIGH);
    digitalWrite(motor3Pin2,LOW);
    ledcWrite(pwmChannel3, speed);
}
void BL_bck(int speed)    //mid-left wheel backward turn
{
    digitalWrite(motor3Pin1,LOW);
    digitalWrite(motor3Pin2,HIGH);
    ledcWrite(pwmChannel3, speed);
}
  
void stop_Stop()    //Stop
{
    ledcWrite(pwmChannel1, 0);
    ledcWrite(pwmChannel2, 0);
    ledcWrite(pwmChannel3, 0);
    ledcWrite(pwmChannel4, 0);
    ledcWrite(pwmChannel5, 0);
    ledcWrite(pwmChannel6, 0);
}


void loop() {

    if (Serial.available() > 0) 
    {    
        // read the incoming data:
        x_str             = Serial.readString();

        ind0              = x_str.indexOf('/');             //finds location of first ,
        bf0               = x_str.substring(0, ind0);       //captures first data String

        // PING COMMING
        if(bf0.toFloat() == 0)
        {
            message_retour = "0/" + ID + "\n";
            Serial.print(message_retour); 
        }

        // MOTOR COMMANDS
        if(bf0.toFloat() == 1)
        {   
            x_str = x_str + "\n";
            // Serial.print(x_str);

            ind1              = x_str.indexOf('/', ind0+1 );            //finds location of first ,
            bf1               = x_str.substring(ind0+1, ind1);       //captures first data String
            ind2              = x_str.indexOf('/', ind1+1 );
            
            FR_received       = x_str.substring(ind1+1, ind2);       //captures first data String
            
            ind3              = x_str.indexOf('/', ind2+1 );    //finds location of second ,
            bf2               = x_str.substring(ind2+1, ind3);
            ind4              = x_str.indexOf('/', ind3+1 );
            
            MR_received       = x_str.substring(ind3+1, ind4);  //captures second data String
            
            ind5              = x_str.indexOf('/', ind4+1 );
            bf3               = x_str.substring(ind4+1, ind5);
            ind6              = x_str.indexOf('/', ind5+1 );            //finds location of first ,
            
            BR_received       = x_str.substring(ind5+1, ind6);
            
            ind7              = x_str.indexOf('/', ind6+1 );
            bf4               = x_str.substring(ind6+1, ind7);
            ind8              = x_str.indexOf('/', ind7+1 );  
            
            FL_received       = x_str.substring(ind7+1, ind8);
            
            ind9              = x_str.indexOf('/', ind8+1 );    //finds location of second ,
            bf5               = x_str.substring(ind8+1, ind9);
            ind10             = x_str.indexOf('/', ind9+1 );
            
            ML_received       = x_str.substring(ind9+1, ind10);

            ind11              = x_str.indexOf('/', ind10+1 );    //finds location of second ,
            bf6                = x_str.substring(ind10+1, ind11);
            ind12              = x_str.indexOf('/', ind11+1 );
            
            BL_received       = x_str.substring(ind11+1, ind12);



            if(FR_received.toFloat() == 0 && MR_received.toFloat() == 0 && BR_received.toFloat() == 0 && FL_received.toFloat() == 0 && ML_received.toFloat() == 0 && BL_received.toFloat() == 0)
            {
                stop_Stop();
            }

            // 0: Forward
            // 1: Backward

            if(bf1.toFloat() == 1)
            {
                // Serial.println("FR BCK");
                FR_bck(FR_received.toFloat());
            }
            else{
                // Serial.println("FR FWD");
                FR_fwd(FR_received.toFloat());
            }

            if(bf2.toFloat() == 1)
            {
                MR_bck(MR_received.toFloat());
            }
            else{
                MR_fwd(MR_received.toFloat());
            }

            if(bf3.toFloat() == 1)
            {
                BR_bck(BR_received.toFloat());
            }
            else{
                BR_fwd(BR_received.toFloat());
            }

            if(bf4.toFloat() == 1)
            {
                FL_bck(FL_received.toFloat());
            }
            else{
                FL_fwd(FL_received.toFloat());
            }

            if(bf5.toFloat() == 1)
            {
                ML_bck(ML_received.toFloat());
            }
            else{
                ML_fwd(ML_received.toFloat());
            }

            if(bf6.toFloat() == 1)
            {
                BL_bck(BL_received.toFloat());
            }
            else{
                BL_fwd(BL_received.toFloat());
            }
        }

        Serial.flush();
    }
}
