package com.example.optimus.tezattendance;

/**
 * Created by optimus on 6/4/18.
 */

public class CustomQueryResult {

    String studentID, studentClass;
    Double studentAttendance;

    public CustomQueryResult(String studentID, String studentClass, Double studentAttendance) {
        this.studentID = studentID;
        this.studentClass = studentClass;
        this.studentAttendance = studentAttendance;
    }
}
