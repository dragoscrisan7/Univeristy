package com.example.backend.Tests;

import com.example.backend.domain.User;
import com.example.backend.repository.IUserRepository;
import com.example.backend.service.UserService;
import com.example.backend.service.IUserService;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.context.TestConfiguration;
import org.springframework.boot.test.mock.mockito.MockBean;
import org.springframework.context.annotation.Bean;
import org.springframework.stereotype.Repository;
import org.springframework.test.context.junit4.SpringRunner;

import org.springframework.security.core.userdetails.UserDetails;
import com.example.backend.domain.RegisterRequest;
import static org.mockito.ArgumentMatchers.any;

import java.util.*;
import java.util.stream.Collectors;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.when;

@RunWith(SpringRunner.class)
@SpringBootTest
public class UserServiceTests {

    @TestConfiguration
    static class UserServiceTestsContextConfiguration {
        @Bean
        public IUserService userService() {
            return new UserService();
        }
    }

    @Autowired
    private IUserService userService;

    @MockBean
    private IUserRepository userRepository;

    @Before
    public void setUp() {
        // Set up mock data
        User user1 = new User("user1", "email1@example.com", "password1");
        User user2 = new User("user2", "email2@example.com", "password2");

        when(userRepository.findByEmail("email1@example.com")).thenReturn(Optional.of(user1));
        when(userRepository.save(any(User.class))).thenReturn(user2);
    }

    @Test
    public void testLoadUserByEmail() {
        String email = "email1@example.com";

        User user = new User("user1", "password1", email); // Update with appropriate constructor
        UserDetails userDetails = user; // User class already implements UserDetails interface
        when(userRepository.findByEmail(email)).thenReturn(Optional.of(user));

        UserDetails loadedUser = userService.loadUserByEmail(email);
        assertEquals(userDetails, loadedUser);
    }

    @Test
    public void testRegister() throws Exception {
        RegisterRequest registerRequest = new RegisterRequest("username", "email@example.com", "password");

        User newUser = new User(registerRequest.getUsername(), registerRequest.getEmail(), registerRequest.getPassword());
        when(userRepository.save(any(User.class))).thenReturn(newUser);

        User registeredUser = userService.register(registerRequest);
        assertEquals(newUser, registeredUser);
    }
}
