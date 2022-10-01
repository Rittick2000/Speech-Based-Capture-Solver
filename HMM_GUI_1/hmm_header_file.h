#include "stdafx.h"

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>

#define N 5			
#define M 32	
int T=0;

long double pi[N+1] = {0.0, 1.0, 0.0, 0.0, 0.0, 0.0};
long double A[N+1][N+1]={0.0};
long double B[N+1][M+1]={0.0};
long double Alpha[150][N+1]={0.0};
long double Beta[150][N+1]={0.0};
long double Gamma[150][N+1]={0.0};
long double Delta[150][N+1]={0.0};
int Psi[150][N+1]={0};
long double Xi[150][N+1][N+1]={0.0};
long double pi_bar[N+1]={0.0};
long double A_bar[N+1][N+1]={0.0};
long double B_bar[N+1][M+1]={0.0};
long double Avg_pi[10][N+1]={0.0};
long double Avg_A[10][N+1][N+1]={0.0};
long double Avg_B[10][N+1][M+1]={0.0};
long double P[100] = {0.0};
long double Pstar=0;
int qstar[150]={0};							
int O[150]={0};								
double codebook[33][13]={0};				
double sample[500000] = {0.0};				
int n = 0;	
int p=12;
int q=12;
double r[13] = {0.0};								
double a[13] = {0.0};								
double c[13] = {0.0};								
double frame_ci[150][13] = {0.0};					
double tokhura_weights[13] = {0.0,1.0, 3.0, 7.0, 13.0, 19.0, 22.0, 25.0, 33.0, 42.0, 50.0, 56.0, 61.0};
double dist_cepstral[50] = {0.0};	
double ct[13] = {0.0};				
int num_correct_outputs=0;			
double overall_accuracy=0.0;		
double accuracy_per_digit[10] = {0.0};

int get_rand_num(){
	return rand() % 10;
}


void read_codebook(){ 	
	FILE *myFile = fopen("codebook.txt","r");	
	int i,j;
	
	while (!feof(myFile)){
		for(i=1; i<=32; i++){
			for(j=1; j<=12; j++){
				fscanf(myFile,"%lf",&codebook[i][j]);
			}
		}
	}

	fclose(myFile);	
}


int energy(double *a){
	double noise_energy=0.0,energy=0.0;
	double temp1=0.0,temp2=0.0,temp3=0.0;
	int i,j;
	for(i=0;i<1000;i++){
		noise_energy+=(a[i]*a[i]);
	}
	noise_energy/=1000;
	for(i=20;i<340;i++){
		temp1+=(a[i]*a[i]);
	}
	temp1/=320;
	for(i=340;i<660;i++){
		temp2+=(a[i]*a[i]);
	}
	temp2/=320;
	for(i=660;i<980;i++){
		temp3+=(a[i]*a[i]);
	}
	temp3/=320;
	j=980;
	while(1){
		if((temp1>1000) && (temp2>1000) && (temp3>1000))
		break;
		temp1=temp2;
		temp2=temp3;
		temp3=0.0;
		for(i=j;i<j+320;i++)
			temp3+=(a[i]*a[i]);
		temp3/=320;
		j=j+320;
	}
	return j-320;
}

// Resets the values of variables required in accuracy calculation
void reset_acc_calculations(){
	int i;
	for(i=0;i<=9;i++){
		accuracy_per_digit[i] = 0.0;
	}
	overall_accuracy = 0.0;
	num_correct_outputs = 0;
}

double get_overall_accuracy(){
	return overall_accuracy;
}

//	Loads the initial model
void load_initial_model(){
	FILE *myFile=fopen("A_initial.txt","r");
	int i,j;

	for(i=1;i<=N;i++){
		for(j=1;j<=N;j++){
			fscanf(myFile,"%Lf",&A[i][j]);
		}
	}
	fclose(myFile);

	myFile=fopen("B_initial.txt","r");

	for(i=1;i<=N;i++){
		for(j=1;j<=M;j++){
			fscanf(myFile,"%Lf",&B[i][j]);
		}
	}
	fclose(myFile);
}


