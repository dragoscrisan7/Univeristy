import { Box, Toolbar, Button, AppBar } from "@mui/material";
import { Link } from "react-router-dom";
import { EndPoints } from "../EndPoints";

export const ApplicationBar = () => {
    return <Box sx={{ display: 'flex', justifyContent: 'space-between' }}>
        <AppBar position="sticky">
            <Toolbar>
                <Button id="goHomeButton" color="inherit" sx={{flexGrow: 1}} component={Link} to={EndPoints.HOME}>Home</Button>
                <Button color="inherit" sx={{flexGrow: 1}} component={Link} to={EndPoints.publicDestination()}>Public List</Button>
                <Button color="inherit" sx={{flexGrow: 1}} component={Link} to={EndPoints.privateDestination()}>Bucket List</Button>
                <Button id="logoutButton" color="inherit" sx={{flexGrow: 1}} component={Link} to={EndPoints.ROOT}>Logout</Button>
            </Toolbar>
        </AppBar>
    </Box>;
}