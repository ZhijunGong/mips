#include<stdio.h>
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<map>
#include<vector>
#include<string>
#include<deque>
#define max1 10002
#define N 5000000

using namespace std;

long long lo;
long long hi;
map<string,int>textlabel;
map<string,int>datalabel;
//line storage[max1];
char data[N];
long long position;
int PC,PD;
long long reload[34];
long long transform(string cc);
bool flagdt;
int hazard_re[34];
class line;
deque<line> DD;

ofstream fout("outputgzj.out");
ifstream infile("array_test1-mahaojun.in");
ofstream outgzj("outgzj_array_test1.txt");

int searchnum(string name)
{
	if(name == "$zero"||name=="$0") return 0;
	if(name == "$at"||name=="$1") return 1;
	if(name == "$v0"||name=="$2") return 2;
	if(name == "$v1"||name=="$3") return 3;
	if(name == "$a0"||name=="$4") return 4;
	if(name == "$a1"||name=="$5") return 5;
	if(name == "$a2"||name=="$6") return 6;
	if(name == "$a3"||name=="$7") return 7;
	if(name == "$t0"||name=="$8") return 8;
	if(name == "$t1"||name=="$9") return 9;
	if(name == "$t2"||name=="$10") return 10;
	if(name == "$t3"||name=="$11") return 11;
	if(name == "$t4"||name=="$12") return 12;
	if(name == "$t5"||name=="$13") return 13;
	if(name == "$t6"||name=="$14") return 14;
	if(name == "$t7"||name=="$15") return 15;
	if(name == "$s0"||name=="$16") return 16;
	if(name == "$s1"||name=="$17") return 17;
	if(name == "$s2"||name=="$18") return 18;
	if(name == "$s3"||name=="$19") return 19;
	if(name == "$s4"||name=="$20") return 20;
	if(name == "$s5"||name=="$21") return 21;
	if(name == "$s6"||name=="$22") return 22;
	if(name == "$s7"||name=="$23") return 23;
	if(name == "$t8"||name=="$24") return 24;
	if(name == "$t9"||name=="$25") return 25;
	if(name == "$k0"||name=="$26") return 26;
	if(name == "$k1"||name=="$27") return 27;
	if(name == "$gp"||name=="$28") return 28;
	if(name == "$sp"||name=="$29") return 29;
	if(name == "$s8"||name=="$30") return 30;
	if(name == "$fp"||name=="$30") return 30;
	if(name == "$ra"||name=="$31") return 31;
	if(name == "$lo"||name=="$32") return 32;
	if(name == "$hi"||name=="$33") return 33;
	else return -1;
}

string INSTRUCTION[51]={
	"add","addu","addiu","sub","subu",
	"mul","mulu","div","divu",
	"xor","xoru","neg","negu",
	"rem","remu",
	"li",
	"seq","sge","sgt","sle","slt","sne",
	"b","beq","bne","bge","ble","bgt","blt","beqz","bnez","blez","bgez","bgtz","bltz",
	"j","jr","jal","jalr",
	"la","lb","lh","lw",
	"sb","sh","sw",
	"move","mfhi","mflo",
	"nop","syscall"
};

int searchINS(string cc){
	int ans=0;
    for(int i=0;i<51;i++){
        if(cc==INSTRUCTION[i]){
        	ans=-i-1;
        	return ans;
		}
        else continue;
    }
    return ans;
}

union Word{
	int iw;
	unsigned int uiw;
	short sh[2];
	unsigned short ush[2];
	char c[4];
	Word(int in){
		iw=in;
	}

	Word(unsigned int uin){
		uiw=uin;
	}
	Word(short s1,short s2){
		sh[0]=s1;sh[1]=s2;
	}
	Word(unsigned short us1,unsigned short us2){
		ush[0]=us1;ush[1]=us2;
	}
	Word(char c1,char c2,char c3,char c4){
		c[0]=c1;c[1]=c2;c[2]=c3;c[3]=c4;
	}
	Word(int pc,char x){
		c[0]=data[pc];c[1]=data[pc+1];c[2]=data[pc+2];c[3]=data[pc+3];
	}
};

