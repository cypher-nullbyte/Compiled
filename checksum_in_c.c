// COMPLETE CHECKSUM ELABORATION:- https://www.youtube.com/watch?v=SkJWDOUJJwA


#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int* decToBin(int dec,int n)
{
    int * bin=(int *)calloc(n,sizeof(int));
    for(int i=n-1;i>=0;i--)
    {
        bin[i]=dec%2;
        dec/=2;
    }
    return bin;
}

void checksumGen(int **data,int n,int k)
{
    int carrynum=0;
    for(int j=k-1;j>=0;j--)
    {
        int sum=0;
        for(int i=0;i<n;i++)
        {
            sum+=data[i][j];
        }
        sum+=carrynum;
        data[n][j]=sum%2;
        carrynum=sum>0 ? sum>>1 : 0;
    }
    int *carry=decToBin(carrynum,k);

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<k;j++)
        {
            printf("%d ",data[i][j]);
        }
        printf("<-Segment [%d] \n",(i+1));
    }
    printf("-----------------\n");
    for(int j=0;j<k;j++)
        printf("%d ",data[n][j]);
    printf("<-Sum1\n");
    carrynum=0;
    for(int i=k-1;i>=0;i--)
    {
        int sum=carrynum+carry[i]+data[n][i];
        data[n][i]=sum%2;
        carrynum=sum>0 ? sum>>1 : 0;
    }
    for(int i=0;i<k;i++)
        printf("%d ",carry[i]);
    printf("<-Carry\n");
    printf("-----------------\n");
    for(int i=0;i<k;i++)
    {   
        printf("%d ",data[n][i]);
        data[n][i]= data[n][i]==0 ? 1 : 0;
    }
    printf("<-Sum2\n");
    printf("-----------------\n");
    for(int i=0;i<k;i++)
    {
        printf("%d ",data[n][i]);
    }
    printf("<-CHECKSUM\n");
}

void checksumChk(int **data,int n,int k)
{
    int *chkBucket=(int *)calloc(k,sizeof(int));
    int carrynum=0;
    for(int j=k-1;j>=0;j--)
    {
        int sum=0;
        for(int i=0;i<=n;i++)
        {
            sum+=data[i][j];
        }
        sum+=carrynum;
        chkBucket[j]=sum%2;
        carrynum=sum>0 ? sum>>1 : 0;
    }
    int *carry=decToBin(carrynum,k);

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<k;j++)
        {
            printf("%d ",data[i][j]);
        }
        printf("<-Segment [%d] \n",(i+1));
    }
    for(int i=0;i<k;i++)
    {
        printf("%d ",data[n][i]);
    }
    printf("<-CHECKSUM (Receiver)\n");
    printf("-----------------\n");
    for(int j=0;j<k;j++)
        printf("%d ",chkBucket[j]);
    printf("<-Sum1\n");
    carrynum=0;
    for(int i=k-1;i>=0;i--)
    {
        int sum=carrynum+carry[i]+chkBucket[i];
        chkBucket[i]=sum%2;
        carrynum=sum>0 ? sum>>1 : 0;
    }
    for(int i=0;i<k;i++)
        printf("%d ",carry[i]);
    printf("<-Carry\n");
    printf("-----------------\n");
    for(int i=0;i<k;i++)
    {
        printf("%d ",chkBucket[i]);
        chkBucket[i]=chkBucket[i]==0 ? 1 : 0;
    }
    printf("<-Sum2\n");
    printf("-----------------\n");
    bool accept=true;
    for(int i=0;i<k;i++)
    {
        printf("%d ",chkBucket[i]);
        if(chkBucket[i]!=0)
            accept=false;
    }
    printf("<-CHECKSUM\n");
    printf("%s",(accept ? "Accepted!" : "Rejected!"));
    printf("\n");
}

int main()
{
    printf("Welcome to CHECKSUM Generation and Validation Program by cYpHeR\n");
    int n,k;
    printf("Enter no of Segmets: ");
    scanf("%d",&n);
    printf("Enter bit lenght of each segmet: ");
    scanf("%d",&k);
    int len=(n+1)*sizeof(int *)+ (n+1)*(k)*sizeof(int);
    int **data=(int **)malloc(len);
    int * ptr=(int *)(data+n+1);
    for(int i=0;i<n+1;i++)
        data[i]=(ptr+k*i);
    for(int i=0;i<n;i++)
    {
        printf("Enter segment[%d] (space separated): ",(i+1));
        for(int j=0;j<k;j++)
        {
            scanf("%d",&data[i][j]);
        }
    }
    checksumGen(data,n,k);
    printf("\nNow sender is sending the segments with checksum ... \n\n");
    printf("------------------------------------------\n");
    printf("Hello Transmission channel do you want to alter message (y/n): ");
    char choice;scanf(" %c",&choice);
    switch(choice)
    {
        case 'y':
            printf("You are supposed to enter %d segments of %d length!\n",n,k);
            for(int i=0;i<n;i++)
            {
                printf("Enter segment[%d] (space separated): ",(i+1));
                for(int j=0;j<k;j++)
                {
                    scanf("%d",&data[i][j]);
                }
            }
            printf("Enter the checksum (space separated): ");
            for(int j=0;j<k;j++)
                scanf("%d",&data[n][j]);
            break;
        case 'n':
            printf("Transmission successfull without error!\n");
            break;
    }
    checksumChk(data,n,k);
}