//	Loads the average model 
void load_average_model(int digit,int iter){
	int i,j;
	char filename[100];
	sprintf(filename,"lambdas/word%d_A%d_matrix.txt",digit,iter);
	FILE *myFile = fopen(filename, "r");
	
	for(i=1;i<=N;i++){
		for(j=1;j<=N;j++){
			fscanf(myFile,"%Le",&A[i][j]);
		}
	}
	fclose(myFile);

	sprintf(filename,"lambdas/word%d_B%d_matrix.txt",digit,iter);
	myFile = fopen(filename, "r");
	
	for(i=1;i<=N;i++){
		for(j=1;j<=M;j++){
			fscanf(myFile,"%Le",&B[i][j]);
		}
	}
	fclose(myFile);
}


//	resets the model to zero
void reset_model(){
	int i,j;
	for(i=1;i<=N;i++){
		pi_bar[i]=0;
	}
	
	for(i=1;i<=N;i++){
		for(j=1;j<=N;j++){
			A_bar[i][j]=0;
		}
	}
	
	for(i=1;i<=N;i++){
		for(j=1;j<=M;j++){
			B_bar[i][j]=0;
		}
	}
}

//	Perform DC shift and normalization on the recorded data
void preprocess(double arr[], int n){
  double peak_value=fabs(arr[0]);
  int i;
  for(i=0;i<n;i++){
	if(fabs(arr[i]) > peak_value){
		peak_value=fabs(arr[i]);
		}
   }

  double normalization_factor = 5000.0 / peak_value, dc_shift = 0.0;

  i=0;
  while (i<n){
    dc_shift += arr[i];
    i++;
  }
  dc_shift /= (double)n;

  for(i=0;i<n;i++){
    arr[i] -= dc_shift;
    arr[i] *= normalization_factor;
  }
}

//	Computes Ri values
void compute_Ri(double arr[],double R[]){
  int i,j;

  for(i=0;i<=p;i++){
 	R[i]=0;
 	for(j=0;j<=319-i;j++){	
 		R[i]+=arr[j]*arr[i+j];
	}
   }
}

//	Compute Ai values
void compute_Ai(double r[],double a[]){
	double e[13];
	double k[13];
	double x[13][13];
	int i,j;
	double s=0.0;

	e[0]=r[0];

	for(i=1;i<=p;i++){	
		for(j=1;j<=i-1;j++){
			s+=x[i-1][j]*r[i-j];
		}
		k[i]=(r[i]-s)/e[i-1];
		x[i][i]=k[i];	
    
		for(j=1;j<=(i-1);j++){
			x[i][j]=x[i-1][j]-k[i]*x[i-1][i-j];
		}
		e[i]=(1-k[i]*k[i])*e[i-1];
		s=0.0;
	}
		
	for(i=1;i<=p;i++){
		a[i]=x[p][i];
	}
}

//	Compute Ci values
void compute_Ci(double a[],double c[]){
  double s = 0.0;
  int i,j;
  c[0] = log10(r[0]*r[0]);

  for(i=1;i<=p;i++){
	for(j=1;j<=i-1;j++){
		s+=((double)j/(double)i)*c[j]*a[i-j];
	}
	c[i]=a[i]+s;
	s=0;
   }
}


//	Calculates the tokhura distance
void calculate_tokhura_dist(double ct[150][13]){
	int i,j,t;
	for(t=1;t<=T;t++){
		for(i=1;i<=32;i++){
			double dist=0;
			for(j=1;j<=12;j++){
				dist+=tokhura_weights[j] * (ct[t][j]-codebook[i][j])*(ct[t][j]-codebook[i][j]);
			}
			dist_cepstral[i]=dist;
		}

		double min_val=dist_cepstral[1];
		int min_idx=1;
		for(i=2;i<=32;i++){
			if(dist_cepstral[i]<min_val){
				min_val=dist_cepstral[i];
				min_idx=i;
			}
		}
		O[t]=min_idx;
	}
}

