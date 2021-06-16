/*
 * this is the receiver code for laser data tranfer
 * pulse width of 50 ms is where i was getting reliable transfer acuuracy it can go lower than that but chances of data lost increses with that
 * 
 * A0 is the LDR valtage redaing PIN
 * 
 * startListening() function first ingnores the fist byte and then start reading values at the the middle of rach pulse 
 * the first bit is just starting bit which sync the communication
 */

#define bits 8
const int txnDelay=50;    //pulse width in ms
const int ref =80;        //ldr HIGH cutoff val
//array that stors received data as int
int a[bits];
int val=0;

void setup() {
  Serial.begin(9600);
  pinMode(A0,INPUT);
}

void loop() {
  val = analogRead(A0);
  if(val>ref){
    startListening();
    printChar(a);
  }
}

//reads the incoming signal and stores to a[] array
void startListening(){
  delay(3*txnDelay/2);      //this delay waits till we are at middle of second bit
  for(int i=0;i<bits;i++){
    val = analogRead(A0);
    if(val>ref) a[i]=1;
    else a[i]=0;
    delay(txnDelay);
  }
}


//a very simple binay to decimal covertor
void printChar(int x[bits]){
  int num= a[0]*128 + a[1]*64 + a[2]*32 + a[3]*16 +a[4]*8 +a[5]*4 +a[6]*2 +a[7];
  //printing the corresponding char val
  Serial.print((char)num);    
}
