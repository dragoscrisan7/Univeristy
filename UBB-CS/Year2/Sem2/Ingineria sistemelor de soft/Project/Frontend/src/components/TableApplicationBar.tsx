import { Box, AppBar, Toolbar, Button } from "@mui/material";
import { Link } from "react-router-dom";
import { EndPoints } from "../EndPoints";

export const TableApplicationBar = (props: any) => {
    const has_add = props.has_add;
    let add_button;
    if (has_add) {
        add_button = <Button color="inherit" sx={{flexGrow: 1}} component={Link} to={props.create_endpoint}>Add Destination</Button>
    }


    return <Box sx={{ display: 'flex', justifyContent: 'space-between' }}>
        <AppBar position="sticky">
            <Toolbar>
                <Button id="goHomeButton" color="inherit" sx={{flexGrow: 1}} component={Link} to={EndPoints.HOME}>Home</Button>
                {add_button}
                <Button id="logoutButton" color="inherit" sx={{flexGrow: 1}} component={Link} to={EndPoints.ROOT}>Logout</Button>
            </Toolbar>
        </AppBar>
    </Box>;
}