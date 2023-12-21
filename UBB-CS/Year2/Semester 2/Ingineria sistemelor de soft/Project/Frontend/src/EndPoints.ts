import { ServerSettings } from "./ServerSettings";

export class EndPoints {

    static ROOT = "/";
    static HOME = "/home"
    static AUTH = "/auth";
    static DESTINATION = "/destinations";

    static CREATE_PUBLIC_ENTRY = "/create/public";
    static CREATE_PRIVATE_ENTRY = "/create/private";

    static backendEndPoint(frontend: string) : string {
        return ServerSettings.API_ENDPOINT +  "/api" + frontend;
    }

    static registerUser() : string {
        return this.AUTH + "/register";
    }

    static loginUser() : string {
        return this.AUTH + "/login";
    }

    static publicDestination() : string {
        return this.DESTINATION + "/public";
    }

    static privateDestination() : string {
        return this.DESTINATION + "/private";
    }

    static getDestination(id: string) : string {
        return this.DESTINATION + "/public/" + id
    }

} 