package com.example.subj1.feature_cab.data.db

import androidx.room.Database
import androidx.room.RoomDatabase
import androidx.room.TypeConverters
import com.example.subj1.feature_cab.data.model.Converters
import com.example.subj1.feature_cab.data.model.OfflineCommand

@Database(
    entities = [OfflineCommand::class],
    version = 1,
    exportSchema = false
)
@TypeConverters(Converters::class)
abstract class OfflineCommandDatabase: RoomDatabase() {

    abstract val oCdao: OfflineCommandsDao
}