package com.example.subj1.di

import android.content.Context
import androidx.room.Room
import com.example.subj1.feature_cab.data.db.OfflineCommandDatabase
import com.example.subj1.feature_cab.data.db.PropertyDatabase
import com.example.subj1.feature_cab.data.repository.PropertyRepo
import com.example.subj1.feature_cab.data.repository.PropertyRepoImpl
import com.example.subj1.feature_cab.data.service.PropertyService
import com.example.subj1.feature_cab.data.use_cases.AddProperty
import com.example.subj1.feature_cab.data.use_cases.GetAllPropertyTypes
import com.example.subj1.feature_cab.data.use_cases.GetProperties
import com.example.subj1.feature_cab.data.use_cases.GetProperty
import com.example.subj1.feature_cab.data.use_cases.PropertyUseCases
import dagger.Module
import dagger.Provides
import dagger.hilt.InstallIn
import dagger.hilt.android.qualifiers.ApplicationContext
import dagger.hilt.components.SingletonComponent
import retrofit2.Retrofit
import javax.inject.Singleton

@Module
@InstallIn(SingletonComponent::class)
object AppModule {
    @Provides
    @Singleton
    fun provideContext(@ApplicationContext context: Context): Context {
        return context
    }

    @Provides
    @Singleton
    fun providePropertyDatabase(@ApplicationContext context: Context): PropertyDatabase {
        return Room.databaseBuilder(
            context,
            PropertyDatabase::class.java,
            "properties_db"
        ).build()
    }

    @Provides
    @Singleton
    fun provideOfflineCommandDatabase(@ApplicationContext context: Context): OfflineCommandDatabase {
        return Room.databaseBuilder(
            context,
            OfflineCommandDatabase::class.java,
            "offline_commands_db"
        ).build()
    }

    @Provides
    @Singleton
    fun providePropertyRepository(
        db: PropertyDatabase,
        cabService: PropertyService,
        oCdb : OfflineCommandDatabase,
        @ApplicationContext context: Context
    ): PropertyRepo {
        return PropertyRepoImpl(db.propertyDao, cabService, oCdb.oCdao, context)
    }

    @Provides
    @Singleton
    fun providePropertyUseCases(repository: PropertyRepo): PropertyUseCases {
        return PropertyUseCases(
            getProperty = GetProperty(repository),
            getProperties = GetProperties(repository),
            addProperty = AddProperty(repository),
            getAllPropertyTypes = GetAllPropertyTypes(repository)
        )
    }

    @Provides
    @Singleton
    fun providePropertyService(retrofit: Retrofit): PropertyService {
        return retrofit.create(PropertyService::class.java)
    }
}