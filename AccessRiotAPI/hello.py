import time

def TimeLoop():
	timeTotal = 1 * 120#max will be set to two mins
	minuteMark = 0
	
	while timeTotal>0 :
		time.sleep(1)#sleep for one second
		timeTotal-=1#decrtement 1 second
		minuteMark+=1
		if minuteMark==60 :
		#every minute, call request
			#make call
			print('\nMinute passed\n')
			minuteMark=0
		
	#end loop
	
def IsGameRunning():
	isExitLoop = False;
	
	while isExitLoop == False :
	
		#is game running, and if so, call TimeLoop()
		userInput = ""
		userInput = input('\nWould you like to run the program for? Y/N ')
		if (userInput == 'y' or userInput == 'Y') :
		
			userInput = input('\nProgram requires game to run, is it running? Y/N ')
			if (userInput == 'y' or userInput == 'Y') :
			
				TimeLoop()
			
		
		elif (userInput == 'n' or userInput == 'N') :
		
			print('\nExiting')
			isExitLoop = True;
		
		else:print('\nInput not recognized ')


print("Hello world!")
IsGameRunning()