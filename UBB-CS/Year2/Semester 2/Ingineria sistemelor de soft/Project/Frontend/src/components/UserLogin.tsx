import { Button, Dialog, DialogActions, DialogContent, DialogContentText, DialogTitle, TextField } from '@mui/material';
import React, { useState } from 'react';
import { useNavigate } from 'react-router-dom';
import * as Authentication from '../helpers/Authentication';
import { AuthRequest } from '../model/AuthRequest';
import { AxiosError } from 'axios';
import { EndPoints } from '../EndPoints';

interface FailMessage {
    message: string;
}

// CSS styles for the container element
const containerStyle : React.CSSProperties = {
    display: 'flex',
    flexDirection: 'column',
    alignItems: 'center',
    justifyContent: 'center',
    height: '100vh', // Adjust the height as per your requirement
};


export const UserLogin = () => {
    const [username, setUsername] = useState<string>("")
    const [password, setPassword] = useState<string>("")
    const [display_error, setDisplayError] = useState<boolean>(false)
    const [error_message, setErrorMessage] = useState<string>("")
    const navigate_details = useNavigate()

    const handle_failed_dialog_open = () => {
        setDisplayError(true)
    }
    
    const handle_failed_dialog_close = () => {
        setDisplayError(false)
    }

    const login = () => {
        let login_request = new AuthRequest();
        login_request.password = password;
        login_request.username = username;

        Authentication.make_request('POST', EndPoints.backendEndPoint(EndPoints.loginUser()), login_request)
        .then(
            (response) => {
                console.log(response);
                Authentication.setAuth(response.data);
                if (Authentication.hasAuthRole("ADMIN")) {
                    // Go to the public list
                    navigate_details(EndPoints.publicDestination())
                }
                else {
                    // Go to the private list
                    navigate_details(EndPoints.privateDestination())
                }
            })
        .catch(
            (error: AxiosError) => {
                console.log(error);
                Authentication.setAuthHeader(null);
                if (error.response != null) {
                    setErrorMessage((error.response.data as FailMessage).message)
                    setDisplayError(true)
                }
                else {
                    setErrorMessage("Failed. Unknown error")
                    setDisplayError(true)
                }
            }
        );


    }

    let failed_dialog_element;
    if (display_error) {
        failed_dialog_element =
            <Dialog
                open={display_error}
                onClose={handle_failed_dialog_open}
                aria-labelledby="alert-dialog-title"
                aria-describedby="alert-dialog-description"
            >
            <DialogTitle id="alert-dialog-title">
                Failure
            </DialogTitle>
            <DialogContent>
                <DialogContentText id="alert-dialog-description">
                    {error_message}
                </DialogContentText>
            </DialogContent>
            <DialogActions>
                <Button onClick={handle_failed_dialog_close} autoFocus>
                    OK
                </Button>
            </DialogActions>
            </Dialog>
        
    }

    return (
        <div style={containerStyle}>
            <React.Fragment>
                <TextField inputProps={{data_testid: 'username'}} label="Username" variant="standard" defaultValue={username} onChange={(event: any)=>{
                    setUsername(event.target.value)
                }} />
                <br></br>
                <TextField inputProps={{data_testid: 'password'}} type="password" label="Password" variant="standard" defaultValue={password}
                 onChange={(event: any) => {
                    setPassword(event.target.value)
                }} />
                <br></br>
                <Button onClick={() => {login()}}>
                    Login
                </Button>

                {failed_dialog_element}
            </React.Fragment>
        </div>
    )
}