//	Computes the Alpha matrix
void forward_procedure(){
	long double Prob=0.0;
	int i,j,t;

	for(i=1;i<=N;i++){
		Alpha[1][i]=pi[i]*B[i][O[1]];
	}
	
	for(t=1;t<=T-1;t++){
		for(j=1;j<=N;j++){
			long double summation=0.0;
			for(i=1;i<=N;i++){
				summation+=Alpha[t][i]*A[i][j];
			}
			Alpha[t+1][j]=summation * B[j][O[t+1]];
		}
	}
	
	for(int i=1;i<=N;i++){
		Prob+=Alpha[T][i];					
	}
}

//	Computes the Beta matrix
void backward_procedure(){
	int i,j,t;
	for(i=1;i<=N;i++){
		Beta[T][i]=1.0;
	}

	for(t=T-1;t>=1;t--){
		for(i=1;i<=N;i++){
			long double summation=0;
			for(j=1;j<=N;j++){
				summation+=A[i][j]*B[j][O[t+1]]*Beta[t+1][j];
			}
			Beta[t][i]=summation;
		}
	}
}


//	computes the Gamma matrix
void calculate_gamma(){
  int i,j,t;
  for(t=1;t<=T;t++){
    for(j=1;j<=N;j++){
      long double numerator = Alpha[t][j]*Beta[t][j];
      long double denominator = 0.0;
      for(i=1;i<=N;i++){
        denominator+=Alpha[t][i]*Beta[t][i];
      }
      Gamma[t][j] = numerator/denominator;
    }
  }
}


//	Vitarbi Algorithm
void viterbi_algo(){
	int i,j,t;

	//	Initialization
	for(i=1;i<=N;i++){
		Delta[1][i] = pi[i]*B[i][O[1]];
		Psi[1][i] = 0;
	}


	// Recursion
	for(t=2;t<=T;t++){
		for(j=1;j<=N;j++){
			long double temp = 0.0, curr_max = 0.0;
			int idx = 0;
			for(i=1;i<=N;i++){
				temp = Delta[t-1][i] * A[i][j];
				if(temp>=curr_max){
				  curr_max = temp;
				  idx = i;
				}
			}
			Delta[t][j]= curr_max*B[j][O[t]];
			Psi[t][j]=idx;
		}
	}

	// Termination
	long double curr_max = 0.0;
	for(i=1;i<=N;i++){
		long double temp = Delta[T][i];
		if(temp>=curr_max){
		  curr_max = temp;
		  qstar[T] = i;
		}
		Pstar=curr_max;
	}

	//	Path Backtracking
	for(t=T-1;t>=1;t--){
		qstar[t] = Psi[t+1][qstar[t+1]];
	}
}

void re_estimation(){
	int i,j,t,k;
	
	for(t=1;t<=T;t++){
    long double summation = 0.0;
		for(i=1;i<=N;i++){
			for(j=1;j<=N;j++){
				summation+=Alpha[t][i]*A[i][j]*B[j][O[t+1]]*Beta[t+1][j];
			}
		}
		for(i=1;i<=N;i++){
			for(j=1;j<=N;j++){
				Xi[t][i][j] = Alpha[t][i]*A[i][j]*B[j][O[t+1]]*Beta[t+1][j] / summation;
			}
		}
	}


	for(i=1;i<=N;i++){
		pi[i]=Gamma[1][i];
	}

	for(i=1;i<=N;i++){
		for(j=1;j<=N;j++){
			long double numerator = 0.0,denominator = 0.0;
			for(t=1;t<=T-1;t++){
				numerator+=Xi[t][i][j];
				denominator+=Gamma[t][i];
			}
			A[i][j]=numerator/denominator;		
		}
	}

	for(i=1;i<=N;i++){
    for(j=1;j<=M;j++){
      long double numerator = 0.0,denominator = 0.0;

      for(t=1;t<=T;t++){
        if(O[t]==j){
          numerator+=Gamma[t][i];
        }
        denominator+=Gamma[t][i];
      }
            
      B[i][j] = numerator/denominator;
    }
  }
}

