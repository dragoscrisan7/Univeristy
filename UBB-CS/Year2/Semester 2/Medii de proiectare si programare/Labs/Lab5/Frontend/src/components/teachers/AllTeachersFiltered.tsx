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
import { useEffect, useState } from "react";
import { Link, useParams } from "react-router-dom";
import { BACKEND_API_URL } from "../../constants";
import { Teacher } from "../../models/Teacher";
import { Student } from "../../models/Student";
import EditIcon from "@mui/icons-material/Edit";
import DeleteForeverIcon from "@mui/icons-material/DeleteForever";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import ReadMoreIcon from "@mui/icons-material/ReadMore";
import { TeachersFiltered } from "../../models/TeachersFiltered";

export const AllTeachersFiltered = () => {
    const [loading, setLoading] = useState(false);
	const [teachersFiltered, setTeachersFiltered] = useState<TeachersFiltered[]>([]);
	useEffect( () => {
		setLoading(true);
		fetch(`${BACKEND_API_URL}/teacher_nr_classes/`)
		.then((response) => response.json())
		.then((data) => {
			setTeachersFiltered(data);
			setLoading(false);
		});
	}, []);

	return (
		<Container>
			<h1>Statistic - Teachers ordered by nr of classes teached</h1>
			{loading && <CircularProgress/>}
			{!loading && teachersFiltered.length == 0 && <p>No data.</p>}
			{!loading && teachersFiltered.length > 0 && (
				<TableContainer component={Paper}>
					<Table sx={{minWidth: 650}} aria-label="simple table">
						<TableHead>
							<TableRow>
								<TableCell align="center">#</TableCell>
								<TableCell align="center">Firstname</TableCell>
								<TableCell align="center">Teaching Subject</TableCell>
								<TableCell align="center">Number of nr of classes</TableCell>
							</TableRow>
						</TableHead>
						<TableBody>
							
							{teachersFiltered.map((teachersFiltered: TeachersFiltered, index) => (
								<TableRow key={(teachersFiltered.id as Teacher).id}>
									<TableCell  align="center" component="th" scope = "row">{index+1}</TableCell>
									<TableCell  align="center" component="th" scope = "row"><>{teachersFiltered.firstname}</></TableCell>
									<TableCell  align="center" component="th" scope = "row">{teachersFiltered.TeachingSubject}</TableCell>
									<TableCell  align="center" component="th" scope = "row">{teachersFiltered.nr_of_classes}</TableCell>
								</TableRow>
							))}
						</TableBody>
					</Table>
				</TableContainer>
			)}
		</Container>
	)
};