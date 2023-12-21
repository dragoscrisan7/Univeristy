import { useEffect, useState } from 'react'
import { useNavigate } from 'react-router-dom'
import { Box, CircularProgress, Snackbar } from '@mui/material';
import React from 'react';
import { DataGrid, GridActionsCellItem, GridColDef, GridRenderCellParams, GridRowParams, GridTreeNodeWithRender } from '@mui/x-data-grid';
import EditIcon from '@mui/icons-material/Edit';
import * as Authentication from '../helpers/Authentication';
import { AxiosError } from 'axios';
import { EndPoints } from '../EndPoints';
import { StayDate } from '../model/StayDate';

export const ShowAll = (props: any) => {
    const navigate_details = useNavigate()

    const [elements, setElements] = useState<any>()
    const [loading, setLoading] = useState<boolean>(false)

    const handleSnackbarClose = () => {
        setLoading(false)
    };

    const update_elements = () => {
        setLoading(true)
        Authentication.make_request('GET', EndPoints.backendEndPoint(props.request_endpoint), "")
        .then((data) => { 
            console.log(data) 
            let response_data = data.data; 
            setElements(response_data);
            setLoading(false)
        }
        )
        .catch(
            (error: AxiosError) => {
                console.log(error);
                setLoading(false)
            }
        );
    }  

    useEffect(() => {
        update_elements()
    }, [props.request_endpoint])

    let table_columns : GridColDef[] = [
        {
            field: 'title',
            headerName: 'Title',
            width: 160,
            headerAlign: 'center',
            align: 'center'
        },
        {
            field: 'geolocation',
            headerName: 'Geolocation',
            width: 160,
            headerAlign: 'center',
            align: 'center'
        },
        {
            field: 'imagePath',
            headerName: 'Image',
            width: 160,
            headerAlign: 'center',
            align: 'center',
            renderCell: (params) => (
                <img src={params.value} alt="Image" style={{ width: '100%', height: 'auto' }} />
            ),
        },
        {
            field: 'description',
            headerName: 'Description',
            width: 160,
            headerAlign: 'center',
            align: 'center'
        },
        {
            field: 'stayDates',
            headerName: 'Stay Dates',
            width: 260,
            headerAlign: 'center',
            align: 'center',
            renderCell: (params: GridRenderCellParams<any, any, any, GridTreeNodeWithRender>) => (
                
                <React.Fragment>
                    <div style={{ display: 'flex', flexDirection: 'column' }}>
                        {params.row.stayDates.map((stayDate: StayDate, index: number) => (
                        <React.Fragment key={index}>
                            <div>
                                {
                                stayDate.startDate.toLocaleString('en-UK', {
                                    year: "numeric",
                                    month: "long",
                                    day: "numeric",
                                })
                                }
                                /
                                {
                                stayDate.endDate.toLocaleString('en-UK', {
                                    year: "numeric",
                                    month: "long",
                                    day: "numeric",
                                })
                                }
                            </div>
                        </React.Fragment>
                        ))}
                    </div>
                </React.Fragment>
            ) 
        }
    ];

    const action_column : GridColDef = {
        field: 'id',
        headerName: 'Create From',
        sortable: false,
        type: 'actions',
        width: 160,
        headerAlign: 'center',
        align: 'center',
        getActions: (params: GridRowParams) => {
            return [
                <GridActionsCellItem icon={<EditIcon/>} onClick={ 
                    () => navigate_details(props.create_endpoint + "/" + parseInt(params.id.valueOf().toString()))
                } label="Edit" />
            ]
        }
    }

    if (props.add_from_template) {
        table_columns.push(action_column)
    }

    let data_grid;
    if (elements != undefined) {
        data_grid = (
            <React.Fragment>
                <Box sx={{ height: '100%', width: '100%' }}>
                    <DataGrid
                        getRowId={(row: any) => row.id}
                        rows={elements}
                        columns={table_columns}
                        rowCount={elements.length}
                        pageSizeOptions={[10]}
                        autoHeight={true}
                        rowHeight={120}
                    />
                </Box>
            </React.Fragment>
        )
    }

    return (
        <React.Fragment>
        <div style={{ display: 'flex', flexDirection: 'column', alignItems: 'center' }}>
            <div style={{ marginTop: '100px', flexGrow: 1 }}>{data_grid}</div>

            <Snackbar
                open={loading}
                onClose={handleSnackbarClose}
                message="Loading..."
                anchorOrigin={{
                vertical: 'bottom',
                horizontal: 'center',
                }}
            >
                <CircularProgress color="inherit" />
            </Snackbar>
        </div>
    </React.Fragment>
    )
}