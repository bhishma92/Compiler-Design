/* Parser1 */ 

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
using namespace std;

class node
{
	public:
		int children;
		bool noVal;
		int nMax=0;
		//bool hasChildren;
		vector<node> childVec;
		vector<int> index;
		int endNode=0;

		vector<node> getVec()
		{
			return childVec;
		}

		int setID(int var)
		{
			id=var;
			return id;
		}

		int getID()
		{
			return id;
		}

		int setType(int num)
		{
			typeNum=num;
			return typeNum;
		}

		int getType()
		{
			return typeNum;
		}

		string setName(string name)
		{
			typeName1=name;
			return typeName1;
		}

		string getName()
		{
			return typeName1;
		}

		int setPos(int pos)
		{
			position=pos;
			return position;
		}

		int getPos()
		{
			return position;
		}

		int setLen(int len)
		{
			length1=len;
			return length1;
		}

		int getLen()
		{
			return length1;
		}

		string setVal(string val)
		{
			if(val == "")
			{	
				noVal=true;
			}
			else
			{
				noVal=false;
			}
			
			value1= val;
			return value1;
			
		}

		bool getNoVal()
		{
			return noVal;
		}

		string getVal()
		{
			if(value1 == "")
			{
				return typeName1;
			}
			return value1;
		}

		bool setTerm(bool t)
		{
			terminal=t;
			return terminal;
		}

		bool getTerm()
		{
			return terminal;
		}

		bool setChild(bool setCh)
		{
			hasChildren=setCh;
			return hasChildren;
		}

		void delChild()
		{
			childVec.pop_back();
		}
		
		node(){}
	

		void addChild(node** child)
		{
			childVec.push_back(**child);
			children++;
		}

		void addIndex(int i)
		{
			index.push_back(i);
			if(nMax<i)
			{
				nMax=i;
			}
		}

		node(bool aa, bool bb, int cc, int dd, int ee, string ff, int gg, int hh, string ii)
		{

			setTerm(aa);
			setChild(bb);
			children=cc;
			setID(dd);
			setType(ee);
			setName(ff);
			setPos(gg);
			setLen(hh);
			setVal(ii);
			
		}

	private:
		bool terminal;
		bool hasChildren;
		int id;
		int typeNum;
		string typeName1;
		int position;
		int length1;
		string value1;



/*
		
*/
};

class tools
{
	public:
		
	bool checkLetter(char ar){
		if( (65<= int(ar) & int(ar) <= 90 ) || (97<= int(ar) & int(ar) <= 122 ) ){
			return true;	
		}											
		
		return false;
																			
	}

	bool checkInt(char br){
                if((int('0') <= int(br)) & (int(br) <=  int('9')) ){
                        return true;
                }

                return false;

        }


	bool checkSpecialChar(char cr){
		int temp= int(cr);
		if( (temp == 33) || (temp > 35 & temp<=47) || (temp>=58 & temp<=64) || (123<=temp & temp<=126) ){
			return true;
		}
		return false;
	}


};

class Parser : public tools, public node
{
	public:
		int size=0;
		vector<int> vec;
		int i=0;
		int token=0; 
		int LEN=0;
		string total;	
		string str;
		bool floatFlag; int quoteLoc;int spec; int strlen;
		int argValue[100];
		int id[1024];
		string val1[1024];
		string name[1024];
		node *ptr[1024];
		int temp;
		int head;
		vector<vector<int> > indexVec;
		int pError=0; int var3=0;
		
		void ptrIn()
		{
			for(int jj=0;jj<1024;jj++)
			{
				ptr[i]=NULL;
			}
			
		}
		//node* tokens1= new node[1024];

		

		string input;int length;
        string tokens[1024];
	
        int arg;

        int parseID;
        //node tokens1[1024];
        node* tokens1[1024];
		node* parseNodes[1024];
		int retVal;
		int tokenVal=0; int indexR;

		

		
		void setString(string s)
		{
			ptrIn();
			input = s;
			length= input.size()-1;
		}
		
		void setArg(int i)
		{
			arg= i;
		}
		
		void addToken(string tokens[1024], int t, string type, string typeName, int pos, int len, string val )
		{

			int x= t+1;
            stringstream ss,ss1,ss2;
            string strNum,strNumP,strNumLen;
            ss<<x; ss>>strNum;
            ss1<<pos; ss1>>strNumP;
            ss2<<len; ss2>>strNumLen;
            int xx=0; int tp=0;
            string conf;

            if(val== "")
            {
               	conf=typeName;
            }
            else
            {
               	conf=val;
            }
			
                        
            while(xx != type.size())
          	{           		
             	tp += ( int( type.at(xx) - '0' ) * pow( 10, (type.size() -xx -1)) ) ;
                xx++;            
            }
                        
                //data structures for parsing
                if((type != "5") & (type != "6") & (type != "7"))
                {

                		tokens1[size] = new node(true,false,0,x,tp,typeName,pos,len,val);
                		
                		id[size]=tp;
                		val1[size]= conf;
                		name[size]=typeName;
                		size++;
                		vec.push_back(0);
                		//tokens1.push_back(temp);

                } //no whitespace new line comment
                	
                
                

                //data structures for parsing ends       

        		if((tp>=1 & tp<=4) || (tp >=7 & tp<=11)){

        			
             		tokens[t] = "TID: " + strNum + ", " + "TYPE: " + type + "(" + typeName + ")" + ", " + "POS: " + strNumP + ", " + "LEN: " + strNumLen + ", " + "VALUE: " + val;	
					LEN=0;
					token++;
			    }
			    else{
			    	tokens[t] = "TID: " + strNum + ", " + "TYPE: " + type + "(" + typeName + ")" + ", " + "POS: " + strNumP + ", " + "LEN: " + strNumLen ;	
					LEN=0;
					token++;
			    }					
                               
		 
			//tokens[t] = "TID: " + to_string(t);
			//cout << tokens[t] << endl;
		}
		
	
		bool isInAlphabet(int dr){
                	if( (dr == 9) || (dr==10) || (dr >= 32 & dr <= 126) ){
                        	return true;
                	}
                	return false;
        	}

        	void isBadChar(int &er){
                	LEN=0;
                	spec= er;
                	while(!isInAlphabet(er)){
                        	er++;
                        	LEN++;
                	}
                	argValue[token]=1;
                	addToken(tokens, token, "99", "ERR3", spec, LEN, "") ;

        	}	
		
		

		void setArgValue(){
			
			for(int x=0; x<100; x++){
				argValue[x]=0;
			}
		}



