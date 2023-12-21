package com.example.backend.domain;

import com.fasterxml.jackson.annotation.JsonFormat;
import com.fasterxml.jackson.annotation.JsonIgnore;
import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.Date;

@SuppressWarnings("JpaDataSourceORMInspection")
@Entity
@Data
@NoArgsConstructor
@AllArgsConstructor
@Builder
@Table(name="stay_date")
public class StayDate {
    @Id
    @GeneratedValue(strategy = GenerationType.SEQUENCE, generator = "stay_date_generator")
    @SequenceGenerator(name = "stay_date_generator", sequenceName = "stay_date_seq")
    private Long id;
    @JsonFormat(pattern = "dd-MM-yyyy")
    private Date startDate;
    @JsonFormat(pattern = "dd-MM-yyyy")
    private Date endDate;
    @ManyToOne
    @JoinColumn(name = "destination_id")
    @JsonIgnoreProperties("stayDates")
    private Destination destination;
}
