print("Hello world!")

def TimeLoop():
	timeTotal = h * 3600#max will be set to an hour
	minuteMark = 0
	
	while(timeTotal>0):
		time.sleep(1)#sleep for one second
		timeTotal-=1#decrtement 1 second
		minuteMark+=1
		if(minuteMark==60)
		{#every minute, call request
			#make call
			minuteMark=0
		}
	#end loop
    
def IsGameRunning():
    isExitLoop = False;
    
    while(isExitLoop == False)
    {
        #is game running, and if so, call TimeLoop()
        userInput = input('\nWould you like to run the program for? Y/N ', userInput)
        if(userInput == 'y' || userInput == 'Y')
        {
            userInput = input('\nProgram requires game to run, is it running? Y/N ', userInput)
            if(userInput == 'y' || userInput == 'Y')
            {
                TimeLoop()
            }
        }
        else if(userInput == 'y' || userInput == 'Y')
        {
            
        }
        else{print('\nInput not recognized ')}
    }