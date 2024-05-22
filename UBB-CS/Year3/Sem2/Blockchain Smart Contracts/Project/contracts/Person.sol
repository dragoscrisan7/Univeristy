// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

import "./AcademicCredential.sol";

contract Person {
    address public owner;
    string public name;
    AcademicCredential[] public academicCredentials;

    event AcademicCredentialReceived(address indexed credential);

    constructor(string memory _name) {
        owner = msg.sender;
        name = _name;
    }

    function receiveAcademicCredential(address _credential) external {
        AcademicCredential credentialContract = AcademicCredential(_credential);
        require(
            credentialContract.isPerson(address(this)),
            "Person is not authorized to receive this credential"
        );
        academicCredentials.push(credentialContract);
        emit AcademicCredentialReceived(_credential);
    }

    function getAcademicCredentials()
        external
        view
        returns (AcademicCredential[] memory)
    {
        return academicCredentials;
    }
}
