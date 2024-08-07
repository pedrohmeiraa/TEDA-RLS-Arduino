#include "rls.h"
#include "teda.h"

const int N = 2;
const float lambda = 0.99;
const float delta = 0.1; 

float Y[20] = {};
float vetor_de_entrada[N] = {0.0, 0.0};
float x_ant[N] = {0.0, 0.0};
float y_pred = 0.001;
const int nA = 352;

float A[nA] = {0.0,
 0.0,
 0.0,
 0.0,
 7.0,
 12.0,
 16.0,
 21.0,
 25.0,
 29.0,
 31.0,
 33.0,
 35.0,
 36.0,
 36.0,
 38.0,
 39.0,
 41.0,
 43.0,
 44.0,
 45.0,
 47.0,
 49.0,
 50.0,
 51.0,
 51.0,
 51.0,
 51.0,
 51.0,
 51.0,
 50.0,
 48.0,
 46.0,
 47.0,
 47.0,
 46.0,
 46.0,
 46.0,
 48.0,
 50.0,
 51.0,
 51.0,
 51.0,
 49.0,
 47.0,
 48.0,
 47.0,
 45.0,
 40.0,
 31.0,
 23.0,
 21.0,
 19.0,
 23.0,
 28.0,
 33.0,
 37.0,
 41.0,
 44.0,
 46.0,
 48.0,
 50.0,
 52.0,
 53.0,
 53.0,
 54.0,
 55.0,
 56.0,
 57.0,
 58.0,
 58.0,
 59.0,
 60.0,
 61.0,
 62.0,
 62.0,
 62.0,
 62.0,
 62.0,
 62.0,
 62.0,
 61.0,
 61.0,
 58.0,
 54.0,
 49.0,
 43.0,
 35.0,
 26.0,
 20.0,
 20.0,
 23.0,
 27.0,
 31.0,
 33.0,
 37.0,
 41.0,
 43.0,
 46.0,
 49.0,
 51.0,
 52.0,
 54.0,
 55.0,
 55.0,
 56.0,
 55.0,
 52.0,
 48.0,
 42.0,
 36.0,
 28.0,
 20.0,
 17.0,
 19.0,
 23.0,
 28.0,
 33.0,
 37.0,
 40.0,
 43.0,
 44.0,
 46.0,
 48.0,
 49.0,
 50.0,
 50.0,
 50.0,
 51.0,
 51.0,
 51.0,
 50.0,
 48.0,
 42.0,
 32.0,
 23.0,
 19.0,
 19.0,
 22.0,
 27.0,
 31.0,
 34.0,
 36.0,
 40.0,
 44.0,
 48.0,
 50.0,
 51.0,
 51.0,
 52.0,
 55.0,
 57.0,
 59.0,
 60.0,
 60.0,
 58.0,
 57.0,
 54.0,
 51.0,
 51.0,
 50.0,
 47.0,
 43.0,
 37.0,
 29.0,
 23.0,
 19.0,
 18.0,
 19.0,
 19.0,
 21.0,
 26.0,
 31.0,
 36.0,
 41.0,
 44.0,
 46.0,
 47.0,
 50.0,
 52.0,
 55.0,
 57.0,
 58.0,
 58.0,
 57.0,
 55.0,
 53.0,
 50.0,
 48.0,
 46.0,
 43.0,
 38.0,
 29.0,
 21.0,
 17.0,
 18.0,
 24.0,
 28.0,
 33.0,
 38.0,
 42.0,
 47.0,
 51.0,
 53.0,
 56.0,
 57.0,
 59.0,
 58.0,
 58.0,
 58.0,
 58.0,
 56.0,
 51.0,
 45.0,
 38.0,
 32.0,
 23.0,
 16.0,
 19.0,
 24.0,
 31.0,
 37.0,
 42.0,
 46.0,
 49.0,
 51.0,
 52.0,
 53.0,
 54.0,
 54.0,
 54.0,
 55.0,
 57.0,
 57.0,
 56.0,
 53.0,
 46.0,
 38.0,
 29.0,
 20.0,
 18.0,
 20.0,
 25.0,
 31.0,
 35.0,
 39.0,
 43.0,
 46.0,
 48.0,
 51.0,
 53.0,
 56.0,
 57.0,
 59.0,
 59.0,
 61.0,
 61.0,
 62.0,
 63.0,
 63.0,
 63.0,
 63.0,
 63.0,
 63.0,
 62.0,
 61.0,
 59.0,
 58.0,
 57.0,
 57.0,
 57.0,
 57.0,
 56.0,
 50.0,
 42.0,
 34.0,
 25.0,
 17.0,
 16.0,
 18.0,
 23.0,
 28.0,
 32.0,
 37.0,
 42.0,
 45.0,
 48.0,
 50.0,
 53.0,
 55.0,
 56.0,
 57.0,
 58.0,
 58.0,
 58.0,
 57.0,
 54.0,
 48.0,
 41.0,
 34.0,
 28.0,
 21.0,
 16.0,
 18.0,
 23.0,
 27.0,
 31.0,
 35.0,
 37.0,
 39.0,
 41.0,
 43.0,
 44.0,
 44.0,
 44.0,
 43.0,
 42.0,
 39.0,
 35.0,
 29.0,
 23.0,
 19.0,
 19.0,
 24.0,
 29.0,
 33.0,
 37.0,
 40.0,
 42.0,
 43.0,
 44.0,
 45.0,
 44.0,
 43.0,
 41.0,
 37.0,
 33.0,
 32.0,
 31.0,
 27.0,
 22.0,
 14.0,
 12.0,
 12.0,
 14.0,
 15.0,
 16.0,
 19.0,
 21.0,
 22.0,
 20.0,
 14.0};


