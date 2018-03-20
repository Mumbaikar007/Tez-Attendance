package com.example.optimus.tezattendance;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;

import java.util.ArrayList;

public class RegisterClass extends AppCompatActivity {

    private EditText editTextClassName;
    private Button buttonAddSubject, buttonRegisterClass;
    private ListView listViewSubjects;
    ArrayList<String> arrayListSubjects;
    ArrayAdapter<String> arrayAdapterSubjects;
    String className;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_register_class);

        editTextClassName = findViewById(R.id.editTextClassName);
        buttonAddSubject = findViewById(R.id.buttonAddSubject);
        buttonRegisterClass = findViewById(R.id.buttonRegisterClass);
        listViewSubjects = findViewById(R.id.listViewSubjects);

        arrayListSubjects = new ArrayList<>();

        buttonAddSubject.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                String subject = editTextClassName.getText().toString();
                arrayListSubjects.add(subject);

                arrayAdapterSubjects = new ArrayAdapter<String>(RegisterClass.this, android.R.layout.simple_list_item_1, arrayListSubjects);
                listViewSubjects.setAdapter(arrayAdapterSubjects);

            }
        });

        buttonRegisterClass.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                className = editTextClassName.getText().toString();
                startActivity(new Intent(RegisterClass.this,RegisterStudent.class)
                        .putExtra("SubjectsList",arrayListSubjects)
                        .putExtra("ClassName", className));

            }
        });

    }
}