		void handleBadChar(int &a){
                                                                
                	LEN=0;						
                       	spec=a-1;
            while( checkSpecialChar(input.at(a)) ){
				
                LEN++;
				a++;
				                                                                                              
            }
			
			argValue[token]=1;
            addToken(tokens, token, "99", "ERR3", spec, LEN, "") ;
				
                     	  
        }
								
		void analysis()
		{
			
			setArgValue();
		
			while( i <= length){

				if(arg==3){
					addToken(tokens, token, "97", "ERR1", 0,0, "");
					break;
				}
				
				//	cout <<length << endl;				

		                /* check for the identifier, for while if else */

                		if( checkLetter(input.at(i)) || input.at(i) == '_'){
                        		
					//cout<<"you are in identifier lexical" <<endl;	
				
								int init= i;
                        		
                        		while(i<=length){
                                		
                      
									LEN++;
						
                        			if(input.substr(init, LEN)== "for"){
                                			addToken(tokens, token, "8", "FOR", i-2, 3, input.substr(init,LEN));
											i++;
											break;
                        			}

                        			else if(input.substr(init, LEN)== "while"){
                                			addToken(tokens, token, "9", "WHILE", i-4, 5, input.substr(init,LEN) );
											i++;
							
											break;
                        			}											
				
                        			else if(input.substr(init, LEN)== "if"){
                                                        addToken(tokens, token, "10", "IF", i-1, 2, input.substr(init,LEN) );
                                                        i++;
                                                        break;
                                                }										

                        			else if(input.substr(init, LEN)== "else"){
                                			addToken(tokens, token, "11", "ELSE", i-3, 4, input.substr(init,LEN) );
											i++;
											break;
                        			}
																		
					/*	else if(checkSpecialChar(input.at(i))){
							
							addToken(tokens, token, "1", "IDENTIFIER", init,LEN, input.substr(init,LEN-1) );
							//cout << "hello!"<<endl;	
							handleBadChar(i);
							//cout<< i <<endl;
							break;	
						}*/
						
									else if((!checkLetter(input.at(i))) & (input.at(i) != '_') & (!checkInt(input.at(i))) ){
										//	cout<< i <<endl;
										addToken(tokens, token, "1", "ID", init,LEN-1, input.substr(init,LEN-1) );
										break;
				
									}
									
												
                        			else if(i ==length){
							
                                		addToken(tokens, token, "1", "ID", init,LEN-1, input.substr(init,LEN) );
										i++;
									}
									
									i++;
						
                			}
				}

				//cout<<"you are in  lexical" <<endl;				

				/* Checking INT & FLOAT lexical */
														
				else if(checkInt(input.at(i))){
					//cout<<"you are in int" <<endl;
					quoteLoc=i;
					
					if(length==0){
						addToken( tokens, token, "3", "INT", quoteLoc, LEN, input.substr(quoteLoc,LEN) );
						i++;
					}
										
					while(i <=length){

						if( checkInt(input.at(i)) ) {
							i++;
							LEN++;
							if(input.at(i) == '.'){
								floatFlag = true;
								i++;
								LEN++;
								break;
							}
							else if((!checkInt(input.at(i))) & (input.at(i) != '.')){
								addToken( tokens, token, "3", "INT", quoteLoc, LEN, input.substr(quoteLoc,LEN) );
								break;
							}
							else if(i == length){
								LEN++;
								addToken( tokens, token, "3", "INT", quoteLoc, LEN, input.substr(quoteLoc,LEN) );
								i++;										
								break;
							}
						}		
						
					}
				/*		
					while((floatFlag) & (i <= length) ){
						cout<<checkInt(input.at(i))<<endl;
						cout<<LEN<<endl;
						
		
						
						addToken( tokens, token, "4", "FLOAT", quoteLoc, LEN, input.substr(quoteLoc,LEN+1) );
						i++;
						break;
					
					} */	
				}	
			
				
				/* String lexical */

				else if(int(input.at(i)) == 34){	//34 is ascii value for "
						
						
						quoteLoc=i;
					
						
						while(i<=length){
							i++;
							if( int(input.at(i))==34  ){
								addToken(tokens, token, "2", "STR", quoteLoc, LEN+2, input.substr(quoteLoc+1,LEN) );
								i++;
								break;
							}
						
							else if(!(isInAlphabet( int(input.at(i)) )) ){
								argValue[token]=1;
								addToken(tokens, token, "98", "ERR2", quoteLoc, LEN+1,"");
								break;
							}
							else if((i==length) & (int(input.at(i)) != 34) ){
								argValue[token]=1;
								addToken(tokens, token, "98", "ERR2", quoteLoc, LEN+1, "");
								
								break;
							}
							else if (int(input.at(i))==10 ){
								argValue[token]=1;
								addToken(tokens, token, "98", "ERR2", quoteLoc, LEN+1, "");
                                
                                break;
							}
							LEN++;
						}
				}						
				
				
				
				/* newline lexical */
				else if(int(input.at(i)) == 10){
					argValue[token]=1;
					addToken(tokens, token, "6", "NEWLINE", i,1, "" );
					i++;
					
				}

				/* whitespace lexical  */
				
				

				/* whitespace lexical  */
				
				else if(int(input.at(i)) == 32){
					//cout<<"whitespace!!"<<endl;
					argValue[token]=1;
                    addToken(tokens, token, "5", "WS", i, 1, "" );
					
					i++;        
                                }
				

				/* comment lexical= assuming any line after # is a comment, next line is normal */
				
				else if ( input.at(i) == '#'){
					quoteLoc=i;
					i++;
					while((int(input.at(i)) != 10)) {
						i++;
						LEN++;
					}
					
					argValue[token]=1;	
					addToken(tokens, token, "7", "COMMENT", quoteLoc,LEN, input.substr(quoteLoc+1,i-quoteLoc-1) );
					
				}

				else if(isInAlphabet(int(input.at(i))) ){
					if(int(input.at(i)) == 33 )
					{
						if((i+1) < input.size())
						{
							if(input.at(i+1) == '=')
							{
								addToken(tokens, token,"31", "!=", i, 1, "" );
								i++;	
							}
							else
							{
								addToken(tokens, token,"12",  "!", i, 1, "" );
							}
						}
					}
					else if( int(input.at(i)) == 40  ){
						addToken(tokens, token,"33", "(", i, 1, "" );	
					}
					else if( int(input.at(i)) ==  41 ){
						addToken(tokens, token,"34", ")", i, 1, "" );	
					}
					else if( int(input.at(i)) == 37  ){
						addToken(tokens, token,"13", "%", i, 1, "" );	
					}
					else if( int(input.at(i)) == 38  ){
						addToken(tokens, token,"14",  "&", i,1, "" );
					}
					else if( int(input.at(i)) == 39  ){
						addToken(tokens, token, "15",  "|", i,1, "" );
					}
					else if( int(input.at(i)) == 43  ){
						addToken(tokens, token,"16",  "+", i,1, "" );
					}
					else if( int(input.at(i)) == 45  ){
						addToken(tokens, token,"17",  "-", i,1, "" );
					}
					else if( int(input.at(i)) == 42  ){
						addToken(tokens, token, "18", "*", i, 1, "" );
					}
					else if( int(input.at(i)) == 47  ){
						addToken(tokens, token,"19",  "/", i,1, "" );

					}
					else if( int(input.at(i)) == 123  ){
						addToken(tokens, token,"20",  "{", i, 1, "" );
					}
					else if( int(input.at(i)) == 124  ){
						addToken(tokens, token,"15",  "|", i, 1, "" );
					}
					else if( int(input.at(i)) == 125 ){
						addToken(tokens, token,"21",  "}", i,1, "" );
					}
					else if( int(input.at(i)) == 91  ){
						addToken(tokens, token,"22", "[", i, 1, "" );
					}
					else if( int(input.at(i)) == 93  ){
						addToken(tokens, token,"23", "]", i,1, "" );
					}
					else if(int(input.at(i)) == 59  ){
						addToken(tokens, token,"24", ";", i,1, "" );
					}
					else if(int(input.at(i)) == 44 ){
						addToken(tokens, token,"25", ",", i,1, "" );
					}
					else if ( int(input.at(i)) == 60 )
					{
						
						if((i+1) < input.size())
						{
							if(input.at(i+1) == '=')
							{
								addToken(tokens, token,"29", "<=", i, 1, "" );
								i++;	
							}
							else
							{
								addToken(tokens, token,"26",  "<", i, 1, "" );
							}
						}
					}
					else if(int(input.at(i)) == 62 )
					{
						if((i+1) < input.size())
						{
							if(input.at(i+1) == '=')
							{
								addToken(tokens, token,"30", ">=", i, 1, "" );
								i++;	
							}
							else
							{
								addToken(tokens, token,"27",  ">", i, 1, "" );
							}
						}	

					}
					else if(int(input.at(i)) == 61 )
					{
						addToken(tokens, token,"28", "=", i, 1, "" );
					}
					else if(int(input.at(i)) == 40 ){
                                                addToken(tokens, token,"29", "(", i, 1, "" );
                                        }
					else if(int(input.at(i)) == 41 ){
                                                addToken(tokens, token,"28", ")", i, 1, "" );
                                        }
                    else if(int(input.at(i)) == 58) 
                    {
                    	if((i+1) < input.size())
						{
							if(input.at(i+1) == '=')
							{
								addToken(tokens, token,"32", ":=", i, 1, "" );
								i++;	
							}
							else
							{
								addToken(tokens, token,"26",  "<", i, 1, "" );
							}
						}
                    }

					else{
						isBadChar(i);
					}
					i++;
				}																
			}
		}



