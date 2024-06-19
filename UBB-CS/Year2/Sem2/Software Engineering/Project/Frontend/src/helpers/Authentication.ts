import axios from 'axios';
import { AuthResponse } from '../model/AuthResponse';
import { ServerSettings } from '../ServerSettings';

export const getAuthToken = () : string => {
    const val = window.localStorage.getItem('auth_token');
    return val == null ? "" : val;
};

export const getAuthUsername = () : string => {
    const val = window.localStorage.getItem('auth_username');
    return val == null ? "" : val;
}

export const getAuthRoles = () : string[] => {
    const val = window.localStorage.getItem('auth_role');
    let authorities = [];
    if (val != null) {
        authorities = JSON.parse(val)
    }
    return authorities;
}

export const hasAuthRole = (role: string) : boolean => {
    const authorities = getAuthRoles();
    for (let index = 0; index < authorities.length; index++) {
        if (authorities[index] == role) {
            return true;
        }
    }
    return false;
}

export const setAuthHeader = (token: any) => {
    window.localStorage.setItem('auth_token', token);
};

export const setAuthUsername = (username: any) => {
    window.localStorage.setItem('auth_username', username);
}

export const setAuthRole = (role: any) => {
    window.localStorage.setItem('auth_role', JSON.stringify(role));
}

export const setAuth = (response: AuthResponse) => {
    setAuthUsername(response.username)
    setAuthHeader(response.accessToken)
    setAuthRole(response.roles);
}

export const resetAuth = () => {
    setAuthHeader(null)
    setAuthUsername(null)
    setAuthRole(null)
}

axios.defaults.baseURL = ServerSettings.API_ENDPOINT;
axios.defaults.headers.post['Content-Type'] = 'application/json';
axios.defaults.headers.common['Access-Control-Allow-Origin'] = '*';

export const make_request = (method: any, url: any, data: any) => {

    let headers = {};
    if (getAuthToken() !== null && getAuthToken() !== "null") {
        headers = {'Authorization': `Bearer ${getAuthToken()}`};
    }

    return axios({
        method: method,
        url: url,
        headers: headers,
        data: data,
        timeout: 600000
    }
    );
};