union Half{
	short sh;
	unsigned short ush;
	char c[2];
	Half(short s){
		sh=s;
	}
	Half(unsigned short us){
		ush=us;
	}
	Half(char c1,char c2){
		c[0]=c1;c[1]=c2;
	}
	Half(int pc,char x){
		c[0]=data[pc];
		c[1]=data[pc+1];
	}
};

union Long{
    long long l;
    int w[2];
    Long(long long ll){l=ll;}
    Long(int i1,int i2){w[0]=i1;w[1]=i2;}
};


int searchlable(string cc){
	return textlabel[cc];
}

int searchlable_data(string cc){
	return datalabel[cc];
}

class line{

	public:

		int num;
	//	int count;
		int oper;
		struct{
			string sentence;
			int Size;
		}str[max1];

		line():num(0),oper(0){
			for(int i=0;i<max1;i++){
				str[i].sentence="";
				str[i].Size=0;
			}
		}

		line &operator=(const string &cc){
		//	count=0;
			
			int cccount=0;
			str[oper].sentence="";
			str[oper].Size=0;
			if(cc[0]=='.'){
				num=1;//.的类型num=1;

				while(cc[cccount]!='\n'){
					if(cc[cccount]=='\t'){
						cccount++;
					}
					if(cc[cccount]==' '){
						oper++;
						cccount++;
					}
					if(cc[cccount]==','&&cc[cccount+1]!=' '){
						cccount++;
						oper++;
					}
					else if(cc[cccount]==','&&cc[cccount+1]==' '){
						cccount++;
					}
					else{
                        str[oper].sentence+=cc[cccount++];
						str[oper].Size++;
					}
                }
			//	str[oper].sentence+='\n';
			}

			else{
				while(cc[cccount]!='\n'){
						if(cc[cccount]=='\t'){
							cccount++;
						}
						if(cc[cccount]==' '){
							oper++;
							cccount++;
						}
						if(cc[cccount]==','&&cc[cccount+1]!=' '){
							cccount++;
							oper++;
						}
						else if(cc[cccount]==','&&cc[cccount+1]==' '){
							cccount++;
						}

						else{
                            if(cc[cccount]==':')num=2;//label声明num=2;
                            str[oper].sentence+=cc[cccount++];
                            str[oper].Size++;
						}
					}
				//	str[oper].sentence+='\n';
				}

			if(num==0)num=3;//指令的 num=3;
			return *this;
		}
		line &operator=(const line &other){
			num=other.num;
			oper=other.oper;
			for(int i=0;i<=other.oper;i++){
				str[i].sentence=other.str[i].sentence;
			}
			return *this;
		}
		int kind(){
			return num;
		}
		void output(){
			for(int i=0;i<=oper;i++){
				printf("%s ",str[i].sentence.c_str());
			}
		}
		int oper_count(){
            return oper;
		}
		void clear(){
			for(int i=0;i<=oper;i++){
				str[i].sentence="";
				str[i].Size=0;
			}
			oper=0;
			num=0;
		}
};

class decode:public line{
	public:
		long long de1,de2,de3;
		int re1,re2,re3;
		int jumpline,jumpmemory;
		string string_address;
		decode &operator=(const decode &other){
			de1=other.de1;
			de2=other.de2;
			de3=other.de3;
			re1=other.re1;
			re2=other.re2;
			re3=other.re3;
			jumpline=other.jumpline;
			jumpmemory=other.jumpmemory;
			string_address=other.string_address;
			num=other.num;
			oper=other.oper;
			for(int i=0;i<=other.oper;i++){
				str[i].sentence=other.str[i].sentence;
				str[i].Size=other.str[i].Size;
			}
            return *this;
        }

