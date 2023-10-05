//Funcoes para gerar token
const getLetterLowerCase = () =>{
    return String.fromCharCode(Math.floor(Math.random()*26) + 97);
    //retorna uma letra minuscula de a a z (comeca a partir de 97 na lista de codigos do fromCharCode) aleatoria
    //https://yorktown.cbe.wwu.edu/sandvig/shared/asciicodes.aspx
    //floor é para arredondar o numero
}

const getLetterUpperCase = () =>{
    return String.fromCharCode(Math.floor(Math.random()*26) + 65);
    //retorna uma letra maiuscula de A a Z (comeca a partir de 65) aleatoria
    //floor é para arredondar o numero
}

const getNumber = () =>{
    return Math.floor(Math.random()*10).toString();
    //retorna um numero de 0 a 9
}

const getSymbol = () =>{
    const symbols = "_"
    return symbols[Math.floor(Math.random()*symbols.length)]
    //retorna um dos simbolos da string symbols de forma aleatoria
}


export const Token = () =>{
    
    let password = "";
    
    const passwordLength = 12; //tamanho da senha
    const generators = [getLetterLowerCase, getLetterUpperCase, getNumber, getSymbol]; //generators é um array formado por caracteres aleatorios de cada funcao

    for (let i = 0; i < passwordLength; i++) { //repetidor para somar cada caractere à nossa variavel password (repetirá 12 vezes)
      const randomGeneratorIndex = Math.floor(Math.random() * generators.length); //escolhe um index aleatorio do nosso generators (pode ser letra, numero, simbolo, etc.)
      const randomValue = generators[randomGeneratorIndex](); //salva o valor correspondente ao index sorteado
      password += randomValue; //adiciona o novo caractere à nossa variavel password
    }
    
    return password; //retorna a senha (token)

}