	Parser(){} 


		

		void parse_error(int &pEr)
		{
			if(pEr==0)
			{
				cout<<"Parse error"<<endl<<endl;
				pEr++;
			}
			
		}

		bool checkBound(int tokenVal, int xx)
		{
			
			if(tokenVal == vec.size())
			{	
				return false;
			}
			return true;
		}

		int sub_token(string lb, int &i, int &tokenVal)
		{
			if(checkBound(tokenVal, i))
			{
				if((val1[tokenVal]== lb) || (lb==""))
					{
						return i;
					}
					else
					{
						return 0;
					}
					

			}
			else
			{
				
				return 0;
			}
			
		}
		
		int handleTokens(int &i, int &tokenVal, int pID)
		{

			//cout<<tokens1[i].getVal()<<endl;
			switch(pID)
			{
				case 1:
					return sub_token("",i,tokenVal);

				case 2:
					return sub_token("",i,tokenVal);

				case 3:
					return sub_token("",i,tokenVal);

				case 4:
					return sub_token("",i,tokenVal);

				case 8:
					return sub_token("for", i,tokenVal);

				case 9:
					return sub_token("while", i,tokenVal);

				case 10:
					return sub_token("if", i,tokenVal);

				case 11:
					return sub_token("else", i,tokenVal);

				case 12:
					return sub_token("!",i,tokenVal);

				case 14:
					return sub_token("&",i,tokenVal);

				case 15:
					return sub_token("|",i,tokenVal);

				case 16:
					return sub_token("+", i,tokenVal);

				case 17:
					return sub_token("-", i,tokenVal);

				case 18:
					return sub_token("*", i,tokenVal);

				case 19:
					return sub_token("/", i,tokenVal);

				case 20:
					return sub_token("{", i,tokenVal);

				case 21:
					return sub_token("}", i,tokenVal);
				
				case 22:
					return sub_token("[", i,tokenVal);

				case 23:
					return sub_token("]", i,tokenVal);

				case 24:
					return sub_token(";", i,tokenVal);

				case 26:
					return sub_token("<", i,tokenVal);

				case 27:
					return sub_token(">", i,tokenVal);

				case 28:
					return sub_token("=", i,tokenVal);

				case 31:
					return sub_token("!=", i,tokenVal);

				case 32:
					return sub_token(":=", i,tokenVal);

				case 33:
					return sub_token("(", i,tokenVal);

				case 34:
					return sub_token(")", i,tokenVal);

				default:
					return 0;
			}
		}

