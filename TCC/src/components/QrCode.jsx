import React, { useState } from 'react';
import './QrCode.css';

const QRCode = ({ token }) => {
  const qrCodeUrl = `https://api.qrserver.com/v1/create-qr-code/?size=150x150&data=${token}`;
  const [loading, setLoading] = useState(true); // inicializa o estado do carregando como true

  return (
    <div className='QrCode'>
      {loading ? (
        <p>Gerando Token...</p> // mostra a mensagem de carregando
      ) : null} {/*quando for falso, vai substituir a mensagem por vazio*/}
      <img
        src={qrCodeUrl}
        alt="QRCODE"
        onLoad={() => setLoading(false)} // seta o carregando como falso
      />
    </div>
  );
};

export default QRCode;