		decode &operator=(const line &cc){
			oper=cc.oper;
			num=cc.num;
			for(int i=0;i<=cc.oper;i++){
				str[i].sentence=cc.str[i].sentence;
				str[i].Size=cc.str[i].Size;
			}
			switch(searchINS(str[0].sentence)){
			    de1=de2=de3=-1;
			    re1=re2=re3=-2;
			    string_address="";
			    jumpline=-1;
				case -1:case -2:case -3:case -4:
				case -5:case -6:case -7:case -8:
				case -9:case -10:case -11:case -12:case -13:
                case -14:case -15:case -16:case -17:case -18:
				case -19:case -20:case -21:case -22:case -47:{
					re1=searchnum(str[1].sentence);
					if(searchnum(str[2].sentence)==-1){
                        re2=transform(cc.str[2].sentence);
                        de1=reload[re1];
                        de2=re2;
                    //    cout<<de2<<endl;
                    }
                    else if(searchnum(str[2].sentence)!=-1&&cc.oper==2){
                    	re2=searchnum(str[2].sentence);
                    	de1=reload[re1];
                    	de2=reload[re2];
					}
                    else if(cc.oper==3&&searchnum(str[3].sentence)==-1){
                    	re2=searchnum(str[2].sentence);
                        re3=transform(str[3].sentence);
                        de1=reload[re1];
                        de2=reload[re2];
                        de3=re3;
                      //  cout<<de2;
                    }
                    else{
                    	re2=searchnum(str[2].sentence);
						re3=searchnum(str[3].sentence);
						de1=reload[re1];
                        de2=reload[re2];
                        de3=reload[re3];
					} 
					break;
				}

				case -23:case -36:case -38:{
					jumpline=searchlable(str[1].sentence);
				//	cout<<jumpline;
					break;
				}

				case -24:case -25:case -26:
				case -27:case -28:case -29:{
					re1=searchnum(str[1].sentence);
					if(searchnum(str[2].sentence)==-1)re2=transform(str[2].sentence);
					else re2=searchnum(str[2].sentence);
					de1=reload[re1];
                    de2=reload[re2];
					jumpline=searchlable(str[3].sentence);
					break;
				}

				case -30:case -31:case -32:
				case -33:case -34:case -35:{
					re1=searchnum(str[1].sentence);
					jumpline=searchlable(str[2].sentence);
					de1=reload[re1];
					break;
				}

				case -37:case -39:{
					re1=searchnum(str[1].sentence);
					cout<<re1;
					de1=reload[re1];
					jumpline=de1;
					cout<<jumpline;
					break;
				}

				case -40:case -41:case -42:case -43:
                case -44:case -45:case -46:{
				    re1=searchnum(str[1].sentence);
				    de1=reload[re1];
				 //   cout<<re1<<endl; 
					string_address=str[2].sentence;
					break;
				}

				case -48:case -49:{
                    re1=searchnum(str[1].sentence);
                    de1=reload[re1];
                    break;
				}

				case -51:{
                    de1=reload[2];
                    de2=reload[4];
                    de3=reload[5];
                    break;
				}
            }
            return *this;
		}
		
		void output(){
			for(int i=0;i<=oper;i++){
				printf("%s",str[i].sentence.c_str());
			}
		}
		void clear(){
			for(int i=0;i<=oper;i++){
				str[i].sentence="";
				str[i].Size=0;
			}
			oper=0;
			num=0;
			de1=de2=de3=-1;
		    re1=re2=re3=-2;
			string_address="";
			jumpline=-1;
			jumpmemory=-1;
		}
};

class Execution:public decode{

	public:
        int ans,anslo,anshi;
        bool if_jump=0;
        bool if_hl=0;
        Execution &operator=(const Execution &other){
            ans=other.ans;
            anshi=other.anshi;
            anslo=other.anslo;
            if_hl=other.if_hl;
            if_jump=other.if_jump;
            de1=other.de1;
			de2=other.de2;
			de3=other.de3;
			re1=other.re1;
			re2=other.re2;
			re3=other.re3;
			jumpline=other.jumpline;
			jumpmemory=other.jumpmemory;
			string_address=other.string_address;
			num=other.num;
			oper=other.oper;
			for(int i=0;i<=other.oper;i++){
				str[i].sentence=other.str[i].sentence;
				str[i].Size=other.str[i].Size;
			}
            return *this;
        }

