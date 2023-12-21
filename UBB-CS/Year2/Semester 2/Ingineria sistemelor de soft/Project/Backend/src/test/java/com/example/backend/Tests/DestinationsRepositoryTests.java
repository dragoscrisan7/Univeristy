package com.example.backend.Tests;

import com.example.backend.domain.User;
import com.example.backend.repository.IDestinationRepository;
import com.example.backend.domain.Destination;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.orm.jpa.DataJpaTest;
import org.springframework.boot.test.autoconfigure.orm.jpa.TestEntityManager;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringRunner;
import org.springframework.test.context.support.AnnotationConfigContextLoader;

import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

@RunWith(SpringRunner.class)
@DataJpaTest
@SuppressWarnings("SpringContextConfigurationInspection")
@ContextConfiguration(loader = AnnotationConfigContextLoader.class)

public class DestinationsRepositoryTests {
    @Autowired
    private TestEntityManager entityManager;
    @Autowired
    private IDestinationRepository repository;

    @Test
    public void test() {
        var user1 = new User("1", "", "");
        var user2 = new User("2","","");
        entityManager.persist(user2);
        entityManager.persist(user1);
        List<Destination> destinations = List.of(new Destination("type1",user1),
                new Destination("type1",user1),
                new Destination("type2",user2)
        );

        for (Destination destination : destinations)
            entityManager.persist(destination);
        entityManager.flush();

        List<Destination> filteredDestinations = repository.findAllByType("type1");
        assertEquals(2, filteredDestinations.size());
        assertTrue(filteredDestinations.contains(destinations.get(0)));
        assertTrue(filteredDestinations.contains(destinations.get(1)));
        assertFalse(filteredDestinations.contains(destinations.get(2)));

        filteredDestinations = repository.findAllByTypeAndUser("type1", user1);
        assertEquals(2, filteredDestinations.size());

        filteredDestinations = repository.findAllByTypeAndUser("type3", user2);
        assertEquals(0, filteredDestinations.size());
    }
}

