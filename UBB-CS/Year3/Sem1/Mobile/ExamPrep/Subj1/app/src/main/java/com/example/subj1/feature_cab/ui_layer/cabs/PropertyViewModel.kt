package com.example.subj1.feature_cab.ui_layer.cabs

import androidx.compose.runtime.State
import androidx.compose.runtime.mutableStateOf
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.example.subj1.feature_cab.data.use_cases.PropertyUseCases
import dagger.hilt.android.lifecycle.HiltViewModel
import kotlinx.coroutines.Job
import kotlinx.coroutines.flow.launchIn
import kotlinx.coroutines.flow.onEach
import kotlinx.coroutines.launch
import javax.inject.Inject

@HiltViewModel
class PropertyViewModel @Inject constructor(
    private val propertyUseCases: PropertyUseCases
): ViewModel() {
    private val _state = mutableStateOf(PropertiesState())
    val state: State<PropertiesState> = _state

    private var getPropertiesJob: Job? = null

    private var getPropertyTypesJob: Job? = null

    private var currentPropertyId: Long? = null

    init {
        getProperties()
    }

    fun onEvent(event: PropertiesEvent) {
        viewModelScope.launch {
            when (event) {
                is PropertiesEvent.AddProperty -> {
                    propertyUseCases.addProperty(event.property)
                }
                is PropertiesEvent.GetProperty -> {
                    val property = propertyUseCases.getProperty(event.propertyId)
                    property?.let {
                        _state.value = state.value.copy(property = property)
                    }
                }
                PropertiesEvent.GetProperties -> {
                    getProperties()
                }
                PropertiesEvent.GetAllPropertyTypes -> {
                    ///getPropertyTypes()
                }
            }
        }
    }

    private fun getProperties() {
        getPropertiesJob?.cancel()
        getPropertiesJob = propertyUseCases.getProperties()
            .onEach { properties ->
                _state.value = state.value.copy(properties = properties)
            }
            .launchIn(viewModelScope)
    }

//    private fun getPropertyTypes() {
//        getPropertyTypesJob?.cancel()
//        getPropertyTypesJob = propertyUseCases.getAllPropertyTypes()
//            .onEach { types ->
//                _state.value = state.value.copy(availableTypes = types)
//            }
//            .launchIn(viewModelScope)
//    }
}