#include<bits/stdc++.h>
#include<omp.h>
#include<sys/time.h>

#define M 512
#define N 1

using namespace std;

int a[M][M], b[M][N], c[M][N] ,sum;

int main(){
	int i,j,k;
	struct timeval tv1, tv2;

	srand(time(0));

	for(i=0;i<M;i++)
		for(j=0;j<M;j++)
			a[i][j] = rand()%M;

	for(i=0;i<M;i++)
		for(j=0;j<N;j++)
			b[i][j] = rand()%M;
	
	for(i=0;i<M;i++)
                for(j=0;j<N;j++)
                        c[i][j] = 0;



	cout<<"Processes: "<<omp_get_num_procs()<<endl;
	gettimeofday(&tv1,NULL);
	#pragma omp parallel private(i,j,k) shared(a,b,c) reduction(+:sum)
	for(i=0;i<M;i++){
		for(j=0;j<N;j++){
			//c[i][j] = 0;
			sum = 0;
			for(k=0;k<M;k++){
				//c[i][j] += a[i][k] * b[k][j];
				sum += a[i][k] * b[k][j];
				c[i][j] = sum;
			}
		}
	}

	gettimeofday(&tv2,NULL);

	double timetaken = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
	cout<<"Time: "<<timetaken<<endl;
/*
	for(i=0;i<M;i++){
                for(j=0;j<M;j++)
                        cout<<a[i][j]<<" ";
		cout<<endl;
	}

	cout<<endl;
	for(i=0;i<M;i++){
                for(j=0;j<N;j++)
                        cout<<b[i][j]<<" ";
                cout<<endl;
        }

	cout<<endl;
	for(i=0;i<M;i++){
                for(j=0;j<N;j++)
                        cout<<c[i][j]<<" ";
                cout<<endl;
        }
*/
	return 0;
}
