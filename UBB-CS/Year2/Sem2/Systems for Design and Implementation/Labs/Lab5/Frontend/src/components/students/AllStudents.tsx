import {
	TableContainer,
	Paper,
	Table,
	TableHead,
	TableRow,
	TableCell,
	TableBody,
	CircularProgress,
	Container,
	IconButton,
	Tooltip,
} from "@mui/material";
import React from "react";
import { useEffect, useState } from "react";
import { Link } from "react-router-dom";
import { BACKEND_API_URL } from "../../constants";
import { Student } from "../../models/Student";
import { Group } from "../../models/Group";
import ReadMoreIcon from "@mui/icons-material/ReadMore";
import EditIcon from "@mui/icons-material/Edit";
import MenuIcon from '@mui/icons-material/Menu';
import DeleteForeverIcon from "@mui/icons-material/DeleteForever";
import AddIcon from "@mui/icons-material/Add";

export const AllStudents = () => {
	const [loading, setLoading] = useState(false);
	const [students, setStudents] = useState<Student[]>([]);
	const [filteredStudents, setFilteredStudents] = useState<Student[]>([]);
	const [chosenStudents, setChosenStudents] = useState<Student[]>([]);
	const [isFiltered, setIsFiltered] = useState(true);

	useEffect(() => {
		setLoading(true);
		fetch(`${BACKEND_API_URL}/students/`)
			.then((response) => response.json())
			.then((data) => {
				setStudents(data);
				const filteredData = [...data].sort((a, b) => a.firstname.localeCompare(b.firstname));
				setChosenStudents(data);
				setFilteredStudents(filteredData);
				setLoading(false);
			});
	}, []);

	const clearFilter = () => {
		if(isFiltered){
			setChosenStudents(filteredStudents);
			setIsFiltered(false);
		}
		else{
			setChosenStudents(students);
			setIsFiltered(true);
		}
	}

	return (
		<Container>
			<h1>All students</h1>

			{loading && <CircularProgress />}
			{!loading && chosenStudents.length === 0 && <p>No students found</p>}
			{!loading && (
				<IconButton component={Link} sx={{ mr: 3 }} to={`/students/add`}>
					<Tooltip title="Add a new student" arrow>
						<AddIcon color="primary" />
					</Tooltip>
				</IconButton>
			)}
			{!loading && (
        	<>
            	<IconButton onClick={clearFilter} sx={{ mr: 3 }}>
                	<Tooltip title={isFiltered ? "Filter" : "Clear Filter"} arrow>
                    	<MenuIcon color="primary" />
                	</Tooltip>
            	</IconButton>
        	</>
    		)}
			{!loading && chosenStudents.length > 0 && (
				<TableContainer component={Paper}>
					<Table sx={{ minWidth: 650 }} aria-label="simple table">
						<TableHead>
							<TableRow>
								<TableCell>#</TableCell>
								<TableCell align="right">Firstname</TableCell>
								<TableCell align="right">Name</TableCell>
								<TableCell align="right">Group number</TableCell>
								<TableCell align="center">Operations</TableCell>
							</TableRow>
						</TableHead>
						<TableBody>
							{chosenStudents.map((student, index) => (
								<TableRow key={student.id}>
									<TableCell component="th" scope="row">
										{index + 1}
									</TableCell>
									<TableCell component="th" scope="row">
										<Link to={`/students/${student.id}/details`} title="View course details">
											{student.firstname}
										</Link>
									</TableCell>
									<TableCell align="right">{student.name}</TableCell>
									<TableCell align="right">{(student.GroupId as Group)?.groupNr}</TableCell>
									<TableCell align="right">
										<IconButton
											component={Link}
											sx={{ mr: 3 }}
											to={`/students/${student.id}/details`}>
											<Tooltip title="View students details" arrow>
												<ReadMoreIcon color="primary" />
											</Tooltip>
										</IconButton>

										<IconButton 
											component={Link} 
											sx={{ mr: 3 }} 
											to={`/students/${student.id}/edit`}>
											<EditIcon />
										</IconButton>

										<IconButton component={Link} sx={{ mr: 3 }} to={`/students/${student.id}/delete`}>
											<DeleteForeverIcon sx={{ color: "red" }} />
										</IconButton>
									</TableCell>
								</TableRow>
							))}
						</TableBody>
					</Table>
				</TableContainer>
			)}
		</Container>
	);
};