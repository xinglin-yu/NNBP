/*
Referrence:
用C语言实现的BP网络
http://www.codeforge.cn/read/53928/bp.c__html?go_blog_box=1
 */


/*******************************
****    Author: WangYanqiu
****    Date:   2007年6月28日
*********************************/
 /********************************
 This is the program for neutron network using BP algorithm. The problem is to
 solving the numetrical approximation problem. In this program, the function is
 f(x,y)=sin(pi*x)*sin(pi*y)
 ***********************************/
 #include <math.h>
 #include <stdlib.h>
 #include <stdio.h>
 /* M是输入维数  */
 #define M 2
 
 /*   N是隐层神经元个数              */
 #define N 5
 
 /* NUMOUT是输出维数    */
 /*#define NUMOUT 1*/
 
 /* SITA是学习率                 */
 
 #define SITA 0.5
 
 FILE *fp;
 
 typedef struct
 {
 
 double weight[N][M] ;/*the weights of the hide layer */
 double input[M];
 double output[N];
  
}HIDELAYER;
 
 
 
typedef struct
{
 
  double weight[N];
  double output;
 
}OUTLAYER;
 
 
typedef struct{
 
double a; /* x axis*/
double b;  /* y axis */
double c;  /* z axis  */
 
}POINT;
 
 
 /*double sigmoid(double x);*/
 void realoutput(POINT* pt);
 void initnet(HIDELAYER* layer,OUTLAYER* outlayer);
 /*void initdata(POINT pt1[400],POINT pt2[225]);*/
 void computOutput(HIDELAYER* aa,OUTLAYER* bb ,POINT *pt);
 double tanhderiv(double x);
 
 void adjust(HIDELAYER*,OUTLAYER*,POINT* pt);
 void train(HIDELAYER* A,OUTLAYER* B);
 void sim(HIDELAYER* A,OUTLAYER* B);
 
 
 
double tanhderiv(double x)
{
 
    double temp;
    temp=cosh(x);
    temp=temp*temp;
    return  1/temp;
 
}
 
/*init the network using function rand()*/
void initnet(HIDELAYER* layer,OUTLAYER* outlayer)
{
   int i,j;
    srand(time(NULL));
 
    for(i=0;i<N;i++)
    for(j=0;j<M;j++){
 
        layer->weight[i][j]=rand()%100/100.0;
        printf("layer's weight is %f\n",layer->weight[i][j]);
         
}
 
        for(j=0;j<N;j++){
 
        layer->output[j]=0;
 
        outlayer->weight[j]=rand()%100/100.0;
 
 
        printf("outputlayer's  is %f\n",outlayer->weight[j]);
         
}
        outlayer->output=0;
 
}
 
 
 /*void initdata(POINT pt1[400],POINT pt2[225])
 {
 
 
  
} */
 
 /*the output of the signal which should be*/
void realoutput(POINT* pt)
 {
 
 
    pt->c=sin(M_PI*pt->a)*sin(M_PI*pt->b);
    printf("real is %f  ",pt->c);
 
  
}
 
 
/* 根据隐层权值和输出层权值,把输入x,y转化成输出  */
 void computOutput(HIDELAYER* aa,OUTLAYER* bb ,POINT *pt)
{
    int i,j;
     double temp;
     double sum=0;
 
     for(i=0;i<N;i++)
     {
 
        temp= (aa->weight[i][0] * pt->a )+  ( aa->weight[i][1] * pt->b);
 
        aa->output[i]=tanh(temp);
              
}
 
     for(i=0;i<N;i++){
 
            sum+= (bb->weight[i]) * (aa->output[i]);
              
}
 
           bb->output=tanh(sum);
 
           printf("output is %f \n",bb->output);
           getch();
 
}
 
 
/* 根据期望输出值z和实际输出值out调整隐层和输出层权重 阀值                  */
 /*void adjust(HIDELAYER* aa,OUTLAYER* bb,double z,double out,double input)*/
 void adjust(HIDELAYER* aa,OUTLAYER* bb,POINT* pt)
{
 
        int i,j;
        double s=0,ss;
        double delta0=0;
        double deltaj=0;
        double temp=0,deriv=0,temp1=0;
 
         for(i=0;i<N;i++)
        {
 
        temp+=(bb->weight[i] * aa->output[i] );
         
}
 
        delta0=(pt->c-(bb->output))*tanhderiv(temp);
        printf("delta0=%f\n",delta0);
        printf("the layers' weight after adjusted:\n");
        for(i=0;i<N;i++) {
 
                for(j=0;j<M;j++) {
 
                        temp1+=aa->input[j]*aa->weight[i][j];
                             
}
                deriv=tanhderiv(temp1);
                deltaj=deriv*delta0*(bb->weight[i]) ;
                aa->weight[i][j]+= SITA*deltaj*(aa->input[j]);
                temp1=0;
           
}
 
 
        for(i=0;i<N;i++)
           {
 for(j=0;j<M;j++)
                {
 
                    s+=aa->weight[i][j]*aa->input[j];
                 
}
              ss=tanh(s);
            bb->weight[i]+=SITA*delta0*ss;
            printf("output layer is %f\n",bb->weight[i]);
            s=0;
             
}
 
}
 
 
void train(HIDELAYER* A,OUTLAYER* B)
{
  double x=0,y=0;
    int count=0;
    POINT pt;
   while(x<=2){
 
 
        while(y<=2){
 
            pt.a=x;
            pt.b=y;
            A->input[0]=x;
            A->input[1]=y;
            printf("x is %f,y is %f ",x,y);
            realoutput(&pt); /*The real output of the function*/
            computOutput(A,B,&pt);
            adjust(A,B,&pt);
            count++;
            /*getch();*/
            /*fprintf(fp,"%f ",pt.c);*/
            if(count%10==0){
 
                /*fprintf(fp,"\n");     */
                printf("\n");
                 
}
            y+=0.05;
             
}
        x+=0.05;
        y=0;/*clear y in the new circulum*/
        fprintf(fp,"hhh%f\n",x);
 
 
     
}
 
}
 
void sim(HIDELAYER* A,OUTLAYER* B)
{
 
double x=2,y=2;
POINT pt;
double err;
while(x<=3){
 
    while(y<=3) {
 
            pt.a=x;
            pt.b=y;
            computOutput(A,B,&pt);
            realoutput(&pt);
            err=pt.c-B->output;
            y+=0.05;
            printf("the exact number is %f",pt.c);
            printf("the output number is %f \n",B->output);
            printf("err is %f for this example \n",err);
            /*getch();*/
           
}
        y=2;
        x+=0.05;
         
}
 
 
}
 
 int main()
 {
 
 
 
    HIDELAYER layer;
    OUTLAYER outlayer;
    /*POINT pt1[400];
    POINT pt2[225];
    */
 
 
    /*open the bpg file. write the result into it.fp points to it*/
    if((fp=fopen("bpg.txt","w"))==NULL) {
 
    printf("failure to write the bpg.txt.\n");
    exit(0);
     
}
    else{ 
 
    printf("open bpg.txt successfully\n");
     
}
    /* initiallize the network */
    initnet(&layer,&outlayer);
    printf("Initial network success!\n");
    getch();
    /*prepare the data well for the train and the simulation*/
    /*initdata(pt1,pt2);*/
    /* begin to train the net */
    train(&layer,&outlayer);
    printf("train over!\n");
    getch();
    sim(&layer,&outlayer);
    printf("sim  over!\n");
    getch();
    fclose(fp);
    getch();
    return 0;
  
}