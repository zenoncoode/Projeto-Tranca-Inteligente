import React from 'react'
import { useState, useEffect } from 'react'
import { useFetch } from '../hooks/useFetch';


const url = "http://localhost:3000/users" //link do servidor

//DEPOIS MUDAR ISSO, POIS NAO MOSTRA HISTORICO DE ACESSOS
//MOSTRA APENAS QUAIS USUARIOS ESTAO CADASTRADOS NO SERVER
const Historico = () => {

    
    const {data:items} = useFetch(url) //pega o data do servidor utilizando o hook passando o link como parametro
   //data foi renomeado para items (fica menos estranho)

    return(
        <div className="List">
            <h1>Lista de Usuários Autorizados</h1>
            <ul>
                {/*faz checagem se items existe para esperar os items chegarem*/}
                {items && items.map((user) => (
                    <li key={user.token}>{user.name} - {user.email}</li>
                ))}
            </ul>
        </div>
    )
}

export default Historico