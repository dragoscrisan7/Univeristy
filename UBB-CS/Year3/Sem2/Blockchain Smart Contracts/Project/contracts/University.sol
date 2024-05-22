// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

import "./Degree.sol";
import "./AcademicCredential.sol";
import "./Person.sol";

contract University {
    address public owner;
    string public name;

    event AcademicCredentialIssued(
        address indexed person,
        address indexed credential
    );

    modifier onlyOwner() {
        require(msg.sender == owner, "Only the owner can call this function");
        _;
    }

    constructor(string memory _name) {
        owner = msg.sender;
        name = _name;
    }

    function issueAcademicCredential(
        address _person,
        string memory _degreeName,
        uint256 _dateOfIssuance
    ) public onlyOwner returns (address) {
        AcademicCredential academicCredential = new AcademicCredential();
        Degree degree = new Degree(_degreeName, _dateOfIssuance);
        academicCredential.addDegree(address(degree));
        academicCredential.addUniversity(msg.sender);

        Person personContract = Person(_person);
        academicCredential.addPerson(_person);
        personContract.receiveAcademicCredential(address(academicCredential));

        emit AcademicCredentialIssued(_person, address(academicCredential));

        return address(academicCredential);
    }
}
