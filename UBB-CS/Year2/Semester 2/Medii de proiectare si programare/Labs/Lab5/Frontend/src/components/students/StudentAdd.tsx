import {
	Autocomplete,
	Select,
	Button,
	Card,
	CardActions,
	CardContent,
	IconButton,
	TextField,
	MenuItem,
	SelectChangeEvent,
} from "@mui/material";
import { Container } from "@mui/system";
import { useCallback, useEffect, useState } from "react";
import { Link, useNavigate, useParams } from "react-router-dom";
import { BACKEND_API_URL } from "../../constants";
import { Student } from "../../models/Student";
import EditIcon from "@mui/icons-material/Edit";
import DeleteForeverIcon from "@mui/icons-material/DeleteForever";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import axios from "axios";
import { Group } from "../../models/Group";
import { debounce } from "lodash";

export const StudentAdd = () => {
	const navigate = useNavigate();

	const [student, setStudent] = useState<Student>({
		firstname: "",
		name: "",
		CNP: 1,
		favorite_colour: "",
		GroupId: undefined, // TODO: also read the teacher_id from the form (NOT from the user!)
	});

	const [groups, setGroups] = useState<Group[]>([]);

	useEffect(() => {
        const getGroups = async () => {
          const response = await axios.get<Group[]>(`${BACKEND_API_URL}/groups/`);
          setGroups(response.data);
        };
        getGroups();
    }, []);

	const addStudent = async (event: { preventDefault: () => void }) => {
		event.preventDefault();
		try {
			await axios.post(`${BACKEND_API_URL}/students/`, student);
			navigate("/students");
		} catch (error) {
			console.log(error);
		}
	};

	return (
		<Container>
			<Card>
				<CardContent>
					<IconButton component={Link} sx={{ mr: 3 }} to={`/students`}>
						<ArrowBackIcon />
					</IconButton>{" "}
					<form onSubmit={addStudent}>
						<TextField
							id="firstname"
							label="First Name"
							variant="outlined"
							fullWidth
							sx={{ mb: 2 }}
							onChange={(event) => setStudent({ ...student, firstname: event.target.value })}
						/>
						<TextField
							id="name"
							label="Name"
							variant="outlined"
							fullWidth
							sx={{ mb: 2 }}
							onChange={(event) => setStudent({ ...student, name: event.target.value })}
						/>

						<TextField
							id="CNP"
							label="CNP"
							variant="outlined"
							fullWidth
							sx={{ mb: 2 }}
							onChange={(event) => setStudent({ ...student, CNP: parseInt(event.target.value) })}
						/>

						<TextField
							id="favorite_colour"
							label="Favorite Color"
							variant="outlined"
							fullWidth
							sx={{ mb: 2 }}
							onChange={(event) => setStudent({ ...student, favorite_colour: event.target.value })}
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

						<Button type="submit">
							Add Student
						</Button>
					</form>
				</CardContent>
				<CardActions></CardActions>
			</Card>
		</Container>
	);
};