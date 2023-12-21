package com.example.backend.controller;

import com.example.backend.domain.Destination;
import com.example.backend.jwt.JwtTokenUtil;
import com.example.backend.service.IDestinationService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Objects;

@RestController
@RequestMapping("/api/destinations")
public class DestinationController {
    @Autowired
    IDestinationService destinationService;

    @GetMapping("/public")
    public List<Destination> findPublicDestinations() {
        return destinationService.findPublicDestinations();
    }

    @PostMapping("/public")
    public Destination addPublicDestination(@RequestBody Destination destination) {
        return destinationService.addPublicDestination(destination);
    }

    @GetMapping("/public/{id}")
    public Destination getDestination(@PathVariable("id") Long id) {
        return destinationService.getDestination(id);
    }

    @GetMapping("/private")
    public ResponseEntity<?> findPrivateDestinations(@RequestHeader(HttpHeaders.AUTHORIZATION) String header) {
        String username = JwtTokenUtil.getUsernameFromAuthorizationHeader(header);
        if (Objects.isNull(username))
            return ResponseEntity.status(HttpStatus.FORBIDDEN).body(new Object() {
                public String getMessage() {return "not authorized";}
            });

        return ResponseEntity.ok(destinationService.findPrivateDestinations(username));
    }

    @PostMapping("/private")
    public ResponseEntity<?> addPrivateDestination(@RequestHeader(HttpHeaders.AUTHORIZATION) String header,
                                                   @RequestBody Destination destination) {
        String username = JwtTokenUtil.getUsernameFromAuthorizationHeader(header);
        if (Objects.isNull(username))
            return ResponseEntity.status(HttpStatus.FORBIDDEN).body(new Object() {
                public String getMessage() {return "not authorized";}
            });

        return ResponseEntity.ok(destinationService.addPrivateDestination(username, destination));
    }
}
