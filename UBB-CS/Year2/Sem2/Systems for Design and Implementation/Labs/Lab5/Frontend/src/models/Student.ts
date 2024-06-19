import { Group } from './Group';

export interface Student{
    id?: number;
    firstname: string;
    name: string;
    CNP: number;
    favorite_colour: string;
    GroupId?: Group | number;
}