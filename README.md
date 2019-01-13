# Tez-Attendance
>  A high-speed student attendance system

An IoT attendance system that scans the student's fingerprint to mark him present. A Firebase Database stores the attendance. 

Basic Idea:

1. Professors connect their Andriod Phone to the Arduio using a Bluetooth using the mobile app. 
2. The Arduino is passed around in the classroom. Fingerprint Scanner attached to Arduino scans the student's fingerprint.
3. Each fingerprint has an associated id, i.e, the student's roll number. It is sent to Arduino and then to Professor's mobile.
4. The andriod app updates the attendance on Firebase. 

The Andriod app can make a new class, register students for the class, take attendance, show defaulters, delete a class.

![](header.png)

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

1. Install Arduiono IDE and Android Studio. 
2. Setup a Firebase connection with Android Studio.

### Installing

1. Clone the repository

```
https://github.com/Mumbaikar007/Tez-Attendance.git
```

2. Open folders in their respective environments.

3. Arduino Connections:<br>
blueTooth tx - 10<br>
blueTooth rx - 11<br>
Adafruit rx - 2<br>
Adafruit tx - 3

## Running the tests

1. Start your Ardunio and Android App.
2. Connect them using bluetooth.
3. Register a Class first: Class name, subject, students and their ids.
4. Take attendance for that class.
5. Check attendance. 
6. Delete the class at the end of semester.

## Built With

* [Arduino](https://www.arduino.cc/) - The IoT device
* [Android Studio](https://developer.android.com/studio/) - Mobile Application
* [AdaFruit Fingerprint Sensor](https://learn.adafruit.com/adafruit-optical-fingerprint-sensor?view=all) - Student Fingerprint Scanning
* Bluetooth - To make connections

## Contributing

Mail me - brainteaser97@gmail.com

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Those who marked me absent for not answering my roll-call. 
* [Solderer TV - Anatoliy](http://solderer.tv/data-transfer-between-android-and-arduino-via-bluetooth/)
* [Darshan](https://github.com/darshan2790), [Sagar](https://github.com/SagarM879), [Jay](https://www.linkedin.com/in/jaykumar0530/), [Aditi](https://github.com/AditiPawaskar)
