package com.example.mobileapplicationproject.database

import android.provider.BaseColumns

class Table
private constructor() {
    object Entry : BaseColumns {
        const val TABLE_NAME = "Goals"
        const val COLUMN_NAME_ID = "id"
        const val COLUMN_NAME_TITLE = "title"
        const val COLUMN_NAME_DESCRIPTION = "description"
        const val COLUMN_NAME_DEADLINE = "deadline"
        const val COLUMN_NAME_IS_PRIVATE = "is_private"
        const val COLUMN_NAME_MINI_GOALS = "mini_goals"
    }
}