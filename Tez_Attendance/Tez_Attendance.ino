

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

int previousFingerPrint = 0;

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

uint8_t readnumber(void) {
  uint8_t num = 0;
  
  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}

/* ================ Done with The Setup ============= */

char ReadFromBluetooth (){

  blueTooth.listen();
  
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

uint8_t getFingerprintEnroll(int id) {

  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  
  mySerial.listen();
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
    blueTooth.write("0");
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    blueTooth.write((char)id +'0');
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

uint8_t ReadIdFromBluetooth(){

  uint8_t number = 0;
  
  for ( int i = 0; i < 3; i ++){
    char digit = ReadFromBluetooth();
    number = ( number * 10 ) + ( digit - '0');       
  }

  return number;
  
}


void RegisterFingerprints() {

  int nextAttendance = 1;

  while (true){
    
    nextAttendance = 0;

    
    Serial.println ("Please enter his/her Roll Number ... ");
    uint8_t id = ReadIdFromBluetooth();

    Serial.print( "Id Entered: ");
    Serial.println ( id );
    
    if ( id == 0 ){
      //Serial.println ("ID 0 Not allowed !!");
      break;
    }
    /*
    Serial.println("Ready to enroll a fingerprint!");
    Serial.println("Please type in the ID # (from 1 to 127) you want to save this finger as...");
    id = readnumber();
    if (id == 0) {// ID #0 not allowed, try again!
       return;
    }
    Serial.print("Enrolling ID #");
    Serial.println(id);
    */

    
    while ( !getFingerprintEnroll(id) );

    /*
    Serial.println ( "Do you want to register someone else ? (1/0)");
    nextAttendance = ( ReadFromBluetooth() == '1' ? 1 : 0 );
    */
    
  }
  
}

/* ================ Done RegisterFingerprints ============= */


/* ================== TakeAttendance =============== */

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
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
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  
  if ( finger.fingerID > 0 && finger.fingerID <10 ){
    if ( previousFingerPrint != finger.fingerID ){
      previousFingerPrint = finger.fingerID;
      blueTooth.write( (char) ( finger.fingerID + '0') ); 
    }
  }
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID; 
}


void TakeAttendance(){

    Serial.println( "getFingerprintIDez");
    int t = 2;
    mySerial.listen();
    while ( true ){
      getFingerprintIDez();
      delay(50);
    }
      
    
}

/* ================ Done TakeAttendance ============= */

/* ================== DeleteFingerprint =============== */

void DeleteFingerprint(){
  
}

/* ================ Done DeleteFingerprint ============= */

/* ================== DeleteEntireDatabase =============== */

void DeleteEntireDatabase(){

    char command = ReadFromBluetooth();

    mySerial.listen();
    if ( (int) command - '0' == 1){
      Serial.println("Almost:D");
      finger.emptyDatabase(); 
    }
  
     
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
              
    case '2': Serial.println("Switching to TakeAttendance");
              TakeAttendance();
              break;
              
    case '3': DeleteFingerprint();
              break;
              
    case '4': Serial.println("Switching to Delete entire database function");
              DeleteEntireDatabase();
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

