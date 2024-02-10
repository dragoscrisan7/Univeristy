import { EndPoints } from "../EndPoints";
import { ShowAll } from "./ShowAll";
import { TableApplicationBar } from "./TableApplicationBar";

export const DisplayPrivateDestinations = () => {
    return <div>
        <TableApplicationBar has_add={true} create_endpoint={EndPoints.CREATE_PRIVATE_ENTRY}></TableApplicationBar>
        <ShowAll create_endpoint={EndPoints.CREATE_PRIVATE_ENTRY} request_endpoint={EndPoints.privateDestination()} 
        add_from_template={false} />
    </div>
}