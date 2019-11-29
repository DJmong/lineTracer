
int pid_control(int val,int goal){
  static int err_p,err_i,err_d;
  static int pre;
  int p=1;
  int i=1;
  int d=1;
  int PID_val;
  
  err_p=goal-val;
  err_i+=err_p;
  err_d=err_p-pre;

  pre=err_p;

  PID_val=err_p*p+err_i*i+err_d*d;

  return PID_val;  
}

int main(void){
  int i=1;
  Serial.begin(9600);
  while(1){
    
    Serial.println(i);
    i+=pid_control(i,25000);
    _delay_ms(50);
  }
  return 1;
}
