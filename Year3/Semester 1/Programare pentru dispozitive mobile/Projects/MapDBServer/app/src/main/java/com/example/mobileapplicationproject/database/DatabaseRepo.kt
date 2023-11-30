package com.example.mobileapplicationproject.database

import android.content.ContentValues
import android.database.sqlite.SQLiteDatabase
import android.util.Log
import com.example.mobileapplicationproject.model.Goal

class DatabaseRepo private constructor(
    private var readableDatabase: SQLiteDatabase,
    private var writableDatabase: SQLiteDatabase
) {
    private var goalList: MutableList<Goal> = ArrayList();

    fun getGoals(): MutableList<Goal> {
        val data: MutableList<Goal> = ArrayList()
        val cursor = readableDatabase.query(Utils.TABLE_NAME, null, null, null, null, null, null);

        while(cursor.moveToNext()){
            val id = cursor.getInt(cursor.getColumnIndexOrThrow("id"))
            val title = cursor.getString(cursor.getColumnIndexOrThrow("title"))
            val description = cursor.getString(cursor.getColumnIndexOrThrow("description"))
            val deadline = cursor.getString(cursor.getColumnIndexOrThrow("deadline"))
            val is_private = cursor.getString(cursor.getColumnIndexOrThrow("is_private")).toBoolean()
            val mini_goalsString = cursor.getString(cursor.getColumnIndexOrThrow("mini_goals"))
            val mini_goals = mini_goalsString.split(",").map { it.trim() }

            val goal = Goal(id, title, description, deadline, is_private, mini_goals)

            data.add(goal)
        }
        cursor.close()

        goalList = data

        return goalList.toMutableList()
    }

    fun getById(id: Int): Goal? {
        for(i in goalList.indices){
            if(id == goalList[i].id){
                return goalList[i]
            }
        }
        return null
    }

    fun add(goal: Goal): Long{
        val values = ContentValues()
        values.put(Utils.COL_TITLE, goal.title)
        values.put(Utils.COL_DESCRIPTION, goal.description)
        values.put(Utils.COL_DEADLINE, goal.deadline)
        values.put(Utils.COL_IS_PRIVATE, if (goal.isPrivate) 1 else 0)
        values.put(Utils.COL_MINI_GOALS, goal.miniGoals.joinToString(","))

        val result = writableDatabase.insert(Utils.TABLE_NAME,null, values)

        if(result == (-1).toLong()){
            val str = "DATABASE -> ADD"
            Log.i(str, "An Error appeared when inserting the element to the database!")
            return -1
        }

        return result
    }

    fun delete(id: Int): Boolean {
        val selection: String = Utils.COL_ID + " = ?"
        val selectionArgs = arrayOf(id.toString())

        val result = writableDatabase.delete(Utils.TABLE_NAME, selection, selectionArgs)

        if(result == -1){
            val str = "DATABASE -> Delete"
            Log.i(str, "An Error appeared when deleting the element from the database!")
            return false
        }

        return true
    }

    fun update(goal: Goal, id: Int): Goal? {
        val values = ContentValues()
        values.put(Utils.COL_TITLE, goal.title)
        values.put(Utils.COL_DESCRIPTION, goal.description)
        values.put(Utils.COL_DEADLINE, goal.deadline)
        values.put(Utils.COL_IS_PRIVATE, if (goal.isPrivate) 1 else 0)
        values.put(Utils.COL_MINI_GOALS, goal.miniGoals.joinToString(","))

        val selection: String = Utils.COL_ID + " = ?"
        val selectionArgs = arrayOf(id.toString())

        val result = writableDatabase.update(Utils.TABLE_NAME, values, selection, selectionArgs)

        if(result == -1){
            val str = "DATABASE -> Update"
            Log.i(str, "An Error appeared when updating the element from the database!")
            return null
        }

        return goal
    }

    companion object{
        private var instance: DatabaseRepo? = null
        fun getInstance(readableDatabase: SQLiteDatabase, writableDatabase: SQLiteDatabase): DatabaseRepo {
            if(instance == null) instance = DatabaseRepo(readableDatabase, writableDatabase)
            return instance as DatabaseRepo
        }
    }

}