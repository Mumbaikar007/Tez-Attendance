

/* =======================================================
                      Attendance Over Network

ID 0 not allowed while registering !!


   ======================================================= */


/* ================== Adding Headers and Port Macros =============== */

# include <SoftwareSerial.h>
# include <Adafruit_Fingerprint.h>


# define blueTooth_rx 10
# define blueTooth_tx 11

# define mySerial_rx 2
# define mySerial_tx 3

/* ================ Done Adding Headers and Port Macros ============= */


/* ================== Declaring Objects =============== */

SoftwareSerial blueTooth ( blueTooth_rx, blueTooth_tx);
SoftwareSerial mySerial ( mySerial_rx, mySerial_tx);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

/* ================ Done Declaring Objects ============= */


/* ================== The Setup  =============== */

void setup() {
  
  Serial.begin(9600);

  while (!Serial);  
  delay(100);
  //Serial.println("\n\nAdafruit Fingerprint sensor enrollment");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  blueTooth.begin(38400);
  
}

/* ================ Done with The Setup ============= */

char ReadFromBluetooth (){
  
  while(!blueTooth.available());
  Serial.println("Wait");

  char digit = blueTooth.read();
  if ( !(digit >= '0' && digit <= '9') ){
    Serial.println("Enter Again !");
    digit = ReadFromBluetooth ();
  }
  
  return digit;
  
}
/* ================== RegisterFingerprints =============== */

uint8_t getFingerprintEnroll( int id ) {

  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  Serial.println("Remove finger");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  Serial.print("Creating model for #");  Serial.println(id);
  
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
}

int ReadIdFromBluetooth(){

  int number = 0;
  
  for ( int i = 0; i < 3; i ++){
    char digit = ReadFromBluetooth();
    number = ( number * 10 ) + ( digit - '0');       
  }

  return number;
  
}


void RegisterFingerprints() {

  int nextAttendance = 1;

  while (nextAttendance){
    
    nextAttendance = 0;

    Serial.println ("Please enter his/her Roll Number ... ");
    int id = ReadIdFromBluetooth();

    Serial.print( "Id Entered: ");
    Serial.println ( id );
    
    while (!getFingerprintEnroll(id) );

    Serial.println ( "Do you want to register someone else ? (1/0)");
    nextAttendance = ( ReadFromBluetooth() == '1' ? 1 : 0 );
    
  }
  
}

/* ================ Done RegisterFingerprints ============= */


/* ================== TakeAttendance =============== */

void TakeAttendance(){

}

/* ================ Done TakeAttendance ============= */

/* ================== DeleteFingerprint =============== */

void DeleteFingerprint(){
  
}

/* ================ Done DeleteFingerprint ============= */

/* ================== DeleteEntireDatabase =============== */

void DeleteEntireDatabase(){
  
}

/* ================ Done DeleteEntireDatabase ============= */



/* ================== Switching Bluetooth Command =============== */

void CheckBluetoothCommand() {
  
  char command = ReadFromBluetooth();

  Serial.println(command);
  
  switch (command){
    
    case '1': Serial.println("Switching to RegisterFingerprints ... ");
              RegisterFingerprints();
              break;
              
    case '2': TakeAttendance();
              break;
              
    case '3': DeleteFingerprint();
              break;
              
    case '4': DeleteEntireDatabase();
              break;

    default : Serial.println("Enter a command !");  
  }
  
  delay(10);
  
}

/* ================ Done Switching Bluetooth Command ============= */



/* ================== The Main Loop =============== */


void loop() {

  CheckBluetoothCommand();
  
}

/* ================ Done The Main Loop ============= */
