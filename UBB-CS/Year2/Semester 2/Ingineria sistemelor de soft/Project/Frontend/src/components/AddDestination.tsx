import React, { useEffect, useState } from "react";
import { Destination } from "../model/Destination";
import { EndPoints } from "../EndPoints";
import * as Authentication from '../helpers/Authentication';
import { AxiosError } from "axios";
import { useNavigate } from "react-router-dom";
import { Box, Button, TextField } from "@mui/material";
import { ApplicationBar } from "./ApplicationBar";
import { StayDate } from "../model/StayDate";
import { DataGrid, GridActionsCellItem, GridColDef, GridRenderCellParams, GridRowParams, GridTreeNodeWithRender } from "@mui/x-data-grid";
import DeleteIcon from '@mui/icons-material/Delete';
import './AddDestination.css'

export const AddDestination = (props: any) => {
    const [element, setElement] = useState<Destination>(new Destination())
    const [new_stay_date, set_new_stay_date] = useState<StayDate>(new StayDate())
    const [formSubmitted, setFormSubmitted] = useState(false)
    const [endDateError, setEndDateError] = useState(false)
    const nagivate_details = useNavigate()

    useEffect(() => {
        if (props.initial_get) {
            Authentication.make_request('GET', props.initial_get_endpoint, "")
            .then((data) => {
                console.log(data)
                let response_data = data.data;
                response_data.stayDates = [];
                setElement(response_data)
            })
            .catch((error: AxiosError) => {
                console.log(error)
            })
        }
    }, [])

    const commit_update = () => {
        setFormSubmitted(true)
        let submit = true
        if (element.title.trim() === '') {
            submit = false;
        }
        if (element.description.trim() === '') {
            submit = false;
        }
        if (element.geolocation.trim() === '') {
            submit = false;
        }
        if (element.imagePath.trim() === '') {
            submit = false;
        }
        if (element.stayDates.length === 0) {
            submit = false;
        }

        if (submit) {
            Authentication.make_request('POST', EndPoints.backendEndPoint(props.request_endpoint), element)
            .then((data) => { setElement(data.data) })
            .catch(
                (error: AxiosError) => {
                    console.log(error);
                }
            );
            nagivate_details(props.update_endpoint)
        }
    }

    const add_stay_date = () => {
        let copy = element.stayDates.slice()
        let copied_stay_date = new StayDate()
        copied_stay_date.id = new_stay_date.id
        copied_stay_date.startDate = new_stay_date.startDate
        copied_stay_date.endDate = new_stay_date.endDate
        copy.push(copied_stay_date)
        setElement({ ...element, stayDates: copy });
        new_stay_date.id = new_stay_date.id + 1;
        set_new_stay_date(new_stay_date)

        setEndDateError(false)
    }

    const delete_stay_date = (id: number) => {
        let index = element.stayDates.findIndex((stayDate) => stayDate.id === id);
        let new_stay_dates = [...element.stayDates];
        new_stay_dates.splice(index, 1);
        setElement({ ...element, stayDates: new_stay_dates });
    }

    let stay_dates_columns : GridColDef[] = [
        {
            field: 'startDate',
            headerName: 'Start Date',
            width: 160,
            renderCell: (params: GridRenderCellParams<any, any, any, GridTreeNodeWithRender>) => (             
                <React.Fragment>
                    <p>{
                    new Date(params.row.startDate).toLocaleString(
                                'en-UK',
                                {
                                    year: "numeric",
                                    month: "long",
                                    day: "numeric",
                                }
                    )}</p>
                </React.Fragment>
            ) 
        },
        {
            field: 'endDate',
            headerName: 'End Date',
            width: 160,
            renderCell: (params: GridRenderCellParams<any, any, any, GridTreeNodeWithRender>) => (             
                <React.Fragment>
                    <p>{
                    new Date(params.row.endDate).toLocaleString(
                                'en-UK',
                                {
                                    year: "numeric",
                                    month: "long",
                                    day: "numeric",
                                }
                    )}</p>
                </React.Fragment>
            ) 
        },
        {
            field: 'id',
            headerName: 'Remove',
            sortable: false,
            type: 'actions',
            width: 100,
            getActions: (params: GridRowParams) => {
                return [
                    <GridActionsCellItem icon={<DeleteIcon/>} onClick={
                        () => delete_stay_date(parseInt(params.id.valueOf().toString()))
                    } label="Delete"/>,
                ]
            }
        }
    ];

    return (
        <React.Fragment>
            <ApplicationBar />        
            <div style={{ display: 'flex', flexDirection: 'column', alignItems: 'center', justifyContent: 'center', minHeight: '80vh' }}>
                <TextField label="Title" variant="standard" value={element.title} style={{ width: '35%' }} 
                error={formSubmitted && element.title.trim() === ''}
                helperText={formSubmitted && element.title.trim() === '' ? 'Title is required' : ''}
                onChange={(event)=>{
                    setElement({...element, title: event.target.value})
                }}/>
                <br></br>
                <TextField label="Geolocation" variant="standard" value={element.geolocation} style={{ width: '35%' }} 
                error={formSubmitted && element.geolocation.trim() === ''}
                helperText={formSubmitted && element.geolocation.trim() === '' ? 'Geolocation is required' : ''}
                onChange={(event)=>{
                    setElement({...element, geolocation: event.target.value})
                }}/>
                <br></br>
                <TextField label="Image URL" variant="standard" value={element.imagePath} style={{ width: '35%' }} 
                error={formSubmitted && element.imagePath.trim() === ''}
                helperText={formSubmitted && element.imagePath.trim() === '' ? 'Image URL is required' : ''}
                onChange={(event)=>{
                    setElement({...element, imagePath: event.target.value})
                }}/>
                <br></br>
                <TextField label="Description" variant="standard" value={element.description} style={{ width: '35%' }} 
                error={formSubmitted && element.description.trim() === ''}
                helperText={formSubmitted && element.description.trim() === '' ? 'Description is required' : ''}
                onChange={(event)=>{
                    setElement({...element, description: event.target.value})
                }}/>
                <br></br>
                
                <p>Stay Dates</p>
                <Box sx={{ height: '100%', width: 425 }}>
                    <DataGrid
                        getRowId={(row: any) => row.id}
                        rows={element.stayDates}
                        columns={stay_dates_columns}
                        rowCount={element.stayDates.length}
                        pageSizeOptions={[10]}
                        autoHeight={true}
                        components={{
                            NoRowsOverlay: () => (
                              <div style={{ width: '100%', textAlign: 'center', padding: '16px' }}>
                                {element.stayDates.length === 0 ? (
                                  <span style={{ color: 'red' }}>No Stay Dates Available</span>
                                ) : (
                                  'No Rows'
                                )}
                              </div>
                            ),
                        }}
                    />
                </Box>
                <br></br>
                
                <p>New Stay Date</p>
                <TextField InputLabelProps={{ shrink: true }} type="date" label="Start Date" variant="standard" style={{ width: '35%' }} onChange={(event)=>{
                        new_stay_date.startDate = new Date(event.target.value)
                        set_new_stay_date(new_stay_date)
                }}/>
                <br></br>
                <TextField InputLabelProps={{ shrink: true }} type="date" label="End Date" variant="standard" style={{ width: '35%' }} 
                error={endDateError}
                helperText={endDateError ? 'End Date should be later than Start Date' : ''}
                onChange={(event)=>{
                        new_stay_date.endDate = new Date(event.target.value)
                        set_new_stay_date(new_stay_date)
                        if (new_stay_date.endDate < new_stay_date.startDate) {
                            setEndDateError(true)
                        }
                        else {
                            setEndDateError(false)
                        }
                }}/>
                <br></br>
                <Button onClick={add_stay_date}>
                    Add Stay Date
                </Button>

                <br></br>
                <Button onClick={commit_update}>
                    Create Destination                
                </Button>
            </div>        
        </React.Fragment>
    )
}