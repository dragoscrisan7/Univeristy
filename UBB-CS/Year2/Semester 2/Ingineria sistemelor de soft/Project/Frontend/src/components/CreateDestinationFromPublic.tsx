import { AddDestination } from "./AddDestination"
import { useParams } from "react-router-dom";
import { EndPoints } from "../EndPoints";

export const CreateDestinationFromPublic = (props: any) => {
    const {id} = useParams()

    if (id != undefined) {
        return <AddDestination request_endpoint={props.request_endpoint} update_endpoint={EndPoints.privateDestination()} initial_get={true} 
        initial_get_endpoint={EndPoints.backendEndPoint(EndPoints.getDestination(id))} />
    }
    else {
        return <AddDestination request_endpoint={props.request_endpoint} update_endpoint={EndPoints.privateDestination()} initial_get={false} />
    }
}