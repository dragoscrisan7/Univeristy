import { Button, Card, CardActions, CardContent, FormControl, IconButton, InputLabel, MenuItem, Select, SelectChangeEvent, TextField } from "@mui/material";
import { Container } from "@mui/system";
import { useEffect, useState } from "react";
import { Link, useNavigate, useParams } from "react-router-dom";
import EditIcon from "@mui/icons-material/Edit";
import DeleteForeverIcon from "@mui/icons-material/DeleteForever";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import axios from "axios";
import { Student } from "../../models/Student";
import { Group } from "../../models/Group";
import { BACKEND_API_URL } from "../../constants";

export const StudentUpdate = () => {
    const { studentId } = useParams();
    const navigate = useNavigate();
    const [groups, setGroups] = useState<Group[]>([])
    const [loading, setLoading] = useState(false);
    const [student, setStudent] = useState<Omit<Student, "id">>({
        firstname: '',
        name: '',
        CNP: 0,
        favorite_colour: '',
        GroupId: undefined,
      });

    useEffect(() => {
        const getGroups = async () => {
            setLoading(true);
            const response = await axios.get<Group[]>(`${BACKEND_API_URL}/groups/`);
            setGroups(response.data);
            setLoading(false);
        };
        getGroups();
        const fetchStudent = async () => {
            setLoading(true);
            const response = await axios.get<Student>(`${BACKEND_API_URL}/students/${studentId}/`);
            const student = response.data
            console.log(student.firstname + " " + student.name + " " + student.CNP + " " + student.favorite_colour + " " + student.GroupId)
            setStudent(student);
            setLoading(false);
        }
        fetchStudent();
      }, [studentId]);

    const updateStudent = async(event: {preventDefault: () => void}) => {
        event.preventDefault();
        try{
            await axios.put(`${BACKEND_API_URL}/students/${studentId}/`, student);
            navigate("/students/");
        }
        catch(error){
            console.log(error);
        }
    };

    const updateCancel = (event: {preventDefault: () => void}) => {
        event.preventDefault();
        navigate("/students/");
    };

    return (
        <Container>
            <Card>
                <CardContent>
                <IconButton
                        component = {Link} sx={{mr:3}} to={`/student/`}>
                            <ArrowBackIcon/>
                    </IconButton>{" "}
                    <form>
                        <TextField
                            id="firstname"
                            value={student.firstname}
                            label="Firstname"
                            variant="outlined"
                            fullWidth
                            sx={{mb:2}}
                            onChange={(event) => setStudent({...student, firstname: event.target.value})}
                        />
                        <TextField
                            id="name"
                            value={student.name}
                            label="Name"
                            variant="outlined"
                            fullWidth
                            sx={{mb:2}}
                            onChange={(event) => setStudent({...student, name: event.target.value})}
                        />
                        <Select
                            id="GroupId"
                            value={(student.GroupId as Group)?.id }
                            onChange={(event: SelectChangeEvent<number>) => {
                                const groupId = event.target.value as number;
                                const group = groups.find((group) => group.id === groupId);
                                setStudent({
                                  ...student,
								  GroupId: group?.id,
                                });
                              }}

                            label="Group"
                            variant="outlined"
                            fullWidth
                            sx={{ mb: 2 }}
                            >
                            {groups.map((group) => (
                            <MenuItem key={group.id} value={group.id}>
                                {group.id};{group.groupNr};<>{group.specialization}</>;{group.language};{group.year}
                            </MenuItem>
                            ))}
                        </Select>
                        <TextField
                            id="CNP"
                            value={student.CNP}
                            label="CNP"
                            variant="outlined"
                            fullWidth
                            sx={{mb:2}}
                            onChange={(event) => setStudent({...student, CNP: parseInt(event.target.value)})}
                        />
                        <TextField
                            id="favorite_colour"
                            value={student.favorite_colour}
                            label="Favorite colour"
                            variant="outlined"
                            fullWidth
                            sx={{mb:2}}
                            onChange={(event) => setStudent({...student, favorite_colour: event.target.value})}
                        />
                    </form>
                </CardContent>
                <CardActions>
                    <Button onClick={updateStudent}>Update</Button>
                    <Button onClick={updateCancel}>Cancel</Button>
                </CardActions>
            </Card>
        </Container>
        )
}