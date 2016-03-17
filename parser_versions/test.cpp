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
		bool hasChildren;

		int setID(int var)
		{
			id=var;
		}

		int getID()
		{
			return id;
		}

		int setType(int num)
		{
			typeNum=num;
		}

		int getType()
		{
			return typeNum;
		}

		string setName(string name)
		{
			typeName1=name;
		}

		string getName()
		{
			return typeName1;
		}

		int setPos(int pos)
		{
			position=pos;
		}

		int setLen(int len)
		{
			length1=len;
		}

		string setVal(string val)
		{
			value1= val;
			
		}

		string getVal()
		{
			if(value1 == "")
			{
				//cout<<"you are reuturning typname"<<endl;
				return typeName1;
			}
			return value1;
		}

		bool setTerm(bool t)
		{
			terminal=t;
		}

		bool setChild(bool setCh)
		{
			hasChildren=setCh;
		}
		
		node(){}

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
		int i=0;
		int token=0; 
		int LEN=0;
		string total;	
		string str;
		bool floatFlag; int quoteLoc;int spec; int strlen;
		int argValue[100];
		int id[1024];
		string val1[1024];
		//node* tokens1= new node[1024];

		

		string input;int length;
        string tokens[1024];
	
        int arg;

        int parseID;
        //node tokens1[1024];
        node* tokens1= new node[1024];
		node* parseNodes= new node[1024];
		int retVal;
		int tokenVal=0;

		
		void setString(string s)
		{
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

                		node *tokens1 = new node(true,false,0,t,tp,typeName,pos,len,conf);
                		tokens1++;
                		id[size]=tp;
                		val1[size]= conf;
                		size++;
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
											//cout<<i<<endl;
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
								addToken(tokens, token,"26",  "<", i, 1, "" );
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


		

		void parse_error()
		{
			cout<<"Parsing error"<<endl;
		}

		bool checkBound(int xx)
		{
			if(xx == size)
			{	cout<<size<<endl;
				return false;
			}
			return true;
		}

		int sub_token(string lb, int &i, int &tokenVal)
		{
			if(checkBound(i))
			{
				if((val1[tokenVal]== lb) || (lb==""))
					{
						//cout<<"i am here"<<endl;
						tokens1[tokenVal].setTerm(true);
						tokens1[tokenVal].hasChildren=false;
						parseNodes[i]=tokens1[tokenVal];
						i++;
						tokenVal++;
					}
					else
					{
						return 0;
					}
					return i;

			}
			else
			{
				parse_error();
				return 0;
			}
			
		}
		
		int handleTokens(int &i, int pID)
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

				case 28:
					return sub_token("=", i,tokenVal);

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

		int cond_expr1(int &i)
		{
			retVal=handleTokens(i, 18);

			if(retVal==0)
			{
				return i;  // epsilon value 
			}
			else
			{
				retVal=and_expr(i); // | found so go ahead;
			}
			if(retVal)
			{
				retVal=cond_expr1(i);
			}

			return retVal; //if error retVal is 0 or it will return index i

		}

		int cond_expr(int &i)
		{
			node* parseNodes= new node(false, true, 0, 0, 0, "",0,0,"cond_expr");
			parseNodes++;
			i++;

			retVal= and_expr(i);

			if(retVal)
			{
				retVal=cond_expr1(i);
			}

			return retVal;

		}

		int and_expr1(int &i)
		{
			retVal=handleTokens(i, 14);

			if(retVal==0)
			{
				return i;  // epsilon value 
			}
			else
			{
				retVal=cmp_expr(i); // & found so go ahead;
			}
			if(retVal)
			{
				retVal=and_expr1(i);
			}

			return retVal; //if error retVal is 0 or it will return index i

		}

		int and_expr(int &i)
		{
			node* parseNodes= new node(false, true, 0, 0, 0, "",0,0,"and_expr");
			parseNodes++;
			i++;

			retVal= eq_expr(i);

			if(retVal)
			{
				retVal=and_expr1(i);
			}

			return retVal;

		}

		int eq_expr1(int &i)
		{
			retVal=handleTokens(i, 28);

			if(retVal==0)
			{
				return i;  // epsilon value 
			}
			else
			{
				retVal=cmp_expr(i); // = found so go ahead;
			}
			if(retVal)
			{
				retVal=eq_expr1(i);
			}

			return retVal; //if error retVal is 0 or it will return index i

		}

		int eq_expr(int &i)
		{
			node* parseNodes= new node(false, true, 0, 0, 0, "",0,0,"eq_expr");
			parseNodes++;
			i++;

			retVal= cmp_expr(i);

			if(retVal)
			{
				retVal=eq_expr1(i);
			}

			return retVal;


		}

		int cmp_expr1(int &i)
		{

			retVal=checkBound(i);
			if(retVal==0)
			{
				return 0;
			}

			if(tokens1[i].getVal() == "<")
			{
				retVal=handleTokens(i,26);
			}
			else if(tokens1[i].getVal() == ">")
			{
				retVal=handleTokens(i,27);
			}
			else if(tokens1[i].getVal() == "<=")
			{
				retVal=handleTokens(i,29);
			}
			else if(tokens1[i].getVal() == ">=")
			{
				retVal=handleTokens(i,30);
			}

			if(retVal==0)
			{
				return i;  // epsilon value 
			}
			else
			{
				retVal=expr(i); // < found so go ahead;
			}
			if(retVal)
			{
				retVal=cmp_expr1(i);
			}

			return retVal; //if error retVal is 0 or it will return index i

		}

		int cmp_expr(int &i)
		{
			node* parseNodes= new node(false, true, 0, 0, 0, "",0,0,"cmp_expr");
			parseNodes++;
			i++;

			retVal= expr(i);

			if(retVal)
			{
				retVal=cmp_expr1(i);
			}

			return retVal;
		}

		int opt_cond_expr(int &i)
		{
			node* parseNodes= new node(false, true, 0, 0, 0, "",0,0,"opt_cond_expr");
			parseNodes++;
			i++;

			retVal=cond_expr(i);

			return retVal;


		}

		int opt_assign(int &i)
		{
			node* parseNodes= new node(false, true, 0, 0, 0, "",0,0,"opt_assign");
			parseNodes++;
			i++;

			retVal=assign_stmt(i);

			return retVal;
		}

		int opt_else(int &i)
		{
			node* parseNodes= new node(false, true, 0, 0, 0, "",0,0,"opt_else");
			parseNodes++;
			i++;

			retVal=handleTokens(i,11);

			retVal=handleTokens(i,20);

			if(retVal)
			{
				retVal=stmt(i,tokenVal);
			}

			if(retVal)
			{
				retVal=handleTokens(i,21);
			}

			return retVal;
		}

		int while_stmt(int &i)
		{
			node* parseNodes= new node(false, true, 0, 0, 0, "",0,0,"while_stmt");
			parseNodes++;
			i++;

			retVal= handleTokens(i,9);

			retVal=handleTokens(i,33);

			if(retVal)
			{
				retVal=cond_expr(i);
			}

			if(retVal)
			{
				retVal=handleTokens(i,34);
			}

			if(retVal)
			{
				retVal=handleTokens(i,20);
			}

			if(retVal)
			{
				retVal=stmt(i,tokenVal);
			}

			if(retVal)
			{
				retVal=handleTokens(i,21);
			}

			return retVal;

		}

		int for_stmt(int &i)
		{
			node* parseNodes= new node(false, true, 0, 0, 0, "",0,0,"for_stmt");
			parseNodes++;
			i++;

			retVal= handleTokens(i,8);

			retVal= handleTokens(i,33);

			if(retVal)
			{
				retVal=opt_assign(i);
			}

			if(retVal)
			{
				retVal=handleTokens(i,24);
			}

			if(retVal)
			{
				retVal=opt_cond_expr(i);
			}

			if(retVal)
			{
				retVal=handleTokens(i,24);
			}

			if(retVal)
			{
				retVal=opt_assign(i);
			}

			if(retVal)
			{
				retVal=handleTokens(i,34);
			}

			if(retVal)
			{
				retVal=handleTokens(i,20);
			}

			if(retVal)
			{
				retVal=stmt(i,tokenVal);
			}

			if(retVal)
			{
				retVal=handleTokens(i,21);
			}

			return retVal;
		}

		int if_stmt(int &i)
		{
			node* parseNodes= new node(false, true, 0, 0, 0, "",0,0,"if_stmt");
			parseNodes++;
			i++;

			retVal= handleTokens(i,10);

			retVal= handleTokens(i,33);

			if(retVal)
			{
				retVal=cond_expr(i);
			}

			if(retVal)
			{
				retVal=handleTokens(i,34);
			}

			if(retVal)
			{
				retVal=handleTokens(i,20);
			}

			if(retVal)
			{
				retVal=stmt(i,tokenVal);
			}

			if(retVal)
			{
				retVal=handleTokens(i,21);
			}

			if(retVal)
			{
				retVal=handleTokens(i,34);
			}

			if(retVal)
			{
				retVal=opt_else(i);
			}

			return retVal;

		}

		int assign_stmt(int &i)
		{
			node* parseNodes= new node(false, true, 0, 0, 0, "",0,0,"assign_stmt");
			parseNodes++;
			i++;


			retVal=handleTokens(i,1);

			if(retVal)
			{
				retVal=handleTokens(i,32);
				
				
			}

			if(retVal)
			{
				cout<<i<<i<<i<<i<<i<<endl;
				retVal=expr(i);
				cout<<"back"<<endl;
				cout<<tokenVal<<endl;
			}

			return retVal;
		}

		int output_stmt(int &i)
		{
			node* parseNodes= new node(false, true, 0, 0, 0, "",0,0,"output_stmt");
			parseNodes++;
			i++;

			retVal=handleTokens(i,22);

			if(retVal)
			{
				retVal=expr(i);
			}

			if(retVal)
			{
				retVal=handleTokens(i,23);
			}

			if(retVal)
			{
				retVal=handleTokens(i,24);
			}

			return retVal;
		}



		int basic_expr(int &i)
		{

			node* parseNodes= new node(false, true, 0, 0, 0, "",0,0,"basic_expr");
			parseNodes++;
			i++;

			retVal=checkBound(i);
			if(retVal==0)
			{
				return 0;
			}

			if(tokens1[i].getName() == "ID")
			{
				retVal=handleTokens(i,1);
			}
			else if(tokens1[i].getName() == "STR")
			{
				retVal=handleTokens(i,2);
			}
			else if(tokens1[i].getName() == "INT")
			{
				retVal=handleTokens(i,2);
			}

			else if(tokens1[i].getName() == "FLOAT")
			{
				retVal=handleTokens(i,2);
			}

			return retVal;
		}

		int paren_expr(int &i)
		{
			node* parseNodes= new node(false, true, 0, 0, 0, "",0,0,"paren_expr");
			parseNodes++;
			i++;
			
			retVal=handleTokens(i, 33);

			if(retVal)
			{
				retVal=basic_expr(i);
				if(retVal)
				{
					retVal=handleTokens(i, 34);
				}
				
				return retVal;
			}
			else
			{
				retVal=basic_expr(i);
				return retVal;
			}
			
		}

		int unary_expr(int &i)
		{
			node* parseNodes= new node(false, true, 0, 0, 0, "",0,0,"unary_expr");
			parseNodes++;
			i++;

			cout<<i<<i<<i<<i<<endl;
			string unary_temp= tokens1[i].getVal();
			
			if(unary_temp == "!")
			{
				retVal=handleTokens(i,12);

				retVal= expr(i);

				return retVal;
			}
			else if(unary_temp == "+")
			{
				retVal=handleTokens(i,16);

				retVal= expr(i);

				return retVal;
			}
			else if(unary_temp == "-")
			{
				retVal=handleTokens(i,17);

				retVal= expr(i);

				return retVal;
			}
			else
			{
				cout<<i<<i<<i<<i<<endl;
				retVal=paren_expr(i);

				return retVal;
			}
		}

		int mult_expr1(int &i)
		{
			retVal=handleTokens(i, 18);

			if(retVal==0)
			{
				return i;  // epsilon value 
			}
			else
			{
				retVal=unary_expr(i); // * found so go ahead;
			}
			if(retVal==0)
			{
				return retVal;
			}
			else
			{
				retVal=mult_expr1(i);
			}

			return retVal; //if error retVal is 0 or it will return index i

		}

		int mult_expr(int &i)
		{
			node* parseNodes= new node(false, true, 0, 0, 0, "",0,0,"mult_expr");
			parseNodes++;
			i++;

			//cout<<i<<i<<i<<i<<endl;
			retVal=unary_expr(i);

			if(retVal==0)
			{
				parse_error();
				return 0;
			}
			else
			{
				retVal= mult_expr1(i);
			}

			return retVal;

		}


		int expr1(int &i)
		{	cout<<"expr1"<<endl;	
			cout<<tokenVal<<endl;	

			retVal=handleTokens(i, 16);

			if(retVal==0)
			{

				return i;  // epsilon value 
			}
			else
			{
				retVal=mult_expr(i); // + found so go ahead;
			}
			if(retVal==0)
			{
				return retVal;
			}
			else
			{
				retVal=expr1(i);
			}

			return retVal; //if error retVal is 0 or it will return index i

		}

		int expr(int &i)
		{
			node* parseNodes= new node(false, true, 0, 0, 0, "",0,0,"expr");
			parseNodes++;
			i++;
			cout<<i<<endl;
			retVal=mult_expr(i);
			cout<<"in expr"<<endl;
			cout<<i<<endl;

			if(retVal==0)
			{
				parse_error();
				return 0;
			}
			else
			{
				retVal=expr1(i);
			}

			return retVal; //if error retVal is 0 or it will return index i


		}

		int stmt(int &i, int &tokenVal) 
		{

				if(checkBound(i))
				{
					node* parseNodes= new node(false, true, 0, 0, 0, "",0,0,"stmt");
					parseNodes++;
				
					//cout<<"print parseID motherfucker"<<endl;
					parseID= id[tokenVal];
					cout<<parseID<<endl;
		
					i++;
				}
				else
				{
					parse_error();
					return 0;
				}

				


				switch(parseID)
				{
					case 9: //while
					{
						retVal= while_stmt(i);

						if(retVal==0)
						{
							parse_error();
							return 0;
						}
						else
						{		
							retVal=stmt(i,tokenVal);	
						}

						return retVal;
					}

						

					case 8: //for
					{
						retVal= for_stmt(i);

						if(retVal==0)
						{
							return 0;
						}
						else
						{
							retVal=stmt(i,tokenVal);
						}

						if(retVal==0)
						{
							return 0;
						}
						else
						{
							return i;
						}
					}
						

					case 10: //if
					{
						retVal= if_stmt(i);

						if(retVal==0)
						{
							return 0;
						}
						else
						{
							retVal=stmt(i,tokenVal);
						}

						if(retVal==0)
						{
							return 0;
						}
						else
						{
							return i;
						}

					}
						

					case 1: //ID := 
					{	

						retVal= assign_stmt(i);
						cout<<"good"<<endl;

						//cout<<tokenVal<<endl;
				

						if(retVal==0)
						{
							return 0;
						}
						else
						{
							retVal=handleTokens(i,24);
						}

						if(retVal==0)
						{
							return 0;
						}
						else
						{
							retVal=stmt(i,tokenVal);
						}

						if(retVal==0)
						{
							return 0;
						}
						else
						{
							return i;
						}

					}	

						

					case 22: // [
					{
						retVal= output_stmt(i);

						if(retVal==0)
						{
							return 0;
						}
						else
						{
							retVal=stmt(i,tokenVal);
						}

						if(retVal==0)
						{
							return 0;
						}
						else
						{
							return i;
						}	

					}	


					case 97:
						cout<< "Lex error" <<endl;
						break;
					case 98:
						cout<< "Lex error" <<endl;
						break;
					case 99:
						cout<< "Lex error" <<endl;
						break;
					case 100:
						cout<< "Lex error" <<endl;
						break;	

					default:
						cout<<"Unimplemented error"<<endl;
						break;


				}
			}

			void startParse(int &i, int &t)
			{
				retVal= stmt(i,t);
				
			}

			void printRes()
			{
				//cout<<"below is size"<<endl;
				//cout<<size<<endl;
				for(int z=0;z<size;z++)
				{
					//cout<<parseNodes[z].getVal()<<endl;
					cout<<tokens1[z].getVal()<<endl;
				}
			}

			void deleteObj()
			{
				for(int z=0;z<i;z++)
				{
					delete parseNodes;
					parseNodes--;
				}
				delete[] parseNodes;

				for(int z=0;z<size;z++)
				{
					delete tokens1;
					tokens1--;
				}
				delete[] tokens1;
			}

};

int main(int argc, char *argv[]){
	
	Parser par;
	string s; 
	int parsPointer=0; int tokenPointer=0; int arg=0;
	string input[100]; 
	int ln=0; 
	string z;
	


        while (1){

                if(getline( cin, s ) && !s.empty()){
                        input[ln]= s;
                        ln++;
                }

                else if(s.empty()){
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
	par.printRes();
	par.deleteObj();
	

		
return 0;	
}

