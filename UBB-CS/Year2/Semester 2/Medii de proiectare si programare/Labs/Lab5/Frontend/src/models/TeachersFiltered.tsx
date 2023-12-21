import { Teacher } from "./Teacher";

export interface TeachersFiltered{
    id: Teacher | number;
    firstname: string;
    TeachingSubject: string;
    nr_of_classes: number;
}