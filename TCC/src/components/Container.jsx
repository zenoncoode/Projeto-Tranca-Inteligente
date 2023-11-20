import React, { useState, useEffect } from 'react';
import './Container.css'
import QRCode from './QrCode';
import { useFetch } from '../hooks/useFetch';
import { Token } from '../hooks/Token';


const url = "http://10.10.10.100:3000/users" //link do servidor

const Container = ({ user }) => {  
    const [name, setName] = useState(user ? user.name : ""); //para a variavel name setada como vazio no inicio, caso name seja diferente de vazio, temos um novo estado
    const [email, setEmail] = useState(user ? user.email : ""); //para a variavel email setada como vazio no inicio, caso email seja diferente de vazio, temos um novo estado
    const [showQRCode, setShowQRCode] = useState(false);
    const [users, setUsers] = useState([]);
    const [token, setToken] = useState("");

    const {data:items} = useFetch(url) //pega o data do servidor utilizando o hook passando o link como parametro
   //data foi renomeado para items (fica menos estranho)

    const handleSubmit = async (e, GeraToken) => { //funcao para enviar o form
      e.preventDefault();
      
      const token = Token() //passa o Token do Hook para a const token

      console.log("Enviando form");       
      console.log(name, email, token);

      const user = {
        name,
        email,
        token
      };

      const res = await fetch("http://10.10.10.100:3000/users", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify(user),
    });

    
      if (name && email) { // Verifica se ambos nome e email estão preenchidos
        setShowQRCode(true);
        setToken(token); // Se estiver usando um estado para o token
      } else {
        setShowQRCode(false);
      }
    };
  
    useEffect(() => {
        // Esconder o QRCode quando os inputs de email ou name estão sendo alterados
        setShowQRCode(false);
    }, [name, email]);

    
    const handleClear = (e) =>{
        e.preventDefault();
        setName("");
        setEmail("");
    }

    return (
      <div>
        {/* envio de form */}
        <form onSubmit={handleSubmit}>
          {/* criacao form */}
          <div className="form-control">
            <label htmlFor="name">Nome</label>
            <input
              type="text"
              name="name"
              placeholder="Digite o nome"
              onChange={(e) => setName(e.target.value)} //quando o mudar de vazio para o que a pessoa digitar, aciona a funcao que salva o nome numa variavel
              value={name} //o valor digitado estara em name
            />
          </div>
          {/* label envovendo o input */}
          <div className="form-control">
            <label>E-mail</label>
            <input
              type="email"
              name="email"
              placeholder="Digite o seu email"
              onChange={(e) => setEmail(e.target.value)} //pega o valor digitado no input de email e coloca o valor numa variavel (funcao setEmail)
              value={email} //o valor do input esta na variavel email
            />     
          </div>
          
          <div className='buttons'>
            {!showQRCode && <input type="submit" value="Cadastrar Usuário"/>}
            {showQRCode && <input id="input_gerado" type='submit' value="Token Gerado!" disabled/>}
            <button onClick={handleClear}>Limpar</button>
          </div>

        </form>
        
        {showQRCode && <QRCode token={token} />} {/* mostra o componente QRcode passando o token como prop */}
      </div>
    );
}

export default Container