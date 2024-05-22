const CredentialManager = artifacts.require("CredentialManager");
const University = artifacts.require("University");
const Person = artifacts.require("Person");
const AcademicCredential = artifacts.require("AcademicCredential");

module.exports = function(deployer) {
  deployer.deploy(CredentialManager);
  deployer.deploy(University, "University of Babes Bolyai");
  deployer.deploy(Person);
  deployer.deploy(AcademicCredential);
};