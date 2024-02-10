import { Card, CardActions, CardContent, IconButton, Tooltip } from "@mui/material";
import { Container } from "@mui/system";
import { useEffect, useState } from "react";
import { Link, useParams } from "react-router-dom";
import { BACKEND_API_URL } from "../../constants";
import { Student } from "../../models/Student";
import { Group } from "../../models/Group";
import EditIcon from "@mui/icons-material/Edit";
import DeleteForeverIcon from "@mui/icons-material/DeleteForever";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import ReadMoreIcon from "@mui/icons-material/ReadMore";

export const StudentDetails = () => {
	const { studentId } = useParams();
	const [student, setStudent] = useState<Student>();

	useEffect(() => {
		const fetchCourse = async () => {
			// TODO: use axios instead of fetch
			// TODO: handle errors
			// TODO: handle loading state
			const response = await fetch(`${BACKEND_API_URL}/students/${studentId}/`);
			const student = await response.json();
			setStudent(student);
		};
		fetchCourse();
	}, [studentId]);

	return (
		<Container>
			<Card>
				<CardContent>
					<IconButton component={Link} sx={{ mr: 3 }} to={`/students`}>
						<ArrowBackIcon />
					</IconButton>{" "}
					<h1>Student Details</h1>
					<p>Student First Name: {student?.firstname}</p>
					<p>Student Name: {student?.name}</p>
					<p>Student CNP: {student?.CNP}</p>
					<p>Student favorite color: {student?.favorite_colour}</p>
					<p><a href={`/groups/${student?.GroupId}/details`} title="View group details">Group{(student?.GroupId as Group)?.groupNr}</a></p>

				</CardContent>
				<CardActions>
					<IconButton component={Link} sx={{ mr: 3 }} to={`/students/${studentId}/edit`}>
						<EditIcon />
					</IconButton>

					<IconButton component={Link} sx={{ mr: 3 }} to={`/students/${studentId}/delete`}>
						<DeleteForeverIcon sx={{ color: "red" }} />
					</IconButton>
				</CardActions>
			</Card>
		</Container>
	);
};
/// q: generate code so that the text from {student?.Group?.groupNr} is a link to the group details page
