// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract Degree {
    address public owner;
    string public degreeName;
    uint256 public dateOfIssuance;

    enum CredentialStatus {
        Active,
        Expired,
        Revoked
    }

    CredentialStatus public status;

    constructor(string memory _degreeName, uint256 _dateOfIssuance) {
        owner = msg.sender;
        degreeName = _degreeName;
        dateOfIssuance = _dateOfIssuance;
        status = CredentialStatus.Active;
    }
}
