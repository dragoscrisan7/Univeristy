import { Student } from "./Student";

export interface Group{
    id: number;
    groupNr: number;
    specialization: string;
    language: string;
    year: number;
    students: Student;
}