//	Makes B stocahstic if its not a stochastic matrix
void make_B_Stochastic(){
	int i,j;
	for(i=1;i<=N;i++){
		int num_zeros_num_correct_outputs = 0;
		long double max_val = 0.0;
		int max_val_idx = 0;

		for(j=1;j<=M;j++){
			if(B[i][j] > max_val){
				max_val = B[i][j];
				max_val_idx = j;
			}
			if(B[i][j] == 0){
				num_zeros_num_correct_outputs++;
				B[i][j] = pow(10.0,-30);
			}
		}
		B[i][max_val_idx]-=num_zeros_num_correct_outputs*pow(10.0,-30);
	}
}


//	Saves the model into files
void save_model(int k,int iter){
	int i,j;
	char filename[100];
	sprintf(filename,"lambdas/word%d_A%d_matrix.txt",k,(iter+1));
	FILE *myFile = fopen(filename, "w");			
	for(i=1; i<=N; i++){
		for(j=1; j<=N; j++){
			fprintf(myFile, "%Le\t",Avg_A[k][i][j]);
		}
		fprintf(myFile,"\n");
	}
	fclose(myFile);

	sprintf(filename,"lambdas/word%d_B%d_matrix.txt",k,(iter+1));
	myFile = fopen(filename, "w");

	for(i=1; i<=N; i++){
		for(j=1; j<=M; j++){
			fprintf(myFile,"%Le\t", Avg_B[k][i][j]);
		}
		fprintf(myFile, "\n");
	}
	fclose(myFile);
}

//	Gives model for each utterance
void get_models(){
	int i,j;
	for(i=1;i<=20;i++){	
		forward_procedure();
		backward_procedure();
		calculate_gamma();
		viterbi_algo();
		re_estimation();
		make_B_Stochastic();
	}
	make_B_Stochastic();

	for(i=1;i<=N;i++){
		pi_bar[i]+=pi[i];
	}
	
	for(i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			A_bar[i][j]+=A[i][j];
		}
	}
	
	for(i=1;i<=N;i++){
		for(j=1;j<=M;j++){
			B_bar[i][j]+=B[i][j];
		}
	}
}


//	Gives average model for each digit
void average(int d){
	int i,j;
	
	for(i=1;i<=N;i++){
		pi_bar[i]/=20;
	}
	
	for(i=1;i<=N;i++){
		for(j=1;j<=N;j++){
			A_bar[i][j]/=20;
		}
	}
	
	for(i=1;i<=N;i++){
		for(j=1;j<=M;j++){
			B_bar[i][j]/=20;
		}
	}
	
	for(i=1;i<=N;i++){
		Avg_pi[d][i]=pi_bar[i];
	}
	
	for(i=1;i<=N;i++){
		for(j=1;j<=N;j++){
			Avg_A[d][i][j]=A_bar[i][j];
		}
	}
	
	for(i=1;i<=N;i++){
		for(j=1;j<=M;j++){
			Avg_B[d][i][j]=B_bar[i][j];
		}
	}

}


//	Training
void train(int iteration){
	for(int i=0;i<=9;i++)//	10 digit
	{
		reset_model();
		for(int j=1;j<=20;j++)//20 utterances each
 		{
			if(iteration==1){
				load_initial_model();
			}
			else{
				load_average_model(i,iteration);
			}
			
			char filename[100];
			sprintf(filename,"Recordings/%d_%d.txt",i,j);

			FILE *myFile = fopen(filename, "r");

			if (myFile != NULL){
				n=0;
    			while (!feof(myFile)){
       				fscanf(myFile,"%lf",&sample[n]);
       				n++;
    			}
			}
 			fclose(myFile);
		
			preprocess(sample,n);
	
			int num_frames = 0;
			double current_frame[320];
			
			int start = energy(sample);
			//for(int i=1,k=start;k<start+ (320*140) && k<n-8000;i++,k+=320){
			for(int i=1,k=start;i<=140 && k<n-8000;i++,k+=240){
				num_frames++;
				for(int lmk = 0; lmk<320; lmk++){
					current_frame[lmk] = sample[lmk+k];
				}

				compute_Ri(current_frame,r);
 				compute_Ai(r,a);
 				compute_Ci(a,c);

 				for(int j=1;j<=12;j++){
					frame_ci[i][j]= c[j];
					frame_ci[i][j] *= (1+ (6.0 * sin((3.14*j)/12.0)));
				}
			}
			T = num_frames;
			calculate_tokhura_dist(frame_ci);
			get_models();
		}
		average(i);
		save_model(i,iteration);
	}
	iteration++;
}


