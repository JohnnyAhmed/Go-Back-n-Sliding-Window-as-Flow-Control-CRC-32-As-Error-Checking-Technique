#include<bits/stdc++.h>
#include<fstream>

using namespace std ;

int frame_count,frame_size,data_size,frame_data_size=66,divisor_size=33,buffer[3],buffer_used=0,buffer_size=3,frame_s[100],lost=-1,alost=-1,inf=99999999999,ra;
char frame[100][100],divisor[33],frame_r[100][100];

int count_data_lenght()
{
    /*fstream data;
    data.open("data.txt");
    for (int i=0 ; i <500; i++)
    {
        int a = rand() ;
        a = a%2 ;
        data << a << " " ;
    }
   // data << 1 << " " << 1<< " " << 0 ;
    data.close();*/
    ifstream data_file;
    data_file.open("data.txt");

    int counter=0;
    int x ;

    while(!data_file.eof())
    {
        data_file >> x ;

        counter++ ;
    }

    data_file.close();

    data_size = counter-1 ;
    cout << "count_data_lenght check " << data_size<<endl ;
    return data_size ;
}

int array_size()
{
    count_data_lenght();
    frame_count =(data_size/frame_data_size) ;
    //cout << "array size check " << frame_count<< endl ;
    return frame_count ;
}



void input_from_file( )
{

    ifstream data_file;
    data_file.open("data.txt");
    array_size() ;
    int d =data_size,n ;

    for(int i=0 ; i<=frame_count ; i++)
    {
        if(i%4==0)
        {
            frame[i][0] ='0' ;
            frame[i][1] ='0' ;
        }
        if(i%4==1)
        {
            frame[i][0] ='0' ;
            frame[i][1] ='1' ;
        }
        if(i%4==2)
        {
            frame[i][0] ='1' ;
            frame[i][1] ='0' ;
        }
        if(i%4==3)
        {
            frame[i][0] ='1' ;
            frame[i][1] ='1' ;
        }


        n=d;
        if(d>frame_data_size)
            n=frame_data_size;

        //cout << n <<endl;
        for(int j=1 ; j<=n  ; j++)
        {
            char x ;
            data_file >> x ;
            frame[i][j] = x ;
            //cout << x <<endl ;

        }
        frame_s[i]=n+32;
        d = d-frame_data_size ;
    }

    data_file.close();

}

void print_data()
{
    int d =data_size,n ;
    for(int i=0 ; i<=frame_count ; i++)
    {
        cout << "frame " << i << ": " ;

       //  n=d;
        //if(d>frame_data_size)
          //  n=frame_data_size;


        for(int j=0 ; j<=99  ; j++)
        {
            cout << frame[i][j] ;
        }
       // d = d-frame_data_size ;
        cout << endl;
    }
}

void divisior_generate()
{
    for(int i=0 ; i<=divisor_size ; i++)
    {
        if(i==0 || i==1|| i==2|| i==4 || i==6|| i==7 ||i==10 || i==11|| i==12|| i==16 || i==22|| i==23|| i==26||i==32)
        {
            divisor[32-i] = '1' ;
        }
        else
            divisor[32-i] = '0';
    }

    cout << "divisor : ";
    for(int i=0 ; i<=divisor_size ; i++)
        cout << divisor[i];
    cout << endl;
}

int check_error(char f[100],int s)
{
   // cout << "checking : "<<endl;

    char crc[100];

    for(int i=0 ; i<=99 ; i++)
    {
        crc[i] = f[i] ;
    }
    int d =data_size,n ;

        for(int j=2; j<=frame_data_size+1 ; j++)
        {

            if(divisor[0]==crc[j])
            {
                for(int k=0 ; k<divisor_size ; k++)
                {
                    if(divisor[k]==crc[k+j])
                    {
                        crc[k+j] = '0';
                       // cout << "a";
                    }

                    else
                    {
                        crc[k+j] = '1' ;

                    }

                }
            }

        }

    for(int i=2; i<s; i++)
    {
        //cout <<crc[i] ;
        if(crc[i]=='1')
            return 1 ;
    }
    //cout <<endl;


     return 0 ;

}

void crc_genarte()
{
    char crc[100],fcs[31];



    int d =data_size,n ;

    for(int i=0 ; i<=frame_count ; i++)
    {
         for(int i=0 ; i<=99 ; i++)
    {
        crc[i] = '0' ;
    }
        n=d;
        if(d>frame_data_size)
            n=frame_data_size;

        for(int j=2 ; j<=n  ; j++)
        {
            crc[j] = frame[i][j];
        }
        d = d-frame_data_size ;
      //cout << "frame " << i <<endl ;
      //for(int j=1; j<=n+32 ; j++)
       //     cout << crc[j];
      //  cout<<endl ;
        for(int j=2; j<=n+1 ; j++)
        {

            if(divisor[0]==crc[j])
            {
                for(int k=0 ; k<divisor_size ; k++)
                {
                    if(divisor[k]==crc[k+j])
                    {
                        crc[k+j] = '0';
                       // cout << "a";
                    }

                    else
                    {
                        crc[k+j] = '1' ;
                      //  cout << "b" ;
                    }

                }
            }
          //  for(int j=1; j<=n+32 ; j++)
          //  cout << crc[j];
       // cout<<endl ;

        }
       // for(int j=1; j<=n+32 ; j++)
       //     cout << crc[j];
     //   cout<<endl ;
        int a =n+32;

        for(int j=0; j<divisor_size-1 ; j++)
        {

            frame[i][a] = crc [a] ;
            a-- ;

        }

      //cout <<endl<<endl;


    }

}
void transmitter()
{
    cout << "\t\t\tGENARATING FRAME WITH FSC CODE " <<endl ;
    input_from_file();
    //cout << "BASIC INFO "
    divisior_generate();
    crc_genarte();
}

