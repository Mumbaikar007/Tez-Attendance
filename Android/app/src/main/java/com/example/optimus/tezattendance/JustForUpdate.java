package com.example.optimus.tezattendance;

/**
 * Created by optimus on 24/3/18.
 */

public class JustForUpdate {

    public String key, rollnumber;
    public Subject subjectToUpdate;

    public JustForUpdate(String key, String rollnumber,Subject subjectToUpdate) {
        this.key = key;
        this.rollnumber = rollnumber;
        this.subjectToUpdate = subjectToUpdate;
    }
}