void forward_procedure_test(int actual_digit){
	int i,j,t,k;
	for(k=0;k<=9;k++){
		long double Prob=0.0;

		for(i=1;i<=N;i++){
			Alpha[1][i]=Avg_pi[k][i]*Avg_B[k][i][O[1]];
		}
	
		for(t=1;t<=T-1;t++){
			for(j=1;j<=N;j++){
				long double summation=0.0;
				for(i=1;i<=N;i++){
					summation+=Alpha[t][i]*Avg_A[k][i][j];
				}
				Alpha[t+1][j]=summation * Avg_B[k][j][O[t+1]];
			}
		}
		
		for(int i=1;i<=N;i++){
			Prob+=Alpha[T][i];					
		}
		P[k]=Prob;
	}

	long double max_val=P[0];
	int max_idx=0;
	
	for(i=1;i<=9;i++){
		if(P[i]>max_val)
		{
			max_val=P[i];
			max_idx=i;
		}
	}
	//printf("%d ",max_idx);
	
	/*
  for(i=0;i<=9;i++){
    fprintf(write_p_values, "P value for %d is - %Le\n",i,P[i]);
  }
  fprintf(write_p_values, "\nActual digit : %d, Predicted digit : %d\n",actual_digit,max_idx);

  fprintf(write_p_values, "--------------------------------------------------------\n\n");
  */
  if(max_idx==actual_digit){
		num_correct_outputs++;
		accuracy_per_digit[actual_digit]+=1.0;
  }
}

//	Testing using pre-recorded data (seen data)
void test(){
	//printf("Testing with pre recorded data (Previously seen):-\n");
	
	reset_acc_calculations();
	for(int i=0;i<=9;i++){
		//printf("\nFor Digit %d:\n",i);
		for(int j=1;j<=20;j++){
			char filename[100];
			sprintf(filename,"Recordings/%d_%d.txt",i,j);

			FILE *myFile = fopen(filename, "r");

			int num = 0;
			if (myFile != NULL){
    			while (!feof(myFile)){
					fscanf(myFile,"%lf",&sample[num++]);
    			}
 			}
 			fclose(myFile);
		
			preprocess(sample,num);

		
			int num_frames =0;
			double current_frame[320];

			int start = energy(sample);
			for(int i=1,k=start;i<=140 && k<n-8000;i++,k+=240){
				num_frames++;
				for(int lmk = 0; lmk<320; lmk++){
					current_frame[lmk] = sample[lmk+k];
				}
			
				compute_Ri(current_frame,r);
 				compute_Ai(r,a);
 				compute_Ci(a,c);

 				for(int j=1;j<=12;j++){
					frame_ci[i][j]=c[j];
					frame_ci[i][j] *= (1+ (6.0 * sin((3.14*j)/12.0)));
				}	
			}
			
			T=num_frames;
			calculate_tokhura_dist(frame_ci);

			//fprintf(write_p_values, "For file %s\n",filename);

			forward_procedure_test(i);
		}
	}

	for(int i=0;i<=9;i++){
		accuracy_per_digit[i]/=20.0;
		accuracy_per_digit[i]*=100.0;
  		//printf("\nAccuracy for digit %d is %.2lf %%",i,accuracy_per_digit[i]);
	 }

	overall_accuracy=(num_correct_outputs*100.0)/200.0;
	//printf("\nOverall overall_accuracy: %.2lf %%\n",overall_accuracy);
}