int reciver()
{
    int i ,l=-1,j,flag=0;

    for( i=0 ; i<buffer_used ; i++)
    {
        cout << "frame " << buffer[i] ;
        if(lost==buffer[i])
        {
            l=1 ;
            j=i;
            cout << " not recieved"<<endl;
            continue;
        }
        else
        {
            cout << " recieved "<<endl;
        }


    }

    if(i==buffer_size&&l==-1)
        cout << "buffer is full " <<endl ;



    cout <<endl <<  "PROCESSING " <<endl ;

    for(int  i=0 ; i<buffer_used ; i++)
    {
        cout << "frame " << buffer[i]  ;

        if(lost==buffer[i])
        {
            flag=1;
        }
        if(flag == 1  )
         {
              cout <<" discarded" ;
         }

         if(check_error(frame_r[buffer[i]],frame_s[buffer[i]])==1 && flag==0&&l==-1)
         {
            cout << " error"  ;
            j = i ;
            flag = 1 ;
         }
         if(flag==0)
            cout << " no error" ;
         cout <<endl ;
    }

    if(flag==1)
    {
        cout << "NACK " << buffer[j]<<endl; ;
        return -buffer[j];
    }
    if(alost==1)
    {
        cout << "ACK lost " <<endl;
        return inf ;

    }



    //cout << "asfdasf " <<buffer[i] <<endl ;
    return buffer[i-1]+1;

}

void random(int f)
{
    lost = -1 ;
    alost = -1 ;
    srand((int)time(NULL));
    int x = rand();
    //cout <<x  <<endl;
    x = x%4;
    if (x==0)           //0 no error
          for(int i=0 ; i<=frame_count ; i++)
              for(int j=0 ; j<=frame_s[i] ; j++)
                frame_r[i][j] = frame[i][j] ;


    if(x==1)               //1 error
    {
        //cout <<"x=1"<<endl;
        for(int i=0 ; i<=frame_count ; i++)
              for(int j=0 ; j<=frame_s[i] ; j++)
                frame_r[i][j] = frame[i][j] ;

        int y=rand();
        y = y%frame_count;
        if(y>=f)
        {
            int z=rand()*rand();
            z=z%frame_data_size ;
            if(z>1)
            {
              //  cout << "check "<<endl;
                if(frame_r[y][z] =='1')
                    frame_r[y][z] = '0';
                else
                    frame_r[y][z] = '1' ;
            }
           // cout << "a";
        }
    }
    if(x==2)                                //2 lost frame
    {
        for(int i=0 ; i<=frame_count ; i++)
              for(int j=0 ; j<=frame_s[i] ; j++)
                frame_r[i][j] = frame[i][j] ;

        int y=rand();
        y = y%frame_count;
        if(y<=frame_count)
        {
            lost=y;
           // cout << lost <<endl;
        }
    }

    if(x==3)                    //3 ack lost
    {
         for(int i=0 ; i<=frame_count ; i++)
              for(int j=0 ; j<=frame_s[i] ; j++)
                frame_r[i][j] = frame[i][j] ;
       alost = 1 ;
    }
}

void transmission()
{
    cout << "\t\t\tTRANSIMISSION" <<endl ;

    int ACK=0;



    while(ACK<=frame_count)
    {
        if(ra==1)
            random(ACK);
        buffer_used=0;

        for(int i=0 ; i<buffer_size ; i++)
        {
            if(ACK+i>frame_count)
                break ;
            buffer[i] = ACK+i;
        //    cout << buffer[i] <<endl;
            buffer_used++;
        }

        int ack = reciver();
        if(ack==inf)
        {
            ACK=ACK ;
        }
        if(ack>0&&ack<inf)
        {
            ACK=ack;
            cout << "ACK " << ACK <<endl ;
        }
        if(ack<=0)
        {
            ack = ack*-1 ;
            ACK=ack;

        }

        cout << endl ;

    }
    cout << "\t\t\tTransmission complete "<<endl<<endl ;
}


int main()
{
    ra=inf;
    cout << "0=no error\t1=random error : " ;
    cin >> ra ;
    transmitter();
    print_data();

    // cout << buffer[2] ;
    transmission();
    /*for(int i=0; i<=6 ; i++)
    {
        cout << endl << "frame " << i  ;
        if(check_error(frame[i],99)==1)
            cout << "error"<<endl;
        else
            cout << "no error" <<endl ;
    }*/

}
