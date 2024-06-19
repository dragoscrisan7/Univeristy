package com.example.backend.Tests;

import com.example.backend.domain.Destination;
import com.example.backend.domain.User;
import com.example.backend.repository.IDestinationRepository;
import com.example.backend.service.DestinationService;
import com.example.backend.service.IDestinationService;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.TestConfiguration;
import org.springframework.boot.test.mock.mockito.MockBean;
import org.springframework.context.annotation.Bean;
import org.springframework.stereotype.Repository;
import org.springframework.test.context.junit4.SpringRunner;

import java.util.*;
import java.util.stream.Collectors;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.when;

@RunWith(SpringRunner.class)
@SuppressWarnings("SpringJavaInjectionPointsAutowiringInspection")
public class DestinationServiceTests {
    @TestConfiguration
    static class DestinationServiceTestsContextConfiguration {
        @Bean
        public IDestinationService destinationService() {
            return new DestinationService();
        }
    }

    @Autowired
    private IDestinationService service;
    @MockBean
    private IDestinationRepository repository;

    public void setUp() {
        User user1 = new User("user1", "p1", "email");
        User user2 = new User("user2", "p2", "gmail");
        List<User> users = List.of(
                user1,
                user2
        );
        List<Destination> publicDestinations = List.of(new Destination("type1",user1),
                new Destination("type1", user1),
                new Destination("type1", user1),
                new Destination("type2", user2)
        );
        List<Destination> privateDestinations = List.of(
                new Destination("type1",user1)
        );

        when(repository.findAll())
                .thenReturn(publicDestinations);
        when(repository.findAllByType("private"))
                .thenReturn(privateDestinations);
        when(repository.findAllByTypeAndUser("private", users.get(0)))
                .thenReturn(Collections.singletonList(privateDestinations.get(0)));

        when(repository.findAllByTypeAndUser("private", users.get(1)))
                .thenReturn(privateDestinations);
    }
    public void testFindPublicDestinations() {
        List<Destination> publicDestinations = service.findPublicDestinations();
        assertEquals(3, publicDestinations.size());
    }

    @Test
    public void testAddPublicDestination() {
        Destination newDestination = new Destination("type3", new User("user3", "p3", "example"));
        when(repository.save(newDestination)).thenReturn(newDestination);

        Destination addedDestination = service.addPublicDestination(newDestination);
        assertEquals(newDestination, addedDestination);
    }

    @Test
    public void testFindPrivateDestinations() {
        String username = "user1";
        List<Destination> privateDestinations = service.findPrivateDestinations(username);
        assertEquals(1, privateDestinations.size());
    }

    @Test
    public void testAddPrivateDestination() {
        String username = "user1";
        Destination newDestination = new Destination("type2", new User(username, "p1", "email"));
        when(repository.save(newDestination)).thenReturn(newDestination);

        Destination addedDestination = service.addPrivateDestination(username, newDestination);
        assertEquals(newDestination, addedDestination);
    }

    @Test
    public void testGetDestination() {
        Long id = 1L;
        Destination destination = new Destination("type1", new User("user1", "p1", "email"));
        when(repository.findById(id)).thenReturn(Optional.of(destination));

        Destination retrievedDestination = service.getDestination(id);
        assertEquals(destination, retrievedDestination);
    }
}
