import { Authority } from "./Authority";
import { Destination } from "./Destination";

export class User {
    id: number = -1;
    username: string = "";
    password: string = "";
    email: string = "";
    roles: Authority[] = [];
    destinations: Destination[] = [];
}