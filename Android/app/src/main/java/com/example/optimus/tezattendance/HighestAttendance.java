package com.example.optimus.tezattendance;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.Query;
import com.google.firebase.database.ValueEventListener;

import java.util.ArrayList;

public class HighestAttendance extends AppCompatActivity {

    EditText editTextQueryClassName, editTextTotalStudents;
    Button buttonQueryClassAdd, buttonQueryResults;
    ListView listViewQueryClasses;
    TextView textViewQueryResult;
    DatabaseReference databaseReference;
    ArrayList<String> arrayListClassesDisplay, arrayListClassNames;
    ArrayAdapter<String> arrayAdapterClasses;
    ArrayList<Integer> arrayListTotalStudents;
    ArrayList<CustomQueryResult> arrayListAttendance;

    ArrayList<Subject> totalLectures, attendedLectures;
    ArrayList<CustomQueryResult> arrayListQueryStore;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_highest_attendance);

        editTextQueryClassName = findViewById(R.id.editTextQueryClassName);
        buttonQueryClassAdd = findViewById( R.id.buttonQueryAddClass);
        buttonQueryResults = findViewById(R.id.buttonQueryResult);
        listViewQueryClasses = findViewById(R.id.listViewQueryListClasses);
        textViewQueryResult = findViewById(R.id.textViewQueryResult);
        //listViewQueryClasses = findViewById(R.id.listViewQueryListClasses);
        arrayListClassNames = new ArrayList<>();
        arrayListAttendance = new ArrayList<>();
        databaseReference = FirebaseDatabase.getInstance().getReference();
        editTextTotalStudents = findViewById(R.id.editTextTotalStudents);
        totalLectures = new ArrayList<>();
        attendedLectures = new ArrayList<>();
        arrayListTotalStudents = new ArrayList<>();
        arrayListClassesDisplay = new ArrayList<>();
        arrayListQueryStore = new ArrayList<>();

        buttonQueryClassAdd.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                String className = editTextQueryClassName.getText().toString();
                String rollNumbers = editTextTotalStudents.getText().toString();

                arrayListClassNames.add(className);
                arrayListTotalStudents.add(Integer.parseInt(rollNumbers));
                
                arrayListClassesDisplay.add(className + ": " + rollNumbers);
                arrayAdapterClasses = new ArrayAdapter<>(HighestAttendance.this, android.R.layout.simple_list_item_1, arrayListClassesDisplay);
                listViewQueryClasses.setAdapter(arrayAdapterClasses);

                databaseReference.child(className).child("Subjects").addValueEventListener(new ValueEventListener() {
                    @Override
                    public void onDataChange(DataSnapshot dataSnapshot) {
                        for (DataSnapshot ds :dataSnapshot.getChildren()){
                            
                            Subject subject = ds.getValue(Subject.class);
                            totalLectures.add(subject);
                            
                        }
                    }

                    @Override
                    public void onCancelled(DatabaseError databaseError) {

                    }
                });

                for ( int i = 1; i <= Integer.parseInt(rollNumbers); i ++){
                    databaseReference.child(className)
                            .child("Students").child(Integer.toString(i))
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



            }
        });
        
        
        buttonQueryResults.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                Double maxAttendance = 0D;

                //Toast.makeText(getApplicationContext(), "" + totalLectures.size(), Toast.LENGTH_LONG).show();
                //Toast.makeText(getApplicationContext(), "" + attendedLectures.size(), Toast.LENGTH_LONG).show();


                for(int i = 0 ;  i < arrayListClassesDisplay.size(); i ++){ // in classes
                    for ( int j = 0 ; j < arrayListTotalStudents.get(i); j ++ ){ // for each student
                        Double totalAttended = 0D;
                        Double totalLecturesd = 0D;
                        for ( int k = 0 ; k < 5; k ++){ // for his 5 subjects
                            totalAttended += Double.parseDouble(attendedLectures.get((i*15)+j*5+k).lectures);
                            totalLecturesd += Double.parseDouble(totalLectures.get((i*3)+k).lectures);
                        }

                        Double currentAttendance = totalAttended * 100 /totalLecturesd;

                        if ( maxAttendance < currentAttendance ){
                            arrayListAttendance.clear();
                            CustomQueryResult customQueryResult = new CustomQueryResult(
                                    Integer.toString(j+1), arrayListClassNames.get(i), currentAttendance
                            );
                            maxAttendance = currentAttendance;
                            arrayListAttendance.add(customQueryResult);
                        }
                        else if ( maxAttendance == currentAttendance){
                            CustomQueryResult customQueryResult = new CustomQueryResult(
                                    Integer.toString(j+1), arrayListClassNames.get(i), currentAttendance
                            );
                            maxAttendance = currentAttendance;
                            arrayListAttendance.add(customQueryResult);
                        }

                    }
                }

                textViewQueryResult.setText( arrayListAttendance.get(0).studentClass + " - "
                                                + arrayListAttendance.get(0).studentID + ": "
                                                + Double.toString(arrayListAttendance.get(0).studentAttendance));

                //Toast.makeText(getApplicationContext(), "" + arrayListAttendance.size(),Toast.LENGTH_LONG ).show();

                
            }
        });

    }
}
