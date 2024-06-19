import React from 'react'
import './App.css'
import { EndPoints } from './EndPoints'
import { UserLogin } from './components/UserLogin'
import { Routes, Route } from 'react-router'
import { BrowserRouter } from 'react-router-dom'
import { DisplayPrivateDestinations } from './components/DisplayPrivateDestinations'
import { DisplayPublicDestinations } from './components/DisplayPublicDestinations'
import { Home } from './components/Home'
import { CreateDestination } from './components/CreateDestination'
import { CreateDestinationFromPublic } from './components/CreateDestinationFromPublic'

function App() {

  return (
    <React.Fragment>
      <div className="App">
        <BrowserRouter>
          <Routes>
            <Route path={EndPoints.ROOT} element={<UserLogin />}></Route>
            <Route path={EndPoints.HOME} element={<Home/>}></Route>
            <Route path={EndPoints.privateDestination()} element={<DisplayPrivateDestinations />}></Route>
            <Route path={EndPoints.publicDestination()} element={<DisplayPublicDestinations />}></Route>
            <Route path={EndPoints.CREATE_PUBLIC_ENTRY} element={<CreateDestination update_endpoint={EndPoints.publicDestination()} 
            request_endpoint={EndPoints.publicDestination()}/>}></Route>
            <Route path={EndPoints.CREATE_PRIVATE_ENTRY} element={<CreateDestination update_endpoint={EndPoints.privateDestination()} 
            request_endpoint={EndPoints.privateDestination()}/>}></Route>
            <Route path={EndPoints.CREATE_PUBLIC_ENTRY + "/:id"} element={<CreateDestinationFromPublic request_endpoint={EndPoints.privateDestination()} />}></Route>
          </Routes>
        </BrowserRouter>
      </div>
    </React.Fragment>
  )
}

export default App
