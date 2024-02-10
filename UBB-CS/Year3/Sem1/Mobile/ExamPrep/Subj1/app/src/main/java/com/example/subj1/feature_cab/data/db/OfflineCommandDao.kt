package com.example.subj1.feature_cab.data.db

import androidx.room.Dao
import androidx.room.Insert
import androidx.room.OnConflictStrategy
import androidx.room.Query
import com.example.subj1.feature_cab.data.model.OfflineCommand

@Dao
interface OfflineCommandsDao {
    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertCommand(command: OfflineCommand)

    @Query("SELECT * FROM offline_commands")
    suspend fun getAllCommands(): List<OfflineCommand>

    @Query("DELETE FROM offline_commands")
    suspend fun clearCommands()
}