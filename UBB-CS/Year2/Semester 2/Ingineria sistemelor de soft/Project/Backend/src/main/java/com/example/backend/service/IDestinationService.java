package com.example.backend.service;

import com.example.backend.domain.Destination;
import com.example.backend.domain.User;

import java.util.List;

public interface IDestinationService {
    List<Destination> findPublicDestinations();
    Destination addPublicDestination(Destination destination);
    List<Destination> findPrivateDestinations(String username);
    Destination addPrivateDestination(String username, Destination destination);
    Destination getDestination(Long id);
}
