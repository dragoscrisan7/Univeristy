package com.example.mobileapplicationproject.view

import android.content.Context
import android.database.sqlite.SQLiteDatabase
import android.net.ConnectivityManager
import android.net.NetworkCapabilities
import android.os.Bundle
import android.view.Window
import android.widget.ImageView
import androidx.appcompat.app.AppCompatActivity
import androidx.core.content.ContextCompat
import androidx.lifecycle.lifecycleScope
import com.example.mobileapplicationproject.R
import com.example.mobileapplicationproject.database.DatabaseRepo
import com.example.mobileapplicationproject.database.Utils
import kotlinx.coroutines.launch
import kotlinx.android.synthetic.main.activity_list_notes.*

class GoalList: AppCompatActivity() {
    private lateinit var readableDatabase: SQLiteDatabase
    private lateinit var writableDatabase: SQLiteDatabase
    private lateinit var goalRepo: DatabaseRepo;

    lateinit var addButton: ImageView
    private lateinit var dbHelper: Utils;

    private var context = this;

    private fun isNetworkConnected(): Boolean {
        val connectivityManager =
            getSystemService(Context.CONNECTIVITY_SERVICE) as ConnectivityManager
        val activeNetwork = connectivityManager.activeNetwork
        val networkCapabilities = connectivityManager.getNetworkCapabilities(activeNetwork)
        return networkCapabilities != null &&
                networkCapabilities.hasCapability(NetworkCapabilities.NET_CAPABILITY_INTERNET)
    }

    override fun onCreate(savedInstanceState: Bundle?){
        val str = "LIST ACTIVITY"

        super.onCreate(savedInstanceState)

        setContentView(R.layout.activity_list_notes)

        supportActionBar?.hide()

        val window: Window = this@GoalList.window
        window.statusBarColor = ContextCompat.getColor(this@GoalList, R.color.black)


        dbHelper = Utils(this)
        readableDatabase = dbHelper.readableDatabase;
        writableDatabase = dbHelper.writableDatabase;
        goalRepo = DatabaseRepo.getInstance(readableDatabase, writableDatabase)!!

        lifecycleScope.launch {
            recyclerView.layoutManager = LinearLayoutManager(context)
            recyclerView.adapter = ItemAdapter(context)
        }

        if (!isNetworkConnected()) {
            showDialog()
        }

    }
}