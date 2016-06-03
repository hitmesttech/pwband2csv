#include<cstdio>
#include<cmath>
#include<cstring>
#include <vector>
#include <algorithm>  
#include <functional>

using namespace std;

class kpd{
public:
  double e[200];//energy
  double k123[3];//coordinates
};

//typedef kpd kpoint_data;

#define eps 1e-6

static inline int kp_greater(kpd a,kpd b)
{
  int i=0;
  if(a.k123[0]>b.k123[0])
    i=1;
  else if( fabs(a.k123[0]-b.k123[0])<eps && a.k123[1]>b.k123[1] )
    i=1;
  else if( fabs(a.k123[0]-b.k123[0])<eps && fabs(a.k123[1]-b.k123[1])<eps && a.k123[2]>b.k123[2])
    i=1;
  return i;
}

int main(int argc, char * argv[])
{
  int nband,nks,i,j;
  double *kpe;
  std::vector<kpd> kpdata;
  FILE *in,*ou;
  
  /* if(argv[1][0]!='<')
    {
      printf("Error with argv\n");
      return 0;
    }
  argv[1][strlen(argv[1])-2]=0;*/
  in=fopen(argv[1],"r");
  ou=fopen(argv[2],"w+");
  fscanf(in," &plot nbnd=%d, nks=%d /",&nband,&nks);
  printf("%d band, %d k point\n",nband,nks);
  for(i=0;i<nks;i++)
    {
      kpd tpd;
      fscanf(in,"%lf%lf%lf",tpd.k123,tpd.k123+1,tpd.k123+2);
      for(j=0,kpe=tpd.e;j<nband;j++,kpe++)
	{
	  fscanf(in,"%lf",kpe);
	}
      kpdata.push_back(tpd);
    }
  std::sort(kpdata.begin(),kpdata.end(),kp_greater);
  fprintf(ou,"n,kn1,kn2,kn3,");
  for(i=0;i<nband;i++)
    {
      fprintf(ou,"kn%d,",i);
    }
  fprintf(ou,"\n");
  i=0;
  for(vector<kpd>::iterator it=kpdata.begin();it!=kpdata.end();it++,i++)
   {
     fprintf(ou,"%lf,%lf,%lf,%lf,",double(i)/double(nks),it->k123[0],it->k123[1],it->k123[2]);
     for(j=0,kpe=it->e;j<nband;j++,kpe++)
       {
	 fprintf(ou,"%lf,",*kpe);
       }
     fprintf(ou,"\n");
   }
  fclose(in);
  fclose(ou);
  return 0;
}

