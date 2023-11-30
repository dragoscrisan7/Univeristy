package com.example.mobileapplicationproject.database

import android.content.Context
import android.database.sqlite.SQLiteDatabase
import android.database.sqlite.SQLiteOpenHelper

class Utils(context: Context?) :
    SQLiteOpenHelper(
    context,
    DATABASE_NAME,
    null,
    DATABASE_VERSION
    ) {
    override fun onCreate(db: SQLiteDatabase) {
        db.execSQL(SQL_CREATE_ENTRIES)
    }

    override fun onUpgrade(
        db: SQLiteDatabase,
        oldVersion: Int,
        newVersion: Int
    ) {
        // This database is only a cache for online data, so its upgrade policy is
        // to simply to discard the data and start over
        db.execSQL(SQL_DELETE_ENTRIES)
        onCreate(db)
    }

    override fun onDowngrade(
        db: SQLiteDatabase,
        oldVersion: Int,
        newVersion: Int
    ) {
        onUpgrade(db, oldVersion, newVersion)
    }

    companion object {
        // If you change the database schema, you must increment the database version.
        const val DATABASE_VERSION = 1
        const val DATABASE_NAME = "GoalsDbs.db"
        const val TABLE_NAME = "Goals"
        const val COL_ID = "id"
        const val COL_TITLE = "title"
        const val COL_DESCRIPTION = "description"
        const val COL_DEADLINE = "deadline"
        const val COL_IS_PRIVATE = "is_private"
        const val COL_MINI_GOALS = "mini_goals"

        private const val SQL_CREATE_ENTRIES =
            "CREATE TABLE " + TABLE_NAME + " (" +
                    COL_ID + " INTEGER PRIMARY KEY AUTOINCREMENT ," +
                    COL_TITLE + " TEXT, " +
                    COL_DESCRIPTION + " TEXT, " +
                    COL_DEADLINE + " TEXT, " +
                    COL_IS_PRIVATE + " INTEGER, " +
                    COL_MINI_GOALS + " TEXT)"

        private const val SQL_DELETE_ENTRIES =
            "DROP TABLE IF EXISTS " + TABLE_NAME
    }

}