		int cond_expr1(node** root, int &i, int &tokenVal)
		{
			indexR=i;
			i++;

			retVal=handleTokens(i, tokenVal, 15);

			if(retVal)
			{
				ptr[i]= tokens1[tokenVal];
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				tokenVal++;					
			}
			else
			{
				i--;
				return i;  // epsilon value 
			}

			i++;
			ptr[i] = new node(false, true, 0, 0, 0, "",0,0,"and_expr");
			(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
			retVal=and_expr(&ptr[i],i,tokenVal);


			if(retVal)
			{
				i++;
				ptr[i] = new node(false, true, 0, 0, 0, "",0,0,"cond_expr1");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				retVal=cond_expr1(&ptr[i],i,tokenVal);
			}
			else
			{	
				int temp1=i;
				for(int dd=temp1;dd > indexR;dd--)
				{
					if((*ptr[dd]).getTerm()==false)
					{
						delete ptr[dd];
					}
					
					i--;

				}
				(*root)->delChild(); //and_expr delteted. since vector makes a copy of push_back element you can delete
				(*root)->delChild(); // | deleted

				parse_error(pError);
				return 0; 
			}

			return retVal; //if error retVal is 0 or it will return index i

		}

		int cond_expr(node** root, int &i,int &tokenVal)
		{
			indexR=i;
			i++;

			ptr[i] = new node(false, true, 0, 0, 0, "",0,0,"and_expr");
			(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
			retVal=and_expr(&ptr[i],i,tokenVal);

			if(retVal)
			{
				i++;
				ptr[i] = new node(false, true, 0, 0, 0, "",0,0,"cond_expr1");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				retVal=cond_expr1(&ptr[i],i,tokenVal);

			}

			return retVal;

		}

		int and_expr1(node** root, int &i,int &tokenVal)
		{
			indexR=i;
			i++;

			retVal=handleTokens(i, tokenVal, 14);

			if(retVal)
			{
				ptr[i]= tokens1[tokenVal];
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				tokenVal++;					
			}
			else
			{
				i--;
				return i;  // epsilon value 
			}

			i++;
			ptr[i] = new node(false, true, 0, 0, 0, "",0,0,"cmp_expr");
			(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
			retVal=cmp_expr(&ptr[i],i,tokenVal);


			if(retVal)
			{
				i++;
				ptr[i] = new node(false, true, 0, 0, 0, "",0,0,"and_expr1");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				retVal=and_expr1(&ptr[i],i,tokenVal);
			}
			else
			{
				int temp1=i;
				for(int dd=temp1;dd > indexR;dd--)
				{
					if((*ptr[dd]).getTerm()==false)
					{
						delete ptr[dd];
					}
					
					i--;

				}
				(*root)->delChild(); //and_expr delteted
				(*root)->delChild(); // & deleted

				parse_error(pError);
				return 0;
			}

			return retVal; //if error retVal is 0 or it will return index i

		}

		int and_expr(node** root, int &i,int &tokenVal)
		{
			indexR=i;
			i++;

			ptr[i] = new node(false, true, 0, 0, 0, "",0,0,"eq_expr");
			(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
			retVal=eq_expr(&ptr[i],i,tokenVal);

			if(retVal)
			{
				i++;
				ptr[i] = new node(false, true, 0, 0, 0, "",0,0,"and_expr1");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				retVal=and_expr1(&ptr[i],i,tokenVal);

			}

			return retVal;

		}

		int eq_expr1(node** root, int &i,int &tokenVal)
		{
			indexR=i;
			i++;

			retVal=handleTokens(i, tokenVal, 28);

			if(retVal)
			{
				ptr[i]= tokens1[tokenVal];
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				tokenVal++;					
			}
			else
			{
				i--;
				return i;  // epsilon value 
			}

			i++;
			ptr[i] = new node(false, true, 0, 0, 0, "",0,0,"cmp_expr");
			(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
			retVal=cmp_expr(&ptr[i],i,tokenVal);


			if(retVal)
			{
				i++;
				ptr[i] = new node(false, true, 0, 0, 0, "",0,0,"eq_expr1");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				retVal=eq_expr1(&ptr[i],i,tokenVal);
			}
			else
			{
				int temp1=i;
				for(int dd=temp1;dd > indexR;dd--)
				{
					if((*ptr[dd]).getTerm()==false)
					{
						delete ptr[dd];
					}
					
					i--;

				}
				(*root)->delChild(); //and_expr delteted
				(*root)->delChild(); // | deleted

				parse_error(pError);
				return 0;
			}

			return retVal; //if error retVal is 0 or it will return index i

		}

		int eq_expr(node** root, int &i,int &tokenVal)
		{
			indexR=i;
			i++;
			
			ptr[i] = new node(false, true, 0, 0, 0, "",0,0,"cmp_expr");
			(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
			retVal=cmp_expr(&ptr[i],i,tokenVal);

			if(retVal)
			{
				i++;
				ptr[i] = new node(false, true, 0, 0, 0, "",0,0,"eq_expr1");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				retVal=eq_expr1(&ptr[i],i,tokenVal);
;
			}

			return retVal;
		}

		int cmp_expr1(node** root, int &i,int &tokenVal)
		{
			indexR=i;
			i++;


			retVal=checkBound(tokenVal, i);
			if(retVal==0)
			{
				return 0;
			}

		
			if(name[tokenVal] == "<")
			{
				retVal=handleTokens(i, tokenVal,26);
			}
			else if(name[tokenVal] == ">")
			{
				retVal=handleTokens(i, tokenVal,27);
			}
			else if(name[tokenVal] == "<=")
			{
				retVal=handleTokens(i, tokenVal,29);
			}
			else if(name[tokenVal] == ">=")
			{
				retVal=handleTokens(i, tokenVal,30);
			}
			else
			{
				retVal=0;
			}

			if(retVal)
			{
				if(retVal)
				{
					ptr[i]= tokens1[tokenVal];
					(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
					tokenVal++;					
				}

				i++;
				ptr[i] = new node(false, true, 0, 0, 0, "",0,0,"expr");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				retVal=expr(&ptr[i],i,tokenVal);
			}
			else
			{
				i--;
				return i; //epsilon
			}

			if(retVal)
			{
				i++;
				ptr[i] = new node(false, true, 0, 0, 0, "",0,0,"cmp_expr1");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				retVal=cmp_expr1(&ptr[i],i,tokenVal);

			}
			else
			{
				int temp1=i;
				for(int dd=temp1;dd > indexR;dd--)
				{
					if((*ptr[dd]).getTerm()==false) //non-terminal
					{
						delete ptr[dd];
					}
					
					i--;

				}
				(*root)->delChild(); //and_expr delteted
				(*root)->delChild(); // | deleted

				parse_error(pError);
				return 0;
			}

			return retVal; //if error retVal is 0 or it will return index i

		}

		int cmp_expr(node** root, int &i,int &tokenVal)
		{
			indexR=i;
			i++;

			ptr[i] = new node(false, true, 0, 0, 0, "",0,0,"expr");
			(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
			retVal=expr(&ptr[i],i,tokenVal);

			if(retVal)
			{
				i++;
				ptr[i] = new node(false, true, 0, 0, 0, "",0,0,"cmp_expr1");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				retVal=cmp_expr1(&ptr[i],i,tokenVal);
			}

			return retVal;
		}

		int opt_cond_expr(node** root, int &i,int &tokenVal)
		{
			indexR=i;
			i++;

			ptr[i]= new node(false, true, 0, 0, 0, "",0,0,"cond_expr");
			(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
			retVal=cond_expr(&ptr[i],i,tokenVal);

			if(retVal==0)
			{
				int temp1=i;
				for(int dd=temp1;dd > indexR;dd--)
				{
					if((*ptr[dd]).getTerm()==false)
					{
						delete ptr[dd];
					}
					
					i--;

				}
				(*root)->delChild(); //cond_expr delteted


				return i; //epsilon
			}
			return retVal;

		}

		int opt_assign(node** root, int &i,int &tokenVal)
		{
			indexR=i;
			i++;

			ptr[i] = new node(false, true, 0, 0, 0, "",0,0,"assign_stmt");
			(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
			retVal=assign_stmt(&ptr[i],i,tokenVal);

			if(retVal==0)
			{
				int temp1=i;
				for(int dd=temp1;dd > indexR;dd--)
				{
					if((*ptr[dd]).getTerm()==false)
					{
						delete ptr[dd];
					}
					
					i--;

				}
				(*root)->delChild(); //cond_expr delteted


				return i; //epsilon
			}
			return retVal;
		}

		int opt_else(node** root, int &i,int &tokenVal)
		{
			indexR=i;
			i++;

			retVal= handleTokens(i, tokenVal,11);

			if(retVal)
			{
				ptr[i]= tokens1[tokenVal];
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				tokenVal++;					
			}

			else
			{
				i--;
				return i;
			}

			retVal= handleTokens(i, tokenVal,20);

			if(retVal)
			{
				i++;
				ptr[i]= tokens1[tokenVal];
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				tokenVal++;					
			}

			else
			{
				parse_error(pError);
				return i;
			}


			if(retVal)
			{
				i++;
				ptr[i] = new node(false, true, 0, 0, 0, "",0,0,"stmt");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				retVal=stmt(&ptr[i],i,tokenVal);
			}


			if(retVal)
			{
				retVal=handleTokens(i, tokenVal,21);
				if(retVal)
				{
					i++;
					ptr[i]= tokens1[tokenVal];
					(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
					tokenVal++;					
				}
			}

			if(retVal==0)
			{
				parse_error(pError);
			}

			return retVal;
		}

		int while_stmt(node** root, int &i,int &tokenVal)
		{
			indexR=i;	
			i++;

			retVal= handleTokens(i, tokenVal,9);


			if(retVal)
			{
				ptr[i]= tokens1[tokenVal];
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				tokenVal++;					
			}

			retVal= handleTokens(i, tokenVal,33);

			if(retVal)
			{
				i++;
				ptr[i]= tokens1[tokenVal];
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				tokenVal++;					
			}



			if(retVal)
			{
				i++;
				ptr[i] = new node(false, true, 0, 0, 0, "",0,0,"cond_expr");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				retVal=cond_expr(&ptr[i],i,tokenVal);
			}

			if(retVal)
			{
				retVal=handleTokens(i, tokenVal,34);
				if(retVal)
				{
					i++;
					ptr[i]= tokens1[tokenVal];
					(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
					tokenVal++;					
				}
			}

			if(retVal)
			{
				retVal=handleTokens(i, tokenVal,20);

				if(retVal)
				{
					i++;
					ptr[i]= tokens1[tokenVal];
					(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
					tokenVal++;					
				}
			}

			if(retVal)
			{
				i++;
				ptr[i] = new node(false, true, 0, 0, 0, "",0,0,"stmt");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				retVal=stmt(&ptr[i],i,tokenVal);
			}

			if(retVal)
			{
				retVal=handleTokens(i, tokenVal,21);
				if(retVal)
				{
					i++;
					ptr[i]= tokens1[tokenVal];
					(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
					tokenVal++;					
				}
			}

			return retVal;

		}

		int for_stmt(node** root, int &i,int &tokenVal)
		{
			indexR=i;
			i++;

			retVal= handleTokens(i, tokenVal,8);

			if(retVal)
			{
				ptr[i]= tokens1[tokenVal];
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				tokenVal++;					
			}

			retVal= handleTokens(i, tokenVal,33);

			if(retVal)
			{
				i++;
				ptr[i]= tokens1[tokenVal];
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				tokenVal++;					
			}


			if(retVal)
			{
				i++;
				ptr[i] = new node(false, true, 0, 0, 0, "",0,0,"opt_assign");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				retVal=opt_assign(&ptr[i],i,tokenVal);
			}

			if(retVal)
			{
				retVal=handleTokens(i, tokenVal,24);
				if(retVal)
				{
					i++;
					ptr[i]= tokens1[tokenVal];
					(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
					tokenVal++;					
				}

			}

			if(retVal)
			{
				i++;
				ptr[i]= new node(false, true, 0, 0, 0, "",0,0,"opt_cond_expr");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				retVal=opt_cond_expr(&ptr[i],i,tokenVal);
			}

			if(retVal)
			{
				retVal=handleTokens(i, tokenVal,24);
				if(retVal)
				{
					i++;
					ptr[i]= tokens1[tokenVal];
					(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
					tokenVal++;					
				}

			}

			if(retVal)
			{
				i++;
				ptr[i] = new node(false, true, 0, 0, 0, "",0,0,"opt_assign");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				retVal=opt_assign(&ptr[i],i,tokenVal);
			}

			if(retVal)
			{
				retVal=handleTokens(i, tokenVal,34);
				if(retVal)
				{
					i++;
					ptr[i]= tokens1[tokenVal];
					(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
					tokenVal++;					
				}

			}

			if(retVal)
			{
				retVal=handleTokens(i, tokenVal,20);
				if(retVal)
				{
					i++;
					ptr[i]= tokens1[tokenVal];
					(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
					tokenVal++;					
				}

			}

			if(retVal)
			{
				i++;
				ptr[i]= new node(false, true, 0, 0, 0, "",0,0,"stmt");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				retVal=stmt(&ptr[i],i,tokenVal);
			}

			if(retVal)
			{
				retVal=handleTokens(i, tokenVal,21);
				if(retVal)
				{
					i++;
					ptr[i]= tokens1[tokenVal];
					(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
					tokenVal++;					
				}

			}

			return retVal;
		}

		int if_stmt(node** root, int &i,int &tokenVal)
		{
			indexR=i;
			i++;

			retVal= handleTokens(i, tokenVal,10);

			if(retVal)
			{
				ptr[i]= tokens1[tokenVal];
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				tokenVal++;					
			}

			retVal= handleTokens(i, tokenVal,33);

			if(retVal)
			{
				i++;
				ptr[i]= tokens1[tokenVal];
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				tokenVal++;					
			}

			if(retVal)
			{
				i++;
				ptr[i] = new node(false, true, 0, 0, 0, "",0,0,"cond_expr");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				retVal=cond_expr(&ptr[i],i,tokenVal);
			}

			if(retVal)
			{
				retVal=handleTokens(i, tokenVal,34);
				if(retVal)
				{
					i++;
					ptr[i]= tokens1[tokenVal];
					(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
					tokenVal++;
				}
			}

			if(retVal)
			{
				retVal=handleTokens(i, tokenVal,20);
				if(retVal)
				{
					i++;
					ptr[i]= tokens1[tokenVal];
					(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
					tokenVal++;
				}
			}

			if(retVal)
			{
				i++;
				ptr[i] = new node(false, true, 0, 0, 0, "",0,0,"stmt");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				retVal=stmt(&ptr[i],i,tokenVal);
			}

			if(retVal)
			{
				retVal=handleTokens(i, tokenVal,21);
				if(retVal)
				{
					i++;
					ptr[i]= tokens1[tokenVal];
					(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
					tokenVal++;
				}
			}

			if(retVal)
			{
				i++;
				ptr[i] = new node(false, true, 0, 0, 0, "",0,0,"opt_else");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				retVal=opt_else(&ptr[i],i,tokenVal);
			}

			return retVal;

		}

		int assign_stmt(node** root, int &i, int &tokenVal)
		{
			indexR=i;
			i++;

			retVal=handleTokens(i, tokenVal,1);

			if(retVal)
			{
				ptr[i]= tokens1[tokenVal];
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				tokenVal++;					
			}
			

			if(retVal)
			{
				retVal=handleTokens(i, tokenVal,32);
				if(retVal)
				{
					i++;
					ptr[i]= tokens1[tokenVal];
					(*root)->addChild(&ptr[i]); (*root)->addIndex(i); // := added	
					tokenVal++;
				}
						
			}

			if(retVal)
			{
				i++;
				ptr[i]= new node(false, true, 0, 0, 0, "",0,0,"expr");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);

				retVal=expr(&ptr[i], i,tokenVal);
			}


			return retVal;
		}

		int output_stmt(node** root, int &i,int &tokenVal)
		{
			indexR=i;
			i++;
					
			retVal=handleTokens(i, tokenVal,22);

			if(retVal)
			{
				ptr[i]= tokens1[tokenVal];
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				tokenVal++;					
			}

			if(retVal)
			{
				i++;
				ptr[i]= new node(false, true, 0, 0, 0, "",0,0,"expr");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				retVal=expr(&ptr[i], i,tokenVal);
			}

			if(retVal)
			{
				retVal=handleTokens(i, tokenVal,23);
				if(retVal)
				{
					i++;
					ptr[i]= tokens1[tokenVal];
					(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
					tokenVal++;				
				}
			}

			if(retVal)
			{
				retVal=handleTokens(i, tokenVal,24);
				if(retVal)
				{
					i++;
					ptr[i]= tokens1[tokenVal];
					(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
					tokenVal++;				
				}

			}

			return retVal;
		}



		int basic_expr(node** root, int &i,int &tokenVal)
		{
			indexR=i;
			i++;

			retVal=checkBound(tokenVal, i);
			if(retVal==0)
			{
				return 0;
			}

			if(name[tokenVal] == "ID")
			{
				retVal=handleTokens(i, tokenVal,1);
			}
			else if(name[tokenVal] == "STR")
			{
				retVal=handleTokens(i, tokenVal,2);
			}
			else if(name[tokenVal] == "INT")
			{
				retVal=handleTokens(i, tokenVal,3);
			}

			else if(name[tokenVal] == "FLOAT")
			{
				retVal=handleTokens(i, tokenVal,4);
			}
			else
			{
				retVal=0;
			}

			if(retVal)
				{
					ptr[i]= tokens1[tokenVal];
					(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
					tokenVal++;
				}
				
			return retVal;
		}

		int paren_expr(node** root, int &i,int &tokenVal)
		{
			indexR=i;
			i++;
			
			retVal=handleTokens(i, tokenVal, 33);
			if(retVal)
			{
				ptr[i]= tokens1[tokenVal];
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				tokenVal++;
			}

			if(retVal)
			{
				i++;
				ptr[i]= new node(false, true, 0, 0, 0, "",0,0,"basic_expr");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);

				retVal=basic_expr(&ptr[i], i,tokenVal);

				if(retVal)
				{
					retVal=handleTokens(i, tokenVal, 34);
					if(retVal)
					{
						i++;
						ptr[i]=tokens1[tokenVal];
						(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
						tokenVal++;						
					}

				}
				
				return retVal;
			}
			else
			{
				ptr[i]= new node(false, true, 0, 0, 0, "",0,0,"basic_expr");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);				
				retVal=basic_expr(&ptr[i], i,tokenVal);
				return retVal;
			}
			
		}

		int unary_expr(node** root, int &i, int &tokenVal)
		{
			indexR=i;
			i++;

			string unary_temp= val1[tokenVal];
			
			if(unary_temp == "!")
			{
				retVal=handleTokens(i, tokenVal,12);
			}
			else if(unary_temp == "+")
			{
				retVal=handleTokens(i, tokenVal,16);
			}
			else if(unary_temp == "-")
			{
				retVal=handleTokens(i, tokenVal,17);
			}
			else
			{
				retVal=0;
			}


			if(retVal)
			{
				ptr[i]= tokens1[tokenVal];
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);				
				tokenVal++;

				i++;
				ptr[i]= new node(false, true, 0, 0, 0, "",0,0,"expr");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				retVal= expr(&ptr[i],i,tokenVal);

				return retVal;				
			}
			else
			{
				ptr[i]= new node(false, true, 0, 0, 0, "",0,0,"paren_expr");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);

				retVal=paren_expr(&ptr[i], i,tokenVal);

				return retVal;
			}
		}

		int mult_expr1(node** root, int &i, int &tokenVal)
		{
			indexR=i;	
			i++;
			retVal=handleTokens(i, tokenVal, 18);
			if(retVal)
			{
				ptr[i]= tokens1[tokenVal];
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				tokenVal++;
			}
			else
			{
				i--;
				return i;
			}

			if(retVal)
			{
				i++;
				ptr[i]= new node(false, true, 0, 0, 0, "",0,0,"unary_expr");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);

				retVal=unary_expr(&ptr[i], i,tokenVal); // * found so go ahead;
				  
			}
			else
			{
				parse_error(pError);
				return 0;
			}

			if(retVal)
			{
				i++;
				ptr[i]= new node(false, true, 0, 0, 0, "",0,0,"mult_expr1");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);				

				retVal=mult_expr1(&ptr[i], i,tokenVal);				
			}
			else
			{
				parse_error(pError);
				return 0;
			}

			if(retVal ==0)
			{
				parse_error(pError);
			}

			return retVal; //if 0 it will give epsilon  or it will return index i

		}

		int mult_expr(node** root, int &i, int &tokenVal)
		{
			indexR=i;	
			i++;

			ptr[i]= new node(false, true, 0, 0, 0, "",0,0,"unary_expr");
			(*root)->addChild(&ptr[i]); (*root)->addIndex(i);

			retVal=unary_expr(&ptr[i] , i,tokenVal);


			if(retVal==0)
			{
				parse_error(pError);
				return 0;
			}
			else
			{
				i++;
				ptr[i]= new node(false, true, 0, 0, 0, "",0,0,"mult_expr1");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);				
				retVal= mult_expr1(&ptr[i], i,tokenVal);
			}

			if(retVal==0)
			{
				parse_error(pError);
			}

			return retVal;

		}


		int expr1(node** root, int &i, int &tokenVal)
		{	
			indexR=i;	
			i++;
			retVal=handleTokens(i, tokenVal, 16);
			if(retVal)
			{
				ptr[i]= tokens1[tokenVal];
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				tokenVal++;
			}

			else
			{
				i--;
				return i;
			}

			if(retVal)
			{
				i++;
				ptr[i]= new node(false, true, 0, 0, 0, "",0,0,"mult_expr");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);

				retVal=mult_expr(&ptr[i], i,tokenVal); // + found so go ahead;
				  
			}
			else
			{
				parse_error(pError);
				return 0;
			}

			if(retVal)
			{
				i++;
				ptr[i]= new node(false, true, 0, 0, 0, "",0,0,"expr1");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);				

				retVal=expr1(&ptr[i], i,tokenVal);				
			}
			else
			{
				parse_error(pError);
				return 0;
			}

			if(retVal ==0)
			{
				parse_error(pError);
			}

			return retVal; //if 0 it will give epsilon  or it will return index i

		}

		int expr(node** root, int &i, int &tokenVal)
		{	
			indexR=i;
			i++;
			
			ptr[i]= new node(false, true, 0, 0, 0, "",0,0,"mult_expr");
			(*root)->addChild(&ptr[i]); (*root)->addIndex(i);	

			retVal=mult_expr(&ptr[i],i,tokenVal);	
		



			if(retVal==0)
			{
				parse_error(pError);
				return 0;
			}
			else
			{
				i++;
				ptr[i]= new node(false, true, 0, 0, 0, "",0,0,"expr1");
				(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
				retVal=expr1(&ptr[i], i,tokenVal);
			}
			if(retVal==0)
			{
				parse_error(pError);
			}

			return retVal; //if error retVal is 0 or it will return index i


		}

		bool checkError()
		{
			for(int h=0; h< vec.size();h++)
			{
				if((name[h]=="ERR1") || (name[h]=="ERR2") || (name[h]=="ERR3"))
				{
					return true;
				}
			}
			return false;

		}

		int stmt(node** root, int &i, int &tokenVal) 
		{

				if(checkError())
				{
					cout<<"Lex error"<<endl<<endl; //lex error
					return 0;
				}

				if(checkBound(tokenVal, i))
				{
					parseID= id[tokenVal];

					if(i==0)
					{
						i++;
					}
					
				}
				else
				{
					return i;
				}

				


				switch(parseID)
				{
					case 9: //while
					{
						if(i > 1)
						{
							i++;
						}

						ptr[i]= new node(false, true, 0, 0, 0, "",0,0,"while_stmt");
						(*root)->addChild(&ptr[i]); (*root)->addIndex(i);

						retVal= while_stmt(&ptr[i], i,tokenVal);

						if(retVal==0)
						{
							parse_error(pError);
							return 0;
						}
						else
						{	
							i++;
							ptr[i]= new node(false, true, 0, 0, 0, "",0,0,"stmt");
							(*root)->addChild(&ptr[i]); (*root)->addIndex(i);	
							retVal=stmt(&ptr[i],i,tokenVal);	
						}

						return i;
					}

						

					case 8: //for
					{
						if(i > 1)
						{
							i++;
						}
						ptr[i]= new node(false, true, 0, 0, 0, "",0,0,"for_stmt");
						(*root)->addChild(&ptr[i]); (*root)->addIndex(i);	
						retVal=for_stmt(&ptr[i],i,tokenVal);	

						if(retVal==0)
						{
							parse_error(pError);
							return 0;
						}
						else
						{
							i++;
							ptr[i]= new node(false, true, 0, 0, 0, "",0,0,"stmt");
							(*root)->addChild(&ptr[i]); (*root)->addIndex(i);	
							retVal=stmt(&ptr[i],i,tokenVal);	
						}

						if(retVal==0)
						{
							parse_error(pError);
							return 0;
						}
						else
						{
							return i;
						}
					}
						

					case 10: //if
					{
						if(i > 1)
						{
							i++;
						}
						ptr[i]= new node(false, true, 0, 0, 0, "",0,0,"if_stmt");
						(*root)->addChild(&ptr[i]); (*root)->addIndex(i);	
						retVal=if_stmt(&ptr[i],i,tokenVal);	

						if(retVal==0)
						{
							parse_error(pError);
							return 0;
						}
						else
						{
							i++;
							ptr[i]= new node(false, true, 0, 0, 0, "",0,0,"stmt");
							(*root)->addChild(&ptr[i]); (*root)->addIndex(i);	
							retVal=stmt(&ptr[i],i,tokenVal);	
						}

						if(retVal==0)
						{
							parse_error(pError);
							return 0;
						}
						else
						{
							return i;
						}

					}
						

					case 1: //ID := 
					{	
						if(i > 1)
						{
							i++;
						}

						ptr[i]= new node(false, true, 0, 0, 0, "",0,0,"assign_stmt");
						(*root)->addChild(&ptr[i]); (*root)->addIndex(i);	

						retVal=assign_stmt(&ptr[i],i,tokenVal);	
	

						if(retVal==0)
						{
							parse_error(pError);
							return 0;
						}
						else
						{	
							retVal=handleTokens(i, tokenVal,24);
							if(retVal)
							{	
								i++;
								ptr[i]= tokens1[tokenVal];
								(*root)->addChild(&ptr[i]); (*root)->addIndex(i);
								tokenVal++;
								
							}
							
						}

						if(retVal==0)
						{
							parse_error(pError);
							return 0;
						}
						else
						{
							i++;
							ptr[i]= new node(false, true, 0, 0, 0, "",0,0,"stmt");
							(*root)->addChild(&ptr[i]); (*root)->addIndex(i);	
							retVal=stmt(&ptr[i],i,tokenVal);

						}

						if(retVal==0)
						{
							parse_error(pError);
							return 0;
						}
						else
						{

							return i;
						}

					}	

						

					case 22: // [
					{
						if(i > 1)
						{
							i++;
						}
						ptr[i]= new node(false, true, 0, 0, 0, "",0,0,"output_stmt");
						(*root)->addChild(&ptr[i]); (*root)->addIndex(i);	
						retVal=output_stmt(&ptr[i],i,tokenVal);	

						if(retVal==0)
						{
							parse_error(pError);
							return 0;
						}
						else
						{
							i++;
							ptr[i]= new node(false, true, 0, 0, 0, "",0,0,"stmt");
							(*root)->addChild(&ptr[i]); (*root)->addIndex(i);	
							retVal=stmt(&ptr[i],i,tokenVal);	
						}	

						if(retVal==0)
						{
							parse_error(pError);
							return 0;
						}
						else
						{
							return i;
						}	

					}	


					case 97:
						cout<< "Lex error" <<endl<<endl;
						return 0;
					case 98:
						cout<< "Lex error" <<endl<<endl;
						return 0;
					case 99:
						cout<< "Lex error" <<endl<<endl;
						return 0;
					case 100:
						cout<< "Lex error" <<endl<<endl;;
						return 0;

					default:
						
						if(checkBound(tokenVal,i))
						{
							if(i == 1) // hasn't entered in the parsing yet
							{
								while(checkBound(tokenVal,i))
								{
									if(handleTokens(i,tokenVal,tokens1[tokenVal]->getType()))
									{
										tokenVal++;
									}
									else
									{
										cout<<"Unimplemented error"<<endl<<endl;
										return 0;
									}								
								}
								parse_error(pError);
								return 0;
							}


							if(handleTokens(i,tokenVal,tokens1[tokenVal]->getType()))
							{
								return i; //epsilon
							}

						}

				}
			}

			void lastIndex(int &ret)
			{
				int h=0; int max;
				temp=0;

				while(temp <= ret)
				{	
					if((*ptr[temp]).index.size() ==0)
					{
						(*ptr[temp]).nMax=temp;
						(*ptr[temp]).index.push_back(temp);

						indexVec.push_back((*ptr[temp]).index);

					}	
					else
					{
						indexVec.push_back((*ptr[temp]).index);
					}
					
					temp++;
				}

				temp=0;
				int counter;

				while(temp<=ret)
				{
					counter=(*ptr[temp]).nMax;
					counter= counter;

					while(counter != indexVec[counter][0])
					{
						counter=(*ptr[counter]).nMax;
					}

					(*ptr[temp]).endNode=counter;
					//cout<<(*ptr[temp]).endNode<<endl;
					temp++;
				}

				
			}

			void startParse(int &i, int &t)
			{
				ptr[i]= new node(false, true, 0, 0, 0, "",0,0,"stmt");
				
				retVal= stmt(&ptr[i], i,t);

				if(retVal != 0)
				{
					lastIndex(retVal);


					temp=0; int var=0;

					while(var != retVal+1)
					{
						if((*ptr[var]).getTerm()==false)
						{
							cout<<"<node>"<<"<nt>"<<(*ptr[var]).getVal()<<"</nt>"<<"<children>"<<endl;
						
						}
						else
						{
							if((*ptr[var]).noVal)
							{
								cout<<"<node>"<<"<id>"<<(*ptr[var]).getID()<<"</id>"<<"<typenum>"<<(*ptr[var]).getType()<<"</typenum>"<<"<typename>"<<(*ptr[var]).getName()<<"</typename>"<<endl;
								cout<<"<position>"<<(*ptr[var]).getPos()<<"</position>"<<"<length>"<<(*ptr[var]).getLen()<<"</length>"<<endl;
								cout<<"</node>"<<endl;
							}
							else
							{
								cout<<"<node>"<<"<id>"<<(*ptr[var]).getID()<<"</id>"<<"<typenum>"<<(*ptr[var]).getType()<<"</typenum>"<<"<typename>"<<(*ptr[var]).getName()<<"</typename>"<<endl;
								cout<<"<position>"<<(*ptr[var]).getPos()<<"</position>"<<"<length>"<<(*ptr[var]).getLen()<<"</length>"<<"<value>"<<(*ptr[var]).getVal()<<"</value>"<<endl;
								cout<<"</node>"<<endl;
							}

						}

						for(int h=0; h<=retVal;h++)
						{
							if((*ptr[h]).endNode == var)
							{
								if((*ptr[h]).getTerm()==false)
								{
									cout<<"</node></children>"<<endl;
								}	
							}
						}
					
						var++;
					}
				}

				//delete node objets

				delete ptr[0];

				if(i==1) //parse error value
				{
					i=0; 
				}	

				for(int z=1;z<=i;z++)
				{
					if((*ptr[z]).getTerm() == false)
					{	
						delete ptr[z];
					}	
					
					
				}

				//delete token objects
				
				for(int g=0;g<vec.size();g++)
				{
					delete tokens1[g];
					//tokens1++;
				}
			}

};

int main(int argc, char *argv[]){
	
	Parser par; int ret;
	string s; 
	int parsPointer=0; int tokenPointer=0; int arg=0;
	string input[100]; 
	int ln=0; 
	string z;
	
	


    while (1)
    {

        if(getline( cin, s ) && !s.empty())
        {
            input[ln]= s;
            ln++;
        }

        else if(s.empty())
        {
            break;
        }
    }


	
	for(int vr=0; vr<ln;vr++){
	
		z= z + input[vr] + "\n";
		
	}

	

	z=z + input[ln];

	par.setString(z); //good
	par.setArg(arg); //good
	par.analysis(); //good

	par.startParse(parsPointer,tokenPointer);

		
return 0;	
}