	Execution &operator=(const decode &cc){
			de1=cc.de1;
			de2=cc.de2;
			de3=cc.de3;
			re1=cc.re1;
			re2=cc.re2;
			re3=cc.re3;
			jumpline=cc.jumpline;
			jumpmemory=cc.jumpmemory;
			string_address=cc.string_address;
			num=cc.num;
			oper=cc.oper;
			for(int i=0;i<=cc.oper;i++){
				str[i].sentence=cc.str[i].sentence;
				str[i].Size=cc.str[i].Size;
			}
			if_jump=0; 
			switch(searchINS(str[0].sentence)){
				case -1:case -2:case -3:{
                    ans=cc.de2+cc.de3;
					break;
				}//add

				case -4:case -5:{
                    ans=cc.de2-cc.de3;
					break;
				}//sub


				case -6:case -7:{
					if(cc.oper==3){
						ans=cc.de2*cc.de3;
						
					}
					else if(cc.oper==2){
                        if_hl=1;
						anslo=Long(cc.de1*cc.de2).w[0];
						anshi=Long(cc.de1*cc.de2).w[1];
                    }
					break;

				}//mul

				case -8:case -9:{
					if(cc.oper==3){
						ans=cc.de2/cc.de3;
					}
					else if(cc.oper==2){
                        if_hl=1;
						anslo=cc.de1/cc.de2;
						anshi=cc.de1%cc.de2;
					}
					break;
				}//div

				case -10:case -11:{
					ans=cc.de2^cc.de3;
				}

				case -12:case -13:{
                    ans=-cc.de2;
				}

				case -14:case -15:{
					ans=cc.de2%cc.de3;
					break;
				}

				case -16:{
					ans=cc.de2;
				//	cout<<ans;
					break;
				}

				case -17:{
					if(cc.de2==cc.de3)ans=1;
					else ans=0;
					break;
				}

				case -18:{
					if(cc.de2>=cc.de3)ans=1;
					else ans=0;
					break;
				}

				case -19:{
					if(cc.de2>cc.de3)ans=1;
					else ans=0;
					break;
				}

				case -20:{
					if(cc.de2<=cc.de3)ans=1;
					else ans=0;
					break;
				}

				case -21:{
					if(cc.de2<cc.de3)ans=1;
					else ans=0;
					break;
				}

				case -22:{
					if(cc.de2!=cc.de3)ans=1;
					else ans=0;
					break;
				}

				case -23:{
					if_jump=1;
					break;
				}//b

				case -24:{
					if(cc.de1==cc.de2)if_jump=1;
					break;
				}//beq

				case -25:{
					if(cc.de1!=cc.de2)if_jump=1;
					break;
				}//bne

				case -26:{
					if(cc.de1>=cc.de2)if_jump=1;
					break;
				}//bge

				case -27:{
					if(cc.de1<=cc.de2)if_jump=1;
					break;
				}//ble

				case -28:{
					if(cc.de1>cc.de2)if_jump=1;
					break;
				}//bgt

				case -29:{
					if(cc.de1<cc.de2)if_jump=1;
					break;
				}//blt

				case -30:{
					if(cc.de1==0)if_jump=1;
					break;
				}

				case -31:{
					if(cc.de1!=0)if_jump=1;
					break;
				}

				case -32:{
					if(cc.de1<=0)if_jump=1;
					break;
				}

				case -33:{
					if(cc.de1>=0)if_jump=1;
				}

				case -34:{
					if(cc.de1>0)if_jump=1;
					break;
				}

				case -35:{
					if(cc.de1<0)if_jump=1;
					break;
				}

				case -36:{
					if_jump=1;
					break;
				}//j

				case -37:{
					if_jump=1;
					break;
				} //jr

				case -38:{
					if_jump=1;
                    reload[31]=PC+1;
					break;
				}//jal

				case -39:{
					if_jump=1;
					reload[31]=PC+1;
					break;
				}//jalr

				case -40:case -41:case -42:case -43:
                case -44:case -45:case -46:{
					bool flag=0;
					string c="";
					string d="";
					int tot=0;
					//cout<<cc.str[2].Size;
					while(cc.string_address[tot]!='('&&tot<cc.str[2].Size){
						c+=cc.string_address[tot];
					//	cout<<c<<endl;
						tot++;
					}
					tot++;
					while(cc.string_address[tot]!=')'&&tot<cc.str[2].Size){
						d+=cc.string_address[tot];
						tot++;
					}
					//cout<<c;
					if(d!="")flag=1;//cout<<d;
					if(!flag){
						jumpmemory=searchlable_data(c);
				//		cout<<jumpmemory;
					}
					else if(flag){
						int p=transform(c);
						jumpmemory=reload[searchnum(d)]+p;
				//		cout<<jumpmemory;
					}
					break;
				}//load,store

				case -47:{
					ans=cc.de2;
					break;
				}//move

				case -48:{
					ans=reload[33];
					break;
				}//mfhi

				case -49:{
					ans=reload[32];
					break;
				}//mflo

				case -50:{

					break;
				}//nop

				case -51:{

					switch(cc.de1){
						case 1:{
						//	printf("%lld",cc.de2);
							outgzj<<cc.de2;
							break;
						}

						case 4:{
						    int i=cc.de2;
							while(data[i]!='\0'){
							//	printf("%c",data[i]);
								outgzj<<data[i];
								cout<<data[i];
								i++;
							}
							break;
						}

						case 5:{
							int i;
						//	scanf("%d",&i);
							infile>>i;
							ans=i;
							break;
						}

						case 8:{
							//string ss="";
							char cbaby;
							int now=cc.de2;
							for(int i=0;i<cc.de3;i++){
							//	char cc=getchar();
								infile.get(cbaby);
								if(cbaby!='\n'){
									data[now++]=cbaby;
								}
							}
							data[now++]='\0';
							break;
						}

						case 9:{
							ans=PD;
							for(int i=0;i<cc.de2;i++)data[PD++]=0;
							break;
						}

						case 10:exit(0);

						case 17:{
							exit(cc.de2);
							break;
						}

					}
					break;
				}//syscall
            }
            return *this;
        }

};