//	Testing using pre-recorded data (unseen data)
void test_offline(){
	reset_acc_calculations();
	//printf("Testing with pre recorded data (Previously unseen):-\n");
	for(int i=0;i<=9;i++){
		//printf("\nFor Digit %d:\n",i);
		for(int j=1;j<=10;j++){
			char filename[100];
			sprintf(filename,"Recordings/test_data/%d_%d.txt",i,j);
			FILE *myFile = fopen(filename, "r");

			int num = 0;
			if (myFile != NULL){
    			while (!feof(myFile)){
					fscanf(myFile,"%lf",&sample[num++]);
    			}
 			}
 			fclose(myFile);
		
			preprocess(sample,num);

		
			int num_frames =0;
			double current_frame[320];

			int start = energy(sample);
			for(int i=1,k=start;i<=140 && k<n-8000;i++,k+=240){
				num_frames++;
				for(int lmk = 0; lmk<320; lmk++){
					current_frame[lmk] = sample[lmk+k];
				}
			
				compute_Ri(current_frame,r);
 				compute_Ai(r,a);
 				compute_Ci(a,c);

 				for(int j=1;j<=12;j++){
					frame_ci[i][j]=c[j];
					frame_ci[i][j] *= (1+ (6.0 * sin((3.14*j)/12.0)));
				}	
			}
			
			T=num_frames;
			calculate_tokhura_dist(frame_ci);
			forward_procedure_test(i);
		}
	}


  for(int i=0;i<=9;i++){
    accuracy_per_digit[i]/=10.0;
    accuracy_per_digit[i]*=100.0;
  	//printf("\nAccuracy for digit %d is %.2lf %%",i,accuracy_per_digit[i]);

  }

   overall_accuracy=(num_correct_outputs*100.0)/100.0;
   //printf("\nOverall overall_accuracy: %.2lf %%\n",overall_accuracy);

}


//	Testing using live data
int test_livedata(){
	//reset_acc_calculations();

	system(".\\Recording_module.exe 3 live_data.wav live_data.txt");
	FILE *myFile = fopen("live_data.txt", "r");

	int num = 0;
	
	while (!feof(myFile)){
		fscanf(myFile,"%lf",&sample[num++]);
	}
	
	fclose(myFile);

	preprocess(sample,num);


	int num_frames =0;
	double current_frame[320];

	int start = energy(sample);
	for(int i=1,k=start;i<=140 && k<n-8000;i++,k+=240){
		num_frames++;
		for(int lmk = 0; lmk<320; lmk++){
			current_frame[lmk] = sample[lmk+k];
		}
	
		compute_Ri(current_frame,r);
		compute_Ai(r,a);
		compute_Ci(a,c);

		for(int j=1;j<=12;j++){
			frame_ci[i][j]=c[j];
			frame_ci[i][j] *= (1+ (6.0 * sin((3.14*j)/12.0)));
		}	
	}
	
	T=num_frames;
	calculate_tokhura_dist(frame_ci);

	int i,j,t,k;
	for(k=0;k<=9;k++){
		long double temp=0;
		long double Prob=0;

		for(i=1;i<=N;i++){
			Alpha[1][i]=Avg_pi[k][i]*Avg_B[k][i][O[1]];
		}
	
		for(t=1;t<=T-1;t++){
			for(j=1;j<=N;j++){
				temp=0;
				for(i=1;i<=N;i++){
					temp+=Alpha[t][i]*Avg_A[k][i][j];
				}
				temp*=Avg_B[k][j][O[t+1]];
				Alpha[t+1][j]=temp;
			}
		}
	
		for(i=1;i<=N;i++){
			Prob+=Alpha[T][i];		
		}
		P[k]=Prob;		
	}

	long double max=P[0];
	int maxindex=0;
	
	for(i=1;i<=9;i++){
		if(P[i]>max)
		{
			max=P[i];
			maxindex=i;
		}
	}
	return maxindex;
}