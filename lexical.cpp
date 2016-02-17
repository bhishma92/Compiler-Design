/* Lexical Analyzer */ 
/*   Please take the commandline arguments starting from 0 */

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class tools{
	public:
		
	bool checkLetter(char ar){
		if( (65<= int(ar) & int(ar) <= 90 ) ^ (97<= int(ar) & int(ar) <= 122 ) ){
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
		if( (temp == 33) ^ (temp > 35 & temp<=47) ^ (temp>=58 & temp<=64) ^ (123<=temp & temp<=126) ){
			return true;
		}
		return false;
	}


};

class Lexical : public tools 
{
	public:
		
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

                        stringstream ss,ss1,ss2;
                        string strNum,strNumP,strNumLen;
                        ss<<t; ss>>strNum;
                        ss1<<pos; ss1>>strNumP;
                        ss2<<len; ss2>>strNumLen;

			tokens[t] = "TID: " + strNum + ", " + "TYPE: " + type + "(" + typeName + ")" + ", " + "POS: " + strNumP + ", " + "LEN: " + strNumLen + ", " + "VALUE: " + val;	
			LEN=0;					
                        token++;
                        
		 
			//tokens[t] = "TID: " + to_string(t);
			//cout << tokens[t] << endl;
		}
		
	
		bool isInAlphabet(int dr){
                	if( (dr == 9) ^ (dr==10) ^ (dr >= 32 & dr <= 126) ){
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
                                                                //cout<<checkSpecialChar(input.at(i)) <<endl;
                        while( checkSpecialChar(input.at(a)) ){
				cout<<checkSpecialChar(input.at(a))<<endl;
                        	LEN++;
				a++;
				cout<< a<<"in bad char"<< endl;                                                                                              
                        }
			//cout<<"out of loop now"<<endl;
			argValue[token]=1;
                        addToken(tokens, token, "99", "ERR3", spec, LEN, "") ;
			//cout<< a <<endl;
			
                     	  
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

                		if( checkLetter(input.at(i)) ){
                        		
					//cout<<"you are in identifier lexical" <<endl;	
				
					int init= i;
                        		while(i<=length){
                                		
                      
						LEN++;
						
                        			if(input.substr(init, LEN)== "for"){
                                			addToken(tokens, token, "8", "FOR", i-2, 3, "");
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
						
						else if(!checkLetter(input.at(i))){
						//	cout<< i <<endl;
							addToken(tokens, token, "1", "IDENTIFIER", init,LEN, input.substr(init,LEN-1) );
							break;
				
						}
												
                        			else if(i ==length){
							
                                			addToken(tokens, token, "1", "IDENTIFIER", init,LEN, input.substr(init,LEN) );
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
							if((input.at(i) == '.')){
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
								addToken(tokens, token, "2", "STR", quoteLoc+1, LEN, input.substr(quoteLoc+1,LEN) );
								i++;
								break;
							}
						
							else if(!(isInAlphabet( int(input.at(i)) )) ){
								argValue[token]=1;
								addToken(tokens, token, "98", "ERR2", quoteLoc+1, LEN,"");
								break;
							}
							else if((i==length) & (int(input.at(i)) != 34) ){
								argValue[token]=1;
								addToken(tokens, token, "98", "ERR2", quoteLoc+1, LEN, "");
								i++;
								break;
							}
							else if (int(input.at(i))==10 ){
								argValue[token]=1;
								addToken(tokens, token, "98", "ERR2", quoteLoc+1, LEN, "");
                                                                i++;
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
                                        addToken(tokens, token, "5", "WHITESPACE", i, 1, "" );
					
					i++;        
                                }
				

				/* comment lexical= assuming any line after # is a comment, next line is normal */
				
				else if ( input.at(i) == '#'){
					quoteLoc=i;
					while(i != length ){
						i++;
						LEN++;
					}
					
					argValue[token]=1;	
					addToken(tokens, token, "7", "COMMENT", quoteLoc,LEN, input.substr(quoteLoc+1,length-quoteLoc) );
					i++;
					
					
				}

				else if(isInAlphabet(int(input.at(i))) ){
					if(int(input.at(i)) == 33 ){
						addToken(tokens, token,"12",  "!", i,1, "" );
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
					else if ( int(input.at(i)) == 60 ){
						addToken(tokens, token,"26",  "<", i, 1, "" );
					}
					else if(int(input.at(i)) == 62 ){
						addToken(tokens, token,"27",  ">", i,1, "" );
					}
					else if(int(input.at(i)) == 61 ){
						addToken(tokens, token,"28", "=", i, 1, "" );
					}
					else if(int(input.at(i)) == 40 ){
                                                addToken(tokens, token,"29", "(", i, 1, "" );
                                        }
					else if(int(input.at(i)) == 41 ){
                                                addToken(tokens, token,"28", ")", i, 1, "" );
                                        }			
					else{
						isBadChar(i);
					}
					i++;
				}																
			}

		}
		
		void addTotal(){
				length++;
                stringstream a1,a2;
                string length1,token1;
                a1<<length; a1>>length1;
                a2<<token; a2>>token1;
                   
			total= string("Totals: ") + "len: " + length1 + ", " + "tokens = " + token1 + "," + "printed = " ;  
		}																											

	 	void printTokens(){
			
			addTotal();
				
			int cnt=0;
                
                	if(arg==0){
                      
				for(int m=0; m<=token;m++){
					cout<<tokens[m]<<endl;
					cnt++;
				}
                      cnt--;
                      stringstream c1;
                      string cnt1;
                      c1<<cnt; c1>>cnt1;
				cout<< total + cnt1 <<endl;
			}
																						
			else if(arg == 1){
				for(int m=0; m<=token;m++){
                                        if(argValue[m] != 1){ /* everything except comment newLine whitespace */
						cout<<tokens[m]<<endl;
						cnt++;
					}
                                }
                       cnt--;
                      stringstream c2;
                      string cnt2;
                      c2<<cnt; c2>>cnt2;
				cout<< total + cnt2 <<endl;
							}

			else if (arg == 2){
				 for(int m=0; m<=token;m++){
                                        if(argValue[m] == 1){ /* only comment newLine whitespace */
                                                cout<<tokens[m]<<endl;
						cnt++;
                                        }
                                }
                      cnt--;
                      stringstream c3;
                      string cnt3;
                      c3<<cnt; c3>>cnt3;
				cout<< total + cnt3 <<endl;

							}
											
			else{
				for(int m=0; m<=token;m++){
                                        cout<<tokens[m]<<endl;
                                }

				cout<< total + "1" <<endl;
			}  											      
                }

	Lexical(){}
		
	
};


int main(int argc, char *argv[]){
	
	Lexical lex; string s; int i;
	string input[100]; int ln=0; string z;

while(1){

	if(argc==1){
		i=0;
		break;
	}

	else if(*argv[1] == '0'){
		i=0;
		break;
	}
	else if (*argv[1] == '1'){
		i=1;
		break;
	}
	else if (*argv[1] == '2'){
		i=2;
		break;
	}
	else{
		i=3;
		break;
	}
	
}
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
	lex.printTokens();
	


					
	
	
	
	
	



	
return 0;	
}
