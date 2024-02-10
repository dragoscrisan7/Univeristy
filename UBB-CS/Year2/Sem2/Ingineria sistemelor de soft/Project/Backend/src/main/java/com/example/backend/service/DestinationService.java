package com.example.backend.service;

import com.example.backend.domain.Destination;
import com.example.backend.domain.User;
import com.example.backend.repository.IDestinationRepository;
import com.example.backend.repository.IUserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

@Service
public class DestinationService implements IDestinationService {
    @Autowired
    private IDestinationRepository destinationRepository;
    @Autowired
    private IUserRepository userRepository;

    @Override
    public List<Destination> findPublicDestinations() {
        return destinationRepository.findAllByType("PUBLIC");
    }

    @Override
    public Destination addPublicDestination(Destination destination) {
        destination.setUser(null);
        destination.setType("PUBLIC");
        Destination returnedDestination = destinationRepository.save(destination);
        returnedDestination.getStayDates().forEach(stayDate -> stayDate.setDestination(returnedDestination));
        return destinationRepository.save(returnedDestination);
    }

    @Override
    public List<Destination> findPrivateDestinations(String username) {
        User user = userRepository.findByUsername(username).orElseThrow();
        return destinationRepository.findAllByTypeAndUser("PRIVATE", user);
    }

    @Override
    public Destination addPrivateDestination(String username, Destination destination) {
        User user = userRepository.findByUsername(username).orElseThrow();
        destination.setId(null);
        destination.setUser(user);
        destination.setType("PRIVATE");
        destination.getStayDates().forEach(stayDate -> stayDate.setDestination(destination));
        Destination returnedDestination = destinationRepository.save(destination);
        returnedDestination.getStayDates().forEach(stayDate -> stayDate.setDestination(returnedDestination));
        return destinationRepository.save(returnedDestination);
    }

    @Override
    public Destination getDestination(Long id) {
        return destinationRepository.findById(id).orElseThrow();
    }
}
