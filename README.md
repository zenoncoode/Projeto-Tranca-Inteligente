# Projeto-Tranca-Inteligente
Projeto de TCC - Construindo um sistema de tranca inteligente com verificação por QR Code

# DEPENDÊNCIAS
Instalar Node.js juntamente com o gerenciador de pacotes npm através do link [(https://nodejs.org/en)](https://nodejs.org/en/download/current)

# CONFIGURANDO O PROJETO (JSON SERVER)
-	Abra o terminal integrado do VS Code do diretório TCC (caso não abra em TCC, só mude o diretório com o comando cd TCC)
- Digite o comando npm install
- Após a instalação, digite o comando npm install json-server 
  - obs: esse comando vai rodar nosso "servidor" local, o qual faremos nossas requisições HTTP
- Após a instalação, digite o comando npm run server

# CONFIGURANDO O PROJETO (RODANDO A APLICAÇÃO)
- Abra mais um terminal integrado do VS Code do diretório TCC (caso não abra em TCC, só mude o diretório com o comando cd TCC
  - obs: o primeiro terminal vamos deixar rodando apenas para o "servidor", então vamos preferencialmente rodar a aplicação em um terminal separado)
- Digite o comando npm run dev
- Agora temos nosso link que abre o navegador com a nossa aplicação rodando. Clique em cima do link com o mouse enquanto pressiona o crtl e o App abrirá
 no seu navegador padrão!

# COMO UTILIZAR O APP
- Digite o nome da pessoa que deseja cadastrar no campo de nome
- Digite o email da pessoa que deseja cadastrar no campo de email
- Clique em Cadastra Usuário
- O App automaticamente irá atribuir um token aleatório ao usuário cadastrado e gerar o QR Code
  - obs: você pode visualizar a lista de usuários cadastrados no arquivo db.json localizado dentro do diretório ./TCC/data

