#include <Arduino.h>
#include <Servo.h>

String ID = "B";

String x_str;
String message_retour;

String bf0;
String SERVO_LEFT;
String SERVO_RIGHT;

int ind0;
int ind1;
int ind2;

// int LED = 2

const int voltageSensor = 4;
int voltage_value = 0;
float vOUT = 0.0;
float vIN = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
int value = 0;

static const int servo1Pin = 2;  // defines pin number for PWM
static const int servo2Pin = 22;  // defines pin number for PWM

/* Constantes pour les broches */
const byte TRIGGER_PIN_1 = 12; // Broche TRIGGER
const byte ECHO_PIN_1 = 13;    // Broche ECHO

const byte TRIGGER_PIN_2 = 27; // Broche TRIGGER
const byte ECHO_PIN_2 = 14;    // Broche ECHO

const byte TRIGGER_PIN_3 = 26; // Broche TRIGGER
const byte ECHO_PIN_3 = 25;    // Broche ECHO

const byte TRIGGER_PIN_4 = 33; // Broche TRIGGER
const byte ECHO_PIN_4 = 32;    // Broche ECHO

const byte TRIGGER_PIN_5 = 19; // Broche TRIGGER
const byte ECHO_PIN_5 = 21;    // Broche ECHO

const byte TRIGGER_PIN_6 = 16; // Broche TRIGGER
const byte ECHO_PIN_6 = 17;    // Broche ECHO

const byte TRIGGER_PIN_7 = 5; // Broche TRIGGER
const byte ECHO_PIN_7 = 18;    // Broche ECHO
 
/* Constantes pour le timeout */
const unsigned long MEASURE_TIMEOUT_1 = 25000UL; // 25ms = ~8m à 340m/s
const unsigned long MEASURE_TIMEOUT_2 = 25000UL; // 25ms = ~8m à 340m/s
const unsigned long MEASURE_TIMEOUT_3 = 25000UL; // 25ms = ~8m à 340m/s
const unsigned long MEASURE_TIMEOUT_4 = 25000UL; // 25ms = ~8m à 340m/s
const unsigned long MEASURE_TIMEOUT_5 = 25000UL; // 25ms = ~8m à 340m/s
const unsigned long MEASURE_TIMEOUT_6 = 25000UL; // 25ms = ~8m à 340m/s
const unsigned long MEASURE_TIMEOUT_7 = 25000UL; // 25ms = ~8m à 340m/s

/* Vitesse du son dans l'air en mm/us */
const float SOUND_SPEED = 340.0 / 1000;


// Setting PWM properties
const int freq = 30000;

const int pwmChannel1 = 1;
const int pwmChannel2 = 2;

const int resolution = 8;
int dutyCycle = 200;


// Servo servo1;  // Create object for servo motor
// Servo servo2;  // Create object for servo motor


