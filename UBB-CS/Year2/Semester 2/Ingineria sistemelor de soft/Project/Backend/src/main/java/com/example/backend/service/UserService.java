package com.example.backend.service;

import com.example.backend.config.SecurityConfig;
import com.example.backend.domain.Authority;
import com.example.backend.domain.Destination;
import com.example.backend.domain.RegisterRequest;
import com.example.backend.domain.User;
import com.example.backend.repository.IAuthorityRepository;
import com.example.backend.repository.IUserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

@Service
public class UserService implements IUserService {

    @Autowired
    private IUserRepository userRepository;
    @Autowired
    private IAuthorityRepository authorityRepository;

    @Override
    public User register(RegisterRequest request) throws Exception {
        String password = SecurityConfig.passwordEncoder().encode(request.getPassword());
        String username = request.getUsername();
        String email = request.getEmail();

        Optional<User> foundUser = userRepository.findByEmail(email);

        if (foundUser.isPresent() && foundUser.get().isEnabled()) {
            throw new Exception("Email " + email + " is already used");
        }

        foundUser = userRepository.findByUsername(username);

        if (foundUser.isPresent()) {
            throw new Exception("Username " + username + " is already used");
        }

        Authority authority = authorityRepository.findFirstByRole("REGULAR").orElseThrow();
        User newUser = new User(null, username, password, email, List.of(authority), new ArrayList<>());

        return userRepository.save(newUser);
    }

    @Override
    public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
        return userRepository.findByUsername(username)
                .orElseThrow(
                        () -> new UsernameNotFoundException("User with username " + username + " not found.")
                );
    }

    @Override
    public UserDetails loadUserByEmail(String email) {
        return userRepository.findByEmail(email)
                .orElseThrow(
                        () -> new UsernameNotFoundException("User with email " + email + " not found")
                );
    }
}
