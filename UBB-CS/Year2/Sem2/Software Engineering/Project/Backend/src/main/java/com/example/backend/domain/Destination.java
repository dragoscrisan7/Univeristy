package com.example.backend.domain;

import com.fasterxml.jackson.annotation.JsonIgnore;
import jakarta.persistence.*;
import lombok.*;

import java.util.ArrayList;
import java.util.List;

@SuppressWarnings("JpaDataSourceORMInspection")
@Entity
@Data
@NoArgsConstructor
@AllArgsConstructor
@Builder
@Table(name = "destination")
public class Destination {
    @Id
    @GeneratedValue(strategy = GenerationType.SEQUENCE, generator = "destination_generator")
    @SequenceGenerator(name = "destination_generator", sequenceName = "destination_seq")
    private Long id;
    @Column(name="destination_type")
    private String type;
    private String geolocation;
    private String title;
    private String imagePath;
    private String description;
    @OneToMany(mappedBy = "destination", cascade = CascadeType.ALL, orphanRemoval = true)
    private List<StayDate> stayDates;
    @ManyToOne
    private User user;

    public Destination(String type, User user){
        this.type = type;
        this.user= user;
        this.stayDates = new ArrayList<>();
    }
}
