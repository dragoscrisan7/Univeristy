package com.example.backend.Tests;

import com.example.backend.domain.User;
import com.example.backend.repository.IUserRepository;
import com.example.backend.domain.Destination;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.orm.jpa.DataJpaTest;
import org.springframework.boot.test.autoconfigure.orm.jpa.TestEntityManager;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Slice;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringRunner;
import org.springframework.test.context.support.AnnotationConfigContextLoader;

import java.util.List;
import java.util.Optional;

import static org.junit.jupiter.api.Assertions.*;

@RunWith(SpringRunner.class)
@DataJpaTest
@SuppressWarnings("SpringContextConfigurationInspection")
@ContextConfiguration(loader = AnnotationConfigContextLoader.class)
public class UsersRepositoryTests {
    @Autowired
    private TestEntityManager entityManager;
    @Autowired
    private IUserRepository repository;

    @Test
    public void test() {
        User user1 = new User((long) 1,"a", "", "email");
        User user3 = new User((long) 3,"d", "", "gmail1");

        List<User> users = List.of(new User("a", "", "email"),
                new User("b","","gmail2"),
                new User("d", "", "gmail1"),
                new User("c","","gmail3")
        );

        for (User user : users)
            entityManager.persist(user);
        entityManager.flush();

        Optional<User> filteredUsers = repository.findByUsername("a");
        assertTrue(filteredUsers.isPresent());
        assertEquals(user1, filteredUsers.get());

        filteredUsers = repository.findByEmail("gmail1");
        assertTrue(filteredUsers.isPresent());
        assertEquals(user3, filteredUsers.get());

        Slice<User> usersSlice = repository.findAllBy(PageRequest.of(0, 1));
        assertEquals(1, usersSlice.getContent().size());
        assertTrue(usersSlice.getContent().contains(user1) || usersSlice.getContent().contains(user3));
    }
}
