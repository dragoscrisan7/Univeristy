import { StayDate } from "./StayDate";

export class Destination {
    id: number = -1;
    type: string = "";
    geolocation: string = "";
    title: string = "";
    imagePath: string = "";
    description: string = "";
    stayDates: StayDate[] = [];
}