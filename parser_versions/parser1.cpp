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
			value1=val;
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
		}

		bool setChild(bool setCh)
		{
			hasChildren=setCh;
		}
		
		node(){}

		node(bool aa, bool bb, int cc, int dd, int ee, string ff, int gg, int hh, string ii){

			terminal=setTerm(aa);
			hasChildren= setChild(bb);
			children=cc;
			id=setID(dd);
			typeNum=setType(ee);
			typeName1=setName(ff);
			position=setPos(gg);
			length1=setLen(hh);
			value1=setVal(ii);
		};

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

class Lexical : public tools, public node
{
	public:
		//added data structures for parsing
		vector<node> tokens1;


		string input;int length;
                string tokens[100];
		//string (*p_token)[10][0]= &tokens;
                int arg;
		
		void setString(string s){
			input = s;
			length= input.size()-1;
		};
		
		void setArg(int i){
			arg= i;
		};
		
		void addToken(string tokens[100], int t, string type, string typeName, int pos, int len, string val ){

						int x= t+1;
                        stringstream ss,ss1,ss2;
                        string strNum,strNumP,strNumLen;
                        ss<<x; ss>>strNum;
                        ss1<<pos; ss1>>strNumP;
                        ss2<<len; ss2>>strNumLen;
                        int xx=0; int tp=0;
                        while(xx != type.size()){

                        		
                        		tp += ( int( type.at(xx) - '0' ) * pow( 10, (type.size() -xx -1)) ) ;
                        		xx++;

                        
                        }
                        
                //data structures for parsing
                if((type != "5") || (type != "6") || (type != "7"))
                {
                		node temp;
                		temp.setID(t);
                		temp.setType(tp);
                		temp.setName(typeName);
                		temp.setPos(pos);
                		temp.setLen(len);
                		temp.setVal(val);
                		temp.hasChildren=false;
                		temp.setTerm(true);
                		temp.children=0;

                		tokens1.push_back(temp);



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
		
		
		int i=0;
		int token=0; 
		int LEN=0;
		string total;	
		string str;
		bool floatFlag; int quoteLoc;int spec; int strlen;
		int argValue[100];
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
								
		void analysis(){
			
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
								addToken(tokens, token,"26",  "<", i, 1, "" );
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



	Lexical(){} 
		
	
};

class Parser : public Lexical
{
	public:
		int i=0;
		int j=0;
		int parseID;
		vector<node> parseNodes;
		int retVal;

		void parse_error()
		{
			cout<<"Parsing error"<<endl;
		}

		bool checkBound(int xx)
		{
			if(xx == tokens1.size())
			{
				return false;
			}
			return true;
		}

		int sub_token(string lb, int &i)
		{
			if(checkBound(i))
			{
				if((tokens1[i].getVal() == lb) || (lb==""))
					{
						parseNodes.push_back(tokens1[i]);
						i++;
					}
					else
					{
						parse_error();
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


			switch(pID)
			{
				case 1:
					return sub_token("",i);
				case 8:
					return sub_token("for", i);

				case 9:
					return sub_token("while", i);

				case 10:
					return sub_token("if", i);

				case 11:
					return sub_token("else", i);

				case 16:
					return sub_token("+", i);

				case 17:
					return sub_token("-", i);

				case 18:
					return sub_token("*", i);

				case 19:
					return sub_token("/", i);

				case 20:
					return sub_token("{", i);

				case 21:
					return sub_token("}", i);
				
				case 22:
					return sub_token("[", i);

				case 23:
					return sub_token("]", i);

				case 24:
					return sub_token(";", i);

				case 32:
					return sub_token(":=", i);

				case 33:
					return sub_token("(", i);

				case 34:
					return sub_token(")", i);

				default:
					return 0;
			}
		}

		int stmt(int &i, int j) //j=0 for statements non-zero for other grammer
			{
				if(checkBound(i))
				{
					//do nothing
				}
				else
				{
					parse_error();
					return 0;
				}

				if(j != 0)
				{
					parseID=j;
				}
				else
				{
					parseID= tokens1[i].getID();
					node newNode;
					newNode.setTerm(false);
					newNode.setVal("stmt");

					if(i< tokens1.size())
					{
						newNode.hasChildren=true;
					}
					else
					{
						cout<<"Parsing error"<<endl;
						return 0;
					}
					parseNodes.push_back(newNode);
				}
				

				switch(parseID)
				{
					case 9: //while
					{

						node newNode(false, true, 0, 0, 0, "",0,0,"while_stmt");
						
						parseNodes.push_back(newNode);

						retVal= handleTokens(i,9);


						if(retVal==0)
						{
							return 0;
						}

						retVal=handleTokens(i,33);

						if(retVal==0)
						{
							return 0;
						}


						//COND_STMT

						if(checkBound(i))
						{

							retVal= stmt(i,101); //cond_stmt

							if(retVal==0)
							{
								return 0;
							}
						}
						else
						{
							parse_error();
							return 0;
						}

						// COND_STMT ENDS

						retVal=handleTokens(i,34);

						if(retVal==0)
						{
							return 0;
						}

						retVal=handleTokens(i,20);

						if(retVal==0)
						{
							return 0;
						}

						//STMT

						if(checkBound(i))
						{

							retVal= stmt(i,0); //stmt

							if(retVal==0)
							{
								return 0;
							}
						}
						else
						{
							parse_error();
							return 0;
						}
						//STMT ENDS

						retVal=handleTokens(i,21);

						if(retVal==0)
						{
							return 0;
						}

						//STMT 
						if(checkBound(i))
						{

							retVal= stmt(i,0); //stmt

							if(retVal==0)
							{
								return 0;
							}
						}
						else
						{
							parse_error();
							return 0;
						}
						//STMT ENDS

						return i;
					}

					case 8: //for
					{
						node newNode(false, true, 0, 0, 0, "",0,0,"for_stmt");
						parseNodes.push_back(newNode);

						retVal= handleTokens(i,8);

						if(retVal==0)
						{
							return 0;
						}


						retVal=handleTokens(i,33);

						if(retVal==0)
						{
							return 0;
						}

						//OPT_ASSIGN_STMT

						if(checkBound(i))
						{
							retVal= stmt(i,102); //OPT_ASSIGN_stmt

							if(retVal==0)
							{
								return 0;
							}
						}
						else
						{
							parse_error();
							return 0;
						}
						//OPT_ASSIGN_STMT ENDS

						retVal=handleTokens(i,24);

						if(retVal==0)
						{
							return 0;
						}

						//OPT_COND_STMT 
						if(checkBound(i))
						{
							retVal= stmt(i,103); //OPT_COND_stmt

							if(retVal==0)
							{
								return 0;
							}
						}
						else
						{
							parse_error();
							return 0;
						}
						//OPT_COND STMT ENDS

						retVal=handleTokens(i,24);

						if(retVal==0)
						{
							return 0;
						}

						//OPT_ASSIGN_STMT

						if(checkBound(i))
						{
							retVal= stmt(i,102); //OPT_ASSIGN_stmt

							if(retVal==0)
							{
								return 0;
							}
						}
						else
						{
							parse_error();
							return 0;
						}
						//OPT_ASSIGN_STMT ENDS

						retVal=handleTokens(i,34);

						if(retVal==0)
						{
							return 0;
						}
						//STMT OF FOR LOOP

						retVal=handleTokens(i,20);

						if(retVal==0)
						{
							return 0;
						}

						//STMT

						if(checkBound(i))
						{

							retVal= stmt(i,0); //stmt

							if(retVal==0)
							{
								return 0;
							}
						}
						else
						{
							parse_error();
							return 0;
						}
						//STMT ENDS

						retVal=handleTokens(i,21);

						if(retVal==0)
						{
							return 0;
						}

						//STMT 
						if(checkBound(i))
						{

							retVal= stmt(i,0); //stmt

							if(retVal==0)
							{
								return 0;
							}
						}
						else
						{
							parse_error();
							return 0;
						}
						//STMT ENDS

						return i;

					}
						

					case 10: //if
					{
						node newNode(false, true, 0, 0, 0, "",0,0,"if_stmt");
						parseNodes.push_back(newNode);

						retVal= handleTokens(i,10);

						if(retVal==0)
						{
							return 0;
						}

						retVal=handleTokens(i,33);

						if(retVal==0)
						{
							return 0;
						}


						//COND_STMT

						if(checkBound(i))
						{

							retVal= stmt(i,101); //cond_stmt

							if(retVal==0)
							{
								return 0;
							}
						}
						else
						{
							parse_error();
							return 0;
						}

						// COND_STMT ENDS

						retVal=handleTokens(i,34);

						if(retVal==0)
						{
							return 0;
						}

						retVal=handleTokens(i,20);

						if(retVal==0)
						{
							return 0;
						}

						//STMT

						if(checkBound(i))
						{

							retVal= stmt(i,0); //stmt

							if(retVal==0)
							{
								return 0;
							}
						}
						else
						{
							parse_error();
							return 0;
						}
						//STMT ENDS

						retVal=handleTokens(i,21);

						if(retVal==0)
						{
							return 0;
						}

						//STMT 
						if(checkBound(i))
						{

							retVal= stmt(i,101); //cond_stmt

							if(retVal==0)
							{
								return 0;
							}
						}
						else
						{
							parse_error();
							return 0;
						}

						//OPT_ELSE
						if(checkBound(i))
						{

							retVal= stmt(i,104); //opt_ELSE_stmt

							if(retVal==0)
							{
								return 0;
							}
						}
						else
						{
							parse_error();
							return 0;
						}

						//STMT 
						if(checkBound(i))
						{

							retVal= stmt(i,0); //stmt

							if(retVal==0)
							{
								return 0;
							}
						}
						else
						{
							parse_error();
							return 0;
						}
						//STMT ENDS
						return i;

					}
						

					case 1: //ID := 
					{
						node newNode(false, true, 0, 0, 0, "",0,0,"assignment_stmt");
						parseNodes.push_back(newNode);

						retVal= handleTokens(i,1);

						if(retVal==0)
						{
							return 0;
						}

						retVal=handleTokens(i,32);

						if(retVal==0)
						{
							return 0;
						}
						//expr
						if(checkBound(i))
						{

							retVal= stmt(i,105); //expr

							if(retVal==0)
							{
								return 0;
							}
						}
						else
						{
							parse_error();
							return 0;
						}

						//; token handle
						retVal= handleTokens(i,24);

						if(retVal==0)
						{
							return 0;
						}

						//STMT 
						if(checkBound(i))
						{

							retVal= stmt(i,0); //stmt

							if(retVal==0)
							{
								return 0;
							}
						}
						else
						{
							parse_error();
							return 0;
						}
						//STMT ENDS

						return i;


					}	

						

					case 22: // [
					{
						node newNode(false, true, 0, 0, 0, "",0,0,"output_stmt");
						parseNodes.push_back(newNode);

						retVal= handleTokens(i,22);

						if(retVal==0)
						{
							return 0;
						}
						//expr
						if(checkBound(i))
						{

							retVal= stmt(i,105); //expr

							if(retVal==0)
							{
								return 0;
							}
						}
						else
						{
							parse_error();
							return 0;
						}

						retVal= handleTokens(i,23);

						if(retVal==0)
						{
							return 0;
						}

						retVal= handleTokens(i,24);

						if(retVal==0)
						{
							return 0;
						}


						//STMT 
						if(checkBound(i))
						{

							retVal= stmt(i,0); //stmt

							if(retVal==0)
							{
								return 0;
							}
						}
						else
						{
							parse_error();
							return 0;
						}
						//STMT ENDS

						return i;

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

					case 101: //expr
						{
							node newNode(false, true, 0, 0, 0, "",0,0,"expr");
							parseNodes.push_back(newNode);


							retVal= stmt(i,102); //102 for multiple expr

							if(retVal==0)
							{
								return 0;
							}

							retVal= stmt(i,201); //201 is A' for expr

							if(retVal==0)
							{
								return 0;
							}

							return i;
						}

					case 102: //multi_expr
						{
							node newNode(false, true, 0, 0, 0, "",0,0,"mult_expr");
							parseNodes.push_back(newNode);

							retVal= stmt(i,103); //102 for unary expr

							if(retVal==0)
							{
								return 0;
							}

							retVal= stmt(i,202); //201 is A' for mult_expr

							if(retVal==0)
							{
								return 0;
							}

							return i;

						}

					case 103: //unary_expr
						{
							node newNode(false, true, 0, 0, 0, "",0,0,"unary_expr");
							parseNodes.push_back(newNode);

							
							


								
						}
							


						



						


					default:
						cout<<"Unimplemented error"<<endl;
						break;


				}
			}

	
		
		


};

int main(int argc, char *argv[]){
	
	Lexical lex; 
	string s; 
	int i=0;
	string input[100]; 
	int ln=0; 
	string z;
	Parser par;


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

	lex.setString(z);
	lex.setArg(i);
	lex.analysis();
	//lex.printTokens();
	

		
return 0;	
}