class memory_access:public Execution{
	public:
        int  datatype;
        int num1;
        short num2;
        char num3;
        memory_access &operator=(const Execution &cc){
        	ans=cc.ans;
            anshi=cc.anshi;
            anslo=cc.anslo;
            if_hl=cc.if_hl;
            if_jump=cc.if_jump;
            de1=cc.de1;
			de2=cc.de2;
			de3=cc.de3;
			re1=cc.re1;
			re2=cc.re2;
			re3=cc.re3;
			jumpline=cc.jumpline;
			jumpmemory=cc.jumpmemory;
			string_address=cc.string_address;
			num=cc.num;
			oper=cc.oper;
			for(int i=0;i<=cc.oper;i++){
				str[i].sentence=cc.str[i].sentence;
				str[i].Size=cc.str[i].Size;
			}
            switch(searchINS(cc.str[0].sentence)){
                case -40:{
                    datatype=4;
                    num1=cc.jumpmemory;
                    break;
                }
                case -41:{
                    datatype=1;
                    num3=data[jumpmemory];
                    break;
                }
                case -42:{
                    datatype=2;
                    num2=Half(jumpmemory,'A').sh;
                    break;
                }

                case -43:{
                    datatype=4;
                    num1=Word(jumpmemory,'A').iw;
                 //   cout<<num1<<endl;
                    break;
                }

                case -44:{
                    int a=cc.de1;
                    data[jumpmemory]=Word(a).c[0];
                    break;
                }

                case -45:{
                    int a=cc.de1;
                    data[jumpmemory]=Word(a).c[0];
                    data[jumpmemory+1]=Word(a).c[1];
                    break;
                }

                case -46:{
                    int a=cc.de1;
                //    cout<<a<<endl;
                    data[jumpmemory]=Word(a).c[0];
                    data[jumpmemory+1]=Word(a).c[1];
                    data[jumpmemory+2]=Word(a).c[2];
                    data[jumpmemory+3]=Word(a).c[3];
                //    cout<<Word(a).iw<<endl;
                    break;
                }

            }
            return *this;
		}
};

class write_back:public memory_access{
	public:

