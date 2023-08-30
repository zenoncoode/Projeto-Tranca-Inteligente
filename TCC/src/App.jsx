import { useState } from 'react'
import './App.css'
import Container from './components/Container'
import Historico from './components/Historico'

function App() {

  return (
    <>
      <div id='register-container' className='register-form'>
        <h2>Cadastrar Autorização</h2>
        <p>Registre quem está apto a receber o token de acesso!</p>
        <Container/>
        {/*<Historico/> NAO ESTÁ FUNCIONAL AINDA*/}
      </div>
    </>
  )
}

export default App
