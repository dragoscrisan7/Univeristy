import { AddDestination } from "./AddDestination"

export const CreateDestination = (props: any) => {
    return <AddDestination request_endpoint={props.request_endpoint} update_endpoint={props.update_endpoint} initial_get={false} />
}