        write_back &operator=(const memory_access &cc){
            switch(searchINS(cc.str[0].sentence)){
                case -1:case -2:case -3:case -4:
				case -5:case -10:case -11:case -12:case -13:
                case -14:case -15:case -16:case -17:case -18:
				case -19:case -20:case -21:case -22:{
                    reload[cc.re1]=cc.ans;
                 //   cout<<reload[cc.re1]<<endl;
                    break;
				}

				case -6:case -7:case -8:
				case -9:{
                    if(cc.if_hl==1){
                        reload[32]=cc.anslo;
                        reload[33]=cc.anshi;
                    }
                    else reload[cc.re1]=cc.ans;
                    
                    break;
				}

				case -23:case -24:case -25:case -26:
				case -27:case -28:case -29:
				case -30:case -31:case -32:
				case -33:case -34:case -35:
                case -36:case -37:case -38:case -39:{
                    if(cc.if_jump==1)PC=cc.jumpline-1;
              //      cout<<PC<<endl;
                    break;
                }

                case -40:case -41:case -42:case -43:{
                    if(cc.datatype==1)reload[cc.re1]=cc.num3;
                    else if(cc.datatype==2)reload[cc.re1]=cc.num2;
                    else if(cc.datatype==4)reload[cc.re1]=cc.num1;
                    
                    break;
                }
                case -44:case -45:case -46:{
                	
                    break;
                }

                case -47:case -48:case -49:{
                	
                    reload[cc.re1]=cc.ans;
                    break;
                }

                case -51:{
                    switch(cc.de1){
                        case 5:case 9:reload[2]=cc.ans;
                    }
                
                    break;
                }
            }
            
            return *this;
		}

};


long long transform(string cc)
{
	long long x=0;
	char c=cc[0];
	int i=0;
	int b=1;
	for(;c<'0'||'9'<c;c=cc[i])if(c=='-'){b=-1;i++;}
	for(;'0'<=c&&c<='9';c=cc[i]){
		i++;x=x*10+c-'0';
	}
	x*=b;
	return x;
}

void out_reload(){
	 for(int i=0;i<=33;i++)cout<<"reload["<<i<<"]="<<reload[i]<<endl;
	 
}

bool datahazard(){

}

