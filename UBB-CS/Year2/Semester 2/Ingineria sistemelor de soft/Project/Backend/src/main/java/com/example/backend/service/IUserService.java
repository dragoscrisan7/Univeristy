package com.example.backend.service;

import com.example.backend.domain.RegisterRequest;
import com.example.backend.domain.User;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;

public interface IUserService extends UserDetailsService {
    UserDetails loadUserByEmail(String email);
    User register(RegisterRequest request) throws Exception;
}