void setup() 
{
    Serial.begin(115200);
    Serial.setTimeout(10); 

    //   servo1.attach(servo1Pin);  // start the library 
    //   servo2.attach(servo2Pin);  // start the library 

    pinMode(servo1Pin, OUTPUT);
    pinMode(servo2Pin, OUTPUT);

    ledcSetup(pwmChannel1, freq, resolution);
    ledcSetup(pwmChannel2, freq, resolution);

    ledcAttachPin(servo1Pin, pwmChannel1);
    ledcAttachPin(servo2Pin, pwmChannel2);

    /* Initialise les broches */
    pinMode(TRIGGER_PIN_1, OUTPUT);
    digitalWrite(TRIGGER_PIN_1, LOW); // La broche TRIGGER doit être à LOW au repos
    pinMode(ECHO_PIN_1, INPUT);

    pinMode(TRIGGER_PIN_2, OUTPUT);
    digitalWrite(TRIGGER_PIN_2, LOW); // La broche TRIGGER doit être à LOW au repos
    pinMode(ECHO_PIN_2, INPUT);

    pinMode(TRIGGER_PIN_3, OUTPUT);
    digitalWrite(TRIGGER_PIN_3, LOW); // La broche TRIGGER doit être à LOW au repos
    pinMode(ECHO_PIN_3, INPUT);

    pinMode(TRIGGER_PIN_4, OUTPUT);
    digitalWrite(TRIGGER_PIN_4, LOW); // La broche TRIGGER doit être à LOW au repos
    pinMode(ECHO_PIN_4, INPUT);

    pinMode(TRIGGER_PIN_5, OUTPUT);
    digitalWrite(TRIGGER_PIN_5, LOW); // La broche TRIGGER doit être à LOW au repos
    pinMode(ECHO_PIN_5, INPUT);

    pinMode(TRIGGER_PIN_6, OUTPUT);
    digitalWrite(TRIGGER_PIN_6, LOW); // La broche TRIGGER doit être à LOW au repos
    pinMode(ECHO_PIN_6, INPUT);

    pinMode(TRIGGER_PIN_7, OUTPUT);
    digitalWrite(TRIGGER_PIN_7, LOW); // La broche TRIGGER doit être à LOW au repos
    pinMode(ECHO_PIN_7, INPUT);
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

        // SERVO COMMANDS
        if(bf0.toFloat() == 1)
        {    
            x_str = x_str + "\n";
            Serial.print(x_str);
            
            ind1              = x_str.indexOf('/', ind0+1 );            //finds location of first ,
            
            SERVO_LEFT        = x_str.substring(ind0+1, ind1);       //captures first data String
            
            ind2              = x_str.indexOf('/', ind1+1 );
            
            SERVO_RIGHT       = x_str.substring(ind1+1, ind2);       //captures first data String
            
            digitalWrite(servo1Pin, HIGH);
            ledcWrite(pwmChannel1, SERVO_LEFT.toFloat());

            digitalWrite(servo2Pin, HIGH);
            ledcWrite(pwmChannel2, SERVO_RIGHT.toFloat());
        }
        
        // SEND ULTRASENSOR VALUES
        if(bf0.toFloat() == 2)
        {
            //   /* 1. Lance une mesure de distance en envoyant une impulsion HIGH de 10µs sur la broche TRIGGER */
            digitalWrite(TRIGGER_PIN_1, HIGH);
            delayMicroseconds(10);
            digitalWrite(TRIGGER_PIN_1, LOW);

            /* 2. Mesure le temps entre l'envoi de l'impulsion ultrasonique et son écho (si il existe) */
            long measure_1 = pulseIn(ECHO_PIN_1, HIGH, MEASURE_TIMEOUT_1);


            digitalWrite(TRIGGER_PIN_2, HIGH);
            delayMicroseconds(10);
            digitalWrite(TRIGGER_PIN_2, LOW);
            long measure_2 = pulseIn(ECHO_PIN_2, HIGH, MEASURE_TIMEOUT_2);


            digitalWrite(TRIGGER_PIN_3, HIGH);
            delayMicroseconds(10);
            digitalWrite(TRIGGER_PIN_3, LOW);
            long measure_3 = pulseIn(ECHO_PIN_3, HIGH, MEASURE_TIMEOUT_3);


            digitalWrite(TRIGGER_PIN_4, HIGH);
            delayMicroseconds(10);
            digitalWrite(TRIGGER_PIN_4, LOW);
            long measure_4 = pulseIn(ECHO_PIN_4, HIGH, MEASURE_TIMEOUT_4);


            digitalWrite(TRIGGER_PIN_5, HIGH);
            delayMicroseconds(10);
            digitalWrite(TRIGGER_PIN_5, LOW);
            long measure_5 = pulseIn(ECHO_PIN_5, HIGH, MEASURE_TIMEOUT_5);


            digitalWrite(TRIGGER_PIN_6, HIGH);
            delayMicroseconds(10);
            digitalWrite(TRIGGER_PIN_6, LOW);
            long measure_6 = pulseIn(ECHO_PIN_6, HIGH, MEASURE_TIMEOUT_6);


            digitalWrite(TRIGGER_PIN_7, HIGH);
            delayMicroseconds(10);
            digitalWrite(TRIGGER_PIN_7, LOW);
            long measure_7 = pulseIn(ECHO_PIN_7, HIGH, MEASURE_TIMEOUT_7);


            /* 3. Calcul la distance à partir du temps mesuré */
            float distance_mm_1 = measure_1 / 2.0 * SOUND_SPEED;
            float distance_mm_2 = measure_2 / 2.0 * SOUND_SPEED;
            float distance_mm_3 = measure_3 / 2.0 * SOUND_SPEED;
            float distance_mm_4 = measure_4 / 2.0 * SOUND_SPEED;
            float distance_mm_5 = measure_5 / 2.0 * SOUND_SPEED;
            float distance_mm_6 = measure_6 / 2.0 * SOUND_SPEED;
            float distance_mm_7 = measure_7 / 2.0 * SOUND_SPEED;
            float voltage_data  = 0;
            float current_data  = 0;

            value = analogRead(voltageSensor);          
            vOUT = (value * 3.3 / 4095);
            vIN = vOUT / (R2/(R1+R2));

            /* Affiche les résultats en mm, cm et m */
            String message = "2/" + String(distance_mm_6)+"/"+String(distance_mm_7)+"/"+String(distance_mm_5)+"/"+String(distance_mm_4)+"/"+String(distance_mm_3)+"/"+String(distance_mm_2)+"/"+String(distance_mm_1) + "/" + String(vIN) + "/" + String(current_data) + "\n";
            Serial.print(message);
        }

        Serial.flush();
    }
    // delay(10);

    // for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
    //   servo1.write(posDegrees);
    //   Serial.println(posDegrees);
    //   delay(20);
    // }

    // for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
    //   servo1.write(posDegrees);
    //   Serial.println(posDegrees);
    //   delay(20);
    // }
}