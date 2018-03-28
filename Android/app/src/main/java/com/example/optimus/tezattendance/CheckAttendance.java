package com.example.optimus.tezattendance;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.util.ArrayList;

public class CheckAttendance extends AppCompatActivity {

    EditText editTextClassName, editTextRollNumber;
    Button buttonCheckAttendace, buttonCalculate;

    ListView listViewAttendance;
    ArrayList<Subject> totalLectures, attendedLectures;

    ArrayList<String> arrayListAttendance;
    ArrayAdapter<String> arrayAdapterAttendance;

    DatabaseReference databaseReference;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_check_attendance);

        editTextClassName = findViewById(R.id.editTextClassNameCheck);
        editTextRollNumber = findViewById(R.id.editTextRollNumberCheck);
        buttonCheckAttendace = findViewById(R.id.buttonCheckAttendanceFinally);
        databaseReference = FirebaseDatabase.getInstance().getReference();
        arrayListAttendance = new ArrayList<>();
        totalLectures = new ArrayList<>();
        attendedLectures = new ArrayList<>();
        buttonCalculate = findViewById( R.id.buttonCalculate);
        listViewAttendance = findViewById(R.id.listViewShowingAttendance);
        buttonCheckAttendace.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                databaseReference.child(editTextClassName.getText().toString())
                        .child("Subjects").addValueEventListener(new ValueEventListener() {
                    @Override
                    public void onDataChange(DataSnapshot dataSnapshot) {

                        for ( DataSnapshot ds : dataSnapshot.getChildren()){

                            Subject subject = ds.getValue(Subject.class);
                            totalLectures.add(subject);

                        }

                    }

                    @Override
                    public void onCancelled(DatabaseError databaseError) {

                    }
                });

                databaseReference.child(editTextClassName.getText().toString())
                        .child("Students").child(editTextRollNumber.getText().toString())
                        .child("Subjects").addValueEventListener(new ValueEventListener() {
                    @Override
                    public void onDataChange(DataSnapshot dataSnapshot) {

                        for (DataSnapshot ds : dataSnapshot.getChildren()){
                            Subject subject = ds.getValue(Subject.class);
                            attendedLectures.add(subject);
                        }

                    }

                    @Override
                    public void onCancelled(DatabaseError databaseError) {

                    }
                });

            }
        });

        buttonCalculate.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                //editTextClassName.setText("LEC: " + totalLectures.size());

                Double totalAttended = 0D;
                Double totalLecturesd = 0D;

                for ( int i = 0 ; i < totalLectures.size(); i ++){

                    totalAttended += Double.parseDouble(attendedLectures.get(i).lectures);
                    totalLecturesd += Double.parseDouble(totalLectures.get(i).lectures);

                    arrayListAttendance.add(totalLectures.get(i).subjectName + ": " +
                            (Double.toString(

                                    Double.parseDouble(attendedLectures.get(i).lectures) * 100 /
                                            Double.parseDouble(totalLectures.get(i).lectures)

                            )) + "%");
                }

                arrayListAttendance.add( "Total Attendance: " + Double.toString(totalAttended/totalLecturesd) + "%");
                arrayAdapterAttendance = new ArrayAdapter<String>(CheckAttendance.this,
                        android.R.layout.simple_list_item_1,arrayListAttendance);
                listViewAttendance.setAdapter(arrayAdapterAttendance);

            }
        });

    }
}
