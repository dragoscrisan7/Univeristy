package com.example.backend.repository;

import com.example.backend.domain.Destination;
import com.example.backend.domain.User;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface IDestinationRepository extends JpaRepository<Destination, Long> {
    List<Destination> findAllByType(String type);
    List<Destination> findAllByTypeAndUser(String type, User user);
}
