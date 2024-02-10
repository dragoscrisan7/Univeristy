package com.example.subj1.feature_cab.data.repository

import android.content.Context
import com.example.subj1.feature_cab.data.db.OfflineCommandsDao
import com.example.subj1.feature_cab.data.db.PropertyDao
import com.example.subj1.feature_cab.data.model.OfflineCommand
import com.example.subj1.feature_cab.data.model.PropertyEntity
import com.example.subj1.feature_cab.data.service.PropertyService
import dagger.hilt.android.qualifiers.ApplicationContext
import kotlinx.coroutines.flow.Flow
import retrofit2.Response
import java.io.IOException
import javax.inject.Inject

class PropertyRepoImpl @Inject constructor(
    private val dao: PropertyDao,
    private val propertyService: PropertyService,
    private val oCdao: OfflineCommandsDao,
    @ApplicationContext private val context: Context
) : PropertyRepo {
///Register
    override fun getAllProperties(): Flow<List<PropertyEntity>> {
        return dao.getAllProperties()
    }

    override suspend fun getPropertyById(id: Long): PropertyEntity? {
        return dao.getPropertyById(id)
    }

    override suspend fun insertProperty(property: PropertyEntity) {
        val localId = dao.insertProperty(property)
        if (isServerReachable()) {
            try {
                val response = propertyService.insertProperty(property)
                if (response.isSuccessful) {
                    val newProperty = response.body()
                    newProperty?.let {
                        dao.updatePropertyId(localId, it.id)
                    }
                } else {
                    val offlineCommand = OfflineCommand(type = OfflineCommand.CommandType.INSERT, property = property, propertyId = localId)
                    oCdao.insertCommand(offlineCommand)
                }
            } catch (e: Exception) {
                val offlineCommand = OfflineCommand(type = OfflineCommand.CommandType.INSERT, property = property, propertyId = localId)
                oCdao.insertCommand(offlineCommand)
            }
        } else {
            val offlineCommand = OfflineCommand(type = OfflineCommand.CommandType.INSERT, property = property, propertyId = localId)
            oCdao.insertCommand(offlineCommand)
        }
    }

    override suspend fun getPropertyTypes(): List<String> {
        return propertyService.getPropertyTypes() ?: emptyList()
    }

    override suspend fun expressInterest(propertyType: String) {
        // Implement your logic for expressing interest in a property type
    }


    override suspend fun processOfflineCommands() {
        val offlineCommands = oCdao.getAllCommands()

        for (command in offlineCommands) {
            when (command.type) {
                OfflineCommand.CommandType.INSERT -> {
                    propertyService.insertProperty(command.property!!)
                }
//                OfflineCommand.CommandType.DELETE -> {
//                    propertyService.deleteCab(command.property!!.id)
//                }
//                OfflineCommand.CommandType.UPDATE -> {
//                    propertyService.updateCab(command.propertyId ?: 0, command.property!!)
//                }
            }
        }

        oCdao.clearCommands()
    }

    suspend fun isServerReachable(): Boolean {
        return try {
            val response = propertyService.getAllProperties()
            response.isNotEmpty()
        } catch (e: IOException) {
            false
        }
    }
}