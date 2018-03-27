package com.example.optimus.tezattendance;

import android.os.Parcel;
import android.os.Parcelable;

/**
 * Created by optimus on 21/3/18.
 */

public class Subject implements Parcelable{

    public String subjectName, lectures;

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel parcel, int i) {

        parcel.writeString(subjectName);
        parcel.writeString(lectures);

    }


    public static final Parcelable.Creator<Subject> CREATOR
            = new Parcelable.Creator<Subject>() {
        public Subject createFromParcel(Parcel in) {
            return new Subject(in);
        }
        public Subject[] newArray(int size) {
            return new Subject[size];
        }
    };



    public Subject(Parcel in) {

        subjectName = in.readString();
        lectures = in.readString();

    }


    public Subject(){

    }

    public Subject( String subjectName, String lectures){
        this.subjectName = subjectName;
        this.lectures = lectures;
    }

}
