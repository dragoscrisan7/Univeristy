// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract AcademicCredential {
    mapping(address => bool) public isUniversity;
    mapping(address => bool) public isPerson;
    mapping(address => bool) public isDegree;

    event UniversityAdded(address indexed university);
    event PersonAdded(address indexed person);
    event DegreeAdded(address indexed degree);

    function addUniversity(address _university) external {
        require(!isUniversity[_university], "University already registered");
        isUniversity[_university] = true;
        emit UniversityAdded(_university);
    }

    function addPerson(address _person) external {
        require(!isPerson[_person], "Person already registered");
        isPerson[_person] = true;
        emit PersonAdded(_person);
    }

    function addDegree(address _degree) external {
        require(!isDegree[_degree], "Degree already registered");
        isDegree[_degree] = true;
        emit DegreeAdded(_degree);
    }
}
