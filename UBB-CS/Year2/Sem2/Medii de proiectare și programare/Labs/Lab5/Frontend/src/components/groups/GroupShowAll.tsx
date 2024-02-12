import { Card, CardActions, CardContent, IconButton, Tooltip } from "@mui/material";
import { Container } from "@mui/system";
import { useEffect, useState } from "react";
import { Link, useParams } from "react-router-dom";
import { BACKEND_API_URL } from "../../constants";
import { Student } from "../../models/Student";
import EditIcon from "@mui/icons-material/Edit";
import DeleteForeverIcon from "@mui/icons-material/DeleteForever";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import ReadMoreIcon from "@mui/icons-material/ReadMore";
import { GroupsFiltered } from "../../models/GroupsFiltered";

export const GroupShowAll = () => {
    const [loading, setLoading] = useState(false);
	const [groupsFiltered, setGroupsFiltered] = useState<GroupsFiltered[]>([]);
	<Container>

    </Container>
};
