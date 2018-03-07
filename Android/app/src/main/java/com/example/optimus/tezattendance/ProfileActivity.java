package com.example.optimus.tezattendance;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;

import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;

public class ProfileActivity extends AppCompatActivity implements View.OnClickListener{

    private FirebaseAuth firebaseAuth;
    private Button buttonLogout;

    private LinearLayout buttonRegisterStudent, buttonEmptyDatabase;
    private LinearLayout buttonTakeAttendance, buttonUploadProxy;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_profile);

        firebaseAuth= FirebaseAuth.getInstance();
        //buttonLogout = findViewById(R.id.buttonLogout);


        buttonEmptyDatabase = findViewById(R.id.linearLayoutDeleteDatabase);
        buttonRegisterStudent = findViewById(R.id.linearLayoutRegister);
        buttonTakeAttendance = findViewById(R.id.linearLayoutTakeAttendance);
        buttonUploadProxy = findViewById( R.id.linearLayoutUpdate);


        if(firebaseAuth.getCurrentUser() == null){
            //user is not logged in
            finish();
            startActivity(new Intent(this,LoginActivity.class));

        }

        FirebaseUser user  = firebaseAuth.getCurrentUser();
        //buttonLogout.setOnClickListener(this);

        buttonEmptyDatabase.setOnClickListener(this);
        buttonRegisterStudent.setOnClickListener(this);
        buttonTakeAttendance.setOnClickListener(this);
        buttonUploadProxy.setOnClickListener(this);

    }

    @Override
    public void onClick(View view) {

        /*
        if( view == buttonLogout){
            Log.d("Auth", "Logged out");
            firebaseAuth.signOut();
            finish();
            startActivity(new Intent(this,LoginActivity.class));
        }
        */

        if ( view == buttonEmptyDatabase){

            startActivity(new Intent(this,EmptyDatabase.class));
        }

        if ( view == buttonRegisterStudent){

            startActivity(new Intent(this,RegisterStudent.class));
        }

        if ( view == buttonTakeAttendance ){

            startActivity(new Intent(this,TakeAttendance.class));
        }

        if ( view == buttonUploadProxy){

            startActivity(new Intent(this,UploadProxy.class));
        }

    }
}
