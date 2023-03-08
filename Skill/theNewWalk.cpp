#include "theNewWalk.h"

/*
#define HIP 0.055
#define THIGH 0.135
#define SHANK 0.11
*/

#define SLOW_FOOTLENGTH_INCREAMENT 0.001
//#define SLOW_FOOTLENGTH_INCREAMENT 0.001
#define SLOW_FOOTLENGTH_INCREAMENTwidth 0.001
#define QUICK_FOOTLENGTH_INCREAMENT 0.003
#define QUICK_FOOTLENGTH_INCREAMENTwidth 0.0025



#define HORIZONMOVEMAXSPEED 0.1
#define HORIZONMOVEMIDSPEED 0.065
#define HORIZONMOVEMINSPEED 0.01

///#define FOOTLENGTH_TEST
#define FENGWALK
///#define USECAIWALK
///#define JointAngleOutput
//#define footp
//#define allWeightOnFoot
//#define COM
//#define ZMP
//#define walkTest

//#define MRLI
//#define MOVE 0.01

//#define jointRecord

//#define ApolloData
#define fengData
/*
#ifdef ApolloData
#define BODYHEIGHT 0.24
#else
#define BODYHEIGHT 0.24
#endif
*/
#define MAX_FOOT_HIGH 0.029//0.033
//#define MAX_FOOT_HIGH1 0.028


#define FOOT_CYCLE 8
#define FOOT_8
///#define SIX

#define MULTIPLE 0.001
#define BODYFORERAKEANGLE 45


//#define sendMessageTest

#ifdef SIX
	#define FOOTXA 0.022
	#define FOOTXB 0.033
	#define FOOTXC 0.033
	#define FOOTXD 0.022
	#define FOOTXE 0.012
	#define FOOTXF 0.00
#endif


extern WorldModel wm;
extern JointEffector mp;
extern Perceptor messageParser;
extern Logger myZMPLogger;
extern Logger myCOMLogger;
extern Agent agent;

extern Logger myRLEG_J1Logger;
extern Logger myRLEG_J2Logger;
extern Logger myRLEG_J3Logger;
extern Logger myRLEG_J4Logger;
extern Logger myRLEG_J5Logger;

extern Logger myLLEG_J1Logger;
extern Logger myLLEG_J2Logger;
extern Logger myLLEG_J3Logger;
extern Logger myLLEG_J4Logger;
extern Logger myLLEG_J5Logger;




	BasicMotion passBall;



void NewWalk::FindMother(int j)
{
	if(j!=0)
	{
		if(j==1)
			uLINK[j].mother=0;
		if (uLINK[j].child!=0)
		{
			uLINK[uLINK[j].child].mother=j;
			FindMother(uLINK[j].child);
			//std:://///////////////cout<<"uLINK[j].child:"<<uLINK[j].child<<std::endl;
		}
		if (uLINK[j].sister!= 0)
		{
			uLINK[uLINK[j].sister].mother=uLINK[j].mother;
			FindMother(uLINK[j].sister);
			//std:://///////////////cout<<"uLINK[j].sister:"<<uLINK[j].sister<<std::endl;
		}
    }
}

float NewWalk::norm(boost::numeric::ublas::vector<float>  w)
{
  //  std:://///////////////cout<<"norm begin"<<std::endl;
	float a;
	a=sqrt(w(0)*w(0)+w(1)*w(1)+w(2)*w(2));
	return a;
}

boost::numeric::ublas::matrix<float> NewWalk::Rodrigues(boost::numeric::ublas::vector<float> w,float dt)
{
	boost::numeric::ublas::matrix<float> RR(3,3),st(3,3);
	//float norm(vector<float>  w);
    float ww=norm(w);
	float th= ww*dt;


    /*vector<float> aaa(3);
    aaa(0)=2;aaa(1)=3;aaa(2)=4;
    float qq=norm(aaa);
    std:://///////////////cout<<"00000000000000000000 :"<<qq<<std::endl;
*/
	boost::numeric::ublas::vector<float>  wn = w/ww;

    boost::numeric::ublas::matrix<float> w_wedge(3,3);
    w_wedge(0,0)=0;             w_wedge(0,1)=-wn(2);  w_wedge(0,2)=wn(1);
    w_wedge(1,0)=wn(2);        w_wedge(1,1)=0;        w_wedge(1,2)=-wn(0);
    w_wedge(2,0)=-wn(1);       w_wedge(2,1)=wn(0);   w_wedge(2,2)=0;

    st(0,0)=1;st(0,1)=0;st(0,2)=0;
	st(1,0)=0;st(1,1)=1;st(1,2)=0;
	st(2,0)=0;st(2,1)=0;st(2,2)=1;
	float w1=sin(th);
	float w2=cos(th);

	RR=st+w_wedge*w1+prod(w_wedge,w_wedge)*(1.0-w2);
//    std:://///////////////cout<<"RRRRRRRRRRRRRRRRRRR"<<std::endl;
//    std:://///////////////cout<<RR<<std::endl;
	return RR;

}
void NewWalk::ForwardKinematics(int j)
{    if (j==0)
		return;
	matrix<float> RR(3,3);


   // std:://///////////////cout<<"check for whether sth wrong"<<std::endl;


	if (j!= 1)
    {

		int mom=uLINK[j].mother;
		uLINK[j].p=prod(uLINK[mom].R,uLINK[j].b) + uLINK[mom].p;
		RR=Rodrigues(uLINK[j].a, uLINK[j].q);
//		std:://///////////////cout<<"j:"<<j<<std::endl;
//		std:://///////////////cout<<"RR:"<<RR<<std::endl;
    //    std:://///////////////cout<<"uLINK[mom].R:"<<uLINK[mom].R<<std::endl;
		uLINK[j].R=prod(uLINK[mom].R,RR);

        if(fabs(uLINK[j].R(0,0))<0.0001)
		uLINK[j].R(0,0)=0;
		if(fabs(uLINK[j].R(0,1))<0.0001)
		uLINK[j].R(0,1)=0;
		if(fabs(uLINK[j].R(0,2))<0.0001)
		uLINK[j].R(0,2)=0;
		if(fabs(uLINK[j].R(1,0))<0.0001)
		uLINK[j].R(1,0)=0;
		if(fabs(uLINK[j].R(1,1))<0.0001)
		uLINK[j].R(1,1)=0;
		if(fabs(uLINK[j].R(1,2))<0.0001)
		uLINK[j].R(1,2)=0;
		if(fabs(uLINK[j].R(2,0))<0.0001)
		uLINK[j].R(2,0)=0;
		if(fabs(uLINK[j].R(2,1))<0.0001)
		uLINK[j].R(2,1)=0;
		if(fabs(uLINK[j].R(2,2))<0.0001)
		uLINK[j].R(2,2)=0;

//		std:://///////////////cout<<"uLINK[j].R"<<uLINK[j].R<<std::endl;
	}

/*
    if(j==6||j==7||j==12||j==13)
    {
        uLINK[j].R(0,0)=1;uLINK[j].R(0,1)=0;uLINK[j].R(0,2)=0;
        uLINK[j].R(1,0)=0;uLINK[j].R(1,1)=1;uLINK[j].R(1,2)=0;
        uLINK[j].R(2,0)=0;uLINK[j].R(2,1)=0;uLINK[j].R(2,2)=1;
    }
  */
/*
if(j==13)
{
	  std:://///////////////cout<<"uLINK["<<j<<"].p:"<<std::endl<<uLINK[j].p<<std::endl;
	  std:://///////////////cout<<"uLINK["<<j<<"].a:"<<std::endl<<uLINK[j].a<<std::endl;
	std:://///////////////cout<<"uLINK["<<j<<"].R:"<<std::endl<<uLINK[j].R<<std::endl<<std::endl;

}
*/
  	ForwardKinematics(uLINK[j].sister);

	ForwardKinematics(uLINK[j].child);
}


float NewWalk::TotalMass(int j)
{
	float mass;
	if(j==0)
		mass=0;
	else
	{
		mass=uLINK[j].m+TotalMass(uLINK[j].sister)+TotalMass(uLINK[j].child);
	}

	return mass;
}

std::vector<int> NewWalk::FindRoute(int to)
{
	std::vector<int> idx,idx2;

	int i = uLINK[to].mother;

	if(i==1)
		idx.insert(idx.begin(),to);
	else
	{
		idx2=FindRoute(i);
		idx=idx2;
		idx.push_back(i+1);
	}
	return idx;
}

boost::numeric::ublas::vector<float> NewWalk::cross(boost::numeric::ublas::vector<float> a,boost::numeric::ublas::vector<float> b)
{
   boost::numeric::ublas::vector<float> c(3);
    c(0)=a(1)*b(2)-b(1)*a(2);
    c(1)=a(2)*b(0)-a(0)*b(2);
    c(2)=a(0)*b(1)-b(0)*a(1);
    return c;
}

boost::numeric::ublas::matrix<float> NewWalk::CalcJacobian(std::vector<int> idx)
{
    
    int j;
    boost::numeric::ublas::vector<float> a(3),b(3);
    int jsize=idx.size();
    int k=idx.back();
    boost::numeric::ublas::vector<float> target=uLINK[k].p;
  //  target(0)=(0);target(1)=uLINK[k].p(1);target(2)=uLINK[k].p(2);
    boost::numeric::ublas::matrix<float> J(6,6);

    for(int n=0;n<jsize;n++)
    {
        j=idx[n];
        a=prod(uLINK[j].R,uLINK[j].a);


        b=cross(a,(target-uLINK[j].p));
        if(firstStep==true)
        {
           // std:://///////////////cout<<"a:"<<a<<std::endl;
           // std:://///////////////cout<<"target:"<<target<<std::endl;
           // std:://///////////////cout<<"uLINK[j].p:"<<uLINK[j].p<<std::endl;

           // std:://///////////////cout<<"b:"<<b<<std::endl;
        }
        J(0,n)=b(0);J(1,n)=b(1);J(2,n)=b(2);
        J(3,n)=a(0);J(4,n)=a(1);J(5,n)=a(2);

    }
    for(int i=0;i<6;i++)
        for(int j=0;j<6;j++)
        {
            if(fabs(J(i,j))<0.001)
                J(i,j)=0;
        }
    return J;
}




float NewWalk::trace(boost::numeric::ublas::matrix<float> R)
{
    float a=R(0,0)+R(1,1)+R(2,2);
    return a;
}



boost::numeric::ublas::vector<float> NewWalk::rot2omega(boost::numeric::ublas::matrix<float> R)
{

    boost::numeric::ublas::vector<float> w(3);
    float alpha=(trace(R)-1)/2;
   // float alpha=(R(0,0)+R(1,1)+R(2,2)-1)/2.0;
   // std:://///////////////cout<<"alpha:"<<alpha<<std::endl;

     if(abs(alpha-1)<0.001)
     {
         w(0)=0;w(1)=0;w(2)=0;
     }
     else
     {
        float th=acos(alpha);
       // std:://///////////////cout<<"th:"<<th<<std::endl;
        float m=0.5*th/sin(th);
       // std:://///////////////cout<<"m:"<<m<<std::endl;
        w(0)=m*(R(2,1)-R(1,2));
        w(1)=m*(R(0,2)-R(2,0));
        w(2)=m*(R(1,0)-R(0,1));
     }
    return w;
}


void NewWalk::swap(float &a,float &b)
{
    float c=a;
    a=b;
    b=c;
}

boost::numeric::ublas::matrix<float> NewWalk::DinV(boost::numeric::ublas::matrix<float> A,int n)
{
    boost::numeric::ublas::matrix<float> v(n,n);
    int i,j,k;
    float d;
    int JS[n],IS[n];
    for (k=0;k<n;k++)
    {
        d=0;
        for (i=k;i<n;i++)
            for (j=k;j<n;j++)
            {
                if (fabs(A(i,j))>d)
                {
                    d=fabs(A(i,j));
                    IS[k]=i;
                    JS[k]=j;
                }
            }
        if (d+1.0==1.0)
        {
            A(0,0)=0;A(0,1)=0;A(0,2)=0;
            A(1,0)=0;A(1,1)=0;A(1,2)=0;
            A(2,0)=0;A(2,1)=0;A(2,2)=0;
            return A;
        }

        if (IS[k]!=k)
            for (j=0;j<n;j++)
                swap(A(k,j),A(IS[k],j));
        if (JS[k]!=k)
            for (i=0;i<n;i++)
                swap(A(i,k),A(i,JS[k]));
        A(k,k)=1/A(k,k);
        for (j=0;j<n;j++)
            if (j!=k)
                A(k,j)=A(k,j)*A(k,k);
        for (i=0;i<n;i++)
            if (i!=k)
                for (j=0;j<n;j++)
                    if (j!=k)
                        A(i,j)=A(i,j)-A(i,k)*A(k,j);
        for (i=0;i<n;i++)
            if (i!=k)
                A(i,k)=-A(i,k)*A(k,k);
    }
            for (k=n-1;k>=0;k--)
            {
                for (j=0;j<n;j++)
                    if (JS[k]!=k)
                        swap(A(k,j),A(JS[k],j));
                for (i=0;i<n;i++)
                    if (IS[k]!=k)
                        swap(A(i,k),A(i,IS[k]));
            }
            return A;

}



boost::numeric::ublas::matrix<float> NewWalk::CalcVWerr(u Cref,u Cnow)
{
    boost::numeric::ublas::matrix<float> a=DinV(Cnow.R,3);
    boost::numeric::ublas::vector<float> perr=Cref.p-Cnow.p;
    boost::numeric::ublas::matrix<float> Rerr=prod(a,Cref.R);//here ,need to qiu ni    Rerr = Cnow.R^-1 * Cref.R;
    boost::numeric::ublas::vector<float> werr=prod(Cnow.R,rot2omega(Rerr));
    boost::numeric::ublas::matrix<float> err(2,3);
    err(0,0)=perr(0);err(0,1)=perr(1);err(0,2)=perr(2);
    err(1,0)=werr(0);err(1,1)=werr(1);err(1,2)=werr(2);
 //    std:://///////////////cout<<"perr:"<<perr<<std::endl;
 //    std:://///////////////cout<<"werr:"<<werr<<std::endl;

    return err;
}

float NewWalk::norm2(boost::numeric::ublas::matrix<float> err)
{
    float a=sqrt(err(0,0)*err(0,0)+err(0,1)*err(0,1)+err(0,2)*err(0,2)+
                  err(1,0)*err(1,0)+err(1,1)*err(1,1)+err(1,2)*err(1,2));
                  return a;
}

void NewWalk::rightDivide(matrix<float> J,matrix<float> err,float d[])
{
    /*float a[6],b[6];
    for (int n=0;n<6;n++)
    {
        a[n]=J(0,n)*J(0,n)+J(1,n)*J(1,n)+J(2,n)*J(2,n)+J(3,n)*J(3,n)+J(4,n)*J(4,n)+J(5,n)*J(5,n);
        b[n]=1/a[n];
    }*/
    matrix<float> JJ=NewWalk::DinV(J,6);
//    std:://///////////////cout<<"JJJJJJJJJJJJJJJJJJJJJJJJJJJ"<<std::endl;
 //   std:://///////////////cout<<JJ<<std::endl;
    for(int m=0;m<6;m++)
    {
       // d[m]=b[m]*(J(0,m)*err(0,0)+J(1,m)*err(0,1)+J(2,m)*err(0,2)+J(3,m)*err(1,0)+J(4,m)*err(1,1)+J(5,m)*err(1,2));
        d[m]=JJ(m,0)*err(0,0)+JJ(m,1)*err(0,1)+JJ(m,2)*err(0,2)+JJ(m,3)*err(1,0)+JJ(m,4)*err(1,1)+JJ(m,5)*err(1,2);
 //       std:://///////////////cout<<"d:"<<d[m]<<std::endl;
 //       std:://///////////////cout<<"a:"<<a[m]<<std::endl;
 //      std:://///////////////cout<<"b:"<<b[m]<<std::endl;
    }
   // return d;
}


void NewWalk::MoveJoints(std::vector<int> idx,float dq[])
{
    int m=idx.size();
    for(int n=0;n<m;n++)
    {
        int j = idx[n];
  //      std:://///////////////cout<<"dq:"<<dq[n]<<std::endl;
  //      std:://///////////////cout<<"before uLINK["<<j<<"].q:"<<uLINK[j].q<<std::endl;
///////////////////cout<<"@@@@@@@@@@@@@@        j:          "<<j<<endl;
        uLINK[j].q = uLINK[j].q + dq[n];
    //    std:://///////////////cout<<"after uLINK["<<j<<"].q:"<<uLINK[j].q<<std::endl;
    }
}


boost::numeric::ublas::matrix<float> NewWalk::Rroll(float phi)
{
    float c=cos(phi);
    float s=sin(phi);
    boost::numeric::ublas::matrix<float> R(3,3);
    R(0,0)=1;R(0,1)=0;R(0,2)=0;
    R(1,0)=0;R(1,1)=c;R(1,2)=-s;
    R(2,0)=0;R(2,1)=s;R(2,2)=c;
    return R;
}


boost::numeric::ublas::matrix<float> NewWalk::Rpitch(float theta)
{
    float c=cos(theta);
    float s=sin(theta);
    boost::numeric::ublas::matrix<float> R(3,3);
    R(0,0)=c;R(0,1)=0;R(0,2)=s;
    R(1,0)=0;R(1,1)=1;R(1,2)=0;
    R(2,0)=-s;R(2,1)=0;R(2,2)=c;
    return R;
}

float NewWalk::sign(float a)
{
    float b;
    if(a>0)
        b=1;
    else if(a==0)
        b=0;
    else
        b=-1;
    return b;
}

void NewWalk::IK_leg(u body,float D,float A,float B,u foot)
{
    float q2,q3,q4,q5,q6,q7,q6a;
    boost::numeric::ublas::vector<float> r(3),middle(3);
    middle(0)=0;middle(1)=D;middle(2)=0;
    boost::numeric::ublas::matrix<float> f=change(foot.R);
    r=prod(f,(body.p+prod(body.R,middle)-foot.p ));

    float C=norm(r);

    float c5=(C*C-A*A-B*B)/(2.0*A*B);

    if(c5>=1.0)
        q5=0.0;
    else if(c5<=-1.0)
        q5=PI;
    else
        q5=acos(c5);

    q6a=asin((A/C)*sin(PI-q5));
    q7=atan2(r(1),r(2));

    if(q7>PI/2)
        q7=q7-PI;
    else if(q7<-PI/2)
        q7=q7+PI;

    q6=-atan2(r(0),sign(r(2))*sqrt(r(1)*r(1)+r(2)*r(2)) )-q6a;

    boost::numeric::ublas::matrix<float> R(3,3),R1(3,3),R2(3,3);
    R1=prod(change(body.R),foot.R);
    R2=prod(Rroll(-q7),Rpitch(-q6-q5));
    R= prod(R1,R2);

    q2=atan2( -R(0,1),R(1,1)  );

    float cz=cos(q2);
    float sz=sin(q2);
    q3=atan2(R(2,1),(-R(0,1)*sz+R(1,1)*cz));
    q4=atan2(-R(2,0),R(2,2));

	if(foot.name=="Rfoot")
	{
///		/////////////////cout<<"++++++++++++++++++++Rfoot"<<endl;
        	uLINK[RLEG_J0].q=q2;
        	uLINK[RLEG_J1].q=q3;
        	uLINK[RLEG_J2].q=q4;
        	uLINK[RLEG_J3].q=q5;
        	uLINK[RLEG_J4].q=q6;
        	uLINK[RLEG_J5].q=q7;
	}
	else if(foot.name=="Lfoot")
	{
///		/////////////////cout<<"---------------------Lfoot"<<endl;
		 uLINK[LLEG_J0].q=q2;
        	uLINK[LLEG_J1].q=q3;
        	uLINK[LLEG_J2].q=q4;
        	uLINK[LLEG_J3].q=q5;
        	uLINK[LLEG_J4].q=q6;
        	uLINK[LLEG_J5].q=q7;
	}

}


void NewWalk::InverseKinematicsAll(int to,u Target)//J\err==pinv(J)*err==(J'*J)^-1*J'*err
{
	float lambda=0.3;
	ForwardKinematics(1);
	std::vector<int> idx=FindRoute(to);

	boost::numeric::ublas::matrix<float> J(6,6);
	boost::numeric::ublas::matrix<float> err(2,3);
	for(int n=0;n<10;n++)//maybe there will be some probleme with here,the M code: for n = 1:10
	{
        J=CalcJacobian(idx);

        err=CalcVWerr(Target,uLINK[to]);

        if(norm2(err)<1e-6)
            break;
        float dq[6];
        rightDivide(J,err,dq);
        for(int i=0;i<6;i++)
        {
  
            dq[i]=lambda*dq[i];

        }

        MoveJoints(idx,dq);

        ForwardKinematics(1);
	}

        boost::numeric::ublas::vector<float> vd = Target.v - uLINK[1].v - cross(uLINK[1].w, (Target.p - uLINK[1].p));
        boost::numeric::ublas::vector<float> wd = Target.w - uLINK[1].w;
        boost::numeric::ublas::matrix<float> vdwd(2,3);
        vdwd(0,0)=vd(0);vdwd(0,1)=vd(1);vdwd(0,2)=vd(2);
        vdwd(1,0)=wd(0);vdwd(1,1)=wd(1);vdwd(1,2)=wd(2);
         float vq[6];
          J=CalcJacobian(idx);
        rightDivide(J,vdwd,vq);

        for(int y=0;y<6;y++)
        {
            int g=idx[y];
            uLINK[g].dq=vq[y];

        }
}



void NewWalk::ForwardVelocity(int j)
{
    if(j==0)
        return;
    else if(j!=1)
    {
        int mom=uLINK[j].mother;
        uLINK[j].v = uLINK[mom].v + cross(uLINK[mom].w, prod(uLINK[mom].R,uLINK[mom].b));
        uLINK[j].w = uLINK[mom].w + prod(uLINK[j].R,(uLINK[j].a * uLINK[j].dq));
    }
//    std:://///////////////cout<<"uLINK["<<j<<"].v:"<<std::endl<<uLINK[j].v<<std::endl;

//	std:://///////////////cout<<"uLINK["<<j<<"].w:"<<std::endl<<uLINK[j].w<<std::endl<<std::endl;

    ForwardVelocity(uLINK[j].sister);
    ForwardVelocity(uLINK[j].child);
}

boost::numeric::ublas::vector<float> NewWalk::calcMC(int j)
{
    boost::numeric::ublas::vector<float> mc(3);
    boost::numeric::ublas::vector<float> test(3);
    if (j==0)
    {
        mc(0)=0;mc(1)=0;mc(2)=0;
    }
    else
    {
///this part is qiute special
/*
        if(j==7||j==13)
        {
            boost::numeric::ublas::vector<float> qq(3);
            qq(0)=0;qq(1)=0;qq(2)=-0.035;
            mc = uLINK[j].m * (uLINK[j].p + qq);
        }
*/
///        else
///        {
            mc = uLINK[j].m * (uLINK[j].p + prod(uLINK[j].R,uLINK[j].c));
 ///       }

 //       std:://///////////////cout<<"uLINK["<<j<<"].m:"<<uLINK[j].m<<std::endl;
 //       std:://///////////////cout<<"uLINK["<<j<<"].p:"<<uLINK[j].p<<std::endl;
        //test=prod(uLINK[j].R,uLINK[j].c);
 //       std:://///////////////cout<<"test:"<<test<<std::endl;
        mc = mc + calcMC(uLINK[j].sister) + calcMC(uLINK[j].child);
    }
 //   std:://///////////////cout<<"j:"<<j<<" mc: "<<mc<<std::endl;
    return mc;
}


boost::numeric::ublas::vector<float> NewWalk::calcCoM()
{
    float M=TotalMass(1);
    boost::numeric::ublas::vector<float> MC=calcMC(1);
    boost::numeric::ublas::vector<float> com=MC/M;
    return com;
}


 boost::numeric::ublas::vector<float> NewWalk::calcP(int j)
{
     boost::numeric::ublas::vector<float> p(3),c1;
    if(j==0)
    {
        p(0)=0;p(1)=0;p(2)=0;
    }
    else
    {
        c1=prod(uLINK[j].R,uLINK[j].c);
        p=uLINK[j].m*(uLINK[j].v+cross(c1,uLINK[j].w));
        p=p+calcP(uLINK[j].sister)+calcP(uLINK[j].child);
    }
    return p;
}

 boost::numeric::ublas::matrix<float> NewWalk::change(matrix<float> a)
{
    boost::numeric::ublas::matrix<float> b(3,3);
    b(0,0)=a(0,0);b(0,1)=a(1,0);b(0,2)=a(2,0);
    b(1,0)=a(0,1);b(1,1)=a(1,1);b(1,2)=a(2,1);
    b(2,0)=a(0,2);b(2,1)=a(1,2);b(2,2)=a(2,2);
    return b;
}
 boost::numeric::ublas::matrix<float> NewWalk::change1(matrix<float> a)
  {
 	 boost::numeric::ublas::matrix<float> b(1,3);
 	 b(0,0)=a(0,0);b(0,1)=a(1,0);b(0,2)=a(2,0);
 	 return b;

  }

  float NewWalk::MULTIP(matrix<float> a,matrix<float> b,int n)
  {
 	 float sum=0.0;
 	 for(int i=0;i<n;i++)
 		 sum=sum+a(0,i)*b(i,0);
 	return sum;

  }
  float NewWalk::MULTIP2(float a[],float b[],int n)
   {
  	 float sum=0.0;
  	 for(int i=0;i<n;i++)
  		 sum=sum+a[i]*b[i];
  	return sum;

   }
  boost::numeric::ublas::matrix<float> NewWalk::MULTIP1(matrix<float> a,matrix<float> b)
   {
 	 boost::numeric::ublas::matrix<float> c(3,1);
 	 c(0,0)=a(0,0)*b(0,0)+a(0,1)*b(1,0)+a(0,2)*b(2,0);
 	 c(1,0)=a(1,0)*b(0,0)+a(1,1)*b(1,0)+a(1,2)*b(2,0);
 	 c(2,0)=a(2,0)*b(0,0)+a(2,1)*b(1,0)+a(2,2)*b(2,0);
  	return c;

   }
  boost::numeric::ublas::matrix<float> NewWalk::Add(matrix<float> a,matrix<float> b,float u)
  {
 	 boost::numeric::ublas::matrix<float> c(3,1);
 	 c(0,0)=a(0,0)+b(0,0)*u;
 	 c(1,0)=a(1,0)+b(1,0)*u;
 	 c(2,0)=a(2,0)+b(2,0)*u;
 	 return c;

  }

 boost::numeric::ublas::vector<float> NewWalk::calcL(int j)
{
     boost::numeric::ublas::vector<float> L(3),c,c1,p;
    if(j==0)
    {
        L(0)=0;L(1)=0;L(2)=0;
    }
    else
    {
        c1=prod(uLINK[j].R,uLINK[j].c);
        c=uLINK[j].p+c1;
        p=uLINK[j].m*(uLINK[j].v+cross(c1,uLINK[j].w));
        L=cross(c,p)+prod(uLINK[j].I,uLINK[j].w);
        L=L+calcL(uLINK[j].sister)+calcL(uLINK[j].child);
    }
    return L;
}


std::pair<float,float> NewWalk::calcZMP( boost::numeric::ublas::vector<float> com, boost::numeric::ublas::vector<float> dP, boost::numeric::ublas::vector<float> dL,float zmpz)
{
    float M = TotalMass(1);
    float px = (M*G*com(0) + zmpz * dP(0) - dL(1))/(M*G + dP(2));
    float py = (M*G*com(1) + zmpz * dP(1) + dL(0))/(M*G + dP(2));
    return std::pair<float,float> (px,py);
}

std::pair<std::vector<float>,std::vector<float> > NewWalk::getZMP()
{
    std::pair<std::vector<float>,std::vector<float> > zmp=zmp_m;
    return zmp;
}
std::pair<float,float> NewWalk::LIPMmy4(float x,float v,float a,float t,float Zc,float c1)
{
	//Vector3 m;
	//m=destination;
	//k1=k1+1;
	//if(k==0)
	//{
	int N=400;
	//x=x+footLength*0.5;
	//float R=0.00000001;
	 boost::numeric::ublas::matrix<float> A(3,3),b(3,1),c(1,3);

	 A(0,0)=1;A(0,1)=t;A(0,2)=t*t/2;
	 A(1,0)=0;A(1,1)=1;A(1,2)=t;
	 A(2,0)=0;A(2,1)=0;A(2,2)=1;

	 b(0,0)=t*t*t/6;b(1,0)=t*t/2;b(2,0)=t;

	 c(0,0)=1;c(0,1)=0;c(0,2)=-Zc/G;
	// c1(0,0)=1;c1(1,0)=0;c1(2,0)=-Zc/G;
	 boost::numeric::ublas::matrix<float> x0(3,1),K(1,3),x1(3,1);
	// boost::numeric::ublas::matrix<float>  f(1,N);
	// boost::numeric::ublas::vector<float> f(N),p(N);
	 float p[N];
	 x0(0,0)=x; x0(1,0)=v; x0(2,0)=a;
	 K(0,0)=5533.8; K(0,1)=1739.9; K(0,2)=143.0803;
	// if(footLength<=0.006 &&  footLength>0)
	// {
		 //c1=c1+0.1;
		 //footLength=0.1;
	 //}
	for(int i=0;i<N;i++)
	{

		//p[i]=c1;
	//	if(MyDistenceToBall<0.03)
//if( wm.GetMyDistanceToBall() > 0.172)
	p[i]=c1+i*footLength;
		//p[i]=c1+i*0.1;
//else
	//p[i]=c1;
	//	if(fabs(p[i])>15 )//|| wm.GetMyDistanceToBall() <= 0.172)
		//	p[i]=p[i-1];

	}
	//f=float((-3608.41183944006,-944.227093404316,-80.9743263741604,193.880247998248,276.649314931906,296.861394724871,296.846012057518,290.431661291072,282.131412116009,273.413777377672,264.752358772619,256.295773143713,248.086613401278,240.133010215597,232.432016015979,224.977242158232,217.761349382630,210.776856239171,204.016397914634,197.472805595397,191.139127339900,185.008629996037,179.074795080491,173.331312836914,167.772075846372,162.391172634224,157.182881414032,152.141664010008,147.262159967281,142.539180848859,137.967704714893,133.542870778907,129.259974235503,125.114461254064,121.101924133163,117.218096610527,113.458849323538,109.820185415474,106.298236282779,102.889257458854,99.5896246299797,96.3958297791253,93.3044774535443,90.3122811521769,87.4160598290164,84.6127345087143,81.8993250108222,79.2729467791823,76.7308078130895,74.2702056969594,71.8885247253393,69.5832331202008,67.3518803375511,65.1920944604972,63.1015796759853,61.0781138325312,59.1195460763399,57.2237945632993,55.3888442444109,53.6127447223013,51.8936081765316,50.2296073554967,48.6189736327761,47.0599951258687,45.5510148753071,44.0904290822143,42.6766854024264,41.3082812953657,39.9837624259065,38.7017211175316,37.4607948551352,36.2596648358761,35.0970545665409,33.9717285059221,32.8824907507683,31.8281837639063,30.8076871431822,29.8199164299103,28.8638219555635,27.9383877254755,27.0426303383679,26.1755979405530,25.3363692136972,24.5240523950700,23.7377843292345,22.9767295501704,22.2400793928533,21.5270511333442,20.8368871564741,20.1688541502389,19.5222423260458,18.8963646639829,18.2905561823076,17.7041732303778,17.1365928042722,16.5872118843723,16.0554467942008,15.5407325798346,15.0425224092315,14.5602869908322,14.0935140108179,13.6417075884261,13.2043877487437,12.7810899124178,12.3713644017398,11.9747759625785,11.5909033016532,11.2193386386543,10.8596872727350,10.5115671629127,10.1746085219343,9.84845342317274,9.53275542013666,9.22717917818856,8.93140011807964,8.64510407092191,8.36798694423094,8.09975439868335,7.84012153524588,7.58881259234270,7.34556065273912,7.11010735982958,6.88220264302861,6.66160445197216,6.44807849924686,6.24139801137347,6.04134348777963,5.84770246750559,5.66026930339474,5.47884494352868,5.30323671967461,5.13325814251965,4.96872870347476,4.80947368283692,4.65532396410613,4.50611585425923,4.36169090978971,4.22189576832835,4.08658198566569,3.95560587800296,3.82882836926375,3.70611484330389,3.58733500086268,3.47236272110297,3.36107592759311,3.25335645858817,3.14908994147246,3.04816567122988,2.95047649281278,2.85591868728441,2.76439186161365,2.67579884200511,2.59004557065094,2.50704100579463,2.42669702500067,2.34892833152700,2.27365236370087,2.20078920720168,2.13026151015750,2.06199440096509,1.99591540874599,1.93195438635404,1.87004343585267,1.81011683638244,1.75211097434247,1.69596427581121,1.64161714113497,1.58901188161446,1.53809265822223,1.48880542228563,1.44109785807243,1.39491932721803,1.35022081493499,1.30695487794800,1.26507559409873,1.22453851356700,1.18530061165656,1.14732024309511,1.11055709780013,1.07497215806338,1.04052765710870,1.00718703897883,0.974914919708958,0.943677049745334,0.913440277569312,0.884172514487986,0.855842700554089,0.828420771578853,0.801877627202842,0.776185099990765,0.751315925517465,0.727243713413265,0.703942919337903,0.681388817853270,0.659557476166140,0.638425728712941,0.617971152559615,0.598172043590368,0.579007393460054,0.560456867285656,0.542500782053199,0.525120085717101,0.508296336969803,0.492011685660143,0.476248853839670,0.460991117416774,0.446222288399131,0.431926697705576,0.418089178529161,0.404695050233721,0.391730102766817,0.379180581572509,0.367033172987933,0.355274990108140,0.343893559104217,0.332876805980116,0.322213043754144,0.311890960051480,0.301899605094548,0.292228380078480,0.282867025919322,0.273805612363023,0.265034527443639,0.256544467279568,0.248326426196936,0.240371687169689,0.232671812566203,0.225218635192594,0.218004249623210,0.211021003809086,0.204261490955485,0.197718541659832,0.191385216301752,0.185254797677097,0.179320783868138,0.173576881342356,0.168016998272500,0.162635238070813,0.157425893130563,0.152383438768227,0.147502527359893,0.142777982665660,0.138204794335992,0.133778112594215,0.129493243089483,0.125345641914761,0.121330910784535,0.117444792367120,0.113683165766614,0.110042042149692,0.106517560512610,0.103105983583908,0.0998036938584673,0.0966071897587154,0.0935130819188875,0.0905180895884172,0.0876190371506199,0.0848128507529840,0.0820965550454828,0.0794672700234511,0.0769222079716683,0.0744586705064039,0.0720740457122895,0.0697658053709672,0.0675315022785829,0.0653687676492659,0.0632753086018464,0.0612489057271354,0.0592874107331887,0.0573887441660512,0.0555508932035650,0.0537719095198960,0.0520499072185119,0.0503830608314195,0.0487696033825344,0.0472078245131269,0.0456960686673574,0.0442327333359688,0.0428162673562783,0.0414451692666586,0.0401179857137632,0.0388333099108049,0.0375897801452524,0.0363860783343567,0.0352209286269785,0.0340930960502291,0.0330013851994892,0.0319446389704160,0.0309217373315900,0.0299315961365014,0.0289731659736143,0.0280454310532856,0.0271474081303613,0.0262781454613025,0.0254367217947379,0.0246222453943672,0.0238338530931826,0.0230707093780006,0.0223320055033358,0.0216169586336735,0.0209248110132324,0.0202548291623353,0.0196063030995358,0.0189785455886742,0.0183708914100646,0.0177826966550386,0.0172133380430989,0.0166622122609546,0.0161287353227412,0.0156123419507418,0.0151124849759567,0.0146286347578810,0.0141602786228781,0.0137069203205502,0.0132680794975318,0.0128432911881445,0.0124321053213756,0.0120340862436554,0.0116488122569277,0.0112758751715233,0.0109148798733612,0.0105654439050195,0.0102271970602306,0.00989978099137083,0.00958284882952797,0.00927606481674290,0.00897910395003680,0.00869165163684403,0.00841340336148735,0.00814406436233924,0.00788334931932919,0.00763098205146378,0.00738669522403887,0.00715023006523396,0.00692133609178748,0.00669977084346216,0.00648529962601824,0.00627769526242318,0.00607673785203251,0.00588221453748679,0.00569391927907820,0.00551165263634569,0.00533522155666921,0.00516443917063653,0.00499912459396745,0.00483910273578377,0.00468420411302286,0.00453426467079708,0.00438912560850917,0.00424863321153856,0.00411263868832047,0.00398099801264501,0.00385357177100866,0.00373022501485644,0.00361082711755831,0.00349525163596767,0.00338337617641504,0.00327508226499544,0.00317025522201148,0.00306878404043856,0.00297056126828421,0.00287548289471617,0.00278344823983851,0.00269435984799905,0.00260812338451496,0.00252464753570667,0.00244384391213460,0.00236562695493567,0.00228991384516034,0.00221662441601425,0.00214568106791122,0.00207700868624740,0.00201053456180986,0.00194618831373448,0.00188390181493216,0.00182360911990397,0.00176524639486847,0.00170875185012753,0.00165406567459875,0.00160112997244492,0.00154988870173363,0.00150028761506164,0.00145227420208140,0.00140579763386855,0.00136080870907149,0.00131725980178589,0.00127510481109898,0.00123429911224994,0.00119479950935487,0.00115656418964591,0.00111955267917626,0.00108372579994398,0.00104904562838918,0.00101547545522062,0.000982979746529062,0.000951524106146164,0.000921075239209130,0.000891600916892251,0.000863069942268224,0.000835452117262917));
	float f[]={-3608.411839,-944.227093,-80.974326,193.880247,276.649314,296.861394,296.846012,290.431661,282.131412,273.413777,264.752358,256.295773,248.086613,240.133010,232.432016,224.977242,217.76134,210.776856,204.016397,197.472805,191.139127,185.008629,179.074795,173.331312,167.772075,162.391172,157.182881,152.141664,147.262159,142.539180,137.967704,133.542870,129.259974,125.114461,121.101924,117.218096,113.45884,109.820185,106.298236,102.889257,99.589624,96.395829,93.304477,90.312281,87.416059,84.612734,81.899325,79.272946,76.730807,74.270205,71.888524,69.583233,67.351880,65.192094,63.101579,61.078113,59.119546,57.223794,55.388844,53.612744,51.893608,50.229607,48.618973,47.059995,45.55101,44.0904,42.6766,41.308,39.98376,38.70172,37.46079,36.25966,35.09705,33.9717,32.88249,31.82818,30.80768,29.81991,28.863821,27.9383,27.042630,26.17559,25.33636,24.524052,23.737784,22.976729,22.240079,21.52705,20.83688,20.16885,19.52,18.896,18.290,17.7041,17.1365,16.587,16.0554,15.5407,15.04252,14.5602,14.0935,13.64170,13.20438,12.78108,12.371364,11.9747,11.590,11.21933,10.8596,10.51156,10.17460,9.8484,9.5327,9.22717,8.931400,8.64510,8.3679,8.09975,7.840,7.58881,7.34556,7.11010,6.88220,6.6616,6.4480,6.2413,6.0413,5.84770,5.66026,5.4788,5.30323,5.1332,4.968,4.8094,4.65532,4.5061,4.36169,4.22189,4.08658,3.9556,3.82882,3.7061,3.58733,3.4723,3.36107,3.25335,3.14908,3.0481,2.95047,2.8559,2.7643,2.6757,2.5900,2.5070,2.42669,2.3489,2.2736,2.200,2.130261,2.0619,1.995,1.931954,1.8700,1.81011,1.752110,1.69596,1.6416,1.58901,1.53809,1.48880,1.4410,1.3949,1.350220,1.30695,1.2650,1.224,1.18530,1.14732,1.110557,1.07497,1.04052,1.0071,0.9749,0.943677,0.913440,0.88417,0.85584,0.8284,0.801877,0.77618,0.75131,0.72724,0.703942,0.6813,0.65955,0.6384,0.61797,0.59817,0.57900,0.56045,0.54250,0.5251,0.50829,0.49201,0.47624,0.46099,0.44622,0.43192,0.41808,0.40469,0.3917,0.3791,0.36703,0.355274,0.3438,0.3328,0.3222,0.31189,0.30189,0.2922,0.28286,0.2738,0.2650,0.2565,0.2483,0.2403,0.2326,0.2252,0.2180,0.21102,0.20426,0.19771,0.19138,0.18525,0.17932,0.17357,0.16801,0.16263,0.15742,0.15238,0.14750,0.14277,0.1382,0.13377,0.1294,0.125,0.121,0.1174,0.1136,0.11004,0.1065,0.1031,0.099,0.0966,0.0935,0.09051,0.08761,0.0848,0.0820,0.07946,0.07692,0.0744,0.0720,0.06976,0.06753,0.0653,0.063,0.06124,0.05928,0.05738,0.05555,0.05377,0.05204,0.05038,0.04876,0.04720,0.0456,0.0442,0.0428,0.04144,0.04011,0.0388,0.03758,0.03638,0.035,0.03409,0.03300,0.0319,0.03092,0.029,0.028,0.028045,0.027147,0.026278,0.025436,0.0246,0.02383,0.0230,0.02233,0.02161,0.02092,0.02025,0.0196,0.01897,0.01837,0.01778,0.01721,0.016662,0.0161,0.01561,0.015,0.014628,0.01416,0.0137,0.01326,0.0128,0.01243,0.01203,0.01164,0.01127,0.01091,0.010565,0.01022,0.00989,0.00958,0.00927,0.00897,0.00869,0.00841,0.00814,0.00788,0.00763,0.0073,0.0071,0.00692,0.00669,0.00648,0.00627,0.0060,0.00588,0.00569,0.00551,0.00533,0.00516,0.00499,0.00483,0.00468,0.00453,0.004389,0.00424,0.0041,0.0039,0.00385,0.00373,0.0036,0.00349,0.0033,0.0032,0.00317,0.0030,0.00297,0.00287,0.0027,0.00269,0.00260,0.00252,0.00244,0.0023,0.0022,0.00221,0.00214,0.00207,0.0020,0.00194,0.00188,0.00182,0.0017,0.00170,0.0016,0.00160,0.00154,0.00150,0.00145,0.0014,0.00136,0.001317,0.001275,0.001234,0.001194,0.001156,0.001119,0.001083,0.001049,0.001015,0.000982,0.000951,0.000921,0.000891,0.000863,0.000835};
	//float f[]={-360.411839,-944.227093,-80.974326,193.880247,276.000314,296.861394,296.846012,290.431661,282.131412,273.413777,264.752358,256.295773,248.086613,240.133010,232.432016,224.977242,217.76134,210.776856,204.016397,197.472805,191.139127,185.008629,179.074795,173.331312,167.772075,162.391172,157.182881,152.141664,147.262159,142.539180,137.967704,133.542870,129.259974,125.114461,121.101924,117.218096,113.45884,109.820185,106.298236,102.889257,99.589624,96.395829,93.304477,90.312281,87.416059,84.612734,81.899325,79.272946,76.730807,74.270205,71.888524,69.583233,67.351880,65.192094,63.101579,61.078113,59.119546,57.223794,55.388844,53.612744,51.893608,50.229607,48.618973,47.059995,45.55101,44.0904,42.6766,41.308,39.98376,38.70172,37.46079,36.25966,35.09705,33.9717,32.88249,31.82818,30.80768,29.81991,28.863821,27.9383,27.042630,26.17559,25.33636,24.524052,23.737784,22.976729,22.240079,21.52705,20.83688,20.16885,19.52,18.896,18.290,17.7041,17.1365,16.587,16.0554,15.5407,15.04252,14.5602,14.0935,13.64170,13.20438,12.78108,12.371364,11.9747,11.590,11.21933,10.8596,10.51156,10.17460,9.8484,9.5327,9.22717,8.931400,8.64510,8.3679,8.09975,7.840,7.58881,7.34556,7.11010,6.88220,6.6616,6.4480,6.2413,6.0413,5.84770,5.66026,5.4788,5.30323,5.1332,4.968,4.8094,4.65532,4.5061,4.36169,4.22189,4.08658,3.9556,3.82882,3.7061,3.58733,3.4723,3.36107,3.25335,3.14908,3.0481,2.95047,2.8559,2.7643,2.6757,2.5900,2.5070,2.42669,2.3489,2.2736,2.200,2.130261,2.0619,1.995,1.931954,1.8700,1.81011,1.752110,1.69596,1.6416,1.58901,1.53809,1.48880,1.4410,1.3949,1.350220,1.30695,1.2650,1.224,1.18530,1.14732,1.110557,1.07497,1.04052,1.0071,0.9749,0.943677,0.913440,0.88417,0.85584,0.8284,0.801877,0.77618,0.75131,0.72724,0.703942,0.6813,0.65955,0.6384,0.61797,0.59817,0.57900,0.56045,0.54250,0.5251,0.50829,0.49201,0.47624,0.46099,0.44622,0.43192,0.41808,0.40469,0.3917,0.3791,0.36703,0.355274,0.3438,0.3328,0.3222,0.31189,0.30189,0.2922,0.28286,0.2738,0.2650,0.2565,0.2483,0.2403,0.2326,0.2252,0.2180,0.21102,0.20426,0.19771,0.19138,0.18525,0.17932,0.17357,0.16801,0.16263,0.15742,0.15238,0.14750,0.14277,0.1382,0.13377,0.1294,0.125,0.121,0.1174,0.1136,0.11004,0.1065,0.1031,0.099,0.0966,0.0935,0.09051,0.08761,0.0848,0.0820,0.07946,0.07692,0.0744,0.0720,0.06976,0.06753,0.0653,0.063,0.06124,0.05928,0.05738,0.05555,0.05377,0.05204,0.05038,0.04876,0.04720,0.0456,0.0442,0.0428,0.04144,0.04011,0.0388,0.03758,0.03638,0.035,0.03409,0.03300,0.0319,0.03092,0.029,0.028,0.028045,0.027147,0.026278,0.025436,0.0246,0.02383,0.0230,0.02233,0.02161,0.02092,0.02025,0.0196,0.01897,0.01837,0.01778,0.01721,0.016662,0.0161,0.01561,0.015,0.014628,0.01416,0.0137,0.01326,0.0128,0.01243,0.01203,0.01164,0.01127,0.01091,0.010565,0.01022,0.00989,0.00958,0.00927,0.00897,0.00869,0.00841,0.00814,0.00788,0.00763,0.0073,0.0071,0.00692,0.00669,0.00648,0.00627,0.0060,0.00588,0.00569,0.00551,0.00533,0.00516,0.00499,0.00483,0.00468,0.00453,0.004389,0.00424,0.0041,0.0039,0.00385,0.00373,0.0036,0.00349,0.0033,0.0032,0.00317,0.0030,0.00297,0.00287,0.0027,0.00269,0.00260,0.00252,0.00244,0.0023,0.0022,0.00221,0.00214,0.00207,0.0020,0.00194,0.00188,0.00182,0.0017,0.00170,0.0016,0.00160,0.00154,0.00150,0.00145,0.0014,0.00136,0.001317,0.001275,0.001234,0.001194,0.001156,0.001119,0.001083,0.001049,0.001015,0.000982,0.000951,0.000921,0.000891,0.000863,0.000835};

	float u;

	u=MULTIP2(f,p,N)-MULTIP(K,x0,3);//+footLength*0.16

	x1=Add(MULTIP1(A,x0),b,u);

	//if(k1<100)

	// if(fabs(footLength)>=0 && fabs(footLength<=0.06))
		// px=x1(0,0)+footLength*0.53175;//0.5388
	//else
		//px=x1(0,0)+footLength*0.54;
	//if(footLength>0)
		// px=x1(0,0)+0.0495;
		//px=x1(0,0)+footLength*0.53195;
//else if(footLength>=0.08)
	//px=x1(0,0)+(50-k1)*0.01;
	//	px=x1(0,0)+0.0514;
	// px=x1(0,0)+footLength*0.5437;
	//else
		//
	//else
//px=x1(0,0)+footLength*0.5;
	//px=x1(0,0)-0.0276;
//	cx0=x1(0,0);
	vxx=x1(1,0);
	ax=x1(2,0);
//	if( wm.GetMyDistanceToBall() > 0.172)
		float px=x1(0,0)+footLength*0.048;//0.0475//0.048//0.049//0.05//上线0.06开始倒
//	else
		//float px=x1(0,0)+0.055;
	//	float px=x1(0,0)+footLength*0.535;//0.53175;0.65//0.53275//0.535
	cx0=px;
	//float px=MULTIP(c,x0,3);
	float vx=x1(1,0);
	//}
 return std::pair<float,float> (px,vx);
}

std::pair<float,float> NewWalk::LIPMmy3(float t,float org,float x0,float Tc,float c1,float Ts)
{
	float C1,C2;
	 float e1=exp(-Ts/Tc);
	 float e2=exp(Ts/Tc);
	 float e3=exp(-t/Tc);
	 float e4=exp(t/Tc);

		    C1=((x0-org)*e1-(c1-org))/(e1-e2);
		    C2=((x0-org)*e2-(c1-org))/(e2-e1);
		   // %Pxt=b1*t+b0+Pxn(n)
		float    px=C1*e4+C2*e3+org;
		float    vx=C1*e4/Tc-C2*e3/Tc;
		        //88888888     cout<<"...."<<px<<",,,,,"<<vx<<endl;

		  //888888888 cout<<"NewWalk::LIPMmy5"<<endl;

		   return std::pair<float,float> (px,vx);



}



std::pair<float,float> NewWalk::LIPMmy(float t,float org,float x0,float Tc,float dx0)
{
    float px = (x0-org) * cosh(t/Tc) +Tc * dx0 * sinh(t/Tc) + org;
    float vx = (x0-org)/Tc * sinh(t/Tc)+dx0 * cosh(t/Tc) ;
    return std::pair<float,float> (px,vx);
}

std::pair<float,float> NewWalk::LIPMmy2(float t,float org,float x0,float Tc,float dx0,float b,float T)
{
	 float px =(x0-org+b) * cosh(t/Tc) +Tc * (dx0 -2*b/T)* sinh(t/Tc) +2*b*t/T-b+ org;
	 float vx =(x0-org+b)/Tc * sinh(t/Tc)+(dx0 -2*b/T)* cosh(t/Tc) +2*b/T ;
	return std::pair<float,float> (px,vx);
}

NewWalk::NewWalk()
{
      UseNewWalk=true;   //use new walk when the game begin
      initFirst=false;
      standHigh=0.175;
      minUpStepHigh=0.155;
      maxDownStepHigh=0.180;
      InitNewWalkData();
      InitHalfStepWalkData();
      
#ifdef FOOT_8
	#ifndef SIX

		FOOTX[0]=0.01;
		FOOTX[1]=0.02;
		FOOTX[2]=MAX_FOOT_HIGH;
		FOOTX[3]=MAX_FOOT_HIGH;
		FOOTX[4]=MAX_FOOT_HIGH;
		FOOTX[5]=0.02;
		FOOTX[6]=0.01;
		FOOTX[7]=0.0;

		time[0] = 0;
	        time[1] = 0.0229;	
	        time[2] = 0.0457;
	        time[3] = 0.0686;
	        time[4] = 0.0914;
	        time[5] = 0.1143;
	        time[6] = 0.1371;
	        time[7] = 0.16;


	/*       if(footLength==0 && footWidth==0)
	       {
	        FOOTX[0]=0.01;
	        		FOOTX[1]=0.02;
	        		FOOTX[2]=0.02;
	        		FOOTX[3]=0.02;
	        		FOOTX[4]=0.02;
	        		FOOTX[5]=0.02;
	        		FOOTX[6]=0.02;
	        		FOOTX[7]=0.1;
	       }

*/
	   /*     if(footLength>0 && footLength<=0.08)
	       	      {


	       	  		FOOTX[0]=0.01;
	       	  		FOOTX[1]=0.02;
	       	  	FOOTX[2]=MAX_FOOT_HIGH1;
	       	  		FOOTX[3]=MAX_FOOT_HIGH1;
	       	  		FOOTX[4]=MAX_FOOT_HIGH1;
	       	  		FOOTX[5]=0.02;
	       	  		FOOTX[6]=0.01;
	       	  		FOOTX[7]=0.0;


	       	      }*/

	
	#else
		FOOTX[0]=FOOTXA;
		FOOTX[1]=FOOTXB;
		FOOTX[2]=FOOTXC;
		FOOTX[3]=FOOTXD;
		FOOTX[4]=FOOTXE;
		FOOTX[5]=FOOTXF;

		time[0] = 0;	
	        time[1] = 0.0229;
	        time[2] = 0.0457;
	        time[3] = 0.0686;
	        time[4] = 0.0914;
	        time[5] = 0.1143;
	#endif
#else
      FOOTX[0]=0.002;
      FOOTX[1]=0.015;
      FOOTX[2]=0.02;
      FOOTX[3]=0.02;
      FOOTX[4]=0.02;
      FOOTX[5]=0.02;

      FOOTX[6]=0.02;
      FOOTX[7]=0.015;
      FOOTX[8]=0.008;
      FOOTX[9]=0.0;

      time[0] = 0;
      time[1] = 0.0222;
      time[2] = 0.0444;
      time[3] = 0.0667;
      time[4] = 0.0889;
      time[5] = 0.1111;
      time[6] = 0.1333;
      time[7] = 0.1556;
      time[8] = 0.1778;
      time[9] = 0.2;
#endif
}


void NewWalk::InitHalfStepWalkData()
{
	turnHeadAngle=0;
	swingLeftAngle=0;
	swingRightAngle=0;
	swingLeftAngle2=0;
	swingRightAngle2=0;
	
	bodyForerakeAngle=0;
	legForerakeAngle=0;
	
	turnLeftAngle=0;
	turnRightAngle=0;
	rightCoxaAngle=0;
	leftCoxaAngle=0;
	rightAnkleAngle=0;
	leftAnkleAngle=0;
	
	stepIncrement=0;
	Ldistance=-0.03;
	Rdistance=-0.03;
	lastCyclesAverageTurnHeadAngle=0;
	
	leftStep=true;
	rightStep=false;
	
	walkCounter=0;
	
	i_SendedCount=0;
	i_ReceivedCount=0;
	firstReadDate=true;
	
}


#ifdef fengData
void NewWalk::InitNewWalkData()
{
  	for(int i=0;i<14;i++)
	{
	    uLINK[i].num=i;
	    uLINK[i].b.resize(3);
	    uLINK[i].a.resize(3);
	    uLINK[i].c.resize(3);
	    uLINK[i].p.resize(3);
	    uLINK[i].v.resize(3);
	    uLINK[i].w.resize(3);

	    uLINK[i].R.resize(3,3);
		uLINK[i].I.resize(3,3);

	}

    Rfoot.b.resize(3);
    Rfoot.a.resize(3);
    Rfoot.c.resize(3);
    Rfoot.p.resize(3);
    Rfoot.v.resize(3);
    Rfoot.w.resize(3);
    Rfoot.R.resize(3,3);


    Lfoot.b.resize(3);
    Lfoot.a.resize(3);
    Lfoot.c.resize(3);
    Lfoot.p.resize(3);
    Lfoot.v.resize(3);
    Lfoot.w.resize(3);
    Lfoot.R.resize(3,3);



	uLINK[0].name="null";
	uLINK[0].m=0.0;
	uLINK[0].mother=0;
	uLINK[0].sister=0;
	uLINK[0].child=0;
	uLINK[0].b(0)=0;uLINK[0].b(1)=0;uLINK[0].b(2)=0;
	uLINK[0].a(0)=0;uLINK[0].a(1)=0;uLINK[0].a(2)=0;
	uLINK[0].c(0)=0;uLINK[0].c(1)=0;uLINK[0].c(2)=0;
	uLINK[0].p(0)=0;uLINK[0].p(1)=0;uLINK[0].p(2)=0;
	uLINK[0].v(0)=0;uLINK[0].v(1)=0;uLINK[0].v(2)=0;
	uLINK[0].w(0)=0;uLINK[0].w(1)=0;uLINK[0].w(2)=0;

	uLINK[0].R(0,0)=0;uLINK[0].R(0,1)=0;uLINK[0].R(0,2)=0;
	uLINK[0].R(1,0)=0;uLINK[0].R(1,1)=0;uLINK[0].R(1,2)=0;
	uLINK[0].R(2,0)=0;uLINK[0].R(2,1)=0;uLINK[0].R(2,2)=0;

	uLINK[0].q=0.0;
	uLINK[0].dq=0.0;
	uLINK[0].ddq=0.0;


	uLINK[1].name="BODY";
	uLINK[1].m=2.5721;
	uLINK[1].mother=0;
	uLINK[1].sister=0;
	uLINK[1].child=2;
	uLINK[1].b(0)=0;uLINK[1].b(1)=0;uLINK[1].b(2)=0.149;
	uLINK[1].a(0)=0;uLINK[1].a(1)=0;uLINK[1].a(2)=1;

	uLINK[1].c(0)=0;uLINK[1].c(1)=0;uLINK[1].c(2)=0.11834;
	uLINK[1].p(0)=0;uLINK[1].p(1)=0;uLINK[1].p(2)=0;
	uLINK[1].v(0)=0;uLINK[1].v(1)=0;uLINK[1].v(2)=0;
	uLINK[1].w(0)=0;uLINK[1].w(1)=0;uLINK[1].w(2)=0;

	uLINK[1].R(0,0)=0;uLINK[1].R(0,1)=0;uLINK[1].R(0,2)=0;
	uLINK[1].R(1,0)=0;uLINK[1].R(1,1)=0;uLINK[1].R(1,2)=0;
	uLINK[1].R(2,0)=0;uLINK[1].R(2,1)=0;uLINK[1].R(2,2)=0;

	uLINK[1].q=0.0;
	uLINK[1].dq=0.0;
	uLINK[1].ddq=0.0;


	uLINK[2].name="RLEG_J0";
	uLINK[2].m=0;
	uLINK[2].mother=1;
	uLINK[2].sister=8;
	uLINK[2].child=3;

	uLINK[2].b(0)=0;uLINK[2].b(1)=-0.055;uLINK[2].b(2)=0;
	uLINK[2].a(0)=0;uLINK[2].a(1)=1;uLINK[2].a(2)=1;

	uLINK[2].c(0)=0;uLINK[2].c(1)=0;uLINK[2].c(2)=0;
	uLINK[2].p(0)=0;uLINK[2].p(1)=0;uLINK[2].p(2)=0;
	uLINK[2].v(0)=0;uLINK[2].v(1)=0;uLINK[2].v(2)=0;
	uLINK[2].w(0)=0;uLINK[2].w(1)=0;uLINK[2].w(2)=0;

	uLINK[2].R(0,0)=0;uLINK[2].R(0,1)=0;uLINK[2].R(0,2)=0;
	uLINK[2].R(1,0)=0;uLINK[2].R(1,1)=0;uLINK[2].R(1,2)=0;
	uLINK[2].R(2,0)=0;uLINK[2].R(2,1)=0;uLINK[2].R(2,2)=0;

	uLINK[2].q=0.0;
	uLINK[2].dq=0.0;
	uLINK[2].ddq=0.0;


	uLINK[3].name="RLEG_J1";//	{3,"RLEG_J1",	0.125,	2,0,4,		{0,0,0},		{1,0,0},	{0,0,0},		0.0,0.0,0.0},
	uLINK[3].m=0;
	uLINK[3].mother=2;
	uLINK[3].sister=0;
	uLINK[3].child=4;

	uLINK[3].b(0)=0;uLINK[3].b(1)=0;uLINK[3].b(2)=0;
	uLINK[3].a(0)=1;uLINK[3].a(1)=0;uLINK[3].a(2)=0;

	uLINK[3].c(0)=0;uLINK[3].c(1)=0;uLINK[3].c(2)=0;
	uLINK[3].p(0)=0;uLINK[3].p(1)=0;uLINK[3].p(2)=0;
	uLINK[3].v(0)=0;uLINK[3].v(1)=0;uLINK[3].v(2)=0;
	uLINK[3].w(0)=0;uLINK[3].w(1)=0;uLINK[3].w(2)=0;

	uLINK[3].R(0,0)=0;uLINK[3].R(0,1)=0;uLINK[3].R(0,2)=0;
	uLINK[3].R(1,0)=0;uLINK[3].R(1,1)=0;uLINK[3].R(1,2)=0;
	uLINK[3].R(2,0)=0;uLINK[3].R(2,1)=0;uLINK[3].R(2,2)=0;

	uLINK[3].q=0.0;
	uLINK[3].dq=0.0;
	uLINK[3].ddq=0.0;


	uLINK[4].name="RLEG_J2";//{4,"RLEG_J2",	0.275,	3,0,5,		{0,0,0},		{0,1,0},	{0,0,0},0.0,0.0,0.0},
	uLINK[4].m=0.49;
	uLINK[4].mother=3;
	uLINK[4].sister=0;
	uLINK[4].child=5;

	uLINK[4].b(0)=0;uLINK[4].b(1)=0;uLINK[4].b(2)=0;
	uLINK[4].a(0)=0;uLINK[4].a(1)=1;uLINK[4].a(2)=0;

	uLINK[4].c(0)=0;uLINK[4].c(1)=0;uLINK[4].c(2)=-0.05245;
	uLINK[4].p(0)=0;uLINK[4].p(1)=0;uLINK[4].p(2)=0;
	uLINK[4].v(0)=0;uLINK[4].v(1)=0;uLINK[4].v(2)=0;
	uLINK[4].w(0)=0;uLINK[4].w(1)=0;uLINK[4].w(2)=0;

	uLINK[4].R(0,0)=0;uLINK[4].R(0,1)=0;uLINK[4].R(0,2)=0;
	uLINK[4].R(1,0)=0;uLINK[4].R(1,1)=0;uLINK[4].R(1,2)=0;
	uLINK[4].R(2,0)=0;uLINK[4].R(2,1)=0;uLINK[4].R(2,2)=0;

	uLINK[4].q=0.0;
	uLINK[4].dq=0.0;
	uLINK[4].ddq=0.0;


	uLINK[5].name="RLEG_J3";//{5,"RLEG_J3",	0.225,	4,0,6,		{0,0,-0.14},	{0,1,0},	{0,0,0},0.0,0.0,0.0},
	uLINK[5].m=0.35;
	uLINK[5].mother=4;
	uLINK[5].sister=0;
	uLINK[5].child=6;

	uLINK[5].b(0)=0;uLINK[5].b(1)=0;uLINK[5].b(2)=-0.135;
	uLINK[5].a(0)=0;uLINK[5].a(1)=1;uLINK[5].a(2)=0;

	uLINK[5].c(0)=0;uLINK[5].c(1)=0;uLINK[5].c(2)=-0.07464;
	uLINK[5].p(0)=0;uLINK[5].p(1)=0;uLINK[5].p(2)=0;
	uLINK[5].v(0)=0;uLINK[5].v(1)=0;uLINK[5].v(2)=0;
	uLINK[5].w(0)=0;uLINK[5].w(1)=0;uLINK[5].w(2)=0;

	uLINK[5].R(0,0)=0;uLINK[5].R(0,1)=0;uLINK[5].R(0,2)=0;
	uLINK[5].R(1,0)=0;uLINK[5].R(1,1)=0;uLINK[5].R(1,2)=0;
	uLINK[5].R(2,0)=0;uLINK[5].R(2,1)=0;uLINK[5].R(2,2)=0;

	uLINK[5].q=0.0;
	uLINK[5].dq=0.0;
	uLINK[5].ddq=0.0;


	uLINK[6].name="RLEG_J4";//{6,"RLEG_J4",	0.125,	5,0,7,		{0,0,-0.11},	{0,1,0},	{0,0,0},0.0,0.0,0.0},
	uLINK[6].m=0;
	uLINK[6].mother=5;
	uLINK[6].sister=0;
	uLINK[6].child=7;

	uLINK[6].b(0)=0;uLINK[6].b(1)=0;uLINK[6].b(2)=-0.11;
	uLINK[6].a(0)=0;uLINK[6].a(1)=1;uLINK[6].a(2)=0;

	uLINK[6].c(0)=0;uLINK[6].c(1)=0;uLINK[6].c(2)=0;
	uLINK[6].p(0)=0;uLINK[6].p(1)=0;uLINK[6].p(2)=0;
	uLINK[6].v(0)=0;uLINK[6].v(1)=0;uLINK[6].v(2)=0;
	uLINK[6].w(0)=0;uLINK[6].w(1)=0;uLINK[6].w(2)=0;

	uLINK[6].R(0,0)=0;uLINK[6].R(0,1)=0;uLINK[6].R(0,2)=0;
	uLINK[6].R(1,0)=0;uLINK[6].R(1,1)=0;uLINK[6].R(1,2)=0;
	uLINK[6].R(2,0)=0;uLINK[6].R(2,1)=0;uLINK[6].R(2,2)=0;

	uLINK[6].q=0.0;
	uLINK[6].dq=0.0;
	uLINK[6].ddq=0.0;


	uLINK[7].name="RLEG_J5";//{7,"RLEG_J5",	0.2,	6,0,0,		{0,0,0},		{1,0,0},	{0,0,0},0.0,0.0,0.0},
	uLINK[7].m=0.2;
	uLINK[7].mother=6;
	uLINK[7].sister=0;
	uLINK[7].child=0;

	uLINK[7].b(0)=0;uLINK[7].b(1)=0;uLINK[7].b(2)=0;
	uLINK[7].a(0)=1;uLINK[7].a(1)=0;uLINK[7].a(2)=0;

	uLINK[7].c(0)=0;uLINK[7].c(1)=0;uLINK[7].c(2)=0;
	uLINK[7].p(0)=0;uLINK[7].p(1)=0;uLINK[7].p(2)=0;
	uLINK[7].v(0)=0;uLINK[7].v(1)=0;uLINK[7].v(2)=0;
	uLINK[7].w(0)=0;uLINK[7].w(1)=0;uLINK[7].w(2)=0;

	uLINK[7].R(0,0)=0;uLINK[7].R(0,1)=0;uLINK[7].R(0,2)=0;
	uLINK[7].R(1,0)=0;uLINK[7].R(1,1)=0;uLINK[7].R(1,2)=0;
	uLINK[7].R(2,0)=0;uLINK[7].R(2,1)=0;uLINK[7].R(2,2)=0;

	uLINK[7].q=0.0;
	uLINK[7].dq=0.0;
	uLINK[7].ddq=0.0;


	uLINK[8].name="LLEG_J0";//	{8,"LLEG_J0",	0.09,	1,0,9,		{0,0.1,0},		{0,0,1},	{0,0,0},0.0,0.0,0.0},
	uLINK[8].m=0;
	uLINK[8].mother=1;
	uLINK[8].sister=0;
	uLINK[8].child=9;

	uLINK[8].b(0)=0;uLINK[8].b(1)=0.055;uLINK[8].b(2)=0;
	uLINK[8].a(0)=0;uLINK[8].a(1)=-1;uLINK[8].a(2)=1;

	uLINK[8].c(0)=0;uLINK[8].c(1)=0;uLINK[8].c(2)=0;
	uLINK[8].p(0)=0;uLINK[8].p(1)=0;uLINK[8].p(2)=0;
	uLINK[8].v(0)=0;uLINK[8].v(1)=0;uLINK[8].v(2)=0;
	uLINK[8].w(0)=0;uLINK[8].w(1)=0;uLINK[8].w(2)=0;

	uLINK[8].R(0,0)=0;uLINK[8].R(0,1)=0;uLINK[8].R(0,2)=0;
	uLINK[8].R(1,0)=0;uLINK[8].R(1,1)=0;uLINK[8].R(1,2)=0;
	uLINK[8].R(2,0)=0;uLINK[8].R(2,1)=0;uLINK[8].R(2,2)=0;

	uLINK[8].q=0.0;
	uLINK[8].dq=0.0;
	uLINK[8].ddq=0.0;


	uLINK[9].name="LLEG_J1";//{9,"LLEG_J1",	0.[9][9]	8,0,10,		{0,0,0},		{1,0,0},	{0,0,0},0.0,0.0,0.0},
	uLINK[9].m=0;
	uLINK[9].mother=8;
	uLINK[9].sister=0;
	uLINK[9].child=10;

	uLINK[9].b(0)=0;uLINK[9].b(1)=0;uLINK[9].b(2)=0;
	uLINK[9].a(0)=1;uLINK[9].a(1)=0;uLINK[9].a(2)=0;

	uLINK[9].c(0)=0;uLINK[9].c(1)=0;uLINK[9].c(2)=0;
	uLINK[9].p(0)=0;uLINK[9].p(1)=0;uLINK[9].p(2)=0;
	uLINK[9].v(0)=0;uLINK[9].v(1)=0;uLINK[9].v(2)=0;
	uLINK[9].w(0)=0;uLINK[9].w(1)=0;uLINK[9].w(2)=0;

	uLINK[9].R(0,0)=0;uLINK[9].R(0,1)=0;uLINK[9].R(0,2)=0;
	uLINK[9].R(1,0)=0;uLINK[9].R(1,1)=0;uLINK[9].R(1,2)=0;
	uLINK[9].R(2,0)=0;uLINK[9].R(2,1)=0;uLINK[9].R(2,2)=0;


	uLINK[9].q=0.0;
	uLINK[9].dq=0.0;
	uLINK[9].ddq=0.0;


	uLINK[10].name="LLEG_J2";	//{10,"LLEG_J2",	0.275,	9,0,11,		{0,0,0},		{0,1,0},	{0,0,0},0.0,0.0,0.0},
	uLINK[10].m=0.49;
	uLINK[10].mother=9;
	uLINK[10].sister=0;
	uLINK[10].child=11;

	uLINK[10].b(0)=0;uLINK[10].b(1)=0;uLINK[10].b(2)=0;
	uLINK[10].a(0)=0;uLINK[10].a(1)=1;uLINK[10].a(2)=0;

	uLINK[10].c(0)=0;uLINK[10].c(1)=0;uLINK[10].c(2)=-0.05245;
	uLINK[10].p(0)=0;uLINK[10].p(1)=0;uLINK[10].p(2)=0;
	uLINK[10].v(0)=0;uLINK[10].v(1)=0;uLINK[10].v(2)=0;
	uLINK[10].w(0)=0;uLINK[10].w(1)=0;uLINK[10].w(2)=0;

	uLINK[10].R(0,0)=0;uLINK[10].R(0,1)=0;uLINK[10].R(0,2)=0;
	uLINK[10].R(1,0)=0;uLINK[10].R(1,1)=0;uLINK[10].R(1,2)=0;
	uLINK[10].R(2,0)=0;uLINK[10].R(2,1)=0;uLINK[10].R(2,2)=0;

	uLINK[10].q=0.0;
	uLINK[10].dq=0.0;
	uLINK[10].ddq=0.0;


	uLINK[11].name="LLEG_J3";//{11,"LLEG_J3",	0.225,	10,0,12,	{0,0,-0.14},	{0,1,0},	{0,0,0},0.0,0.0,0.0},
	uLINK[11].m=0.35;
	uLINK[11].mother=10;
	uLINK[11].sister=0;
	uLINK[11].child=12;

	uLINK[11].b(0)=0;uLINK[11].b(1)=0;uLINK[11].b(2)=-0.135;
	uLINK[11].a(0)=0;uLINK[11].a(1)=1;uLINK[11].a(2)=0;

	uLINK[11].c(0)=0;uLINK[11].c(1)=0;uLINK[11].c(2)=-0.07464;
	uLINK[11].p(0)=0;uLINK[11].p(1)=0;uLINK[11].p(2)=0;
	uLINK[11].v(0)=0;uLINK[11].v(1)=0;uLINK[11].v(2)=0;
	uLINK[11].w(0)=0;uLINK[11].w(1)=0;uLINK[11].w(2)=0;

	uLINK[11].R(0,0)=0;uLINK[11].R(0,1)=0;uLINK[11].R(0,2)=0;
	uLINK[11].R(1,0)=0;uLINK[11].R(1,1)=0;uLINK[11].R(1,2)=0;
	uLINK[11].R(2,0)=0;uLINK[11].R(2,1)=0;uLINK[11].R(2,2)=0;

	uLINK[11].q=0.0;
	uLINK[11].dq=0.0;
	uLINK[11].ddq=0.0;


	uLINK[12].name="LLEG_J4";//{12,"LLEG_J4",	0.125,	11,0,13,	{0,0,-0.11},	{0,1,0},	{0,0,0},0.0,0.0,0.0},
	uLINK[12].m=0;
	uLINK[12].mother=11;
	uLINK[12].sister=0;
	uLINK[12].child=13;

	uLINK[12].b(0)=0;uLINK[12].b(1)=0;uLINK[12].b(2)=-0.11;
	uLINK[12].a(0)=0;uLINK[12].a(1)=1;uLINK[12].a(2)=0;

	uLINK[12].c(0)=0;uLINK[12].c(1)=0;uLINK[12].c(2)=0;
	uLINK[12].p(0)=0;uLINK[12].p(1)=0;uLINK[12].p(2)=0;
	uLINK[12].v(0)=0;uLINK[12].v(1)=0;uLINK[12].v(2)=0;
	uLINK[12].w(0)=0;uLINK[12].w(1)=0;uLINK[12].w(2)=0;

	uLINK[12].R(0,0)=0;uLINK[12].R(0,1)=0;uLINK[12].R(0,2)=0;
	uLINK[12].R(1,0)=0;uLINK[12].R(1,1)=0;uLINK[12].R(1,2)=0;
	uLINK[12].R(2,0)=0;uLINK[12].R(2,1)=0;uLINK[12].R(2,2)=0;


	uLINK[12].q=0.0;
	uLINK[12].dq=0.0;
	uLINK[12].ddq=0.0;


	uLINK[13].name="LLEG_J5";//{13,"LLEG_J5",	0.2,	12,0,0,		{0,0,0},		{1,0,0},	{0,0,0},0.0,0.0,0.0},
	uLINK[13].m=0.2;
	uLINK[13].mother=12;
	uLINK[13].sister=0;
	uLINK[13].child=0;

	uLINK[13].b(0)=0;uLINK[13].b(1)=0;uLINK[13].b(2)=0;
	uLINK[13].a(0)=1;uLINK[13].a(1)=0;uLINK[13].a(2)=0;

	uLINK[13].c(0)=0;uLINK[13].c(1)=0;uLINK[13].c(2)=0;
	uLINK[13].p(0)=0;uLINK[13].p(1)=0;uLINK[13].p(2)=0;
	uLINK[13].v(0)=0;uLINK[13].v(1)=0;uLINK[13].v(2)=0;
	uLINK[13].w(0)=0;uLINK[13].w(1)=0;uLINK[13].w(2)=0;

	uLINK[13].R(0,0)=0;uLINK[13].R(0,1)=0;uLINK[13].R(0,2)=0;
	uLINK[13].R(1,0)=0;uLINK[13].R(1,1)=0;uLINK[13].R(1,2)=0;
	uLINK[13].R(2,0)=0;uLINK[13].R(2,1)=0;uLINK[13].R(2,2)=0;

	uLINK[13].q=0.0;
	uLINK[13].dq=0.0;
	uLINK[13].ddq=0.0;

	uLINK[BODY].p(2) =0.21;

	uLINK[BODY].R(0,0)=1;uLINK[BODY].R(0,1)=0;uLINK[BODY].R(0,2)=0;
	uLINK[BODY].R(1,0)=0;uLINK[BODY].R(1,1)=1;uLINK[BODY].R(1,2)=0;
	uLINK[BODY].R(2,0)=0;uLINK[BODY].R(2,1)=0;uLINK[BODY].R(2,2)=1;

	uLINK[BODY].v(0)=0;uLINK[BODY].v(1)=0;uLINK[BODY].v(2)=0;
	uLINK[BODY].w(0)=0;uLINK[BODY].w(1)=0;uLINK[BODY].w(2)=0;


	Rfoot.name="Rfoot";
	Rfoot.m=0.2;///0.2
	Rfoot.mother=7;///7
	Rfoot.sister=0;
	Rfoot.child=0;
	Rfoot.b(0)=0;Rfoot.b(1)=0;Rfoot.b(2)=0;
	Rfoot.a(0)=0;Rfoot.a(1)=0;Rfoot.a(2)=1;
	Rfoot.c(0)=0;Rfoot.c(1)=0;Rfoot.c(2)=-0.035;
	Rfoot.p(0)=-0.02;Rfoot.p(1)=-0.055;Rfoot.p(2)=0.05;
//	Rfoot.p(0)=-0.01;Rfoot.p(1)=-0.055;Rfoot.p(2)=0.05;
	Rfoot.v(0)=0;Rfoot.v(1)=0;Rfoot.v(2)=0;
	Rfoot.w(0)=0;Rfoot.w(1)=0;Rfoot.w(2)=0;

	Rfoot.R(0,0)=1;Rfoot.R(0,1)=0;Rfoot.R(0,2)=0;
	Rfoot.R(1,0)=0;Rfoot.R(1,1)=1;Rfoot.R(1,2)=0;
	Rfoot.R(2,0)=0;Rfoot.R(2,1)=0;Rfoot.R(2,2)=1;

	Rfoot.q=0.0;
	Rfoot.dq=0.0;
	Rfoot.ddq=0.0;
	Lfoot.name="Lfoot";
	Lfoot.m=0.2;///0.2
	Lfoot.mother=13;///13
	Lfoot.sister=0;
	Lfoot.child=0;
	Lfoot.b(0)=0;Lfoot.b(1)=0;Lfoot.b(2)=0;
	Lfoot.a(0)=0;Lfoot.a(1)=0;Lfoot.a(2)=1;

	Lfoot.c(0)=0;Lfoot.c(1)=0;Lfoot.c(2)=-0.035;
	Lfoot.p(0)=-0.02;Lfoot.p(1)=0.055;Lfoot.p(2)=0.05;
//	Lfoot.p(0)=-0.01;Lfoot.p(1)=0.055;Lfoot.p(2)=0.05;
	Lfoot.v(0)=0;Lfoot.v(1)=0;Lfoot.v(2)=0;
	Lfoot.w(0)=0;Lfoot.w(1)=0;Lfoot.w(2)=0;

	Lfoot.R(0,0)=1;Lfoot.R(0,1)=0;Lfoot.R(0,2)=0;
	Lfoot.R(1,0)=0;Lfoot.R(1,1)=1;Lfoot.R(1,2)=0;
	Lfoot.R(2,0)=0;Lfoot.R(2,1)=0;Lfoot.R(2,2)=1;

	Lfoot.q=0.0;
	Lfoot.dq=0.0;
	Lfoot.ddq=0.0;

	uLINK[RLEG_J2].q = -10.0*PI_180;
	uLINK[RLEG_J3].q = 20.0*PI_180;
	uLINK[RLEG_J4].q = -10.0*PI_180;
	uLINK[RLEG_J5].q = 0*PI_180;

	uLINK[LLEG_J2].q = -10.0*PI_180;
	uLINK[LLEG_J3].q = 20.0*PI_180;
	uLINK[LLEG_J4].q = -10.0*PI_180;
	uLINK[LLEG_J5].q = 0*PI_180;
	
	com.resize(3);
	com(0)=0;com(1)=0;com(2)=0;
	oldFoot.resize(3);
	oldFoot(0)=0;oldFoot(1)=0;oldFoot(2)=0;
	oldRFoot.resize(3);
	oldRFoot(0)=0;oldRFoot(1)=0;oldRFoot(2)=0;
	oldLFoot.resize(3);
	oldLFoot(0)=0;oldLFoot(1)=0;oldLFoot(2)=0;
	P.resize(3);
	P(0)=0;P(1)=0;P(2)=0;
	V.resize(3);
	V(0)=0;V(1)=0;V(2)=0;
	Zc=0.0;
	Tc=0.0;
	cx0=0.0;cy0=0.0;vx0=0.0;vx1=0.0;vy0=0.0;vy1=0.0;
	Dtime=0.0;EndTime=0.0;tsize=0;datak=0.0;datakk=0.0;eachFoot=0.0;footLength=0.0;footDisc=0.0;zmpz=0.0;k=0;kk=0.0;kky=0.0;nk=0.0;
	y0=0.0;y1=0.0;Ty=0.0;Ty2=0.0;Tx=0.0;x0=0.0;x1=0.0;
	px=0.0;py=0.0;vx=0.0;vy=0.0;
	
	turnHeadAngle=0;
	swingLeftAngle=0;
	swingRightAngle=0;
	swingLeftAngle2=0;
	swingRightAngle2=0;
	bodyForerakeAngle=0;
	legForerakeAngle=0;
	horizonForerakeAngle=0;
	
	turnLeftAngle=0;
	turnRightAngle=0;
	
	whichFoot=0;
	increaseHigh=0;
///	beginShoot=true;
	
	horizMoveLength=0;
	turnAngle=0;
	nextX=0;
	nextY=0;
	Sx=0.22;
	Sy=0.11;
	
	firstStep=true;
	leftStep=false;
	rightStep=false;
	init=false;
	
	firstReadDate=true;///feng
	walkCounter=0;///feng
	sendCount=0;///feng

	judgeFallDown=false;
	hasFallDown=false;
	
	footWidth=0;
	footLength=0;
	
///	intercept=false;
	
	initPass();
}
#endif



Action NewWalk::CreateWalkGait(Vector3& destination,float& angleToTurn,TopSpeed& topSpeed)
{
//	cout<<"1111111"<<endl;
 	if(hasFallDown==true)///new add
  	{
  		InitNewWalkData();
  		hasFallDown=false;
 		UseNewWalk=true;
		/////////////////cout<<"*****************fall down"<<endl;
     	}
     	
     	if(UseNewWalk==false)
 	{
		if(walkCounter==1&&stepIncrement<=0.003)
 		{
		      InitNewWalkData();
		      UseNewWalk=true;
		      
  		}
 		else
 		{
 			/////////////////cout<<"time :"<<wm.GetCurrentGameTime()<<"	walk Counter "<<walkCounter<<endl;
 			WalkDirection ww =WALK_FORWARD;
 			SpeedStrategy sss=QUICK_SPEED_DOWN;
 			float cc =0;
 			HorizonMoveDirection hh=HORIZONMOVE_NULL;
 			return HalfStepGait(ww,cc,sss,hh,cc);
 		}
 	}
//     	cout<<"updateTime"<<endl;
         updateTime();
	 updateBodyAngleToDestination(destination);
	 updateFootLengthWidth(topSpeed);
//  	cout<<"	 updateTurnAngle( angleToTurn);"<<endl;
	 updateTurnAngle( angleToTurn);

	// adjustMySpeedByBodyState();
	//adjustMyBarycenterToProtectMyself();
	 exchangeArms();
//	 	cout<<"exchangeArms();"<<endl;

	 preparation();
//	 	cout<<"	 preparation();"<<endl;
    updatePV();
	///  updatepbPV();

// 	cout<<"readNewWalkData"<<endl;
	return readNewWalkData();
}

void NewWalk::updateTime()
{
        if(firstStep==true)
        {
            walkCounter++;
		//changeFoot=false;
            if(walkCounter==FOOT_CYCLE)
            {
                firstStep=false;
                leftStep=true;
                walkCounter=0;
		init=false;
            }
        }
        else//firstStep==false
        {
            if(leftStep==true)
            {
                walkCounter++;
		if(walkCounter==FOOT_CYCLE)
                {
		    
		    leftStep=false;
                    rightStep=true;
                    walkCounter=0;
		    
		    if(justAfterPass)
		    {
			justAfterPass=false;
		    }
		    if(justAfterPass3)
		    {
			justAfterPass3=false;
		    }
		    if(nowForPass)
		    {
			justAfterPass=true;
			nowForPass=false;
		    }
		    if(nowForPass2)
			nowForPass2=false;
		    if(nowForPass3)
		    {
			nowForPass3=false;
			justAfterPass3=true; 
		    }
    		    if(nowForPass4)
			nowForPass4=false;

		 
		  //     ///////////cout<<"change step , my distance to ball :"<<wm.GetMyDistanceToBall()<<"	foot Lengh :"<<footLength<<endl;
		
                }
            }
            else if(rightStep==true)
            {
                walkCounter++;
		
		
		
                if(walkCounter==FOOT_CYCLE)
                {
                    rightStep=false;
                    leftStep=true;
                    walkCounter=0;
		   		    
		    if(justAfterPass)
		    {
			justAfterPass=false;
		    }
		    if(justAfterPass3)
		    {
			justAfterPass3=false;
		    }
		    if(nowForPass)
		    {
			justAfterPass=true;
			nowForPass=false;
		    }
		    if(nowForPass2)
			nowForPass2=false;
		    if(nowForPass4)
			nowForPass4=false;
		    if(nowForPass3)
		    {
			nowForPass3=false;
			justAfterPass3=true;
		    }
		        //  ///////////cout<<"change step , my distance to ball :"<<wm.GetMyDistanceToBall()<<"	foot Lengh :"<<footLength<<endl;
                }
            }
        }
}


void NewWalk::updateWalkDirection(WalkDirection& walkDirection)
{
//if(walkCounter==0)
{
	if( walkDirection==WALK_FORWARD )
	{
		whetherWalkForward=1;
	}
	else if(walkDirection==WALK_BACKWARD)
	{
		whetherWalkForward=-1;
	}
}
}


void NewWalk::updateSpeedStrategy(SpeedStrategy& speedStrategy,DecisionMotion& decisionChoice,WalkDirection& walkDirection,TopSpeed& topSpeed)
{
//	if(walkCounter==0)///	if(leftStep==true||rightStep==true)
{  cout<<"eeeeeeeeeeeee"<<endl;
   cout<<"eeeeeeeeeeeee"<<endl;
   cout<<"eeeeeeeeeeeee"<<endl;
   cout<<"eeeeeeeeeeeee"<<endl;

	if(speedStrategy==FORWARD_QUICK_SPEED_UP)
	{
		footLength=footLength+QUICK_FOOTLENGTH_INCREAMENT;
		if(topSpeed==MAX_SPEED)
		{
			if(footLength>MAXSPEED)
				footLength=MAXSPEED;
		}
		else if(topSpeed==MID_SPEED)
		{
			if(footLength>MIDSPEED)
				footLength=MIDSPEED;
		}
		else if(topSpeed==MIN_SPEED)
		{
			if(footLength>MINSPEED)
				footLength=MINSPEED;
		}
		else// if(decisionChoice==WALK_TO_MY_POSITION)
		{
		//	if(footLength>MAXSPEED)
		//		footLength=MAXSPEED;
		}
	}
	else if(speedStrategy==FORWARD_SLOW_SPEED_UP)
	{
		footLength=footLength+SLOW_FOOTLENGTH_INCREAMENT;
		if(topSpeed==MAX_SPEED)
		{
			/////////////////cout<<"1999999"<<endl;
			if(footLength>MAXSPEED)
				footLength=MAXSPEED;
		}
		else if(topSpeed==MID_SPEED)
		{
			if(footLength>MIDSPEED)
			{
				/////////////////cout<<"1222222"<<endl;
				footLength=MIDSPEED;
			}
		}
		else if(topSpeed==MIN_SPEED)
		{
			if(footLength-MINSPEED>SLOW_FOOTLENGTH_INCREAMENT+0.001)
			{
				/////////////////cout<<"1333333"<<endl;
				footLength=footLength-2*QUICK_FOOTLENGTH_INCREAMENT;
			}
			else if(footLength+MINSPEED<-SLOW_FOOTLENGTH_INCREAMENT-0.001)
			{
				/////////////////cout<<"1888888888"<<endl;
				footLength=footLength+2*QUICK_FOOTLENGTH_INCREAMENT;	
			}
			else
			{
				/////////////////cout<<"144444"<<endl;
				footLength=MINSPEED;
			}
		}
		else// if(decisionChoice==WALK_TO_MY_POSITION)
		{
		//	if(footLength>MAXSPEED)
		//		footLength=MAXSPEED;
		}
	}
	else if(speedStrategy==FORWARD_QUICK_SPEED_DOWN)
	{
		footLength=footLength-QUICK_FOOTLENGTH_INCREAMENT;
		if(topSpeed==MAX_SPEED)
		{
			/////////////////cout<<"121212121212"<<endl;
			if(footLength<MAXSPEED)
				footLength=MAXSPEED;
		}
		else if(topSpeed==MID_SPEED)
		{
			if(footLength<MIDSPEED)
			{
				if(MIDSPEED-footLength>QUICK_FOOTLENGTH_INCREAMENT+0.001)
				{
					/////////////////cout<<"footLength=footLength+2*QUICK_FOOTLENGTH_INCREAMENT;"<<endl;
					footLength=footLength+2*QUICK_FOOTLENGTH_INCREAMENT;
				}
				else
				{
					/////////////////cout<<"footLength=MIDSPEED;"<<endl;
					footLength=MIDSPEED;
				}
			}
		}
		else if(topSpeed==MIN_SPEED)
		{
			/////////////////cout<<"3232323232"<<endl;
			if(footLength<MINSPEED)
				footLength=MINSPEED;
		}
		else// if(decisionChoice==WALK_TO_MY_POSITION)
		{
			if(footLength<0)
				footLength=0;
		}
	}
	else if(speedStrategy==FORWARD_SLOW_SPEED_DOWN)
	{
		footLength=footLength-SLOW_FOOTLENGTH_INCREAMENT;
		if(topSpeed==MAX_SPEED)
		{
			if(footLength<MAXSPEED)
				footLength=MAXSPEED;
		}
		else if(topSpeed==MID_SPEED)
		{
			if(footLength<MIDSPEED)
				footLength=MIDSPEED;
		}
		else if(topSpeed==MIN_SPEED)
		{
			if(footLength+MINSPEED<-SLOW_FOOTLENGTH_INCREAMENT-0.001)
			{
				footLength=footLength+2*QUICK_FOOTLENGTH_INCREAMENT;
			}
			else if(footLength-MINSPEED>SLOW_FOOTLENGTH_INCREAMENT+0.001)
			{
				footLength=footLength-2*QUICK_FOOTLENGTH_INCREAMENT;
			}
			else
				footLength=MINSPEED;
		}
		else// if(decisionChoice==WALK_TO_MY_POSITION)
		{
			if(footLength<0)
				footLength=0;
		}
	}

	else if(speedStrategy==BACKWARD_QUICK_SPEED_DOWN)
	{
		cout<<"66666666666666666"<<endl;
		if(footLength<=0)
		{
			footLength=footLength+QUICK_FOOTLENGTH_INCREAMENT;
			if(topSpeed==MAX_SPEED)
			{
				/////////////////cout<<"777777111111111"<<endl;
				if(footLength>-MAXSPEED)
				{
					/////////////////cout<<"777777772222222222"<<endl;
					footLength=-MAXSPEED;
				}
			}
			else if(topSpeed==MID_SPEED)
				{
				/////////////////cout<<"8888811111111"<<endl;
				if(footLength>-MIDSPEED)
				{
					/////////////////cout<<"88888882222222"<<endl;
					if(MID_SPEED-fabs(footLength)>QUICK_FOOTLENGTH_INCREAMENT+0.001)
						footLength=footLength-2*QUICK_FOOTLENGTH_INCREAMENT;
					else
						footLength=-MIDSPEED;
				}
			}
			else if(topSpeed==MIN_SPEED)
			{
				/////////////////cout<<"999999999111111"<<endl;
				if(footLength>-MINSPEED)
				{
					/////////////////cout<<"9999999222222"<<endl;
					footLength=-MINSPEED;
				}
				//if(footLength-MIN_SPEED>QUICK_FOOTLENGTH_INCREAMENT+0.001)
				//		footLength=footLength-2*QUICK_FOOTLENGTH_INCREAMENT;
				//	else if(footLength+MIN_SPEED<-QUICK_FOOTLENGTH_INCREAMENT-0.001)
				//		footLength=footLength+2*QUICK_FOOTLENGTH_INCREAMENT;;
			}
			else// if(decisionChoice==WALK_TO_MY_POSITION)
			{
				/////////////////cout<<"01010101010101"<<endl;
				if(footLength>0)
				{
					/////////////////cout<<"111111101110111011"<<endl;
					footLength=0;
				}
			}
		}
		else if(footLength>0)
		{
			footLength=footLength-2*QUICK_FOOTLENGTH_INCREAMENT;
			/////////////////cout<<"0808080808080800808"<<endl;
		/*	if(topSpeed==MAX_SPEED)
			{
				/////////////////cout<<"777777111111111"<<endl;
				if(footLength>-MAXSPEED)
				{
					/////////////////cout<<"777777772222222222"<<endl;
					footLength=-MAXSPEED;
				}
			}
			else if(topSpeed==MID_SPEED)
				{
				/////////////////cout<<"8888811111111"<<endl;
				if(footLength>-MIDSPEED)
				{
					/////////////////cout<<"88888882222222"<<endl;
					if(MID_SPEED-fabs(footLength)>QUICK_FOOTLENGTH_INCREAMENT+0.001)
						footLength=footLength-2*QUICK_FOOTLENGTH_INCREAMENT;
					else
						footLength=-MIDSPEED;
				}
			}
			else if(topSpeed==MIN_SPEED)
			{
				/////////////////cout<<"999999999111111"<<endl;
				if(footLength>-MINSPEED)
				{
					/////////////////cout<<"9999999222222"<<endl;
					footLength=-MINSPEED;
				}
				//if(footLength-MIN_SPEED>QUICK_FOOTLENGTH_INCREAMENT+0.001)
				//		footLength=footLength-2*QUICK_FOOTLENGTH_INCREAMENT;
				//	else if(footLength+MIN_SPEED<-QUICK_FOOTLENGTH_INCREAMENT-0.001)
				//		footLength=footLength+2*QUICK_FOOTLENGTH_INCREAMENT;;
			}
			else// if(decisionChoice==WALK_TO_MY_POSITION)
			{
				/////////////////cout<<"01010101010101"<<endl;
				if(footLength>0)
				{
					/////////////////cout<<"111111101110111011"<<endl;
					footLength=0;
				}
			}
		*/
		}
	}
	else if(speedStrategy==BACKWARD_SLOW_SPEED_DOWN)
	{
		footLength=footLength+SLOW_FOOTLENGTH_INCREAMENT;
		if(topSpeed==MAX_SPEED)
		{
			if(footLength>-MAXSPEED)
				footLength=-MAXSPEED;
		}
		else if(topSpeed==MID_SPEED)
		{
			if(footLength>-MIDSPEED)
				footLength=-MIDSPEED;
		}
		else if(topSpeed==MIN_SPEED)
		{
			if(footLength>-MINSPEED)
				footLength=-MINSPEED;
		}
		else// if(decisionChoice==WALK_TO_MY_POSITION)
		{
			if(footLength>0)
				footLength=0;
		}
	}
	else if(speedStrategy==BACKWARD_QUICK_SPEED_UP)
	{
		footLength=footLength-QUICK_FOOTLENGTH_INCREAMENT;
		if(topSpeed==MAX_SPEED)
		{
			if(footLength<-MAXSPEED)
				footLength=-MAXSPEED;
		}
		else if(topSpeed==MID_SPEED)
		{
			if(footLength<-MIDSPEED)
				footLength=-MIDSPEED;
		}
		else if(topSpeed==MIN_SPEED)
		{
			if(footLength<-MINSPEED)
				footLength=-MINSPEED;
		}
		else// if(decisionChoice==WALK_TO_MY_POSITION)
		{
			
		}
	}
	else if(speedStrategy==BACKWARD_SLOW_SPEED_UP)
	{
		footLength=footLength-SLOW_FOOTLENGTH_INCREAMENT;
		if(topSpeed==MAX_SPEED)
		{
			if(footLength<-MAXSPEED)
				footLength=-MAXSPEED;
		}
		else if(topSpeed==MID_SPEED)
		{
			/////////////////cout<<"1555555"<<endl;
			if(footLength<-MIDSPEED)
				footLength=-MIDSPEED;
		}
		else if(topSpeed==MIN_SPEED)
		{
			/////////////////cout<<"16666666"<<endl;
			if(MINSPEED+footLength<SLOW_FOOTLENGTH_INCREAMENT-0.001)
			{
				/////////////////cout<<"1777777111"<<endl;
				footLength=footLength+2*QUICK_FOOTLENGTH_INCREAMENT;
			}
			else if(footLength-MINSPEED>SLOW_FOOTLENGTH_INCREAMENT+0.001)
			{
				/////////////////cout<<"177777222"<<endl;
				footLength=footLength-2*QUICK_FOOTLENGTH_INCREAMENT;
			}
			else
				footLength=-MINSPEED;
		}
		else// if(decisionChoice==WALK_TO_MY_POSITION)
		{
			
		}
	
	}
	else///SPEED_NULL
	{
		if(footLength>MAXSPEED)
		{
			footLength-=2*QUICK_FOOTLENGTH_INCREAMENT;
		}
		else if(footLength>MID_SPEED)
		{
			footLength-=2*QUICK_FOOTLENGTH_INCREAMENT;
		}
		else if(footLength>MIN_SPEED)
		{
			footLength-=QUICK_FOOTLENGTH_INCREAMENT;
		}
		else if(footLength<-MAX_SPEED)
		{
			footLength+=2*QUICK_FOOTLENGTH_INCREAMENT;
		}
		else if(footLength<-MID_SPEED)
		{
			footLength+=2*QUICK_FOOTLENGTH_INCREAMENT;
		}
		else if(footLength<-MIN_SPEED)
		{
			footLength+=1*QUICK_FOOTLENGTH_INCREAMENT;
		}
		else
		{
			footLength=0.00;
		}
	}
}
/////////////////cout<<"  footLength:       "<<footLength<<endl;
}


void NewWalk::updateHorizontalMoveSpeed(HorizonMoveDirection& moveDirection,HorizonMoveSpeedStrategy& moveStrategy,TopHorizontalSpeed& topHorizontalSpeed)///moveDirection rightnow useless
{
//	if(walkCounter==1)///if(leftStep==true||rightStep==true)
{
	if(moveStrategy==HORIZONMOVE_LEFT_QUICK_SPEED_UP )
	{
		footWidth=footWidth-0.002;
		if(topHorizontalSpeed==HORIZONTAL_MAX_SPEED)
		{
			if(footWidth<-HORIZONMOVEMAXSPEED)
			footWidth=-HORIZONMOVEMAXSPEED;
		}
		else if(topHorizontalSpeed==HORIZONTAL_MID_SPEED)
		{
			if(footWidth<-HORIZONMOVEMIDSPEED)
			footWidth=-HORIZONMOVEMIDSPEED;
		}
		else if(topHorizontalSpeed==HORIZONTAL_MIN_SPEED)
		{
			if(footWidth<-HORIZONMOVEMINSPEED)
			footWidth=-HORIZONMOVEMINSPEED;
		}
		else
		{
			if(footWidth<-HORIZONMOVEMAXSPEED)
			footWidth=-HORIZONMOVEMAXSPEED;
		}
		
	}
	else if(moveStrategy==HORIZONMOVE_RIGHT_QUICK_SPEED_DOWN)
	{
		footWidth=footWidth-0.002;
		if(topHorizontalSpeed==HORIZONTAL_MAX_SPEED)
		{
			if(footWidth<HORIZONMOVEMAXSPEED)
			footWidth=HORIZONMOVEMAXSPEED;
		}
		else if(topHorizontalSpeed==HORIZONTAL_MID_SPEED)
		{
			if(footWidth<HORIZONMOVEMIDSPEED)
			footWidth=HORIZONMOVEMIDSPEED;
		}
		else if(topHorizontalSpeed==HORIZONTAL_MIN_SPEED)
		{
			if(footWidth<HORIZONMOVEMINSPEED)
			footWidth=HORIZONMOVEMINSPEED;
		}
		else
		{
			if(footWidth<0)
			footWidth=0;
		}
	}
	else if(moveStrategy==HORIZONMOVE_LEFT_SLOW_SPEED_UP )
	{
		footWidth=footWidth-0.001;
		if(topHorizontalSpeed==HORIZONTAL_MAX_SPEED)
		{
			if(footWidth<-HORIZONMOVEMAXSPEED)
			footWidth=-HORIZONMOVEMAXSPEED;
		}
		else if(topHorizontalSpeed==HORIZONTAL_MID_SPEED)
		{
			if(footWidth<-HORIZONMOVEMIDSPEED)
			footWidth=-HORIZONMOVEMIDSPEED;
		}
		else if(topHorizontalSpeed==HORIZONTAL_MIN_SPEED)
		{
			if(footWidth<-HORIZONMOVEMINSPEED)
			footWidth=-HORIZONMOVEMINSPEED;
		}
		else
		{
			if(footWidth<-HORIZONMOVEMAXSPEED)
			footWidth=-HORIZONMOVEMAXSPEED;
		}
	}
	else if(moveStrategy==HORIZONMOVE_RIGHT_SLOW_SPEED_DOWN)
	{
		footWidth=footWidth-0.001;
		if(topHorizontalSpeed==HORIZONTAL_MAX_SPEED)
		{
			if(footWidth<HORIZONMOVEMAXSPEED)
			footWidth=HORIZONMOVEMAXSPEED;
		}
		else if(topHorizontalSpeed==HORIZONTAL_MID_SPEED)
		{
			if(footWidth<HORIZONMOVEMIDSPEED)
			{
				footWidth=HORIZONMOVEMIDSPEED;
//				/////////////////cout<<"footWidth=HORIZONMOVEMIDSPEED"<<endl;
			}	
		}
		else if(topHorizontalSpeed==HORIZONTAL_MIN_SPEED)
		{
			if(footWidth<HORIZONMOVEMINSPEED)
			{
				footWidth=HORIZONMOVEMINSPEED;
//				/////////////////cout<<"footWidth=HORIZONMOVEMINSPEED"<<endl;
			}
		}
		else
		{
			if(footWidth<0)
			{
				footWidth=0;
//				/////////////////cout<<"footWidth=0;"<<endl;
			}
		}
	}
	else if(moveStrategy==HORIZONMOVE_RIGHT_QUICK_SPEED_UP)
	{
		footWidth=footWidth+0.002;
		if(topHorizontalSpeed==HORIZONTAL_MAX_SPEED)
		{
			if(footWidth>HORIZONMOVEMAXSPEED)
			footWidth=HORIZONMOVEMAXSPEED;
		}
		else if(topHorizontalSpeed==HORIZONTAL_MID_SPEED)
		{
			if(footWidth>HORIZONMOVEMIDSPEED)
			footWidth=HORIZONMOVEMIDSPEED;
		}
		else if(topHorizontalSpeed==HORIZONTAL_MIN_SPEED)
		{
			if(footWidth>HORIZONMOVEMINSPEED)
			footWidth=HORIZONMOVEMINSPEED;
		}
		else
		{
			if(footWidth>HORIZONMOVEMAXSPEED)
			footWidth=HORIZONMOVEMAXSPEED;	
		}
	}
	else if(moveStrategy==HORIZONMOVE_LEFT_QUICK_SPEED_DOWN)
	{
		footWidth=footWidth+0.002;
		if(topHorizontalSpeed==HORIZONTAL_MAX_SPEED)
		{
			if(footWidth>-HORIZONMOVEMAXSPEED)
			footWidth=-HORIZONMOVEMAXSPEED;
		}
		else if(topHorizontalSpeed==HORIZONTAL_MID_SPEED)
		{
			if(footWidth>-HORIZONMOVEMIDSPEED)
			footWidth=-HORIZONMOVEMIDSPEED;
		}
		else if(topHorizontalSpeed==HORIZONTAL_MIN_SPEED)
		{
			if(footWidth>-HORIZONMOVEMINSPEED)
			footWidth=-HORIZONMOVEMINSPEED;
		}
		else
		{
			if(footWidth>0)
			footWidth=0;
		}
		
	}
	else if(moveStrategy==HORIZONMOVE_RIGHT_SLOW_SPEED_UP )
	{
		footWidth=footWidth+0.001;
		if(topHorizontalSpeed==HORIZONTAL_MAX_SPEED)
		{
			if(footWidth>HORIZONMOVEMAXSPEED)
			footWidth=HORIZONMOVEMAXSPEED;
		}
		else if(topHorizontalSpeed==HORIZONTAL_MID_SPEED)
		{
			if(footWidth>HORIZONMOVEMIDSPEED)
			footWidth=HORIZONMOVEMIDSPEED;
		}
		else if(topHorizontalSpeed==HORIZONTAL_MIN_SPEED)
		{
			if(footWidth>HORIZONMOVEMINSPEED)
			footWidth=HORIZONMOVEMINSPEED;
		}
		else
		{
			if(footWidth>HORIZONMOVEMAXSPEED)
			footWidth=HORIZONMOVEMAXSPEED;
		}
		
	}
	else if(moveStrategy==HORIZONMOVE_LEFT_SLOW_SPEED_DOWN)
	{
		footWidth=footWidth+0.001;
		if(topHorizontalSpeed==HORIZONTAL_MAX_SPEED)
		{
			if(footWidth>-HORIZONMOVEMAXSPEED)
			footWidth=-HORIZONMOVEMAXSPEED;
		}
		else if(topHorizontalSpeed==HORIZONTAL_MID_SPEED)
		{
			if(footWidth>-HORIZONMOVEMIDSPEED)
			footWidth=-HORIZONMOVEMIDSPEED;
		}
		else if(topHorizontalSpeed==HORIZONTAL_MIN_SPEED)
		{
			if(footWidth>-HORIZONMOVEMINSPEED)
			footWidth=-HORIZONMOVEMINSPEED;
		}
		else
		{
			if(footWidth>0)
			footWidth=0;
		}
		
	}
	else
	{
		footWidth=0;
	}

}	
/////////////////cout<<"footWidth:         "<<footWidth<<endl;
}

void NewWalk::updateTurnAngle(float& angle)
{
  /*
	float slowTurnIncrement=0.008;
	float quickTurnIncrement=0.016;
	float slowTurnMinAngle=-0.08;
	float quickTurnMinAngle=-0.16;*/

	float slowTurnIncrement=0.012;
	float quickTurnIncrement=0.023;
	float slowTurnMinAngle=-0.08;
	float quickTurnMinAngle=-0.16;
	
	if(footLength>=1.50)
			{
				/*     slowTurnIncrement=0;
				  	 quickTurnIncrement=0;
			        slowTurnMinAngle=0;
					 quickTurnMinAngle=0;*/


		slowTurnIncrement=0.012;
		 quickTurnIncrement=0.023;
		 slowTurnMinAngle=-0.08;
			 quickTurnMinAngle=-0.16;

			}
	if(footLength>=0.11 && footLength<0.150 )
	{ quickTurnIncrement=0.012;
	 quickTurnMinAngle=-0.08;

	}
	if(fabs(angle)>20)
	{
		turnSlowly=false;
		turnQuickly=true;
	}
	else if(fabs(angle)<=20)
	{
		turnSlowly=true;
		turnQuickly=false;
	}

	
	if(leftStep == true)//put up the left foot
	{

		if( fabs(angle) <= 1 )
		{
		/*	if(footLength<=0.06)
			{
			turnLeftAngle=0;
			turnRightAngle=0;
			}
			else*/
			{
			turnLeftAngle= turnLeftAngle+0;
			turnRightAngle=turnLeftAngle;
			}
		}
		else if(angle < 0)//turn to right
		{	
			if(turnSlowly == true)
			{
				if(turnLeftAngle <= 0)
					turnLeftAngle=turnLeftAngle+slowTurnIncrement;
			
				turnRightAngle=turnLeftAngle;
			}
			else if(turnQuickly == true)
			{
				if(turnLeftAngle <= 0)
					turnLeftAngle=turnLeftAngle+quickTurnIncrement;
			
				turnRightAngle=turnLeftAngle;
			}
		}
		else//turn to left
		{
			if(turnSlowly == true)
			{
				if(turnRightAngle >= slowTurnMinAngle)
					turnRightAngle=turnRightAngle-slowTurnIncrement;
			
				turnLeftAngle=turnRightAngle;
			}
			else if(turnQuickly == true)
			{
				if(turnRightAngle >= quickTurnMinAngle)
					turnRightAngle=turnRightAngle-quickTurnIncrement;
			
				turnLeftAngle=turnRightAngle;
			}
		}
	}
	else if(rightStep == true)//put up the right foot
	{
if( fabs(angle) <= 1 )
		{
		/*	 if(footLength<=0.06)
			 {
			turnLeftAngle=0;
		turnRightAngle=0;
			 }
			 else*/
			 {
			turnLeftAngle=turnLeftAngle+0;
						turnRightAngle=turnLeftAngle;
			 }
		}
		else if(angle < 0)//turn to right
		{	
			if(turnSlowly == true)
			{
				if(turnLeftAngle >= slowTurnMinAngle)
					turnLeftAngle=turnLeftAngle-slowTurnIncrement;
			
				turnRightAngle=turnLeftAngle;
			}
			else if(turnQuickly == true)
			{
				if(turnLeftAngle >= quickTurnMinAngle)
					turnLeftAngle=turnLeftAngle-quickTurnIncrement;
			
				turnRightAngle=turnLeftAngle;
			}
		}
		else//turn to left
		{
			if(turnSlowly == true)
			{
				if(turnRightAngle <= 0)
					turnRightAngle=turnRightAngle+slowTurnIncrement;
			
				turnLeftAngle=turnRightAngle;
			}
			else if(turnQuickly == true)
			{
				if(turnRightAngle <= 0)
					turnRightAngle=turnRightAngle+quickTurnIncrement;
				turnLeftAngle=turnRightAngle;
			}
		}
	}
	
}
void NewWalk::exchangeArms()
{
	if(lastCycleFootLength>0.16)
	{
	      lastCycleFootLength=0.16;    //0.13
	}
	if(firstStep==true)
	{
		swingLeftAngle=swingLeftAngle+lastCycleFootLength*15;		//15
		swingRightAngle=-swingLeftAngle;			
	}
	else if(leftStep==true)
	{
		swingLeftAngle=swingLeftAngle-lastCycleFootLength*30;//30  //100
		swingRightAngle=-swingLeftAngle;
		if(walkCounter==3)
		{
		  swingLeftAngle=0;
		  swingRightAngle=0;
		}
	}
	else
	{
		swingLeftAngle=swingLeftAngle+lastCycleFootLength*30;//30 //100
		swingRightAngle=-swingLeftAngle;	
		if(walkCounter==3)
		{
		  swingLeftAngle=0;
		  swingRightAngle=0;
		}
	}
	if(fabs(footLength)<=0.02)
	{
		swingLeftAngle=0;
		swingRightAngle=0;
	}
	      bodyForerakeAngle=3.3*PI_180; //3.3  5.5
	      legForerakeAngle=0.6*PI_180;//0.6
	      horizonForerakeAngle=footWidth*25*PI_180;
	      if(footWidth<0){
		swingRightAngle2=0;
		swingLeftAngle2=-footWidth*200;
	      }
	      else{
		swingRightAngle2=-footWidth*200;
		swingLeftAngle2=0;
	      }
// 	      bodyForerakeAngle=4*PI/180;
// 	      legForerakeAngle=0.7*PI/180;
// // 	      if(fabs(footWidth)<0.05)
// 		    horizonForerakeAngle=footWidth*26*PI/180;
// 	      else
// 		    horizonForerakeAngle=footWidth*22*PI/180;
// 	if(footLength<0){ 
// 		if(footLength<lastCycleFootLength){
// 			bodyForerakeAngle-=0.05*PI/180;
// 			if(bodyForerakeAngle<2.1*PI/180)
// 			      bodyForerakeAngle=2.1*PI/180;
// 		}
// 		else if(footLength>lastCycleFootLength){
// 			bodyForerakeAngle+=0.1*PI/180;
// 			if(bodyForerakeAngle>4*PI/180)
// 			      bodyForerakeAngle=4*PI/180;
// 		}
// 	}
// 	
// 	if(footWidth>lastCycleFootWidth)
// 	{
// 		horizonForerakeAngle=footWidth*22*PI/180+0.05*PI/180;
// 		if(footWidth<0)
// 		{
// 		  if(horizonForerakeAngle>0)
// 		      horizonForerakeAngle=0;
// 		}
// 		else 
// 		{
// 		   if(horizonForerakeAngle>footWidth*28*PI/180)
// 		     horizonForerakeAngle=footWidth*28*PI/180;
// 		}
// 	}
// 	else if(footWidth<lastCycleFootWidth)
// 	{
// 		horizonForerakeAngle=footWidth*22*PI/180-0.05*PI/180;
// 		if(footWidth>0)
// 		{
// 		  if(horizonForerakeAngle<0)
// 		      horizonForerakeAngle=0;
// 		}
// 		else 
// 		{
// 		   if(horizonForerakeAngle<footWidth*28*PI/180)
// 		     horizonForerakeAngle=footWidth*28*PI/180;
// 		}
// 	}
// 	else
// 	{
// 		if(horizonForerakeAngle>footWidth*22*PI/180)
// 		{
// 		      horizonForerakeAngle-=0.01*PI/180;
// 		      if(horizonForerakeAngle<footWidth*22*PI/180)
// 			horizonForerakeAngle=footWidth*22*PI/180;
// 		}
// 		else if(horizonForerakeAngle<footWidth*22*PI/180)
// 		{
//   		      horizonForerakeAngle+=0.01*PI/180;
// 		      if(horizonForerakeAngle>footWidth*22*PI/180)
// 			horizonForerakeAngle=footWidth*22*PI/180;
// 		}
// 	}
	
}

void NewWalk::preparation()
{
	HIP=agent.GetHIP();
		THIGH=agent.GetTHIGH();
		SHANK=agent.GetSHANK();
		BODYHEIGHT=agent.GetBODYHEIGHT();
		cout<<"HIP"<<HIP<<endl;
		cout<<"THIGH"<<THIGH<<endl;
		cout<<"SHANK"<<SHANK<<endl;
		cout<<"BODYHEIGHT"<<BODYHEIGHT<<endl;



    if(firstStep==true)
    {

        if(init==false)
        {

// 		if(footLength<=0.02&&footLength>=0)
// 		{
// 			Lfoot.p(0)=0.02;///*whetherWalkForward;
// 			Rfoot.p(0)=0.02;///*whetherWalkForward;
// 			///////////////////cout<<"**********"<<endl;
// 		}
// 		else if(footLength<=0&&footLength>=-0.02)
// 		{
// 			Lfoot.p(0)=-0.02;///*whetherWalkForward;
// 			Rfoot.p(0)=-0.02;///*whetherWalkForward;
// 			///////////////////cout<<"**********"<<endl;
// 		}
// 		else if(footLength<=0.04&&footLength>=0)
// 		{
// 			Lfoot.p(0)=0.015;///*whetherWalkForward;
// 			Rfoot.p(0)=0.015;///*whetherWalkForward;
// 		}
// 		else if(footLength<=0&&footLength>=-0.04)
// 		{
// 			Lfoot.p(0)=-0.015;///*whetherWalkForward;
// 			Rfoot.p(0)=-0.015;///*whetherWalkForward;
// 		}
// 		else if(footLength<=0.06&&footLength>=0)
// 		{
// 			Lfoot.p(0)=0.01;///*whetherWalkForward;
// 			Rfoot.p(0)=0.01;///*whetherWalkForward;
// 		}
// 		else if(footLength<=0&&footLength>=-0.06)
// 		{
// 			Lfoot.p(0)=-0.01;///*whetherWalkForward;
// 			Rfoot.p(0)=-0.01;///*whetherWalkForward;
// 		}
// 		else if(footLength<=0.09&&footLength>=0)
// 		{
// 			Lfoot.p(0)=0.005;///*whetherWalkForward;
// 			Rfoot.p(0)=0.005;///*whetherWalkForward;
// 		}
// 		else if(footLength<=0&&footLength>=-0.09)
// 		{
// 			Lfoot.p(0)=-0.005;///*whetherWalkForward;
// 			Rfoot.p(0)=-0.005;///*whetherWalkForward;
// 		}
	IK_leg(uLINK[BODY],-HIP,THIGH,SHANK,Rfoot);
	IK_leg(uLINK[BODY],HIP,THIGH,SHANK,Lfoot);
	ForwardKinematics(1);
	ForwardVelocity(1);
	
	  
        com = calcCoM();
        Zc  = com(2);

        Tc  = sqrt(Zc/G);

        cx0 = com(0);
        cy0 = com(1);

	 P1 = calcP(1);
         L1 = calcL(1);

	Dtime = 0.022222222;
	Ty2=0.02*FOOT_CYCLE;
	oldRFoot=Rfoot.p;

	//if(footWidth<0)
	{	
		footLength=0;
		footWidth=0;
	}
	

	nextX=Lfoot.p(0)+footLength;		

	eachFoot=((nextX-oldRFoot[0])/FOOT_CYCLE);

	lastCycleFootLength=footLength;
	lastCycleFootWidth=footWidth;


	horizMoveLength=footWidth/2/FOOT_CYCLE;

	y0=Sy/2-footWidth*1.50;	
	vy0=y0*(cosh(Ty2/Tc)-1)/(Tc*sinh(Ty2/Tc));
	cx0=-0.02;//-0.02
	vx0=0.35; 

	init=true;
        }

    }
    else if(firstStep==false)
    {
        if(init==false)
        {
            init=true;
        }

        if(leftStep==true)
        {

            if(walkCounter==0)
            {
		cx0 = com(0);
		cy0 = com(1);




            	oldRFoot=Lfoot.p;

	 	nextX=Rfoot.p(0)+footLength;
		

		eachFoot=((nextX-oldRFoot[0])/FOOT_CYCLE);

		lastCycleFootLength=footLength;
		lastCycleFootWidth=footWidth;
	
		horizMoveLength=footWidth/2/FOOT_CYCLE;

	
 		y0=-Sy/2-footWidth*1.5;
		
		x0=Rfoot.p(0)-cx0;

		vx0=x0*(cosh(Ty2/Tc)+1)/(Tc*sinh(Ty2/Tc));	

	        vy0=y0*(cosh(Ty2/Tc)-1)/(Tc*sinh(Ty2/Tc));  
		
		
	}

        }
        else if (rightStep==true)
        {

            if(walkCounter==0)
            {
		
		cx0 = com(0);
                cy0 = com(1);

                oldRFoot=Rfoot.p;
		nextX=Lfoot.p(0)+footLength;
	
		eachFoot=((nextX-oldRFoot[0])/FOOT_CYCLE);

		lastCycleFootLength=footLength;
		lastCycleFootWidth=footWidth;
		
		horizMoveLength=footWidth/2/FOOT_CYCLE;

		y0=Sy/2-footWidth*1.5;
		x0=Lfoot.p(0)-cx0;

	        vx0=x0*(cosh(Ty2/Tc)+1)/(Tc*sinh(Ty2/Tc));	

	        vy0=y0*(cosh(Ty2/Tc)-1)/(Tc*sinh(Ty2/Tc));
		
		///////////cout<<"cx0 :"<<cx0<<"	vx0 :"<<vx0<<endl;
	}

        }
    }
}
void NewWalk::updatePV()
{//cout<<"footLenth"<<footLength<<endl;
// cout<<"footwidth"<<footWidth<<endl;
      if(firstStep==true)
    {

    k=walkCounter;

EndTime=0.02*FOOT_CYCLE;

//#ifdef MRLI

//std::pair<float,float> ret1=  LIPMmy2(time[k],Lfoot.p(0),cx0,Tc,0.0,MOVE,EndTime);
//#else
//std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Lfoot.p(0),cx0,Tc,Lfoot.p(0)+0.5*footLength,0.16);
if(footLength>0)
{
std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Lfoot.p(0),cx0,Tc,Lfoot.p(0)+0.51*footLength,0.16);
//	std::pair<float,float>  ret1= LIPMmy4(cx0,vx0,0,0.005,Zc,Lfoot.p(0)+footLength);
 //std::pair<float,float> ret1= LIPMmy(time[k],Lfoot.p(0),cx0,Tc,0.0);
//#endif

#ifdef footp
	std:://///////////////cout<<"firstStep   Lfoot.p(0):"<<Lfoot.p(0)<<std::endl;
#endif
    px=ret1.first;
    vx=ret1.second;
}
else
{
std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Lfoot.p(0),cx0,Tc,Lfoot.p(0)+0.5*footLength,0.16);
//	std::pair<float,float>  ret1= LIPMmy4(cx0,vx0,0,0.005,Zc,Lfoot.p(0)+footLength);
	 //std::pair<float,float> ret1= LIPMmy(time[k],Lfoot.p(0),cx0,Tc,0.0);
	//#endif

	#ifdef footp
		std:://///////////////cout<<"firstStep   Lfoot.p(0):"<<Lfoot.p(0)<<std::endl;
	#endif
	    px=ret1.first;
	    vx=ret1.second;

}
   //std::pair<float,float> ret2= LIPMmy3(k*0.02,Lfoot.p(1),cy0,Tc,cy0-0.5*footWidth,0.16);

std::pair<float,float> ret2= LIPMmy(time[k],Lfoot.p(1),cy0,Tc,vy0);
 //  std::pair<float,float> ret2= LIPMmy3(k*0.02+0.02,Lfoot.p(1),cy0,Tc,cy0-0.0245,0.16);
#ifdef footp
	std:://///////////////cout<<"firstStep   Lfoot.p(1):"<<Lfoot.p(1)<<std::endl;
#endif
	 py=ret2.first;
    vy=ret2.second;


    uLINK[BODY].p(0)=px;uLINK[BODY].p(1)=py;uLINK[BODY].p(2)=BODYHEIGHT;

    uLINK[BODY].v(0)=vx;uLINK[BODY].v(1)=vy;uLINK[BODY].v(2)=0.0;

//Rfoot.p(2)=0.032*sin((k*0.02+0.02)/0.16*180)+0.05;
 	Rfoot.p(2)=FOOTX[k]+0.05;
		     //Rfoot.p(0)=oldRFoot(0);//+eachFoot*k;

 		Rfoot.p(0)=oldRFoot(0)+eachFoot*k;
   //Rfoot.p(1)=Lfoot.p(1)-0.11;
Rfoot.p(1)=uLINK[BODY].p(1)-0.055-horizMoveLength*k;

IK_leg(uLINK[BODY],-HIP,THIGH,SHANK,Rfoot);
IK_leg(uLINK[BODY],HIP,THIGH,SHANK,Lfoot);
ForwardKinematics(1);
#ifdef JointAngleOutput
///////////////////cout<<"left-------------"<<endl<<uLINK[RLEG_J0].q<<endl<<uLINK[RLEG_J1].q<<endl<<uLINK[RLEG_J2].q<<endl<<uLINK[RLEG_J3].q<<endl<<uLINK[RLEG_J4].q<<endl<<uLINK[RLEG_J5].q<<endl<<
   //          uLINK[LLEG_J0].q<<endl<<uLINK[LLEG_J1].q<<endl<<uLINK[LLEG_J2].q<<endl<<uLINK[LLEG_J3].q<<endl<<uLINK[LLEG_J4].q<<endl<<uLINK[LLEG_J5].q<<endl<<"====="<<endl;

/////////////////cout<<"successful??????????????????????????????"<<endl;
/////////////////cout<<"first-------------"<<endl<<uLINK[RLEG_J0].q<<endl<<uLINK[RLEG_J1].q<<endl<<uLINK[RLEG_J2].q<<endl<<uLINK[RLEG_J3].q<<endl<<uLINK[RLEG_J4].q<<endl<<uLINK[RLEG_J5].q<<endl<<
             uLINK[LLEG_J0].q<<endl<<uLINK[LLEG_J1].q<<endl<<uLINK[LLEG_J2].q<<endl<<uLINK[LLEG_J3].q<<endl<<uLINK[LLEG_J4].q<<endl<<uLINK[LLEG_J5].q<<endl<<"====="<<endl;
#endif

  	if(fabs(uLINK[RLEG_J0].q)<0.01)
        uLINK[RLEG_J0].q=0;
    if(fabs(uLINK[RLEG_J1].q)<0.01)
        uLINK[RLEG_J1].q=0;
    if(fabs(uLINK[RLEG_J2].q)<0.01)
        uLINK[RLEG_J2].q=0;
    if(fabs(uLINK[RLEG_J3].q)<0.01)
        uLINK[RLEG_J3].q=0;
    if(fabs(uLINK[RLEG_J4].q)<0.01)
        uLINK[RLEG_J4].q=0;
    if(fabs(uLINK[RLEG_J5].q)<0.01)
        uLINK[RLEG_J5].q=0;
    if(fabs(uLINK[LLEG_J0].q)<0.01)
        uLINK[LLEG_J0].q=0;
    if(fabs(uLINK[LLEG_J1].q)<0.01)
        uLINK[LLEG_J1].q=0;
    if(fabs(uLINK[LLEG_J2].q)<0.01)
        uLINK[LLEG_J2].q=0;
    if(fabs(uLINK[LLEG_J3].q)<0.01)
        uLINK[LLEG_J3].q=0;
    if(fabs(uLINK[LLEG_J4].q)<0.01)
        uLINK[LLEG_J4].q=0;
    if(fabs(uLINK[LLEG_J5].q)<0.01)
        uLINK[LLEG_J5].q=0;

    ForwardVelocity(1);
    com=calcCoM();



    P = calcP(1);

    L = calcL(1);
    dP = (P-P1)/Dtime;
    dL = (L-L1)/Dtime;
    zmp= calcZMP(com,dP,dL,zmpz);

    P1 = P;
    L1 = L;

    com_m.push_back(com);
    zmp_m.first.push_back(zmp.first);
    zmp_m.second.push_back(zmp.second);
#ifdef COM
std:://///////////////cout<<"com:("<<com(0)<<" , "<<com(1)<<")"<<std::endl;
	string name11="COM:(";
		char name22=',';
		char name33=')';
		myCOMLogger.DoLogByFormatting(name11,"%f%c%f%c",com(0),name22,com(1),name33);
#endif
#ifdef ZMP
std:://///////////////cout<<"zmp:("<<zmp.first<<","<<zmp.second<<")"<<std::endl;
		string name1="ZMP:(";
		char name2=',';
		char name3=')';
		myZMPLogger.DoLogByFormatting(name1,"%f%c%f%c",zmp.first,name2,zmp.second,name3);


#endif



    }

    else if(firstStep==false)
    {
        if(leftStep==true)
        {

		EndTime=0.02*FOOT_CYCLE;
		 k=walkCounter;
//#ifdef MRLI
    //		std::pair<float,float> ret1= LIPMmy2(time[k],Rfoot.p(0),cx0,Tc,vx0,MOVE,EndTime);
//#else
//std::pair<float,float> ret1= LIPMmy(time[k],Rfoot.p(0),cx0,Tc,vx0);
		 if(footLength>0 && footLength<0.08)
		 {
std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Rfoot.p(0),cx0,Tc,Rfoot.p(0)+0.51*footLength,0.16);
		//	 std::pair<float,float>  ret1= LIPMmy4(cx0,vx0,ax,0.005,Zc,Rfoot.p(0)+footLength);
	//	 std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Rfoot.p(0),cx0,Tc,Rfoot.p(0)+0.5*footLength,0.16);
//#endif

#ifdef footp
		std:://///////////////cout<<"notfirstStep   Rfoot.p(0):"<<Rfoot.p(0)<<std::endl;
#endif
   		px=ret1.first;
    		vx=ret1.second;
		 }
		 else if(footLength>0.08)
		 {
		 std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Rfoot.p(0),cx0,Tc,Rfoot.p(0)+0.51*footLength,0.16);
	//		 std::pair<float,float>  ret1= LIPMmy4(cx0,vx0,ax,0.005,Zc,Rfoot.p(0)+footLength);
			 	//	 std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Rfoot.p(0),cx0,Tc,Rfoot.p(0)+0.5*footLength,0.16);
			 //#endif

			 #ifdef footp
			 		std:://///////////////cout<<"notfirstStep   Rfoot.p(0):"<<Rfoot.p(0)<<std::endl;
			 #endif
			    		px=ret1.first;
			     		vx=ret1.second;
		 }
		 else
		 {std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Rfoot.p(0),cx0,Tc,Rfoot.p(0)+0.5*footLength,0.16);
		//	 std::pair<float,float>  ret1= LIPMmy4(cx0,vx0,ax,0.005,Zc,Rfoot.p(0)+footLength);
			//	 std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Rfoot.p(0),cx0,Tc,Rfoot.p(0)+0.5*footLength,0.16);
		//#endif

		#ifdef footp
				std:://///////////////cout<<"notfirstStep   Rfoot.p(0):"<<Rfoot.p(0)<<std::endl;
		#endif
		   		px=ret1.first;
		    		vx=ret1.second;

		 }
    //	 std::pair<float,float> ret2= LIPMmy3(k*0.02+0.02,Rfoot.p(1),cy0,Tc,Rfoot.p(1)+0.5*footWidth,0.16);
 	std::pair<float,float> ret2= LIPMmy(time[k],Rfoot.p(1),cy0,Tc,vy0);
    //	std::pair<float,float> ret2= LIPMmy3(k*0.02+0.02,Rfoot.p(1),cy0,Tc,cy0+0.0245,0.16);
#ifdef footp
   		std:://///////////////cout<<"notfirstStep   Rfoot.p(1):"<<Rfoot.p(1)<<std::endl;
#endif
		py=ret2.first;
    		vy=ret2.second;

		 uLINK[BODY].p(0)=px;uLINK[BODY].p(1)=py;uLINK[BODY].p(2)=BODYHEIGHT;

    		uLINK[BODY].v(0)=vx;uLINK[BODY].v(1)=vy;uLINK[BODY].v(2)=0.0;


	Lfoot.p(2)=FOOTX[k]+0.05;
    	//	Lfoot.p(2)=0.032*sin((k*0.02+0.02)/0.16*180)+0.05;
	 if(nowForPass)
	   Lfoot.p(2)=FOOTX[k]+0.05+0.006;
	 if(nowForPass3)
	   Lfoot.p(2)=FOOTX[k]+0.06;

	 Lfoot.p(0)=oldRFoot(0)+eachFoot*k;

   Lfoot.p(1)=uLINK[BODY].p(1)+0.055-horizMoveLength*k;


///	InverseKinematicsAll(RLEG_J5, Rfoot);
///	InverseKinematicsAll(LLEG_J5, Lfoot);
IK_leg(uLINK[BODY],-HIP,THIGH,SHANK,Rfoot);
IK_leg(uLINK[BODY],HIP,THIGH,SHANK,Lfoot);
ForwardKinematics(1);
#ifdef JointAngleOutput
///////////////////cout<<"left-------------"<<endl<<uLINK[RLEG_J0].q<<endl<<uLINK[RLEG_J1].q<<endl<<uLINK[RLEG_J2].q<<endl<<uLINK[RLEG_J3].q<<endl<<uLINK[RLEG_J4].q<<endl<<uLINK[RLEG_J5].q<<endl<<
   //          uLINK[LLEG_J0].q<<endl<<uLINK[LLEG_J1].q<<endl<<uLINK[LLEG_J2].q<<endl<<uLINK[LLEG_J3].q<<endl<<uLINK[LLEG_J4].q<<endl<<uLINK[LLEG_J5].q<<endl<<"====="<<endl;

/////////////////cout<<"successful??????????????????????????????"<<endl;
/////////////////cout<<"left-------------"<<endl<<uLINK[RLEG_J0].q<<endl<<uLINK[RLEG_J1].q<<endl<<uLINK[RLEG_J2].q<<endl<<uLINK[RLEG_J3].q<<endl<<uLINK[RLEG_J4].q<<endl<<uLINK[RLEG_J5].q<<endl<<
             uLINK[LLEG_J0].q<<endl<<uLINK[LLEG_J1].q<<endl<<uLINK[LLEG_J2].q<<endl<<uLINK[LLEG_J3].q<<endl<<uLINK[LLEG_J4].q<<endl<<uLINK[LLEG_J5].q<<endl<<"====="<<endl;
#endif
 //std:://///////////////cout<<"0:"<<std::endl;
    	if(fabs(uLINK[RLEG_J0].q)<0.01)
        uLINK[RLEG_J0].q=0;
    if(fabs(uLINK[RLEG_J1].q)<0.01)
        uLINK[RLEG_J1].q=0;
    if(fabs(uLINK[RLEG_J2].q)<0.01)
        uLINK[RLEG_J2].q=0;
    if(fabs(uLINK[RLEG_J3].q)<0.01)
        uLINK[RLEG_J3].q=0;
    if(fabs(uLINK[RLEG_J4].q)<0.01)
        uLINK[RLEG_J4].q=0;
    if(fabs(uLINK[RLEG_J5].q)<0.01)
        uLINK[RLEG_J5].q=0;
    if(fabs(uLINK[LLEG_J0].q)<0.01)
        uLINK[LLEG_J0].q=0;
    if(fabs(uLINK[LLEG_J1].q)<0.01)
        uLINK[LLEG_J1].q=0;
    if(fabs(uLINK[LLEG_J2].q)<0.01)
        uLINK[LLEG_J2].q=0;
    if(fabs(uLINK[LLEG_J3].q)<0.01)
        uLINK[LLEG_J3].q=0;
    if(fabs(uLINK[LLEG_J4].q)<0.01)
        uLINK[LLEG_J4].q=0;
    if(fabs(uLINK[LLEG_J5].q)<0.01)
        uLINK[LLEG_J5].q=0;


    ForwardVelocity(1);
    com=calcCoM();




    P = calcP(1);

    L = calcL(1);
    dP = (P-P1)/Dtime;
    dL = (L-L1)/Dtime;
    zmp= calcZMP(com,dP,dL,zmpz);

    P1 = P;
    L1 = L;

    com_m.push_back(com);
    zmp_m.first.push_back(zmp.first);
   zmp_m.second.push_back(zmp.second);
#ifdef COM
std:://///////////////cout<<"com:("<<com(0)<<" , "<<com(1)<<")"<<std::endl;
	string name11="COM:(";
		char name22=',';
		char name33=')';
		myCOMLogger.DoLogByFormatting(name11,"%f%c%f%c",com(0),name22,com(1),name33);
#endif
#ifdef ZMP
std:://///////////////cout<<"zmp:("<<zmp.first<<","<<zmp.second<<")"<<std::endl;
std:://///////////////cout<<"zmp:("<<zmp.first<<","<<zmp.second<<")"<<std::endl;
		string name1="ZMP:(";
		char name2=',';
		char name3=')';
		myZMPLogger.DoLogByFormatting(name1,"%f%c%f%c",zmp.first,name2,zmp.second,name3);

#endif


  }
        else if(rightStep==true)
        {

		EndTime=0.2;
		    k=walkCounter;

		//#ifdef MRLI
    //		std::pair<float,float> ret1= LIPMmy2(time[k],Lfoot.p(0),cx0,Tc,vx0,MOVE,EndTime);
//#else
		    if(footLength>0 &&footLength<0.08)
		    {
		    std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Lfoot.p(0),cx0,Tc,Lfoot.p(0)+0.51*footLength,0.16);//0.6
		//    	std::pair<float,float>  ret1= LIPMmy4(cx0,vx0,ax,0.005,Zc,Lfoot.p(0)+footLength);
		    	//std::pair<float,float> ret1= LIPMmy(time[k],Lfoot.p(0),cx0,Tc,vx0);
//#endif
		  //  std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Lfoot.p(0),cx0,Tc,Lfoot.p(0)-0.5*footLength,0.16);
#ifdef footp
		std:://///////////////cout<<"notfirstStep   Lfoot.p(0):"<<Lfoot.p(0)<<std::endl;
#endif
 		px=ret1.first;
    		vx=ret1.second;
		    }
		    else if(footLength>=0.08 )
		    {
		    	std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Lfoot.p(0),cx0,Tc,Lfoot.p(0)+0.51*footLength,0.16);
		    	//std::pair<float,float> ret1= LIPMmy(time[k],Lfoot.p(0),cx0,Tc,vx0);
		   // 	std::pair<float,float>  ret1= LIPMmy4(cx0,vx0,ax,0.005,Zc,Lfoot.p(0)+footLength);
		    	//#endif
		    			  //  std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Lfoot.p(0),cx0,Tc,Lfoot.p(0)-0.5*footLength,0.16);
		    	#ifdef footp
		    			std:://///////////////cout<<"notfirstStep   Lfoot.p(0):"<<Lfoot.p(0)<<std::endl;
		    	#endif
		    	 		px=ret1.first;
		    	    		vx=ret1.second;
		    }
		    else
		    {
		    	std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Lfoot.p(0),cx0,Tc,Lfoot.p(0)+0.5*footLength,0.16);
		    	//std::pair<float,float> ret1= LIPMmy(time[k],Lfoot.p(0),cx0,Tc,vx0);
		    //	std::pair<float,float>  ret1= LIPMmy4(cx0,vx0,ax,0.005,Zc,Lfoot.p(0)+footLength);
		    	//#endif
		    			  //  std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Lfoot.p(0),cx0,Tc,Lfoot.p(0)-0.5*footLength,0.16);
		    	#ifdef footp
		    			std:://///////////////cout<<"notfirstStep   Lfoot.p(0):"<<Lfoot.p(0)<<std::endl;
		    	#endif
		    	 		px=ret1.first;
		    	    		vx=ret1.second;
		    }

 	std::pair<float,float> ret2= LIPMmy(time[k],Lfoot.p(1),cy0,Tc,vy0);
    		//std::pair<float,float> ret2= LIPMmy3(k*0.02+0.02,Lfoot.p(1),cy0,Tc,cy0-0.0245,0.16);
    		// std::pair<float,float> ret2= LIPMmy3(k*0.02+0.02,Lfoot.p(1),cy0,Tc,Lfoot.p(1)-0.5*footWidth,0.16);
#ifdef footp
 		std:://///////////////cout<<"notfirstStep   Lfoot.p(1):"<<Lfoot.p(1)<<std::endl;
#endif
		py=ret2.first;
    		vy=ret2.second;

		 uLINK[BODY].p(0)=px;uLINK[BODY].p(1)=py;uLINK[BODY].p(2)=BODYHEIGHT;

    		uLINK[BODY].v(0)=vx;uLINK[BODY].v(1)=vy;uLINK[BODY].v(2)=0.0;


	Rfoot.p(2)=FOOTX[k]+0.05;
    	//	Rfoot.p(2)=0.032*sin((k*0.02+0.02)/0.16*180)+0.05;
		 if(nowForPass)
	   Rfoot.p(2)=FOOTX[k]+0.05+0.006;
	   	 if(nowForPass3)
	   Rfoot.p(2)=FOOTX[k]+0.06;

		Rfoot.p(0)=oldRFoot(0)+eachFoot*k;

   Rfoot.p(1)=uLINK[BODY].p(1)-0.055-horizMoveLength*k;

IK_leg(uLINK[BODY],-HIP,THIGH,SHANK,Rfoot);
IK_leg(uLINK[BODY],HIP,THIGH,SHANK,Lfoot);

ForwardKinematics(1);
#ifdef JointAngleOutput
///////////////////cout<<"left-------------"<<endl<<uLINK[RLEG_J0].q<<endl<<uLINK[RLEG_J1].q<<endl<<uLINK[RLEG_J2].q<<endl<<uLINK[RLEG_J3].q<<endl<<uLINK[RLEG_J4].q<<endl<<uLINK[RLEG_J5].q<<endl<<
   //          uLINK[LLEG_J0].q<<endl<<uLINK[LLEG_J1].q<<endl<<uLINK[LLEG_J2].q<<endl<<uLINK[LLEG_J3].q<<endl<<uLINK[LLEG_J4].q<<endl<<uLINK[LLEG_J5].q<<endl<<"====="<<endl;

/////////////////cout<<"successful??????????????????????????????"<<endl;
/////////////////cout<<"right-------------"<<endl<<uLINK[RLEG_J0].q<<endl<<uLINK[RLEG_J1].q<<endl<<uLINK[RLEG_J2].q<<endl<<uLINK[RLEG_J3].q<<endl<<uLINK[RLEG_J4].q<<endl<<uLINK[RLEG_J5].q<<endl<<
             uLINK[LLEG_J0].q<<endl<<uLINK[LLEG_J1].q<<endl<<uLINK[LLEG_J2].q<<endl<<uLINK[LLEG_J3].q<<endl<<uLINK[LLEG_J4].q<<endl<<uLINK[LLEG_J5].q<<endl<<"====="<<endl;
#endif
    ForwardVelocity(1);
    com=calcCoM();

///

    P = calcP(1);

    L = calcL(1);
    dP = (P-P1)/Dtime;
    dL = (L-L1)/Dtime;
    zmp= calcZMP(com,dP,dL,zmpz);

    P1 = P;
    L1 = L;

 	com_m.push_back(com);
	zmp_m.first.push_back(zmp.first);
	zmp_m.second.push_back(zmp.second);
#ifdef COM
std:://///////////////cout<<"com:("<<com(0)<<" , "<<com(1)<<")"<<std::endl;
	string name11="COM:(";
		char name22=',';
		char name33=')';
		myCOMLogger.DoLogByFormatting(name11,"%f%c%f%c",com(0),name22,com(1),name33);
#endif
#ifdef ZMP
std:://///////////////cout<<"zmp:("<<zmp.first<<","<<zmp.second<<")"<<std::endl;
		string name1="ZMP:(";
		char name2=',';
		char name3=')';
		myZMPLogger.DoLogByFormatting(name1,"%f%c%f%c",zmp.first,name2,zmp.second,name3);
#endif

///////////////////cout<<wm.GetCurrentGameTime()<<"walkcounter:"<<walkCounter<<endl;

	  }
    }

}

void NewWalk::updateshootPV()
{///cout<<"footLenth"<<footLength<<endl;
///// cout<<"footwidth"<<footWidth<<endl;
	float FOOTH[10];
		FOOTH[0]=0.01;
		FOOTH[1]=0.02;
		FOOTH[2]=0.028;
		FOOTH[3]=0.028;
		FOOTH[4]=0.028;
		FOOTH[5]=0.02;
		FOOTH[6]=0.01;
		FOOTH[7]=0.00;
      if(firstStep==true)
    {

    k=walkCounter;

EndTime=0.02*FOOT_CYCLE;

//#ifdef MRLI

//std::pair<float,float> ret1=  LIPMmy2(time[k],Lfoot.p(0),cx0,Tc,0.0,MOVE,EndTime);
//#else
//std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Lfoot.p(0),cx0,Tc,Lfoot.p(0)+0.5*footLength,0.16);
if(footLength>0)
{
std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Lfoot.p(0),cx0,Tc,Lfoot.p(0)+0.526*footLength,0.16);
 //std::pair<float,float> ret1= LIPMmy(time[k],Lfoot.p(0),cx0,Tc,0.0);
//#endif

#ifdef footp
	std:://///////////////cout<<"firstStep   Lfoot.p(0):"<<Lfoot.p(0)<<std::endl;
#endif
    px=ret1.first;
    vx=ret1.second;
}
else
{
	std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Lfoot.p(0),cx0,Tc,Lfoot.p(0)+0.5*footLength,0.16);
	 //std::pair<float,float> ret1= LIPMmy(time[k],Lfoot.p(0),cx0,Tc,0.0);
	//#endif

	#ifdef footp
		std:://///////////////cout<<"firstStep   Lfoot.p(0):"<<Lfoot.p(0)<<std::endl;
	#endif
	    px=ret1.first;
	    vx=ret1.second;

}
   //std::pair<float,float> ret2= LIPMmy3(k*0.02,Lfoot.p(1),cy0,Tc,cy0-0.5*footWidth,0.16);

std::pair<float,float> ret2= LIPMmy(time[k],Lfoot.p(1),cy0,Tc,vy0);
 //  std::pair<float,float> ret2= LIPMmy3(k*0.02+0.02,Lfoot.p(1),cy0,Tc,cy0-0.0245,0.16);
#ifdef footp
	std:://///////////////cout<<"firstStep   Lfoot.p(1):"<<Lfoot.p(1)<<std::endl;
#endif
	 py=ret2.first;
    vy=ret2.second;


    uLINK[BODY].p(0)=px;uLINK[BODY].p(1)=py;uLINK[BODY].p(2)=BODYHEIGHT;

    uLINK[BODY].v(0)=vx;uLINK[BODY].v(1)=vy;uLINK[BODY].v(2)=0.0;

//	Rfoot.p(2)=FOOTH[k]+0.05;
 	Rfoot.p(2)=FOOTX[k]+0.05;
		     //Rfoot.p(0)=oldRFoot(0);//+eachFoot*k;

 		Rfoot.p(0)=oldRFoot(0)+eachFoot*k;
   //Rfoot.p(1)=Lfoot.p(1)-0.11;
Rfoot.p(1)=uLINK[BODY].p(1)-0.055-horizMoveLength*k;

IK_leg(uLINK[BODY],-HIP,THIGH,SHANK,Rfoot);
IK_leg(uLINK[BODY],HIP,THIGH,SHANK,Lfoot);
ForwardKinematics(1);
#ifdef JointAngleOutput
///////////////////cout<<"left-------------"<<endl<<uLINK[RLEG_J0].q<<endl<<uLINK[RLEG_J1].q<<endl<<uLINK[RLEG_J2].q<<endl<<uLINK[RLEG_J3].q<<endl<<uLINK[RLEG_J4].q<<endl<<uLINK[RLEG_J5].q<<endl<<
   //          uLINK[LLEG_J0].q<<endl<<uLINK[LLEG_J1].q<<endl<<uLINK[LLEG_J2].q<<endl<<uLINK[LLEG_J3].q<<endl<<uLINK[LLEG_J4].q<<endl<<uLINK[LLEG_J5].q<<endl<<"====="<<endl;

/////////////////cout<<"successful??????????????????????????????"<<endl;
/////////////////cout<<"first-------------"<<endl<<uLINK[RLEG_J0].q<<endl<<uLINK[RLEG_J1].q<<endl<<uLINK[RLEG_J2].q<<endl<<uLINK[RLEG_J3].q<<endl<<uLINK[RLEG_J4].q<<endl<<uLINK[RLEG_J5].q<<endl<<
             uLINK[LLEG_J0].q<<endl<<uLINK[LLEG_J1].q<<endl<<uLINK[LLEG_J2].q<<endl<<uLINK[LLEG_J3].q<<endl<<uLINK[LLEG_J4].q<<endl<<uLINK[LLEG_J5].q<<endl<<"====="<<endl;
#endif

  	if(fabs(uLINK[RLEG_J0].q)<0.01)
        uLINK[RLEG_J0].q=0;
    if(fabs(uLINK[RLEG_J1].q)<0.01)
        uLINK[RLEG_J1].q=0;
    if(fabs(uLINK[RLEG_J2].q)<0.01)
        uLINK[RLEG_J2].q=0;
    if(fabs(uLINK[RLEG_J3].q)<0.01)
        uLINK[RLEG_J3].q=0;
    if(fabs(uLINK[RLEG_J4].q)<0.01)
        uLINK[RLEG_J4].q=0;
    if(fabs(uLINK[RLEG_J5].q)<0.01)
        uLINK[RLEG_J5].q=0;
    if(fabs(uLINK[LLEG_J0].q)<0.01)
        uLINK[LLEG_J0].q=0;
    if(fabs(uLINK[LLEG_J1].q)<0.01)
        uLINK[LLEG_J1].q=0;
    if(fabs(uLINK[LLEG_J2].q)<0.01)
        uLINK[LLEG_J2].q=0;
    if(fabs(uLINK[LLEG_J3].q)<0.01)
        uLINK[LLEG_J3].q=0;
    if(fabs(uLINK[LLEG_J4].q)<0.01)
        uLINK[LLEG_J4].q=0;
    if(fabs(uLINK[LLEG_J5].q)<0.01)
        uLINK[LLEG_J5].q=0;

    ForwardVelocity(1);
    com=calcCoM();



    P = calcP(1);

    L = calcL(1);
    dP = (P-P1)/Dtime;
    dL = (L-L1)/Dtime;
    zmp= calcZMP(com,dP,dL,zmpz);

    P1 = P;
    L1 = L;

    com_m.push_back(com);
    zmp_m.first.push_back(zmp.first);
    zmp_m.second.push_back(zmp.second);
#ifdef COM
std:://///////////////cout<<"com:("<<com(0)<<" , "<<com(1)<<")"<<std::endl;
	string name11="COM:(";
		char name22=',';
		char name33=')';
		myCOMLogger.DoLogByFormatting(name11,"%f%c%f%c",com(0),name22,com(1),name33);
#endif
#ifdef ZMP
std:://///////////////cout<<"zmp:("<<zmp.first<<","<<zmp.second<<")"<<std::endl;
		string name1="ZMP:(";
		char name2=',';
		char name3=')';
		myZMPLogger.DoLogByFormatting(name1,"%f%c%f%c",zmp.first,name2,zmp.second,name3);


#endif



    }

    else if(firstStep==false)
    {
        if(leftStep==true)
        {

		EndTime=0.02*FOOT_CYCLE;
		 k=walkCounter;
//#ifdef MRLI
    //		std::pair<float,float> ret1= LIPMmy2(time[k],Rfoot.p(0),cx0,Tc,vx0,MOVE,EndTime);
//#else
//std::pair<float,float> ret1= LIPMmy(time[k],Rfoot.p(0),cx0,Tc,vx0);
		 if(footLength>0 && footLength<0.08)
		 {
std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Rfoot.p(0),cx0,Tc,Rfoot.p(0)+0.60*footLength,0.16);
	//	 std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Rfoot.p(0),cx0,Tc,Rfoot.p(0)+0.5*footLength,0.16);
//#endif

#ifdef footp
		std:://///////////////cout<<"notfirstStep   Rfoot.p(0):"<<Rfoot.p(0)<<std::endl;
#endif
   		px=ret1.first;
    		vx=ret1.second;
		 }
		 else if(footLength>0.08)
		 {
			 std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Rfoot.p(0),cx0,Tc,Rfoot.p(0)+0.522*footLength,0.16);
			 	//	 std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Rfoot.p(0),cx0,Tc,Rfoot.p(0)+0.5*footLength,0.16);
			 //#endif

			 #ifdef footp
			 		std:://///////////////cout<<"notfirstStep   Rfoot.p(0):"<<Rfoot.p(0)<<std::endl;
			 #endif
			    		px=ret1.first;
			     		vx=ret1.second;
		 }
		 else
		 {std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Rfoot.p(0),cx0,Tc,Rfoot.p(0)+0.5*footLength,0.16);
			//	 std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Rfoot.p(0),cx0,Tc,Rfoot.p(0)+0.5*footLength,0.16);
		//#endif

		#ifdef footp
				std:://///////////////cout<<"notfirstStep   Rfoot.p(0):"<<Rfoot.p(0)<<std::endl;
		#endif
		   		px=ret1.first;
		    		vx=ret1.second;

		 }
    //	 std::pair<float,float> ret2= LIPMmy3(k*0.02+0.02,Rfoot.p(1),cy0,Tc,Rfoot.p(1)+0.5*footWidth,0.16);
 	std::pair<float,float> ret2= LIPMmy(time[k],Rfoot.p(1),cy0,Tc,vy0);
    //	std::pair<float,float> ret2= LIPMmy3(k*0.02+0.02,Rfoot.p(1),cy0,Tc,cy0+0.0245,0.16);
#ifdef footp
   		std:://///////////////cout<<"notfirstStep   Rfoot.p(1):"<<Rfoot.p(1)<<std::endl;
#endif
		py=ret2.first;
    		vy=ret2.second;

		 uLINK[BODY].p(0)=px;uLINK[BODY].p(1)=py;uLINK[BODY].p(2)=BODYHEIGHT;

    		uLINK[BODY].v(0)=vx;uLINK[BODY].v(1)=vy;uLINK[BODY].v(2)=0.0;

    	//	 Lfoot.p(2)=FOOTH[k]+0.05;
	 Lfoot.p(2)=FOOTX[k]+0.05;
	 if(nowForPass)
	   Lfoot.p(2)=FOOTX[k]+0.05+0.006;
	 if(nowForPass3)
	   Lfoot.p(2)=FOOTX[k]+0.06;

	 Lfoot.p(0)=oldRFoot(0)+eachFoot*k;

   Lfoot.p(1)=uLINK[BODY].p(1)+0.055-horizMoveLength*k;


///	InverseKinematicsAll(RLEG_J5, Rfoot);
///	InverseKinematicsAll(LLEG_J5, Lfoot);
IK_leg(uLINK[BODY],-HIP,THIGH,SHANK,Rfoot);
IK_leg(uLINK[BODY],HIP,THIGH,SHANK,Lfoot);
ForwardKinematics(1);
#ifdef JointAngleOutput
///////////////////cout<<"left-------------"<<endl<<uLINK[RLEG_J0].q<<endl<<uLINK[RLEG_J1].q<<endl<<uLINK[RLEG_J2].q<<endl<<uLINK[RLEG_J3].q<<endl<<uLINK[RLEG_J4].q<<endl<<uLINK[RLEG_J5].q<<endl<<
   //          uLINK[LLEG_J0].q<<endl<<uLINK[LLEG_J1].q<<endl<<uLINK[LLEG_J2].q<<endl<<uLINK[LLEG_J3].q<<endl<<uLINK[LLEG_J4].q<<endl<<uLINK[LLEG_J5].q<<endl<<"====="<<endl;

/////////////////cout<<"successful??????????????????????????????"<<endl;
/////////////////cout<<"left-------------"<<endl<<uLINK[RLEG_J0].q<<endl<<uLINK[RLEG_J1].q<<endl<<uLINK[RLEG_J2].q<<endl<<uLINK[RLEG_J3].q<<endl<<uLINK[RLEG_J4].q<<endl<<uLINK[RLEG_J5].q<<endl<<
             uLINK[LLEG_J0].q<<endl<<uLINK[LLEG_J1].q<<endl<<uLINK[LLEG_J2].q<<endl<<uLINK[LLEG_J3].q<<endl<<uLINK[LLEG_J4].q<<endl<<uLINK[LLEG_J5].q<<endl<<"====="<<endl;
#endif
 //std:://///////////////cout<<"0:"<<std::endl;
    	if(fabs(uLINK[RLEG_J0].q)<0.01)
        uLINK[RLEG_J0].q=0;
    if(fabs(uLINK[RLEG_J1].q)<0.01)
        uLINK[RLEG_J1].q=0;
    if(fabs(uLINK[RLEG_J2].q)<0.01)
        uLINK[RLEG_J2].q=0;
    if(fabs(uLINK[RLEG_J3].q)<0.01)
        uLINK[RLEG_J3].q=0;
    if(fabs(uLINK[RLEG_J4].q)<0.01)
        uLINK[RLEG_J4].q=0;
    if(fabs(uLINK[RLEG_J5].q)<0.01)
        uLINK[RLEG_J5].q=0;
    if(fabs(uLINK[LLEG_J0].q)<0.01)
        uLINK[LLEG_J0].q=0;
    if(fabs(uLINK[LLEG_J1].q)<0.01)
        uLINK[LLEG_J1].q=0;
    if(fabs(uLINK[LLEG_J2].q)<0.01)
        uLINK[LLEG_J2].q=0;
    if(fabs(uLINK[LLEG_J3].q)<0.01)
        uLINK[LLEG_J3].q=0;
    if(fabs(uLINK[LLEG_J4].q)<0.01)
        uLINK[LLEG_J4].q=0;
    if(fabs(uLINK[LLEG_J5].q)<0.01)
        uLINK[LLEG_J5].q=0;


    ForwardVelocity(1);
    com=calcCoM();




    P = calcP(1);

    L = calcL(1);
    dP = (P-P1)/Dtime;
    dL = (L-L1)/Dtime;
    zmp= calcZMP(com,dP,dL,zmpz);

    P1 = P;
    L1 = L;

    com_m.push_back(com);
    zmp_m.first.push_back(zmp.first);
   zmp_m.second.push_back(zmp.second);
#ifdef COM
std:://///////////////cout<<"com:("<<com(0)<<" , "<<com(1)<<")"<<std::endl;
	string name11="COM:(";
		char name22=',';
		char name33=')';
		myCOMLogger.DoLogByFormatting(name11,"%f%c%f%c",com(0),name22,com(1),name33);
#endif
#ifdef ZMP
std:://///////////////cout<<"zmp:("<<zmp.first<<","<<zmp.second<<")"<<std::endl;
std:://///////////////cout<<"zmp:("<<zmp.first<<","<<zmp.second<<")"<<std::endl;
		string name1="ZMP:(";
		char name2=',';
		char name3=')';
		myZMPLogger.DoLogByFormatting(name1,"%f%c%f%c",zmp.first,name2,zmp.second,name3);

#endif


  }
        else if(rightStep==true)
        {

		EndTime=0.2;
		    k=walkCounter;

		//#ifdef MRLI
    //		std::pair<float,float> ret1= LIPMmy2(time[k],Lfoot.p(0),cx0,Tc,vx0,MOVE,EndTime);
//#else
		    if(footLength>0 &&footLength<0.08)
		    {
		    std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Lfoot.p(0),cx0,Tc,Lfoot.p(0)+0.60*footLength,0.16);
//std::pair<float,float> ret1= LIPMmy(time[k],Lfoot.p(0),cx0,Tc,vx0);
//#endif
		  //  std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Lfoot.p(0),cx0,Tc,Lfoot.p(0)-0.5*footLength,0.16);
#ifdef footp
		std:://///////////////cout<<"notfirstStep   Lfoot.p(0):"<<Lfoot.p(0)<<std::endl;
#endif
 		px=ret1.first;
    		vx=ret1.second;
		    }
		    else if(footLength>=0.08 )
		    {
		    	std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Lfoot.p(0),cx0,Tc,Lfoot.p(0)+0.522*footLength,0.16);
		    	//std::pair<float,float> ret1= LIPMmy(time[k],Lfoot.p(0),cx0,Tc,vx0);
		    	//#endif
		    			  //  std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Lfoot.p(0),cx0,Tc,Lfoot.p(0)-0.5*footLength,0.16);
		    	#ifdef footp
		    			std:://///////////////cout<<"notfirstStep   Lfoot.p(0):"<<Lfoot.p(0)<<std::endl;
		    	#endif
		    	 		px=ret1.first;
		    	    		vx=ret1.second;
		    }
		    else
		    {
		    	std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Lfoot.p(0),cx0,Tc,Lfoot.p(0)+0.5*footLength,0.16);
		    	//std::pair<float,float> ret1= LIPMmy(time[k],Lfoot.p(0),cx0,Tc,vx0);
		    	//#endif
		    			  //  std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Lfoot.p(0),cx0,Tc,Lfoot.p(0)-0.5*footLength,0.16);
		    	#ifdef footp
		    			std:://///////////////cout<<"notfirstStep   Lfoot.p(0):"<<Lfoot.p(0)<<std::endl;
		    	#endif
		    	 		px=ret1.first;
		    	    		vx=ret1.second;
		    }

 	std::pair<float,float> ret2= LIPMmy(time[k],Lfoot.p(1),cy0,Tc,vy0);
    		//std::pair<float,float> ret2= LIPMmy3(k*0.02+0.02,Lfoot.p(1),cy0,Tc,cy0-0.0245,0.16);
    		// std::pair<float,float> ret2= LIPMmy3(k*0.02+0.02,Lfoot.p(1),cy0,Tc,Lfoot.p(1)-0.5*footWidth,0.16);
#ifdef footp
 		std:://///////////////cout<<"notfirstStep   Lfoot.p(1):"<<Lfoot.p(1)<<std::endl;
#endif
		py=ret2.first;
    		vy=ret2.second;

		 uLINK[BODY].p(0)=px;uLINK[BODY].p(1)=py;uLINK[BODY].p(2)=BODYHEIGHT;

    		uLINK[BODY].v(0)=vx;uLINK[BODY].v(1)=vy;uLINK[BODY].v(2)=0.0;

    	//	Rfoot.p(2)=FOOTH[k]+0.05;
	Rfoot.p(2)=FOOTX[k]+0.05;
		 if(nowForPass)
	   Rfoot.p(2)=FOOTX[k]+0.05+0.006;
	   	 if(nowForPass3)
	   Rfoot.p(2)=FOOTX[k]+0.06;

		Rfoot.p(0)=oldRFoot(0)+eachFoot*k;

   Rfoot.p(1)=uLINK[BODY].p(1)-0.055-horizMoveLength*k;

IK_leg(uLINK[BODY],-HIP,THIGH,SHANK,Rfoot);
IK_leg(uLINK[BODY],HIP,THIGH,SHANK,Lfoot);

ForwardKinematics(1);
#ifdef JointAngleOutput
///////////////////cout<<"left-------------"<<endl<<uLINK[RLEG_J0].q<<endl<<uLINK[RLEG_J1].q<<endl<<uLINK[RLEG_J2].q<<endl<<uLINK[RLEG_J3].q<<endl<<uLINK[RLEG_J4].q<<endl<<uLINK[RLEG_J5].q<<endl<<
   //          uLINK[LLEG_J0].q<<endl<<uLINK[LLEG_J1].q<<endl<<uLINK[LLEG_J2].q<<endl<<uLINK[LLEG_J3].q<<endl<<uLINK[LLEG_J4].q<<endl<<uLINK[LLEG_J5].q<<endl<<"====="<<endl;

/////////////////cout<<"successful??????????????????????????????"<<endl;
/////////////////cout<<"right-------------"<<endl<<uLINK[RLEG_J0].q<<endl<<uLINK[RLEG_J1].q<<endl<<uLINK[RLEG_J2].q<<endl<<uLINK[RLEG_J3].q<<endl<<uLINK[RLEG_J4].q<<endl<<uLINK[RLEG_J5].q<<endl<<
             uLINK[LLEG_J0].q<<endl<<uLINK[LLEG_J1].q<<endl<<uLINK[LLEG_J2].q<<endl<<uLINK[LLEG_J3].q<<endl<<uLINK[LLEG_J4].q<<endl<<uLINK[LLEG_J5].q<<endl<<"====="<<endl;
#endif
    ForwardVelocity(1);
    com=calcCoM();

///

    P = calcP(1);

    L = calcL(1);
    dP = (P-P1)/Dtime;
    dL = (L-L1)/Dtime;
    zmp= calcZMP(com,dP,dL,zmpz);

    P1 = P;
    L1 = L;

 	com_m.push_back(com);
	zmp_m.first.push_back(zmp.first);
	zmp_m.second.push_back(zmp.second);
#ifdef COM
std:://///////////////cout<<"com:("<<com(0)<<" , "<<com(1)<<")"<<std::endl;
	string name11="COM:(";
		char name22=',';
		char name33=')';
		myCOMLogger.DoLogByFormatting(name11,"%f%c%f%c",com(0),name22,com(1),name33);
#endif
#ifdef ZMP
std:://///////////////cout<<"zmp:("<<zmp.first<<","<<zmp.second<<")"<<std::endl;
		string name1="ZMP:(";
		char name2=',';
		char name3=')';
		myZMPLogger.DoLogByFormatting(name1,"%f%c%f%c",zmp.first,name2,zmp.second,name3);
#endif

///////////////////cout<<wm.GetCurrentGameTime()<<"walkcounter:"<<walkCounter<<endl;

	  }
    }

}




void NewWalk::updatePBPV1()
{///cout<<"footLenth"<<footLength<<endl;
///// cout<<"footwidth"<<footWidth<<endl;
      if(firstStep==true)
    {

    k=walkCounter;

EndTime=0.02*FOOT_CYCLE;

//#ifdef MRLI

//std::pair<float,float> ret1=  LIPMmy2(time[k],Lfoot.p(0),cx0,Tc,0.0,MOVE,EndTime);
//#else
//std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Lfoot.p(0),cx0,Tc,Lfoot.p(0)+0.5*footLength,0.16);
if(footLength>0)
{
std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Lfoot.p(0),cx0,Tc,Lfoot.p(0)+0.3*footLength,0.16);
 //std::pair<float,float> ret1= LIPMmy(time[k],Lfoot.p(0),cx0,Tc,0.0);
//#endif

#ifdef footp
	std:://///////////////cout<<"firstStep   Lfoot.p(0):"<<Lfoot.p(0)<<std::endl;
#endif
    px=ret1.first;
    vx=ret1.second;
}
else
{
	std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Lfoot.p(0),cx0,Tc,Lfoot.p(0)+0.2*footLength,0.16);
	 //std::pair<float,float> ret1= LIPMmy(time[k],Lfoot.p(0),cx0,Tc,0.0);
	//#endif

	#ifdef footp
		std:://///////////////cout<<"firstStep   Lfoot.p(0):"<<Lfoot.p(0)<<std::endl;
	#endif
	    px=ret1.first;
	    vx=ret1.second;

}
   //std::pair<float,float> ret2= LIPMmy3(k*0.02,Lfoot.p(1),cy0,Tc,cy0-0.5*footWidth,0.16);

std::pair<float,float> ret2= LIPMmy(time[k],Lfoot.p(1),cy0,Tc,vy0);
 //  std::pair<float,float> ret2= LIPMmy3(k*0.02+0.02,Lfoot.p(1),cy0,Tc,cy0-0.0245,0.16);
#ifdef footp
	std:://///////////////cout<<"firstStep   Lfoot.p(1):"<<Lfoot.p(1)<<std::endl;
#endif
	 py=ret2.first;
    vy=ret2.second;


    uLINK[BODY].p(0)=px;uLINK[BODY].p(1)=py;uLINK[BODY].p(2)=BODYHEIGHT;

    uLINK[BODY].v(0)=vx;uLINK[BODY].v(1)=vy;uLINK[BODY].v(2)=0.0;


 	Rfoot.p(2)=FOOTX[k]+0.05;
		     //Rfoot.p(0)=oldRFoot(0);//+eachFoot*k;

 		Rfoot.p(0)=oldRFoot(0)+eachFoot*k;
   //Rfoot.p(1)=Lfoot.p(1)-0.11;
Rfoot.p(1)=uLINK[BODY].p(1)-0.055-horizMoveLength*k;

IK_leg(uLINK[BODY],-HIP,THIGH,SHANK,Rfoot);
IK_leg(uLINK[BODY],HIP,THIGH,SHANK,Lfoot);
ForwardKinematics(1);
#ifdef JointAngleOutput
///////////////////cout<<"left-------------"<<endl<<uLINK[RLEG_J0].q<<endl<<uLINK[RLEG_J1].q<<endl<<uLINK[RLEG_J2].q<<endl<<uLINK[RLEG_J3].q<<endl<<uLINK[RLEG_J4].q<<endl<<uLINK[RLEG_J5].q<<endl<<
   //          uLINK[LLEG_J0].q<<endl<<uLINK[LLEG_J1].q<<endl<<uLINK[LLEG_J2].q<<endl<<uLINK[LLEG_J3].q<<endl<<uLINK[LLEG_J4].q<<endl<<uLINK[LLEG_J5].q<<endl<<"====="<<endl;

/////////////////cout<<"successful??????????????????????????????"<<endl;
/////////////////cout<<"first-------------"<<endl<<uLINK[RLEG_J0].q<<endl<<uLINK[RLEG_J1].q<<endl<<uLINK[RLEG_J2].q<<endl<<uLINK[RLEG_J3].q<<endl<<uLINK[RLEG_J4].q<<endl<<uLINK[RLEG_J5].q<<endl<<
             uLINK[LLEG_J0].q<<endl<<uLINK[LLEG_J1].q<<endl<<uLINK[LLEG_J2].q<<endl<<uLINK[LLEG_J3].q<<endl<<uLINK[LLEG_J4].q<<endl<<uLINK[LLEG_J5].q<<endl<<"====="<<endl;
#endif

  	if(fabs(uLINK[RLEG_J0].q)<0.01)
        uLINK[RLEG_J0].q=0;
    if(fabs(uLINK[RLEG_J1].q)<0.01)
        uLINK[RLEG_J1].q=0;
    if(fabs(uLINK[RLEG_J2].q)<0.01)
        uLINK[RLEG_J2].q=0;
    if(fabs(uLINK[RLEG_J3].q)<0.01)
        uLINK[RLEG_J3].q=0;
    if(fabs(uLINK[RLEG_J4].q)<0.01)
        uLINK[RLEG_J4].q=0;
    if(fabs(uLINK[RLEG_J5].q)<0.01)
        uLINK[RLEG_J5].q=0;
    if(fabs(uLINK[LLEG_J0].q)<0.01)
        uLINK[LLEG_J0].q=0;
    if(fabs(uLINK[LLEG_J1].q)<0.01)
        uLINK[LLEG_J1].q=0;
    if(fabs(uLINK[LLEG_J2].q)<0.01)
        uLINK[LLEG_J2].q=0;
    if(fabs(uLINK[LLEG_J3].q)<0.01)
        uLINK[LLEG_J3].q=0;
    if(fabs(uLINK[LLEG_J4].q)<0.01)
        uLINK[LLEG_J4].q=0;
    if(fabs(uLINK[LLEG_J5].q)<0.01)
        uLINK[LLEG_J5].q=0;

    ForwardVelocity(1);
    com=calcCoM();



    P = calcP(1);

    L = calcL(1);
    dP = (P-P1)/Dtime;
    dL = (L-L1)/Dtime;
    zmp= calcZMP(com,dP,dL,zmpz);

    P1 = P;
    L1 = L;

    com_m.push_back(com);
    zmp_m.first.push_back(zmp.first);
    zmp_m.second.push_back(zmp.second);
#ifdef COM
std:://///////////////cout<<"com:("<<com(0)<<" , "<<com(1)<<")"<<std::endl;
	string name11="COM:(";
		char name22=',';
		char name33=')';
		myCOMLogger.DoLogByFormatting(name11,"%f%c%f%c",com(0),name22,com(1),name33);
#endif
#ifdef ZMP
std:://///////////////cout<<"zmp:("<<zmp.first<<","<<zmp.second<<")"<<std::endl;
		string name1="ZMP:(";
		char name2=',';
		char name3=')';
		myZMPLogger.DoLogByFormatting(name1,"%f%c%f%c",zmp.first,name2,zmp.second,name3);


#endif



    }

    else if(firstStep==false)
    {
        if(leftStep==true)
        {

		EndTime=0.02*FOOT_CYCLE;
		 k=walkCounter;
//#ifdef MRLI
    //		std::pair<float,float> ret1= LIPMmy2(time[k],Rfoot.p(0),cx0,Tc,vx0,MOVE,EndTime);
//#else
//std::pair<float,float> ret1= LIPMmy(time[k],Rfoot.p(0),cx0,Tc,vx0);
		 if(footLength>0 && footLength<0.08)
		 {
std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Rfoot.p(0),cx0,Tc,Rfoot.p(0)+0.25*footLength,0.16);
	//	 std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Rfoot.p(0),cx0,Tc,Rfoot.p(0)+0.5*footLength,0.16);
//#endif

#ifdef footp
		std:://///////////////cout<<"notfirstStep   Rfoot.p(0):"<<Rfoot.p(0)<<std::endl;
#endif
   		px=ret1.first;
    		vx=ret1.second;
		 }
		 else if(footLength>0.08)
		 {
			 std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Rfoot.p(0),cx0,Tc,Rfoot.p(0)+0.25*footLength,0.16);
			 	//	 std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Rfoot.p(0),cx0,Tc,Rfoot.p(0)+0.5*footLength,0.16);
			 //#endif

			 #ifdef footp
			 		std:://///////////////cout<<"notfirstStep   Rfoot.p(0):"<<Rfoot.p(0)<<std::endl;
			 #endif
			    		px=ret1.first;
			     		vx=ret1.second;
		 }
		 else
		 {std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Rfoot.p(0),cx0,Tc,Rfoot.p(0)+0.50*footLength,0.16);
			//	 std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Rfoot.p(0),cx0,Tc,Rfoot.p(0)+0.5*footLength,0.16);
		//#endif

		#ifdef footp
				std:://///////////////cout<<"notfirstStep   Rfoot.p(0):"<<Rfoot.p(0)<<std::endl;
		#endif
		   		px=ret1.first;
		    		vx=ret1.second;

		 }
    //	 std::pair<float,float> ret2= LIPMmy3(k*0.02+0.02,Rfoot.p(1),cy0,Tc,Rfoot.p(1)+0.5*footWidth,0.16);
 	std::pair<float,float> ret2= LIPMmy(time[k],Rfoot.p(1),cy0,Tc,vy0);
    //	std::pair<float,float> ret2= LIPMmy3(k*0.02+0.02,Rfoot.p(1),cy0,Tc,cy0+0.0245,0.16);
#ifdef footp
   		std:://///////////////cout<<"notfirstStep   Rfoot.p(1):"<<Rfoot.p(1)<<std::endl;
#endif
		py=ret2.first;
    		vy=ret2.second;

		 uLINK[BODY].p(0)=px;uLINK[BODY].p(1)=py;uLINK[BODY].p(2)=BODYHEIGHT;

    		uLINK[BODY].v(0)=vx;uLINK[BODY].v(1)=vy;uLINK[BODY].v(2)=0.0;


	 Lfoot.p(2)=FOOTX[k]+0.05;
	 if(nowForPass)
	   Lfoot.p(2)=FOOTX[k]+0.05+0.006;
	 if(nowForPass3)
	   Lfoot.p(2)=FOOTX[k]+0.06;

	 Lfoot.p(0)=oldRFoot(0)+eachFoot*k;

   Lfoot.p(1)=uLINK[BODY].p(1)+0.055-horizMoveLength*k;


///	InverseKinematicsAll(RLEG_J5, Rfoot);
///	InverseKinematicsAll(LLEG_J5, Lfoot);
IK_leg(uLINK[BODY],-HIP,THIGH,SHANK,Rfoot);
IK_leg(uLINK[BODY],HIP,THIGH,SHANK,Lfoot);
ForwardKinematics(1);
#ifdef JointAngleOutput
///////////////////cout<<"left-------------"<<endl<<uLINK[RLEG_J0].q<<endl<<uLINK[RLEG_J1].q<<endl<<uLINK[RLEG_J2].q<<endl<<uLINK[RLEG_J3].q<<endl<<uLINK[RLEG_J4].q<<endl<<uLINK[RLEG_J5].q<<endl<<
   //          uLINK[LLEG_J0].q<<endl<<uLINK[LLEG_J1].q<<endl<<uLINK[LLEG_J2].q<<endl<<uLINK[LLEG_J3].q<<endl<<uLINK[LLEG_J4].q<<endl<<uLINK[LLEG_J5].q<<endl<<"====="<<endl;

/////////////////cout<<"successful??????????????????????????????"<<endl;
/////////////////cout<<"left-------------"<<endl<<uLINK[RLEG_J0].q<<endl<<uLINK[RLEG_J1].q<<endl<<uLINK[RLEG_J2].q<<endl<<uLINK[RLEG_J3].q<<endl<<uLINK[RLEG_J4].q<<endl<<uLINK[RLEG_J5].q<<endl<<
             uLINK[LLEG_J0].q<<endl<<uLINK[LLEG_J1].q<<endl<<uLINK[LLEG_J2].q<<endl<<uLINK[LLEG_J3].q<<endl<<uLINK[LLEG_J4].q<<endl<<uLINK[LLEG_J5].q<<endl<<"====="<<endl;
#endif
 //std:://///////////////cout<<"0:"<<std::endl;
    	if(fabs(uLINK[RLEG_J0].q)<0.01)
        uLINK[RLEG_J0].q=0;
    if(fabs(uLINK[RLEG_J1].q)<0.01)
        uLINK[RLEG_J1].q=0;
    if(fabs(uLINK[RLEG_J2].q)<0.01)
        uLINK[RLEG_J2].q=0;
    if(fabs(uLINK[RLEG_J3].q)<0.01)
        uLINK[RLEG_J3].q=0;
    if(fabs(uLINK[RLEG_J4].q)<0.01)
        uLINK[RLEG_J4].q=0;
    if(fabs(uLINK[RLEG_J5].q)<0.01)
        uLINK[RLEG_J5].q=0;
    if(fabs(uLINK[LLEG_J0].q)<0.01)
        uLINK[LLEG_J0].q=0;
    if(fabs(uLINK[LLEG_J1].q)<0.01)
        uLINK[LLEG_J1].q=0;
    if(fabs(uLINK[LLEG_J2].q)<0.01)
        uLINK[LLEG_J2].q=0;
    if(fabs(uLINK[LLEG_J3].q)<0.01)
        uLINK[LLEG_J3].q=0;
    if(fabs(uLINK[LLEG_J4].q)<0.01)
        uLINK[LLEG_J4].q=0;
    if(fabs(uLINK[LLEG_J5].q)<0.01)
        uLINK[LLEG_J5].q=0;


    ForwardVelocity(1);
    com=calcCoM();




    P = calcP(1);

    L = calcL(1);
    dP = (P-P1)/Dtime;
    dL = (L-L1)/Dtime;
    zmp= calcZMP(com,dP,dL,zmpz);

    P1 = P;
    L1 = L;

    com_m.push_back(com);
    zmp_m.first.push_back(zmp.first);
   zmp_m.second.push_back(zmp.second);
#ifdef COM
std:://///////////////cout<<"com:("<<com(0)<<" , "<<com(1)<<")"<<std::endl;
	string name11="COM:(";
		char name22=',';
		char name33=')';
		myCOMLogger.DoLogByFormatting(name11,"%f%c%f%c",com(0),name22,com(1),name33);
#endif
#ifdef ZMP
std:://///////////////cout<<"zmp:("<<zmp.first<<","<<zmp.second<<")"<<std::endl;
std:://///////////////cout<<"zmp:("<<zmp.first<<","<<zmp.second<<")"<<std::endl;
		string name1="ZMP:(";
		char name2=',';
		char name3=')';
		myZMPLogger.DoLogByFormatting(name1,"%f%c%f%c",zmp.first,name2,zmp.second,name3);

#endif


  }
        else if(rightStep==true)
        {

		EndTime=0.2;
		    k=walkCounter;

		//#ifdef MRLI
    //		std::pair<float,float> ret1= LIPMmy2(time[k],Lfoot.p(0),cx0,Tc,vx0,MOVE,EndTime);
//#else
		    if(footLength>0 &&footLength<0.08)
		    {
		    std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Lfoot.p(0),cx0,Tc,Lfoot.p(0)+0.25*footLength,0.16);
//std::pair<float,float> ret1= LIPMmy(time[k],Lfoot.p(0),cx0,Tc,vx0);
//#endif
		  //  std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Lfoot.p(0),cx0,Tc,Lfoot.p(0)-0.5*footLength,0.16);
#ifdef footp
		std:://///////////////cout<<"notfirstStep   Lfoot.p(0):"<<Lfoot.p(0)<<std::endl;
#endif
 		px=ret1.first;
    		vx=ret1.second;
		    }
		    else if(footLength>=0.08 )
		    {
		    	std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Lfoot.p(0),cx0,Tc,Lfoot.p(0)+0.25*footLength,0.16);
		    	//std::pair<float,float> ret1= LIPMmy(time[k],Lfoot.p(0),cx0,Tc,vx0);
		    	//#endif
		    			  //  std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Lfoot.p(0),cx0,Tc,Lfoot.p(0)-0.5*footLength,0.16);
		    	#ifdef footp
		    			std:://///////////////cout<<"notfirstStep   Lfoot.p(0):"<<Lfoot.p(0)<<std::endl;
		    	#endif
		    	 		px=ret1.first;
		    	    		vx=ret1.second;
		    }
		    else
		    {
		    	std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Lfoot.p(0),cx0,Tc,Lfoot.p(0)+0.50*footLength,0.16);
		    	//std::pair<float,float> ret1= LIPMmy(time[k],Lfoot.p(0),cx0,Tc,vx0);
		    	//#endif
		    			  //  std::pair<float,float> ret1= LIPMmy3(k*0.02+0.02,Lfoot.p(0),cx0,Tc,Lfoot.p(0)-0.5*footLength,0.16);
		    	#ifdef footp
		    			std:://///////////////cout<<"notfirstStep   Lfoot.p(0):"<<Lfoot.p(0)<<std::endl;
		    	#endif
		    	 		px=ret1.first;
		    	    		vx=ret1.second;
		    }

 	std::pair<float,float> ret2= LIPMmy(time[k],Lfoot.p(1),cy0,Tc,vy0);
    		//std::pair<float,float> ret2= LIPMmy3(k*0.02+0.02,Lfoot.p(1),cy0,Tc,cy0-0.0245,0.16);
    		// std::pair<float,float> ret2= LIPMmy3(k*0.02+0.02,Lfoot.p(1),cy0,Tc,Lfoot.p(1)-0.5*footWidth,0.16);
#ifdef footp
 		std:://///////////////cout<<"notfirstStep   Lfoot.p(1):"<<Lfoot.p(1)<<std::endl;
#endif
		py=ret2.first;
    		vy=ret2.second;

		 uLINK[BODY].p(0)=px;uLINK[BODY].p(1)=py;uLINK[BODY].p(2)=BODYHEIGHT;

    		uLINK[BODY].v(0)=vx;uLINK[BODY].v(1)=vy;uLINK[BODY].v(2)=0.0;


	Rfoot.p(2)=FOOTX[k]+0.05;
		 if(nowForPass)
	   Rfoot.p(2)=FOOTX[k]+0.05+0.006;
	   	 if(nowForPass3)
	   Rfoot.p(2)=FOOTX[k]+0.06;

		Rfoot.p(0)=oldRFoot(0)+eachFoot*k;

   Rfoot.p(1)=uLINK[BODY].p(1)-0.055-horizMoveLength*k;

IK_leg(uLINK[BODY],-HIP,THIGH,SHANK,Rfoot);
IK_leg(uLINK[BODY],HIP,THIGH,SHANK,Lfoot);

ForwardKinematics(1);
#ifdef JointAngleOutput
///////////////////cout<<"left-------------"<<endl<<uLINK[RLEG_J0].q<<endl<<uLINK[RLEG_J1].q<<endl<<uLINK[RLEG_J2].q<<endl<<uLINK[RLEG_J3].q<<endl<<uLINK[RLEG_J4].q<<endl<<uLINK[RLEG_J5].q<<endl<<
   //          uLINK[LLEG_J0].q<<endl<<uLINK[LLEG_J1].q<<endl<<uLINK[LLEG_J2].q<<endl<<uLINK[LLEG_J3].q<<endl<<uLINK[LLEG_J4].q<<endl<<uLINK[LLEG_J5].q<<endl<<"====="<<endl;

/////////////////cout<<"successful??????????????????????????????"<<endl;
/////////////////cout<<"right-------------"<<endl<<uLINK[RLEG_J0].q<<endl<<uLINK[RLEG_J1].q<<endl<<uLINK[RLEG_J2].q<<endl<<uLINK[RLEG_J3].q<<endl<<uLINK[RLEG_J4].q<<endl<<uLINK[RLEG_J5].q<<endl<<
             uLINK[LLEG_J0].q<<endl<<uLINK[LLEG_J1].q<<endl<<uLINK[LLEG_J2].q<<endl<<uLINK[LLEG_J3].q<<endl<<uLINK[LLEG_J4].q<<endl<<uLINK[LLEG_J5].q<<endl<<"====="<<endl;
#endif
    ForwardVelocity(1);
    com=calcCoM();

///

    P = calcP(1);

    L = calcL(1);
    dP = (P-P1)/Dtime;
    dL = (L-L1)/Dtime;
    zmp= calcZMP(com,dP,dL,zmpz);

    P1 = P;
    L1 = L;

 	com_m.push_back(com);
	zmp_m.first.push_back(zmp.first);
	zmp_m.second.push_back(zmp.second);
#ifdef COM
std:://///////////////cout<<"com:("<<com(0)<<" , "<<com(1)<<")"<<std::endl;
	string name11="COM:(";
		char name22=',';
		char name33=')';
		myCOMLogger.DoLogByFormatting(name11,"%f%c%f%c",com(0),name22,com(1),name33);
#endif
#ifdef ZMP
std:://///////////////cout<<"zmp:("<<zmp.first<<","<<zmp.second<<")"<<std::endl;
		string name1="ZMP:(";
		char name2=',';
		char name3=')';
		myZMPLogger.DoLogByFormatting(name1,"%f%c%f%c",zmp.first,name2,zmp.second,name3);
#endif

///////////////////cout<<wm.GetCurrentGameTime()<<"walkcounter:"<<walkCounter<<endl;

	  }
    }

}




void NewWalk::updatepbPV()
{
      if(firstStep==true)
    {

    k=walkCounter;

EndTime=0.02*FOOT_CYCLE;
	
//#ifdef MRLI

//std::pair<float,float> ret1=  LIPMmy2(time[k],Lfoot.p(0),cx0,Tc,0.0,MOVE,EndTime);
//#else
 std::pair<float,float> ret1= LIPMmy(time[k],Lfoot.p(0),cx0,Tc,0.0);
//#endif

#ifdef footp
	std:://///////////////cout<<"firstStep   Lfoot.p(0):"<<Lfoot.p(0)<<std::endl;
#endif
    px=ret1.first;
    vx=ret1.second;

    std::pair<float,float> ret2= LIPMmy(time[k],Lfoot.p(1),cy0,Tc,vy0);
#ifdef footp
	std:://///////////////cout<<"firstStep   Lfoot.p(1):"<<Lfoot.p(1)<<std::endl;
#endif
	 py=ret2.first;
    vy=ret2.second;


    uLINK[BODY].p(0)=px+0.01;uLINK[BODY].p(1)=py;uLINK[BODY].p(2)=BODYHEIGHT;

    uLINK[BODY].v(0)=vx;uLINK[BODY].v(1)=vy;uLINK[BODY].v(2)=0.0;


 	Rfoot.p(2)=FOOTX[k]+0.05;
		     //Rfoot.p(0)=oldRFoot(0);//+eachFoot*k;
	
 		Rfoot.p(0)=oldRFoot(0)+eachFoot*k;
   //Rfoot.p(1)=Lfoot.p(1)-0.11;
Rfoot.p(1)=uLINK[BODY].p(1)-0.055-horizMoveLength*k;

IK_leg(uLINK[BODY],-HIP,THIGH,SHANK,Rfoot);
IK_leg(uLINK[BODY],HIP,THIGH,SHANK,Lfoot);
ForwardKinematics(1);
#ifdef JointAngleOutput
///////////////////cout<<"left-------------"<<endl<<uLINK[RLEG_J0].q<<endl<<uLINK[RLEG_J1].q<<endl<<uLINK[RLEG_J2].q<<endl<<uLINK[RLEG_J3].q<<endl<<uLINK[RLEG_J4].q<<endl<<uLINK[RLEG_J5].q<<endl<<
   //          uLINK[LLEG_J0].q<<endl<<uLINK[LLEG_J1].q<<endl<<uLINK[LLEG_J2].q<<endl<<uLINK[LLEG_J3].q<<endl<<uLINK[LLEG_J4].q<<endl<<uLINK[LLEG_J5].q<<endl<<"====="<<endl;

/////////////////cout<<"successful??????????????????????????????"<<endl;
/////////////////cout<<"first-------------"<<endl<<uLINK[RLEG_J0].q<<endl<<uLINK[RLEG_J1].q<<endl<<uLINK[RLEG_J2].q<<endl<<uLINK[RLEG_J3].q<<endl<<uLINK[RLEG_J4].q<<endl<<uLINK[RLEG_J5].q<<endl<<
             uLINK[LLEG_J0].q<<endl<<uLINK[LLEG_J1].q<<endl<<uLINK[LLEG_J2].q<<endl<<uLINK[LLEG_J3].q<<endl<<uLINK[LLEG_J4].q<<endl<<uLINK[LLEG_J5].q<<endl<<"====="<<endl;
#endif
  
  	if(fabs(uLINK[RLEG_J0].q)<0.01)
        uLINK[RLEG_J0].q=0;
    if(fabs(uLINK[RLEG_J1].q)<0.01)
        uLINK[RLEG_J1].q=0;
    if(fabs(uLINK[RLEG_J2].q)<0.01)
        uLINK[RLEG_J2].q=0;
    if(fabs(uLINK[RLEG_J3].q)<0.01)
        uLINK[RLEG_J3].q=0;
    if(fabs(uLINK[RLEG_J4].q)<0.01)
        uLINK[RLEG_J4].q=0;
    if(fabs(uLINK[RLEG_J5].q)<0.01)
        uLINK[RLEG_J5].q=0;
    if(fabs(uLINK[LLEG_J0].q)<0.01)
        uLINK[LLEG_J0].q=0;
    if(fabs(uLINK[LLEG_J1].q)<0.01)
        uLINK[LLEG_J1].q=0;
    if(fabs(uLINK[LLEG_J2].q)<0.01)
        uLINK[LLEG_J2].q=0;
    if(fabs(uLINK[LLEG_J3].q)<0.01)
        uLINK[LLEG_J3].q=0;
    if(fabs(uLINK[LLEG_J4].q)<0.01)
        uLINK[LLEG_J4].q=0;
    if(fabs(uLINK[LLEG_J5].q)<0.01)
        uLINK[LLEG_J5].q=0;

    ForwardVelocity(1);
    com=calcCoM();



    P = calcP(1);

    L = calcL(1);
    dP = (P-P1)/Dtime;
    dL = (L-L1)/Dtime;
    zmp= calcZMP(com,dP,dL,zmpz);

    P1 = P;
    L1 = L;

    com_m.push_back(com);
    zmp_m.first.push_back(zmp.first);
    zmp_m.second.push_back(zmp.second);
#ifdef COM
std:://///////////////cout<<"com:("<<com(0)<<" , "<<com(1)<<")"<<std::endl;
	string name11="COM:(";
		char name22=',';
		char name33=')';
		myCOMLogger.DoLogByFormatting(name11,"%f%c%f%c",com(0),name22,com(1),name33);
#endif
#ifdef ZMP
std:://///////////////cout<<"zmp:("<<zmp.first<<","<<zmp.second<<")"<<std::endl;
		string name1="ZMP:(";
		char name2=',';
		char name3=')';
		myZMPLogger.DoLogByFormatting(name1,"%f%c%f%c",zmp.first,name2,zmp.second,name3);


#endif



    }

    else if(firstStep==false)
    {
        if(leftStep==true)
        {

		EndTime=0.02*FOOT_CYCLE;
		 k=walkCounter;
//#ifdef MRLI
    //		std::pair<float,float> ret1= LIPMmy2(time[k],Rfoot.p(0),cx0,Tc,vx0,MOVE,EndTime);
//#else
 std::pair<float,float> ret1= LIPMmy(time[k],Rfoot.p(0),cx0,Tc,vx0);
//#endif

#ifdef footp
		std:://///////////////cout<<"notfirstStep   Rfoot.p(0):"<<Rfoot.p(0)<<std::endl;
#endif 
   		px=ret1.first;
    		vx=ret1.second;

   	 	std::pair<float,float> ret2= LIPMmy(time[k],Rfoot.p(1),cy0,Tc,vy0);
#ifdef footp 
   		std:://///////////////cout<<"notfirstStep   Rfoot.p(1):"<<Rfoot.p(1)<<std::endl;
#endif
		py=ret2.first;
    		vy=ret2.second;

		 uLINK[BODY].p(0)=px+0.01;uLINK[BODY].p(1)=py;uLINK[BODY].p(2)=BODYHEIGHT;

    		uLINK[BODY].v(0)=vx;uLINK[BODY].v(1)=vy;uLINK[BODY].v(2)=0.0;


	 Lfoot.p(2)=FOOTX[k]+0.05;
	 if(nowForPass)
	   Lfoot.p(2)=FOOTX[k]+0.05+0.006;
	 if(nowForPass3)
	   Lfoot.p(2)=FOOTX[k]+0.06;

	 Lfoot.p(0)=oldRFoot(0)+eachFoot*k;

   Lfoot.p(1)=uLINK[BODY].p(1)+0.055-horizMoveLength*k;


///	InverseKinematicsAll(RLEG_J5, Rfoot);
///	InverseKinematicsAll(LLEG_J5, Lfoot); 
IK_leg(uLINK[BODY],-HIP,THIGH,SHANK,Rfoot);
IK_leg(uLINK[BODY],HIP,THIGH,SHANK,Lfoot);
ForwardKinematics(1);
#ifdef JointAngleOutput
///////////////////cout<<"left-------------"<<endl<<uLINK[RLEG_J0].q<<endl<<uLINK[RLEG_J1].q<<endl<<uLINK[RLEG_J2].q<<endl<<uLINK[RLEG_J3].q<<endl<<uLINK[RLEG_J4].q<<endl<<uLINK[RLEG_J5].q<<endl<<
   //          uLINK[LLEG_J0].q<<endl<<uLINK[LLEG_J1].q<<endl<<uLINK[LLEG_J2].q<<endl<<uLINK[LLEG_J3].q<<endl<<uLINK[LLEG_J4].q<<endl<<uLINK[LLEG_J5].q<<endl<<"====="<<endl;

/////////////////cout<<"successful??????????????????????????????"<<endl;
/////////////////cout<<"left-------------"<<endl<<uLINK[RLEG_J0].q<<endl<<uLINK[RLEG_J1].q<<endl<<uLINK[RLEG_J2].q<<endl<<uLINK[RLEG_J3].q<<endl<<uLINK[RLEG_J4].q<<endl<<uLINK[RLEG_J5].q<<endl<<
             uLINK[LLEG_J0].q<<endl<<uLINK[LLEG_J1].q<<endl<<uLINK[LLEG_J2].q<<endl<<uLINK[LLEG_J3].q<<endl<<uLINK[LLEG_J4].q<<endl<<uLINK[LLEG_J5].q<<endl<<"====="<<endl;
#endif
 //std:://///////////////cout<<"0:"<<std::endl;
    	if(fabs(uLINK[RLEG_J0].q)<0.01)
        uLINK[RLEG_J0].q=0;
    if(fabs(uLINK[RLEG_J1].q)<0.01)
        uLINK[RLEG_J1].q=0;
    if(fabs(uLINK[RLEG_J2].q)<0.01)
        uLINK[RLEG_J2].q=0;
    if(fabs(uLINK[RLEG_J3].q)<0.01)
        uLINK[RLEG_J3].q=0;
    if(fabs(uLINK[RLEG_J4].q)<0.01)
        uLINK[RLEG_J4].q=0;
    if(fabs(uLINK[RLEG_J5].q)<0.01)
        uLINK[RLEG_J5].q=0;
    if(fabs(uLINK[LLEG_J0].q)<0.01)
        uLINK[LLEG_J0].q=0;
    if(fabs(uLINK[LLEG_J1].q)<0.01)
        uLINK[LLEG_J1].q=0;
    if(fabs(uLINK[LLEG_J2].q)<0.01)
        uLINK[LLEG_J2].q=0;
    if(fabs(uLINK[LLEG_J3].q)<0.01)
        uLINK[LLEG_J3].q=0;
    if(fabs(uLINK[LLEG_J4].q)<0.01)
        uLINK[LLEG_J4].q=0;
    if(fabs(uLINK[LLEG_J5].q)<0.01)
        uLINK[LLEG_J5].q=0;


    ForwardVelocity(1);
    com=calcCoM();




    P = calcP(1);

    L = calcL(1);
    dP = (P-P1)/Dtime;
    dL = (L-L1)/Dtime;
    zmp= calcZMP(com,dP,dL,zmpz);

    P1 = P;
    L1 = L;

    com_m.push_back(com);
    zmp_m.first.push_back(zmp.first);
   zmp_m.second.push_back(zmp.second);
#ifdef COM
std:://///////////////cout<<"com:("<<com(0)<<" , "<<com(1)<<")"<<std::endl;
	string name11="COM:(";
		char name22=',';
		char name33=')';
		myCOMLogger.DoLogByFormatting(name11,"%f%c%f%c",com(0),name22,com(1),name33);
#endif
#ifdef ZMP
std:://///////////////cout<<"zmp:("<<zmp.first<<","<<zmp.second<<")"<<std::endl;
std:://///////////////cout<<"zmp:("<<zmp.first<<","<<zmp.second<<")"<<std::endl;
		string name1="ZMP:(";
		char name2=',';
		char name3=')';
		myZMPLogger.DoLogByFormatting(name1,"%f%c%f%c",zmp.first,name2,zmp.second,name3);

#endif


  }
        else if(rightStep==true)
        {

		EndTime=0.2;
		    k=walkCounter;

		//#ifdef MRLI
    //		std::pair<float,float> ret1= LIPMmy2(time[k],Lfoot.p(0),cx0,Tc,vx0,MOVE,EndTime);
//#else
std::pair<float,float> ret1= LIPMmy(time[k],Lfoot.p(0),cx0,Tc,vx0);
//#endif

#ifdef footp
		std:://///////////////cout<<"notfirstStep   Lfoot.p(0):"<<Lfoot.p(0)<<std::endl;
#endif   
 		px=ret1.first;
    		vx=ret1.second;

   	 	std::pair<float,float> ret2= LIPMmy(time[k],Lfoot.p(1),cy0,Tc,vy0);
#ifdef footp   
 		std:://///////////////cout<<"notfirstStep   Lfoot.p(1):"<<Lfoot.p(1)<<std::endl;
#endif
		py=ret2.first;
    		vy=ret2.second;

		 uLINK[BODY].p(0)=px+0.01;uLINK[BODY].p(1)=py;uLINK[BODY].p(2)=BODYHEIGHT;

    		uLINK[BODY].v(0)=vx;uLINK[BODY].v(1)=vy;uLINK[BODY].v(2)=0.0;
 

	Rfoot.p(2)=FOOTX[k]+0.05;	
		 if(nowForPass)
	   Rfoot.p(2)=FOOTX[k]+0.05+0.006;
	   	 if(nowForPass3)
	   Rfoot.p(2)=FOOTX[k]+0.06;

		Rfoot.p(0)=oldRFoot(0)+eachFoot*k;
	
   Rfoot.p(1)=uLINK[BODY].p(1)-0.055-horizMoveLength*k;

IK_leg(uLINK[BODY],-HIP,THIGH,SHANK,Rfoot);
IK_leg(uLINK[BODY],HIP,THIGH,SHANK,Lfoot);

ForwardKinematics(1);
#ifdef JointAngleOutput
///////////////////cout<<"left-------------"<<endl<<uLINK[RLEG_J0].q<<endl<<uLINK[RLEG_J1].q<<endl<<uLINK[RLEG_J2].q<<endl<<uLINK[RLEG_J3].q<<endl<<uLINK[RLEG_J4].q<<endl<<uLINK[RLEG_J5].q<<endl<<
   //          uLINK[LLEG_J0].q<<endl<<uLINK[LLEG_J1].q<<endl<<uLINK[LLEG_J2].q<<endl<<uLINK[LLEG_J3].q<<endl<<uLINK[LLEG_J4].q<<endl<<uLINK[LLEG_J5].q<<endl<<"====="<<endl;

/////////////////cout<<"successful??????????????????????????????"<<endl;
/////////////////cout<<"right-------------"<<endl<<uLINK[RLEG_J0].q<<endl<<uLINK[RLEG_J1].q<<endl<<uLINK[RLEG_J2].q<<endl<<uLINK[RLEG_J3].q<<endl<<uLINK[RLEG_J4].q<<endl<<uLINK[RLEG_J5].q<<endl<<
             uLINK[LLEG_J0].q<<endl<<uLINK[LLEG_J1].q<<endl<<uLINK[LLEG_J2].q<<endl<<uLINK[LLEG_J3].q<<endl<<uLINK[LLEG_J4].q<<endl<<uLINK[LLEG_J5].q<<endl<<"====="<<endl;
#endif
    ForwardVelocity(1);
    com=calcCoM();

///

    P = calcP(1);

    L = calcL(1);
    dP = (P-P1)/Dtime;
    dL = (L-L1)/Dtime;
    zmp= calcZMP(com,dP,dL,zmpz);

    P1 = P;
    L1 = L;

 	com_m.push_back(com);
	zmp_m.first.push_back(zmp.first);
	zmp_m.second.push_back(zmp.second);
#ifdef COM
std:://///////////////cout<<"com:("<<com(0)<<" , "<<com(1)<<")"<<std::endl;
	string name11="COM:(";
		char name22=',';
		char name33=')';
		myCOMLogger.DoLogByFormatting(name11,"%f%c%f%c",com(0),name22,com(1),name33);
#endif
#ifdef ZMP
std:://///////////////cout<<"zmp:("<<zmp.first<<","<<zmp.second<<")"<<std::endl;
		string name1="ZMP:(";
		char name2=',';
		char name3=')';
		myZMPLogger.DoLogByFormatting(name1,"%f%c%f%c",zmp.first,name2,zmp.second,name3);
#endif

///////////////////cout<<wm.GetCurrentGameTime()<<"walkcounter:"<<walkCounter<<endl;
		
	  }
    }
  
}

std::string NewWalk::readNewWalkData()
{

/*	if(footWidth>=0.11)
	{
		footWidth=0.11;
	}
	else if(footWidth<=-0.11)
		 footWidth=-0.11;
    */

//	///////////////cout<<"body angle :"<<bodyForerakeAngle<<"			leg Forerake Angle ="<<legForerakeAngle<<endl;
updateLastCyclesAverageTurnHeadAngle();
updateLastCyclesAverageVerticalTurnHeadAngle();
//	bodyForerakeAngle=0;
//std:://///////////////cout<<"call the readNewWalkData"<<std::endl<<std::endl;
std::string ss,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,srarm1,slarm1,srarm2,slarm2,srarm3,slarm3,srarm4,slarm4;

int CYCLE=50;
    /*
        {0,0}, {-105,0}, {-5,0}, {90,0}, {45,0}, {0,0}, {0,0}, {28.55,0}, {-90.32,0}, {61.77,0}, {-0,0},
		{-35,0}, {-105,0}, {5,0}, {-90,0}, {-45,0}, {0,0}, {0,0}, {28.55,0}, {-90.32,0}, {61.77,0}, {-0,0}
    */
	float angHead1,angHead2;
	float angLleg1,angLleg2,angLleg3,angLleg4,angLleg5,angLleg6;
	float angRleg1,angRleg2,angRleg3,angRleg4,angRleg5,angRleg6;
	float angLarm1,angLarm2,angLarm3,angLarm4;
	float angRarm1,angRarm2,angRarm3,angRarm4;
	//if(sendCount==2)
	//{
	receiveJointInfo();
	//}
	//cout<<"firstReadDate::"<<firstReadDate<<endl;
	if(firstReadDate==true)
	{
		//cout<<"firstReadDate==true"<<endl;
		angHead1 = messageParser.mHingeJointSenseMap[JID_HEAD_1].angle*PI_180;
		//cout<<"angHead1::"<<angHead1<<endl;
		angHead2 = messageParser.mHingeJointSenseMap[JID_HEAD_2].angle*PI_180;
		//cout<<"angHead2::"<<angHead2<<endl;
		angLleg1 = messageParser.mHingeJointSenseMap[JID_LLEG_1].angle*PI_180;
		//cout<<"angLleg1::"<<angLleg1<<endl;
		angLleg2 = messageParser.mHingeJointSenseMap[JID_LLEG_2].angle*PI_180;
		//cout<<"angLleg2::"<<angLleg2<<endl;
		angLleg3 = messageParser.mHingeJointSenseMap[JID_LLEG_3].angle*PI_180;
		//cout<<"angLleg3::"<<angLleg3<<endl;
		angLleg4 = messageParser.mHingeJointSenseMap[JID_LLEG_4].angle*PI_180;
		//cout<<"angLleg4::"<<angLleg4<<endl;
		angLleg5 = messageParser.mHingeJointSenseMap[JID_LLEG_5].angle*PI_180;
		//cout<<"angLleg5::"<<angLleg5<<endl;
		angLleg6 = messageParser.mHingeJointSenseMap[JID_LLEG_6].angle*PI_180;
		//cout<<"angLleg6::"<<angLleg6<<endl;
		
		angRleg1 = messageParser.mHingeJointSenseMap[JID_RLEG_1].angle*PI_180;
		//cout<<"angRleg1::"<<angRleg1<<endl;
		angRleg2 = messageParser.mHingeJointSenseMap[JID_RLEG_2].angle*PI_180;
		//cout<<"angRleg2::"<<angRleg2<<endl;
		angRleg3 = messageParser.mHingeJointSenseMap[JID_RLEG_3].angle*PI_180;
		//cout<<"angRleg3::"<<angRleg3<<endl;
		angRleg4 = messageParser.mHingeJointSenseMap[JID_RLEG_4].angle*PI_180;
		//cout<<"angRleg4::"<<angRleg4<<endl;
		angRleg5 = messageParser.mHingeJointSenseMap[JID_RLEG_5].angle*PI_180;
		//cout<<"angRleg5::"<<angRleg5<<endl;
		angRleg6 = messageParser.mHingeJointSenseMap[JID_RLEG_6].angle*PI_180;
		//cout<<"angRleg6::"<<angRleg6<<endl;
		angLarm1 = messageParser.mHingeJointSenseMap[JID_LARM_1].angle*PI_180;
		//cout<<"angLarm1::"<<angLarm1<<endl;
		angLarm2 = messageParser.mHingeJointSenseMap[JID_LARM_2].angle*PI_180;
		//cout<<"angLarm2::"<<angLarm2<<endl;
		angLarm3 = messageParser.mHingeJointSenseMap[JID_LARM_3].angle*PI_180;
		//cout<<"angLarm3::"<<angLarm3<<endl;
		angLarm4 = messageParser.mHingeJointSenseMap[JID_LARM_4].angle*PI_180;
		//cout<<"angLarm4::"<<angLarm4<<endl;
		angRarm1 = messageParser.mHingeJointSenseMap[JID_RARM_1].angle*PI_180;
		//cout<<"angRarm1::"<<angRarm1<<endl;
		angRarm2 = messageParser.mHingeJointSenseMap[JID_RARM_2].angle*PI_180;
		//cout<<"angRarm2::"<<angRarm2<<endl;
		angRarm3 = messageParser.mHingeJointSenseMap[JID_RARM_3].angle*PI_180;
		//cout<<"angRarm3::"<<angRarm3<<endl;
		angRarm4 = messageParser.mHingeJointSenseMap[JID_RARM_4].angle*PI_180;
		//cout<<"angRarm4::"<<angRarm4<<endl;
		firstReadDate=false;
	}
	else
	{
		//cout<<"firstReadDate==false"<<endl;
		angHead1 = Forecast_mHingeJointSenseMap[JID_HEAD_1].angle;
		angHead2 = Forecast_mHingeJointSenseMap[JID_HEAD_2].angle;
	
		angLleg1 = Forecast_mHingeJointSenseMap[JID_LLEG_1].angle;
		angLleg2 = Forecast_mHingeJointSenseMap[JID_LLEG_2].angle;
		angLleg3 = Forecast_mHingeJointSenseMap[JID_LLEG_3].angle;
		angLleg4 = Forecast_mHingeJointSenseMap[JID_LLEG_4].angle;
		angLleg5 = Forecast_mHingeJointSenseMap[JID_LLEG_5].angle;
		angLleg6 = Forecast_mHingeJointSenseMap[JID_LLEG_6].angle;
	
		angRleg1 = Forecast_mHingeJointSenseMap[JID_RLEG_1].angle;
		angRleg2 = Forecast_mHingeJointSenseMap[JID_RLEG_2].angle;
		angRleg3 = Forecast_mHingeJointSenseMap[JID_RLEG_3].angle;
		angRleg4 = Forecast_mHingeJointSenseMap[JID_RLEG_4].angle;
		angRleg5 = Forecast_mHingeJointSenseMap[JID_RLEG_5].angle;
		angRleg6 = Forecast_mHingeJointSenseMap[JID_RLEG_6].angle;
	
		angLarm1 = Forecast_mHingeJointSenseMap[JID_LARM_1].angle;
		angLarm2 = Forecast_mHingeJointSenseMap[JID_LARM_2].angle;
		angLarm3 = Forecast_mHingeJointSenseMap[JID_LARM_3].angle;
		angLarm4 = Forecast_mHingeJointSenseMap[JID_LARM_4].angle;
	
		angRarm1 = Forecast_mHingeJointSenseMap[JID_RARM_1].angle;
		angRarm2 = Forecast_mHingeJointSenseMap[JID_RARM_2].angle;
		angRarm3 = Forecast_mHingeJointSenseMap[JID_RARM_3].angle;
		angRarm4 = Forecast_mHingeJointSenseMap[JID_RARM_4].angle;
	}
	//cout<<"sendCount::"<<sendCount<<endl;
 	if(sendCount==2)
 	{
 		//cout<<"sendCount==2"<<endl;
		Delay_mHingeJointSenseMap[JID_HEAD_1].angle = Received_mHingeJointSenseMap[JID_HEAD_1].angle-Sended_mHingeJointSenseMap2[JID_HEAD_1].angle;
		Delay_mHingeJointSenseMap[JID_HEAD_2].angle = Received_mHingeJointSenseMap[JID_HEAD_2].angle-Sended_mHingeJointSenseMap2[JID_HEAD_2].angle;

		Delay_mHingeJointSenseMap[JID_LARM_1].angle = Received_mHingeJointSenseMap[JID_LARM_1].angle-Sended_mHingeJointSenseMap2[JID_LARM_1].angle;
		Delay_mHingeJointSenseMap[JID_LARM_2].angle = Received_mHingeJointSenseMap[JID_LARM_2].angle-Sended_mHingeJointSenseMap2[JID_LARM_2].angle;
		Delay_mHingeJointSenseMap[JID_LARM_3].angle = Received_mHingeJointSenseMap[JID_LARM_3].angle-Sended_mHingeJointSenseMap2[JID_LARM_3].angle;
		Delay_mHingeJointSenseMap[JID_LARM_4].angle = Received_mHingeJointSenseMap[JID_LARM_4].angle-Sended_mHingeJointSenseMap2[JID_LARM_4].angle;

		Delay_mHingeJointSenseMap[JID_RARM_1].angle = Received_mHingeJointSenseMap[JID_RARM_1].angle-Sended_mHingeJointSenseMap2[JID_RARM_1].angle;
		Delay_mHingeJointSenseMap[JID_RARM_2].angle = Received_mHingeJointSenseMap[JID_RARM_2].angle-Sended_mHingeJointSenseMap2[JID_RARM_2].angle;
		Delay_mHingeJointSenseMap[JID_RARM_3].angle = Received_mHingeJointSenseMap[JID_RARM_3].angle-Sended_mHingeJointSenseMap2[JID_RARM_3].angle;
		Delay_mHingeJointSenseMap[JID_RARM_4].angle = Received_mHingeJointSenseMap[JID_RARM_4].angle-Sended_mHingeJointSenseMap2[JID_RARM_4].angle;

		Delay_mHingeJointSenseMap[JID_LLEG_1].angle = Received_mHingeJointSenseMap[JID_LLEG_1].angle-Sended_mHingeJointSenseMap2[JID_LLEG_1].angle;
		Delay_mHingeJointSenseMap[JID_LLEG_2].angle = Received_mHingeJointSenseMap[JID_LLEG_2].angle-Sended_mHingeJointSenseMap2[JID_LLEG_2].angle;
		Delay_mHingeJointSenseMap[JID_LLEG_3].angle = Received_mHingeJointSenseMap[JID_LLEG_3].angle-Sended_mHingeJointSenseMap2[JID_LLEG_3].angle;
		Delay_mHingeJointSenseMap[JID_LLEG_4].angle = Received_mHingeJointSenseMap[JID_LLEG_4].angle-Sended_mHingeJointSenseMap2[JID_LLEG_4].angle;
		Delay_mHingeJointSenseMap[JID_LLEG_5].angle = Received_mHingeJointSenseMap[JID_LLEG_5].angle-Sended_mHingeJointSenseMap2[JID_LLEG_5].angle;
		Delay_mHingeJointSenseMap[JID_LLEG_6].angle = Received_mHingeJointSenseMap[JID_LLEG_6].angle-Sended_mHingeJointSenseMap2[JID_LLEG_6].angle;

		Delay_mHingeJointSenseMap[JID_RLEG_1].angle = Received_mHingeJointSenseMap[JID_RLEG_1].angle-Sended_mHingeJointSenseMap2[JID_RLEG_1].angle;
		Delay_mHingeJointSenseMap[JID_RLEG_2].angle = Received_mHingeJointSenseMap[JID_RLEG_2].angle-Sended_mHingeJointSenseMap2[JID_RLEG_2].angle;
		Delay_mHingeJointSenseMap[JID_RLEG_3].angle = Received_mHingeJointSenseMap[JID_RLEG_3].angle-Sended_mHingeJointSenseMap2[JID_RLEG_3].angle;
		Delay_mHingeJointSenseMap[JID_RLEG_4].angle = Received_mHingeJointSenseMap[JID_RLEG_4].angle-Sended_mHingeJointSenseMap2[JID_RLEG_4].angle;
		Delay_mHingeJointSenseMap[JID_RLEG_5].angle = Received_mHingeJointSenseMap[JID_RLEG_5].angle-Sended_mHingeJointSenseMap2[JID_RLEG_5].angle;
		Delay_mHingeJointSenseMap[JID_RLEG_6].angle = Received_mHingeJointSenseMap[JID_RLEG_6].angle-Sended_mHingeJointSenseMap2[JID_RLEG_6].angle;
		sendCount=0;
 	}
 	else
 		{
 		Delay_mHingeJointSenseMap.clear();
 		}
 	//cout<<"turnLeftAngle::"<<turnLeftAngle<<endl;
//cout<<"time :"<<wm.GetCurrentGameTime()<<"counter  :"<<walkCounter<<endl;
	sendAngle.Head1.Aimangle=turnHeadAngle*PI_180-angHead1-Delay_mHingeJointSenseMap[JID_HEAD_1].angle;
	sendAngle.Head2.Aimangle=-42*PI_180-angHead2-Delay_mHingeJointSenseMap[JID_HEAD_2].angle ;

	sendAngle.Larm1.Aimangle=-(90-swingLeftAngle)*PI_180-angLarm1-Delay_mHingeJointSenseMap[JID_LARM_1].angle;
	sendAngle.Larm2.Aimangle=(swingLeftAngle2)*PI_180-angLarm2-Delay_mHingeJointSenseMap[JID_LARM_2].angle;
	sendAngle.Larm3.Aimangle=-90*PI_180-angLarm3-Delay_mHingeJointSenseMap[JID_LARM_3].angle;
	sendAngle.Larm4.Aimangle=-(30+swingLeftAngle*0.75)*PI_180-angLarm4-Delay_mHingeJointSenseMap[JID_LARM_4].angle;

	sendAngle.Rarm1.Aimangle=(-90+swingRightAngle)*PI_180-angRarm1-Delay_mHingeJointSenseMap[JID_RARM_1].angle ;
	sendAngle.Rarm2.Aimangle=(swingRightAngle2)*PI_180-angRarm2-Delay_mHingeJointSenseMap[JID_RARM_2].angle;
	sendAngle.Rarm3.Aimangle=90*PI_180-angRarm3-Delay_mHingeJointSenseMap[JID_RARM_3].angle;
	sendAngle.Rarm4.Aimangle=(30+swingRightAngle*0.75)*PI_180-angRarm4-Delay_mHingeJointSenseMap[JID_RARM_4].angle;
//std:://///////////////cout<<"Delay_mHingeJointSenseMap[JID_RLEG_2].angle: "<<Delay_mHingeJointSenseMap[JID_RLEG_2].angle<<std::endl;
	/////////////////cout<<"bodyForerakeAngle:"<<bodyForerakeAngle<<endl;
	sendAngle.Lleg1.Aimangle=turnLeftAngle-angLleg1-Delay_mHingeJointSenseMap[JID_LLEG_1].angle ;
	sendAngle.Lleg2.Aimangle=uLINK[LLEG_J1].q-angLleg2-Delay_mHingeJointSenseMap[JID_LLEG_2].angle+horizonForerakeAngle;
	sendAngle.Lleg3.Aimangle=-uLINK[LLEG_J2].q+bodyForerakeAngle-angLleg3-Delay_mHingeJointSenseMap[JID_LLEG_3].angle ;
	sendAngle.Lleg4.Aimangle=-uLINK[LLEG_J3].q-angLleg4-Delay_mHingeJointSenseMap[JID_LLEG_4].angle ;
	sendAngle.Lleg5.Aimangle=-uLINK[LLEG_J4].q-angLleg5-Delay_mHingeJointSenseMap[JID_LLEG_5].angle+legForerakeAngle;
	sendAngle.Lleg6.Aimangle=uLINK[LLEG_J5].q-angLleg6-Delay_mHingeJointSenseMap[JID_LLEG_6].angle ;

	sendAngle.Rleg1.Aimangle=turnRightAngle-angRleg1-Delay_mHingeJointSenseMap[JID_RLEG_1].angle ;
	sendAngle.Rleg2.Aimangle=uLINK[RLEG_J1].q-angRleg2-Delay_mHingeJointSenseMap[JID_RLEG_2].angle+horizonForerakeAngle;
	sendAngle.Rleg3.Aimangle=-uLINK[RLEG_J2].q+bodyForerakeAngle-angRleg3-Delay_mHingeJointSenseMap[JID_RLEG_3].angle ;
	sendAngle.Rleg4.Aimangle=-uLINK[RLEG_J3].q-angRleg4-Delay_mHingeJointSenseMap[JID_RLEG_4].angle ;
	sendAngle.Rleg5.Aimangle=-uLINK[RLEG_J4].q-angRleg5-Delay_mHingeJointSenseMap[JID_RLEG_5].angle+legForerakeAngle;
	sendAngle.Rleg6.Aimangle=uLINK[RLEG_J5].q-angRleg6-Delay_mHingeJointSenseMap[JID_RLEG_6].angle ;

//cout<<"turnLeftAngle:  "<<turnLeftAngle<<endl;
//cout<<"turnRightAngle:  "<<turnRightAngle<<endl;
//	Forecast_mHingeJointSenseMap[JID_HEAD_1].angle=0;
	//Forecast_mHingeJointSenseMap[JID_HEAD_2].angle-35*PI/180;
	
	Forecast_mHingeJointSenseMap[JID_LLEG_1].angle=turnLeftAngle;
	Forecast_mHingeJointSenseMap[JID_LLEG_2].angle=uLINK[LLEG_J1].q+horizonForerakeAngle;
	Forecast_mHingeJointSenseMap[JID_LLEG_3].angle=-uLINK[LLEG_J2].q+bodyForerakeAngle;
	Forecast_mHingeJointSenseMap[JID_LLEG_4].angle=-uLINK[LLEG_J3].q;
	Forecast_mHingeJointSenseMap[JID_LLEG_5].angle=-uLINK[LLEG_J4].q+legForerakeAngle;
	Forecast_mHingeJointSenseMap[JID_LLEG_6].angle=uLINK[LLEG_J5].q;
	
	Forecast_mHingeJointSenseMap[JID_RLEG_1].angle=turnRightAngle;
	Forecast_mHingeJointSenseMap[JID_RLEG_2].angle=uLINK[RLEG_J1].q+horizonForerakeAngle;
	Forecast_mHingeJointSenseMap[JID_RLEG_3].angle=-uLINK[RLEG_J2].q+bodyForerakeAngle;
	Forecast_mHingeJointSenseMap[JID_RLEG_4].angle=-uLINK[RLEG_J3].q;
	Forecast_mHingeJointSenseMap[JID_RLEG_5].angle=-uLINK[RLEG_J4].q+legForerakeAngle;
	Forecast_mHingeJointSenseMap[JID_RLEG_6].angle=uLINK[RLEG_J5].q;

	Forecast_mHingeJointSenseMap[JID_HEAD_1].angle=turnHeadAngle*PI_180;
	Forecast_mHingeJointSenseMap[JID_HEAD_2].angle=-42*PI_180;

	Forecast_mHingeJointSenseMap[JID_LARM_1].angle=-(90-swingLeftAngle)*PI_180;
	Forecast_mHingeJointSenseMap[JID_LARM_2].angle=(swingLeftAngle2)*PI_180;
	Forecast_mHingeJointSenseMap[JID_LARM_3].angle=-90*PI_180;
	Forecast_mHingeJointSenseMap[JID_LARM_4].angle=-(30+swingLeftAngle*0.75)*PI_180;
	
	Forecast_mHingeJointSenseMap[JID_RARM_1].angle=(-90+swingRightAngle)*PI_180;
	Forecast_mHingeJointSenseMap[JID_RARM_2].angle=(swingRightAngle2)*PI_180;
	Forecast_mHingeJointSenseMap[JID_RARM_3].angle=90*PI_180;
	Forecast_mHingeJointSenseMap[JID_RARM_4].angle=(30+swingRightAngle*0.75)*PI_180;
 	sendCount++;///////////////////////////
	
//	if(messageParser.abnormalServerCycle==true)
//	{
//		Sended_mHingeJointSenseMap2=Sended_mHingeJointSenseMap1;
//		Sended_mHingeJointSenseMap1=Sended_mHingeJointSenseMap;
//		Sended_mHingeJointSenseMap=Forecast_mHingeJointSenseMap;
//	}
//	else
	{
		Sended_mHingeJointSenseMap2=Sended_mHingeJointSenseMap;
		Sended_mHingeJointSenseMap=Forecast_mHingeJointSenseMap;	      
	}
	

	addPassMotion();

	if(abs(sendAngle.Lleg3.Aimangle) > 7.0354/50)
	{
		if(sendAngle.Lleg3.Aimangle > 0)
			sendAngle.Lleg3.Aimangle = 7.1/50;
		else
			sendAngle.Lleg3.Aimangle = -7.1/50;
	}

	if(abs(sendAngle.Lleg4.Aimangle) > 7.0354/50)
	{
		if(sendAngle.Lleg4.Aimangle > 0)
			sendAngle.Lleg4.Aimangle = 7.1/50;
		else
			sendAngle.Lleg4.Aimangle = -7.1/50;
	}

	if(abs(sendAngle.Lleg5.Aimangle) > 7.0354/50)
	{
		if(sendAngle.Lleg5.Aimangle > 0)
			sendAngle.Lleg5.Aimangle = 7.1/50;
		else
			sendAngle.Lleg5.Aimangle = -7.1/50;
	}

	if(abs(sendAngle.Rleg3.Aimangle) > 7.0354/50)
	{
		if(sendAngle.Rleg3.Aimangle > 0)
			sendAngle.Rleg3.Aimangle = 7.1/50;
		else
			sendAngle.Rleg3.Aimangle = -7.1/50;
	}

	if(abs(sendAngle.Rleg4.Aimangle) > 7.0354/50)
	{
		if(sendAngle.Rleg4.Aimangle > 0)
			sendAngle.Rleg4.Aimangle = 7.1/50;
		else
			sendAngle.Rleg4.Aimangle = -7.1/50;
	}

	if(abs(sendAngle.Rleg5.Aimangle) > 7.0354/50)
	{
		if(sendAngle.Rleg5.Aimangle > 0)
			sendAngle.Rleg5.Aimangle = 7.1/50;
		else
			sendAngle.Rleg5.Aimangle = -7.1/50;
	}
	//cout<<"walkCounter::"<<this->walkCounter<<endl;
	//cout<<"sendAngle.Head1.Aimangle::"<<sendAngle.Head1.Aimangle<<endl;
	//cout<<"sendAngle.Head2.Aimangle::"<<sendAngle.Head2.Aimangle<<endl;
	//cout<<"sendAngle.Larm1.Aimangle::"<<sendAngle.Larm1.Aimangle<<endl;
	//cout<<"sendAngle.Larm2.Aimangle::"<<sendAngle.Larm2.Aimangle<<endl;
	//cout<<"sendAngle.Larm3.Aimangle::"<<sendAngle.Larm3.Aimangle<<endl;
	//cout<<"sendAngle.Larm4.Aimangle::"<<sendAngle.Larm4.Aimangle<<endl;
	//cout<<"sendAngle.Lleg1.Aimangle::"<<sendAngle.Lleg1.Aimangle<<endl;
	//cout<<"sendAngle.Lleg2.Aimangle::"<<sendAngle.Lleg2.Aimangle<<endl;
	//cout<<"sendAngle.Lleg3.Aimangle::"<<sendAngle.Lleg3.Aimangle<<endl;
	//cout<<"sendAngle.Lleg4.Aimangle::"<<sendAngle.Lleg4.Aimangle<<endl;
	//cout<<"sendAngle.Lleg5.Aimangle::"<<sendAngle.Lleg5.Aimangle<<endl;
	//cout<<"sendAngle.Lleg6.Aimangle::"<<sendAngle.Lleg6.Aimangle<<endl;
	//cout<<"sendAngle.Rarm1.Aimangle::"<<sendAngle.Rarm1.Aimangle<<endl;
	//cout<<"sendAngle.Rarm2.Aimangle::"<<sendAngle.Rarm2.Aimangle<<endl;
	//cout<<"sendAngle.Rarm3.Aimangle::"<<sendAngle.Rarm3.Aimangle<<endl;
	//cout<<"sendAngle.Rarm4.Aimangle::"<<sendAngle.Rarm4.Aimangle<<endl;
	//cout<<"sendAngle.Rleg1.Aimangle::"<<sendAngle.Rleg1.Aimangle<<endl;
	//cout<<"sendAngle.Rleg2.Aimangle::"<<sendAngle.Rleg2.Aimangle<<endl;
	//cout<<"sendAngle.Rleg3.Aimangle::"<<sendAngle.Rleg3.Aimangle<<endl;
	//cout<<"sendAngle.Rleg4.Aimangle::"<<sendAngle.Rleg4.Aimangle<<endl;
	//cout<<"sendAngle.Rleg5.Aimangle::"<<sendAngle.Rleg5.Aimangle<<endl;
	//cout<<"sendAngle.Rleg6.Aimangle::"<<sendAngle.Rleg6.Aimangle<<endl;

	  float tempHead1=sendAngle.Head1.Aimangle*CYCLE;
//	  //cout<<"tempHead1::"<<tempHead1<<endl;
	  sHead1=mp.HJHead_1Rad(tempHead1);
//	  //cout<<"sHead1::"<<sHead1<<endl;

	  float tempHead2=sendAngle.Head2.Aimangle*CYCLE;
//	  //cout<<"tempHead2::"<<tempHead2<<endl;
	  sHead2=mp.HJHead_2Rad(tempHead2);
//	  //cout<<"sHead2::"<<sHead2<<endl;

	  float tempLarm1=sendAngle.Larm1.Aimangle*CYCLE;
	  slarm1=mp.HJLarm_1Rad(tempLarm1);

	  float tempLarm2=sendAngle.Larm2.Aimangle*CYCLE;
	  slarm2=mp.HJLarm_2Rad(tempLarm2);

float templarm3=sendAngle.Larm3.Aimangle*CYCLE;
	  slarm3=mp.HJLarm_3Rad(templarm3);

float tempLarm4=sendAngle.Larm4.Aimangle*CYCLE;
	  slarm4=mp.HJLarm_4Rad(tempLarm4);

float tempLleg1=sendAngle.Lleg1.Aimangle*CYCLE;
	  s1=mp.HJLleg_1Rad(tempLleg1);

float tempLleg2=sendAngle.Lleg2.Aimangle*CYCLE;
	  s2=mp.HJLleg_2Rad(tempLleg2);

	  float tempLleg3=sendAngle.Lleg3.Aimangle*CYCLE;
	  s3=mp.HJLleg_3Rad(tempLleg3);
	  float tempLleg4=sendAngle.Lleg4.Aimangle*CYCLE;
	  s4=mp.HJLleg_4Rad(tempLleg4);
	  float tempLleg5=sendAngle.Lleg5.Aimangle*CYCLE;
	  s5=mp.HJLleg_5Rad(tempLleg5);
	  float tempLleg6=sendAngle.Lleg6.Aimangle*CYCLE;
	  s6=mp.HJLleg_6Rad(tempLleg6);
	  float tempRarm1=sendAngle.Rarm1.Aimangle*CYCLE;
	  srarm1=mp.HJRarm_1Rad(tempRarm1);
	  float tempRarm2=sendAngle.Rarm2.Aimangle*CYCLE;
	  srarm2=mp.HJRarm_2Rad(tempRarm2);
	  float tempRarm3=sendAngle.Rarm3.Aimangle*CYCLE;
	  srarm3=mp.HJRarm_3Rad(tempRarm3);
	  float tempRarm4=sendAngle.Rarm4.Aimangle*CYCLE;
	  srarm4=mp.HJRarm_4Rad(tempRarm4);
	  float tempRleg1=sendAngle.Rleg1.Aimangle*CYCLE;
	  s7=mp.HJRleg_1Rad(tempRleg1);
	  float tempRleg2=sendAngle.Rleg2.Aimangle*CYCLE;
	  s8=mp.HJRleg_2Rad(tempRleg2);
	  float tempRleg3=sendAngle.Rleg3.Aimangle*CYCLE;
	  s9=mp.HJRleg_3Rad(tempRleg3);
	  float tempRleg4=sendAngle.Rleg4.Aimangle*CYCLE;
	  s10=mp.HJRleg_4Rad(tempRleg4);
	  float tempRleg5=sendAngle.Rleg5.Aimangle*CYCLE;
	  s11=mp.HJRleg_5Rad(tempRleg5);
	  float tempRleg6=sendAngle.Rleg6.Aimangle*CYCLE;
	  s12=mp.HJRleg_6Rad(tempRleg6);
   ss=sHead1+sHead2+s1+s2+s3+s4+s5+s6+s7+s8+s9+s10+s11+s12+slarm1+srarm1+slarm2+srarm2+slarm3+srarm3+slarm4+srarm4;

#ifdef jointRecord
string Rleg2="RLEG_J1:";
string Rleg3="RLEG_J2:"; 
string Rleg4="RLEG_J3:";
string Rleg5="RLEG_J4:";
string Rleg6="RLEG_J5:";

string Lleg2="LLEG_J1:";
string Lleg3="LLEG_J2:";
string Lleg4="LLEG_J3:";
string Lleg5="LLEG_J4:";
string Lleg6="LLEG_J5:";

char mark=';';
myRLEG_J1Logger.DoLogByFormatting(Rleg2,"%f%c",Rleg2a,mark);
myRLEG_J2Logger.DoLogByFormatting(Rleg3,"%f%c",Rleg3a,mark);
myRLEG_J3Logger.DoLogByFormatting(Rleg4,"%f%c",Rleg4a,mark);
myRLEG_J4Logger.DoLogByFormatting(Rleg5,"%f%c",Rleg5a,mark);
myRLEG_J5Logger.DoLogByFormatting(Rleg6,"%f%c",Rleg6a,mark);

myLLEG_J1Logger.DoLogByFormatting(Lleg2,"%f%c",Lleg2a,mark);
myLLEG_J2Logger.DoLogByFormatting(Lleg3,"%f%c",Lleg3a,mark);
myLLEG_J3Logger.DoLogByFormatting(Lleg4,"%f%c",Lleg4a,mark);
myLLEG_J4Logger.DoLogByFormatting(Lleg5,"%f%c",Lleg5a,mark);
myLLEG_J5Logger.DoLogByFormatting(Lleg6,"%f%c",Lleg6a,mark);
#endif


	return ss;
}


void  NewWalk::receiveJointInfo()
{
		Received_mHingeJointSenseMap[JID_HEAD_1].angle = messageParser.mHingeJointSenseMap[JID_HEAD_1].angle*PI_180;
		Received_mHingeJointSenseMap[JID_HEAD_2].angle = messageParser.mHingeJointSenseMap[JID_HEAD_2].angle*PI_180;
		
		Received_mHingeJointSenseMap[JID_LLEG_1].angle = messageParser.mHingeJointSenseMap[JID_LLEG_1].angle*PI_180;
		Received_mHingeJointSenseMap[JID_LLEG_2].angle = messageParser.mHingeJointSenseMap[JID_LLEG_2].angle*PI_180;
		Received_mHingeJointSenseMap[JID_LLEG_3].angle = messageParser.mHingeJointSenseMap[JID_LLEG_3].angle*PI_180;
		Received_mHingeJointSenseMap[JID_LLEG_4].angle = messageParser.mHingeJointSenseMap[JID_LLEG_4].angle*PI_180;
		Received_mHingeJointSenseMap[JID_LLEG_5].angle = messageParser.mHingeJointSenseMap[JID_LLEG_5].angle*PI_180;
		Received_mHingeJointSenseMap[JID_LLEG_6].angle = messageParser.mHingeJointSenseMap[JID_LLEG_6].angle*PI_180;
		
		Received_mHingeJointSenseMap[JID_RLEG_1].angle = messageParser.mHingeJointSenseMap[JID_RLEG_1].angle*PI_180;
		Received_mHingeJointSenseMap[JID_RLEG_2].angle = messageParser.mHingeJointSenseMap[JID_RLEG_2].angle*PI_180;
		Received_mHingeJointSenseMap[JID_RLEG_3].angle = messageParser.mHingeJointSenseMap[JID_RLEG_3].angle*PI_180;
		Received_mHingeJointSenseMap[JID_RLEG_4].angle = messageParser.mHingeJointSenseMap[JID_RLEG_4].angle*PI_180;
		Received_mHingeJointSenseMap[JID_RLEG_5].angle = messageParser.mHingeJointSenseMap[JID_RLEG_5].angle*PI_180;
		Received_mHingeJointSenseMap[JID_RLEG_6].angle = messageParser.mHingeJointSenseMap[JID_RLEG_6].angle*PI_180;
		
		Received_mHingeJointSenseMap[JID_LARM_1].angle = messageParser.mHingeJointSenseMap[JID_LARM_1].angle*PI_180;
		Received_mHingeJointSenseMap[JID_LARM_2].angle = messageParser.mHingeJointSenseMap[JID_LARM_2].angle*PI_180;
		Received_mHingeJointSenseMap[JID_LARM_3].angle = messageParser.mHingeJointSenseMap[JID_LARM_3].angle*PI_180;
		Received_mHingeJointSenseMap[JID_LARM_4].angle = messageParser.mHingeJointSenseMap[JID_LARM_4].angle*PI_180;
		
		Received_mHingeJointSenseMap[JID_RARM_1].angle = messageParser.mHingeJointSenseMap[JID_RARM_1].angle*PI_180;
		Received_mHingeJointSenseMap[JID_RARM_2].angle = messageParser.mHingeJointSenseMap[JID_RARM_2].angle*PI_180;
		Received_mHingeJointSenseMap[JID_RARM_3].angle = messageParser.mHingeJointSenseMap[JID_RARM_3].angle*PI_180;
		Received_mHingeJointSenseMap[JID_RARM_4].angle = messageParser.mHingeJointSenseMap[JID_RARM_4].angle*PI_180;

}


int NewWalk::GetWalkCounter()
{
	return walkCounter;
}

float NewWalk::GetFootLength()
{
  return lastCycleFootLength;
	//return footLength;
}

void NewWalk::SetFootLength(float foot)
{
	footLength=foot;
}

float NewWalk::GetFootWidth()
{
  return lastCycleFootWidth;
	//return footWidth;
}

void NewWalk::SetFootWidth(float foot)
{
	footWidth=foot;
}

float NewWalk::GetTurnHeadAngle()
{
	return turnHeadAngle;
}

void NewWalk::SetTurnHeadAngle(float angle)
{
	if(angle>120)
	{
		turnHeadAngle=120;
	}
	else if(angle<-120)
	{
		turnHeadAngle=-120;
	}
	else
	{
		turnHeadAngle=angle;
	}
	/* if(!wm.CanSeeTheBall() &&  turnHeadAngle==120  )
		 {
			 turnHeadAngle= -120;
		 }
		 else if(!wm.CanSeeTheBall() &&  turnHeadAngle==-120)
		 {
			 turnHeadAngle= 120;
		 }*/
}

/////////////////////////////shoot ball//////////////////////////////

void NewWalk::updateLastCyclesAverageTurnHeadAngle()
{
	static int point=0;
	if(wm.CanSeeTheBall())
	{
		lastCyclesTurnHeadAngle[point%LAST_CYCLES_OF_TURN_HEAD_ANGLE]=wm.GetCurrentJointAngle(JID_HEAD_1);
	}
	else 
	{
		lastCyclesTurnHeadAngle[point%LAST_CYCLES_OF_TURN_HEAD_ANGLE]=GetLastCyclesAverageTurnHeadAngle();
	}
	point++;
	
	float angle;
	float totalAngle;
	for(int i=0;i<LAST_CYCLES_OF_TURN_HEAD_ANGLE;i++)
	{
	//	ball=Vector3( lastCyclesBallCoordinate[i].x,lastCyclesBallCoordinate[i].y,lastCyclesBallCoordinate[i].z   );
		angle=lastCyclesTurnHeadAngle[i];
///		if(fabs(ball.x()-lastCyclesAverageBallCoordinate.x())>0.1)
		{
//			/////////////////cout<<"DDDDDDDDDDDlastCyclesBallCoordinate[  " <<i<<"  ]:   "<<lastCyclesBallCoordinate[i]<<endl;
		}
///		else if(fabs(ball.y()-lastCyclesAverageBallCoordinate.y())>0.1)
		{
//			/////////////////cout<<"EEEEEEEEEEElastCyclesBallCoordinate[  " <<i<<"  ]:   "<<lastCyclesBallCoordinate[i]<<endl;
		}
		totalAngle+=angle;
	}	
	lastCyclesAverageTurnHeadAngle=totalAngle/LAST_CYCLES_OF_TURN_HEAD_ANGLE;
	/////////////////cout<<"FFFFFFFFFFlastCyclesAverageTurnHeadAngle:    "<<lastCyclesAverageTurnHeadAngle<<endl;
}

float NewWalk::GetLastCyclesAverageTurnHeadAngle()
{
	return lastCyclesAverageTurnHeadAngle;
}


void NewWalk::updateLastCyclesAverageVerticalTurnHeadAngle()
{
	static int point=0;
	if(wm.CanSeeTheBall())
	{
		lastCyclesVerticalTurnHeadAngle[point%LAST_CYCLES_OF_TURN_HEAD_ANGLE]=wm.GetCurrentJointAngle(JID_HEAD_2);
	}
	else
	{
		lastCyclesVerticalTurnHeadAngle[point%LAST_CYCLES_OF_TURN_HEAD_ANGLE]=GetLastCyclesAverageVerticalTurnHeadAngle();
	}
	point++;
	
	float angle;
	float totalAngle;
	for(int i=0;i<LAST_CYCLES_OF_TURN_HEAD_ANGLE;i++)
	{
	//	ball=Vector3( lastCyclesBallCoordinate[i].x,lastCyclesBallCoordinate[i].y,lastCyclesBallCoordinate[i].z   );
		angle=lastCyclesVerticalTurnHeadAngle[i];
///		if(fabs(ball.x()-lastCyclesAverageBallCoordinate.x())>0.1)
		{
//			/////////////////cout<<"DDDDDDDDDDDlastCyclesBallCoordinate[  " <<i<<"  ]:   "<<lastCyclesBallCoordinate[i]<<endl;
		}
///		else if(fabs(ball.y()-lastCyclesAverageBallCoordinate.y())>0.1)
		{
//			/////////////////cout<<"EEEEEEEEEEElastCyclesBallCoordinate[  " <<i<<"  ]:   "<<lastCyclesBallCoordinate[i]<<endl;
		}
		totalAngle+=angle;
	}	
	lastCyclesAverageVerticalTurnHeadAngle=totalAngle/LAST_CYCLES_OF_TURN_HEAD_ANGLE;
	/////////////////cout<<"QQQQQQQQQQQlastCyclesAverageVerticalTurnHeadAngle:    "<<lastCyclesAverageVerticalTurnHeadAngle<<endl;
}

float NewWalk::GetLastCyclesAverageVerticalTurnHeadAngle()
{
	return lastCyclesAverageVerticalTurnHeadAngle;
}

void NewWalk::updateBodyAngleToDestination(Vector3& destination)
{

	Vector3 myCoordinate=wm.GetMyCoordinate();

	Vector3 ballCoordinate=wm.GetLastCyclesAverageBallCoordinate();
	Vector3 destinationCoordinate=destination;

//	float a=sqrt(   ( destinationCoordinate.x()-ballCoordinate.x() )*(destinationCoordinate.x()-ballCoordinate.x() )+ ( destinationCoordinate.y()-ballCoordinate.y() )*(destinationCoordinate.y()-ballCoordinate.y() )  );
//	float b=sqrt(   ( destinationCoordinate.x()-myCoordinate.x() )*(destinationCoordinate.x()-myCoordinate.x() )+ ( destinationCoordinate.y()-myCoordinate.y() )*(destinationCoordinate.y()-myCoordinate.y() )  );
//	float c=sqrt(   ( myCoordinate.x()-ballCoordinate.x() )*(myCoordinate.x()-ballCoordinate.x() )+ ( myCoordinate.y()-ballCoordinate.y() )*(myCoordinate.y()-ballCoordinate.y() )  );

//	bodyAngleToDestination=acos((c*c+b*b-a*a)/2/b/c)*180/PI+wm.GetMyBodyAngleToBall();
	/////////////////cout<<"444444444444444444444 GetMyBodyAngleToBall() :     "<<wm.GetMyBodyAngleToBall()<<endl;
//	/////////////////cout<<"5555555555555acos((c*c+b*b-a*a)/2/b/c)*180/PI:     "<<acos((c*c+b*b-a*a)/2/b/c)*180/PI<<endl;
//	/////////////////cout<<"6666666666666666666666bodyAngleToDestination:      "<<bodyAngleToDestination<<endl;

//	Vector3 myCoordinate=wm.GetMyCoordinate();

	/////////////////cout<<"testesttestes   atan(-2)*180/PI:   "<<atan(-2)*180/PI<<"testesttestes   atan(2)*180/PI:   "<<atan(2)*180/PI<<endl;
//	Vector3 destinationCoordinate=destination;
	/////////////////cout<<"555555555555555  GetBodyToX     :"<<wm.GetBodyToX()<<endl;
	/////////////////cout<<"666666666666666 GetMyBodyAngleToXAxis()     :"<<wm.GetMyBodyAngleToXAxis()<<endl;
	if(destination.x()>=myCoordinate.x())
	{
		bodyAngleToDestination=atan(  (  myCoordinate.y()-destinationCoordinate.y() ) / ( myCoordinate.x()-destinationCoordinate.x() ) ) *180/PI-wm.GetBodyToX();
	}
	else if(destination.x()<myCoordinate.x())
	{
		bodyAngleToDestination=180+atan(  (  myCoordinate.y()-destinationCoordinate.y() ) / ( myCoordinate.x()-destinationCoordinate.x() ) ) *180/PI-wm.GetBodyToX();
	}

	if(destinationCoordinate==ballCoordinate)
	{
		bodyAngleToDestination=wm.GetMyBodyAngleToBall();
	}
	/////////////////cout<<"myCoordinate:"<<myCoordinate<<endl;
	/////////////////cout<<"destinationCoordinate:"<<destinationCoordinate<<endl;
	/////////////////cout<<"77777777777777 GetLastCyclesAverageBodyToXAngle():  "<<wm.GetLastCyclesAverageBodyToXAngle()<<"  destination:  "<<destination<<endl;
	/////////////////cout<<"ordinate.y() ) / ( myCoordinate.x()-destinationCoordinate.x() ) ) *180/PI     "<<atan(  (  myCoordinate.y()-destinationCoordinate.y() ) / ( myCoordinate.x()-destinationCoordinate.x() ) ) *180/PI<<endl;
	/////////////////cout<<"999999999999999999999999999bodyAngleToDestination:      "<<bodyAngleToDestination<<endl;
}


void NewWalk::SetBodyAngleToDestination(float angle)
{
	bodyAngleToDestination=angle;
}

float NewWalk::GetBodyAngleToDestination()
{
	return bodyAngleToDestination;
}



void NewWalk::updateFootLengthWidth(TopSpeed& topSpeed)
{		Vector3 my=wm.GetMyCoordinate();
Vector3 ball=wm.GetBallCoordinate();
	float angle=GetBodyAngleToDestination();

	/////////////cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~wm.GetMyBodyAngleToBall():        "<<wm.GetMyBodyAngleToBall()<<endl;
///	footLength=footLength*cos(angle*PI/180 );
///	footWidth=footLength*sin(-angle*PI/180 );
	if(topSpeed==AVOID_SPEED)
	{
//		if(ball.y()<my.y())
//		{
//			footLength=0;
//			footWidth=0.08;
//
//		}
//		else
//		{
//			footLength=0;
//					footWidth=-0.08;
//		}
		footLength=-0.08;
		footWidth=0;
	}


	if(topSpeed==NULL_SPEED)
			 {// if(speed>=0.174)
			//	topSpeed=SLOW_SPEED;


	//		else
				if(speed>=0.15)
				topSpeed=MID_SPEED;
			//	speed=0.13;
			/*  if(speed>=0.1)
			  {
				  speed=0.07;
			  }*/
			else if(speed>0.1)
			{
				//speed=0.05;
				speed=MIDMINSPEED;
			}
			else //(speed>0.04)
					{
						speed=MINSPEED;
					}
//			else
//			{
//				footLength=0;
//				footWidth=0;
//			}
			}
	if(topSpeed==MAX_SPEED)
	{
		///////////////cout<<"aaaaaaaa"<<endl;
		if(speed-MAXSPEED>2*QUICK_FOOTLENGTH_INCREAMENT)
		{
			speed-=1*QUICK_FOOTLENGTH_INCREAMENT;
			///////////////cout<<"aaaaabbbb"<<endl;
		}
		else if(MAXSPEED-speed>2*QUICK_FOOTLENGTH_INCREAMENT)
		{
			speed+=1*QUICK_FOOTLENGTH_INCREAMENT;
			///////////////cout<<"aaaaacccc"<<endl;
		}
		else
		{
			speed=MAXSPEED;
			///////////////cout<<"aaaaadddd"<<endl;
		}
	}
	else	if(topSpeed==SLOW_SPEED)
		{
			///////////////cout<<"aaaaaaaa"<<endl;
			if(speed-SLOWSPEED>2*QUICK_FOOTLENGTH_INCREAMENT)
			{
				speed-=1*QUICK_FOOTLENGTH_INCREAMENT;
				///////////////cout<<"aaaaabbbb"<<endl;
			}
			else if(SLOWSPEED-speed>2*QUICK_FOOTLENGTH_INCREAMENT)
			{
				speed+=1*QUICK_FOOTLENGTH_INCREAMENT;
				///////////////cout<<"aaaaacccc"<<endl;
			}
			else
			{
				speed=SLOWSPEED;
				///////////////cout<<"aaaaadddd"<<endl;
			}
		}
	else if(topSpeed==MID_SPEED)
	{
		if(speed-MIDSPEED>2*QUICK_FOOTLENGTH_INCREAMENT)
		{
			speed-=1*QUICK_FOOTLENGTH_INCREAMENT;
			///////////////cout<<"bbbbbbbbb"<<endl;
		}
		else if(MIDSPEED-speed>2*QUICK_FOOTLENGTH_INCREAMENT)
		{
			speed+=1*QUICK_FOOTLENGTH_INCREAMENT;
			///////////////cout<<"ccccccccc"<<endl;
		}
		else
		{
			speed=MIDSPEED;
			///////////////cout<<"ddddddddd"<<endl;
		}
	}
	else if(topSpeed==MIDMIN_SPEED)
	{
	  	if(speed-MIDMINSPEED>2*QUICK_FOOTLENGTH_INCREAMENT)
		{
			speed-=1*QUICK_FOOTLENGTH_INCREAMENT;
			///////////////cout<<"bbbbbbbbb2222222"<<endl;
		}
		else if(MIDMINSPEED-speed>2*QUICK_FOOTLENGTH_INCREAMENT)
		{
			speed+=1*QUICK_FOOTLENGTH_INCREAMENT;
			///////////////cout<<"cccccccc2c2222222"<<endl;
		}
		else
		{
			speed=MIDMINSPEED;
			///////////////cout<<"ddddddddd2222222"<<endl;
		}
	}
	else if(topSpeed==MIN_SPEED)
	{
		if(speed-MINSPEED>2*QUICK_FOOTLENGTH_INCREAMENT)
		{
			speed-=1*QUICK_FOOTLENGTH_INCREAMENT;
			///////////////cout<<"ffffffffff"<<endl;
		}
		else if(MINSPEED-speed>2*QUICK_FOOTLENGTH_INCREAMENT)
		{
			speed+=1*QUICK_FOOTLENGTH_INCREAMENT;
			///////////////cout<<"ggggggggggg"<<endl;
		}
		else
		{
			speed=MINSPEED;
			///////////////cout<<"hhhhhhhhhh"<<endl;
		}
	}

	/////////////cout<<"(speed*cos(angle*PI/180 ):"<<speed*cos(angle*PI/180 )<<endl;

	if((footLength>=0)&&(speed*cos(angle*PI_180 )>=0)||(footLength<=0)&&(speed*cos(angle*PI_180 )<=0))
	{
		///////////////cout<<"xxxxxxxxxxxxxxxxxxxxxxxxxxx"<<endl;
		if(footLength-speed*cos(angle*PI_180 )>QUICK_FOOTLENGTH_INCREAMENT)
		{
			footLength-=1.2*QUICK_FOOTLENGTH_INCREAMENT;
			///////////////cout<<"iiiiiiiiiiiiiiiiiiiii"<<endl;
		}
		else if(speed*cos(angle*PI_180 )-footLength>QUICK_FOOTLENGTH_INCREAMENT)
		{
			footLength+=1.2*QUICK_FOOTLENGTH_INCREAMENT;
			///////////////cout<<"jjjjjjjjjjjjjjjjjj"<<endl;
		}
		else
		{
			footLength=speed*cos(angle*PI_180 );
			///////////////cout<<"lllllllllllllllll"<<endl;
		}
	}
	else if(footLength>0&&speed*cos(angle*PI_180 )<0)
	{
		footLength-=1.2*QUICK_FOOTLENGTH_INCREAMENT;
		///////////////cout<<"kkkkkkkkkkkkk"<<endl;
	}
	else if(footLength<0&&speed*cos(angle*PI_180 )>0)
	{
		footLength+=1.2*QUICK_FOOTLENGTH_INCREAMENT;
		///////////////cout<<"ppppppppppppp"<<endl;
	}

	float mid;
	///////////////cout<<"XXXXXXXXXXXXXX footLength*tan(angle*PI/180 ):"<<footLength*tan(angle*PI/180 )<<endl;
	///////////////cout<<"XXXXXXXXXXXXXX footLength*tan(-angle*PI/180 ):"<<footLength*tan(-angle*PI/180 )<<endl;

	/////////////cout<<"XXXXXXXXXXXXXXXXXXX(speed*sin(-angle*PI/180 ):"<<speed*sin(-angle*PI/180 )<<endl;

	mid=speed*sin(-angle*PI/180 );

	if((footWidth>=0)&&(mid>=0)||(footWidth<=0)&&(mid<=0))
	{
		///////////////cout<<"yyyyyyyyyyyyyyyyyyyyyyyyy"<<endl;
		if(footWidth-mid>QUICK_FOOTLENGTH_INCREAMENTwidth)
		{
			footWidth-=2.5*QUICK_FOOTLENGTH_INCREAMENTwidth;
			///////////////cout<<"mmmmmmmmmmmmmmm"<<endl;
		}
		else if(mid-footWidth>QUICK_FOOTLENGTH_INCREAMENTwidth)
		{
			footWidth+=2.5*QUICK_FOOTLENGTH_INCREAMENTwidth;
			///////////////cout<<"nnnnnnnnnnnnnnnnnnn"<<endl;
		}
		else
		{
			footWidth=mid;
			///////////////cout<<"oooooooooooooooooooo"<<endl;
		}
	}
	else if(footWidth>0&&mid<0)
	{
		footWidth-=2.5*QUICK_FOOTLENGTH_INCREAMENTwidth;
		///////////////cout<<"qqqqqqqqqqqqqqq"<<endl;
	}
	else if(footWidth<0&&mid>0)
	{
		footWidth+=2.5*QUICK_FOOTLENGTH_INCREAMENTwidth;
		///////////////cout<<"ssssssssssssssssss"<<endl;
	}
	
	if(fabs(footWidth)>0.004)
	{
	      if(footLength<-0.09)
	      {
		  footLength=footLength*(1-fabs(footWidth));
		  footWidth=footWidth*(1-fabs(footWidth));
	      }
	      else if(footLength>0.09)
	      {
		  footLength=footLength*(1-fabs(footWidth)*0.6);
		  footWidth=footWidth*(1-fabs(footWidth)*0.6);
	      }
	}
	//if(footLength>=0.158)
	//		footWidth=0;
		if(footLength<-0.158)
			footWidth=0;



				if((wm.GetMyDistanceToBall()<0.12 &&wm.CanDoLocalizationDirectly() && ball.y()<4.5*CELL_LENGTH
					&& wm.GetMyAngleToBall()<20 && ball.x()>my.x() && ball.x()>-4*CELL_LENGTH && ball.x()<6.5*CELL_LENGTH ) ||
						(wm.GetMyDistanceToBall()<0.12 &&wm.CanDoLocalizationDirectly() && ball.y()<4.5*CELL_LENGTH
									&& wm.GetMyAngleToBall()<20 && ball.x()>my.x() && ball.x()>-4*CELL_LENGTH)&& ball.x()<6.5*CELL_LENGTH )
				{
//					if( ball.x()<9*1.667 &&ball.x()>8.3*1.667 && fabs(ball.y())<0.5*1.667)
//					footWidth=-wm.GetMyDistanceToBall()*sin(angle*PI/180 );
//				    footLength=wm.GetMyDistanceToBall()*cos(angle*PI/180)+0.058 ;

	/*		if(ball.x()>my.x()){
                            if( fabs(wm.GetMyAngleToBall())<3){
									footWidth=-wm.GetMyDistanceToBall()*sin(angle*PI/180 )+0.005;
									 if(leftStep==true)
											footWidth=-wm.GetMyDistanceToBall()*sin(angle*PI/180 )-0.005;
                            }
								if(footLength>0&& footLength<0.171)  //0.05
								footLength=wm.GetMyDistanceToBall()*cos(angle*PI/180) +0.04;//0.04
					}*/
			/*	if(footLength<0.08 && wm.GetMyAngleToBall()<20
						&& footWidth<=0.04)
					footLength=0.16;*/
				}
				if(footLength>0.172)
					footLength=0.172;
				if(footLength>=0.172)
					footWidth=0;


				if(footWidth>=0.11)
						{
							footWidth=0.11;
						}
						else if(footWidth<=-0.11)
							 footWidth=-0.11;
//	footLength=speed*cos(angle*PI/180 );
//	footWidth=speed*sin(-angle*PI/180 );
/*	cout<<"~~~~~~~~~~~~~~~~~speed:  "<<speed<<endl;
	cout<<"~~~~~~~~~~~~~~~~~~~~footLength; "<<footLength<<endl;
	cout<<"~~~~~~~~~~~~~~~~~~~footWidth;"<<footWidth<<endl;*/
//			if(	wm.GetCurrentGameMode()==PM_KickOff_Our)
//			{
//				footLength=0;
//							footWidth=0.07;
//			}

}
Action NewWalk::PrepareForFreeKickCIT(int leftShootDistance)
{
	if(hasFallDown==true)///new add
	 	{
	 		InitNewWalkData();
	 		hasFallDown=false;
			UseNewWalk=true;
			///////////////////cout<<"fall down"<<endl;
		}
		if(UseNewWalk==false)
	 	{
			return prepareForShoot_HalfStep(leftShootDistance);
	 	}
		updateTime();
		///////////////////cout<<"after fall down"<<endl;
		exchangeArms();
		////////////////////cout<<"after exchange arms "<<endl;
		updateShootParameterForKickCIT(leftShootDistance);
		///////////////////cout<<"after update Shoot Parameter "<<endl;

	    preparation();
		////////////////////cout<<"after preparation "<<endl;

		updateshootPV();
		///	/////////////////cout<<"after update PV "<<endl;

		return readNewWalkData();
	}





void NewWalk::updateShootParameterForKickCIT(int leftShootDistance)
{
	/////////////////////cout<<"time::"<<wm.GetCurrentGameTime()<<endl;
	//footWidth=0;
	turnHeadAngle=0;
	adjustAngle=0;
///////////////cout<<"time ="<<wm.GetCurrentGameTime()<<"          foot length ="<<footLength<<"            my distance to ball ="<<wm.GetMyDistanceToBall()<<"   cos(fabs(wm.GetMyBodyAngleToBall()) ="<<cos(fabs(wm.GetMyAngleToBall()))<<endl;

	if(wm.GetMyDistanceToBall()<=(0.21+0.32*(lastCycleFootLength/0.17)))
	{
	      ///////////////cout<<"--0.005"<<endl;
		footLength=footLength-0.008;
		if(footLength<=0.008)
			footLength=0.008;
// 		///////////////cout<<"					slow down for shoot!!!!!!!!"<<endl;
		 if(wm.GetMyDistanceToBall()>0.21&&footLength<0.04)
		 {
		   ///////////////cout<<"					111111"<<endl;

		      footLength=footLength+0.005;
		 }
	}
	else
	{
		footLength=footLength+SLOW_FOOTLENGTH_INCREAMENT*1.3;
		if(footLength>=MAXSPEED)
			footLength=MAXSPEED;
// 		///////////////cout<<"					too slow speed up!!!!"<<endl;
	}

	if(wm.GetMyDistanceToBall()>0.22&&footLength<0.03)
	{
	  	///////////////cout<<"				2222222222222"<<endl;
		//0.0015
		footLength=footLength+0.0025;
	}
	float angle=0;
	Vector3 my=wm.GetMyCoordinate();
	/////////////////cout<<"!!!Get  My  Angle  To  Flag(VO_GOAL1_R) ="<<wm.GetMyAngleToFlag(VO_GOAL1_R)<<endl;
	/////////////////cout<<"!!!Get  My  Angle  To  Flag(VO_GOAL2_R) ="<<wm.GetMyAngleToFlag(VO_GOAL2_R)<<endl;
// 	///////////////cout<<"!!!Get  My  Angle  To  BALL) ="<<wm.GetMyAngleToBall()<<endl;
	if(leftShootDistance==1)
	{
		angle=wm.GetMyAngleToBall()-5;
	}
	else
	{
		angle=wm.GetMyAngleToBall()+5;
	}

	if(footLength<0.08&&wm.GetMyDistanceToBall()<0.4)
	{
	  if(my.x()>3) ///this part for only the vanguard do turn to opp goal when shooting.cause in this class can not get player's role
	  {
	    /////////////cout<<"my.x()>3,and turn to opp goal for shoot"<<endl;
		if(wm.GetMyTeamIndex() == TI_LEFT)
		{
			if(wm.GetMyAngleToFlag(VO_GOAL1_R)<0&&wm.GetMyAngleToFlag(VO_GOAL2_R)<0)
			{
				float temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_R)-wm.GetMyAngleToFlag(VO_GOAL2_R))/2;
				angle=wm.GetMyAngleToFlag(VO_GOAL1_R)-temp;
			}
			else if(wm.GetMyAngleToFlag(VO_GOAL1_R)>0&&wm.GetMyAngleToFlag(VO_GOAL2_R)>0)
			{
				float temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_R)-wm.GetMyAngleToFlag(VO_GOAL2_R))/2;
				angle=wm.GetMyAngleToFlag(VO_GOAL2_R)+temp;
			}
			else
			{
				float temp;
				if(wm.GetMyAngleToFlag(VO_GOAL1_R)>-wm.GetMyAngleToFlag(VO_GOAL2_R))
				{
				      temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_R)-wm.GetMyAngleToFlag(VO_GOAL2_R))*5/7;
				}
				else
				      temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_R)-wm.GetMyAngleToFlag(VO_GOAL2_R))*2/7;

				angle=wm.GetMyAngleToFlag(VO_GOAL1_R)-temp;
			}
		}
		else
		{
			if(wm.GetMyAngleToFlag(VO_GOAL1_L)<0&&wm.GetMyAngleToFlag(VO_GOAL2_L)<0)
			{
				float temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_L)-wm.GetMyAngleToFlag(VO_GOAL2_L))/2;
				angle=wm.GetMyAngleToFlag(VO_GOAL2_L)-temp;
			}
			else if(wm.GetMyAngleToFlag(VO_GOAL1_L)>0&&wm.GetMyAngleToFlag(VO_GOAL2_L)>0)
			{
				float temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_L)-wm.GetMyAngleToFlag(VO_GOAL2_L))/2;
				angle=wm.GetMyAngleToFlag(VO_GOAL1_L)+temp;
			}
			else
			{
				float temp;
				if(wm.GetMyAngleToFlag(VO_GOAL2_L)>-wm.GetMyAngleToFlag(VO_GOAL1_L))
				 temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_L)-wm.GetMyAngleToFlag(VO_GOAL2_L))*5/7;
				 else
				   temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_L)-wm.GetMyAngleToFlag(VO_GOAL2_L))*2/7;

				angle=wm.GetMyAngleToFlag(VO_GOAL2_L)-temp;
			}
		}
		/////////////cout<<"angle:"<<angle<<endl;
	  }
	  else
	  {

	    //cout<<"do not turn ,just shoot ball"<<endl;
	  }

		if(wm.GetMyAngleToBall()>0)
		{
			if(wm.GetMyAngleToBall()>11.5)
			{
				///////////////////cout<<"////////////////////////////////////////move left!!!//////////////////////////////////"<<footWidth<<endl;
				//footWidth=footWidth-QUICK_FOOTLENGTH_INCREAMENT;
				//float width=fabs(wm.GetMyDistanceToBall()*sin(wm.GetMyAngleToBall()))-0.0225;
				float width=fabs(wm.GetMyDistanceToBall()*sin(wm.GetMyAngleToBall()));
// 					///////////////cout<<"move left ***********  width to move ::"<<endl;
					//if(width<0)
				if(width<0.0225)
						footLength=0;
					else if(width<=0.06)
						footWidth=-width;
					else
						footWidth=-0.06;
			}
			else if(wm.GetMyAngleToBall()<5)
			{
// 				///////////////cout<<"////////////////////////////////////////move right!!!//////////////////////////////////"<<endl;
					// 		footWidth=footWidth+QUICK_FOOTLENGTH_INCREAMENT;
				//	footWidth=0.0225;
				footWidth=0.0225;

			}
			else
				footWidth=0;
		}
		else
		{
			if(wm.GetMyAngleToBall()<-11.5)
			{
				///////////////////cout<<"////////////////////////////////////////move left!!!//////////////////////////////////"<<footWidth<<endl;
				//footWidth=footWidth-QUICK_FOOTLENGTH_INCREAMENT;
				//	float width=fabs(wm.GetMyDistanceToBall()*sin(wm.GetMyAngleToBall()))-0.0225;
					float width=fabs(wm.GetMyDistanceToBall()*sin(wm.GetMyAngleToBall()));
					/////////////////cout<<"////////////////////////////////// move right/////////////////////////// "<<endl;
					if(width<0.0225)
						footLength=0;
					else if(width<=0.06)
						footWidth=width;
					else
						footWidth=0.06;
			}
			else if(wm.GetMyAngleToBall()>-5)
			{
				 	//	///////////////cout<<"////////////////////////////////////////move left!!!//////////////////////////////////"<<endl;
					// 		footWidth=footWidth+QUICK_FOOTLENGTH_INCREAMENT;
					//footWidth=-0.0225;
				footWidth=-0.0225;

			}
			else
				footWidth=0;
		}
	}
	/////////////////cout<<"time :"<<wm.GetCurrentGameTime()<<"               foot width =" <<footWidth<<endl;
	updateTurnAngle(angle);
}









Action NewWalk::PrepareForFreeKick(int leftShootDistance)
{
 	if(hasFallDown==true)///new add
 	{
 		InitNewWalkData();
 		hasFallDown=false;
		UseNewWalk=true;
		///////////////////cout<<"fall down"<<endl;
	}
	if(UseNewWalk==false)
 	{
		return prepareForShoot_HalfStep(leftShootDistance);
 	}
        updateTime();
	///////////////////cout<<"after fall down"<<endl;
	exchangeArms();
	////////////////////cout<<"after exchange arms "<<endl;
	//updateShootParameter(leftShootDistance);
	updateShootParameterForFreeKick(leftShootDistance);
	///////////////////cout<<"after update Shoot Parameter "<<endl;

    preparation();
	////////////////////cout<<"after preparation "<<endl;

//	updateshootPV();
    updatePV();
	///	/////////////////cout<<"after update PV "<<endl;

	return readNewWalkData();
}

void NewWalk::updateShootParameterForFreeKick(int leftShootDistance)
{Vector3 ball=wm.GetLastCyclesAverageBallCoordinate();
	/////////////////////cout<<"time::"<<wm.GetCurrentGameTime()<<endl;
	//footWidth=0;
	turnHeadAngle=0;
	adjustAngle=0;
///////////////cout<<"time ="<<wm.GetCurrentGameTime()<<"          foot length ="<<footLength<<"            my distance to ball ="<<wm.GetMyDistanceToBall()<<"   cos(fabs(wm.GetMyBodyAngleToBall()) ="<<cos(fabs(wm.GetMyAngleToBall()))<<endl;

	if(wm.GetMyDistanceToBall()<=(0.25+0.32*(lastCycleFootLength/0.17)))
	{
	      ///////////////cout<<"--0.005"<<endl;
		footLength=footLength-0.008;
		if(footLength<=0.008)
			footLength=0.008;
// 		///////////////cout<<"					slow down for shoot!!!!!!!!"<<endl;
		 if(wm.GetMyDistanceToBall()>0.26&&footLength<0.04)  //0.21
		 {
		   ///////////////cout<<"					111111"<<endl;

		      footLength=footLength+0.005;
		 }
	}
	else  if(wm.GetMyDistanceToBall()-0.05>0.47 && wm.GetMyDistanceToBall()-0.05<0.8)
	{
		footLength=footLength+SLOW_FOOTLENGTH_INCREAMENT*1.3;
		//if(footLength>=MAXSPEED)
		//	footLength=MAXSPEED;
	//	if(footLength>=0.06)
	//	footLength=0.06;
	}
	else
	{
		footLength=footLength+SLOW_FOOTLENGTH_INCREAMENT*1.3;
				if(footLength>=MAXSPEED)
					footLength=MAXSPEED-0.06;

	}

	if(wm.GetMyDistanceToBall()-0.03>0.27&&footLength<0.03)
	{
	  	///////////////cout<<"				2222222222222"<<endl;
		//0.0015
		footLength=footLength+0.0025;
	}
	if(footLength>0.170)
		footLength=0.17;
	float 	angle=0;
	//angle=wm.GetMyBodyAngleToBall();
	//angle=0;
	Vector3 my=wm.GetMyCoordinate();
	/////////////////cout<<"!!!Get  My  Angle  To  Flag(VO_GOAL1_R) ="<<wm.GetMyAngleToFlag(VO_GOAL1_R)<<endl;
	/////////////////cout<<"!!!Get  My  Angle  To  Flag(VO_GOAL2_R) ="<<wm.GetMyAngleToFlag(VO_GOAL2_R)<<endl;
// 	///////////////cout<<"!!!Get  My  Angle  To  BALL) ="<<wm.GetMyAngleToBall()<<endl;
	if(leftShootDistance==1)
	{
		angle=wm.GetMyAngleToBall()-5;
	}
	else
	{
		angle=wm.GetMyAngleToBall()+5;
	}

	 //he if(footLength<0.08&&wm.GetMyDistanceToBall()<0.4)
	{
	  if(my.x()>0) ///3 this part for only the vanguard do turn to opp goal when shooting.cause in this class can not get player's role
	  {
	    /////////////cout<<"my.x()>3,and turn to opp goal for shoot"<<endl;
		if(wm.GetMyTeamIndex() == TI_LEFT)
		{
			if(wm.GetMyAngleToFlag(VO_GOAL1_R)<0&&wm.GetMyAngleToFlag(VO_GOAL2_R)<0)
			{
				float temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_R)-wm.GetMyAngleToFlag(VO_GOAL2_R))/2;
				angle=wm.GetMyAngleToFlag(VO_GOAL1_R)-temp;
			}
			else if(wm.GetMyAngleToFlag(VO_GOAL1_R)>0&&wm.GetMyAngleToFlag(VO_GOAL2_R)>0)
			{
				float temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_R)-wm.GetMyAngleToFlag(VO_GOAL2_R))/2;
				angle=wm.GetMyAngleToFlag(VO_GOAL2_R)+temp;
			}
			else
			{
				float temp;
				if(wm.GetMyAngleToFlag(VO_GOAL1_R)>-wm.GetMyAngleToFlag(VO_GOAL2_R))
				{
				      temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_R)-wm.GetMyAngleToFlag(VO_GOAL2_R))*5/7;
				}
				else
				      temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_R)-wm.GetMyAngleToFlag(VO_GOAL2_R))*2/7;

				angle=wm.GetMyAngleToFlag(VO_GOAL1_R)-temp;
			}
		}
		else
		{
			if(wm.GetMyAngleToFlag(VO_GOAL1_L)<0&&wm.GetMyAngleToFlag(VO_GOAL2_L)<0)
			{
				float temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_L)-wm.GetMyAngleToFlag(VO_GOAL2_L))/2;
				angle=wm.GetMyAngleToFlag(VO_GOAL2_L)-temp;
			}
			else if(wm.GetMyAngleToFlag(VO_GOAL1_L)>0&&wm.GetMyAngleToFlag(VO_GOAL2_L)>0)
			{
				float temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_L)-wm.GetMyAngleToFlag(VO_GOAL2_L))/2;
				angle=wm.GetMyAngleToFlag(VO_GOAL1_L)+temp;
			}
			else
			{
				float temp;
				if(wm.GetMyAngleToFlag(VO_GOAL2_L)>-wm.GetMyAngleToFlag(VO_GOAL1_L))
				 temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_L)-wm.GetMyAngleToFlag(VO_GOAL2_L))*5/7;
				 else
				   temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_L)-wm.GetMyAngleToFlag(VO_GOAL2_L))*2/7;

				angle=wm.GetMyAngleToFlag(VO_GOAL2_L)-temp;
			}
		}
		/////////////cout<<"angle:"<<angle<<endl;
	  }
	 // else
	  {

	    //cout<<"do not turn ,just shoot ball"<<endl;
	  }

		if(wm.GetMyAngleToBall()>0)
		{
			if(wm.GetMyAngleToBall()>11.5)
			{
				///////////////////cout<<"////////////////////////////////////////move left!!!//////////////////////////////////"<<footWidth<<endl;
				//footWidth=footWidth-QUICK_FOOTLENGTH_INCREAMENT;
				//float width=fabs(wm.GetMyDistanceToBall()*sin(wm.GetMyAngleToBall()))-0.0225;
				float width=fabs(wm.GetMyDistanceToBall()*sin(wm.GetMyAngleToBall()));
// 					///////////////cout<<"move left ***********  width to move ::"<<endl;
					//if(width<0)
				if(width<0.0425)//0.0225
						footLength=0;
					else if(width<=0.06)
						footWidth=-width;
					else
						footWidth=-0.04;  //0.06
			}
			else if(wm.GetMyAngleToBall()<5)
			{
// 				///////////////cout<<"////////////////////////////////////////move right!!!//////////////////////////////////"<<endl;
					// 		footWidth=footWidth+QUICK_FOOTLENGTH_INCREAMENT;
				//	footWidth=0.0225;
				footWidth=0.0225;

			}
			else
				footWidth=0;
		}
		else
		{
			if(wm.GetMyAngleToBall()<-11.5)
			{
				///////////////////cout<<"////////////////////////////////////////move left!!!//////////////////////////////////"<<footWidth<<endl;
				//footWidth=footWidth-QUICK_FOOTLENGTH_INCREAMENT;
				//	float width=fabs(wm.GetMyDistanceToBall()*sin(wm.GetMyAngleToBall()))-0.0225;
					float width=fabs(wm.GetMyDistanceToBall()*sin(wm.GetMyAngleToBall()));
					/////////////////cout<<"////////////////////////////////// move right/////////////////////////// "<<endl;
					if(width<0.0425)  //0.0225
						footLength=0;
					else if(width<=0.06)
						footWidth=width;
					else
						footWidth=0.04;   //0.06
			}
			else if(wm.GetMyAngleToBall()>-5)
			{
				 	//	///////////////cout<<"////////////////////////////////////////move left!!!//////////////////////////////////"<<endl;
					// 		footWidth=footWidth+QUICK_FOOTLENGTH_INCREAMENT;
					//footWidth=-0.0225;
				footWidth=-0.0225;

			}
			else
				footWidth=0;
		}
	}
//	if( angle==0 && footWidth!=0 &&fabs(wm.GetMyAngleToBall())>11.5 &&ball.x() <my.x()	)
//		footLength=-0.05;
	/////////////////cout<<"time :"<<wm.GetCurrentGameTime()<<"               foot width =" <<footWidth<<endl;
	//Vector3 ball=wm.GetLastCyclesAverageBallCoordinate();
	//ball.x()=ball.x()+0.05;
	//&& (fabs(my.y()) < fabs(ball.y()) + 0.1)
	//if((ball.x() <my.x()+0.1)	)
	//angle = wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
	//if(ball.x()<my.x()+0.08)
	//	angle=wm.GetMyBodyAngleToBall();


	//angle = wm.GetMyBodyAngleToXAxis();
	//else
	//	angle=wm.GetLastCyclesAverageBallGoalToXAxisAngle();
//	if(ball.x() <my.x()+0.03 && (fabs(my.y()) > fabs(ball.y()) + 0.1)&&fabs(wm.GetMyAngleToBall()>60)&&fabs(wm.GetMyBodyAngleToXAxis()<80) )
//		{footLength=-0.1;
//		 footWidth=0;
//		}
	if(ball.x() <my.x()+0.08) //&& (fabs(my.y()) > fabs(ball.y()) + 0.1)&&fabs(wm.GetMyAngleToBall()>60)&&fabs(wm.GetMyBodyAngleToXAxis()<80) )
			{//footLength=-0.07;
			// footWidth=0;
			}
	if(wm.GetMyTeamIndex() == TI_LEFT)
			{
				if(wm.GetMyAngleToFlag(VO_GOAL1_R)<0&&wm.GetMyAngleToFlag(VO_GOAL2_R)<0)
				{
					float temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_R)-wm.GetMyAngleToFlag(VO_GOAL2_R))/2;
					angle=wm.GetMyAngleToFlag(VO_GOAL1_R)-temp;
				}
				else if(wm.GetMyAngleToFlag(VO_GOAL1_R)>0&&wm.GetMyAngleToFlag(VO_GOAL2_R)>0)
				{
					float temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_R)-wm.GetMyAngleToFlag(VO_GOAL2_R))/2;
					angle=wm.GetMyAngleToFlag(VO_GOAL2_R)+temp;
				}

				else
				{
					float temp;
					if(wm.GetMyAngleToFlag(VO_GOAL1_R)>-wm.GetMyAngleToFlag(VO_GOAL2_R))
					{
					      temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_R)-wm.GetMyAngleToFlag(VO_GOAL2_R))*5/7;
					}
					else
					      temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_R)-wm.GetMyAngleToFlag(VO_GOAL2_R))*2/7;

					angle=wm.GetMyAngleToFlag(VO_GOAL1_R)-temp;
				}
			}
	//fabs(wm.GetMyAngleToBall())>11.5 &&
//	if( angle==0 && footWidth!=0 &&ball.x() <my.x()+0.1&&!wm.CanSeeTheBall()	)
//			footLength=-0.08;
	// angle = wm.GetMyAngleToBall();
//	if( wm.GetCurrentGameMode() !=PM_KickOff_Our)
//	{
//	if (wm.CanSeeTheFlag(VO_GOAL1_R) && wm.CanSeeTheFlag(VO_GOAL2_R))
//	angle=(wm.GetMyAngleToFlag(VO_GOAL2_R)+wm.GetMyAngleToFlag(VO_GOAL1_R))/2;
//	}
//	else
	{
	//	angle=wm.GetMyAngleToBall();
	}
		//if(!wm.CanSeeTheFlag(VO_GOAL1_R) && !wm.CanSeeTheFlag(VO_GOAL2_R))
	//if(!(wm.CanSeeTheFlag(VO_GOAL1_R))  ||(! wm.CanSeeTheFlag(VO_GOAL2_R)))
	//	if(angle==0 && (footWidth)==0  )
//	angle = wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();

	 if (wm.CanSeeTheFlag(VO_GOAL1_R) && wm.CanSeeTheFlag(VO_GOAL2_R))
	angle=(wm.GetMyAngleToFlag(VO_GOAL2_R)+wm.GetMyAngleToFlag(VO_GOAL1_R))/2;




		//if(!wm.CanSeeTheFlag(VO_GOAL1_R) && !wm.CanSeeTheFlag(VO_GOAL2_R))
	//if(!(wm.CanSeeTheFlag(VO_GOAL1_R))  ||(! wm.CanSeeTheFlag(VO_GOAL2_R)))
	//	if(angle==0 && (footWidth)==0  )
	angle = wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis() ;

if(	wm.GetCurrentGameMode()==PM_KickOff_Our )
	  angle=wm.GetMyAngleToBall();
//angle =5;
	updateTurnAngle(angle);
}




Action NewWalk::PrePareForShoot(int leftShootDistance)
{
 	if(hasFallDown==true)///new add
 	{
 		InitNewWalkData();
 		hasFallDown=false;
		UseNewWalk=true;
		///////////////////cout<<"fall down"<<endl;
    	}
    	if(UseNewWalk==false)
 	{		
		return prepareForShoot_HalfStep(leftShootDistance);
 	}
        updateTime();
	///////////////////cout<<"after fall down"<<endl;
	exchangeArms();
	////////////////////cout<<"after exchange arms "<<endl;
	updateShootParameter(leftShootDistance);
	///////////////////cout<<"after update Shoot Parameter "<<endl;
	
    preparation();
	////////////////////cout<<"after preparation "<<endl;

	updateshootPV();
	///	/////////////////cout<<"after update PV "<<endl;
	
	return readNewWalkData();
}
void NewWalk::updateShootParameter(int leftShootDistance)
{
	/////////////////////cout<<"time::"<<wm.GetCurrentGameTime()<<endl;
	//footWidth=0;
	turnHeadAngle=0;
	adjustAngle=0;
///////////////cout<<"time ="<<wm.GetCurrentGameTime()<<"          foot length ="<<footLength<<"            my distance to ball ="<<wm.GetMyDistanceToBall()<<"   cos(fabs(wm.GetMyBodyAngleToBall()) ="<<cos(fabs(wm.GetMyAngleToBall()))<<endl;

	if(wm.GetMyDistanceToBall()<=(0.15+0.32*(lastCycleFootLength/0.17)))
	{
	      ///////////////cout<<"--0.005"<<endl;
		footLength=footLength-0.008;
		if(footLength<=0.008)
			footLength=0.008;
// 		///////////////cout<<"					slow down for shoot!!!!!!!!"<<endl;
		 if(wm.GetMyDistanceToBall()>0.25 &&footLength<0.04)   //0.21
		 {
		   ///////////////cout<<"					111111"<<endl;

		      footLength=footLength+0.005;
		 }
	}
	else
	{
		footLength=footLength+SLOW_FOOTLENGTH_INCREAMENT*1.3;
		if(footLength>=MAXSPEED)
			footLength=MAXSPEED;
// 		///////////////cout<<"					too slow speed up!!!!"<<endl;
	}


	////////////////////////////////////////////////////////
//	if(wm.GetMyDistanceToBall()<=(0.2+0.32*(lastCycleFootLength/0.17)))  //0.25
//	{
//	      ///////////////cout<<"--0.005"<<endl;
//		footLength=footLength-0.008;
//		if(footLength<=0.008)
//			footLength=0.008;
//// 		///////////////cout<<"					slow down for shoot!!!!!!!!"<<endl;
//		 if(wm.GetMyDistanceToBall()>0.26&&footLength<0.04)  //0.21
//		 {
//		   ///////////////cout<<"					111111"<<endl;
//
//		      footLength=footLength+0.005;
//		 }
//	}
//	else  if(wm.GetMyDistanceToBall()-0.05>0.47 && wm.GetMyDistanceToBall()-0.05<0.8)
//	{
//		footLength=footLength+SLOW_FOOTLENGTH_INCREAMENT*1.5;
//		//if(footLength>=MAXSPEED)
//		//	footLength=MAXSPEED;
//	//	if(footLength>=0.06)
//	//	footLength=0.06;
//	}
//	else
//	{
//		footLength=footLength+SLOW_FOOTLENGTH_INCREAMENT*1.6;
//				if(footLength>=MAXSPEED)
//					footLength=MAXSPEED-0.06;
//
//	}
//
//












	//////////////////////////////////////////////////////////////////////

	if(wm.GetMyDistanceToBall()>0.22&&footLength<0.03)
	{
	  	///////////////cout<<"				2222222222222"<<endl;
		//0.0015
		footLength=footLength+0.0025;
	}
	float angle=0;
	Vector3 my=wm.GetMyCoordinate();
	/////////////////cout<<"!!!Get  My  Angle  To  Flag(VO_GOAL1_R) ="<<wm.GetMyAngleToFlag(VO_GOAL1_R)<<endl;
	/////////////////cout<<"!!!Get  My  Angle  To  Flag(VO_GOAL2_R) ="<<wm.GetMyAngleToFlag(VO_GOAL2_R)<<endl;
// 	///////////////cout<<"!!!Get  My  Angle  To  BALL) ="<<wm.GetMyAngleToBall()<<endl;
	if(leftShootDistance==1)
	{
		angle=wm.GetMyAngleToBall()-5;
	}
	else
	{
		angle=wm.GetMyAngleToBall()+5;
	}
	
	if(footLength<0.08&&wm.GetMyDistanceToBall()<0.4)
	{
	  if(my.x()>3) ///this part for only the vanguard do turn to opp goal when shooting.cause in this class can not get player's role
	  {
	    /////////////cout<<"my.x()>3,and turn to opp goal for shoot"<<endl;
		if(wm.GetMyTeamIndex() == TI_LEFT)
		{
			if(wm.GetMyAngleToFlag(VO_GOAL1_R)<0&&wm.GetMyAngleToFlag(VO_GOAL2_R)<0)
			{
				float temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_R)-wm.GetMyAngleToFlag(VO_GOAL2_R))/2;
				angle=wm.GetMyAngleToFlag(VO_GOAL1_R)-temp;
			}
			else if(wm.GetMyAngleToFlag(VO_GOAL1_R)>0&&wm.GetMyAngleToFlag(VO_GOAL2_R)>0)
			{
				float temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_R)-wm.GetMyAngleToFlag(VO_GOAL2_R))/2;
				angle=wm.GetMyAngleToFlag(VO_GOAL2_R)+temp;
			}
			else
			{
				float temp;
				if(wm.GetMyAngleToFlag(VO_GOAL1_R)>-wm.GetMyAngleToFlag(VO_GOAL2_R))
				{
				      temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_R)-wm.GetMyAngleToFlag(VO_GOAL2_R))*5/7;
				}
				else
				      temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_R)-wm.GetMyAngleToFlag(VO_GOAL2_R))*2/7;
				  
				angle=wm.GetMyAngleToFlag(VO_GOAL1_R)-temp;
			}
		}
		else
		{
			if(wm.GetMyAngleToFlag(VO_GOAL1_L)<0&&wm.GetMyAngleToFlag(VO_GOAL2_L)<0)
			{
				float temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_L)-wm.GetMyAngleToFlag(VO_GOAL2_L))/2;
				angle=wm.GetMyAngleToFlag(VO_GOAL2_L)-temp;
			}
			else if(wm.GetMyAngleToFlag(VO_GOAL1_L)>0&&wm.GetMyAngleToFlag(VO_GOAL2_L)>0)
			{
				float temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_L)-wm.GetMyAngleToFlag(VO_GOAL2_L))/2;
				angle=wm.GetMyAngleToFlag(VO_GOAL1_L)+temp;
			}
			else
			{
				float temp;
				if(wm.GetMyAngleToFlag(VO_GOAL2_L)>-wm.GetMyAngleToFlag(VO_GOAL1_L))
				 temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_L)-wm.GetMyAngleToFlag(VO_GOAL2_L))*5/7;
				 else
				   temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_L)-wm.GetMyAngleToFlag(VO_GOAL2_L))*2/7;
				   
				angle=wm.GetMyAngleToFlag(VO_GOAL2_L)-temp;
			}
		}
		/////////////cout<<"angle:"<<angle<<endl;
	  }
	  else
	  {

	    //cout<<"do not turn ,just shoot ball"<<endl;
	  }

		if(wm.GetMyAngleToBall()>0)
		{
			if(wm.GetMyAngleToBall()>11.5)
			{
				///////////////////cout<<"////////////////////////////////////////move left!!!//////////////////////////////////"<<footWidth<<endl;
				//footWidth=footWidth-QUICK_FOOTLENGTH_INCREAMENT;
				//float width=fabs(wm.GetMyDistanceToBall()*sin(wm.GetMyAngleToBall()))-0.0225;
				float width=fabs(wm.GetMyDistanceToBall()*sin(wm.GetMyAngleToBall()));
// 					///////////////cout<<"move left ***********  width to move ::"<<endl;
					//if(width<0)
				if(width<0.0225)   //0.0225
						footLength=0;
					else if(width<=0.06)
						footWidth=-width;
					else
						footWidth=-0.06;   //-0.06
			}
			else if(wm.GetMyAngleToBall()<5)
			{
// 				///////////////cout<<"////////////////////////////////////////move right!!!//////////////////////////////////"<<endl;
					// 		footWidth=footWidth+QUICK_FOOTLENGTH_INCREAMENT;
				//	footWidth=0.0225;
				footWidth=0.0225;

			}
			else
				footWidth=0;
		}
		else
		{
			if(wm.GetMyAngleToBall()<-11.5)
			{
				///////////////////cout<<"////////////////////////////////////////move left!!!//////////////////////////////////"<<footWidth<<endl;
				//footWidth=footWidth-QUICK_FOOTLENGTH_INCREAMENT;
				//	float width=fabs(wm.GetMyDistanceToBall()*sin(wm.GetMyAngleToBall()))-0.0225;
					float width=fabs(wm.GetMyDistanceToBall()*sin(wm.GetMyAngleToBall()));
					/////////////////cout<<"////////////////////////////////// move right/////////////////////////// "<<endl;
					if(width<0.0225)   //0.0225
						footLength=0;
					else if(width<=0.06)
						footWidth=width;
					else
						footWidth=0.06;   //0.06
			}
			else if(wm.GetMyAngleToBall()>-5)
			{
				 	//	///////////////cout<<"////////////////////////////////////////move left!!!//////////////////////////////////"<<endl;
					// 		footWidth=footWidth+QUICK_FOOTLENGTH_INCREAMENT;
					//footWidth=-0.0225;
				footWidth=-0.0225;
			
			}
			else
				footWidth=0;
		}
	}
	/////////////////cout<<"time :"<<wm.GetCurrentGameTime()<<"               foot width =" <<footWidth<<endl;
	updateTurnAngle(angle);
}

void NewWalk::adjustMySpeedByBodyState()
{
	if(messageParser.playerAroundMe==OPPONENT_FRONT&&footLength>=0.1&&fabs(wm.GetMyBodyAngleToXAxis())<30)
	{
	      footLength-=QUICK_FOOTLENGTH_INCREAMENT;
	}
	if(wm.EstimateWhetherUseHalfWalk()&&fabs(wm.GetMyBodyAngleToXAxis())<30&&footLength>=0.1)
	{
	       footLength-=QUICK_FOOTLENGTH_INCREAMENT;
	}
	
	if(footLength<0&&fabs(wm.GetMyBodyAngleToBall()<13)&&wm.GetMyDistanceToBall()>0.3)
	{
	      footLength+=QUICK_FOOTLENGTH_INCREAMENT;
	}
	if(wm.GetLastCyclesAverageBallCoordinate().x()<-10&&wm.GetMyCoordinate().x()<-10.2&&footLength<0&&fabs(wm.GetMyBodyAngleToBall())<15)
	{
	      footLength+=QUICK_FOOTLENGTH_INCREAMENT;
	}
	
	if(wm.GetMyTeamIndex()==TI_LEFT)
	{

		if(messageParser.mVisionSenseMap[VO_GOAL1_R].phi!=0&&messageParser.mVisionSenseMap[VO_GOAL2_R].phi!=0)
		{
			if((messageParser.mVisionSenseMap[VO_GOAL1_R].theta+messageParser.mHingeJointSenseMap[JID_HEAD_1].angle)*(messageParser.mVisionSenseMap[VO_GOAL2_R].theta+messageParser.mHingeJointSenseMap[JID_HEAD_1].angle)<0)
			{
				if((wm.GetMyBodyAngleToBall()>0&&wm.GetMyBodyAngleToBall()<messageParser.mVisionSenseMap[VO_GOAL1_R].theta+messageParser.mHingeJointSenseMap[JID_HEAD_1].angle)||(wm.GetMyBodyAngleToBall()<0&&wm.GetMyBodyAngleToBall()>messageParser.mVisionSenseMap[VO_GOAL2_R].theta+messageParser.mHingeJointSenseMap[JID_HEAD_1].angle))
				{
					if(footWidth>0)
					{
					      footWidth-=QUICK_FOOTLENGTH_INCREAMENTwidth;
					      if(footWidth<0)
					      {
						      footWidth=0;
					      }
					}
					else
					{
						footWidth+=QUICK_FOOTLENGTH_INCREAMENTwidth;
						if(footWidth>0)
						{
						      footWidth=0;
						}
					}
					
					if(footLength<0)
					{
					      footLength+=QUICK_FOOTLENGTH_INCREAMENT;
					}
				}

			}
		}
	}
	else
	{
	      	if(messageParser.mVisionSenseMap[VO_GOAL1_L].phi!=0&&messageParser.mVisionSenseMap[VO_GOAL2_L].phi!=0)
		{
			if((messageParser.mVisionSenseMap[VO_GOAL1_L].theta+messageParser.mHingeJointSenseMap[JID_HEAD_1].angle)*(messageParser.mVisionSenseMap[VO_GOAL2_L].theta+messageParser.mHingeJointSenseMap[JID_HEAD_1].angle)<0)
			{
				if((wm.GetMyBodyAngleToBall()>0&&wm.GetMyBodyAngleToBall()<messageParser.mVisionSenseMap[VO_GOAL2_L].theta+messageParser.mHingeJointSenseMap[JID_HEAD_1].angle)||(wm.GetMyBodyAngleToBall()<0&&wm.GetMyBodyAngleToBall()>messageParser.mVisionSenseMap[VO_GOAL1_L].theta+messageParser.mHingeJointSenseMap[JID_HEAD_1].angle))
				{
					if(footWidth>0)
					{
					      footWidth-=QUICK_FOOTLENGTH_INCREAMENTwidth;
					      if(footWidth<0)
					      {
						      footWidth=0;
					      }
					}
					else
					{
						footWidth+=QUICK_FOOTLENGTH_INCREAMENTwidth;
						if(footWidth>0)
						{
						      footWidth=0;
						}
					}
					
					if(footLength<0)
					{
					      footLength+=QUICK_FOOTLENGTH_INCREAMENT;
					}
				}

			}
		}
	}
#if 0
	if(wm.isBodyInDangerousState())
	{
		if(wm.GetMyFallDirection()==D_FORWARD) //lastCyclebodyForerake=1
		{
			footLength+=SLOW_FOOTLENGTH_INCREAMENT;
			if(lastCyclebodyForerake==0)
			{
				lastCyclebodyForerake=1;
			}
			else if(lastCyclebodyForerake==-1)
			{
				if(adjustAngle>0)
					adjustAngle=-adjustAngle;
				else if(adjustAngle<0)
					adjustAngle=-3;
			}
			adjustAngle-=0.2;
			if(adjustAngle<-3)
				adjustAngle=-3;
			if(footLength>MAXSPEED)
				footLength=MAXSPEED;
			/////////////////////cout<<"	D   forward		adjust angle !!!!!  v  ="<<adjustAngle<<endl;
			
		}
		else
		{
			if(footLength>=0)			  
			    footLength-=QUICK_FOOTLENGTH_INCREAMENT;
			if(lastCyclebodyForerake==0)
			{
				lastCyclebodyForerake=-1;
			}
			else if(lastCyclebodyForerake==1)
			{
				if(adjustAngle<0)
					adjustAngle=-adjustAngle;
				else if(adjustAngle>0)
					adjustAngle=3;
			}
			adjustAngle+=0.2;
			if(adjustAngle>3)
				adjustAngle=3;
			if(footLength<-MINSPEED)
				footLength=-MINSPEED;
		/////////////////////cout<<"	D backward		adjust angle !!!!!  v  ="<<adjustAngle<<endl;
		
		}
	}
	else
	{
		lastCyclebodyForerake=0;
		if(adjustAngle>0.3)
			adjustAngle-=0.4;
		else if(adjustAngle<-0.3)
			adjustAngle+=0.4;
		else
			adjustAngle=0;
	}
#endif
}

int NewWalk::WhichFootRaised()
{
	if(firstStep)
		return 0;
	if(walkCounter>0&&walkCounter<FOOT_CYCLE-1)
	{
		if(rightStep==true)
			return 1;
		else
			return -1;
	}
	else
		return 0; 
}
 
void NewWalk::adjustMyBarycenterToProtectMyself()  //unfinished   powered by feng
{
      //float angle=GetMyAngleToBall();
      //myBodyAngleToBall=angle+GetCurrentJointAngle(JID_HEAD_1);
	float nearestOpponentDistance=9; 
	float nearestOpponentAngle=0;
	for( TPlayerSenseMap::iterator iter=messageParser.mOpponentSenseMap.begin(); iter!=messageParser.mOpponentSenseMap.end(); ++iter )
	{
		if(nearestOpponentDistance=(*iter).second.head.distance<nearestOpponentDistance)
		{
		    nearestOpponentDistance=(*iter).second.head.distance;
		    nearestOpponentAngle=(*iter).second.head.theta+wm.GetCurrentJointAngle(JID_HEAD_1);
		}
		  /////////////////cout<<"time :"<<GetCurrentGameTime()<<"		number :"<<(*iter).second.unum<<"	distance :"<<(*iter).second.head.distance<<"		angle :"
	      //<<(*iter).second.head.theta<<"	phi :"<<(*iter).second.head.phi<<endl;
	}
	///////////////cout<<"time :"<<wm.GetCurrentGameTime()<<"		distance :"<<nearestOpponentDistance<<"			body angle :"<<nearestOpponentAngle<<endl;
}
Action NewWalk::HalfStepGait(WalkDirection& walkDirection,float& angle,SpeedStrategy& currentCycleSpeedStrategy,HorizonMoveDirection& horizonMoveDirection,float& HeadTurnAngle)
{cout<<"11111111111111111"<<endl;
cout<<"11111111111111111"<<endl;
cout<<"11111111111111111"<<endl;
cout<<"11111111111111111"<<endl;
	if(hasFallDown==true)
 	{
		InitHalfStepWalkData();
 		hasFallDown=false;
		UseNewWalk=false;
    	}
 	if(UseNewWalk==true)
	{
		if(walkCounter==0&&footLength<0.02)
		{
			InitHalfStepWalkData();
			UseNewWalk=false;
		}
		else
		{
			updateTime();
			exchangeArms();
			footLength-=0.004;
			footWidth=0;
			float rr =0;
			updateTurnAngle(rr);
			turnHeadAngle=0;
			preparation();
			updatePV();
			return readNewWalkData();
		}
	}

    	if( walkCounter < 5 )
	{
		walkCounter=walkCounter++;
	}
	else
	{
		walkCounter=1;
		float increment=0.001;
		if(stepIncrement < 0.012&& currentCycleSpeedStrategy == SPEED_UP)
		{
			stepIncrement=stepIncrement+increment;
			

		}
		else if(stepIncrement > increment)
		{
			if(currentCycleSpeedStrategy == SLOW_SPEED_DOWN)
			{
				stepIncrement=stepIncrement-0.001;
			}
			else if(currentCycleSpeedStrategy == QUICK_SPEED_DOWN)
			{
				stepIncrement=stepIncrement-0.002;
			}
				//stepIncrement=stepIncrement-0.002;
		}
		
		if(stepIncrement < 0.001)
		{

			Ldistance=-0.03;
			Rdistance=-0.03;
		}
	}
	if(walkCounter < 3)
	{
		upFootHigh=(2*(minUpStepHigh-standHigh)*(walkCounter*0.02))/0.1+standHigh;
		downFootHigh=(2*(maxDownStepHigh-standHigh)*(walkCounter*0.02))/0.1+standHigh;
	}
	else
	{
		upFootHigh=(2*(standHigh-minUpStepHigh)*(walkCounter*0.02))/0.1+2*minUpStepHigh-standHigh;
		downFootHigh=(2*(standHigh-maxDownStepHigh)*(walkCounter*0.02))/0.1+2*maxDownStepHigh-standHigh;
	}
	
	if(walkDirection == WALK_FORWARD)
	{
		if(leftStep == true)
		{
			Ldistance=Ldistance+stepIncrement;
			Rdistance=Rdistance-stepIncrement;

			Lhigh=upFootHigh;
			Rhigh=downFootHigh;
	//			///////////////cout<<"1walkCounter :"<<walkCounter<<"		Ldistance :"<<Ldistance<<"	Rdistance:"<<Rdistance<<"      Lhigh :"<<Lhigh<<" 	Rhigh :"<<Rhigh<<"	stepIncrement :"<<stepIncrement<<endl;

			
		}
		else if(rightStep == true)
		{
			Ldistance=Ldistance-stepIncrement;
			Rdistance=Rdistance+stepIncrement;

			Lhigh=downFootHigh;
			Rhigh=upFootHigh;
	//			///////////////cout<<"2walkCounter :"<<walkCounter<<"		Ldistance :"<<Ldistance<<"	Rdistance:"<<Rdistance<<"      Lhigh :"<<Lhigh<<" 	Rhigh :"<<Rhigh<<"	stepIncrement :"<<stepIncrement<<endl;

		}
	}
	else if (walkDirection == WALK_BACKWARD)
	{
		if(leftStep == true)
		{
			Ldistance=Ldistance-stepIncrement;
			Rdistance=Rdistance+stepIncrement;

			Lhigh=upFootHigh;
			Rhigh=downFootHigh;
	//			///////////////cout<<"3walkCounter :"<<walkCounter<<"		Ldistance :"<<Ldistance<<"	Rdistance:"<<Rdistance<<"      Lhigh :"<<Lhigh<<" 	Rhigh :"<<Rhigh<<"	stepIncrement :"<<stepIncrement<<endl;

			
		}
		else if(rightStep == true)
		{
			Ldistance=Ldistance+stepIncrement;
			Rdistance=Rdistance-stepIncrement;

			Lhigh=downFootHigh;
			Rhigh=upFootHigh;
	//			///////////////cout<<"4walkCounter :"<<walkCounter<<"		Ldistance :"<<Ldistance<<"	Rdistance:"<<Rdistance<<"      Lhigh :"<<Lhigh<<" 	Rhigh :"<<Rhigh<<"	stepIncrement :"<<stepIncrement<<endl;

			
		}
	}
 
	/////////////////cout<<"//////////////////////////////////////////////////////////////////////////////////////"<<endl;
	if(leftStep == true && walkCounter == 5)
	{
		leftStep=false;
		rightStep=true;
	}
	else if(rightStep == true && walkCounter == 5)
	{
		leftStep=true;
		rightStep=false;
	}
	
	CalculateHorizontalMoveAngle(horizonMoveDirection);

	CalculateTurnAngle(angle);
	
	turnHeadAngle=HeadTurnAngle;
	
	return HalfStepActualize();
  
}
string NewWalk::HalfStepActualize()
{
	//cout<<"start HalfStepActualize()"<<endl;
      	double k,d,b,c,x,y,Rdatui,Rxiaotui,Ldatui,Lxiaotui;
	
	k=Rhigh*Rhigh+ShankHeight*ShankHeight+Rdistance*Rdistance-ThighHeight*ThighHeight;
	d=4.0*Rdistance*Rdistance*ShankHeight*ShankHeight+4.0*Rhigh*Rhigh*ShankHeight*ShankHeight;
	b=4.0*Rdistance*ShankHeight*k;
	c=k*k-4.0*Rhigh*Rhigh*ShankHeight*ShankHeight;
	x=(-b+sqrt(b*b-4.0*d*c))/(2.0*d);
	y=(x*ShankHeight+Rdistance)/ThighHeight;
	Rdatui=asin(y)*180/PI;
	Rxiaotui=asin(x)*180/PI+Rdatui;

	k=Lhigh*Lhigh+ShankHeight*ShankHeight+Ldistance*Ldistance-ThighHeight*ThighHeight;
	d=4.0*Ldistance*Ldistance*ShankHeight*ShankHeight+4.0*Lhigh*Lhigh*ShankHeight*ShankHeight;
	b=4.0*Ldistance*ShankHeight*k;
	c=k*k-4.0*Lhigh*Lhigh*ShankHeight*ShankHeight;
	x=(-b+sqrt(b*b-4.0*d*c))/(2.0*d);
	y=(x*ShankHeight+Ldistance)/ThighHeight;
	Ldatui=asin(y)*180/PI;
	Lxiaotui=asin(x)*180/PI+Ldatui;
	///////////////////////////////////////////
	string ss,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,srarm1,slarm1,srarm2,slarm2,srarm3,slarm3,srarm4,slarm4;
	float angHead1,angHead2;
	float angLleg1,angLleg2,angLleg3,angLleg4,angLleg5,angLleg6;
	float angRleg1,angRleg2,angRleg3,angRleg4,angRleg5,angRleg6;
	float angLarm1,angLarm2,angLarm3,angLarm4;
	float angRarm1,angRarm2,angRarm3,angRarm4;
	
	Record_Received_JointSense();	///记录曾经收到的server发送的消息
	
	if(firstReadDate==true)
	{
		firstReadDate =false;
		IsFirstinReadData = true;
		CountinReadData = 0;

		angHead1 = messageParser.mHingeJointSenseMap[JID_HEAD_1].angle;
		angHead2 = messageParser.mHingeJointSenseMap[JID_HEAD_2].angle;
		
		angLleg1 = messageParser.mHingeJointSenseMap[JID_LLEG_1].angle;
		angLleg2 = messageParser.mHingeJointSenseMap[JID_LLEG_2].angle;
		angLleg3 = messageParser.mHingeJointSenseMap[JID_LLEG_3].angle;
		angLleg4 = messageParser.mHingeJointSenseMap[JID_LLEG_4].angle;
		angLleg5 = messageParser.mHingeJointSenseMap[JID_LLEG_5].angle;
		angLleg6 = messageParser.mHingeJointSenseMap[JID_LLEG_6].angle;
		
		angRleg1 = messageParser.mHingeJointSenseMap[JID_RLEG_1].angle;
		angRleg2 = messageParser.mHingeJointSenseMap[JID_RLEG_2].angle;
		angRleg3 = messageParser.mHingeJointSenseMap[JID_RLEG_3].angle;
		angRleg4 = messageParser.mHingeJointSenseMap[JID_RLEG_4].angle;
		angRleg5 = messageParser.mHingeJointSenseMap[JID_RLEG_5].angle;
		angRleg6 = messageParser.mHingeJointSenseMap[JID_RLEG_6].angle;
		
		angLarm1 = messageParser.mHingeJointSenseMap[JID_LARM_1].angle;
		angLarm2 = messageParser.mHingeJointSenseMap[JID_LARM_2].angle;
		angLarm3 = messageParser.mHingeJointSenseMap[JID_LARM_3].angle;
		angLarm4 = messageParser.mHingeJointSenseMap[JID_LARM_4].angle;
		
		angRarm1 = messageParser.mHingeJointSenseMap[JID_RARM_1].angle;
		angRarm2 = messageParser.mHingeJointSenseMap[JID_RARM_2].angle;
		angRarm3 = messageParser.mHingeJointSenseMap[JID_RARM_3].angle;
		angRarm4 = messageParser.mHingeJointSenseMap[JID_RARM_4].angle;
		///////////////cout<<"first read data time :"<<wm.GetCurrentGameTime()<<endl;
	}
	else
	{
		angHead1 = Forecast_mHingeJointSenseMap[JID_HEAD_1].angle;
		angHead2 = Forecast_mHingeJointSenseMap[JID_HEAD_2].angle;
	
		angLleg1 = Forecast_mHingeJointSenseMap[JID_LLEG_1].angle;
		angLleg2 = Forecast_mHingeJointSenseMap[JID_LLEG_2].angle;
		angLleg3 = Forecast_mHingeJointSenseMap[JID_LLEG_3].angle;
		angLleg4 = Forecast_mHingeJointSenseMap[JID_LLEG_4].angle;
		angLleg5 = Forecast_mHingeJointSenseMap[JID_LLEG_5].angle;
		angLleg6 = Forecast_mHingeJointSenseMap[JID_LLEG_6].angle;
	
		angRleg1 = Forecast_mHingeJointSenseMap[JID_RLEG_1].angle;
		angRleg2 = Forecast_mHingeJointSenseMap[JID_RLEG_2].angle;
		angRleg3 = Forecast_mHingeJointSenseMap[JID_RLEG_3].angle;
		angRleg4 = Forecast_mHingeJointSenseMap[JID_RLEG_4].angle;
		angRleg5 = Forecast_mHingeJointSenseMap[JID_RLEG_5].angle;
		angRleg6 = Forecast_mHingeJointSenseMap[JID_RLEG_6].angle;
	
		angLarm1 = Forecast_mHingeJointSenseMap[JID_LARM_1].angle;
		angLarm2 = Forecast_mHingeJointSenseMap[JID_LARM_2].angle;
		angLarm3 = Forecast_mHingeJointSenseMap[JID_LARM_3].angle;
		angLarm4 = Forecast_mHingeJointSenseMap[JID_LARM_4].angle;
	
		angRarm1 = Forecast_mHingeJointSenseMap[JID_RARM_1].angle;
		angRarm2 = Forecast_mHingeJointSenseMap[JID_RARM_2].angle;
		angRarm3 = Forecast_mHingeJointSenseMap[JID_RARM_3].angle;
		angRarm4 = Forecast_mHingeJointSenseMap[JID_RARM_4].angle;
	}


	if(i_SendedCount==3)
	{
		Delay_mHingeJointSenseMap[JID_HEAD_1].angle = Received_mHingeJointSenseMap3[JID_HEAD_1].angle-Sended_mHingeJointSenseMap2[JID_HEAD_1].angle;
		Delay_mHingeJointSenseMap[JID_HEAD_2].angle = Received_mHingeJointSenseMap3[JID_HEAD_2].angle-Sended_mHingeJointSenseMap2[JID_HEAD_2].angle;

		Delay_mHingeJointSenseMap[JID_LARM_1].angle = Received_mHingeJointSenseMap3[JID_LARM_1].angle-Sended_mHingeJointSenseMap2[JID_LARM_1].angle;
		Delay_mHingeJointSenseMap[JID_LARM_2].angle = Received_mHingeJointSenseMap3[JID_LARM_2].angle-Sended_mHingeJointSenseMap2[JID_LARM_2].angle;
		Delay_mHingeJointSenseMap[JID_LARM_3].angle = Received_mHingeJointSenseMap3[JID_LARM_3].angle-Sended_mHingeJointSenseMap2[JID_LARM_3].angle;
		Delay_mHingeJointSenseMap[JID_LARM_4].angle = Received_mHingeJointSenseMap3[JID_LARM_4].angle-Sended_mHingeJointSenseMap2[JID_LARM_4].angle;

		Delay_mHingeJointSenseMap[JID_RARM_1].angle = Received_mHingeJointSenseMap3[JID_RARM_1].angle-Sended_mHingeJointSenseMap2[JID_RARM_1].angle;
		Delay_mHingeJointSenseMap[JID_RARM_2].angle = Received_mHingeJointSenseMap3[JID_RARM_2].angle-Sended_mHingeJointSenseMap2[JID_RARM_2].angle;
		Delay_mHingeJointSenseMap[JID_RARM_3].angle = Received_mHingeJointSenseMap3[JID_RARM_3].angle-Sended_mHingeJointSenseMap2[JID_RARM_3].angle;
		Delay_mHingeJointSenseMap[JID_RARM_4].angle = Received_mHingeJointSenseMap3[JID_RARM_4].angle-Sended_mHingeJointSenseMap2[JID_RARM_4].angle;

		Delay_mHingeJointSenseMap[JID_LLEG_1].angle = Received_mHingeJointSenseMap3[JID_LLEG_1].angle-Sended_mHingeJointSenseMap2[JID_LLEG_1].angle;
		Delay_mHingeJointSenseMap[JID_LLEG_2].angle = Received_mHingeJointSenseMap3[JID_LLEG_2].angle-Sended_mHingeJointSenseMap2[JID_LLEG_2].angle;
		Delay_mHingeJointSenseMap[JID_LLEG_3].angle = Received_mHingeJointSenseMap3[JID_LLEG_3].angle-Sended_mHingeJointSenseMap2[JID_LLEG_3].angle;
		Delay_mHingeJointSenseMap[JID_LLEG_4].angle = Received_mHingeJointSenseMap3[JID_LLEG_4].angle-Sended_mHingeJointSenseMap2[JID_LLEG_4].angle;
		Delay_mHingeJointSenseMap[JID_LLEG_5].angle = Received_mHingeJointSenseMap3[JID_LLEG_5].angle-Sended_mHingeJointSenseMap2[JID_LLEG_5].angle;
		Delay_mHingeJointSenseMap[JID_LLEG_6].angle = Received_mHingeJointSenseMap3[JID_LLEG_6].angle-Sended_mHingeJointSenseMap2[JID_LLEG_6].angle;

		Delay_mHingeJointSenseMap[JID_RLEG_1].angle = Received_mHingeJointSenseMap3[JID_RLEG_1].angle-Sended_mHingeJointSenseMap2[JID_RLEG_1].angle;
		Delay_mHingeJointSenseMap[JID_RLEG_2].angle = Received_mHingeJointSenseMap3[JID_RLEG_2].angle-Sended_mHingeJointSenseMap2[JID_RLEG_2].angle;
		Delay_mHingeJointSenseMap[JID_RLEG_3].angle = Received_mHingeJointSenseMap3[JID_RLEG_3].angle-Sended_mHingeJointSenseMap2[JID_RLEG_3].angle;
		Delay_mHingeJointSenseMap[JID_RLEG_4].angle = Received_mHingeJointSenseMap3[JID_RLEG_4].angle-Sended_mHingeJointSenseMap2[JID_RLEG_4].angle;
		Delay_mHingeJointSenseMap[JID_RLEG_5].angle = Received_mHingeJointSenseMap3[JID_RLEG_5].angle-Sended_mHingeJointSenseMap2[JID_RLEG_5].angle;
		Delay_mHingeJointSenseMap[JID_RLEG_6].angle = Received_mHingeJointSenseMap3[JID_RLEG_6].angle-Sended_mHingeJointSenseMap2[JID_RLEG_6].angle;

	}
	else
		Delay_mHingeJointSenseMap.clear();


	if(IsFirstinReadData)
	{
		Delay_mHingeJointSenseMap.clear();
		CountinReadData++;
		if(CountinReadData>=10)
			IsFirstinReadData = false;
	}

	/*Head1a=turnHeadAngle-angHead1-Delay_mHingeJointSenseMap[JID_HEAD_1].angle;
	Head2a=-45-angHead2-Delay_mHingeJointSenseMap[JID_HEAD_2].angle;

	Larm1a=-90-angLarm1-Delay_mHingeJointSenseMap[JID_LARM_1].angle;
	Larm2a=5-angLarm2-Delay_mHingeJointSenseMap[JID_LARM_2].angle;
	Larm3a=-90-angLarm3-Delay_mHingeJointSenseMap[JID_LARM_3].angle;
	Larm4a=-30-angLarm4-Delay_mHingeJointSenseMap[JID_LARM_4].angle;

	Rarm1a=-90-angRarm1-Delay_mHingeJointSenseMap[JID_RARM_1].angle ;
	Rarm2a=-5-angRarm2-Delay_mHingeJointSenseMap[JID_RARM_2].angle;
	Rarm3a=90-angRarm3-Delay_mHingeJointSenseMap[JID_RARM_3].angle;
	Rarm4a=30-angRarm4-Delay_mHingeJointSenseMap[JID_RARM_4].angle;
	
	Lleg1a=turnLeftAngle-angLleg1-Delay_mHingeJointSenseMap[JID_LLEG_1].angle ;
	Lleg2a=leftCoxaAngle-angLleg2-Delay_mHingeJointSenseMap[JID_LLEG_2].angle;
	Lleg3a=Ldatui-angLleg3-Delay_mHingeJointSenseMap[JID_LLEG_3].angle+stepIncrement*250;
	Lleg4a=-Lxiaotui-angLleg4-Delay_mHingeJointSenseMap[JID_LLEG_4].angle+stepIncrement*150;
	Lleg5a=Lxiaotui-Ldatui-angLleg5-Delay_mHingeJointSenseMap[JID_LLEG_5].angle;
	Lleg6a=leftAnkleAngle-angLleg6-Delay_mHingeJointSenseMap[JID_LLEG_6].angle;

	Rleg1a=turnRightAngle-angRleg1-Delay_mHingeJointSenseMap[JID_RLEG_1].angle;
	Rleg2a=rightCoxaAngle-angRleg2-Delay_mHingeJointSenseMap[JID_RLEG_2].angle;
	Rleg3a=Rdatui-angRleg3-Delay_mHingeJointSenseMap[JID_RLEG_3].angle+stepIncrement*250;
	Rleg4a=-Rxiaotui-angRleg4-Delay_mHingeJointSenseMap[JID_RLEG_4].angle+stepIncrement*150;
	Rleg5a=Rxiaotui-Rdatui-angRleg5-Delay_mHingeJointSenseMap[JID_RLEG_5].angle;
	Rleg6a=rightAnkleAngle-angRleg6-Delay_mHingeJointSenseMap[JID_RLEG_6].angle;
	////////////////////////////////////////////////////////////////////////
	Forecast_mHingeJointSenseMap[JID_LLEG_1].angle=turnLeftAngle;
	Forecast_mHingeJointSenseMap[JID_LLEG_2].angle=leftCoxaAngle;
	Forecast_mHingeJointSenseMap[JID_LLEG_3].angle=Ldatui+stepIncrement*250;
	Forecast_mHingeJointSenseMap[JID_LLEG_4].angle= -Lxiaotui+stepIncrement*150;
	Forecast_mHingeJointSenseMap[JID_LLEG_5].angle=Lxiaotui-Ldatui;
	Forecast_mHingeJointSenseMap[JID_LLEG_6].angle=leftAnkleAngle;
	
	Forecast_mHingeJointSenseMap[JID_RLEG_1].angle=turnRightAngle;
	Forecast_mHingeJointSenseMap[JID_RLEG_2].angle=rightCoxaAngle;
	Forecast_mHingeJointSenseMap[JID_RLEG_3].angle=Rdatui+stepIncrement*250;
	Forecast_mHingeJointSenseMap[JID_RLEG_4].angle= -Rxiaotui+stepIncrement*150;
	Forecast_mHingeJointSenseMap[JID_RLEG_5].angle=Rxiaotui-Rdatui;
	Forecast_mHingeJointSenseMap[JID_RLEG_6].angle=rightAnkleAngle;

	Forecast_mHingeJointSenseMap[JID_HEAD_1].angle=turnHeadAngle;
	Forecast_mHingeJointSenseMap[JID_HEAD_2].angle=-45;

	Forecast_mHingeJointSenseMap[JID_LARM_1].angle=-90;
	Forecast_mHingeJointSenseMap[JID_LARM_2].angle=5;
	Forecast_mHingeJointSenseMap[JID_LARM_3].angle=-90;
	Forecast_mHingeJointSenseMap[JID_LARM_4].angle=-30;
	
	Forecast_mHingeJointSenseMap[JID_RARM_1].angle=-90;
	Forecast_mHingeJointSenseMap[JID_RARM_2].angle=-5;
	Forecast_mHingeJointSenseMap[JID_RARM_3].angle=90;
	Forecast_mHingeJointSenseMap[JID_RARM_4].angle=30;
	
		Record_Sended_JointSense();	///记录 Agent 发送的消息
	if(abs(Lleg3a) > 7.0354)
	{
		if(Lleg3a > 0)
			Lleg3a = 7.1;
		else
			Lleg3a = -7.1;
	}

	if(abs(Lleg4a) > 7.0354)
	{
		if(Lleg4a > 0)
			Lleg4a = 7.1;
		else
			Lleg4a = -7.1;
	}

	if(abs(Lleg5a) > 7.0354)
	{
		if(Lleg5a > 0)
			Lleg5a = 7.1;
		else
			Lleg5a = -7.1;
	}

	if(abs(Rleg3a) > 7.0354)
	{
		if(Rleg3a > 0)
			Rleg3a = 7.1;
		else
			Rleg3a = -7.1;
	}

	if(abs(Rleg4a) > 7.0354)
	{
		if(Rleg4a > 0)
			Rleg4a = 7.1;
		else
			Rleg4a = -7.1;
	}

	if(abs(Rleg5a) > 7.0354)
	{
		if(Rleg5a > 0)
			Rleg5a = 7.1;
		else
			Rleg5a = -7.1;
	}

			sHead1=mp.HJHead_1Rad(Head1a*PI/180*50);
			sHead2=mp.HJHead_2Rad(Head2a*PI/180*50);
			slarm1=mp.HJLarm_1Rad(Larm1a*PI/180*50);
			slarm2=mp.HJLarm_2Rad(Larm2a*PI/180*50);
			slarm3=mp.HJLarm_3Rad(Larm3a*PI/180*50);
			slarm4=mp.HJLarm_4Rad(Larm4a*PI/180*50);
			s1=mp.HJLleg_1Rad(Lleg1a*PI/180*50);
			s2=mp.HJLleg_2Rad(Lleg2a*PI/180*50);
			s3=mp.HJLleg_3Rad(Lleg3a*PI/180*50);
			s4=mp.HJLleg_4Rad(Lleg4a*PI/180*50);
			s5=mp.HJLleg_5Rad(Lleg5a*PI/180*50);
			s6=mp.HJLleg_6Rad(Lleg6a*PI/180*50);
			srarm1=mp.HJRarm_1Rad(Rarm1a*PI/180*50);
			srarm2=mp.HJRarm_2Rad(Rarm2a*PI/180*50);
			srarm3=mp.HJRarm_3Rad(Rarm3a*PI/180*50);
			srarm4=mp.HJRarm_4Rad(Rarm4a*PI/180*50);
			s7=mp.HJRleg_1Rad(Rleg1a*PI/180*50);
			s8=mp.HJRleg_2Rad(Rleg2a*PI/180*50);
			s9=mp.HJRleg_3Rad(Rleg3a*PI/180*50);
			s10=mp.HJRleg_4Rad(Rleg4a*PI/180*50);
			s11=mp.HJRleg_5Rad(Rleg5a*PI/180*50);
			s12=mp.HJRleg_6Rad(Rleg6a*PI/180*50);
	ss=sHead1+sHead2+s1+s2+s3+s4+s5+s6+s7+s8+s9+s10+s11+s12+slarm1+srarm1+slarm2+srarm2+slarm3+srarm3+slarm4+srarm4;
*/
	//cout<<"end HalfStepActualize()"<<endl;
	return ss;
}
void NewWalk::Record_Sended_JointSense()///预测将要达到的角度
{
	if(i_SendedCount==0)
		Sended_mHingeJointSenseMap1 = Forecast_mHingeJointSenseMap;
	else if(i_SendedCount==1)
		Sended_mHingeJointSenseMap2 = Forecast_mHingeJointSenseMap;
	else if(i_SendedCount==2)
		Sended_mHingeJointSenseMap3 = Forecast_mHingeJointSenseMap;
	else if(i_SendedCount==3)
	{
		Sended_mHingeJointSenseMap1 = Sended_mHingeJointSenseMap2;
		Sended_mHingeJointSenseMap2 = Sended_mHingeJointSenseMap3;
		Sended_mHingeJointSenseMap3 = Forecast_mHingeJointSenseMap;
	}
	i_SendedCount++;
	if(i_SendedCount==5)
	{
		i_SendedCount=0;
		Sended_mHingeJointSenseMap1.clear();
		Sended_mHingeJointSenseMap2.clear();
		Sended_mHingeJointSenseMap3.clear();
	}
}


void NewWalk::Record_Received_JointSense()
{
	mHingeJointSenseMap=messageParser.GetCurrentJointMap();
	if(i_ReceivedCount==0)
		Received_mHingeJointSenseMap1 = mHingeJointSenseMap;
	else if(i_ReceivedCount==1)
		Received_mHingeJointSenseMap2 = mHingeJointSenseMap;
	else if(i_ReceivedCount==2)
		Received_mHingeJointSenseMap3 = mHingeJointSenseMap;
	else if(i_ReceivedCount==3)
	{
		Received_mHingeJointSenseMap1 = Received_mHingeJointSenseMap2;
		Received_mHingeJointSenseMap2 = Received_mHingeJointSenseMap3;
		Received_mHingeJointSenseMap3 = mHingeJointSenseMap;
	}
	i_ReceivedCount++;
	if(i_ReceivedCount==5)
	{
		i_ReceivedCount=0;
		Received_mHingeJointSenseMap1.clear();
		Received_mHingeJointSenseMap2.clear();
		Received_mHingeJointSenseMap3.clear();
	}
}
void NewWalk::CalculateTurnAngle(float& angle)
{
	float slowTurnIncrement=1;//0.4
	float quickTurnIncrement=1.5;//0.96
	float slowTurnMinAngle=-5;//-2.4
	float quickTurnMinAngle=-7.5;//-4.8
	
	if(footLength>=1.55)
	{
		slowTurnIncrement=0.4;
			 quickTurnIncrement=0.96;
			 slowTurnMinAngle=-2.4;
		 quickTurnMinAngle=-4.8;
	}
	if(fabs(angle)>20)
	{
		turnSlowly=false;
		turnQuickly=true;
	}
	else
	{
		turnSlowly=true;
		turnQuickly=false;
	}
	
	if(leftStep == true)//put up the left foot
	{
		if( fabs(angle) <= 5 )
		{
			//if(fabs(footLength)<=0.04)
			{
			turnLeftAngle=0+turnLeftAngle;
			turnRightAngle=turnLeftAngle;
			}
		}
		else if(angle < 0)//turn to right
		{	
			if(turnSlowly == true)
			{
				if(turnLeftAngle <= 0)
					turnLeftAngle=turnLeftAngle+slowTurnIncrement;
			
				turnRightAngle=turnLeftAngle;
			}
			else if(turnQuickly == true)
			{
				if(turnLeftAngle <= 0)
					turnLeftAngle=turnLeftAngle+quickTurnIncrement;
			
				turnRightAngle=turnLeftAngle;
			}
		}
		else//turn to left
		{
			if(turnSlowly == true)
			{
				if(turnRightAngle >= slowTurnMinAngle)
					turnRightAngle=turnRightAngle-slowTurnIncrement;
			
				turnLeftAngle=turnRightAngle;
			}
			else if(turnQuickly == true)
			{
				if(turnRightAngle >= quickTurnMinAngle)
					turnRightAngle=turnRightAngle-quickTurnIncrement;
			
				turnLeftAngle=turnRightAngle;
			}
		}
	}
	else if(rightStep == true)//put up the right foot
	{
		if( fabs(angle) <= 5 )
		{//if(fabs(footLength)<=0.04l )
		{
			turnLeftAngle=turnLeftAngle+0;
			turnRightAngle=turnLeftAngle;}
		}
		else if(angle < 0)//turn to right
		{	
			if(turnSlowly == true)
			{
				if(turnLeftAngle >= slowTurnMinAngle)
					turnLeftAngle=turnLeftAngle-slowTurnIncrement;
			
				turnRightAngle=turnLeftAngle;
			}
			else if(turnQuickly == true)
			{
				if(turnLeftAngle >= quickTurnMinAngle)
					turnLeftAngle=turnLeftAngle-quickTurnIncrement;
			
				turnRightAngle=turnLeftAngle;
			}
		}
		else//turn to left
		{
			if(turnSlowly == true)
			{
				if(turnRightAngle <= 0)
					turnRightAngle=turnRightAngle+slowTurnIncrement;
			
				turnLeftAngle=turnRightAngle;
			}
			else if(turnQuickly == true)
			{
				if(turnRightAngle <= 0)
					turnRightAngle=turnRightAngle+quickTurnIncrement;
			
				turnLeftAngle=turnRightAngle;
			}
		}
	}
}

void NewWalk::CalculateHorizontalMoveAngle(HorizonMoveDirection& horizonMoveDirection)
{	
	float maxAngle=10;
	float increment=maxAngle/5;
	if(leftStep == true)
	{
		if(horizonMoveDirection== HORIZONMOVE_LEFT )
		{
			rightCoxaAngle=rightCoxaAngle-increment;
			if( rightCoxaAngle<-maxAngle )
				rightCoxaAngle=-maxAngle;
			
			leftCoxaAngle=leftCoxaAngle+increment;
			if( leftCoxaAngle>maxAngle )
				leftCoxaAngle=maxAngle;
			
			rightAnkleAngle=rightAnkleAngle+increment;
			if( rightAnkleAngle>maxAngle )
				rightAnkleAngle=maxAngle;
			
			leftAnkleAngle=leftAnkleAngle-increment;
			if( leftAnkleAngle<-maxAngle )
				leftAnkleAngle=-maxAngle;
		}
		else if( horizonMoveDirection== HORIZONMOVE_RIGHT )
		{
			rightCoxaAngle=rightCoxaAngle+increment;
			if( rightCoxaAngle>0 )
				rightCoxaAngle=0;
			
			leftCoxaAngle=leftCoxaAngle-increment;
			if( leftCoxaAngle<0 )
				leftCoxaAngle=0;
			
			rightAnkleAngle=rightAnkleAngle-increment;
			if( rightAnkleAngle<0 )
				rightAnkleAngle=0;
			
			leftAnkleAngle=leftAnkleAngle+increment;
			if( leftAnkleAngle>0 )
				leftAnkleAngle=0;
		}
		else
		{
			rightCoxaAngle=0;
			leftCoxaAngle=0;
			rightAnkleAngle=0;
			leftAnkleAngle=0;
		}
	}
	else if (rightStep == true)
	{
		if( horizonMoveDirection== HORIZONMOVE_LEFT )
		{
			rightCoxaAngle=rightCoxaAngle+increment;
			if( rightCoxaAngle>0 )
				rightCoxaAngle=0;
			
			leftCoxaAngle=leftCoxaAngle-increment;
			if( leftCoxaAngle<0 )
				leftCoxaAngle=0;
			
			rightAnkleAngle=rightAnkleAngle-increment;
			if( rightAnkleAngle<0 )
				rightAnkleAngle=0;
			
			leftAnkleAngle=leftAnkleAngle+increment;
			if( leftAnkleAngle>0 )
				leftAnkleAngle=0;
		}
		else if( horizonMoveDirection== HORIZONMOVE_RIGHT)
		{
			rightCoxaAngle=rightCoxaAngle-increment;
			if( rightCoxaAngle<-maxAngle )
				rightCoxaAngle=-maxAngle;
			
			leftCoxaAngle=leftCoxaAngle+increment;
			if( leftCoxaAngle>maxAngle )
				leftCoxaAngle=maxAngle;
			
			rightAnkleAngle=rightAnkleAngle+increment;
			if( rightAnkleAngle>maxAngle )
				rightAnkleAngle=maxAngle;
			
			leftAnkleAngle=leftAnkleAngle-increment;
			if( leftAnkleAngle<-maxAngle )
				leftAnkleAngle=-maxAngle;
		}
		else
		{
			rightCoxaAngle=0;
			leftCoxaAngle=0;
			rightAnkleAngle=0;
			leftAnkleAngle=0;
		}
	}
}


Action NewWalk::prepareForShoot_HalfStep(int footSelect)
{
	if( walkCounter < 5 )
	{
	      walkCounter++;
	}
	else
	{
		walkCounter=1;
		float increment=0.001;
		if(stepIncrement < 0.012&&wm.GetMyDistanceToBall()>0.33)
		{
		      stepIncrement=stepIncrement+increment;
		}
		else if(stepIncrement > increment)
		{
			    stepIncrement=stepIncrement-0.002;
		}
		if(stepIncrement < 0.0016)
		{
		    stepIncrement=0.0016;
		}
	}
	
	if(walkCounter < 3)
	{
		upFootHigh=(2*(minUpStepHigh-standHigh)*(walkCounter*0.02))/0.1+standHigh;
		downFootHigh=(2*(maxDownStepHigh-standHigh)*(walkCounter*0.02))/0.1+standHigh;
	}
	else
	{
		upFootHigh=(2*(standHigh-minUpStepHigh)*(walkCounter*0.02))/0.1+2*minUpStepHigh-standHigh;
		downFootHigh=(2*(standHigh-maxDownStepHigh)*(walkCounter*0.02))/0.1+2*maxDownStepHigh-standHigh;
	}

	if(leftStep == true)
	{
		Ldistance=Ldistance+stepIncrement;
		Rdistance=Rdistance-stepIncrement;

		Lhigh=upFootHigh;
		Rhigh=downFootHigh;
	}
	else if(rightStep == true)
	{
		Ldistance=Ldistance-stepIncrement;
		Rdistance=Rdistance+stepIncrement;

		Lhigh=downFootHigh;
		Rhigh=upFootHigh;
//			/////////////////cout<<"2walkCounter :"<<walkCounter<<"		Ldistance :"<<Ldistance<<"	Rdistance:"<<Rdistance<<"      Lhigh :"<<Lhigh<<" 	Rhigh :"<<Rhigh<<"	stepIncrement :"<<stepIncrement<<endl;
	}
	if(leftStep == true && walkCounter == 5)
	{
		leftStep=false;
		rightStep=true;
	}
	else if(rightStep == true && walkCounter == 5)
	{
		leftStep=true;
		rightStep=false;
	}
	float angle =0;
	HorizonMoveDirection horizonMoveDirection;
	if(footSelect==1)
	{
	      angle=wm.GetMyAngleToBall()+4;
	}
	else
	{
		angle=wm.GetMyAngleToBall()-4;
	}
	if(wm.GetMyDistanceToBall()<0.3)
	{
		if(wm.GetMyTeamIndex() == TI_LEFT)
		{
			if(wm.GetMyAngleToFlag(VO_GOAL1_R)<0&&wm.GetMyAngleToFlag(VO_GOAL2_R)<0)
			{
				float temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_R)-wm.GetMyAngleToFlag(VO_GOAL2_R))/2;
				angle=wm.GetMyAngleToFlag(VO_GOAL1_R)-temp;
			}
			else if(wm.GetMyAngleToFlag(VO_GOAL1_R)>0&&wm.GetMyAngleToFlag(VO_GOAL2_R)>0)
			{
				float temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_R)-wm.GetMyAngleToFlag(VO_GOAL2_R))/2;
				angle=wm.GetMyAngleToFlag(VO_GOAL1_R)+temp;
			}
			else
			{
				float temp=(wm.GetMyAngleToFlag(VO_GOAL1_R)-wm.GetMyAngleToFlag(VO_GOAL2_R))/2;
				angle=wm.GetMyAngleToFlag(VO_GOAL1_R)-temp;
			}
		}
		else
		{
			if(wm.GetMyAngleToFlag(VO_GOAL1_L)<0&&wm.GetMyAngleToFlag(VO_GOAL2_L)<0)
			{
				float temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_L)-wm.GetMyAngleToFlag(VO_GOAL2_L))/2;
				angle=wm.GetMyAngleToFlag(VO_GOAL1_R)-temp;
			}
			else if(wm.GetMyAngleToFlag(VO_GOAL1_L)>0&&wm.GetMyAngleToFlag(VO_GOAL2_L)>0)
			{
				float temp=fabs(wm.GetMyAngleToFlag(VO_GOAL1_L)-wm.GetMyAngleToFlag(VO_GOAL2_L))/2;
				angle=wm.GetMyAngleToFlag(VO_GOAL1_R)+temp;
			}
			else
			{
				float temp=(wm.GetMyAngleToFlag(VO_GOAL1_L)-wm.GetMyAngleToFlag(VO_GOAL2_L))/2;
				angle=wm.GetMyAngleToFlag(VO_GOAL1_R)-temp;
			}
		}

		if(wm.GetMyAngleToBall()>0)
		{
			if(wm.GetMyAngleToBall()>10.5)
			{
				horizonMoveDirection=HORIZONMOVE_LEFT;
				///////////////cout<<"time :"<<wm.GetCurrentGameTime()<<"	move right"<<endl;
			}
			else if(wm.GetMyAngleToBall()<4)
			{
				horizonMoveDirection=HORIZONMOVE_RIGHT;
				///////////////cout<<"time :"<<wm.GetCurrentGameTime()<<"	move left"<<endl;

			}
			else
				horizonMoveDirection=HORIZONMOVE_NULL;
		}
		else
		{
			if(wm.GetMyAngleToBall()<-10.5)
			{
				horizonMoveDirection=HORIZONMOVE_RIGHT;
				/////////////cout<<"time :"<<wm.GetCurrentGameTime()<<"	move left"<<endl;

			}
			else if(wm.GetMyAngleToBall()>-4)
			{
				horizonMoveDirection=HORIZONMOVE_LEFT;
				/////////////cout<<"time :"<<wm.GetCurrentGameTime()<<"	move right"<<endl;

			}
			else
				horizonMoveDirection=HORIZONMOVE_NULL;
		}
	}
	CalculateHorizontalMoveAngle(horizonMoveDirection);
	CalculateTurnAngle(angle);
	turnHeadAngle=0;
	return HalfStepActualize();
}

Action NewWalk::PassBall(PassDirection passDirection)
{
     	  if(hasFallDown==true)
  	{
  		InitNewWalkData();
  		hasFallDown=false;
     	}
        updateTime();
	turnHeadAngle=0;
	float speed;
	if(passDirection==PASS_FRONT)
	    speed =0.075;
	else speed=0.06;
	turnAngle=wm.GetMyAngleToBall();
	if(passDirection!=PASS_HORIZ)
	{
		if(footWidth>0)
		{
			footWidth-=0.004;
			if(footWidth<0)
			    footWidth=0;
		}
		else if(footWidth<0)
		{
			footWidth+=0.004;
			if(footWidth>0)
			    footWidth=0;
		}
	}
	if(passDirection!=PASS_HORIZ&&passDirection!=PASS_BACK){
		if(wm.GetMyDistanceToBall()<=(0.33+0.32*(lastCycleFootLength/0.16)))
		{
			if(footLength>speed)
			{
			      footLength=footLength-0.0035;
			      if(footLength<=speed)
				      footLength=speed;
			}
			else if(footLength<speed)
			{
			      if(footLength<0.03)
			      {
				  footLength+=SLOW_FOOTLENGTH_INCREAMENT;
			      }
			      else
			      {	
				    footLength+=SLOW_FOOTLENGTH_INCREAMENT/2;
				      if(footLength>speed)
					footLength=speed;
			      }
			}
			if(passDirection==PASS_LEFT_FRONT||passDirection==PASS_RIGHT_FRONT||passDirection==PASS_RIGHT_FRONT_LESS_STRENGTH||passDirection==PASS_LEFT_FRONT_LESS_STRENGTH)
			{
				if(wm.GetMyAngleToBall()>0){
					if(wm.GetMyAngleToBall()>5)
					{
						float width=fabs(wm.GetMyDistanceToBall()*sin(wm.GetMyAngleToBall()))-0.0225;
						if(width<0)
							footWidth=0;
						else if(width<=0.05)
							footWidth=-width;
						else
							footWidth=-0.05;
					}
					else
					  footWidth=0;
				}
				else{
					if(wm.GetMyAngleToBall()<-5)
					{
						float width=fabs(wm.GetMyDistanceToBall()*sin(wm.GetMyAngleToBall()))-0.0225;
						if(width<0)
							footWidth=0;
						else if(width<=0.05)
							footWidth=width;
						else
							footWidth=0.05;
					}
					else
					  footWidth=0;
				}		
			}
		}
		else
		{
			if(footLength<0.16)
			{
			  footLength+=0.003;
			  if(footLength>0.16)
			    footLength=0.16;
			}
			else
			{
			      footLength-=0.003;
			}		
		}
	}

#if 1
	if(passDirection==PASS_HORIZ)
	{
		turnHeadAngle=wm.GetMyAngleToBall()+messageParser.mHingeJointSenseMap[JID_HEAD_1].angle;
		turnAngle=wm.GetMyBodyAngleToBall();
		if(wm.GetMyDistanceToBall()<1.5)
		{
			if(wm.GetMyBodyAngleToBall()>0)
			{
				turnAngle=wm.GetMyBodyAngleToBall()-78;
				if(wm.GetMyDistanceToBall()<0.6)
				{
				      if(footWidth<-0.06)
				      {
					  footWidth+=SLOW_FOOTLENGTH_INCREAMENT*2;
				      }
				      else 
					footWidth-=SLOW_FOOTLENGTH_INCREAMENT*1.5;
				}
				else
				{
				      if(footWidth>-0.11)
					   footWidth-=SLOW_FOOTLENGTH_INCREAMENT*1.5;
				      else
					  footWidth=-0.11;
				}
			}
			else
			{
				turnAngle=wm.GetMyBodyAngleToBall()+78;
				if(wm.GetMyDistanceToBall()<0.6)
				{
				      if(footWidth>0.06)
				      {
					  footWidth-=SLOW_FOOTLENGTH_INCREAMENT*2;
				      }
				      else 
					footWidth+=SLOW_FOOTLENGTH_INCREAMENT*1.5;
				}
				else
				{
				      if(footWidth<0.11)
					   footWidth+=SLOW_FOOTLENGTH_INCREAMENT*1.5;
				      else
					  footWidth=0.11;
				}
			}
			footLength-=0.004;
			if(footLength<0)
			  footLength=0;
			///////////cout<<"turn angle ::"<<turnAngle<<endl;
		}
		else
		{
			footLength+=0.004;
			if(footLength>0.12)
			  footLength=0.12;
	
		}
		
		if(wm.GetMyDistanceToBall()<0.2&&walkCounter==0)
		{
			if((wm.GetMyBodyAngleToBall()>0&&leftStep)||(wm.GetMyBodyAngleToBall()<0&&rightStep))
			nowForPass2=true;
			///////////cout<<"horiz pass!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
		}
	}
#endif
#if 1
	if(passDirection==PASS_FRONT)
	{
		if(walkCounter==0&&wm.GetMyDistanceToBall()<=(0.23+footLength*0.45)&&fabs(wm.GetMyAngleToBall())<10)//&s&rightStep)//counterr==12)//)
		{
 			if(wm.GetMyBodyAngleToBall()>0&&leftStep||wm.GetMyBodyAngleToBall()<0&&rightStep)
 			{
			    //  /////////cout<<"i will pass ball,my  distance to ball :"<<wm.GetMyDistanceToBall()<<endl;
			      nowForPass=true;
			      footLength=0.18;
			}
			//havePassed=true;
		}
	}
#endif
#if 1
	if(passDirection==PASS_BACK)
	{
		turnHeadAngle=0;//wm.GetMyAngleToBall()+messageParser.mHingeJointSenseMap[JID_HEAD_1].angle;
// 		if(wm.GetMyBodyAngleToBall()>0)
// 		{
// 			turnAngle=wm.GetMyBodyAngleToBall()-173;
// 		}
// 		else
// 		{
// 			turnAngle=wm.GetMyBodyAngleToBall()+173;
// 		}
//		/////////cout<<"turnAngle :"<<turnAngle<<endl;
		
		turnAngle=wm.GetMyAngleToBall();
		footLength+=0.001;
		if(footLength>0.16)
		  footLength=0.16;
		
// 		if(walkCounter==0&&wm.GetMyDistanceToBall()<=0.215)//(0.22+footLength*0.45))//&s&rightStep)//counterr==12)//)
// 		{
//  			if(wm.GetMyBodyAngleToBall()>0&&leftStep||wm.GetMyBodyAngleToBall()<0&&rightStep)
//  			{
// 			      /////////cout<<"nowForPass4 :"<<"my distance :"<<wm.GetMyDistanceToBall()<<" 	my angle to ball :"<<wm.GetMyBodyAngleToBall()<<endl;
// 			      nowForPass4=true;
// 			      footLength=-0.16;
// 			}
// 			//havePassed=true;
// 		}
	}
#endif
#if 1
	if(passDirection==PASS_RIGHT_FRONT)
	{
		if(walkCounter==0&&wm.GetMyDistanceToBall()<=(0.22+footLength*0.45)&&leftStep&&footLength<0.1&&wm.GetMyBodyAngleToBall()<8&&fabs(footWidth)<0.03)//counterr==12)//)
		{  
			      nowForPass3=true;
			      footLength=0.18;
		}
	}
	else if(passDirection==PASS_LEFT_FRONT)
	{
		if(walkCounter==0&&wm.GetMyDistanceToBall()<=(0.225+footLength*0.45)&&rightStep&&footLength<0.1&&wm.GetMyBodyAngleToBall()<8&&fabs(footWidth)<0.03)//counterr==12)//)
		{  
			      nowForPass3=true;
			      footLength=0.18;
		}
	}
	if(passDirection==PASS_RIGHT_FRONT_LESS_STRENGTH)
	{
		if(walkCounter==0&&wm.GetMyDistanceToBall()<=(0.22+footLength*0.45)&&leftStep&&footLength<0.1&&wm.GetMyBodyAngleToBall()<8&&fabs(footWidth)<0.03)//counterr==12)//)
		{  
			      nowForPass4=true;
			      footLength=0.18;
		}
	}
	else if(passDirection==PASS_LEFT_FRONT_LESS_STRENGTH)
	{
		if(walkCounter==0&&wm.GetMyDistanceToBall()<=(0.22+footLength*0.45)&&rightStep&&footLength<0.1&&wm.GetMyBodyAngleToBall()<8&&fabs(footWidth)<0.03)//counterr==12)//)
		{  
			      nowForPass4=true;
			      footLength=0.18;
		}
	}
#endif
	exchangeArms();
	updateTurnAngle(turnAngle);

	preparation();
	if(passDirection==PASS_FRONT)
			 updatepbPV();
		else
			 updatePBPV1();
//	 updatePBPV1();
  //    updatepbPV();
	return readNewWalkData();
}
void NewWalk::initPass()
{
	nowForPass=false;
	nowForPass2=false;
	nowForPass3=false;
	nowForPass4=false;
	justAfterPass=false;
	justAfterPass3=false;
	
	mark11=0;
}
void NewWalk::changeBody_P(FallDirection direct)
{
   if(direct==D_BACK)
   {
	   uLINK[BODY].p(0)=Lfoot.p(0)+0.05;
	   cout<<"uLINK[BODY].p(0):"<<uLINK[BODY].p(0)<<endl;
   }
   else if(direct==D_LEFT)
   {
	   uLINK[BODY].p(1)=Rfoot.p(1)-0.01;
	   cout<<"uLINK[BODY].p(1):"<<uLINK[BODY].p(1)<<endl;
   }
   else if(direct==D_RIGHT)
   {
	   uLINK[BODY].p(1)=Lfoot.p(1)+0.01;
	   cout<<"uLINK[BODY].p(1):"<<uLINK[BODY].p(1)<<endl;
   }

}
bool NewWalk::whetherCanQuitPassProcess()
{
	if(nowForPass||nowForPass2||justAfterPass||nowForPass3||justAfterPass3)
	    return false;
	else
	    return true;
}
void NewWalk::addPassMotion()
{
  //cout<<"in addPassMotion"<<endl;
	if(nowForPass&&leftStep)
	{
	  //cout<<"1"<<endl;
		passBall.PassBallFront_LeftF(sendAngle,walkCounter,footLength);
	}
	
	if(nowForPass&&rightStep)
	{
	  //cout<<"2"<<endl;
		passBall.PassBallFront_RightF(sendAngle,walkCounter,footLength); 
		//passBall.PassBallFrontStrength2_LeftF(sendAngle,walkCounter);
	}
	
	if(nowForPass4&&leftStep)
	{ 
		//cout<<"3"<<endl;
		//passBall.PassBallRightFront_LessS(sendAngle,walkCounter);
		passBall.PassBallRightFront_LessS(sendAngle,walkCounter);
		if(walkCounter==6)
		if(mark11<=2)
		{
		  walkCounter=5;
		  mark11++;
		}
	}
	
	if(nowForPass4&&rightStep)
	{
	  //cout<<"4"<<endl;
				//passBall.PassBallLeftFront_LessS(sendAngle,walkCounter);
		passBall.PassBallLeftFront_LessS(sendAngle,walkCounter);
		if(walkCounter==6)
		      if(mark11<=2)
		      {
			walkCounter=5;
			mark11++;
		      }
	}
	if(nowForPass2)
	{
	  //cout<<"5"<<endl;
		passBall.PassBallHoriz(sendAngle,walkCounter);
	}
	
	if(nowForPass3&&leftStep)
	{
	  //cout<<"6"<<endl;

		//passBall.PassBallRightFront_LessS(sendAngle,walkCounter);
		passBall.PassBallRightFront(sendAngle,walkCounter);
		if(walkCounter==6)
		      if(mark11<=2)
		      {
			walkCounter=5;
			mark11++;
		      }
	}
	
	if(nowForPass3&&rightStep)
	{
	  //cout<<"7"<<endl;
		//passBall.PassBallLeftFront_LessS(sendAngle,walkCounter);
		passBall.PassBallLeftFront(sendAngle,walkCounter);
		if(walkCounter==6)
		      if(mark11<=2)
		      {
			walkCounter=5;
			mark11++;
		      }
	}
	
/*	if(justAfterPass&&rightStep)
	{
	  switch(walkCounter)
	  {
	    //case 0:sendAngle.Lleg5.Aimangle=-30;sendAngle.Rleg3.Aimangle=30;sendAngle.Lleg3.Aimangle=-30;sendAngle.Lleg4.Aimangle=-30;break;
	    //case 1:sendAngle.Lleg5.Aimangle=-30;sendAngle.Rleg3.Aimangle=30;sendAngle.Lleg3.Aimangle=-30;sendAngle.Lleg4.Aimangle=-30;break;
	  //  case 2:sendAngle.Lleg5.Aimangle=-30;sendAngle.Rleg3.Aimangle=30;sendAngle.Lleg3.Aimangle=-30;sendAngle.Lleg4.Aimangle=-30;sendAngle.Lleg5.Aimangle=30;break;
	  //  case 3:sendAngle.Lleg5.Aimangle=-30;sendAngle.Rleg3.Aimangle=30;sendAngle.Lleg4.Aimangle=-30;break;
	  //  case 4:sendAngle.Lleg5.Aimangle=-30;sendAngle.Rleg3.Aimangle=30;sendAngle.Lleg3.Aimangle=30;break;
	    case 5:sendAngle.Lleg5.Aimangle=-30;sendAngle.Rleg3.Aimangle=30;sendAngle.Lleg3.Aimangle=30;break;
	    case 7:sendAngle.Lleg5.Aimangle=-30;sendAngle.Rleg3.Aimangle=30;sendAngle.Lleg3.Aimangle=30;break;
	    case 6:sendAngle.Lleg3.Aimangle=30;sendAngle.Rleg3.Aimangle=30;sendAngle.Lleg5.Aimangle=-30;break;
	    default:break;
	  }
	}
	if(justAfterPass&&leftStep)
	{
	  switch(walkCounter)
	  {
	  //  case 0:sendAngle.Lleg3.Aimangle=30;sendAngle.Rleg5.Aimangle=-30;sendAngle.Rleg3.Aimangle=-30;sendAngle.Rleg4.Aimangle=-30;break;
	  //  case 1:sendAngle.Lleg3.Aimangle=30;sendAngle.Rleg5.Aimangle=-30;sendAngle.Rleg3.Aimangle=-30;sendAngle.Rleg4.Aimangle=-30;break;
	  //  case 2:sendAngle.Lleg3.Aimangle=30;sendAngle.Rleg5.Aimangle=-30;sendAngle.Rleg3.Aimangle=-30;sendAngle.Rleg4.Aimangle=-30;sendAngle.Rleg5.Aimangle=30;break;
	  //  case 3:sendAngle.Lleg3.Aimangle=30;sendAngle.Rleg5.Aimangle=-30;sendAngle.Rleg4.Aimangle=-30;break;
	   // case 4:sendAngle.Lleg3.Aimangle=30;sendAngle.Rleg5.Aimangle=-30;sendAngle.Rleg3.Aimangle=30;break;
	    case 5:sendAngle.Lleg3.Aimangle=30;sendAngle.Rleg5.Aimangle=-30;sendAngle.Rleg3.Aimangle=30;break;
	    case 6:sendAngle.Lleg3.Aimangle=30;sendAngle.Rleg3.Aimangle=30;sendAngle.Rleg5.Aimangle=-30;break;
	    case 7:sendAngle.Lleg3.Aimangle=30;sendAngle.Rleg5.Aimangle=-30;sendAngle.Rleg3.Aimangle=30;break;
	    default:break;
	  }
	}*/
}












