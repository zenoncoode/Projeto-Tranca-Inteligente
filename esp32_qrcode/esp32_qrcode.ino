//Bibliotecas utilizadas
#include "ESPino32CAM.h"
#include "ESPino32CAM_QRCode.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

//Config do wifi
const char* ssid = "MASSINHA DE EVA";
const char* password =  "senhaarea2020";

//URL servidor.
String serverName = "http://192.168.1.106:3000/users?token=";

//Objetos de camera
ESPino32CAM cam;   //Objeto para captura de imagem
ESPino32QRCode qr; //Objeto para decoficação da imagem
 
//Define os pinos da câmera
//Pinos internos.
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22
#define flash 4
 
 
//Variável para limitar o print no monitor serial se caso o QR Code ainda estiver na frente da câmera
int trava;
int rele = 12;

 
void setup() {
  //Definicao do clock.
  Serial.begin(115200);

  pinMode(rele, OUTPUT);
  digitalWrite(flash, LOW); //Turn on
  //Connectar no wifi.
  WiFi.begin(ssid, password);
 
  //Enquanto não conectado, Tentar conectar.
  //loop
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Conectando no wifi.");
  }

  Serial.println("Conectado ao wifi!");
  Serial.println("Endereço de IP: ");
  //Mostra o ip atual do cliente.
  Serial.println(WiFi.localIP());
  Serial.println("Leitor de QR Code");
  
  //Define pino do flash
  pinMode(flash,OUTPUT);
  digitalWrite(flash,LOW);//Desliga o flash
     
  //Configura os pinos da câmera
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_VGA;  
  config.jpeg_quality = 4;
  config.fb_count = 1;
   
  esp_err_t err = esp_camera_init(&config); //Inicialização da câmera

  if (err != ESP_OK) {
     
    Serial.printf("O início da câmera falhou com erro 0x%x", err);//Informa erro se a câmera não for iniciada corretamente
    delay(1000);
    //Em caso de err, reiniciar o esp32
    ESP.restart();//Reinicia o ESP

  }
 
  //Inicializa o objeto de decodificação
  qr.init(&cam);
  sensor_t *s = cam.sensor();
  s->set_framesize(s, FRAMESIZE_CIF);
  s->set_whitebal(s, true);
   
  Serial.println();
  Serial.println("Aguardando código"); 
 
}
 
void loop()
{
  digitalWrite(flash, HIGH);
  unsigned long pv_time = millis();
  camera_fb_t *fb = cam.capture(); //Captura a imagem
  if (!fb)
  {
    Serial.println("Falha na captura da imagem");
    return; // reinicia o arduino
  }
  // configuração de cor
  dl_matrix3du_t *rgb888, *rgb565;
  if (cam.jpg2rgb(fb, &rgb888)) //If jpg converter para rgb.
  {
    rgb565 = cam.rgb565(rgb888);
  }
  //Limpa a memoria da camera.
  cam.clearMemory(rgb888);
  cam.clearMemory(rgb565);
  dl_matrix3du_t *image_rgb;

  //If img.
  if (cam.jpg2rgb(fb, &image_rgb))
  {
    cam.clearMemory(fb);
         
    qrResoult res = qr.recognition(image_rgb); //Faz decodificação da imagem contendo os dados
     
    if (res.status) //Se conseguir decodificar a imagem mostra os dados na tela
    { 
      //IF qrcode não estiver na tela por muito tempo,
      if(trava == 0){
        //Trava o código para que a leitura nao seja feita o tempo todo
        //valida_token(token)

        trava = 1;
        String leitura = "Código QR Lido: " + res.payload; //Variável para mostrar os dados contidos no QR Code
        Serial.println();
        Serial.println(leitura);  //Mostra os dados no monitor serial

        //Inicia o cliente HTTP. <- Resquest web.
        HTTPClient http;
        //define a url com o filtro.
        String serverPath = serverName  + res.payload;
        //Iniciar a conexao com o servidor serverPath (URL + Filtro)      
        http.begin(serverPath.c_str());
        //Get no servidor com o filtro token.
        int httpResponseCode = http.GET();
        Serial.println(serverPath.c_str());
        Serial.println("HTTP Response code: ");
        //If não der erro durante a conexao. deve retornar 200
        Serial.println(httpResponseCode);
        //Caso conexao retorne > 0 (esperado 200)
        if (httpResponseCode > 0) {
          //Caso o retorno seja OK no servidor.
          if (httpResponseCode == HTTP_CODE_OK){
            //Cria o objeto json
            DynamicJsonDocument doc(2048);
            //Transforma o json em uma lista. array
            deserializeJson(doc, http.getString());
            JsonArray array = doc.as<JsonArray>();

            Serial.println(array.size());

            //If lista no servidor retornar mais de 0 registros. (Quando 0 então não existe TOKEN no servidor.)
            if(array.size() > 0){
              Serial.println("Usuario existe.");
              digitalWrite(rele, HIGH);
              delay(5000);
              //abrir_porta();
            }
            else{
              Serial.println("Usuario Náo existe.");
            }
          }
        }
        //Finaliza o HTTP
        http.end();
      }
        
    }
    else{ //Se não aguarda receber código 
        
       trava = 0;
       Serial.println();
       Serial.println("Aguardando código"); 
       digitalWrite(flash, LOW);
        digitalWrite(rele, LOW);
        cam.clearMemory(image_rgb); //Apaga imagem para receber uma nova imagem
        delay(1000);
     }
            
    }
  
}