RLSFilter rls_filter(lambda, delta);
TEDA teda(1.8);
int flag = 0;
int outlier_count = 0;
int N_outlier_max = 2;
bool correction = true;

const int INTERVALO = 500; // Intervalo de tempo em milissegundos

//Accelerometer variables
float x, y, z, valor_atual=0;

void setup() {
  Serial.begin(9600);
  while (!Serial);
//Serial.println("Started");
  Serial.println("CLEARDATA");
  Serial.println("LABEL,Date,Hour,x_ant,x_atual,flag,x_antp,x_atualp,y_pred_ar");
  randomSeed(analogRead(0));

}

void loop()
{
    for (int i=0; i < nA; i++)
    {      
      valor_atual = A[i];

      flag = teda.run(valor_atual);

      Serial.print("DATA, DATE, TIME,");
      Serial.print(x_ant[1]);
      Serial.print(",");
      Serial.print(valor_atual);
      Serial.print(",");      


      if (flag == 1){
          outlier_count++;
          valor_atual = y_pred;
      }
      else{
          outlier_count = 0;
      }

      if (correction == true && outlier_count == N_outlier_max + 1)
      {
          valor_atual = A[i];
      }
      
      // Updating weights
      rls_filter.update(valor_atual, x_ant);

      vetor_de_entrada[0] = x_ant[1];
      vetor_de_entrada[1] = valor_atual;
      
      // Predicting
      y_pred = rls_filter.filter(vetor_de_entrada);

      // Second stage
      if (flag == 1){
          valor_atual = y_pred;
      }
      // Consecutive outliers treating
      if(correction == true && outlier_count == N_outlier_max + 1){
          outlier_count = 0;
          valor_atual = A[i];
      }

      Serial.print(flag);
      Serial.print(",");
      Serial.print(x_ant[1]);
      Serial.print(",");
      Serial.print(valor_atual);
      Serial.print(",");                         
      Serial.println(y_pred);      
      
      x_ant[0] = vetor_de_entrada[0];
      x_ant[1] = vetor_de_entrada[1];

      delay(INTERVALO);  
    }
         
 }
