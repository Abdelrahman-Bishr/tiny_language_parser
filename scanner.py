
import random
import sys
import os
from collections import OrderedDict

def stripOfComments(line):
    newLine=line;
    comms=line.split('{');
    endComm=[]
    if(len(comms)>1):
       newLine=comms[0]
       endComm=[None]*(len(comms)-1)
       for i in range(1,len(comms)):
           comms[i].strip()
           endComm[i-1]=comms[i].split('}')[0];
           if(len(comms[i].split('}'))>1 ):
               newLine+=comms[i].split('}')[1];
           else:
               newLine+='#'
    return newLine,endComm


def isValid(str1): 
  
    # If first character is invalid 
    if (((ord(str1[0]) >= ord('a') and
          ord(str1[0]) <= ord('z')) or 
         (ord(str1[0]) >= ord('A') and 
          ord(str1[1]) <= ord('Z')) or 
          ord(str1[0]) == ord('_')) == False): 
        return False
  
    # Traverse the for the rest of the characters 
    for i in range(1, len(str1)): 
        if (((ord(str1[i]) >= ord('a') and 
              ord(str1[i]) <= ord('z')) or 
             (ord(str1[i]) >= ord('A') and 
              ord(str1[i]) <= ord('Z')) or 
             (ord(str1[i]) >= ord('0') and
              ord(str1[i]) <= ord('9')) or 
              ord(str1[i]) == ord('_')) == False): 
            return False
  
    # is a valid identifier 
    return True


def hasNumbers(inputString):

    return any(char.isdigit() for char in inputString)

def main() :
       reserved = {'if'    :  'IF','then'  :  'THEN','else'  :  'ELSE',
		   'repeat'  :  'REPEAT','until':  'UNTIL', 
			'write'  :  'WRITE','read'  :  'READ' ,  'end'  :  'END'
				}

       operators= {    '+'  :  'PLUS'	    ,'*'  :  'MULTIPLICATION', 
				'/'  :  'DIVISION'  ,'-'  : 'MINUS'}
       comparators=[':=','=','>','<'];
       comparatorsDict= {':=' :  'ASSIGN',
                     '='  :  'EQUAL' ,
                      '>':  'GREATER THAN'   , 
                     '<':  'LESS THAN',	
				}

       brackets={  	'('  :  'OPENBRACKET',    ')'  :  'CLOSEBRACKET',
				'{'  :  'L CURLY BRACE',      '}'  :  'R CURLY BRACE',
                ';' : 'SEMICOLOMN'
                }

       error = False
       file= open("input.txt","r")

#####=======================================================================================####
        ## separate comments and code
       lines,comments=stripOfComments(file.read());
       file.close()

        #write comments to their file
       commsFile=open('comments.txt','w');
       comms="";
       for comm in comments:
	       comms+=comm+"\n";
       commsFile.write(comms);
       commsFile.flush();
       commsFile.close();

        #write code to its own file
       codeFile=open('output.txt','r+');
       codeFile.truncate(0);
       code="";
       for line in lines:
	       code+=line+"";
       codeFile.write(code);
       codeFile.flush();
       codeFile.seek(0)

       finalOut=""
#####=======================================================================================####
       for line in codeFile :

#           finalOut+='\n\nline: '+line+'\n';

           temp = line[:]
           result = {}
           final ={}
#####=======================================================================================####

           # find operators#
           for item in operators:
                while  line.find(item) != -1:
 #and line[line.find(item)+1].isdigit():
                   if item=='-':
                       dum=line[line.find(item):].split(' ');
                    #    print('\n\n\n\n',dum[0],'\n\n\n\n');
                       if(dum[0].isdigit()):
                           print('++++++++++++++++++++++++++++++++++++++++++\n')
                        #    continue 
                   result.update( {line.find(item)  : item} )
                   final.update( {line.find(item)  : operators[item]} )

                #    replace it with space#
                   line=line.replace(item ," " * len(item),1)
#####=======================================================================================####

           # find comparators #
           for item in comparators:
               while  line.find(item) != -1:
                   result.update( {line.find(item)  : item} )
                   final.update( {line.find(item)  : comparatorsDict[item]} )

                   #replace it with space#
                   line=line.replace(item ," " * len(item),1)
#####=======================================================================================####

           # find brackets#
           for item in brackets:
               while  line.find(item) != -1:
                   result.update( {line.find(item)  : item} )
                   final.update( {line.find(item)  : brackets[item]} )

                    #replace it with space#
                   line=line.replace(item ," " * len(item),1)
#####=======================================================================================####

          
           #find id 
           id = ""
           done1 =  False
           error = False
           other = line.split()
           for item in other :
               if (item.isidentifier() ):
                   if( item in reserved.keys()):
                       continue;
                   if hasNumbers(item):
                       error = True
                       break
    
                   result.update( {line.find(item)  : item} )
                   final.update( {line.find(item)  : "identifier"} )
                   line=line.replace(item ," " * len(item),1)
           if error == True:
               print("error")
#####=======================================================================================####

           #find digit
           digit = ""
           done2 = False
           for item in temp :
                if(item.isdigit()):
                   digit +=item
                   done2 = True
                else :
                    if done2 == True:
                        result.update( {line.find(digit)  : digit} )
                        final.update( {line.find(digit)  : "NUMBER"} )
                        line=line.replace(digit ," " * len(digit),1)
                        digit =""
                        done2 = False

#####=======================================================================================####

            #find reserved  #
           another=line.split()
           for item in another :
               if item in reserved: 
                   result.update( {line.find(item)  : item} )
                   final.update( {line.find(item)  : reserved[item]} )
                   line=line.replace(item ," " * len(item),1)
        

           sorted_list = []
           for key in result:
               sorted_list.append(key)

           sorted_list.sort()
#####=======================================================================================####
            ###ERROR DETECTION
           for char in line:
               if(char !=' ' and char != '\n' and char != '\t' ):
                   error=True;
                   finalOut+='error\n';
                   print(line)
                   print('error 3shan shaker');
                   break;

#####=======================================================================================####
           if error == False:
                  for index in sorted_list:
                   print(result[index]," , ",final[index],);
                   finalOut+=(result[index]+" , "+final[index]+'\n');
       codeFile.truncate(0);
       codeFile.seek(0);
       codeFile.write(finalOut);
       codeFile.flush()
       codeFile.flush()
       codeFile.flush()
       codeFile.seek(0);
       codeFile.close()


               
       print("\n")


main()
           