int main()
{
	reload[29]=4*1024*1024;
	char tem[103];
	string tmp[max1];
	int i=0;
	int num=0;
	int position;
	ifstream fin("input.txt");

	while(fin.getline(tem,1000)){
		tmp[i]=tem;
		tmp[i]+='\n';
		i++;
	}
	num=i;
	for(int k=0;k<num;k++)cout<<tmp[k];
	i=0;
	line LINE,lineafter;
	line LL;
//	printf("%d",num);

while(i+1<num){
	//	cout<<i;
		LINE.clear(); 
        LINE=tmp[i];
        DD.push_back(LINE);
        position=i;
    if(LINE.str[0].sentence==".data"){
        lineafter=tmp[++i];position++;
        while(lineafter.str[0].sentence!=".text"){
        	
            if(lineafter.kind()==2){
                string n="";
                for(int j=0;j<lineafter.str[0].Size-1;j++){
                    n+=lineafter.str[0].sentence[j];
                }
                datalabel.insert(pair<string,int>(n,PD));
            //    cout<<n<<":"<<datalabel[n]<<endl;
                DD.push_back(lineafter);
                i++;
                if(i>=num)break;
                lineafter.clear();
                lineafter=tmp[i];
                position=i;
             //   cout<<i<<endl;
            }
            else{
            	
                if(lineafter.str[0].sentence==".align"){
					int n=transform(lineafter.str[1].sentence);
					int k=0;
					while(PD>k*(1<<n))k++;
					PD =k*(1<<n);
					DD.push_back(lineafter);
					if(i+1>=num)break;
					lineafter.clear();
					lineafter=tmp[++i];
				//	cout<<i<<endl;
				}//.align

                if(lineafter.str[0].sentence==".ascii"){
                    string ss="";
					for(int k=1;lineafter.str[1].sentence[k+1]!='"';k++)ss+=lineafter.str[1].sentence[k];
					for(int j=0;j<lineafter.str[1].Size-1;j++){
						if(ss[j]=='\\'){
							if(ss[j+1]=='n')data[PD++]='\n';
							else if(ss[j+1]='t')data[PD++]='\t';
							j++;
							continue;
						}
						else{
							data[PD++]=ss[j];
						}
					}
					DD.push_back(lineafter);
					if(i+1>=num)break;
					lineafter.clear();
					lineafter=tmp[++i];
					
					position=i;
				//	cout<<i<<endl;
				}//.ascii

				if(lineafter.str[0].sentence==".asciiz"){
					string ss=lineafter.str[1].sentence;
				//	cout<<ss<<endl;
				//	cout<<lineafter.str[1].Size-1<<endl;
					//for(int k=1;lineafter.str[1].sentence[k+1]!='"';k++)ss+=lineafter.str[1].sentence[k];
					for(int j=1;j<lineafter.str[1].Size-1;j++){
						if(ss[j]=='\\'){
							if(ss[j+1]=='n')data[PD++]='\n';
							else if(ss[j+1]='t')data[PD++]='\t';
							j++;
							continue;
						}
						else{
							data[PD++]=ss[j];
						//	cout<<data[PD-1]<<endl;
						}
					}
					data[PD++]='\0';
					DD.push_back(lineafter);
					if(i+1>=num)break;
					lineafter.clear();
					lineafter=tmp[++i];
					position=i;
				//	cout<<i<<endl;
				}//.asciiz

				if(lineafter.str[0].sentence==".byte"){
					for(int j=1;j<=lineafter.oper;j++){
						char a=transform(lineafter.str[j].sentence);
						data[PD++]=a;
					}
					DD.push_back(lineafter);
					if(i+1>=num)break;
					lineafter.clear();
					lineafter=tmp[++i];
					position=i;
				//	cout<<i<<endl;
				}//.byte

				if(lineafter.str[0].sentence==".halfword"){
					for(int j=1;j<=lineafter.oper;j++){
						short a=transform(lineafter.str[j].sentence);
						data[PD++]=Half(a).c[0];
						data[PD++]=Half(a).c[1];
					}
					DD.push_back(lineafter);
					if(i+1>=num)break;
					lineafter.clear();
					lineafter=tmp[++i];
					position=i;
				//	cout<<i<<endl;
				}//.halfword

				if(lineafter.str[0].sentence==".word"){
					for(int j=1;j<=lineafter.oper;j++){
						int  a=transform(lineafter.str[j].sentence);
						data[PD++]=Word(a).c[0];
						data[PD++]=Word(a).c[1];
						data[PD++]=Word(a).c[2];
						data[PD++]=Word(a).c[3];
					}
					DD.push_back(lineafter);
					if(i+1>=num)break;
					lineafter.clear();
					lineafter=tmp[++i];
					position=i;
				//	cout<<i<<endl;
				}//.word

				if(lineafter.str[0].sentence==".space"){
					int a=transform(lineafter.str[1].sentence);
					for(int j=1;j<=a;j++)data[PD++]=0;
					DD.push_back(lineafter);
					if(i+1>=num)break;
					lineafter.clear();
					lineafter=tmp[++i];
					position=i;
				//	cout<<i<<endl;
				}//.space
				
				else if(lineafter.str[0].sentence==".data"){
					DD.push_back(lineafter);
					if(i+1>=num)break;
					lineafter.clear();
					lineafter=tmp[++i];
					position=i;
				//	cout<<i<<endl;
				}
					
				}
			}
		
		}

		else if(LINE.str[0].sentence==".text"){//text
			lineafter=tmp[++i];position++;
			while(lineafter.str[0].sentence!=".data"){
				if(lineafter.kind()==2){
					
                    string n="";
                    for(int j=0;j<lineafter.str[0].Size-1;j++){
                        n+=lineafter.str[0].sentence[j];
                    }
					textlabel.insert(pair<string,int>(n,position));
				//	cout<<position<<" ";
				//	cout<<n<<textlabel[n]<<endl;
					DD.push_back(lineafter);
					if(i+1>=num)break;
					lineafter.clear();
					lineafter=tmp[++i];
					position=i;
				//	cout<<i<<endl;
				}
				else{
					DD.push_back(lineafter);
                    if(i+1>=num)break;
                    lineafter.clear();
					lineafter=tmp[++i];
					position=i;
				//	cout<<i<<endl;
				}
			}
		}
	}
	
	int m=0;
//	printf("%d",m);
	PC=searchlable("main");
	//printf("%d",PC);
	line LN;
	decode DE;
	Execution EX;
	memory_access M_A;
	write_back W_R;
	while(PC<num){
		 LN.clear();DE.clear();
	//	 printf("%d",PC);
		 system("pause");
		 LN=tmp[++PC];
         DE=LN;
         EX=DE;
         M_A=EX;
         W_R=M_A;
         out_reload();
		 LN.output();printf(" PC=%d\n",PC);
		 printf("PD=%d\n",PD);
		 cout<<"---------over---------"<<endl;
    }

	return 0;
}

