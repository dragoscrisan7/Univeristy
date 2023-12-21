import * as Authentication from '../helpers/Authentication';
import { EndPoints } from "../EndPoints";
import { TableApplicationBar } from "./TableApplicationBar";
import { ShowAll } from "./ShowAll";

export const DisplayPublicDestinations = () => {
    return (
        <div>
            <TableApplicationBar has_add={Authentication.hasAuthRole("ADMIN")} create_endpoint={EndPoints.CREATE_PUBLIC_ENTRY}></TableApplicationBar>
            <ShowAll create_endpoint={EndPoints.CREATE_PUBLIC_ENTRY} request_endpoint={EndPoints.publicDestination()} 
            add_from_template={!Authentication.hasAuthRole("ADMIN")} />
        </div>
    )
}